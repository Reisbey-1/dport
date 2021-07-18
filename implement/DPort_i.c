

/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


 /* File created by MIDL compiler version 8.01.0622 */
/* at Tue Jan 19 06:14:07 2038
 */
/* Compiler settings for DPort.idl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 8.01.0622 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */



#ifdef __cplusplus
extern "C"{
#endif 


#include <rpc.h>
#include <rpcndr.h>

#ifdef _MIDL_USE_GUIDDEF_

#ifndef INITGUID
#define INITGUID
#include <guiddef.h>
#undef INITGUID
#else
#include <guiddef.h>
#endif

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        DEFINE_GUID(name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8)

#else // !_MIDL_USE_GUIDDEF_

#ifndef __IID_DEFINED__
#define __IID_DEFINED__

typedef struct _IID
{
    unsigned long x;
    unsigned short s1;
    unsigned short s2;
    unsigned char  c[8];
} IID;

#endif // __IID_DEFINED__

#ifndef CLSID_DEFINED
#define CLSID_DEFINED
typedef IID CLSID;
#endif // CLSID_DEFINED

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        EXTERN_C __declspec(selectany) const type name = {l,w1,w2,{b1,b2,b3,b4,b5,b6,b7,b8}}

#endif // !_MIDL_USE_GUIDDEF_

MIDL_DEFINE_GUID(IID, IID_ISerialSink,0xBC614BD5,0xD5DD,0x4C23,0x83,0x8F,0x14,0xD6,0x20,0x3A,0x8D,0x25);


MIDL_DEFINE_GUID(IID, IID_ISerialPort,0x4BB8490C,0x5955,0x41CF,0xB5,0xC3,0xAA,0x41,0xDC,0xC2,0xFF,0x96);


MIDL_DEFINE_GUID(IID, IID__ISerialPortEvents,0x12A8852F,0xCE62,0x4FDF,0xA7,0xA8,0xE3,0xFA,0xFB,0xCE,0x7D,0xE8);


MIDL_DEFINE_GUID(IID, LIBID_DPortLib,0xF1E2849F,0x13B0,0x4547,0x90,0xB5,0x1D,0x8B,0x10,0x72,0x77,0x15);


MIDL_DEFINE_GUID(CLSID, CLSID_SerialSink,0xA0C0A43D,0xC3F9,0x408B,0x8F,0x99,0x9D,0x33,0xA0,0x7A,0x4F,0x66);


MIDL_DEFINE_GUID(CLSID, CLSID_SerialPort,0xAF34303D,0xCB9F,0x4019,0xAD,0xFF,0x91,0x5B,0x0E,0xC1,0xC5,0x45);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif



