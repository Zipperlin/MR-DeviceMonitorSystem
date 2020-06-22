/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Tue Feb 06 14:59:21 2018
 */
/* Compiler settings for PATestClientExt.idl:
    Oicf (OptLev=i2), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
*/
//@@MIDL_FILE_HEADING(  )


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 440
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __PATestClientLibExt_i_h__
#define __PATestClientLibExt_i_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IDBPIM_FWD_DEFINED__
#define __IDBPIM_FWD_DEFINED__
typedef interface IDBPIM IDBPIM;
#endif 	/* __IDBPIM_FWD_DEFINED__ */


#ifndef __IDBConfig_FWD_DEFINED__
#define __IDBConfig_FWD_DEFINED__
typedef interface IDBConfig IDBConfig;
#endif 	/* __IDBConfig_FWD_DEFINED__ */


#ifndef __IDBSession_FWD_DEFINED__
#define __IDBSession_FWD_DEFINED__
typedef interface IDBSession IDBSession;
#endif 	/* __IDBSession_FWD_DEFINED__ */


#ifndef __DBPIM_FWD_DEFINED__
#define __DBPIM_FWD_DEFINED__

#ifdef __cplusplus
typedef class DBPIM DBPIM;
#else
typedef struct DBPIM DBPIM;
#endif /* __cplusplus */

#endif 	/* __DBPIM_FWD_DEFINED__ */


#ifndef __DBConfig_FWD_DEFINED__
#define __DBConfig_FWD_DEFINED__

#ifdef __cplusplus
typedef class DBConfig DBConfig;
#else
typedef struct DBConfig DBConfig;
#endif /* __cplusplus */

#endif 	/* __DBConfig_FWD_DEFINED__ */


#ifndef __DBSession_FWD_DEFINED__
#define __DBSession_FWD_DEFINED__

#ifdef __cplusplus
typedef class DBSession DBSession;
#else
typedef struct DBSession DBSession;
#endif /* __cplusplus */

#endif 	/* __DBSession_FWD_DEFINED__ */


#ifndef __ISATL_FWD_DEFINED__
#define __ISATL_FWD_DEFINED__

#ifdef __cplusplus
typedef class ISATL ISATL;
#else
typedef struct ISATL ISATL;
#endif /* __cplusplus */

#endif 	/* __ISATL_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/* interface __MIDL_itf_PATestClientExt_0000 */
/* [local] */ 

#ifndef __GENERALDEFINE_IDL__
#define __GENERALDEFINE_IDL__
typedef 
enum _STARTUPRESULT
    {	enumSTARTUPRESULT_UNKNOWN	= 0,
	enumSTARTUPRESULT_SUCCESS	= enumSTARTUPRESULT_UNKNOWN + 1,
	enumSTARTUPRESULT_FAILED	= enumSTARTUPRESULT_SUCCESS + 1
    }	STARTUPRESULT;

typedef 
enum _WORKSTATE
    {	enumWORKSTATE_UNKNOWN	= 0,
	enumWORKSTATE_UNINITIALIZED	= enumWORKSTATE_UNKNOWN + 1,
	enumWORKSTATE_INITIALIZING	= enumWORKSTATE_UNINITIALIZED + 1,
	enumWORKSTATE_READY	= enumWORKSTATE_INITIALIZING + 1,
	enumWORKSTATE_WORKING	= enumWORKSTATE_READY + 1,
	enumWORKSTATE_EMERGENCYSTOP	= enumWORKSTATE_WORKING + 1,
	enumWORKSTATE_RESTARTING	= enumWORKSTATE_EMERGENCYSTOP + 1,
	enumWORKSTATE_ERROR	= enumWORKSTATE_RESTARTING + 1,
	enumWORKSTATE_UNINITIALIZING	= enumWORKSTATE_ERROR + 1
    }	WORKSTATE;

#endif
typedef 
enum _MPPS_STATE
    {	enumMPPSStatus_NotImported	= 0,
	enumMPPSStatus_Imported	= 1,
	enumMPPSStatus_InProgress	= 2,
	enumMPPSStatus_Discontinued	= 3,
	enumMPPSStatus_Completed	= 4
    }	MPPS_STATE;

typedef 
enum _PATIENT_TYPE
    {	enumNormalPatient	= 0,
	enumEmergencyPatient	= enumNormalPatient + 1,
	enumServicePatient	= enumEmergencyPatient + 1
    }	PATIENT_TYPE;

typedef 
enum _WORKSTATE_TYPE
    {	enumApplicaton	= 1,
	enumDemo	= enumApplicaton + 1
    }	WORKSTATE_TYPE;

typedef 
enum _UID_TYPE
    {	enumPatient	= 1,
	enumStudy	= enumPatient + 1,
	enumSeries	= enumStudy + 1,
	enumImage	= enumSeries + 1,
	enumAprRegion	= enumImage + 1,
	enumAprOrgan	= enumAprRegion + 1
    }	UID_TYPE;

typedef struct  ComplexSearchStruct
    {
    BSTR bsFieldName;
    BSTR bsFieldValue;
    }	ComplexSearchStruct;

typedef struct  ShutterStruct
    {
    INT iLeftVerticalEdge;
    INT iRightVerticalEdge;
    INT iUpperHorizontalEdge;
    INT iLowerHorizontalEdge;
    }	ShutterStruct;

typedef struct  ConfigInfoStruct
    {
    LONG lID;
    BSTR bsManufacture;
    BSTR bsSoftwareVersion;
    DOUBLE dbSpatialResolution;
    DATE dtLastCalibrationDate;
    DATE dtLastCalibrationTime;
    BSTR bsInstitutionName;
    BSTR bsInstitutionAddress;
    BSTR bsStationName;
    DATE dtLastStudyDateTime;
    BSTR bsInstitutionalDepartmentName;
    BSTR bsManufacturerModelName;
    BSTR bsDeviceSerialNumber;
    DOUBLE dbImagerPixelSpacingY;
    DOUBLE dbImagerPixelSpacingX;
    LONG lColumns;
    LONG lRow;
    INT iSamplesPerPixel;
    INT iPhotometricInterpretation;
    INT iBitAllocated;
    INT iBitStored;
    INT iHighBit;
    BSTR bsLastRecPatientUID;
    BSTR bsDetectorType;
    BSTR bsPositionerType;
    INT iPixelIntensitvRelationship;
    INT iPixelIntensitvRelationshipSign;
    INT iPixelRepresentation;
    INT iRescaleIntercept;
    INT iRescaleSlope;
    BSTR bsRescaleType;
    INT iSmallestImagePixelValue;
    INT iLargestImagePixelValue;
    INT iDefaultShutterExtraOpen;
    float fBigFocalSpotActulSize;
    float fSmallFocalSpotActulSize;
    }	ConfigInfoStruct;

typedef struct  DoctorInfoStruct
    {
    LONG lDoctorID;
    BSTR bsDoctorName;
    INT iDoctorPotence;
    BSTR bsDoctorPassword;
    DATE dtCreateDateTime;
    }	DoctorInfoStruct;

typedef struct  PatientInfoStruct
    {
    BSTR bsPatientUID;
    BSTR bsPatientID;
    BSTR bsPatientName;
    BSTR bsPatientFullName;
    INT iGender;
    DATE dtBirthDate;
    DATE dtRegDateTime;
    INT iPatientAge;
    INT iPatientAgeUnit;
    BOOL bLockFlag;
    BSTR bsPatientComment;
    PATIENT_TYPE enumEmergencyFlag;
    BSTR bsEthnicGroup;
    BSTR bsOtherPatientIDs;
    BSTR bsOtherPatientName;
    BSTR bsOccupation;
    BSTR bsPatientFilePath;
    BOOL bImportedOrNot;
    BOOL bSendFlag;
    BOOL bPrintFlag;
    BSTR bsLastExamRegionAndOrganName;
    BSTR bsLastExamDateTime;
    }	PatientInfoStruct;

typedef struct  StudyInfoStruct
    {
    BSTR bsStudyUID;
    BSTR bsPatientUID;
    INT iStudyID;
    DATE dtStartStudyDateTime;
    BSTR bsReferringPhysicianName;
    DOUBLE dbPatientSize;
    DOUBLE dbPatientWeight;
    BSTR bsStudyDescription;
    BSTR bsPatientHistory;
    BSTR bsStudyImagePath;
    BSTR bsOperatorName;
    BOOL bImportedOrNot;
    BSTR bsInstanceUID;
    MPPS_STATE enumMPPSState;
    BSTR bsAccessionNumber;
    BSTR bsPerformingPhysicianName;
    BOOL bSendFlag;
    BOOL bPrintFlag;
    }	StudyInfoStruct;

typedef struct  SeriesInfoStruct
    {
    BSTR bsSeriesUID;
    BSTR bsStudyUID;
    INT iSeriesID;
    BSTR bsSeriesDescription;
    BSTR bsSeriesFilePath;
    DATE dtCreateDateTime;
    BOOL bImportedOrNot;
    BSTR bsAprRegionName;
    }	SeriesInfoStruct;

typedef struct  AprOrientationStruct
    {
    INT iAprImageLaterality;
    INT iAprPatientPosition;
    }	AprOrientationStruct;

typedef struct  ImageInfoStruct
    {
    BSTR bsImageUID;
    BSTR bsSeriesUID;
    INT iImageID;
    BSTR bsImageFilePath;
    DOUBLE dbKV;
    DOUBLE dbMA;
    DOUBLE dbMS;
    DOUBLE dbMAS;
    INT iFocalSpot;
    DOUBLE dbSID;
    DATE dtImageCreateDateTime;
    INT iExposureType;
    INT iAECField;
    AprOrientationStruct AprOrientation;
    BSTR bsPatientOrientation;
    DOUBLE dbPixelSpacingX;
    DOUBLE dbPixelSpacingY;
    LONG lViewPosition;
    INT iWW;
    INT iWL;
    DOUBLE dbDAP;
    BSTR bsAprOrganUID;
    BSTR bsAprOrganName;
    INT iBodyType;
    ShutterStruct ShutterInfo;
    }	ImageInfoStruct;

