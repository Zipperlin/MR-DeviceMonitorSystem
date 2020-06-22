#if !defined(AFX_BURNDLG_H__E351BF99_2523_489D_941A_D99069F5D899__INCLUDED_)
#define AFX_BURNDLG_H__E351BF99_2523_489D_941A_D99069F5D899__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BurnDlg.h : header file
//
#include "..\\src\\PALib_i.h"
#include "TestClientSrcDlg.h"
#include "BurnPatientInfo.h"
#include <vector>
using namespace std;

class CTestClientSrcDlg;
//#include "NeroPartner.h"
/////////////////////////////////////////////////////////////////////////////
// CBurnDlg dialog

class CBurnDlg : public CDialog
{
// Construction
public:
	void OnButtonDelJob();
	void Init();
	CBurnDlg(CWnd* pParent = NULL);   // standard constructor

	void UpdateSpeedInfo(long lItemNum, BurnSpeedInfo* pSpeedInfo);
	void UpdateMediaInfo(BurnMediaInfo* pMediaInfo);
	void BurnMediaNotReady(BSTR bsInfo);
	
	void CheckDeviceAndDiscStatus();
	void UpdateDlgInfo();
	void UpdateJobList();
	
	void SetJobState(LPCTSTR szJobID, JobState enumJobState);
	void SetJobPhase(LPCTSTR szJobID, LPCTSTR szJobPhase);
	void SetJobProgress(JobProgressStruct* pJobProgressStruct);
	void SetJobDetail(JobDetailStruct* pJobDetailStruct);

	void ShowPatientInfo(long lItemNum, BurnPatientInfoStruct* pBurnPatientList);
	void ShowStudyInfo(long lItemNum, BurnStudyInfoStruct* pBurnStudyList);
	void ShowSeriesInfo(long lItemNum, BurnSeriesInfoStruct* pBurnSeriesList);
	void ShowImageInfo(long lItemNum, BurnImageInfoStruct* pBurnImageList);
	void ShowContentSize(unsigned long ulSizeInMega);

	vector<DWORD> m_vtrBurnSpeed;

// Dialog Data
	//{{AFX_DATA(CBurnDlg)
	enum { IDD = IDD_FORMVIEW_BURN };
	CButton	m_staticBurnPhase;
	CProgressCtrl	m_progressBurn;
	CEdit	m_editMessage;
	CListBox	m_listboxDirsAndFiles;
	CButton	m_ratioDiscTypeDVD;
	CComboBox	m_cbboxBurnSpeed;
	CListCtrl	m_CListJobList;
	
	CButton	m_ratioDiscTypeCD;
	CComboBox	m_cbboxDevices;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBurnDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
private:
// 	BOOL CompareDeviceInfo(DeviceInfo* pDeviceInfoFormer, DeviceInfo* pDeviceInfoLatter);
	BOOL GetBurnJobSettings(BurnJobSettingsByPA* pbjs);
	BOOL GetBurnUIDTypeAndList(long* plUIDNum, BSTR** ppbsUIDList, PatientAdminUIDType* penumUIDType);
	void UpdataEstimatedSize();

	void EnableWindowDuringGetDeviceMediaInfo(BOOL bEnable);

    IGeneralSys* m_pIGeneral; 
    IPAPrint* m_pIPAPrint;
	IPABurn* m_pIPABurn;

	HANDLE m_hCheckDeviceAndDiscStatusEvent;
	HANDLE m_hCheckDeviceAndDiscStatusThread;

// 	DeviceInfo m_DeviceInfo;
// 	DiscInfo m_DiscInfo;
// 	DeviceDiscInfo m_DeviceDiscInfo;
	BurnSettings m_BurnSettins;

	vector<CString> m_vtrPatientUIDs;
	vector<CString> m_vtrStudyUIDs;
	vector<CString> m_vtrSeriesUIDs;

	CBurnPatientInfo m_BurnPatientInfoDlg;
//	CNeroPartner m_BurnPartner;
protected:

	// Generated message map functions
	//{{AFX_MSG(CBurnDlg)
	afx_msg void OnButtonNeroapiinit();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeComboDevice();
	afx_msg void OnButtonBurn();
	afx_msg void OnButtonAddFiles();
	afx_msg void OnButtonAddDirs();
	afx_msg void OnButtonErase();
	afx_msg void OnButtonPause();
	afx_msg void OnButtonAbort();
	afx_msg void OnButtonDelete();
	afx_msg void OnButtonBurnbypa();
	afx_msg void OnCheckDicom();
	afx_msg void OnCheckBmp();
	afx_msg void OnCheckJpeg();
	afx_msg void OnSelchangeComboDownscale();
	afx_msg void OnButtonAddUid();
	afx_msg void OnButtonDelUid();
	afx_msg void OnSelchangeComboUidType();
	afx_msg void OnButtonCheckdevice();
	afx_msg void OnButtonUncheckdevice();
	afx_msg void OnButtonBurnprepare();
	afx_msg void OnButtonCancelburnprepare();
	afx_msg void OnSelchangeComboBurnType();
	afx_msg void OnButtonRefreshDeviceMediaInfo();
	afx_msg void OnButtonClearUid();
	afx_msg void OnButtonBurnUnfinishedjob();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BURNDLG_H__E351BF99_2523_489D_941A_D99069F5D899__INCLUDED_)
