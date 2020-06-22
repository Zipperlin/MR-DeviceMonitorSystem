/* Time: <@(#)FCPartner.cpp   2009-3-5 - 10:42:46   Fan Zengfei >
 *********************************************************************
 *  Philips-Neusoft Medical Systems Co. Corporation 
 *
 *  Project : 
 *
 *  File Name : FCPartner.cpp
 *         
 *  Author : Fan Zengfei                          Date: 2009-3-5
 *
 *  Description : Communication class with FilmComposer
 *
 *********************************************************************
 * Develop or modification record:
 *
 * $Log: $ 
 *
 *	1	2009-3-5 - 10:42:46		FanZF	Creation
 *
 *********************************************************************
 */

// FCPartner.cpp: implementation of the CFCPartner class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "FCPartner.h"
#include "PALib_i.h"
#include "Printing.h"
#include "Tlhelp32.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

DWORD WINAPI FCMonitorThreadProc(LPVOID lpParam) 
{ 
//	PRINTTRACE_ENTER_FUNCTION

	try
	{
		CFCPartner* pFCPartner = (CFCPartner*)lpParam;

		pFCPartner->FCMonitorProc();

		return THREADE_RET_CODE_OK; 
	}
	PA_CATCH_ERROR_RET(THREADE_RET_CODE_ERROR)
}

// DWORD WINAPI CheckFCStatusThreadProc(LPVOID lpParam) 
// { 
// //	PRINTTRACE_ENTER_FUNCTION
// 
// 	CFCPartner* pFCPartner = (CFCPartner*)lpParam;
// 
// 	pFCPartner->CheckFilmComposerStatus();
// 
// //	PRINTTRACE_LEAVE_FUNCTION
//     return THREADE_RET_CODE_OK; 
// }

CFCPartner::CFCPartner()
{
	m_IPrintQueue = NULL;

	m_FCProcessHandle = NULL;
// 	m_hCheckFCStatusThread = NULL;
	m_hFCMonitorEvent = NULL;
	m_FCMonitorHandle = NULL;

	m_PrintProcessInfo.hProcess = NULL;
	m_PrintProcessInfo.hThread = NULL;

	m_hFCLoadImageEvent = NULL;
// 	m_hFCSocketOKEvent = NULL;

// 	m_socketFCServer = INVALID_SOCKET;
// 	m_socketFCMonitorServer = INVALID_SOCKET;
// 	m_socketFCMonitorClient = INVALID_SOCKET;

	m_bImagesReachLimitation = FALSE;

	m_strFCFullPath = _T("");

	m_iActivePrintJobCount = 0;
	m_enumFCStatus = enumFilmComposerIdle;
}

CFCPartner::~CFCPartner()
{

}

BOOL CFCPartner::Init()
{
	m_iActivePrintJobCount = 0;
	m_strFCFullPath = GetFCFullPath();
	if (m_strFCFullPath.IsEmpty())
	{
		return FALSE;
	}

	//<< 启动FC
	if(!StartUpFilmComposer())
	{
		PRINTTRACE_ERROR("StartUpFilmComposer()")
		return FALSE;
	}

	//<< 获得PQ接口及PQSink连接
	if (!SetConnection())
	{
		PRINTTRACE_ERROR("SetConnection()")
		return FALSE;
	}


	m_hFCLoadImageEvent = CreateEvent(NULL, TRUE, TRUE, NULL);
	m_hFCMonitorEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
	m_FCMonitorHandle = CreateThread(NULL, 0, FCMonitorThreadProc, this, 0, NULL);
	if (NULL == m_FCMonitorHandle)
		return FALSE;
	else
		return TRUE;

	return TRUE;
}

