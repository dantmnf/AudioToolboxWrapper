#define UNICODE
#include <windows.h>
#include <shlobj.h>
#include <shlwapi.h>
#include <stdio.h>
#include <stdint.h>
#define LIBNAME "CoreAudioToolbox.dll"
#define LIBNAMEW TEXT(LIBNAME)
#define FILL(hlib, name) \
  extern void *p ## name; \
  p ## name = GetProcAddress(hlib, #name);


HMODULE ATWrapper_hTargetLib = NULL;
static BOOL ExitOnLoadError = TRUE;

typedef int32_t OSStatus;
typedef OSStatus (*defAudioConverterNew)(void*, void*, void*);
static defAudioConverterNew pAudioConverterNew;



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

// we are calliing this function from assembly,
//   so keep its signature as simple as possible
void ATWrapper_PrepareLazyLoad() {
  if(ATWrapper_hTargetLib) return;
  ATWrapper_hTargetLib = LoadTargetLibrary();

  if(!ATWrapper_hTargetLib) {
    if(ExitOnLoadError) {
      fprintf(stderr, "\nAudioToolboxStub: can't load CoreAudioToolbox.dll\n");
      exit(127);
    } else {
      return;
    }
  }


  FILL(ATWrapper_hTargetLib, ACAC3DecoderEntry)
  FILL(ATWrapper_hTargetLib, ACAC3DecoderFactory)
  FILL(ATWrapper_hTargetLib, ACAMRDecoderEntry)
  FILL(ATWrapper_hTargetLib, ACAMREncoderEntry)
  FILL(ATWrapper_hTargetLib, ACAppleIMA4DecoderEntry)
  FILL(ATWrapper_hTargetLib, ACAppleIMA4EncoderEntry)
  FILL(ATWrapper_hTargetLib, ACAppleLosslessDecoderEntry)
  FILL(ATWrapper_hTargetLib, ACAppleLosslessEncoderEntry)
  FILL(ATWrapper_hTargetLib, ACGSMDecoderEntry)
  FILL(ATWrapper_hTargetLib, ACILBCDecoderEntry)
  FILL(ATWrapper_hTargetLib, ACILBCEncoderEntry)
  FILL(ATWrapper_hTargetLib, ACMP3DecoderEntry)
  FILL(ATWrapper_hTargetLib, ACMP4AACHighEfficiencyDecoderEntry)
  FILL(ATWrapper_hTargetLib, ACMP4AACHighEfficiencyEncoderEntry)
  FILL(ATWrapper_hTargetLib, ACMP4AACHighEfficiencyEncoderFactory)
  FILL(ATWrapper_hTargetLib, ACMP4AACLowComplexityDecoderEntry)
  FILL(ATWrapper_hTargetLib, ACMP4AACLowComplexityEncoderEntry)
  FILL(ATWrapper_hTargetLib, ACMPADecoderEntry)
  FILL(ATWrapper_hTargetLib, ACMSADPCMDecoderEntry)
  FILL(ATWrapper_hTargetLib, ACPureVoiceDecoderEntry)
  FILL(ATWrapper_hTargetLib, ACPureVoiceEncoderEntry)
  FILL(ATWrapper_hTargetLib, ACQDesignDecoderEntry)
  FILL(ATWrapper_hTargetLib, AQOfflineMixerConnectAudioQueue)
  FILL(ATWrapper_hTargetLib, AQOfflineMixerDisconnectAudioQueue)
  FILL(ATWrapper_hTargetLib, AQOfflineMixerDispose)
  FILL(ATWrapper_hTargetLib, AQOfflineMixerGetProperty)
  FILL(ATWrapper_hTargetLib, AQOfflineMixerGetPropertySize)
  FILL(ATWrapper_hTargetLib, AQOfflineMixerNew)
  FILL(ATWrapper_hTargetLib, AQOfflineMixerRender)
  FILL(ATWrapper_hTargetLib, AQOfflineMixerReset)
  FILL(ATWrapper_hTargetLib, AQOfflineMixerSetProperty)
  FILL(ATWrapper_hTargetLib, AUControlFreakFactory)
  FILL(ATWrapper_hTargetLib, AUConverterEntry)
  FILL(ATWrapper_hTargetLib, AUDirectSoundEntry)
  FILL(ATWrapper_hTargetLib, AUGenericOutputEntry)
  FILL(ATWrapper_hTargetLib, AUGraphicEQEntry)
  FILL(ATWrapper_hTargetLib, AUHighShelfFilterEntry)
  FILL(ATWrapper_hTargetLib, AULittleLateNightModeFactory)
  FILL(ATWrapper_hTargetLib, AULowShelfFilterEntry)
  FILL(ATWrapper_hTargetLib, AUMatrixMixerEntry)
  FILL(ATWrapper_hTargetLib, AUMozartCompressorSingleBandFactory)
  FILL(ATWrapper_hTargetLib, AUMultiChannelMixerEntry)
  FILL(ATWrapper_hTargetLib, AUPitchEntry)
  FILL(ATWrapper_hTargetLib, AUVarispeedEntry)
  FILL(ATWrapper_hTargetLib, AUWASAPIEntry)
  FILL(ATWrapper_hTargetLib, AudioCodecAppendInputBufferList)
  FILL(ATWrapper_hTargetLib, AudioCodecAppendInputData)
  FILL(ATWrapper_hTargetLib, AudioCodecGetProperty)
  FILL(ATWrapper_hTargetLib, AudioCodecGetPropertyInfo)
  FILL(ATWrapper_hTargetLib, AudioCodecInitialize)
  FILL(ATWrapper_hTargetLib, AudioCodecProduceOutputBufferList)
  FILL(ATWrapper_hTargetLib, AudioCodecProduceOutputPackets)
  FILL(ATWrapper_hTargetLib, AudioCodecReset)
  FILL(ATWrapper_hTargetLib, AudioCodecSetProperty)
  FILL(ATWrapper_hTargetLib, AudioCodecUninitialize)
  FILL(ATWrapper_hTargetLib, AudioComponentCopyName)
  FILL(ATWrapper_hTargetLib, AudioComponentCount)
  FILL(ATWrapper_hTargetLib, AudioComponentFindNext)
  FILL(ATWrapper_hTargetLib, AudioComponentGetDescription)
  FILL(ATWrapper_hTargetLib, AudioComponentGetVersion)
  FILL(ATWrapper_hTargetLib, AudioComponentInstanceCanDo)
  FILL(ATWrapper_hTargetLib, AudioComponentInstanceDispose)
  FILL(ATWrapper_hTargetLib, AudioComponentInstanceGetComponent)
  FILL(ATWrapper_hTargetLib, AudioComponentInstanceNew)
  FILL(ATWrapper_hTargetLib, AudioComponentRegister)
  FILL(ATWrapper_hTargetLib, AudioConverterConvertBuffer)
  FILL(ATWrapper_hTargetLib, AudioConverterDispose)
  FILL(ATWrapper_hTargetLib, AudioConverterFillBuffer)
  FILL(ATWrapper_hTargetLib, AudioConverterFillComplexBuffer)
  FILL(ATWrapper_hTargetLib, AudioConverterGetProperty)
  FILL(ATWrapper_hTargetLib, AudioConverterGetPropertyInfo)
  // FILL(ATWrapper_hTargetLib, AudioConverterNew)
  FILL(ATWrapper_hTargetLib, AudioConverterNewSpecific)
  FILL(ATWrapper_hTargetLib, AudioConverterReset)
  FILL(ATWrapper_hTargetLib, AudioConverterSetProperty)
  FILL(ATWrapper_hTargetLib, AudioFileClose)
  FILL(ATWrapper_hTargetLib, AudioFileCountUserData)
  FILL(ATWrapper_hTargetLib, AudioFileCreateWithURL)
  FILL(ATWrapper_hTargetLib, AudioFileGetGlobalInfo)
  FILL(ATWrapper_hTargetLib, AudioFileGetGlobalInfoSize)
  FILL(ATWrapper_hTargetLib, AudioFileGetProperty)
  FILL(ATWrapper_hTargetLib, AudioFileGetPropertyInfo)
  FILL(ATWrapper_hTargetLib, AudioFileGetUserData)
  FILL(ATWrapper_hTargetLib, AudioFileGetUserDataSize)
  FILL(ATWrapper_hTargetLib, AudioFileInitializeWithCallbacks)
  FILL(ATWrapper_hTargetLib, AudioFileOpenURL)
  FILL(ATWrapper_hTargetLib, AudioFileOpenWithCallbacks)
  FILL(ATWrapper_hTargetLib, AudioFileOptimize)
  FILL(ATWrapper_hTargetLib, AudioFileReadBytes)
  FILL(ATWrapper_hTargetLib, AudioFileReadPacketData)
  FILL(ATWrapper_hTargetLib, AudioFileReadPackets)
  FILL(ATWrapper_hTargetLib, AudioFileRemoveUserData)
  FILL(ATWrapper_hTargetLib, AudioFileSetProperty)
  FILL(ATWrapper_hTargetLib, AudioFileSetUserData)
  FILL(ATWrapper_hTargetLib, AudioFileStreamClose)
  FILL(ATWrapper_hTargetLib, AudioFileStreamGetProperty)
  FILL(ATWrapper_hTargetLib, AudioFileStreamGetPropertyInfo)
  FILL(ATWrapper_hTargetLib, AudioFileStreamOpen)
  FILL(ATWrapper_hTargetLib, AudioFileStreamParseBytes)
  FILL(ATWrapper_hTargetLib, AudioFileStreamSeek)
  FILL(ATWrapper_hTargetLib, AudioFileStreamSetProperty)
  FILL(ATWrapper_hTargetLib, AudioFileWriteBytes)
  FILL(ATWrapper_hTargetLib, AudioFileWritePackets)
  FILL(ATWrapper_hTargetLib, AudioFormatGetProperty)
  FILL(ATWrapper_hTargetLib, AudioFormatGetPropertyInfo)
  FILL(ATWrapper_hTargetLib, AudioOutputUnitStart)
  FILL(ATWrapper_hTargetLib, AudioOutputUnitStop)
  FILL(ATWrapper_hTargetLib, AudioQueueAddPropertyListener)
  FILL(ATWrapper_hTargetLib, AudioQueueAllocateBuffer)
  FILL(ATWrapper_hTargetLib, AudioQueueAllocateBufferWithMemory)
  FILL(ATWrapper_hTargetLib, AudioQueueAllocateBufferWithPacketDescriptions)
  FILL(ATWrapper_hTargetLib, AudioQueueAllocateBufferWithPacketDescriptionsWithMemory)
  FILL(ATWrapper_hTargetLib, AudioQueueConvertToScaledSampleTime)
  FILL(ATWrapper_hTargetLib, AudioQueueConvertToUnscaledSampleTime)
  FILL(ATWrapper_hTargetLib, AudioQueueCreateTimeline)
  FILL(ATWrapper_hTargetLib, AudioQueueDeviceGetCurrentTime)
  FILL(ATWrapper_hTargetLib, AudioQueueDeviceGetNearestStartTime)
  FILL(ATWrapper_hTargetLib, AudioQueueDeviceTranslateTime)
  FILL(ATWrapper_hTargetLib, AudioQueueDispose)
  FILL(ATWrapper_hTargetLib, AudioQueueDisposeTimeline)
  FILL(ATWrapper_hTargetLib, AudioQueueEnqueueBuffer)
  FILL(ATWrapper_hTargetLib, AudioQueueEnqueueBufferWithParameters)
  FILL(ATWrapper_hTargetLib, AudioQueueEnqueueSilence)
  FILL(ATWrapper_hTargetLib, AudioQueueFlush)
  FILL(ATWrapper_hTargetLib, AudioQueueFreeBuffer)
  FILL(ATWrapper_hTargetLib, AudioQueueGetCurrentTime)
  FILL(ATWrapper_hTargetLib, AudioQueueGetParameter)
  FILL(ATWrapper_hTargetLib, AudioQueueGetProperty)
  FILL(ATWrapper_hTargetLib, AudioQueueGetPropertySize)
  FILL(ATWrapper_hTargetLib, AudioQueueNewInput)
  FILL(ATWrapper_hTargetLib, AudioQueueNewOutput)
  FILL(ATWrapper_hTargetLib, AudioQueueOfflineRender)
  FILL(ATWrapper_hTargetLib, AudioQueuePause)
  FILL(ATWrapper_hTargetLib, AudioQueuePrime)
  FILL(ATWrapper_hTargetLib, AudioQueueRemovePropertyListener)
  FILL(ATWrapper_hTargetLib, AudioQueueReset)
  FILL(ATWrapper_hTargetLib, AudioQueueScheduleParameters)
  FILL(ATWrapper_hTargetLib, AudioQueueSetOfflineRenderFormat)
  FILL(ATWrapper_hTargetLib, AudioQueueSetParameter)
  FILL(ATWrapper_hTargetLib, AudioQueueSetProperty)
  FILL(ATWrapper_hTargetLib, AudioQueueStart)
  FILL(ATWrapper_hTargetLib, AudioQueueStop)
  FILL(ATWrapper_hTargetLib, AudioUnitAddPropertyListener)
  FILL(ATWrapper_hTargetLib, AudioUnitAddRenderNotify)
  FILL(ATWrapper_hTargetLib, AudioUnitGetParameter)
  FILL(ATWrapper_hTargetLib, AudioUnitGetProperty)
  FILL(ATWrapper_hTargetLib, AudioUnitGetPropertyInfo)
  FILL(ATWrapper_hTargetLib, AudioUnitInitialize)
  FILL(ATWrapper_hTargetLib, AudioUnitRemovePropertyListener)
  FILL(ATWrapper_hTargetLib, AudioUnitRemovePropertyListenerWithUserData)
  FILL(ATWrapper_hTargetLib, AudioUnitRemoveRenderNotify)
  FILL(ATWrapper_hTargetLib, AudioUnitRender)
  FILL(ATWrapper_hTargetLib, AudioUnitReset)
  FILL(ATWrapper_hTargetLib, AudioUnitScheduleParameters)
  FILL(ATWrapper_hTargetLib, AudioUnitSetParameter)
  FILL(ATWrapper_hTargetLib, AudioUnitSetProperty)
  FILL(ATWrapper_hTargetLib, AudioUnitUninitialize)
  FILL(ATWrapper_hTargetLib, CAShow)
  FILL(ATWrapper_hTargetLib, CAShowFile)
  FILL(ATWrapper_hTargetLib, ExtAudioFileCreateWithURL)
  FILL(ATWrapper_hTargetLib, ExtAudioFileDispose)
  FILL(ATWrapper_hTargetLib, ExtAudioFileGetProperty)
  FILL(ATWrapper_hTargetLib, ExtAudioFileGetPropertyInfo)
  FILL(ATWrapper_hTargetLib, ExtAudioFileOpenURL)
  FILL(ATWrapper_hTargetLib, ExtAudioFileRead)
  FILL(ATWrapper_hTargetLib, ExtAudioFileSeek)
  FILL(ATWrapper_hTargetLib, ExtAudioFileSetProperty)
  FILL(ATWrapper_hTargetLib, ExtAudioFileTell)
  FILL(ATWrapper_hTargetLib, ExtAudioFileWrapAudioFileID)
  FILL(ATWrapper_hTargetLib, ExtAudioFileWrite)
  FILL(ATWrapper_hTargetLib, ExtAudioFileWriteAsync)
  FILL(ATWrapper_hTargetLib, MPADecoderEntry)
  FILL(ATWrapper_hTargetLib, RefAudioFileReadBytes)
  FILL(ATWrapper_hTargetLib, RefAudioFileReadPackets)
  FILL(ATWrapper_hTargetLib, RefAudioFileWriteBytes)
  FILL(ATWrapper_hTargetLib, RefAudioFileWritePackets)
  FILL(ATWrapper_hTargetLib, RefExtAudioFileSeek)

  pAudioConverterNew = (defAudioConverterNew)GetProcAddress(ATWrapper_hTargetLib, "AudioConverterNew");
}


// ffmpeg will call this function first, return error instead of exitting
// OSStatus AudioConverterNew(AudioStreamBasicDescription *inSourceFormat,
//                            AudioStreamBasicDescription *inDestinationFormat,
//                            AudioConverterRef *outAudioConverter);
OSStatus AudioConverterNew(void *inSourceFormat, void *inDestinationFormat, void *outAudioConverter) {
  if(!ATWrapper_hTargetLib) {
    ExitOnLoadError = FALSE;
    ATWrapper_PrepareLazyLoad();
    ExitOnLoadError = TRUE;
    if(!ATWrapper_hTargetLib) {
      // fputs("WARNING: can't load CoreAudioToolbox.dll", stderr);
      return 3587; // NSExecutableLoadError
    }
  }
  return pAudioConverterNew(inSourceFormat, inDestinationFormat, outAudioConverter);
}
