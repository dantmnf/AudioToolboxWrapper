#define UNICODE
#include <windows.h>
#include <shlobj.h>
#include <shlwapi.h>
#include <stdio.h>
#include <stdint.h>
#include <AudioToolbox/AudioToolbox.h>
#define LIBNAME "CoreAudioToolbox.dll"
#define LIBNAMEW TEXT(LIBNAME)

#ifdef _WIN64
#define QTFILES L"QTfiles64"
#else
#define QTFILES L"QTfiles"
#endif

#define FNTYPE(name) __TYPEOF_##name
#define DECLARE_FUNCTION(Tret, callconv, name, ...) typedef Tret (callconv * __TYPEOF_##name)(__VA_ARGS__); FNTYPE(name) p##name; Tret callconv name(__VA_ARGS__)

#define FILL(hlib, name)  p ## name = (FNTYPE(name))GetProcAddress(hlib, #name)
#define CALL_FUNCTION(name, ...) p ## name(__VA_ARGS__)
#define NSExecutableLoadError 3587

#define LOADLIB_GUARD               \
  if (!prepared)                    \
  {                                 \
    PrepareLazyLoad();              \
    if (!prepared)                  \
    {                               \
      return NSExecutableLoadError; \
    }                               \
  }

static HMODULE hTargetLib = NULL;
static void PrepareLazyLoad();
static volatile LONG preparing = 0, prepared = 0;

DECLARE_FUNCTION(OSStatus, __cdecl, AudioConverterNew, 
  const AudioStreamBasicDescription *inSourceFormat,
  const AudioStreamBasicDescription *inDestinationFormat,
  AudioConverterRef *outAudioConverter)
{
  LOADLIB_GUARD;
  return CALL_FUNCTION(AudioConverterNew, inSourceFormat, inDestinationFormat, outAudioConverter);
}

DECLARE_FUNCTION(OSStatus, __cdecl, AudioConverterDispose, AudioConverterRef inAudioConverter)
{
  LOADLIB_GUARD;
  return CALL_FUNCTION(AudioConverterDispose, inAudioConverter);
}

DECLARE_FUNCTION(OSStatus, __cdecl, AudioConverterReset, AudioConverterRef inAudioConverter){
  LOADLIB_GUARD;
  return CALL_FUNCTION(AudioConverterReset, inAudioConverter);
}

DECLARE_FUNCTION(OSStatus, __cdecl, AudioConverterGetProperty,
    AudioConverterRef inAudioConverter,
    AudioConverterPropertyID inPropertyID,
    UInt32 *ioPropertyDataSize,
    void *outPropertyData)
{
  LOADLIB_GUARD;
  return CALL_FUNCTION(AudioConverterGetProperty, inAudioConverter, inPropertyID, ioPropertyDataSize, outPropertyData);
}

DECLARE_FUNCTION(OSStatus, __cdecl, AudioConverterGetPropertyInfo,
    AudioConverterRef inAudioConverter,
    AudioConverterPropertyID inPropertyID,
    UInt32 *outSize,
    Boolean *outWritable)
{
  LOADLIB_GUARD;
  return CALL_FUNCTION(AudioConverterGetPropertyInfo, inAudioConverter, inPropertyID, outSize, outWritable);
}

DECLARE_FUNCTION(OSStatus, __cdecl, AudioConverterSetProperty,
    AudioConverterRef inAudioConverter,
    AudioConverterPropertyID inPropertyID,
    UInt32 inPropertyDataSize,
    const void *inPropertyData)
{
  LOADLIB_GUARD;
  return CALL_FUNCTION(AudioConverterSetProperty, inAudioConverter, inPropertyID, inPropertyDataSize, inPropertyData);
}

DECLARE_FUNCTION(OSStatus, __cdecl, AudioFormatGetProperty,
   AudioFormatPropertyID inPropertyID,
   UInt32                inSpecifierSize,
   const void            *inSpecifier,
   UInt32                *ioPropertyDataSize,
   void                  *outPropertyData)
{
  LOADLIB_GUARD;
  return CALL_FUNCTION(AudioFormatGetProperty, inPropertyID, inSpecifierSize, inSpecifier, ioPropertyDataSize, outPropertyData);
}

DECLARE_FUNCTION(OSStatus, __cdecl, AudioFormatGetPropertyInfo,
   AudioFormatPropertyID  inPropertyID,
   UInt32                 inSpecifierSize,
   const void             *inSpecifier,
   UInt32                 *outPropertyDataSize)
{
  LOADLIB_GUARD;
  return CALL_FUNCTION(AudioFormatGetPropertyInfo, inPropertyID, inSpecifierSize, inSpecifier, outPropertyDataSize);
}

