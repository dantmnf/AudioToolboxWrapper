#ifndef CoreAudioToolbox_H
#define CoreAudioToolbox_H

#ifdef __GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmultichar"
#endif
#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wfour-char-constants"
#endif
/* it is multichar character constant in Apple SDKs */
#include "CoreAudio/MacTypes.h"
#include "CoreAudio/CoreFoundation.h"
#include "CoreAudio/CoreAudioTypes.h"
#include "CoreAudio/AudioComponent.h"
#include "CoreAudio/AudioCodec.h"
#include "CoreAudio/AudioConverter.h"
#include "CoreAudio/AudioFile.h"
#include "CoreAudio/AudioFormat.h"

#ifdef __GNUC__
#pragma GCC diagnostic pop
#endif
#ifdef __clang__
#pragma clang diagnostic pop
#endif
#endif