typedef struct  PostProcessingInfo
    {
    BSTR bsImageUID;
    BSTR bsSeriesUID;
    BOOL bLogLUT;
    INT iEELevel;
    INT iWW;
    INT iWL;
    INT iRotation;
    BOOL bInverse;
    float fZoomFactor;
    BOOL bShutter;
    INT iOffsetX;
    INT iOffsetY;
    BOOL bOverlay;
    INT iElectroShutter_Left;
    INT iElectroShutter_Right;
    INT iElectroShutter_Top;
    INT iElectroShutter_Bottom;
    BSTR bsProcessedImageFilePath;
    DATE dtProcessDateTime;
    INT iColumns;
    INT iRow;
    INT iBitAllocated;
    INT iBitStored;
    INT iHighBit;
    BOOL bAGC;
    INT iDenoiseLevel;
    INT iCurveType;
    INT iEqualizeLevel;
    BOOL bImgMerage;
    INT iRLFlagType;
    INT iRLFlag_X;
    INT iRLFlag_Y;
    INT iCrop_Left;
    INT iCrop_Top;
    INT iDensityLevel;
    float fLeftWindowMargin;
    float fRightWindowMargin;
    BOOL bTitchFlag;
    }	PostProcessingInfo;

typedef struct  AprIPSettingPara
    {
    BSTR bsIPRegionName;
    BSTR bsIPOrganUID;
    BSTR bsIPOrganName;
    BOOL bAGC;
    BOOL bLogLUT;
    INT iEELevel;
    INT iDenoiseLevel;
    INT iCurveType;
    INT iEqualizeLevel;
    INT iWW;
    INT iWL;
    INT iDensityLevel;
    }	AprIPSettingPara;

typedef 
enum _XRAYSTATUS
    {	enumOn	= 0,
	enumOff	= enumOn + 1,
	enumPrepare	= enumOff + 1
    }	XRAYSTATUS;

typedef struct  ShutterRectStruct
    {
    DOUBLE dXrayLUX;
    DOUBLE dXrayLUY;
    DOUBLE dXrayRUX;
    DOUBLE dXrayRUY;
    DOUBLE dXrayRDX;
    DOUBLE dXrayRDY;
    DOUBLE dXrayLDX;
    DOUBLE dXrayLDY;
    }	ShutterRectStruct;

typedef struct  PBLInfoStruct
    {
    DOUBLE dbSID;
    ShutterStruct ShutterInfo;
    BOOL bAutoTubeTracing;
    DOUBLE dbBeamOffsetV;
    ShutterRectStruct ShutterRect;
    }	PBLInfoStruct;

typedef struct  AprRegionParaStruct
    {
    BSTR bsRegionUID;
    BSTR bsHVRegionUID;
    LONG lRegionID;
    BSTR bsRegionName;
    BSTR bsRegionDescription;
    BSTR bsAuthor;
    }	AprRegionParaStruct;

typedef struct  AprOrganParaStruct
    {
    BSTR bsOrganUID;
    BSTR bsHVOrganUID;
    BSTR bsRegionUID;
    LONG lRegionID;
    LONG lOrganID;
    BSTR bsOrganName;
    INT iShutterFieldSize;
    BOOL bAGC;
    BOOL bLogLUT;
    INT iEELevel;
    INT iDenoiseLevel;
    INT iCurveType;
    INT iEqualizeLevel;
    INT iWW;
    INT iWL;
    AprOrientationStruct AprOrientation;
    INT iViewPosition;
    BSTR bsPatientOrientation;
    INT iDensityLevel;
    float fLeftWindowMargin;
    float fRightWindowMargin;
    BOOL bAutoWindowing;
    float fLogGain;
    INT iSegType;
    INT iAutoCropType;
    float fLogPara1;
    float fLogPara2;
    float fLogPara3;
    BOOL bGeneralOrgan;
    INT iFlipOrientation;
    }	AprOrganParaStruct;

typedef 
enum _REVIEW_TYPE
    {	enumPreview	= 0,
	enumComplete	= enumPreview + 1,
	enumCanceledImage	= enumComplete + 1
    }	REVIEW_TYPE;

typedef 
enum _DICOMINFO_TYPE
    {	enumDicomPatient	= 0,
	enumDicomStudy	= enumDicomPatient + 1
    }	DICOMINFO_TYPE;

typedef struct  EEParaStruct
    {
    INT iEELevel;
    INT iBand;
    float fCF;
    float fP;
    float fG;
    float fC0;
    float fGain;
    float fContrast;
    }	EEParaStruct;

typedef struct  DenoiseParaStruct
    {
    INT iDenoiseLevel;
    INT iBand;
    float fMdc;
    float fDeltaM;
    float fDmin;
    float fMAc;
    float fDeltaA;
    float fAmin;
    }	DenoiseParaStruct;



extern RPC_IF_HANDLE __MIDL_itf_PATestClientExt_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_PATestClientExt_0000_v0_0_s_ifspec;

#ifndef __IDBPIM_INTERFACE_DEFINED__
#define __IDBPIM_INTERFACE_DEFINED__

