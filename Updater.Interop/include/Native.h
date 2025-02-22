#pragma once

class Native
{
public:

    /// <summary>
    /// 
    /// </summary>
    /// <param name="sahPath"></param>
    /// <param name="safPath"></param>
    /// <param name="progressCallback"></param>
    static void DataBuilder(const wchar_t* sahPath, const wchar_t* safPath, const void(*progressCallback)() = nullptr);

    /// <summary>
    /// 
    /// </summary>
    /// <param name="targetSahPath"></param>
    /// <param name="targetSafPath"></param>
    /// <param name="updateSahPath"></param>
    /// <param name="updateSafPath"></param>
    /// <param name="progressCallback"></param>
    static void DataPatcher(
        const wchar_t* targetSahPath, 
        const wchar_t* targetSafPath, 
        const wchar_t* updateSahPath, 
        const wchar_t* updateSafPath, 
        const void(*progressCallback)() = nullptr
    );

    /// <summary>
    /// 
    /// </summary>
    /// <param name="sahPath"></param>
    /// <returns></returns>
    static int GetSahFileCount(const wchar_t* sahPath);

    /// <summary>
    /// 
    /// </summary>
    /// <param name="sahPath"></param>
    /// <param name="safPath"></param>
    /// <param name="lstPath"></param>
    /// <param name="progressCallback"></param>
    static void RemoveFiles(const wchar_t* sahPath, const wchar_t* safPath, const wchar_t* lstPath, const void(*progressCallback)() = nullptr);
};
