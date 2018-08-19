#include <stdio.h>
#include <AudioToolbox/AudioToolbox.h>

int main() {
  AudioStreamBasicDescription in_format = {
       .mSampleRate = 48000,
       .mFormatID = kAudioFormatLinearPCM,
       .mFormatFlags = kAudioFormatFlagIsSignedInteger | kAudioFormatFlagIsPacked,
       .mBytesPerPacket = 4,
       .mFramesPerPacket = 1,
       .mBytesPerFrame = 4,
       .mChannelsPerFrame = 2,
       .mBitsPerChannel = 16,
   };
  AudioStreamBasicDescription out_format = {
       .mSampleRate = 44100,
       .mFormatID = kAudioFormatLinearPCM,
       .mFormatFlags = kAudioFormatFlagIsSignedInteger | kAudioFormatFlagIsPacked,
       .mBytesPerPacket = 4,
       .mFramesPerPacket = 1,
       .mBytesPerFrame = 4,
       .mChannelsPerFrame = 2,
       .mBitsPerChannel = 16,
  };
  AudioConverterRef converter;
  OSStatus ret = AudioConverterNew(&in_format, &out_format, &converter);
  printf("AudioConverterNew() => %d\n", ret);
  if (ret) {
    printf("failed\n");
  } else {
    printf("successfully created AudioConverter instance\n");
  }
}
