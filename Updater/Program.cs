﻿using System.ComponentModel;
using System.Diagnostics;
using System.IO;
using System.Net.Http;
using Parsec.Shaiya.Data;
using Updater.Common;
using Updater.Core;

namespace Updater
{
    public static class Program
    {
        public static void DoWork(HttpClient httpClient, BackgroundWorker worker)
        {
            var serverCfg = new ServerConfiguration(httpClient);
            var clientCfg = new ClientConfiguration();
            
            if (serverCfg.UpdaterVersion > Constants.UpdaterVersion)
            {
                TryNewUpdater(httpClient, worker);
                return;
            }

            if (serverCfg.PatchFileVersion > clientCfg.CurrentVersion)
            {
                uint progressMax = serverCfg.PatchFileVersion - clientCfg.CurrentVersion;
                uint progressValue = 1;

                while (clientCfg.CurrentVersion < serverCfg.PatchFileVersion)
                {
                    var version = clientCfg.CurrentVersion + 1;
                    var patch = new Patch(version);

                    var progressMessage = string.Format(Constants.ProgressMessage1, progressValue, progressMax);
                    worker.ReportProgress(0, progressMessage);

                    Util.DownloadToFile(httpClient, patch.Url, patch.Path);

                    if (!File.Exists(patch.Path))
                    {
                        worker.ReportProgress(0, Constants.ProgressMessage2);
                        break;
                    }

                    worker.ReportProgress(0, Constants.ProgressMessage3);
                    clientCfg.Write("StartUpdate", "EXTRACT_START");

                    if (Util.ExtractZipFile(patch.Path) != 0)
                    {
                        worker.ReportProgress(0, Constants.ProgressMessage4);
                        break;
                    }

                    clientCfg.Write("StartUpdate", "EXTRACT_END");
                    File.Delete(patch.Path);

                    worker.ReportProgress(0, Constants.ProgressMessage5);
                    clientCfg.Write("StartUpdate", "UPDATE_START");

                    if (DataPatcher(worker) != 0)
                    {
                        worker.ReportProgress(0, Constants.ProgressMessage6);
                        break;
                    }

                    clientCfg.Write("StartUpdate", "UPDATE_END");

                    ++clientCfg.CurrentVersion;
                    ++progressValue;

                    var percentProgress = ((double)clientCfg.CurrentVersion / serverCfg.PatchFileVersion) * 100;
                    if (percentProgress != 0)
                    {
                        worker.ReportProgress((int)percentProgress, 2);
                        worker.ReportProgress((int)percentProgress, Constants.ProgressMessage7);
                    }

                    if (clientCfg.Write("CurrentVersion", clientCfg.CurrentVersion.ToString()) == 0)
                    {
                        worker.ReportProgress(0, Constants.ProgressMessage8);
                        break;
                    }
                }
            }
        }

        public static int DataPatcher(BackgroundWorker worker)
        {
            try
            {
                var data = new Data("data.sah", "data.saf");
                var update = new Data("update.sah", "update.saf");

                if (File.Exists("delete.lst"))
                {
                    data.RemoveFilesFromLst("delete.lst");
                    data.Sah.Write(data.Sah.Path);
                    File.Delete("delete.lst");
                }

                if (update.FileCount == 0)
                    return -1;

                int progressValue = 0;

                void callback()
                {
                    ++progressValue;
                    var percentProgress = ((double)progressValue / update.FileCount) * 100;
                    worker.ReportProgress((int)percentProgress, 1);
                }

                using var dataPatcher = new DataPatcher();
                dataPatcher.Patch(data, update, callback);
                data.Sah.Write(data.Sah.Path);

                File.Delete("update.sah");
                File.Delete("update.saf");
                return 0;
            }
            catch (Exception ex)
            {
                var log = new Log();
                log.Write(ex.ToString());
                return -1;
            }
        }

        public static void TryNewUpdater(HttpClient httpClient, BackgroundWorker worker)
        {
            try
            {
                worker.ReportProgress(0, Constants.ProgressMessage0);

                var newUpdater = new NewUpdater();
                Util.DownloadToFile(httpClient, newUpdater.Url, NewUpdater.FileName);

                if (File.Exists(NewUpdater.FileName))
                {
                    worker.ReportProgress(100, 2);

                    var fileName = Path.Combine(Directory.GetCurrentDirectory(), "game.exe");
                    Process.Start(fileName, "new updater");
                    Process.GetCurrentProcess().Kill();
                }
                else
                {
                    worker.ReportProgress(0, Constants.ProgressMessage2);
                }
            }
            catch (Exception ex)
            {
                var log = new Log();
                log.Write(ex.ToString());
            }
        }
    }
}
