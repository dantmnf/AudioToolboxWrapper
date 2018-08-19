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

#ifdef __cplusplus
#define FNTYPE(x) decltype(x)
#define CAST(T, x) reinterpret_cast<T>(x)
#elif defined(__GNUC__) || defined(__clang__)
#define FNTYPE(x) typeof(x)
#define CAST(T, x) ((T)(x))
#else
#error no typeof(x)/decltype(x) equivalent
#endif

#define DECLARE_FUNCTION_POINTER(fn) static FNTYPE(fn)* p ## fn = NULL;
#define FILL(hlib, name)  p ## name = CAST(FNTYPE(name)*, GetProcAddress(hlib, #name));
#define CALL_FUNCTION(name, ...) p ## name(__VA_ARGS__)
#define NSExecutableLoadError 3587

#ifdef __cplusplus
extern "C" {
#endif


DECLARE_FUNCTION_POINTER(AudioConverterDispose)
DECLARE_FUNCTION_POINTER(AudioConverterFillComplexBuffer)
DECLARE_FUNCTION_POINTER(AudioConverterGetProperty)
DECLARE_FUNCTION_POINTER(AudioConverterGetPropertyInfo)
DECLARE_FUNCTION_POINTER(AudioConverterNew)
DECLARE_FUNCTION_POINTER(AudioConverterReset)
DECLARE_FUNCTION_POINTER(AudioConverterSetProperty)
DECLARE_FUNCTION_POINTER(AudioFormatGetProperty)
DECLARE_FUNCTION_POINTER(AudioFormatGetPropertyInfo)

static HMODULE hTargetLib = NULL;

static BOOL GetModulePath(WCHAR *pBuf, DWORD dwBufSize) {
  if (GetModuleFileNameW(NULL, pBuf, dwBufSize)) {
    PathRemoveFileSpec(pBuf);
    return TRUE;
  }
  return FALSE;
}

static HMODULE LoadTargetLibrary() {
  WCHAR *pszLibraryPath = HeapAlloc(GetProcessHeap(), 0, 65536);

  /* try CoreAudioToolbox.dll */
  HMODULE hLib = LoadLibraryW(LIBNAMEW);
  if (hLib) goto success;

  /* try Program Files\Common Files\Apple\Apple Application Support\CoreAudioToolbox.dll */
  SHGetFolderPathW(NULL, CSIDL_PROGRAM_FILES_COMMON, NULL, SHGFP_TYPE_CURRENT, pszLibraryPath);
  PathAppendW(pszLibraryPath, L"Apple\\Apple Application Support\\" LIBNAMEW);
  hLib = LoadLibraryExW(pszLibraryPath, NULL, LOAD_LIBRARY_SEARCH_DEFAULT_DIRS | LOAD_LIBRARY_SEARCH_DLL_LOAD_DIR);
  if (hLib) goto success;

  /* try executable path\QTfiles(64)\CoreAudioToolbox.dll */
  if (GetModulePath(pszLibraryPath, 65535)) {
    PathAppendW(pszLibraryPath, QTFILES L"\\" LIBNAMEW);
    hLib = LoadLibraryExW(pszLibraryPath, NULL, LOAD_LIBRARY_SEARCH_DEFAULT_DIRS | LOAD_LIBRARY_SEARCH_DLL_LOAD_DIR);
    if (hLib) goto success;
  }

success:
  HeapFree(GetProcessHeap(), 0, pszLibraryPath);
  return hLib;
}


static HMODULE PrepareLazyLoad() {
  if(hTargetLib)
    return hTargetLib;

  hTargetLib = LoadTargetLibrary();

  if(!hTargetLib)
    return NULL;

  FILL(hTargetLib, AudioConverterDispose);
  FILL(hTargetLib, AudioConverterFillComplexBuffer);
  FILL(hTargetLib, AudioConverterGetProperty);
  FILL(hTargetLib, AudioConverterGetPropertyInfo);
  FILL(hTargetLib, AudioConverterNew);
  FILL(hTargetLib, AudioConverterReset);
  FILL(hTargetLib, AudioConverterSetProperty);
  FILL(hTargetLib, AudioFormatGetProperty);
  FILL(hTargetLib, AudioFormatGetPropertyInfo);

  return hTargetLib;
}

#define LOADLIB_GUARD               \
  if (!hTargetLib)                  \
  {                                 \
    PrepareLazyLoad();              \
    if (!hTargetLib)                \
    {                               \
      return NSExecutableLoadError; \
    }                               \
  }

OSStatus AudioConverterNew(
  const AudioStreamBasicDescription *inSourceFormat,
  const AudioStreamBasicDescription *inDestinationFormat,
  AudioConverterRef *outAudioConverter)
{
  LOADLIB_GUARD;
  return CALL_FUNCTION(AudioConverterNew, inSourceFormat, inDestinationFormat, outAudioConverter);
}

OSStatus AudioConverterDispose(AudioConverterRef inAudioConverter)
{
  LOADLIB_GUARD;
  return CALL_FUNCTION(AudioConverterDispose, inAudioConverter);
}

OSStatus AudioConverterReset(AudioConverterRef inAudioConverter){
  LOADLIB_GUARD;
  return CALL_FUNCTION(AudioConverterReset, inAudioConverter);
}

OSStatus AudioConverterGetProperty(
    AudioConverterRef inAudioConverter,
    AudioConverterPropertyID inPropertyID,
    UInt32 *ioPropertyDataSize,
    void *outPropertyData)
{
  LOADLIB_GUARD;
  return CALL_FUNCTION(AudioConverterGetProperty, inAudioConverter, inPropertyID, ioPropertyDataSize, outPropertyData);
}

OSStatus AudioConverterGetPropertyInfo(
    AudioConverterRef inAudioConverter,
    AudioConverterPropertyID inPropertyID,
    UInt32 *outSize,
    Boolean *outWritable)
{
  LOADLIB_GUARD;
  return CALL_FUNCTION(AudioConverterGetPropertyInfo, inAudioConverter, inPropertyID, outSize, outWritable);
}

OSStatus AudioConverterSetProperty(
    AudioConverterRef inAudioConverter,
    AudioConverterPropertyID inPropertyID,
    UInt32 inPropertyDataSize,
    const void *inPropertyData)
{
  LOADLIB_GUARD;
  return CALL_FUNCTION(AudioConverterSetProperty, inAudioConverter, inPropertyID, inPropertyDataSize, inPropertyData);
}

OSStatus AudioFormatGetProperty (
   AudioFormatPropertyID inPropertyID,
   UInt32                inSpecifierSize,
   const void            *inSpecifier,
   UInt32                *ioPropertyDataSize,
   void                  *outPropertyData)
{
  LOADLIB_GUARD;
  return CALL_FUNCTION(AudioFormatGetProperty, inPropertyID, inSpecifierSize, inSpecifier, ioPropertyDataSize, outPropertyData);
}

OSStatus AudioFormatGetPropertyInfo (
   AudioFormatPropertyID  inPropertyID,
   UInt32                 inSpecifierSize,
   const void             *inSpecifier,
   UInt32                 *outPropertyDataSize)
{
  LOADLIB_GUARD;
  return CALL_FUNCTION(AudioFormatGetPropertyInfo, inPropertyID, inSpecifierSize, inSpecifier, outPropertyDataSize);
}

OSStatus AudioConverterFillComplexBuffer(
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

#ifdef __cplusplus
} // extern "C"
#endif
