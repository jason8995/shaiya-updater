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
        /// Converts each separator to a preferred separator as needed.
        /// </summary>
        /// <param name="path"></param>
        /// <returns></returns>
        /// <remarks>https://learn.microsoft.com/en-us/cpp/standard-library/path-class?view=msvc-170#make_preferred</remarks>
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
