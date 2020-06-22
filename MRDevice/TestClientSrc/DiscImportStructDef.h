#if !defined(__DISCIMPORTSTRUCTDEF_H__)
#define __DISCIMPORTSTRUCTDEF_H__

typedef enum _tagSelectState
{
	enumUnSelected			= 0,
	enumPartlySelected		= 1,
	enumSelected			= 2
} SelectedState;

typedef struct _tagDiscImportPatientStruct
{
	CString		strPatientUID;

	SelectedState		enumSelectState;

	CString		strPatientID;			// PatientID and 
	CString		strPatientName;
	CString		strPatientGender;		// M: Male, F: Female, O: Other
	DATE		dtBirthDate;			// Only Date is useful, Time is useless
	UINT		uStudyNum;
}DiscImportPatientStruct;

typedef struct _tagDiscImportStudyStruct
{
	CString		strStudyUID;
	CString		strPatientUID;

	SelectedState		enumSelectState;

	CString		strStudyID;
	DATE		dtStudyDateTime;
	CString		strRefPhisicianName;
	CString		strStudyDescription;
	UINT		uSeriesNum;
}DiscImportStudyStruct;

typedef struct _tagDiscImportSeriesStruct
{
	CString		strSeriesUID;
	CString		strStudyUID;

	SelectedState		enumSelectState;

	CString		strSeriesID;
	CString		strAprRegionName;
	UINT		uImageNum;
}DiscImportSeriesStruct;

typedef struct _tagDiscImportImageStruct
{
	CString		strImageUID;
	CString		strSeriesUID;

	SelectedState		enumSelectState;

	CString		strImageID;
	CString		strAprOrganName;
	UINT		uRows;
	UINT		uColumns;
}DiscImportImageStruct;

#endif // !defined(__DISCIMPORTSTRUCTDEF_H__)
