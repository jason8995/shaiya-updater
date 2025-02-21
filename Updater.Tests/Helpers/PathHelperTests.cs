using Updater.Helpers;

namespace Updater.Tests.Helpers
{
    public class PathHelperTests
    {
        [TestCase("a/b/c")]
        [TestCase("a\\b\\c")]
        public void MakePreferredTest(string path)
        {
            var preferred = PathHelper.MakePreferred(path);
            foreach (char value in preferred)
            {
                if (PathHelper.IsDirectorySeparator(value))
                    Assert.That(value, Is.EqualTo(Path.DirectorySeparatorChar));
            }
        }

        [TestCase("/a/b/c/", ExpectedResult = 3)]
        [TestCase("a\\b\\c", ExpectedResult = 3)]
        [TestCase("a/b/c/d", ExpectedResult = 4)]
        public int SplitTest(string path)
        {
            return PathHelper.Split(path).Length;
        }
    }
}
