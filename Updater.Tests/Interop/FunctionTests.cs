using Updater.Interop;

namespace Updater.Tests.Interop
{
    [TestFixture]
    public class FunctionTests
    {
        private int ProgressValue { get; set; }
        private void ProgressCallback() => ProgressValue++;

        [SetUp]
        public void SetUp()
        {
            ProgressValue = 0;
        }

        [TestCase("Interop/data.sah", "Interop/data.saf", "Interop/update.sah", "Interop/update.saf"), Order(1)]
        public void DataPatcherTest(string targetSahPath, string targetSafPath, string updateSahPath, string updateSafPath)
        {
            var fileCount = Function.GetSahFileCount(updateSahPath);
            Function.DataPatcher(targetSahPath, targetSafPath, updateSahPath, updateSafPath, ProgressCallback);
            Assert.That(ProgressValue, Is.EqualTo(fileCount));
        }

        [TestCase("Interop/data.sah", "Interop/data.saf", "Interop/delete.lst"), Order(2)]
        public void RemoveFilesTest(string sahPath, string safPath, string lstPath)
        {
            var paths = File.ReadAllLines(lstPath);
            var fileCount = paths.Length;

            Function.RemoveFiles(sahPath, safPath, lstPath, ProgressCallback);
            Assert.That(ProgressValue, Is.EqualTo(fileCount));
        }

        [TestCase("Interop/data.sah", "Interop/data.saf"), Order(3)]
        public void DataBuilderTest(string sahPath, string safPath)
        {
            var fileCount = Function.GetSahFileCount(sahPath);
            Function.DataBuilder(sahPath, safPath, ProgressCallback);
            Assert.That(ProgressValue, Is.EqualTo(fileCount));
        }
    }
}
