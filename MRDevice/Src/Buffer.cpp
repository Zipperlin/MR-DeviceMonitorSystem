/* Time: <@(#)Buffer.cpp   2009-3-5 - 10:29:24   Fan Zengfei >
 *********************************************************************
 *  Philips-Neusoft Medical Systems Co. Corporation 
 *
 *  Project : 
 *
 *  File Name : Buffer.cpp
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
 *	1	2009-3-5 - 10:29:24		FanZF	Creation
 *
 *********************************************************************
 */

// Buffer.cpp: implementation of the CBuffer class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Buffer.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CBuffer::CBuffer()
{
	m_pByte = NULL;
	m_BufferSize = 0;
	m_BufferValidSize = 0;
}

CBuffer::~CBuffer()
{
	ReleaseBuffer();
}

CBuffer::CBuffer(DWORD dwBufferSize)
{
	m_pByte = new BYTE[dwBufferSize];
	m_BufferSize = dwBufferSize;
	m_BufferValidSize = 0;
}

BOOL  CBuffer::SetSize(DWORD dwBufferSize)
{
	if (NULL != m_pByte)
		ReleaseBuffer();

	m_pByte = new BYTE[dwBufferSize];
	m_BufferSize = dwBufferSize;
	m_BufferValidSize = 0;

	return TRUE;
}

BOOL  CBuffer::ReleaseBuffer()
{
	if (NULL != m_pByte)
	{
		delete []m_pByte;
		m_pByte = NULL;
		m_BufferSize = 0;
		m_BufferValidSize = 0;
	}
	return TRUE;
}

BYTE* CBuffer::GetBuffer()
{
	return m_pByte;
}

DWORD CBuffer::GetSize()
{
	return m_BufferSize;
}

DWORD CBuffer::GetValidSize()
{
	return m_BufferValidSize;
}