BOOL CFCPartner::UnInit()
{
	BOOL bRet = TRUE;

	if (m_hFCLoadImageEvent)
	{
		CloseHandle(m_hFCLoadImageEvent);
		m_hFCLoadImageEvent = NULL;
	}

	// exit Monitor Thread
	if (m_FCMonitorHandle)
	{
		SetEvent(m_hFCMonitorEvent);
		
		DWORD dwRet = WaitForSingleObject(m_FCMonitorHandle, FILMCOMPOSER_MONITOR_THREAD_EXIT_WAIT_TIME);
		if (WAIT_OBJECT_0 == dwRet)
		{
		}
		else if(WAIT_TIMEOUT == dwRet)
		{
			if (TerminateThread(m_FCMonitorHandle, 0))
			{
				PRINTTRACE_INFO("TerminateThread(m_FCMonitorHandle, 0)")
			}
			else
			{
				bRet = FALSE;
				PRINTTRACE_ERROR("TerminateThread(m_FCMonitorHandle, 0)")
			}
		}
		CloseHandle(m_FCMonitorHandle);
		m_FCMonitorHandle = NULL;
		CloseHandle(m_hFCMonitorEvent);
		m_hFCMonitorEvent = NULL;
	}

	//<< 清空PQ中的任务（主要目的是停止正在执行及等待中的任务）

	m_iActivePrintJobCount = 0;


	//<< 断开PQ接口及PQSink连接
	if (!Disconnection())
	{
		bRet = FALSE;
		PRINTTRACE_ERROR("CFCPartner Disconnection() failed")
	}
	else
	{
		PRINTTRACE_INFO("CFCPartner Disconnection() succeed")
	}

	//<< 退出FC及PQ
	if (!ShutDownFilmComposer())
	{
		bRet = FALSE;
		PRINTTRACE_ERROR("CFCPartner ShutDownFilmComposer() failed")
	}
	else
	{
		PRINTTRACE_INFO("CFCPartner ShutDownFilmComposer() succeed")
	}
	
	return bRet;
}

BOOL CFCPartner::StartUpFilmComposer()
{
	BOOL bRet;
	
	if (GetFCHandle())
	{
		Notify(NOTIFY_FC_STARTUP);
		return TRUE;
	}
	
	if(NULL == m_FCProcessHandle)
	{	
		CString strFCFullPath;
		STARTUPINFO suInfo;
		memset (&suInfo, 0, sizeof(suInfo));
		suInfo.cb = sizeof(suInfo);
		suInfo.dwFlags = STARTF_USESHOWWINDOW ;
		suInfo.wShowWindow = SW_HIDE ;

		bRet = ::CreateProcess(m_strFCFullPath,
			NULL,
			NULL,
			NULL,
			FALSE,
			HIGH_PRIORITY_CLASS,
			NULL,
			NULL,
			&suInfo,
			&m_PrintProcessInfo);

		if(!bRet)
		{
			PRINTTRACE_ERROR("::CreateProcess(strFCFullPath...")
			return FALSE ;
		}
		else
		{
			m_FCProcessHandle = m_PrintProcessInfo.hProcess;

			// Find FC window
			HWND hFCWnd = NULL;
			int iRetryTimes = 0;
			while (!hFCWnd)
			{
				++iRetryTimes;
				if (iRetryTimes > 100)
				{
					PRINTTRACE_ERROR("iRetryTimes > 100")
					return FALSE;
				}
				else
				{
					Sleep(100);
					hFCWnd = ::FindWindow(_T("PNMS_FilmComposer"), NULL);
				}
			}

			CString strTrace;
			strTrace.Format(_T("iRetryTimes = %d"), iRetryTimes);
			PRINTTRACE_INFO(strTrace)

			CRect rc;
			::GetWindowRect(hFCWnd, &rc);
			::SetWindowPos(hFCWnd,HWND_NOTOPMOST,rc.left,rc.top,rc.right-rc.left,rc.bottom-rc.top,SWP_HIDEWINDOW);
			
			// CloseHandle of m_PrintProcessInfo.hThread since it's useless			
			CloseHandle(m_PrintProcessInfo.hThread);
			m_PrintProcessInfo.hThread = NULL;
			
			Notify(NOTIFY_FC_STARTUP);
			PRINTTRACE_INFO("Filmcoposer proc Created: CreateProcess(FILMCOMPOSER_FULL_PATH...)")
			return TRUE ;
		}
	}
	else
	{
		if (WAIT_TIMEOUT == WaitForSingleObject(m_FCProcessHandle, 0))
		{
			return TRUE;
		}
		else
		{
			CloseHandle(m_FCProcessHandle);
			m_FCProcessHandle = NULL;
			return StartUpFilmComposer();
		}
	}

	return TRUE;
}

