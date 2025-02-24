using System.IO;
using System.Runtime.InteropServices;

namespace Updater.Helpers
{
    public static class PathHelper
    {
        /// <summary>
        /// Returns a value that indicates whether the specified character is a directory separator.
        /// </summary>
        /// <param name="value"></param>
        /// <returns></returns>
        public static bool IsDirectorySeparator(char value)
        {
            return value == Path.AltDirectorySeparatorChar || value == Path.DirectorySeparatorChar;
        }

        /// <summary>
        /// On a Windows system, converts each separator to a preferred separator as needed. On a POSIX system, 
        /// the generic format and the native format are the same.
        /// </summary>
        /// <param name="path"></param>
        /// <returns></returns>
        public static string MakePreferred(string path)
        {
            if (RuntimeInformation.IsOSPlatform(OSPlatform.Windows))
                return path.Replace(Path.AltDirectorySeparatorChar, Path.DirectorySeparatorChar);
            else
                return path;
        }

        /// <summary>
        /// Splits a path into components based on directory separators.
        /// </summary>
        /// <param name="path"></param>
        /// <returns>A string array containing the components delimited by directory separators.</returns>
        public static string[] Split(string path)
        {
            var separator = new char[] { Path.AltDirectorySeparatorChar, Path.DirectorySeparatorChar };
            return path.Split(separator, StringSplitOptions.RemoveEmptyEntries);
        }
    }
}
