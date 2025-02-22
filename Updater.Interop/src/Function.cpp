#include <vcclr.h>
#include "include/Function.h"
#include "include/Native.h"
using namespace System;
using namespace System::Runtime::InteropServices;
using namespace Updater::Interop;

void Function::DataBuilder(const String^ sahPath, const String^ safPath, Action^ progressCallback)
{
    cli::pin_ptr<const wchar_t> gcSahPath = PtrToStringChars(sahPath);
    cli::pin_ptr<const wchar_t> gcSafPath = PtrToStringChars(safPath);

    if (!progressCallback)
    {
        Native::DataBuilder(gcSahPath, gcSafPath);
    }
    else
    {
        auto gch = GCHandle::Alloc(progressCallback);
        auto ptr = Marshal::GetFunctionPointerForDelegate(progressCallback).ToPointer();
        auto callback = static_cast<const void(*)()>(ptr);

        Native::DataBuilder(gcSahPath, gcSafPath, callback);
        gch.Free();
    }
}

void Function::DataPatcher(
    const String^ targetSahPath, 
    const String^ targetSafPath, 
    const String^ updateSahPath, 
    const String^ updateSafPath, 
    Action^ progressCallback
)
{
    cli::pin_ptr<const wchar_t> gcTargetSahPath = PtrToStringChars(targetSahPath);
    cli::pin_ptr<const wchar_t> gcTargetSafPath = PtrToStringChars(targetSafPath);
    cli::pin_ptr<const wchar_t> gcUpdateSahPath = PtrToStringChars(updateSahPath);
    cli::pin_ptr<const wchar_t> gcUpdateSafPath = PtrToStringChars(updateSafPath);

    if (!progressCallback)
    {
        Native::DataPatcher(gcTargetSahPath, gcTargetSafPath, gcUpdateSahPath, gcUpdateSafPath);
    }
    else
    {
        auto gch = GCHandle::Alloc(progressCallback);
        auto ptr = Marshal::GetFunctionPointerForDelegate(progressCallback).ToPointer();
        auto callback = static_cast<const void(*)()>(ptr);

        Native::DataPatcher(gcTargetSahPath, gcTargetSafPath, gcUpdateSahPath, gcUpdateSafPath, callback);
        gch.Free();
    }
}

int Function::GetSahFileCount(const String^ sahPath)
{
    cli::pin_ptr<const wchar_t> gcSahPath = PtrToStringChars(sahPath);
    return Native::GetSahFileCount(gcSahPath);
}

void Function::RemoveFiles(const String^ sahPath, const String^ safPath, const String^ lstPath, Action^ progressCallback)
{
    cli::pin_ptr<const wchar_t> gcSahPath = PtrToStringChars(sahPath);
    cli::pin_ptr<const wchar_t> gcSafPath = PtrToStringChars(safPath);
    cli::pin_ptr<const wchar_t> gcLstPath = PtrToStringChars(lstPath);

    if (!progressCallback)
    {
        Native::RemoveFiles(gcSahPath, gcSafPath, gcLstPath);
    }
    else
    {
        auto gch = GCHandle::Alloc(progressCallback);
        auto ptr = Marshal::GetFunctionPointerForDelegate(progressCallback).ToPointer();
        auto callback = static_cast<const void(*)()>(ptr);

        Native::RemoveFiles(gcSahPath, gcSafPath, gcLstPath, callback);
        gch.Free();
    }
}