BOOL CFCPartner::ShutDownFilmComposer()
{
	//<< FC
	CString strCMDLine;

	strCMDLine = m_strFCFullPath;
	strCMDLine += _T(" ");
	strCMDLine += FILMCOMPOSER_CMDLINE_CLOSE;

	if (!SendCMDLine(strCMDLine))
	{
		PRINTTRACE_ERROR("SendCMDLine(strCMDLine)")
		return FALSE;
	}

	//<< PQ
	HANDLE hSnapshot = CreateToolhelp32Snapshot( TH32CS_SNAPPROCESS, 0 );
	PROCESSENTRY32 pe32;
	pe32.dwSize = sizeof( PROCESSENTRY32 );
	Process32First( hSnapshot, &pe32 );
	do 
	{
		if (!CString(_T("PrintQueueManager.exe")).CompareNoCase(pe32.szExeFile))
		{
			//<< find PQ
			HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, FALSE, pe32.th32ProcessID);
			if (NULL == hProcess)
			{
				PRINTTRACE_ERROR("OpenProcess(PQ) failed")
			}
			else
			{
				BOOL bRet = TerminateProcess(hProcess, 0);
				if (!bRet)
				{
					PRINTTRACE_ERROR("TerminateProcess(PQ) failed")
				}

				CloseHandle(hProcess);
				hProcess = NULL;
			}
			break;
		}
	}while( Process32Next( hSnapshot, &pe32 ) ); 	
	
	CloseHandle( hSnapshot );

	return TRUE;
}

BOOL CFCPartner::GetFCHandle()
{
	if (m_FCProcessHandle)
	{
		if (WAIT_TIMEOUT == WaitForSingleObject(m_FCProcessHandle, 0))
			return TRUE;
		else
		{
			CloseHandle(m_FCProcessHandle);
			m_FCProcessHandle = NULL;
			return FALSE;
		}
	}
	else
	{
		PROCESSENTRY32 proc;
		HANDLE hSnapshot = NULL;
		BOOL bIsExist;	
		CString strProcName;
		BOOL bRet = FALSE;
		
		hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPALL, 0); //获取进程快照句柄
		proc.dwSize = sizeof(PROCESSENTRY32);
		bIsExist = Process32First(hSnapshot, &proc); //查找第一个进程
		while (bIsExist)
		{	
			strProcName = proc.szExeFile;
			if (_tcsicmp(strProcName, FILMCOMPOSER_PROCNAME) == 0) 
			{
				m_FCProcessHandle = OpenProcess(PROCESS_ALL_ACCESS, TRUE, proc.th32ProcessID);
				if (m_FCProcessHandle)
				{
					bRet = TRUE;
					break;
				}
				else
				{
					// FC is running but failed to get its HANDLE
					bRet = FALSE;
					break;
				}
			}
				
			bIsExist = Process32Next(hSnapshot, &proc);
		}
		CloseHandle(hSnapshot);
		return bRet;
	}
}


