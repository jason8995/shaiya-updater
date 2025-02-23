using System.IO;
using System.Runtime.InteropServices;

namespace Updater.Helpers
{
    public static class PathHelper
    {
        /// <summary>
        /// 
        /// </summary>
        /// <param name="value"></param>
        /// <returns></returns>
        public static bool IsDirectorySeparator(char value)
        {
            return value == Path.AltDirectorySeparatorChar || value == Path.DirectorySeparatorChar;
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="path"></param>
        /// <returns>See std::filesystem::path::make_preferred docs.</returns>
        public static string MakePreferred(string path)
        {
            if (RuntimeInformation.IsOSPlatform(OSPlatform.Windows))
                return path.Replace(Path.AltDirectorySeparatorChar, Path.DirectorySeparatorChar);
            else
                return path;
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="path"></param>
        /// <returns></returns>
        public static string[] Split(string path)
        {
            var separator = new char[] { Path.AltDirectorySeparatorChar, Path.DirectorySeparatorChar };
            return path.Split(separator, StringSplitOptions.RemoveEmptyEntries);
        }
    }
}
