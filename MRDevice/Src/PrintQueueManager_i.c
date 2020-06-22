/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 5.01.0164 */
/* at Tue Feb 06 14:58:56 2018
 */
/* Compiler settings for PrintQueueManager.idl:
    Oicf (OptLev=i2), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
*/
//@@MIDL_FILE_HEADING(  )
#ifdef __cplusplus
extern "C"{
#endif 


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

const IID IID_IPrintQueue = {0xFF599785,0x6256,0x41B4,{0xB0,0xFF,0x78,0xFE,0x7B,0xD5,0x3C,0x80}};


const IID IID_IPrintJob = {0xE7C906C2,0x210C,0x4b21,{0xB5,0xC5,0xAB,0xC2,0xD5,0x19,0xDB,0x0E}};


const IID LIBID_PRINTQUEUEMANAGERLib = {0xC4AF7CD8,0xCB34,0x4F2D,{0x9B,0x45,0x1A,0x61,0x28,0x32,0xD3,0xE5}};


const IID DIID__IPrintQueueChangeEvents = {0x718D4637,0x708B,0x4FEA,{0x88,0xB7,0xBB,0x51,0x33,0x25,0x25,0xAF}};


const CLSID CLSID_PrintQueue = {0x65DA6714,0xB467,0x4195,{0xB2,0x11,0x23,0x10,0x22,0xBB,0x00,0xC2}};


#ifdef __cplusplus
}
#endif