// BOOL CFCPartner::CheckFilmComposerStatus()
// {
// 
// 	char buf[128];
// 	struct sockaddr_in servaddr, cliaddr;
// 	int addrlen;
// 	if ((m_socketFCMonitorServer = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
// 	{
// 		 return FALSE;
// 	}
// 	memset(&servaddr, 0, sizeof(servaddr));
// 	servaddr.sin_family = AF_INET;
// 	servaddr.sin_port = htons(FILMCOMPOSER_CLIENT_PORT);
// 	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
//  
// 	
// 	int iRet = bind(m_socketFCMonitorServer, (struct sockaddr *)&servaddr, sizeof(servaddr));
// 	if (iRet)
// 	{
// 		iRet = WSAGetLastError();
// 
// 		return FALSE;
// 	}
// 	listen(m_socketFCMonitorServer, 5);
// 	
// 	addrlen = sizeof(cliaddr);
// 	while(TRUE)
// 	{
// 			
// 		if((m_socketFCMonitorClient = accept(m_socketFCMonitorServer, (struct sockaddr *)&cliaddr, &addrlen)) <0 )
// 		{
// 			iRet = WSAGetLastError();
// 			return FALSE;
// 		}
// 
// 		memset(buf, 0, sizeof(buf));		
// 		recv(m_socketFCMonitorClient, buf, sizeof(buf), 0);
// 		
// 		CString strAccepted = buf;
// 		
// 		if(-1 != strAccepted.Find(FILMCOMPOSER_STATUS_PRINTING))
// 		{
// 			if (!m_bIsFCPrinting)
// 			{
// 				m_bIsFCPrinting = TRUE;
// 				Notify(NOTIFY_FC_STATE_CHANGED, enumFilmComposerPRINTING);
// 			}
// 		}
// 		else if(-1 != strAccepted.Find(FILMCOMPOSER_STATUS_ERROR))
// 		{
// 			m_bIsFCPrinting = FALSE;
// 			Notify(NOTIFY_FC_STATE_CHANGED, enumFilmComposerERROR);
// 			Notify(NOTIFY_FC_ENABLE_FC, TRUE);
// 		}
// 		else if(-1 != strAccepted.Find(FILMCOMPOSER_STATUS_SUCCESS))
// 		{
// 			m_bIsFCPrinting = FALSE;
// 			Notify(NOTIFY_FC_STATE_CHANGED, enumFilmComposerSUCCESS);
// 			Notify(NOTIFY_FC_ENABLE_FC, TRUE);
// 		}
// 		else if(-1 != strAccepted.Find(FILMCOMPOSER_STATUS_STOPOVER))
// 		{
// 			if (m_bIsFCPrinting)
// 			{
// 				m_bIsFCPrinting = FALSE;
// 				Notify(NOTIFY_FC_STATE_CHANGED, enumFilmComposerSTOPOVER);
// 				Notify(NOTIFY_FC_ENABLE_FC, TRUE);
// 			}
// 		}
// 		else if (-1 != strAccepted.Find(FILMCOMPOSER_STATUS_BREAK))
// 		{
// 			Notify(NOTIFY_FC_ENABLE_FC, TRUE);
// 		}
// 		else if(-1 != strAccepted.Find(FILMCOMPOSER_IMAGES_LIMITED))
// 		{
// 			if (!m_bImagesReachLimitation)
// 			{
// 				m_bImagesReachLimitation = TRUE;
//  				Notify(NOTIFY_FC_LOAD_IMAGE_LIMITED);
// 			}
// 		}
// 		else if (-1 != strAccepted.Find(FILMCOMPOSER_STATUS_INVALID_PRINTER))
// 		{
// 			Notify(NOTIFY_FC_INVALID_PRINTER);
// 		}
// 		else if (!strAccepted.Compare(FILMCOMPOSER_RECEIVED_OK))
// 		{
// 			SetEvent(m_hFCSocketOKEvent);
// 		}
// 		else
// 		{
// 			PRINTTRACE_WARNING(strAccepted)
// 			Notify(NOTIFY_FC_STATE_CHANGED, enumFilmComposerUNKNOW);
// 		}
// 		closesocket(m_socketFCMonitorClient);
// 
// 		PRINTTRACE_INFO(strAccepted)
// 		
// 	}
// 
// 
// 	return TRUE;
// }


BOOL CFCPartner::FCMonitorProc()
{
	BOOL bRet = TRUE;
	DWORD dwRet;

	while (TRUE)
	{
		dwRet = WaitForSingleObject(m_hFCMonitorEvent, FILMCOMPOSER_MONITOR_INSPECT_TIME);
		if (WAIT_TIMEOUT == dwRet)
		{
			if (NULL != m_FCProcessHandle)
			{
				if (WAIT_TIMEOUT == WaitForSingleObject(m_FCProcessHandle, 0))
				{
					continue;
				}
				else
				{
					// the original FC is not existed, but maybe a new on is running

					if (!Disconnection())
					{
						bRet = FALSE;
						break;
					}

					CloseHandle(m_FCProcessHandle);
					m_FCProcessHandle = NULL;

					if(StartUpFilmComposer())
					{
						if (!SetConnection())
						{
							bRet = FALSE;
							break;
						}
					}	
					else
					{
						bRet = FALSE;
						break;
					}
				}
			}
		}
		else if (WAIT_OBJECT_0 == dwRet)
		{
			break;
		}

	}
	return bRet;
}

BOOL CFCPartner::SetConnection()
{
	BOOL bRet = TRUE;
	HRESULT hr = CoCreateInstance(CLSID_PrintQueue, NULL, CLSCTX_LOCAL_SERVER, IID_IPrintQueue, (LPVOID*)&m_IPrintQueue);
	if (S_OK != hr)
	{
		PRINTTRACE_ERROR("CoCreateInstance(CLSID_PrintQueue, NULL, CLSCTX_LOCAL_SERVER, IID_IPrintQueue, (LPVOID*)&m_IPrintQueue) failed!")
		return FALSE;
	}

	//<< 连接点
	m_PQSink.Attch(this);
	bRet = m_PQSink.SetConnection(CLSID_PrintQueue, DIID__IPrintQueueChangeEvents);
	if (!bRet)
	{
		PRINTTRACE_ERROR("m_PQSink.SetConnection(CLSID_PrintQueue, DIID__IPrintQueueChangeEvents)")
		return FALSE;
	}

	return TRUE;
}

