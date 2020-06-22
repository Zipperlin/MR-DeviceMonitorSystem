/* Time: <@(#)IDPathGen.cpp   2009-3-5 - 10:45:50   Fan Zengfei >
 *********************************************************************
 *  Philips-Neusoft Medical Systems Co. Corporation 
 *
 *  Project : 
 *
 *  File Name : IDPathGen.cpp
 *         
 *  Author : Fan Zengfei                          Date: 2009-3-5
 *
 *  Description : The generation of ID and path according with PatientAdmin
 *
 *********************************************************************
 * Develop or modification record:
 *
 * $Log: $ 
 *
 *	1	2009-3-5 - 10:45:50		FanZF	Creation
 *
 *********************************************************************
 */

// IDPathGen.cpp: implementation of the CIDPathGen class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "IDPathGen.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CIDPathGen* CIDPathGen::m_pInstance = NULL;

CIDPathGen::CIDPathGen()
{
	m_iCreateRandomNum = 0;
}

CIDPathGen::~CIDPathGen()
{

}

CIDPathGen* CIDPathGen::GetInstance()
{
	if (NULL == m_pInstance)
	{
		m_pInstance = new CIDPathGen;
	}

	return m_pInstance;
}

void CIDPathGen::ReleaseInstance()
{
	if (m_pInstance)
	{
		delete m_pInstance;
		m_pInstance = NULL;
	}
}

CString CIDPathGen::GenPatientID()
{
	SYSTEMTIME st;
	::GetLocalTime(&st);
	m_iCreateRandomNum = (++m_iCreateRandomNum) % 100;
	CString strTemp;
	strTemp.Format(_T("%04d%02d%02d%02d%02d%02d%03d%02d"), st.wYear, st.wMonth,
				st.wDay, st.wHour, st.wMinute, st.wSecond, st.wMilliseconds, m_iCreateRandomNum);

	return strTemp;
}

CString CIDPathGen::GenPatientImagePath()
{
	SYSTEMTIME st;
	::GetLocalTime(&st);
	m_iCreateRandomNum = (++m_iCreateRandomNum) % 100;
	CString strPatientImagePath;
	strPatientImagePath.Format(_T("\\P%04d%02d%02d%02d%02d%02d%03d%02d"), st.wYear, st.wMonth,
		st.wDay, st.wHour, st.wMinute, st.wSecond, st.wMilliseconds, m_iCreateRandomNum);
	return strPatientImagePath;
}

CString CIDPathGen::GenStudyImagePath(LPCTSTR szPatientImagePath)
{
	SYSTEMTIME st;
	::GetLocalTime(&st);
	m_iCreateRandomNum = (++m_iCreateRandomNum) % 100;
	CString strStudyImagePath;
	strStudyImagePath.Format(_T("%s\\S%04d%02d%02d%02d%02d%02d%03d%02d"), szPatientImagePath, st.wYear, st.wMonth,
		st.wDay, st.wHour, st.wMinute, st.wSecond, st.wMilliseconds, m_iCreateRandomNum);
	return strStudyImagePath;
}

CString CIDPathGen::GenSeriesImagePath(LPCTSTR szStudyImagePath)
{
	SYSTEMTIME st;
	::GetLocalTime(&st);
	m_iCreateRandomNum = (++m_iCreateRandomNum) % 100;
	CString strSeriesImagePath;
	strSeriesImagePath.Format(_T("%s\\%04d%02d%02d%02d%02d%02d%03d%02d"), szStudyImagePath, st.wYear, st.wMonth,
		st.wDay, st.wHour, st.wMinute, st.wSecond, st.wMilliseconds, m_iCreateRandomNum);
	return strSeriesImagePath;
}

CString CIDPathGen::GenImagePath(LPCTSTR szSeriesImagePath, LPCTSTR szImageUID)
{
	CString strImagePath;
	strImagePath.Format(_T("%s\\I%s.dcm"), szSeriesImagePath, szImageUID);
	return strImagePath;
}

CString CIDPathGen::GenPostProcessedImagePath(LPCTSTR szSeriesImagePath, LPCTSTR szImageUID)
{
	CString strImagePath;
	strImagePath.Format(_T("%s\\I%s_pro.dcm"), szSeriesImagePath, szImageUID);
	return strImagePath;
}

CString CIDPathGen::GenPostProcessedImagePSPath(LPCTSTR szPostProcessedImagePath)
{
	CString strPSPath;
	CString strPostProcessedImage = szPostProcessedImagePath;
	int iPos = strPostProcessedImage.ReverseFind(_T('.'));
	strPSPath = strPostProcessedImage.Left(iPos);
	strPSPath += DICOM_DCM_PS_FILE_EXTEND_NAME;

	return strPSPath;
}
