#define UNICODE
#include <windows.h>
#include <shlobj.h>
#include <shlwapi.h>
#include <stdio.h>
#include <stdint.h>
#include <AudioToolbox/AudioToolbox.h>
#define LIBNAME "CoreAudioToolbox.dll"
#define LIBNAMEW TEXT(LIBNAME)


#ifdef __cplusplus
#define FNTYPE(x) decltype(x)
#define CAST(T, x) reinterpret_cast<T>(x)
#elif defined(__GNUC__)
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

static HMODULE hTargetLib = NULL;


static HMODULE LoadTargetLibrary() {
  WCHAR *pszAppleAppSupportPath = HeapAlloc(GetProcessHeap(), 0, 65536);
  SHGetFolderPathW(NULL, CSIDL_PROGRAM_FILES_COMMON, NULL, SHGFP_TYPE_CURRENT, pszAppleAppSupportPath);
  PathAppendW(pszAppleAppSupportPath, L"Apple\\Apple Application Support");
  SetDllDirectoryW(pszAppleAppSupportPath);
  HMODULE hLib = LoadLibraryW(LIBNAMEW);
  SetDllDirectoryW(NULL);
  HeapFree(GetProcessHeap(), 0, pszAppleAppSupportPath);
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
