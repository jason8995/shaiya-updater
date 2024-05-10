﻿using System.Runtime.InteropServices;

namespace Updater.Common
{
    static class Win32
    {
        [DllImport("user32", EntryPoint = "FindWindowW", CharSet = CharSet.Unicode)]
        public static extern IntPtr FindWindowW(string? className, string? windowName);

        [DllImport("kernel32", EntryPoint = "GetPrivateProfileIntW", CharSet = CharSet.Unicode)]
        public static extern uint GetPrivateProfileIntW(string section, string key, int _default, string fileName);

        [DllImport("kernel32", EntryPoint = "GetPrivateProfileStringW", CharSet = CharSet.Unicode)]
        public static extern uint GetPrivateProfileStringW(string? section, string? key, string? _default, char[] output, uint size, string fileName);

        [DllImport("kernel32", EntryPoint = "WritePrivateProfileStringW", CharSet = CharSet.Unicode)]
        public static extern int WritePrivateProfileStringW(string section, string? key, string? value, string fileName);
    }
}