DECLARE_FUNCTION(OSStatus, __cdecl, AudioConverterFillComplexBuffer,
    AudioConverterRef inAudioConverter,
    AudioConverterComplexInputDataProc inInputDataProc,
    void *inInputDataProcUserData,
    UInt32 *ioOutputDataPacketSize,
    AudioBufferList *outOutputData,
    AudioStreamPacketDescription *outPacketDescription)
{
  LOADLIB_GUARD;
  return CALL_FUNCTION(AudioConverterFillComplexBuffer, inAudioConverter, inInputDataProc, inInputDataProcUserData, ioOutputDataPacketSize, outOutputData, outPacketDescription);
}

static BOOL MyPathRemoveFileSpecW(wchar_t *path) {
  int len = lstrlenW(path);
  BOOL result = FALSE;
  for(wchar_t *pos = path + len; pos >= path; pos--) {
    if(*pos == L'\\') {
      *pos = 0;
      result = TRUE;
    }
  }
  return result;
}

static BOOL MyPathAppendW(wchar_t *path1, wchar_t *path2) {
  int p1len = lstrlenW(path1);
  if (p1len != 0 && (path1[p1len-1] != L'\\' || path2[0] != L'\\')) {
    lstrcatW(path1, L"\\");
  }
  lstrcatW(path1, path2);
  return TRUE;
}

static BOOL GetModulePath(WCHAR *pBuf, DWORD dwBufSize) {
  if (GetModuleFileNameW(NULL, pBuf, dwBufSize)) {
    MyPathRemoveFileSpecW(pBuf);
    return TRUE;
  }
  return FALSE;
}

static HMODULE LoadTargetLibrary() {
  WCHAR *pszLibraryPath = HeapAlloc(GetProcessHeap(), 0, 65536);

  /* try CoreAudioToolbox.dll */
  HMODULE hLib = LoadLibraryW(LIBNAMEW);
  if (hLib) goto success;

  /* try executable path\QTfiles(64)\CoreAudioToolbox.dll */
  if (GetModulePath(pszLibraryPath, 65535)) {
    MyPathAppendW(pszLibraryPath, QTFILES L"\\" LIBNAMEW);
    hLib = LoadLibraryExW(pszLibraryPath, NULL, LOAD_LIBRARY_SEARCH_DEFAULT_DIRS | LOAD_LIBRARY_SEARCH_DLL_LOAD_DIR);
    if (hLib) goto success;
  }

  /* try Program Files\Common Files\Apple\Apple Application Support\CoreAudioToolbox.dll */
  if (SUCCEEDED(SHGetFolderPathW(NULL, CSIDL_PROGRAM_FILES_COMMON, NULL, SHGFP_TYPE_CURRENT, pszLibraryPath))) {
    MyPathAppendW(pszLibraryPath, L"Apple\\Apple Application Support\\" LIBNAMEW);
    hLib = LoadLibraryExW(pszLibraryPath, NULL, LOAD_LIBRARY_SEARCH_DEFAULT_DIRS | LOAD_LIBRARY_SEARCH_DLL_LOAD_DIR);
    if (hLib) goto success;
  }

success:
  HeapFree(GetProcessHeap(), 0, pszLibraryPath);
  return hLib;
}

static void PrepareLazyLoad() {
  if(prepared)
    return;

  if(InterlockedCompareExchange(&preparing, 1, 0) == 1) {
    while(!prepared);
    return;
  }

  hTargetLib = LoadTargetLibrary();

  if(!hTargetLib) {
    InterlockedCompareExchange(&preparing, 0, 1);
    return;
  }

  FILL(hTargetLib, AudioConverterDispose);
  FILL(hTargetLib, AudioConverterFillComplexBuffer);
  FILL(hTargetLib, AudioConverterGetProperty);
  FILL(hTargetLib, AudioConverterGetPropertyInfo);
  FILL(hTargetLib, AudioConverterNew);
  FILL(hTargetLib, AudioConverterReset);
  FILL(hTargetLib, AudioConverterSetProperty);
  FILL(hTargetLib, AudioFormatGetProperty);
  FILL(hTargetLib, AudioFormatGetPropertyInfo);

  InterlockedCompareExchange(&prepared, 1, 0);
  InterlockedCompareExchange(&preparing, 0, 1);
}
