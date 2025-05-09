﻿using System.ComponentModel;
using System.Diagnostics;
using System.IO;
using System.Net.Http;
using System.Windows;
using Updater.Common;
using Updater.Configuration;
using Updater.Core;
using Updater.Extensions;
using Updater.Helpers;
using Updater.Interop;
using Updater.Resources;

namespace Updater
{
    public static class Program
    {
        public static void DoWork(HttpClient httpClient, BackgroundWorker backgroundWorker)
        {
            ClientConfiguration? clientConfiguration = null;
            ServerConfiguration? serverConfiguration = null;

            try
            {
                serverConfiguration = new ServerConfiguration(httpClient);
                clientConfiguration = new ClientConfiguration();

                if (serverConfiguration.UpdaterVersion > Constants.UpdaterVersion)
                {
                    backgroundWorker.ReportProgress(0, new ProgressReport(Strings.ProgressMessage1));
                    UpdaterPatcher(httpClient);
                    return;
                }

                if (serverConfiguration.PatchFileVersion > clientConfiguration.CurrentVersion)
                {
                    backgroundWorker.ReportProgress(0, new ProgressReport(1));
                    backgroundWorker.ReportProgress(0, new ProgressReport(2));

                    int progressMax = serverConfiguration.PatchFileVersion - clientConfiguration.CurrentVersion;
                    int progressValue = 1;

                    while (clientConfiguration.CurrentVersion < serverConfiguration.PatchFileVersion)
                    {
                        var progressMessage = string.Format(Strings.ProgressMessage2, progressValue, progressMax);
                        backgroundWorker.ReportProgress(0, new ProgressReport(progressMessage));

                        var patch = new Patch(clientConfiguration.CurrentVersion + 1);
                        httpClient.DownloadFile(patch.Url, patch.Path);

                        if (!File.Exists(patch.Path))
                        {
                            backgroundWorker.ReportProgress(0, new ProgressReport(Strings.ProgressMessage3));
                            return;
                        }

                        backgroundWorker.ReportProgress(0, new ProgressReport(Strings.ProgressMessage4));
                        clientConfiguration.StartUpdate = "EXTRACT_START";

                        // Issue: antivirus software could be scanning a file when this method tries to overwrite it.
                        if (!patch.ExtractToCurrentDirectory())
                        {
                            backgroundWorker.ReportProgress(0, new ProgressReport(Strings.ProgressMessage5));
                            return;
                        }

                        clientConfiguration.StartUpdate = "EXTRACT_END";
                        File.Delete(patch.Path);

                        backgroundWorker.ReportProgress(0, new ProgressReport(Strings.ProgressMessage6));
                        clientConfiguration.StartUpdate = "UPDATE_START";

                        DataPatcher(backgroundWorker);

                        clientConfiguration.StartUpdate = "UPDATE_END";
                        clientConfiguration.CurrentVersion++;
                        progressValue++;

                        var percentProgress = MathHelper.CalculatePercentage(clientConfiguration.CurrentVersion, serverConfiguration.PatchFileVersion);
                        if (percentProgress > 0)
                            backgroundWorker.ReportProgress(percentProgress, new ProgressReport(Strings.ProgressMessage7, 2));
                    }

                    backgroundWorker.ReportProgress(0, new ProgressReport(Strings.ProgressMessage8));
                    DataBuilder(backgroundWorker);
                    backgroundWorker.ReportProgress(0, new ProgressReport(Strings.ProgressMessage7));
                }
            }
            catch (Exception ex)
            {
                var caption = Application.ResourceAssembly.GetName().Name;
                MessageBox.Show(ex.ToString(), caption, MessageBoxButton.OK, MessageBoxImage.Error);
            }
            finally
            {
                clientConfiguration?.Save();
                clientConfiguration?.Dispose();
                serverConfiguration?.Dispose();
            }
        }

        private static void DataBuilder(BackgroundWorker backgroundWorker)
        {
            if (!File.Exists("data.sah") || !File.Exists("data.saf"))
                return;

            var fileCount = Function.GetSahFileCount("data.sah");
            if (fileCount <= 0)
                throw new FileFormatException();

            var progressReport = new ProgressReport(1);
            var progress = new Progress(backgroundWorker, progressReport, fileCount, 1);
            Function.DataBuilder("data.sah", "data.saf", progress.PerformStep);
        }

        private static void DataPatcher(BackgroundWorker backgroundWorker)
        {
            if (File.Exists("delete.lst"))
            {
                var paths = File.ReadAllLines("delete.lst");
                var fileCount = paths.Length;
                if (fileCount <= 0)
                    throw new FileFormatException();

                var progressReport = new ProgressReport(1);
                var progress = new Progress(backgroundWorker, progressReport, fileCount, 1);
                Function.RemoveFiles("data.sah", "data.saf", "delete.lst", progress.PerformStep);
                File.Delete("delete.lst");
            }

            if (File.Exists("update.sah") && File.Exists("update.saf"))
            {
                var fileCount = Function.GetSahFileCount("update.sah");
                if (fileCount <= 0)
                    throw new FileFormatException();

                var progressReport = new ProgressReport(1);
                var progress = new Progress(backgroundWorker, progressReport, fileCount, 1);
                Function.DataPatcher("data.sah", "data.saf", "update.sah", "update.saf", progress.PerformStep);

                File.Delete("update.sah");
                File.Delete("update.saf");
            }
        }

        /// <summary>
        /// Downloads a new updater, starts a client process, passing "new updater" as the 
        /// command-line argument, and terminates the current process.
        /// 
        /// Expect the client to delete the old updater, rename the new updater and create 
        /// an updater process.
        /// </summary>
        private static void UpdaterPatcher(HttpClient httpClient)
        {
            var newUpdater = new NewUpdater();
            httpClient.DownloadFile(newUpdater.Url, newUpdater.Path);

            if (!File.Exists(newUpdater.Path))
                return;

            var fileName = Path.Combine(Directory.GetCurrentDirectory(), "game.exe");
            Process.Start(fileName, "new updater");

            var currentProcess = Process.GetCurrentProcess();
            currentProcess.Kill();
        }
    }
}
