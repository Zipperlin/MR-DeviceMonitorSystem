#include "stdafx.h"

#include "SystemEventProxy.h"


CSystemEventProxy::CSystemEventProxy( void )
{
	PRINTTRACE_ENTER_FUNCTION
	PRINTTRACE_LEAVE_FUNCTION	
}

CSystemEventProxy::~CSystemEventProxy( void )
{
	PRINTTRACE_ENTER_FUNCTION
	m_pInterface = NULL;
	PRINTTRACE_LEAVE_FUNCTION
}
