#ifndef __MACTYPES__
#define __MACTYPES__

#include<stdint.h>

typedef uint8_t            UInt8;
typedef int8_t             SInt8;
typedef uint16_t           UInt16;
typedef int16_t            SInt16;
typedef uint32_t           UInt32;
typedef int32_t            SInt32;
typedef int64_t            SInt64;
typedef uint64_t           UInt64;
typedef float              Float32;
typedef double             Float64;

typedef uint32_t           FourCharCode;
typedef SInt32             OSStatus;
typedef FourCharCode       OSType;
typedef unsigned char      Boolean;
typedef OSStatus           ComponentResult;
struct ComponentInstanceRecord {
  long                data[1];
};
typedef struct ComponentInstanceRecord  ComponentInstanceRecord;
typedef ComponentInstanceRecord *       ComponentInstance;

typedef UInt16             UniChar;

enum {
  kVariableLengthArray          = 1
};

#define TARGET_OS_IPHONE 0
#define __MAC_OS_X_VERSION_MIN_REQUIRED 101100
#define __MAC_10_9
#endif