BOOL CFCPartner::Disconnection()
{
	BOOL bRet = TRUE;
	if (NULL != m_IPrintQueue)
	{
		m_IPrintQueue->Release();
		m_IPrintQueue = NULL;
	}

	m_PQSink.Detach();
	m_PQSink.ReleaseConnection();

	return bRet;
}

BOOL CFCPartner::SendCMDLine(CString& strCMDLine)
{
	if (NULL == m_FCProcessHandle)
		return FALSE;

	CBuffer aBuffer(strCMDLine.GetLength() + 1);
	WideCharToMultiByte(CP_ACP, WC_COMPOSITECHECK, strCMDLine, -1, (LPSTR)aBuffer.GetBuffer(), aBuffer.GetSize(), NULL, NULL ); 
	::WinExec((LPSTR)aBuffer.GetBuffer(), SW_SHOW);
	return TRUE;
}

BOOL CFCPartner::LoadImage(CString& strImageFullName)
{
	if (NULL == m_FCProcessHandle)
		return FALSE;

	CString strCMDLine;

	strCMDLine = m_strFCFullPath;

	//GaoXing 每次发送图象到FC，FC负责删除副本临时文件
	strCMDLine += _T(" ");
	strCMDLine += _T("-autoremove");
	
	strCMDLine += _T(" ");
	strCMDLine += FILMCOMPOSER_CMDLINE_LOADIMAGE;

	strCMDLine += _T(" ");
	strCMDLine += strImageFullName;

	if (!SendCMDLine(strCMDLine))
	{
		PRINTTRACE_ERROR("SendCMDLine(strCMDLine)")
		return FALSE;
	}

	return TRUE;
}

BOOL CFCPartner::LoadImages(vector<CString>* pvtrDICOMImages, BOOL* pJobCancelFlag)
{

	Notify(NOTIFY_FC_LOAD_IMAGE_PROGRESS, 0, pvtrDICOMImages->size());

	if (NULL == m_FCProcessHandle)
		return FALSE;

	char* szCMDLineBuffer = new char[MAX_PATH * (FILMCOMPOSER_LOADIMAGES_MAX_PER_TIME + 1)];

	m_bImagesReachLimitation = FALSE;

	for (INT i = 0; i < pvtrDICOMImages->size(); )
	{
		WaitForSingleObject(m_hFCLoadImageEvent, INFINITE);

		// Is Job Cancelled?
		if (*pJobCancelFlag)
		{
			delete []szCMDLineBuffer;
			return TRUE;
		}

		CString strCMDLine = m_strFCFullPath;
		strCMDLine += _T(" ");
		strCMDLine += FILMCOMPOSER_CMDLINE_LOADIMAGE;
		
		int iImageCountLoaded = 0;
		while (i < pvtrDICOMImages->size() && iImageCountLoaded < FILMCOMPOSER_LOADIMAGES_MAX_PER_TIME)
		{
			strCMDLine += _T(" ");
			strCMDLine += (*pvtrDICOMImages)[i];

			++i;
			++iImageCountLoaded;
		}

		memzero(szCMDLineBuffer, MAX_PATH * (FILMCOMPOSER_LOADIMAGES_MAX_PER_TIME + 1));
		WideCharToMultiByte(CP_ACP, WC_COMPOSITECHECK, strCMDLine, -1, szCMDLineBuffer, MAX_PATH * (pvtrDICOMImages->size() +1), NULL, NULL ); 
		if (::WinExec(szCMDLineBuffer, SW_SHOWNOACTIVATE) > 31)
		{
			Notify(NOTIFY_FC_LOAD_IMAGE_PROGRESS, i, pvtrDICOMImages->size());
			PRINTTRACE_INFO("::WinExec(szCMDLineBuffer, SW_SHOW) > 31")

			// Waiting for socket msg from FC
			Sleep(10);

			// Reach FC Images Limitation or not
			if (m_bImagesReachLimitation)
			{
				delete []szCMDLineBuffer;
				return FALSE;
			}
		}
		else
		{
			PRINTTRACE_ERROR("::WinExec(szCMDLineBuffer, SW_SHOW) <= 31")
			delete []szCMDLineBuffer;
			return FALSE;
		}


	}
	
	delete []szCMDLineBuffer;
	return TRUE;

}

