#pragma once
using namespace System;

namespace Updater::Interop
{
    public ref class Function sealed
    {
    public:

        /// <summary>
        /// 
        /// </summary>
        /// <param name="sahPath"></param>
        /// <param name="safPath"></param>
        /// <param name="progressCallback"></param>
        static void DataBuilder(String^ sahPath, String^ safPath, Action^ progressCallback);

        /// <summary>
        /// 
        /// </summary>
        /// <param name="targetSahPath"></param>
        /// <param name="targetSafPath"></param>
        /// <param name="updateSahPath"></param>
        /// <param name="updateSafPath"></param>
        /// <param name="progressCallback"></param>
        static void DataPatcher(String^ targetSahPath, String^ targetSafPath, String^ updateSahPath, String^ updateSafPath, Action^ progressCallback);

        /// <summary>
        /// 
        /// </summary>
        /// <param name="sahPath"></param>
        /// <returns></returns>
        static int GetSahFileCount(String^ sahPath);

        /// <summary>
        /// 
        /// </summary>
        /// <param name="sahPath"></param>
        /// <param name="safPath"></param>
        /// <param name="lstPath"></param>
        /// <param name="progressCallback"></param>
        static void RemoveFiles(String^ sahPath, String^ safPath, String^ lstPath, Action^ progressCallback);
    };
}
