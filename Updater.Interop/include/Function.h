#pragma once
using namespace System;

namespace Updater::Interop
{
    public ref class Function sealed
    {
    public:

        static void DataBuilder(const String^ sahPath, const String^ safPath, Action^ progressCallback);

        static void DataPatcher(
            const String^ targetSahPath, 
            const String^ targetSafPath, 
            const String^ updateSahPath, 
            const String^ updateSafPath, 
            Action^ progressCallback
        );

        static int GetSahFileCount(const String^ sahPath);
        static void RemoveFiles(const String^ sahPath, const String^ safPath, const String^ lstPath, Action^ progressCallback);
    };
}