BOOL CFCPartner::SetRowAndCol(UINT uiRow, UINT uiCol)
{
	if (NULL == m_FCProcessHandle)
		return FALSE;

	CString strCMDLine;
	CString strRow;
	CString strCol;

	strRow.Format(_T(" %d "), uiRow);
	strCol.Format(_T(" %d"), uiCol);

	strCMDLine = m_strFCFullPath;
	strCMDLine += _T(" ");
	strCMDLine += FILMCOMPOSER_CMDLINE_ROW;
	strCMDLine += strRow;
	strCMDLine += FILMCOMPOSER_CMDLINE_COL;
	strCMDLine += strCol;

	if (!SendCMDLine(strCMDLine))
	{
		return FALSE;
	}

	return TRUE;
	
}

// BOOL CFCPartner::SendCMD(char* buf, UINT len)
// {
// 	int iRet;
// 	struct sockaddr_in servaddr;
// 	if ((m_socketFCServer = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
// 	{
// 		iRet = WSAGetLastError();
// 		return FALSE;
// 	}
// 	memset(&servaddr, 0, sizeof(servaddr));
// 	servaddr.sin_family = AF_INET;
// 
// 	servaddr.sin_addr.s_addr = inet_addr(FILMCOMPOSER_HOST_ADRESS);
// 	servaddr.sin_port = htons(FILMCOMPOSER_SERVER_PORT);
//  
// 	if(SOCKET_ERROR == connect(m_socketFCServer, (struct sockaddr *)&servaddr, sizeof(servaddr)))
// 	{
// 		PRINTTRACE_ERROR(_T("ERROR: Connect to FC server"));
// 		iRet = WSAGetLastError();
// 
// 		closesocket(m_socketFCServer);
// 		m_socketFCServer = INVALID_SOCKET;
// 		return FALSE;
// 	}
// 
// 	if (SOCKET_ERROR == send(m_socketFCServer, buf, len, 0))
// 	{
// 		PRINTTRACE_ERROR("SOCKET_ERROR == send(...), buf: ")
// 		PRINTTRACE_INFO(buf)
// 		closesocket(m_socketFCServer);
// 		m_socketFCServer = INVALID_SOCKET;
// 		return FALSE;
// 	}
// 	else
// 	{
// 		PRINTTRACE_INFO("SOCKET_ERROR != send(...)")
// 		PRINTTRACE_INFO(buf)
// 		closesocket(m_socketFCServer);
// 		m_socketFCServer = INVALID_SOCKET;
// 		return TRUE;
// 	}
// }

// BOOL CFCPartner::ShowProgressBar(BOOL bShow)
// {
// 	char szCMDBuffer[FILMCOMPOSER_SOCKET_BUFFER_LEN] = {0};
// 
// 	if (bShow)
// 	{
// 		if (m_bIsFCPrinting)
// 		{
// 			WideCharToMultiByte (CP_ACP, WC_COMPOSITECHECK, FILMCOMPOSER_SEND_SHOW_PROGRESSBAR, -1, szCMDBuffer, sizeof(szCMDBuffer), NULL, NULL);
// 			return SendCMD(szCMDBuffer, FILMCOMPOSER_SOCKET_BUFFER_LEN);
// 		}
// 		else
// 		{
// 			return TRUE;
// 		}
// 	}
// 	else
// 	{
// 		WideCharToMultiByte (CP_ACP, WC_COMPOSITECHECK, FILMCOMPOSER_SEND_HIDE_PROGRESSBAR, -1, szCMDBuffer, sizeof(szCMDBuffer), NULL, NULL);
// 		return SendCMD(szCMDBuffer, FILMCOMPOSER_SOCKET_BUFFER_LEN);
// 	}
// }

BOOL CFCPartner::SaveSession()
{
	return TRUE;
}

