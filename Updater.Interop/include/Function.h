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
        static void DataBuilder(const String^ sahPath, const String^ safPath, Action^ progressCallback);

        /// <summary>
        /// 
        /// </summary>
        /// <param name="targetSahPath"></param>
        /// <param name="targetSafPath"></param>
        /// <param name="updateSahPath"></param>
        /// <param name="updateSafPath"></param>
        /// <param name="progressCallback"></param>
        static void DataPatcher(
            const String^ targetSahPath, 
            const String^ targetSafPath, 
            const String^ updateSahPath, 
            const String^ updateSafPath, 
            Action^ progressCallback
        );

        /// <summary>
        /// 
        /// </summary>
        /// <param name="sahPath"></param>
        /// <returns></returns>
        static int GetSahFileCount(const String^ sahPath);

        /// <summary>
        /// 
        /// </summary>
        /// <param name="sahPath"></param>
        /// <param name="safPath"></param>
        /// <param name="lstPath"></param>
        /// <param name="progressCallback"></param>
        static void RemoveFiles(const String^ sahPath, const String^ safPath, const String^ lstPath, Action^ progressCallback);
    };
}
