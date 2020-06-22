/* Time: <@(#)IDPathGen.h   2009-3-5 - 10:45:18   Fan Zengfei >
 *********************************************************************
 *  Philips-Neusoft Medical Systems Co. Corporation 
 *
 *  Project : 
 *
 *  File Name : IDPathGen.h
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
 *	1	2009-3-5 - 10:45:18		FanZF	Creation
 *
 *********************************************************************
 */

// IDPathGen.h: interface for the CIDPathGen class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IDPATHGEN_H__A893ACEB_3903_46A3_A678_A31EEECD070C__INCLUDED_)
#define AFX_IDPATHGEN_H__A893ACEB_3903_46A3_A678_A31EEECD070C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CIDPathGen  
{
public:
	virtual ~CIDPathGen();

	static CIDPathGen* GetInstance();
	void ReleaseInstance();

	CString GenPatientID();
	CString GenPatientImagePath();
	CString GenStudyImagePath(LPCTSTR szPatientImagePath);
	CString GenSeriesImagePath(LPCTSTR szStudyImagePath);
	CString GenImagePath(LPCTSTR szSeriesImagePath, LPCTSTR szImageUID);
	CString GenPostProcessedImagePath(LPCTSTR szSeriesImagePath, LPCTSTR szImageUID);
	CString GenPostProcessedImagePSPath(LPCTSTR szPostProcessedImagePath);

private:
	CIDPathGen();


	static CIDPathGen*	m_pInstance;

	int					m_iCreateRandomNum;
};

#endif // !defined(AFX_IDPATHGEN_H__A893ACEB_3903_46A3_A678_A31EEECD070C__INCLUDED_)
