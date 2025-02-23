using Updater.Helpers;

namespace Updater.Tests.Helpers
{
    [TestFixture]
    public class PathHelperTests
    {
        [Test]
        public void IsDirectorySeparatorTest()
        {
            Assert.Multiple(() =>
            {
                Assert.That(PathHelper.IsDirectorySeparator(Path.AltDirectorySeparatorChar), Is.True);
                Assert.That(PathHelper.IsDirectorySeparator(Path.DirectorySeparatorChar), Is.True);
            });
        }

        [TestCase("/a/b/c/")]
        [TestCase("a/b/c/d")]
        public void MakePreferredTest(string path)
        {
            var preferred = PathHelper.MakePreferred(path);
            foreach (char value in preferred)
            {
                if (PathHelper.IsDirectorySeparator(value))
                    Assert.That(value, Is.EqualTo(Path.DirectorySeparatorChar));
            }
        }

        [TestCase("/", ExpectedResult = 0)]
        [TestCase("/a/b/c/", ExpectedResult = 3)]
        [TestCase("a/b/c/d", ExpectedResult = 4)]
        public int SplitTest(string path)
        {
            return PathHelper.Split(path).Length;
        }
    }
}