BOOL CFCPartner::CancelPrinting()
{
// 	if (m_bIsFCPrinting)
// 	{
// 		char szCMDBuffer[FILMCOMPOSER_SOCKET_BUFFER_LEN] = {0};
// 		WideCharToMultiByte (CP_ACP, WC_COMPOSITECHECK, FILMCOMPOSER_SEND_SUSPEND, -1, szCMDBuffer, sizeof(szCMDBuffer), NULL, NULL);
// 
// 		UINT uFCCMDRetryTime = 0;
// 		while (++uFCCMDRetryTime <= FILMCOMPOSER_SEND_CMD_RETRY_TIMES)
// 		{
// 			ResetEvent(m_hFCSocketOKEvent);
// 
// 			if (!SendCMD(szCMDBuffer, FILMCOMPOSER_SOCKET_BUFFER_LEN))
// 			{
// 				PRINTTRACE_ERROR("SendCMD(szCMDBuffer, FILMCOMPOSER_SOCKET_BUFFER_LEN")
// 				continue;
// //				return FALSE;
// 			}
// 
// 			if (WAIT_OBJECT_0 == WaitForSingleObject(m_hFCSocketOKEvent, FILMCOMPOSER_RECEIVE_OK_WAIT_TIME))
// 			{
// 				// Recieved OK
// 				return TRUE;
// 			}
// 			else
// 			{
// 				// Not Recieved, so resend
// 				continue;
// 			}
// 		}
// 
// 		if (uFCCMDRetryTime > FILMCOMPOSER_SEND_CMD_RETRY_TIMES)
// 		{
// 			// Still not Recieved OK after N time retry, so Terminate FC
// 			PRINTTRACE_WARNING("uFCCMDRetryTime > FILMCOMPOSER_SEND_CMD_RETRY_TIMES")
// 			if (::TerminateProcess(m_FCProcessHandle, 0))
// 			{
// 				PRINTTRACE_ERROR("::TerminateProcess(m_FCProcessHandle, 0)")
// 				return FALSE;
// 			}
// 			else
// 			{
// 				return TRUE;
// 			}
// 
// 		}
// 
// 		return TRUE;
// 	}
// 	else
// 	{
// 		return TRUE;
// 	}

	return TRUE;
}

