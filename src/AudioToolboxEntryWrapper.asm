%ifidn __OUTPUT_FORMAT__, win64
  bits 64
  %define ptrres resq 1
  %define mangle(x) x
%elifidn __OUTPUT_FORMAT__, win32
  bits 32
  %define ptrres resd 1
  %define mangle(x) _ %+ x
%endif

section .text
align 8
extern mangle(ATWrapper_PrepareLazyLoad)
extern mangle(ATWrapper_hTargetLib)

%macro declare 1
  section .bss
    global mangle(p%1)
    mangle(p%1): ptrres
  section .text
    global mangle(%1)
    mangle(%1):
    call ATWrapper_PrepareLazyLoad2
    jmp [mangle(p%1)]
%endmacro

section .text
ATWrapper_PrepareLazyLoad2:
  cmp dword [mangle(ATWrapper_hTargetLib)], 0
  jz _continue
  ret
 _continue:
%ifidn __OUTPUT_FORMAT__, win64
  push r9
  push r8
  push rdx
  push rcx
%endif
  call mangle(ATWrapper_PrepareLazyLoad)
%ifidn __OUTPUT_FORMAT__, win64
  pop rcx
  pop rdx
  pop r8
  pop r9
%endif
  ret

declare ACAC3DecoderEntry
declare ACAC3DecoderFactory
declare ACAMRDecoderEntry
declare ACAMREncoderEntry
declare ACAppleIMA4DecoderEntry
declare ACAppleIMA4EncoderEntry
declare ACAppleLosslessDecoderEntry
declare ACAppleLosslessEncoderEntry
declare ACGSMDecoderEntry
declare ACILBCDecoderEntry
declare ACILBCEncoderEntry
declare ACMP3DecoderEntry
declare ACMP4AACHighEfficiencyDecoderEntry
declare ACMP4AACHighEfficiencyEncoderEntry
declare ACMP4AACHighEfficiencyEncoderFactory
declare ACMP4AACLowComplexityDecoderEntry
declare ACMP4AACLowComplexityEncoderEntry
declare ACMPADecoderEntry
declare ACMSADPCMDecoderEntry
declare ACPureVoiceDecoderEntry
declare ACPureVoiceEncoderEntry
declare ACQDesignDecoderEntry
declare AQOfflineMixerConnectAudioQueue
declare AQOfflineMixerDisconnectAudioQueue
declare AQOfflineMixerDispose
declare AQOfflineMixerGetProperty
declare AQOfflineMixerGetPropertySize
declare AQOfflineMixerNew
declare AQOfflineMixerRender
declare AQOfflineMixerReset
declare AQOfflineMixerSetProperty
declare AUControlFreakFactory
declare AUConverterEntry
declare AUDirectSoundEntry
declare AUGenericOutputEntry
declare AUGraphicEQEntry
declare AUHighShelfFilterEntry
declare AULittleLateNightModeFactory
declare AULowShelfFilterEntry
declare AUMatrixMixerEntry
declare AUMozartCompressorSingleBandFactory
declare AUMultiChannelMixerEntry
declare AUPitchEntry
declare AUVarispeedEntry
declare AUWASAPIEntry
declare AudioCodecAppendInputBufferList
declare AudioCodecAppendInputData
declare AudioCodecGetProperty
declare AudioCodecGetPropertyInfo
declare AudioCodecInitialize
declare AudioCodecProduceOutputBufferList
declare AudioCodecProduceOutputPackets
declare AudioCodecReset
declare AudioCodecSetProperty
declare AudioCodecUninitialize
declare AudioComponentCopyName
declare AudioComponentCount
declare AudioComponentFindNext
declare AudioComponentGetDescription
declare AudioComponentGetVersion
declare AudioComponentInstanceCanDo
declare AudioComponentInstanceDispose
declare AudioComponentInstanceGetComponent
declare AudioComponentInstanceNew
declare AudioComponentRegister
declare AudioConverterConvertBuffer
declare AudioConverterDispose
declare AudioConverterFillBuffer
declare AudioConverterFillComplexBuffer
declare AudioConverterGetProperty
declare AudioConverterGetPropertyInfo
;declare AudioConverterNew
declare AudioConverterNewSpecific
declare AudioConverterReset
declare AudioConverterSetProperty
declare AudioFileClose
declare AudioFileCountUserData
declare AudioFileCreateWithURL
declare AudioFileGetGlobalInfo
declare AudioFileGetGlobalInfoSize
declare AudioFileGetProperty
declare AudioFileGetPropertyInfo
declare AudioFileGetUserData
declare AudioFileGetUserDataSize
declare AudioFileInitializeWithCallbacks
declare AudioFileOpenURL
declare AudioFileOpenWithCallbacks
declare AudioFileOptimize
declare AudioFileReadBytes
declare AudioFileReadPacketData
declare AudioFileReadPackets
declare AudioFileRemoveUserData
declare AudioFileSetProperty
declare AudioFileSetUserData
declare AudioFileStreamClose
declare AudioFileStreamGetProperty
declare AudioFileStreamGetPropertyInfo
declare AudioFileStreamOpen
declare AudioFileStreamParseBytes
declare AudioFileStreamSeek
declare AudioFileStreamSetProperty
declare AudioFileWriteBytes
declare AudioFileWritePackets
declare AudioFormatGetProperty
declare AudioFormatGetPropertyInfo
declare AudioOutputUnitStart
declare AudioOutputUnitStop
declare AudioQueueAddPropertyListener
declare AudioQueueAllocateBuffer
declare AudioQueueAllocateBufferWithMemory
declare AudioQueueAllocateBufferWithPacketDescriptions
declare AudioQueueAllocateBufferWithPacketDescriptionsWithMemory
declare AudioQueueConvertToScaledSampleTime
declare AudioQueueConvertToUnscaledSampleTime
declare AudioQueueCreateTimeline
declare AudioQueueDeviceGetCurrentTime
declare AudioQueueDeviceGetNearestStartTime
declare AudioQueueDeviceTranslateTime
declare AudioQueueDispose
declare AudioQueueDisposeTimeline
declare AudioQueueEnqueueBuffer
declare AudioQueueEnqueueBufferWithParameters
declare AudioQueueEnqueueSilence
declare AudioQueueFlush
declare AudioQueueFreeBuffer
declare AudioQueueGetCurrentTime
declare AudioQueueGetParameter
declare AudioQueueGetProperty
declare AudioQueueGetPropertySize
declare AudioQueueNewInput
declare AudioQueueNewOutput
declare AudioQueueOfflineRender
declare AudioQueuePause
declare AudioQueuePrime
declare AudioQueueRemovePropertyListener
declare AudioQueueReset
declare AudioQueueScheduleParameters
declare AudioQueueSetOfflineRenderFormat
declare AudioQueueSetParameter
declare AudioQueueSetProperty
declare AudioQueueStart
declare AudioQueueStop
declare AudioUnitAddPropertyListener
declare AudioUnitAddRenderNotify
declare AudioUnitGetParameter
declare AudioUnitGetProperty
declare AudioUnitGetPropertyInfo
declare AudioUnitInitialize
declare AudioUnitRemovePropertyListener
declare AudioUnitRemovePropertyListenerWithUserData
declare AudioUnitRemoveRenderNotify
declare AudioUnitRender
declare AudioUnitReset
declare AudioUnitScheduleParameters
declare AudioUnitSetParameter
declare AudioUnitSetProperty
declare AudioUnitUninitialize
declare CAShow
declare CAShowFile
declare ExtAudioFileCreateWithURL
declare ExtAudioFileDispose
declare ExtAudioFileGetProperty
declare ExtAudioFileGetPropertyInfo
declare ExtAudioFileOpenURL
declare ExtAudioFileRead
declare ExtAudioFileSeek
declare ExtAudioFileSetProperty
declare ExtAudioFileTell
declare ExtAudioFileWrapAudioFileID
declare ExtAudioFileWrite
declare ExtAudioFileWriteAsync
declare MPADecoderEntry
declare RefAudioFileReadBytes
declare RefAudioFileReadPackets
declare RefAudioFileWriteBytes
declare RefAudioFileWritePackets
declare RefExtAudioFileSeek
