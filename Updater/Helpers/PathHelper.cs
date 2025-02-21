using System.IO;

namespace Updater.Helpers
{
    public static class PathHelper
    {
        public static bool IsDirectorySeparator(char value)
        {
            return value == '/' || value == '\\';
        }

        public static string MakePreferred(string path)
        {
            var newChar = Path.DirectorySeparatorChar;
            return path.Replace('/', newChar).Replace('\\', newChar);
        }

        public static string[] Split(string path)
        {
            var separator = new char[] { '/', '\\' };
            return path.Split(separator, StringSplitOptions.RemoveEmptyEntries);
        }
    }
}