BOOL CFCPartner::IsFCPrinting()
{
	if (enumFilmComposerPRINTING == m_enumFCStatus)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

void CFCPartner::EnableLoadImage()
{
	SetEvent(m_hFCLoadImageEvent);
}

void CFCPartner::DisableLoadImage()
{
	ResetEvent(m_hFCLoadImageEvent);
}

void CFCPartner::PQStateChangeNotify(LPCTSTR szJobUID, PQ_EPrintJobStatusChange operation)
{
	CString strTrace;
	
	CString strJobUID = szJobUID;
	CString strOperation;

	//<< ActivePrintJobCount计数规则：
	//<< XX_2_PRINTING，则计数+1
	//<< XX_2_COMPLETE, FAILURE, SUSPEND，则计数-1

	switch (operation)
	{
	case STATUS_CHANGE_NEW_JOB:
		strOperation = _T("STATUS_CHANGE_NEW_JOB");
		break;
	case STATUS_CHANGE_SUSPEND_2_READY:
		strOperation = _T("STATUS_CHANGE_SUSPEND_2_READY");
		break;
	case STATUS_CHANGE_READY_2_PRINTING:
		++m_iActivePrintJobCount;
		if (m_iActivePrintJobCount == 1)
		{
			m_enumFCStatus = enumFilmComposerPRINTING;
			Notify(NOTIFY_FC_STATE_CHANGED, m_enumFCStatus);
		}
		else if (m_iActivePrintJobCount > 1)
		{
			;
		}
		else
		{
			//<< <=0, error
			strTrace.Format(_T("m_iActivePrintJobCount = %d"), m_iActivePrintJobCount);
			PRINTTRACE_ERROR(strTrace)
		}
		strOperation = _T("STATUS_CHANGE_READY_2_PRINTING");
	    break;
	case STATUS_CHANGE_PRINTING_2_COMPLETE:
		--m_iActivePrintJobCount;
		if (m_iActivePrintJobCount == 0)
		{
			m_enumFCStatus = enumFilmComposerIdle;
			Notify(NOTIFY_FC_STATE_CHANGED, m_enumFCStatus);
		}
		else if (m_iActivePrintJobCount > 0)
		{
			;
		}
		else
		{
			//<< <0, error
			strTrace.Format(_T("m_iActivePrintJobCount = %d"), m_iActivePrintJobCount);
			PRINTTRACE_ERROR(strTrace)
		}
		strOperation = _T("STATUS_CHANGE_PRINTING_2_COMPLETE");
	    break;
	case STATUS_CHANGE_PRINTING_2_FAILURE:
		--m_iActivePrintJobCount;
		if (m_iActivePrintJobCount == 0)
		{
			m_enumFCStatus = enumFilmComposerIdle;
			Notify(NOTIFY_FC_STATE_CHANGED, m_enumFCStatus);
		}
		else if (m_iActivePrintJobCount > 0)
		{
			;
		}
		else
		{
			//<< <0, error
			strTrace.Format(_T("m_iActivePrintJobCount = %d"), m_iActivePrintJobCount);
			PRINTTRACE_ERROR(strTrace)
		}
		strOperation = _T("STATUS_CHANGE_PRINTING_2_FAILURE");
		break;
	case STATUS_CHANGE_PRINTING_2_SUSPEND:
		--m_iActivePrintJobCount;
		if (m_iActivePrintJobCount == 0)
		{
			m_enumFCStatus = enumFilmComposerIdle;
			Notify(NOTIFY_FC_STATE_CHANGED, m_enumFCStatus);
		}
		else if (m_iActivePrintJobCount > 0)
		{
			;
		}
		else
		{
			//<< <0, error
			strTrace.Format(_T("m_iActivePrintJobCount = %d"), m_iActivePrintJobCount);
			PRINTTRACE_ERROR(strTrace)
		}
		strOperation = _T("STATUS_CHANGE_PRINTING_2_SUSPEND");
		break;
	case STATUS_CHANGE_FAILURE_2_READY:
		++m_iActivePrintJobCount;
		if (m_iActivePrintJobCount == 1)
		{
			m_enumFCStatus = enumFilmComposerPRINTING;
			Notify(NOTIFY_FC_STATE_CHANGED, m_enumFCStatus);
		}
		else if (m_iActivePrintJobCount > 1)
		{
			;
		}
		else
		{
			//<< <=0, error
			strTrace.Format(_T("m_iActivePrintJobCount = %d"), m_iActivePrintJobCount);
			PRINTTRACE_ERROR(strTrace)
		}
		strOperation = _T("STATUS_CHANGE_FAILURE_2_READY");
	    break;
	case STATUS_CHANGE_ONEFILM_COMPLETE:
		strOperation = _T("STATUS_CHANGE_ONEFILM_COMPLETE");
	    break;
	case STATUS_CHANGE_JOB_REMOVE:
		strOperation = _T("STATUS_CHANGE_JOB_REMOVE");
	    break;
	case STATUS_CHANGE_JOB_REMOVEALL:
		m_iActivePrintJobCount = 0;
		if (enumFilmComposerPRINTING == m_enumFCStatus)
		{
			m_enumFCStatus = enumFilmComposerIdle;
			Notify(NOTIFY_FC_STATE_CHANGED, m_enumFCStatus);
		}

		strOperation = _T("STATUS_CHANGE_JOB_REMOVEALL");
	    break;
	case STATUS_CHANGE_JOB_MOVEDOWN:
		strOperation = _T("STATUS_CHANGE_JOB_MOVEDOWN");
	    break;
	case STATUS_CHANGE_JOB_MOVEUP:
		strOperation = _T("STATUS_CHANGE_JOB_MOVEUP");
	    break;
	case STATUS_CHANGE_JOB_MOVE2TOP:
		strOperation = _T("STATUS_CHANGE_JOB_MOVE2TOP");
	    break;
	case STATUS_CHANGE_JOB_STOP_PRINTING:
		strOperation = _T("STATUS_CHANGE_JOB_STOP_PRINTING");
	    break;
	case STATUS_CHANGE_JOB_STOP_NOT_PRINTING:
		strOperation = _T("STATUS_CHANGE_JOB_STOP_NOT_PRINTING");
	    break;
	default:
		strOperation = _T("unknow status change");
	    break;
	}

	strTrace.Format(_T("Print Queue state changed: %s %s"), strJobUID, strOperation);
	PRINTTRACE_INFO(strTrace)
}


CString CFCPartner::GetFCFullPath()
{
	DWORD dwBufferLen = MAX_PATH;
	TCHAR szBuffer[MAX_PATH] = {0};

	CString strFCFullPath;

	DWORD dwRet = GetModuleFileName(NULL, szBuffer, MAX_PATH);
	if (0 != dwRet)
	{
		wchar_t* p = wcsrchr(szBuffer, _T('\\'));
		if (NULL != p)
		{
			*p = _T('\0');
			strFCFullPath = szBuffer;
			strFCFullPath += FILMCOMPOSER_DIRECTORY;
			strFCFullPath += _T("\\");
			strFCFullPath += FILMCOMPOSER_PROCNAME;
			
			PRINTTRACE_INFO(strFCFullPath)
			return strFCFullPath;
		}
		else
		{
			return _T("");
		}
	}
	else
	{
		return _T("");
	}

}
