#pragma once

class Native
{
public:

    static void DataBuilder(const wchar_t* sahPath, const wchar_t* safPath, const void(*progressCallback)() = nullptr);

    static void DataPatcher(
        const wchar_t* targetSahPath, 
        const wchar_t* targetSafPath, 
        const wchar_t* updateSahPath, 
        const wchar_t* updateSafPath, 
        const void(*progressCallback)() = nullptr
    );

    static int GetSahFileCount(const wchar_t* sahPath);
    static void RemoveFiles(const wchar_t* sahPath, const wchar_t* safPath, const wchar_t* lstPath, const void(*progressCallback)() = nullptr);
};
