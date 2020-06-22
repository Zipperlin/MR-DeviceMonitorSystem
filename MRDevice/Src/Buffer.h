/* Time: <@(#)Buffer.h   2009-3-5 - 10:29:10   Fan Zengfei >
 *********************************************************************
 *  Philips-Neusoft Medical Systems Co. Corporation 
 *
 *  Project : 
 *
 *  File Name : Buffer.h
 *         
 *  Author : Fan Zengfei                          Date: 2009-3-5
 *
 *  Description : Heap memory management
 *
 *********************************************************************
 * Develop or modification record:
 *
 * $Log: $ 
 *
 *	1	2009-3-5 - 10:29:10		FanZF	Creation
 *
 *********************************************************************
 */

// Buffer.h: interface for the CBuffer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BUFFER_H__692B9AA5_2704_4F78_8E7B_70BD25C3E22C__INCLUDED_)
#define AFX_BUFFER_H__692B9AA5_2704_4F78_8E7B_70BD25C3E22C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CBuffer  
{
public:
	CBuffer();
	CBuffer(DWORD dwBufferSize);
	virtual ~CBuffer();

	BOOL  SetSize(DWORD dwBufferSize);
	BOOL  ReleaseBuffer();

	BYTE* GetBuffer();
	DWORD GetSize();
	DWORD GetValidSize();
private:
	BYTE* m_pByte;
	DWORD m_BufferSize;
	DWORD m_BufferValidSize;

};

#endif // !defined(AFX_BUFFER_H__692B9AA5_2704_4F78_8E7B_70BD25C3E22C__INCLUDED_)