/* interface IDBPIM */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IDBPIM;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("A6FE9509-A685-4002-B40C-F40CD4B472DA")
    IDBPIM : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE AddPatientInfo( 
            /* [in] */ PatientInfoStruct patInfo,
            /* [out] */ BSTR __RPC_FAR *pbsPatientUID) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ImportPatientInfo( 
            /* [in] */ PatientInfoStruct patInfo) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ModifyPatientInfo( 
            /* [in] */ PatientInfoStruct patInfo) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetPatientInfo( 
            /* [in] */ BSTR bsPatientUID,
            /* [out] */ PatientInfoStruct __RPC_FAR *pPatientInfoStruct) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetPatientList( 
            /* [in] */ UINT uiInNum,
            /* [out] */ UINT __RPC_FAR *puiOutCount,
            /* [size_is][size_is][out] */ PatientInfoStruct __RPC_FAR *__RPC_FAR *ppInfo) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE DeletePatientInfo( 
            /* [in] */ BSTR bsPatientUID) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetPatientInfoByID( 
            /* [in] */ BSTR bsPatientID,
            /* [out] */ PatientInfoStruct __RPC_FAR *pPatientInfoStruct) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetComplexQueryResult( 
            /* [in] */ UINT uiFieldNum,
            /* [size_is][in] */ ComplexSearchStruct __RPC_FAR *scSearchStruct,
            /* [out] */ UINT __RPC_FAR *puiCount,
            /* [size_is][size_is][out] */ PatientInfoStruct __RPC_FAR *__RPC_FAR *ppSearchInfo) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE IsPatientExist( 
            /* [in] */ BSTR bsPatientUID,
            /* [out] */ BOOL __RPC_FAR *pbExist) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE IsPatientIDExist( 
            /* [in] */ BSTR lPatientID,
            /* [out] */ BOOL __RPC_FAR *pbExist) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE LockPatient( 
            /* [in] */ BSTR bsPatientUID) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE UnlockPatient( 
            /* [in] */ BSTR bsPatientUID) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE IsPatientLocked( 
            /* [in] */ BSTR bsPatientUID,
            /* [out] */ BOOL __RPC_FAR *pbLocked) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE AddStudyInfo( 
            /* [in] */ StudyInfoStruct studyInfo,
            /* [out] */ BSTR __RPC_FAR *pbsStudyUID,
            /* [out] */ INT __RPC_FAR *piStudyID) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ImportStudyInfo( 
            /* [in] */ StudyInfoStruct studyInfo) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ModifyStudyInfo( 
            /* [in] */ StudyInfoStruct studyInfo) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetStudyInfo( 
            /* [in] */ BSTR bsStudyUID,
            /* [out] */ StudyInfoStruct __RPC_FAR *pStudyInfo) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetStudyListByPatientUID( 
            /* [in] */ BSTR bsPatientUID,
            /* [out] */ long __RPC_FAR *lpCount,
            /* [size_is][size_is][out] */ StudyInfoStruct __RPC_FAR *__RPC_FAR *ppInfo) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetStudyUIDByInstanceUID( 
            /* [in] */ BSTR bsStudyInstanceUID,
            /* [out] */ BSTR __RPC_FAR *pbsStudyUID) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE DeleteStudyInfo( 
            /* [in] */ BSTR bsStudyUID) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetMPPSState( 
            /* [in] */ BSTR bsStudyUID,
            /* [in] */ MPPS_STATE enumState) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetMPPSState( 
            /* [in] */ BSTR bsStudyUID,
            /* [out] */ MPPS_STATE __RPC_FAR *penumState) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE IsStudyExist( 
            /* [in] */ BSTR bsStudyUID,
            /* [out] */ BOOL __RPC_FAR *pbExist) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE IsInstanceUIDExist( 
            /* [in] */ BSTR bsInstanceUID,
            /* [out] */ BOOL __RPC_FAR *pbExist) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE AddSeriesInfo( 
            /* [in] */ SeriesInfoStruct sSeriesInfo,
            /* [out] */ BSTR __RPC_FAR *pbsSeriesUID) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ImportSeriesInfo( 
            /* [in] */ SeriesInfoStruct sSeriesInfo) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ModifySeriesInfo( 
            /* [in] */ SeriesInfoStruct scSeriesInfo) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetSeriesInfo( 
            /* [in] */ BSTR bsSeriesUID,
            /* [out] */ SeriesInfoStruct __RPC_FAR *pSeriesInfo) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetSeriesListByStudyUID( 
            /* [in] */ BSTR bsStudyUID,
            /* [out] */ long __RPC_FAR *lpCount,
            /* [size_is][size_is][out] */ SeriesInfoStruct __RPC_FAR *__RPC_FAR *ppInfo) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE DeleteSeriesInfo( 
            /* [in] */ BSTR bsSeriesUID) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE IsSeriesExist( 
            /* [in] */ BSTR bsSeriesUID,
            /* [out] */ BOOL __RPC_FAR *pbExist) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetNextSeriesID( 
            /* [in] */ BSTR bsStudyUID,
            /* [out] */ INT __RPC_FAR *piSeriesID) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE AddImageInfo( 
            /* [in] */ ImageInfoStruct scImageInfo,
            /* [out] */ BSTR __RPC_FAR *pbsImageUID) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ImportImageInfo( 
            /* [in] */ ImageInfoStruct scImageInfo) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ModifyImageInfo( 
            /* [in] */ ImageInfoStruct scImageInfo) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetImageInfo( 
            /* [in] */ BSTR bsImageUID,
            /* [out] */ ImageInfoStruct __RPC_FAR *pImageInfo) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetImageListBySeriesUID( 
            /* [in] */ BSTR bsSeriesUID,
            /* [out] */ long __RPC_FAR *lpCount,
            /* [size_is][size_is][out] */ ImageInfoStruct __RPC_FAR *__RPC_FAR *ppInfo) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE DeleteImageInfo( 
            /* [in] */ BSTR bsImageUID) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE IsImageExist( 
            /* [in] */ BSTR bsImageUID,
            /* [out] */ BOOL __RPC_FAR *pbExist) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetNextImageID( 
            /* [in] */ BSTR bsSeriesUID,
            /* [out] */ INT __RPC_FAR *piImageID) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetPostProcessingInfo( 
            /* [in] */ PostProcessingInfo scPostProcessingInfo) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetPostProcessingInfo( 
            /* [in] */ BSTR bsImageUID,
            /* [out] */ PostProcessingInfo __RPC_FAR *pPostProcessingInfo) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IDBPIMVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IDBPIM __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IDBPIM __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IDBPIM __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AddPatientInfo )( 
            IDBPIM __RPC_FAR * This,
            /* [in] */ PatientInfoStruct patInfo,
            /* [out] */ BSTR __RPC_FAR *pbsPatientUID);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ImportPatientInfo )( 
            IDBPIM __RPC_FAR * This,
            /* [in] */ PatientInfoStruct patInfo);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ModifyPatientInfo )( 
            IDBPIM __RPC_FAR * This,
            /* [in] */ PatientInfoStruct patInfo);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetPatientInfo )( 
            IDBPIM __RPC_FAR * This,
            /* [in] */ BSTR bsPatientUID,
            /* [out] */ PatientInfoStruct __RPC_FAR *pPatientInfoStruct);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetPatientList )( 
            IDBPIM __RPC_FAR * This,
            /* [in] */ UINT uiInNum,
            /* [out] */ UINT __RPC_FAR *puiOutCount,
            /* [size_is][size_is][out] */ PatientInfoStruct __RPC_FAR *__RPC_FAR *ppInfo);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DeletePatientInfo )( 
            IDBPIM __RPC_FAR * This,
            /* [in] */ BSTR bsPatientUID);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetPatientInfoByID )( 
            IDBPIM __RPC_FAR * This,
            /* [in] */ BSTR bsPatientID,
            /* [out] */ PatientInfoStruct __RPC_FAR *pPatientInfoStruct);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetComplexQueryResult )( 
            IDBPIM __RPC_FAR * This,
            /* [in] */ UINT uiFieldNum,
            /* [size_is][in] */ ComplexSearchStruct __RPC_FAR *scSearchStruct,
            /* [out] */ UINT __RPC_FAR *puiCount,
            /* [size_is][size_is][out] */ PatientInfoStruct __RPC_FAR *__RPC_FAR *ppSearchInfo);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *IsPatientExist )( 
            IDBPIM __RPC_FAR * This,
            /* [in] */ BSTR bsPatientUID,
            /* [out] */ BOOL __RPC_FAR *pbExist);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *IsPatientIDExist )( 
            IDBPIM __RPC_FAR * This,
            /* [in] */ BSTR lPatientID,
            /* [out] */ BOOL __RPC_FAR *pbExist);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *LockPatient )( 
            IDBPIM __RPC_FAR * This,
            /* [in] */ BSTR bsPatientUID);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *UnlockPatient )( 
            IDBPIM __RPC_FAR * This,
            /* [in] */ BSTR bsPatientUID);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *IsPatientLocked )( 
            IDBPIM __RPC_FAR * This,
            /* [in] */ BSTR bsPatientUID,
            /* [out] */ BOOL __RPC_FAR *pbLocked);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AddStudyInfo )( 
            IDBPIM __RPC_FAR * This,
            /* [in] */ StudyInfoStruct studyInfo,
            /* [out] */ BSTR __RPC_FAR *pbsStudyUID,
            /* [out] */ INT __RPC_FAR *piStudyID);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ImportStudyInfo )( 
            IDBPIM __RPC_FAR * This,
            /* [in] */ StudyInfoStruct studyInfo);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ModifyStudyInfo )( 
            IDBPIM __RPC_FAR * This,
            /* [in] */ StudyInfoStruct studyInfo);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetStudyInfo )( 
            IDBPIM __RPC_FAR * This,
            /* [in] */ BSTR bsStudyUID,
            /* [out] */ StudyInfoStruct __RPC_FAR *pStudyInfo);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetStudyListByPatientUID )( 
            IDBPIM __RPC_FAR * This,
            /* [in] */ BSTR bsPatientUID,
            /* [out] */ long __RPC_FAR *lpCount,
            /* [size_is][size_is][out] */ StudyInfoStruct __RPC_FAR *__RPC_FAR *ppInfo);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetStudyUIDByInstanceUID )( 
            IDBPIM __RPC_FAR * This,
            /* [in] */ BSTR bsStudyInstanceUID,
            /* [out] */ BSTR __RPC_FAR *pbsStudyUID);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DeleteStudyInfo )( 
            IDBPIM __RPC_FAR * This,
            /* [in] */ BSTR bsStudyUID);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetMPPSState )( 
            IDBPIM __RPC_FAR * This,
            /* [in] */ BSTR bsStudyUID,
            /* [in] */ MPPS_STATE enumState);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetMPPSState )( 
            IDBPIM __RPC_FAR * This,
            /* [in] */ BSTR bsStudyUID,
            /* [out] */ MPPS_STATE __RPC_FAR *penumState);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *IsStudyExist )( 
            IDBPIM __RPC_FAR * This,
            /* [in] */ BSTR bsStudyUID,
            /* [out] */ BOOL __RPC_FAR *pbExist);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *IsInstanceUIDExist )( 
            IDBPIM __RPC_FAR * This,
            /* [in] */ BSTR bsInstanceUID,
            /* [out] */ BOOL __RPC_FAR *pbExist);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AddSeriesInfo )( 
            IDBPIM __RPC_FAR * This,
            /* [in] */ SeriesInfoStruct sSeriesInfo,
            /* [out] */ BSTR __RPC_FAR *pbsSeriesUID);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ImportSeriesInfo )( 
            IDBPIM __RPC_FAR * This,
            /* [in] */ SeriesInfoStruct sSeriesInfo);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ModifySeriesInfo )( 
            IDBPIM __RPC_FAR * This,
            /* [in] */ SeriesInfoStruct scSeriesInfo);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetSeriesInfo )( 
            IDBPIM __RPC_FAR * This,
            /* [in] */ BSTR bsSeriesUID,
            /* [out] */ SeriesInfoStruct __RPC_FAR *pSeriesInfo);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetSeriesListByStudyUID )( 
            IDBPIM __RPC_FAR * This,
            /* [in] */ BSTR bsStudyUID,
            /* [out] */ long __RPC_FAR *lpCount,
            /* [size_is][size_is][out] */ SeriesInfoStruct __RPC_FAR *__RPC_FAR *ppInfo);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DeleteSeriesInfo )( 
            IDBPIM __RPC_FAR * This,
            /* [in] */ BSTR bsSeriesUID);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *IsSeriesExist )( 
            IDBPIM __RPC_FAR * This,
            /* [in] */ BSTR bsSeriesUID,
            /* [out] */ BOOL __RPC_FAR *pbExist);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetNextSeriesID )( 
            IDBPIM __RPC_FAR * This,
            /* [in] */ BSTR bsStudyUID,
            /* [out] */ INT __RPC_FAR *piSeriesID);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AddImageInfo )( 
            IDBPIM __RPC_FAR * This,
            /* [in] */ ImageInfoStruct scImageInfo,
            /* [out] */ BSTR __RPC_FAR *pbsImageUID);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ImportImageInfo )( 
            IDBPIM __RPC_FAR * This,
            /* [in] */ ImageInfoStruct scImageInfo);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ModifyImageInfo )( 
            IDBPIM __RPC_FAR * This,
            /* [in] */ ImageInfoStruct scImageInfo);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetImageInfo )( 
            IDBPIM __RPC_FAR * This,
            /* [in] */ BSTR bsImageUID,
            /* [out] */ ImageInfoStruct __RPC_FAR *pImageInfo);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetImageListBySeriesUID )( 
            IDBPIM __RPC_FAR * This,
            /* [in] */ BSTR bsSeriesUID,
            /* [out] */ long __RPC_FAR *lpCount,
            /* [size_is][size_is][out] */ ImageInfoStruct __RPC_FAR *__RPC_FAR *ppInfo);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DeleteImageInfo )( 
            IDBPIM __RPC_FAR * This,
            /* [in] */ BSTR bsImageUID);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *IsImageExist )( 
            IDBPIM __RPC_FAR * This,
            /* [in] */ BSTR bsImageUID,
            /* [out] */ BOOL __RPC_FAR *pbExist);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetNextImageID )( 
            IDBPIM __RPC_FAR * This,
            /* [in] */ BSTR bsSeriesUID,
            /* [out] */ INT __RPC_FAR *piImageID);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetPostProcessingInfo )( 
            IDBPIM __RPC_FAR * This,
            /* [in] */ PostProcessingInfo scPostProcessingInfo);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetPostProcessingInfo )( 
            IDBPIM __RPC_FAR * This,
            /* [in] */ BSTR bsImageUID,
            /* [out] */ PostProcessingInfo __RPC_FAR *pPostProcessingInfo);
        
        END_INTERFACE
    } IDBPIMVtbl;

    interface IDBPIM
    {
        CONST_VTBL struct IDBPIMVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDBPIM_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDBPIM_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDBPIM_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDBPIM_AddPatientInfo(This,patInfo,pbsPatientUID)	\
    (This)->lpVtbl -> AddPatientInfo(This,patInfo,pbsPatientUID)

#define IDBPIM_ImportPatientInfo(This,patInfo)	\
    (This)->lpVtbl -> ImportPatientInfo(This,patInfo)

#define IDBPIM_ModifyPatientInfo(This,patInfo)	\
    (This)->lpVtbl -> ModifyPatientInfo(This,patInfo)

#define IDBPIM_GetPatientInfo(This,bsPatientUID,pPatientInfoStruct)	\
    (This)->lpVtbl -> GetPatientInfo(This,bsPatientUID,pPatientInfoStruct)

#define IDBPIM_GetPatientList(This,uiInNum,puiOutCount,ppInfo)	\
    (This)->lpVtbl -> GetPatientList(This,uiInNum,puiOutCount,ppInfo)

#define IDBPIM_DeletePatientInfo(This,bsPatientUID)	\
    (This)->lpVtbl -> DeletePatientInfo(This,bsPatientUID)

#define IDBPIM_GetPatientInfoByID(This,bsPatientID,pPatientInfoStruct)	\
    (This)->lpVtbl -> GetPatientInfoByID(This,bsPatientID,pPatientInfoStruct)

#define IDBPIM_GetComplexQueryResult(This,uiFieldNum,scSearchStruct,puiCount,ppSearchInfo)	\
    (This)->lpVtbl -> GetComplexQueryResult(This,uiFieldNum,scSearchStruct,puiCount,ppSearchInfo)

#define IDBPIM_IsPatientExist(This,bsPatientUID,pbExist)	\
    (This)->lpVtbl -> IsPatientExist(This,bsPatientUID,pbExist)

#define IDBPIM_IsPatientIDExist(This,lPatientID,pbExist)	\
    (This)->lpVtbl -> IsPatientIDExist(This,lPatientID,pbExist)

#define IDBPIM_LockPatient(This,bsPatientUID)	\
    (This)->lpVtbl -> LockPatient(This,bsPatientUID)

#define IDBPIM_UnlockPatient(This,bsPatientUID)	\
    (This)->lpVtbl -> UnlockPatient(This,bsPatientUID)

#define IDBPIM_IsPatientLocked(This,bsPatientUID,pbLocked)	\
    (This)->lpVtbl -> IsPatientLocked(This,bsPatientUID,pbLocked)

#define IDBPIM_AddStudyInfo(This,studyInfo,pbsStudyUID,piStudyID)	\
    (This)->lpVtbl -> AddStudyInfo(This,studyInfo,pbsStudyUID,piStudyID)

#define IDBPIM_ImportStudyInfo(This,studyInfo)	\
    (This)->lpVtbl -> ImportStudyInfo(This,studyInfo)

#define IDBPIM_ModifyStudyInfo(This,studyInfo)	\
    (This)->lpVtbl -> ModifyStudyInfo(This,studyInfo)

#define IDBPIM_GetStudyInfo(This,bsStudyUID,pStudyInfo)	\
    (This)->lpVtbl -> GetStudyInfo(This,bsStudyUID,pStudyInfo)

#define IDBPIM_GetStudyListByPatientUID(This,bsPatientUID,lpCount,ppInfo)	\
    (This)->lpVtbl -> GetStudyListByPatientUID(This,bsPatientUID,lpCount,ppInfo)

#define IDBPIM_GetStudyUIDByInstanceUID(This,bsStudyInstanceUID,pbsStudyUID)	\
    (This)->lpVtbl -> GetStudyUIDByInstanceUID(This,bsStudyInstanceUID,pbsStudyUID)

#define IDBPIM_DeleteStudyInfo(This,bsStudyUID)	\
    (This)->lpVtbl -> DeleteStudyInfo(This,bsStudyUID)

#define IDBPIM_SetMPPSState(This,bsStudyUID,enumState)	\
    (This)->lpVtbl -> SetMPPSState(This,bsStudyUID,enumState)

#define IDBPIM_GetMPPSState(This,bsStudyUID,penumState)	\
    (This)->lpVtbl -> GetMPPSState(This,bsStudyUID,penumState)

#define IDBPIM_IsStudyExist(This,bsStudyUID,pbExist)	\
    (This)->lpVtbl -> IsStudyExist(This,bsStudyUID,pbExist)

#define IDBPIM_IsInstanceUIDExist(This,bsInstanceUID,pbExist)	\
    (This)->lpVtbl -> IsInstanceUIDExist(This,bsInstanceUID,pbExist)

#define IDBPIM_AddSeriesInfo(This,sSeriesInfo,pbsSeriesUID)	\
    (This)->lpVtbl -> AddSeriesInfo(This,sSeriesInfo,pbsSeriesUID)

#define IDBPIM_ImportSeriesInfo(This,sSeriesInfo)	\
    (This)->lpVtbl -> ImportSeriesInfo(This,sSeriesInfo)

#define IDBPIM_ModifySeriesInfo(This,scSeriesInfo)	\
    (This)->lpVtbl -> ModifySeriesInfo(This,scSeriesInfo)

#define IDBPIM_GetSeriesInfo(This,bsSeriesUID,pSeriesInfo)	\
    (This)->lpVtbl -> GetSeriesInfo(This,bsSeriesUID,pSeriesInfo)

#define IDBPIM_GetSeriesListByStudyUID(This,bsStudyUID,lpCount,ppInfo)	\
    (This)->lpVtbl -> GetSeriesListByStudyUID(This,bsStudyUID,lpCount,ppInfo)

#define IDBPIM_DeleteSeriesInfo(This,bsSeriesUID)	\
    (This)->lpVtbl -> DeleteSeriesInfo(This,bsSeriesUID)

#define IDBPIM_IsSeriesExist(This,bsSeriesUID,pbExist)	\
    (This)->lpVtbl -> IsSeriesExist(This,bsSeriesUID,pbExist)

#define IDBPIM_GetNextSeriesID(This,bsStudyUID,piSeriesID)	\
    (This)->lpVtbl -> GetNextSeriesID(This,bsStudyUID,piSeriesID)

#define IDBPIM_AddImageInfo(This,scImageInfo,pbsImageUID)	\
    (This)->lpVtbl -> AddImageInfo(This,scImageInfo,pbsImageUID)

#define IDBPIM_ImportImageInfo(This,scImageInfo)	\
    (This)->lpVtbl -> ImportImageInfo(This,scImageInfo)

#define IDBPIM_ModifyImageInfo(This,scImageInfo)	\
    (This)->lpVtbl -> ModifyImageInfo(This,scImageInfo)

#define IDBPIM_GetImageInfo(This,bsImageUID,pImageInfo)	\
    (This)->lpVtbl -> GetImageInfo(This,bsImageUID,pImageInfo)

#define IDBPIM_GetImageListBySeriesUID(This,bsSeriesUID,lpCount,ppInfo)	\
    (This)->lpVtbl -> GetImageListBySeriesUID(This,bsSeriesUID,lpCount,ppInfo)

#define IDBPIM_DeleteImageInfo(This,bsImageUID)	\
    (This)->lpVtbl -> DeleteImageInfo(This,bsImageUID)

#define IDBPIM_IsImageExist(This,bsImageUID,pbExist)	\
    (This)->lpVtbl -> IsImageExist(This,bsImageUID,pbExist)

#define IDBPIM_GetNextImageID(This,bsSeriesUID,piImageID)	\
    (This)->lpVtbl -> GetNextImageID(This,bsSeriesUID,piImageID)

#define IDBPIM_SetPostProcessingInfo(This,scPostProcessingInfo)	\
    (This)->lpVtbl -> SetPostProcessingInfo(This,scPostProcessingInfo)

#define IDBPIM_GetPostProcessingInfo(This,bsImageUID,pPostProcessingInfo)	\
    (This)->lpVtbl -> GetPostProcessingInfo(This,bsImageUID,pPostProcessingInfo)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE IDBPIM_AddPatientInfo_Proxy( 
    IDBPIM __RPC_FAR * This,
    /* [in] */ PatientInfoStruct patInfo,
    /* [out] */ BSTR __RPC_FAR *pbsPatientUID);


void __RPC_STUB IDBPIM_AddPatientInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IDBPIM_ImportPatientInfo_Proxy( 
    IDBPIM __RPC_FAR * This,
    /* [in] */ PatientInfoStruct patInfo);


void __RPC_STUB IDBPIM_ImportPatientInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IDBPIM_ModifyPatientInfo_Proxy( 
    IDBPIM __RPC_FAR * This,
    /* [in] */ PatientInfoStruct patInfo);


void __RPC_STUB IDBPIM_ModifyPatientInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IDBPIM_GetPatientInfo_Proxy( 
    IDBPIM __RPC_FAR * This,
    /* [in] */ BSTR bsPatientUID,
    /* [out] */ PatientInfoStruct __RPC_FAR *pPatientInfoStruct);


void __RPC_STUB IDBPIM_GetPatientInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IDBPIM_GetPatientList_Proxy( 
    IDBPIM __RPC_FAR * This,
    /* [in] */ UINT uiInNum,
    /* [out] */ UINT __RPC_FAR *puiOutCount,
    /* [size_is][size_is][out] */ PatientInfoStruct __RPC_FAR *__RPC_FAR *ppInfo);


void __RPC_STUB IDBPIM_GetPatientList_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IDBPIM_DeletePatientInfo_Proxy( 
    IDBPIM __RPC_FAR * This,
    /* [in] */ BSTR bsPatientUID);


void __RPC_STUB IDBPIM_DeletePatientInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IDBPIM_GetPatientInfoByID_Proxy( 
    IDBPIM __RPC_FAR * This,
    /* [in] */ BSTR bsPatientID,
    /* [out] */ PatientInfoStruct __RPC_FAR *pPatientInfoStruct);


void __RPC_STUB IDBPIM_GetPatientInfoByID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IDBPIM_GetComplexQueryResult_Proxy( 
    IDBPIM __RPC_FAR * This,
    /* [in] */ UINT uiFieldNum,
    /* [size_is][in] */ ComplexSearchStruct __RPC_FAR *scSearchStruct,
    /* [out] */ UINT __RPC_FAR *puiCount,
    /* [size_is][size_is][out] */ PatientInfoStruct __RPC_FAR *__RPC_FAR *ppSearchInfo);


void __RPC_STUB IDBPIM_GetComplexQueryResult_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IDBPIM_IsPatientExist_Proxy( 
    IDBPIM __RPC_FAR * This,
    /* [in] */ BSTR bsPatientUID,
    /* [out] */ BOOL __RPC_FAR *pbExist);


void __RPC_STUB IDBPIM_IsPatientExist_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IDBPIM_IsPatientIDExist_Proxy( 
    IDBPIM __RPC_FAR * This,
    /* [in] */ BSTR lPatientID,
    /* [out] */ BOOL __RPC_FAR *pbExist);


void __RPC_STUB IDBPIM_IsPatientIDExist_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IDBPIM_LockPatient_Proxy( 
    IDBPIM __RPC_FAR * This,
    /* [in] */ BSTR bsPatientUID);


void __RPC_STUB IDBPIM_LockPatient_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IDBPIM_UnlockPatient_Proxy( 
    IDBPIM __RPC_FAR * This,
    /* [in] */ BSTR bsPatientUID);


void __RPC_STUB IDBPIM_UnlockPatient_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IDBPIM_IsPatientLocked_Proxy( 
    IDBPIM __RPC_FAR * This,
    /* [in] */ BSTR bsPatientUID,
    /* [out] */ BOOL __RPC_FAR *pbLocked);


void __RPC_STUB IDBPIM_IsPatientLocked_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IDBPIM_AddStudyInfo_Proxy( 
    IDBPIM __RPC_FAR * This,
    /* [in] */ StudyInfoStruct studyInfo,
    /* [out] */ BSTR __RPC_FAR *pbsStudyUID,
    /* [out] */ INT __RPC_FAR *piStudyID);


void __RPC_STUB IDBPIM_AddStudyInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IDBPIM_ImportStudyInfo_Proxy( 
    IDBPIM __RPC_FAR * This,
    /* [in] */ StudyInfoStruct studyInfo);


void __RPC_STUB IDBPIM_ImportStudyInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IDBPIM_ModifyStudyInfo_Proxy( 
    IDBPIM __RPC_FAR * This,
    /* [in] */ StudyInfoStruct studyInfo);


void __RPC_STUB IDBPIM_ModifyStudyInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IDBPIM_GetStudyInfo_Proxy( 
    IDBPIM __RPC_FAR * This,
    /* [in] */ BSTR bsStudyUID,
    /* [out] */ StudyInfoStruct __RPC_FAR *pStudyInfo);


void __RPC_STUB IDBPIM_GetStudyInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IDBPIM_GetStudyListByPatientUID_Proxy( 
    IDBPIM __RPC_FAR * This,
    /* [in] */ BSTR bsPatientUID,
    /* [out] */ long __RPC_FAR *lpCount,
    /* [size_is][size_is][out] */ StudyInfoStruct __RPC_FAR *__RPC_FAR *ppInfo);


void __RPC_STUB IDBPIM_GetStudyListByPatientUID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IDBPIM_GetStudyUIDByInstanceUID_Proxy( 
    IDBPIM __RPC_FAR * This,
    /* [in] */ BSTR bsStudyInstanceUID,
    /* [out] */ BSTR __RPC_FAR *pbsStudyUID);


void __RPC_STUB IDBPIM_GetStudyUIDByInstanceUID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IDBPIM_DeleteStudyInfo_Proxy( 
    IDBPIM __RPC_FAR * This,
    /* [in] */ BSTR bsStudyUID);


void __RPC_STUB IDBPIM_DeleteStudyInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IDBPIM_SetMPPSState_Proxy( 
    IDBPIM __RPC_FAR * This,
    /* [in] */ BSTR bsStudyUID,
    /* [in] */ MPPS_STATE enumState);


void __RPC_STUB IDBPIM_SetMPPSState_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IDBPIM_GetMPPSState_Proxy( 
    IDBPIM __RPC_FAR * This,
    /* [in] */ BSTR bsStudyUID,
    /* [out] */ MPPS_STATE __RPC_FAR *penumState);


void __RPC_STUB IDBPIM_GetMPPSState_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IDBPIM_IsStudyExist_Proxy( 
    IDBPIM __RPC_FAR * This,
    /* [in] */ BSTR bsStudyUID,
    /* [out] */ BOOL __RPC_FAR *pbExist);


void __RPC_STUB IDBPIM_IsStudyExist_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IDBPIM_IsInstanceUIDExist_Proxy( 
    IDBPIM __RPC_FAR * This,
    /* [in] */ BSTR bsInstanceUID,
    /* [out] */ BOOL __RPC_FAR *pbExist);


void __RPC_STUB IDBPIM_IsInstanceUIDExist_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IDBPIM_AddSeriesInfo_Proxy( 
    IDBPIM __RPC_FAR * This,
    /* [in] */ SeriesInfoStruct sSeriesInfo,
    /* [out] */ BSTR __RPC_FAR *pbsSeriesUID);


void __RPC_STUB IDBPIM_AddSeriesInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IDBPIM_ImportSeriesInfo_Proxy( 
    IDBPIM __RPC_FAR * This,
    /* [in] */ SeriesInfoStruct sSeriesInfo);


void __RPC_STUB IDBPIM_ImportSeriesInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IDBPIM_ModifySeriesInfo_Proxy( 
    IDBPIM __RPC_FAR * This,
    /* [in] */ SeriesInfoStruct scSeriesInfo);


void __RPC_STUB IDBPIM_ModifySeriesInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IDBPIM_GetSeriesInfo_Proxy( 
    IDBPIM __RPC_FAR * This,
    /* [in] */ BSTR bsSeriesUID,
    /* [out] */ SeriesInfoStruct __RPC_FAR *pSeriesInfo);


void __RPC_STUB IDBPIM_GetSeriesInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IDBPIM_GetSeriesListByStudyUID_Proxy( 
    IDBPIM __RPC_FAR * This,
    /* [in] */ BSTR bsStudyUID,
    /* [out] */ long __RPC_FAR *lpCount,
    /* [size_is][size_is][out] */ SeriesInfoStruct __RPC_FAR *__RPC_FAR *ppInfo);


void __RPC_STUB IDBPIM_GetSeriesListByStudyUID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IDBPIM_DeleteSeriesInfo_Proxy( 
    IDBPIM __RPC_FAR * This,
    /* [in] */ BSTR bsSeriesUID);


void __RPC_STUB IDBPIM_DeleteSeriesInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IDBPIM_IsSeriesExist_Proxy( 
    IDBPIM __RPC_FAR * This,
    /* [in] */ BSTR bsSeriesUID,
    /* [out] */ BOOL __RPC_FAR *pbExist);


void __RPC_STUB IDBPIM_IsSeriesExist_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IDBPIM_GetNextSeriesID_Proxy( 
    IDBPIM __RPC_FAR * This,
    /* [in] */ BSTR bsStudyUID,
    /* [out] */ INT __RPC_FAR *piSeriesID);


void __RPC_STUB IDBPIM_GetNextSeriesID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IDBPIM_AddImageInfo_Proxy( 
    IDBPIM __RPC_FAR * This,
    /* [in] */ ImageInfoStruct scImageInfo,
    /* [out] */ BSTR __RPC_FAR *pbsImageUID);


void __RPC_STUB IDBPIM_AddImageInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IDBPIM_ImportImageInfo_Proxy( 
    IDBPIM __RPC_FAR * This,
    /* [in] */ ImageInfoStruct scImageInfo);


void __RPC_STUB IDBPIM_ImportImageInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IDBPIM_ModifyImageInfo_Proxy( 
    IDBPIM __RPC_FAR * This,
    /* [in] */ ImageInfoStruct scImageInfo);


void __RPC_STUB IDBPIM_ModifyImageInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IDBPIM_GetImageInfo_Proxy( 
    IDBPIM __RPC_FAR * This,
    /* [in] */ BSTR bsImageUID,
    /* [out] */ ImageInfoStruct __RPC_FAR *pImageInfo);


void __RPC_STUB IDBPIM_GetImageInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IDBPIM_GetImageListBySeriesUID_Proxy( 
    IDBPIM __RPC_FAR * This,
    /* [in] */ BSTR bsSeriesUID,
    /* [out] */ long __RPC_FAR *lpCount,
    /* [size_is][size_is][out] */ ImageInfoStruct __RPC_FAR *__RPC_FAR *ppInfo);


void __RPC_STUB IDBPIM_GetImageListBySeriesUID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IDBPIM_DeleteImageInfo_Proxy( 
    IDBPIM __RPC_FAR * This,
    /* [in] */ BSTR bsImageUID);


void __RPC_STUB IDBPIM_DeleteImageInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IDBPIM_IsImageExist_Proxy( 
    IDBPIM __RPC_FAR * This,
    /* [in] */ BSTR bsImageUID,
    /* [out] */ BOOL __RPC_FAR *pbExist);


void __RPC_STUB IDBPIM_IsImageExist_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IDBPIM_GetNextImageID_Proxy( 
    IDBPIM __RPC_FAR * This,
    /* [in] */ BSTR bsSeriesUID,
    /* [out] */ INT __RPC_FAR *piImageID);


void __RPC_STUB IDBPIM_GetNextImageID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IDBPIM_SetPostProcessingInfo_Proxy( 
    IDBPIM __RPC_FAR * This,
    /* [in] */ PostProcessingInfo scPostProcessingInfo);


void __RPC_STUB IDBPIM_SetPostProcessingInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IDBPIM_GetPostProcessingInfo_Proxy( 
    IDBPIM __RPC_FAR * This,
    /* [in] */ BSTR bsImageUID,
    /* [out] */ PostProcessingInfo __RPC_FAR *pPostProcessingInfo);


void __RPC_STUB IDBPIM_GetPostProcessingInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IDBPIM_INTERFACE_DEFINED__ */


#ifndef __IDBConfig_INTERFACE_DEFINED__
#define __IDBConfig_INTERFACE_DEFINED__

/* interface IDBConfig */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IDBConfig;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("4C60238F-73D8-49CF-B213-A40D283A5013")
    IDBConfig : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetConfigInfo( 
            /* [in] */ ConfigInfoStruct ConfigInfo) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetConfigInfo( 
            /* [out] */ ConfigInfoStruct __RPC_FAR *pConfigInfo) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetDoctorInfo( 
            /* [in] */ DoctorInfoStruct scDoctorInfo) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetDoctorList( 
            /* [out] */ long __RPC_FAR *lpCount,
            /* [size_is][size_is][out] */ DoctorInfoStruct __RPC_FAR *__RPC_FAR *ppDoctorInfo) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE DelDoctorInfo( 
            /* [in] */ long lDoctorID) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetDoctorPassword( 
            /* [in] */ long lDoctorID,
            /* [in] */ BSTR bsPassword) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE AddDoctorInfo( 
            /* [in] */ DoctorInfoStruct scDoctorInfo,
            /* [out] */ long __RPC_FAR *lDoctorID) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IDBConfigVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IDBConfig __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IDBConfig __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IDBConfig __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetConfigInfo )( 
            IDBConfig __RPC_FAR * This,
            /* [in] */ ConfigInfoStruct ConfigInfo);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetConfigInfo )( 
            IDBConfig __RPC_FAR * This,
            /* [out] */ ConfigInfoStruct __RPC_FAR *pConfigInfo);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetDoctorInfo )( 
            IDBConfig __RPC_FAR * This,
            /* [in] */ DoctorInfoStruct scDoctorInfo);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetDoctorList )( 
            IDBConfig __RPC_FAR * This,
            /* [out] */ long __RPC_FAR *lpCount,
            /* [size_is][size_is][out] */ DoctorInfoStruct __RPC_FAR *__RPC_FAR *ppDoctorInfo);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DelDoctorInfo )( 
            IDBConfig __RPC_FAR * This,
            /* [in] */ long lDoctorID);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetDoctorPassword )( 
            IDBConfig __RPC_FAR * This,
            /* [in] */ long lDoctorID,
            /* [in] */ BSTR bsPassword);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AddDoctorInfo )( 
            IDBConfig __RPC_FAR * This,
            /* [in] */ DoctorInfoStruct scDoctorInfo,
            /* [out] */ long __RPC_FAR *lDoctorID);
        
        END_INTERFACE
    } IDBConfigVtbl;

    interface IDBConfig
    {
        CONST_VTBL struct IDBConfigVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDBConfig_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDBConfig_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDBConfig_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDBConfig_SetConfigInfo(This,ConfigInfo)	\
    (This)->lpVtbl -> SetConfigInfo(This,ConfigInfo)

#define IDBConfig_GetConfigInfo(This,pConfigInfo)	\
    (This)->lpVtbl -> GetConfigInfo(This,pConfigInfo)

#define IDBConfig_SetDoctorInfo(This,scDoctorInfo)	\
    (This)->lpVtbl -> SetDoctorInfo(This,scDoctorInfo)

#define IDBConfig_GetDoctorList(This,lpCount,ppDoctorInfo)	\
    (This)->lpVtbl -> GetDoctorList(This,lpCount,ppDoctorInfo)

#define IDBConfig_DelDoctorInfo(This,lDoctorID)	\
    (This)->lpVtbl -> DelDoctorInfo(This,lDoctorID)

#define IDBConfig_SetDoctorPassword(This,lDoctorID,bsPassword)	\
    (This)->lpVtbl -> SetDoctorPassword(This,lDoctorID,bsPassword)

#define IDBConfig_AddDoctorInfo(This,scDoctorInfo,lDoctorID)	\
    (This)->lpVtbl -> AddDoctorInfo(This,scDoctorInfo,lDoctorID)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE IDBConfig_SetConfigInfo_Proxy( 
    IDBConfig __RPC_FAR * This,
    /* [in] */ ConfigInfoStruct ConfigInfo);


void __RPC_STUB IDBConfig_SetConfigInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IDBConfig_GetConfigInfo_Proxy( 
    IDBConfig __RPC_FAR * This,
    /* [out] */ ConfigInfoStruct __RPC_FAR *pConfigInfo);


void __RPC_STUB IDBConfig_GetConfigInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IDBConfig_SetDoctorInfo_Proxy( 
    IDBConfig __RPC_FAR * This,
    /* [in] */ DoctorInfoStruct scDoctorInfo);


void __RPC_STUB IDBConfig_SetDoctorInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IDBConfig_GetDoctorList_Proxy( 
    IDBConfig __RPC_FAR * This,
    /* [out] */ long __RPC_FAR *lpCount,
    /* [size_is][size_is][out] */ DoctorInfoStruct __RPC_FAR *__RPC_FAR *ppDoctorInfo);


void __RPC_STUB IDBConfig_GetDoctorList_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IDBConfig_DelDoctorInfo_Proxy( 
    IDBConfig __RPC_FAR * This,
    /* [in] */ long lDoctorID);


void __RPC_STUB IDBConfig_DelDoctorInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IDBConfig_SetDoctorPassword_Proxy( 
    IDBConfig __RPC_FAR * This,
    /* [in] */ long lDoctorID,
    /* [in] */ BSTR bsPassword);


void __RPC_STUB IDBConfig_SetDoctorPassword_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IDBConfig_AddDoctorInfo_Proxy( 
    IDBConfig __RPC_FAR * This,
    /* [in] */ DoctorInfoStruct scDoctorInfo,
    /* [out] */ long __RPC_FAR *lDoctorID);


void __RPC_STUB IDBConfig_AddDoctorInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IDBConfig_INTERFACE_DEFINED__ */


#ifndef __IDBSession_INTERFACE_DEFINED__
#define __IDBSession_INTERFACE_DEFINED__

/* interface IDBSession */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IDBSession;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("1B352455-716C-4D2B-915E-F774938F72EF")
    IDBSession : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ResetSessionStruct( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetCurrentPatientUID( 
            /* [in] */ BSTR bsCurrentPatientUID) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetCurrentPatientUID( 
            /* [out] */ BSTR __RPC_FAR *pbsCurrentPatientUID) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetPatientID( 
            /* [in] */ BSTR bspatientID) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetPatientID( 
            /* [out] */ BSTR __RPC_FAR *pbsPatientID) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetPatientName( 
            /* [in] */ BSTR bsPatientName) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetPatientName( 
            /* [out] */ BSTR __RPC_FAR *pbsPatientName) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetPatientGender( 
            /* [in] */ INT iGender) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetPatientGender( 
            /* [out] */ INT __RPC_FAR *piGender) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetCurrentStudyUID( 
            /* [in] */ BSTR bsCurrentStudyUID) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetCurrentStudyUID( 
            /* [out] */ BSTR __RPC_FAR *pbsCurrentStudyUID) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetReferringPhysicianName( 
            /* [in] */ BSTR bsReferringPhysicianName) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetReferringPhysicianName( 
            /* [out] */ BSTR __RPC_FAR *pbsReferringPhysicianName) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetOperatorName( 
            /* [in] */ BSTR bsOperatorName) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetOperatorName( 
            /* [out] */ BSTR __RPC_FAR *pbsOperatorName) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetSeriesInfo( 
            /* [in] */ SeriesInfoStruct scSeriesInfo) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetSeriesInfo( 
            /* [out] */ SeriesInfoStruct __RPC_FAR *pscSeriesInfo) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetImageInfo( 
            /* [in] */ ImageInfoStruct scImageInfo) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetImageInfo( 
            /* [out] */ ImageInfoStruct __RPC_FAR *pscImageInfo) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetImageLaterality( 
            /* [in] */ INT iImageLaterality) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetImageLaterality( 
            /* [out] */ INT __RPC_FAR *piImageLaterality) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetPatientPosition( 
            /* [in] */ INT iPatientPosition) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetPatientPosition( 
            /* [out] */ INT __RPC_FAR *piPatientPosition) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetViewPosition( 
            /* [in] */ LONG lViewPosition) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetViewPosition( 
            /* [out] */ LONG __RPC_FAR *plViewPosition) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetPBLInfo( 
            /* [in] */ PBLInfoStruct scPblInfo) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetPBLInfo( 
            /* [out] */ PBLInfoStruct __RPC_FAR *pscPblInfo) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetShutterFieldSize( 
            /* [in] */ INT iSFS) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetShutterFieldSize( 
            /* [out] */ INT __RPC_FAR *piSFS) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetAprIPSettingPara( 
            /* [in] */ AprIPSettingPara scAprIPSetting) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetAprIPSettingPara( 
            /* [out] */ AprIPSettingPara __RPC_FAR *pscAprIPSetting) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetAprOrientation( 
            /* [in] */ AprOrientationStruct scAprOrientation) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetAprOrientation( 
            /* [out] */ AprOrientationStruct __RPC_FAR *pscAprOrientation) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetXRAYSTATUS( 
            /* [in] */ XRAYSTATUS enumXRAYSTATUS) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetXRAYSTATUS( 
            /* [out] */ XRAYSTATUS __RPC_FAR *penumXRAYSTATUS) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetDAP( 
            /* [in] */ DOUBLE dbDAP) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetDAP( 
            /* [out] */ DOUBLE __RPC_FAR *pdbDAP) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ChangeSysWorkState( 
            /* [in] */ WORKSTATE_TYPE enumWorkState) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ActiveReviewing( 
            /* [in] */ REVIEW_TYPE enumReviewType) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ModifyDicomInfo( 
            /* [in] */ DICOMINFO_TYPE enumInfoType,
            /* [in] */ BSTR bsUID) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetImageRootDriver( 
            /* [out] */ BSTR __RPC_FAR *pbsPath) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IDBSessionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IDBSession __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IDBSession __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IDBSession __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ResetSessionStruct )( 
            IDBSession __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetCurrentPatientUID )( 
            IDBSession __RPC_FAR * This,
            /* [in] */ BSTR bsCurrentPatientUID);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetCurrentPatientUID )( 
            IDBSession __RPC_FAR * This,
            /* [out] */ BSTR __RPC_FAR *pbsCurrentPatientUID);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetPatientID )( 
            IDBSession __RPC_FAR * This,
            /* [in] */ BSTR bspatientID);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetPatientID )( 
            IDBSession __RPC_FAR * This,
            /* [out] */ BSTR __RPC_FAR *pbsPatientID);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetPatientName )( 
            IDBSession __RPC_FAR * This,
            /* [in] */ BSTR bsPatientName);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetPatientName )( 
            IDBSession __RPC_FAR * This,
            /* [out] */ BSTR __RPC_FAR *pbsPatientName);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetPatientGender )( 
            IDBSession __RPC_FAR * This,
            /* [in] */ INT iGender);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetPatientGender )( 
            IDBSession __RPC_FAR * This,
            /* [out] */ INT __RPC_FAR *piGender);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetCurrentStudyUID )( 
            IDBSession __RPC_FAR * This,
            /* [in] */ BSTR bsCurrentStudyUID);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetCurrentStudyUID )( 
            IDBSession __RPC_FAR * This,
            /* [out] */ BSTR __RPC_FAR *pbsCurrentStudyUID);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetReferringPhysicianName )( 
            IDBSession __RPC_FAR * This,
            /* [in] */ BSTR bsReferringPhysicianName);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetReferringPhysicianName )( 
            IDBSession __RPC_FAR * This,
            /* [out] */ BSTR __RPC_FAR *pbsReferringPhysicianName);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetOperatorName )( 
            IDBSession __RPC_FAR * This,
            /* [in] */ BSTR bsOperatorName);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetOperatorName )( 
            IDBSession __RPC_FAR * This,
            /* [out] */ BSTR __RPC_FAR *pbsOperatorName);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetSeriesInfo )( 
            IDBSession __RPC_FAR * This,
            /* [in] */ SeriesInfoStruct scSeriesInfo);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetSeriesInfo )( 
            IDBSession __RPC_FAR * This,
            /* [out] */ SeriesInfoStruct __RPC_FAR *pscSeriesInfo);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetImageInfo )( 
            IDBSession __RPC_FAR * This,
            /* [in] */ ImageInfoStruct scImageInfo);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetImageInfo )( 
            IDBSession __RPC_FAR * This,
            /* [out] */ ImageInfoStruct __RPC_FAR *pscImageInfo);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetImageLaterality )( 
            IDBSession __RPC_FAR * This,
            /* [in] */ INT iImageLaterality);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetImageLaterality )( 
            IDBSession __RPC_FAR * This,
            /* [out] */ INT __RPC_FAR *piImageLaterality);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetPatientPosition )( 
            IDBSession __RPC_FAR * This,
            /* [in] */ INT iPatientPosition);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetPatientPosition )( 
            IDBSession __RPC_FAR * This,
            /* [out] */ INT __RPC_FAR *piPatientPosition);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetViewPosition )( 
            IDBSession __RPC_FAR * This,
            /* [in] */ LONG lViewPosition);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetViewPosition )( 
            IDBSession __RPC_FAR * This,
            /* [out] */ LONG __RPC_FAR *plViewPosition);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetPBLInfo )( 
            IDBSession __RPC_FAR * This,
            /* [in] */ PBLInfoStruct scPblInfo);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetPBLInfo )( 
            IDBSession __RPC_FAR * This,
            /* [out] */ PBLInfoStruct __RPC_FAR *pscPblInfo);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetShutterFieldSize )( 
            IDBSession __RPC_FAR * This,
            /* [in] */ INT iSFS);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetShutterFieldSize )( 
            IDBSession __RPC_FAR * This,
            /* [out] */ INT __RPC_FAR *piSFS);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetAprIPSettingPara )( 
            IDBSession __RPC_FAR * This,
            /* [in] */ AprIPSettingPara scAprIPSetting);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetAprIPSettingPara )( 
            IDBSession __RPC_FAR * This,
            /* [out] */ AprIPSettingPara __RPC_FAR *pscAprIPSetting);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetAprOrientation )( 
            IDBSession __RPC_FAR * This,
            /* [in] */ AprOrientationStruct scAprOrientation);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetAprOrientation )( 
            IDBSession __RPC_FAR * This,
            /* [out] */ AprOrientationStruct __RPC_FAR *pscAprOrientation);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetXRAYSTATUS )( 
            IDBSession __RPC_FAR * This,
            /* [in] */ XRAYSTATUS enumXRAYSTATUS);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetXRAYSTATUS )( 
            IDBSession __RPC_FAR * This,
            /* [out] */ XRAYSTATUS __RPC_FAR *penumXRAYSTATUS);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetDAP )( 
            IDBSession __RPC_FAR * This,
            /* [in] */ DOUBLE dbDAP);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetDAP )( 
            IDBSession __RPC_FAR * This,
            /* [out] */ DOUBLE __RPC_FAR *pdbDAP);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ChangeSysWorkState )( 
            IDBSession __RPC_FAR * This,
            /* [in] */ WORKSTATE_TYPE enumWorkState);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ActiveReviewing )( 
            IDBSession __RPC_FAR * This,
            /* [in] */ REVIEW_TYPE enumReviewType);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ModifyDicomInfo )( 
            IDBSession __RPC_FAR * This,
            /* [in] */ DICOMINFO_TYPE enumInfoType,
            /* [in] */ BSTR bsUID);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetImageRootDriver )( 
            IDBSession __RPC_FAR * This,
            /* [out] */ BSTR __RPC_FAR *pbsPath);
        
        END_INTERFACE
    } IDBSessionVtbl;

    interface IDBSession
    {
        CONST_VTBL struct IDBSessionVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDBSession_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDBSession_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDBSession_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDBSession_ResetSessionStruct(This)	\
    (This)->lpVtbl -> ResetSessionStruct(This)

#define IDBSession_SetCurrentPatientUID(This,bsCurrentPatientUID)	\
    (This)->lpVtbl -> SetCurrentPatientUID(This,bsCurrentPatientUID)

#define IDBSession_GetCurrentPatientUID(This,pbsCurrentPatientUID)	\
    (This)->lpVtbl -> GetCurrentPatientUID(This,pbsCurrentPatientUID)

#define IDBSession_SetPatientID(This,bspatientID)	\
    (This)->lpVtbl -> SetPatientID(This,bspatientID)

#define IDBSession_GetPatientID(This,pbsPatientID)	\
    (This)->lpVtbl -> GetPatientID(This,pbsPatientID)

#define IDBSession_SetPatientName(This,bsPatientName)	\
    (This)->lpVtbl -> SetPatientName(This,bsPatientName)

#define IDBSession_GetPatientName(This,pbsPatientName)	\
    (This)->lpVtbl -> GetPatientName(This,pbsPatientName)

#define IDBSession_SetPatientGender(This,iGender)	\
    (This)->lpVtbl -> SetPatientGender(This,iGender)

#define IDBSession_GetPatientGender(This,piGender)	\
    (This)->lpVtbl -> GetPatientGender(This,piGender)

#define IDBSession_SetCurrentStudyUID(This,bsCurrentStudyUID)	\
    (This)->lpVtbl -> SetCurrentStudyUID(This,bsCurrentStudyUID)

#define IDBSession_GetCurrentStudyUID(This,pbsCurrentStudyUID)	\
    (This)->lpVtbl -> GetCurrentStudyUID(This,pbsCurrentStudyUID)

#define IDBSession_SetReferringPhysicianName(This,bsReferringPhysicianName)	\
    (This)->lpVtbl -> SetReferringPhysicianName(This,bsReferringPhysicianName)

#define IDBSession_GetReferringPhysicianName(This,pbsReferringPhysicianName)	\
    (This)->lpVtbl -> GetReferringPhysicianName(This,pbsReferringPhysicianName)

#define IDBSession_SetOperatorName(This,bsOperatorName)	\
    (This)->lpVtbl -> SetOperatorName(This,bsOperatorName)

#define IDBSession_GetOperatorName(This,pbsOperatorName)	\
    (This)->lpVtbl -> GetOperatorName(This,pbsOperatorName)

#define IDBSession_SetSeriesInfo(This,scSeriesInfo)	\
    (This)->lpVtbl -> SetSeriesInfo(This,scSeriesInfo)

#define IDBSession_GetSeriesInfo(This,pscSeriesInfo)	\
    (This)->lpVtbl -> GetSeriesInfo(This,pscSeriesInfo)

#define IDBSession_SetImageInfo(This,scImageInfo)	\
    (This)->lpVtbl -> SetImageInfo(This,scImageInfo)

#define IDBSession_GetImageInfo(This,pscImageInfo)	\
    (This)->lpVtbl -> GetImageInfo(This,pscImageInfo)

#define IDBSession_SetImageLaterality(This,iImageLaterality)	\
    (This)->lpVtbl -> SetImageLaterality(This,iImageLaterality)

#define IDBSession_GetImageLaterality(This,piImageLaterality)	\
    (This)->lpVtbl -> GetImageLaterality(This,piImageLaterality)

#define IDBSession_SetPatientPosition(This,iPatientPosition)	\
    (This)->lpVtbl -> SetPatientPosition(This,iPatientPosition)

#define IDBSession_GetPatientPosition(This,piPatientPosition)	\
    (This)->lpVtbl -> GetPatientPosition(This,piPatientPosition)

#define IDBSession_SetViewPosition(This,lViewPosition)	\
    (This)->lpVtbl -> SetViewPosition(This,lViewPosition)

#define IDBSession_GetViewPosition(This,plViewPosition)	\
    (This)->lpVtbl -> GetViewPosition(This,plViewPosition)

#define IDBSession_SetPBLInfo(This,scPblInfo)	\
    (This)->lpVtbl -> SetPBLInfo(This,scPblInfo)

#define IDBSession_GetPBLInfo(This,pscPblInfo)	\
    (This)->lpVtbl -> GetPBLInfo(This,pscPblInfo)

#define IDBSession_SetShutterFieldSize(This,iSFS)	\
    (This)->lpVtbl -> SetShutterFieldSize(This,iSFS)

#define IDBSession_GetShutterFieldSize(This,piSFS)	\
    (This)->lpVtbl -> GetShutterFieldSize(This,piSFS)

#define IDBSession_SetAprIPSettingPara(This,scAprIPSetting)	\
    (This)->lpVtbl -> SetAprIPSettingPara(This,scAprIPSetting)

#define IDBSession_GetAprIPSettingPara(This,pscAprIPSetting)	\
    (This)->lpVtbl -> GetAprIPSettingPara(This,pscAprIPSetting)

#define IDBSession_SetAprOrientation(This,scAprOrientation)	\
    (This)->lpVtbl -> SetAprOrientation(This,scAprOrientation)

#define IDBSession_GetAprOrientation(This,pscAprOrientation)	\
    (This)->lpVtbl -> GetAprOrientation(This,pscAprOrientation)

#define IDBSession_SetXRAYSTATUS(This,enumXRAYSTATUS)	\
    (This)->lpVtbl -> SetXRAYSTATUS(This,enumXRAYSTATUS)

#define IDBSession_GetXRAYSTATUS(This,penumXRAYSTATUS)	\
    (This)->lpVtbl -> GetXRAYSTATUS(This,penumXRAYSTATUS)

#define IDBSession_SetDAP(This,dbDAP)	\
    (This)->lpVtbl -> SetDAP(This,dbDAP)

#define IDBSession_GetDAP(This,pdbDAP)	\
    (This)->lpVtbl -> GetDAP(This,pdbDAP)

#define IDBSession_ChangeSysWorkState(This,enumWorkState)	\
    (This)->lpVtbl -> ChangeSysWorkState(This,enumWorkState)

#define IDBSession_ActiveReviewing(This,enumReviewType)	\
    (This)->lpVtbl -> ActiveReviewing(This,enumReviewType)

#define IDBSession_ModifyDicomInfo(This,enumInfoType,bsUID)	\
    (This)->lpVtbl -> ModifyDicomInfo(This,enumInfoType,bsUID)

#define IDBSession_GetImageRootDriver(This,pbsPath)	\
    (This)->lpVtbl -> GetImageRootDriver(This,pbsPath)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE IDBSession_ResetSessionStruct_Proxy( 
    IDBSession __RPC_FAR * This);


void __RPC_STUB IDBSession_ResetSessionStruct_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IDBSession_SetCurrentPatientUID_Proxy( 
    IDBSession __RPC_FAR * This,
    /* [in] */ BSTR bsCurrentPatientUID);


void __RPC_STUB IDBSession_SetCurrentPatientUID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IDBSession_GetCurrentPatientUID_Proxy( 
    IDBSession __RPC_FAR * This,
    /* [out] */ BSTR __RPC_FAR *pbsCurrentPatientUID);


void __RPC_STUB IDBSession_GetCurrentPatientUID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IDBSession_SetPatientID_Proxy( 
    IDBSession __RPC_FAR * This,
    /* [in] */ BSTR bspatientID);


void __RPC_STUB IDBSession_SetPatientID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IDBSession_GetPatientID_Proxy( 
    IDBSession __RPC_FAR * This,
    /* [out] */ BSTR __RPC_FAR *pbsPatientID);


void __RPC_STUB IDBSession_GetPatientID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IDBSession_SetPatientName_Proxy( 
    IDBSession __RPC_FAR * This,
    /* [in] */ BSTR bsPatientName);


void __RPC_STUB IDBSession_SetPatientName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IDBSession_GetPatientName_Proxy( 
    IDBSession __RPC_FAR * This,
    /* [out] */ BSTR __RPC_FAR *pbsPatientName);


void __RPC_STUB IDBSession_GetPatientName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IDBSession_SetPatientGender_Proxy( 
    IDBSession __RPC_FAR * This,
    /* [in] */ INT iGender);


void __RPC_STUB IDBSession_SetPatientGender_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IDBSession_GetPatientGender_Proxy( 
    IDBSession __RPC_FAR * This,
    /* [out] */ INT __RPC_FAR *piGender);


void __RPC_STUB IDBSession_GetPatientGender_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IDBSession_SetCurrentStudyUID_Proxy( 
    IDBSession __RPC_FAR * This,
    /* [in] */ BSTR bsCurrentStudyUID);


void __RPC_STUB IDBSession_SetCurrentStudyUID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IDBSession_GetCurrentStudyUID_Proxy( 
    IDBSession __RPC_FAR * This,
    /* [out] */ BSTR __RPC_FAR *pbsCurrentStudyUID);


void __RPC_STUB IDBSession_GetCurrentStudyUID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IDBSession_SetReferringPhysicianName_Proxy( 
    IDBSession __RPC_FAR * This,
    /* [in] */ BSTR bsReferringPhysicianName);


void __RPC_STUB IDBSession_SetReferringPhysicianName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IDBSession_GetReferringPhysicianName_Proxy( 
    IDBSession __RPC_FAR * This,
    /* [out] */ BSTR __RPC_FAR *pbsReferringPhysicianName);


void __RPC_STUB IDBSession_GetReferringPhysicianName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IDBSession_SetOperatorName_Proxy( 
    IDBSession __RPC_FAR * This,
    /* [in] */ BSTR bsOperatorName);


void __RPC_STUB IDBSession_SetOperatorName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IDBSession_GetOperatorName_Proxy( 
    IDBSession __RPC_FAR * This,
    /* [out] */ BSTR __RPC_FAR *pbsOperatorName);


void __RPC_STUB IDBSession_GetOperatorName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IDBSession_SetSeriesInfo_Proxy( 
    IDBSession __RPC_FAR * This,
    /* [in] */ SeriesInfoStruct scSeriesInfo);


void __RPC_STUB IDBSession_SetSeriesInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IDBSession_GetSeriesInfo_Proxy( 
    IDBSession __RPC_FAR * This,
    /* [out] */ SeriesInfoStruct __RPC_FAR *pscSeriesInfo);


void __RPC_STUB IDBSession_GetSeriesInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IDBSession_SetImageInfo_Proxy( 
    IDBSession __RPC_FAR * This,
    /* [in] */ ImageInfoStruct scImageInfo);


void __RPC_STUB IDBSession_SetImageInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IDBSession_GetImageInfo_Proxy( 
    IDBSession __RPC_FAR * This,
    /* [out] */ ImageInfoStruct __RPC_FAR *pscImageInfo);


void __RPC_STUB IDBSession_GetImageInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IDBSession_SetImageLaterality_Proxy( 
    IDBSession __RPC_FAR * This,
    /* [in] */ INT iImageLaterality);


void __RPC_STUB IDBSession_SetImageLaterality_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IDBSession_GetImageLaterality_Proxy( 
    IDBSession __RPC_FAR * This,
    /* [out] */ INT __RPC_FAR *piImageLaterality);


void __RPC_STUB IDBSession_GetImageLaterality_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IDBSession_SetPatientPosition_Proxy( 
    IDBSession __RPC_FAR * This,
    /* [in] */ INT iPatientPosition);


void __RPC_STUB IDBSession_SetPatientPosition_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IDBSession_GetPatientPosition_Proxy( 
    IDBSession __RPC_FAR * This,
    /* [out] */ INT __RPC_FAR *piPatientPosition);


void __RPC_STUB IDBSession_GetPatientPosition_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IDBSession_SetViewPosition_Proxy( 
    IDBSession __RPC_FAR * This,
    /* [in] */ LONG lViewPosition);


void __RPC_STUB IDBSession_SetViewPosition_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IDBSession_GetViewPosition_Proxy( 
    IDBSession __RPC_FAR * This,
    /* [out] */ LONG __RPC_FAR *plViewPosition);


void __RPC_STUB IDBSession_GetViewPosition_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IDBSession_SetPBLInfo_Proxy( 
    IDBSession __RPC_FAR * This,
    /* [in] */ PBLInfoStruct scPblInfo);


void __RPC_STUB IDBSession_SetPBLInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IDBSession_GetPBLInfo_Proxy( 
    IDBSession __RPC_FAR * This,
    /* [out] */ PBLInfoStruct __RPC_FAR *pscPblInfo);


void __RPC_STUB IDBSession_GetPBLInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IDBSession_SetShutterFieldSize_Proxy( 
    IDBSession __RPC_FAR * This,
    /* [in] */ INT iSFS);


void __RPC_STUB IDBSession_SetShutterFieldSize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IDBSession_GetShutterFieldSize_Proxy( 
    IDBSession __RPC_FAR * This,
    /* [out] */ INT __RPC_FAR *piSFS);


void __RPC_STUB IDBSession_GetShutterFieldSize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IDBSession_SetAprIPSettingPara_Proxy( 
    IDBSession __RPC_FAR * This,
    /* [in] */ AprIPSettingPara scAprIPSetting);


void __RPC_STUB IDBSession_SetAprIPSettingPara_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IDBSession_GetAprIPSettingPara_Proxy( 
    IDBSession __RPC_FAR * This,
    /* [out] */ AprIPSettingPara __RPC_FAR *pscAprIPSetting);


void __RPC_STUB IDBSession_GetAprIPSettingPara_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IDBSession_SetAprOrientation_Proxy( 
    IDBSession __RPC_FAR * This,
    /* [in] */ AprOrientationStruct scAprOrientation);


void __RPC_STUB IDBSession_SetAprOrientation_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IDBSession_GetAprOrientation_Proxy( 
    IDBSession __RPC_FAR * This,
    /* [out] */ AprOrientationStruct __RPC_FAR *pscAprOrientation);


void __RPC_STUB IDBSession_GetAprOrientation_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IDBSession_SetXRAYSTATUS_Proxy( 
    IDBSession __RPC_FAR * This,
    /* [in] */ XRAYSTATUS enumXRAYSTATUS);


void __RPC_STUB IDBSession_SetXRAYSTATUS_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IDBSession_GetXRAYSTATUS_Proxy( 
    IDBSession __RPC_FAR * This,
    /* [out] */ XRAYSTATUS __RPC_FAR *penumXRAYSTATUS);


void __RPC_STUB IDBSession_GetXRAYSTATUS_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IDBSession_SetDAP_Proxy( 
    IDBSession __RPC_FAR * This,
    /* [in] */ DOUBLE dbDAP);


void __RPC_STUB IDBSession_SetDAP_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IDBSession_GetDAP_Proxy( 
    IDBSession __RPC_FAR * This,
    /* [out] */ DOUBLE __RPC_FAR *pdbDAP);


void __RPC_STUB IDBSession_GetDAP_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IDBSession_ChangeSysWorkState_Proxy( 
    IDBSession __RPC_FAR * This,
    /* [in] */ WORKSTATE_TYPE enumWorkState);


void __RPC_STUB IDBSession_ChangeSysWorkState_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IDBSession_ActiveReviewing_Proxy( 
    IDBSession __RPC_FAR * This,
    /* [in] */ REVIEW_TYPE enumReviewType);


void __RPC_STUB IDBSession_ActiveReviewing_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IDBSession_ModifyDicomInfo_Proxy( 
    IDBSession __RPC_FAR * This,
    /* [in] */ DICOMINFO_TYPE enumInfoType,
    /* [in] */ BSTR bsUID);


void __RPC_STUB IDBSession_ModifyDicomInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IDBSession_GetImageRootDriver_Proxy( 
    IDBSession __RPC_FAR * This,
    /* [out] */ BSTR __RPC_FAR *pbsPath);


void __RPC_STUB IDBSession_GetImageRootDriver_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IDBSession_INTERFACE_DEFINED__ */



#ifndef __PATestClientLibExt_LIBRARY_DEFINED__
#define __PATestClientLibExt_LIBRARY_DEFINED__

/* library PATestClientLibExt */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_PATestClientLibExt;

EXTERN_C const CLSID CLSID_DBPIM;

#ifdef __cplusplus

class DECLSPEC_UUID("C571EBD4-8BE7-4498-9C16-C222A9537EB6")
DBPIM;
#endif

EXTERN_C const CLSID CLSID_DBConfig;

#ifdef __cplusplus

class DECLSPEC_UUID("B0021308-93EF-42D5-817A-3FFD57659F76")
DBConfig;
#endif

EXTERN_C const CLSID CLSID_DBSession;

#ifdef __cplusplus

class DECLSPEC_UUID("05D97A96-4206-42C1-9B78-8C5C8909E1BC")
DBSession;
#endif

EXTERN_C const CLSID CLSID_ISATL;

#ifdef __cplusplus

class DECLSPEC_UUID("264349CE-E89F-41DA-8434-C1600FB8FB5E")
ISATL;
#endif
#endif /* __PATestClientLibExt_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long __RPC_FAR *, unsigned long            , BSTR __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  BSTR_UserMarshal(  unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, BSTR __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  BSTR_UserUnmarshal(unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, BSTR __RPC_FAR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long __RPC_FAR *, BSTR __RPC_FAR * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
