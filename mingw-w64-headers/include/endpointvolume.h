/*** Autogenerated by WIDL 10.12 from include/endpointvolume.idl - Do not edit ***/

#ifdef _WIN32
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif
#include <rpc.h>
#include <rpcndr.h>
#endif

#ifndef COM_NO_WINDOWS_H
#include <windows.h>
#include <ole2.h>
#endif

#ifndef __endpointvolume_h__
#define __endpointvolume_h__

/* Forward declarations */

#ifndef __IAudioEndpointVolumeCallback_FWD_DEFINED__
#define __IAudioEndpointVolumeCallback_FWD_DEFINED__
typedef interface IAudioEndpointVolumeCallback IAudioEndpointVolumeCallback;
#ifdef __cplusplus
interface IAudioEndpointVolumeCallback;
#endif /* __cplusplus */
#endif

#ifndef __IAudioEndpointVolume_FWD_DEFINED__
#define __IAudioEndpointVolume_FWD_DEFINED__
typedef interface IAudioEndpointVolume IAudioEndpointVolume;
#ifdef __cplusplus
interface IAudioEndpointVolume;
#endif /* __cplusplus */
#endif

#ifndef __IAudioEndpointVolumeEx_FWD_DEFINED__
#define __IAudioEndpointVolumeEx_FWD_DEFINED__
typedef interface IAudioEndpointVolumeEx IAudioEndpointVolumeEx;
#ifdef __cplusplus
interface IAudioEndpointVolumeEx;
#endif /* __cplusplus */
#endif

/* Headers for imported files */

#include <unknwn.h>
#include <devicetopology.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct AUDIO_VOLUME_NOTIFICATION_DATA {
    GUID guidEventContext;
    WINBOOL bMuted;
    FLOAT fMasterVolume;
    UINT nChannels;
    FLOAT afChannelVolumes[1];
} AUDIO_VOLUME_NOTIFICATION_DATA;
typedef struct AUDIO_VOLUME_NOTIFICATION_DATA *PAUDIO_VOLUME_NOTIFICATION_DATA;
#define ENDPOINT_HARDWARE_SUPPORT_VOLUME 0x1
#define ENDPOINT_HARDWARE_SUPPORT_MUTE 0x2
#define ENDPOINT_HARDWARE_SUPPORT_METER 0x4
#ifndef __IAudioEndpointVolumeCallback_FWD_DEFINED__
#define __IAudioEndpointVolumeCallback_FWD_DEFINED__
typedef interface IAudioEndpointVolumeCallback IAudioEndpointVolumeCallback;
#ifdef __cplusplus
interface IAudioEndpointVolumeCallback;
#endif /* __cplusplus */
#endif

#ifndef __IAudioEndpointVolume_FWD_DEFINED__
#define __IAudioEndpointVolume_FWD_DEFINED__
typedef interface IAudioEndpointVolume IAudioEndpointVolume;
#ifdef __cplusplus
interface IAudioEndpointVolume;
#endif /* __cplusplus */
#endif

#ifndef __IAudioEndpointVolumeEx_FWD_DEFINED__
#define __IAudioEndpointVolumeEx_FWD_DEFINED__
typedef interface IAudioEndpointVolumeEx IAudioEndpointVolumeEx;
#ifdef __cplusplus
interface IAudioEndpointVolumeEx;
#endif /* __cplusplus */
#endif

#ifndef __IAudioMeterInformation_FWD_DEFINED__
#define __IAudioMeterInformation_FWD_DEFINED__
typedef interface IAudioMeterInformation IAudioMeterInformation;
#ifdef __cplusplus
interface IAudioMeterInformation;
#endif /* __cplusplus */
#endif

/*****************************************************************************
 * IAudioEndpointVolumeCallback interface
 */
#ifndef __IAudioEndpointVolumeCallback_INTERFACE_DEFINED__
#define __IAudioEndpointVolumeCallback_INTERFACE_DEFINED__

DEFINE_GUID(IID_IAudioEndpointVolumeCallback, 0x657804fa, 0xd6ad, 0x4496, 0x8a,0x60, 0x35,0x27,0x52,0xaf,0x4f,0x89);
#if defined(__cplusplus) && !defined(CINTERFACE)
MIDL_INTERFACE("657804fa-d6ad-4496-8a60-352752af4f89")
IAudioEndpointVolumeCallback : public IUnknown
{
    virtual HRESULT STDMETHODCALLTYPE OnNotify(
        AUDIO_VOLUME_NOTIFICATION_DATA *pNotify) = 0;

};
#ifdef __CRT_UUID_DECL
__CRT_UUID_DECL(IAudioEndpointVolumeCallback, 0x657804fa, 0xd6ad, 0x4496, 0x8a,0x60, 0x35,0x27,0x52,0xaf,0x4f,0x89)
#endif
#else
typedef struct IAudioEndpointVolumeCallbackVtbl {
    BEGIN_INTERFACE

    /*** IUnknown methods ***/
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(
        IAudioEndpointVolumeCallback *This,
        REFIID riid,
        void **ppvObject);

    ULONG (STDMETHODCALLTYPE *AddRef)(
        IAudioEndpointVolumeCallback *This);

    ULONG (STDMETHODCALLTYPE *Release)(
        IAudioEndpointVolumeCallback *This);

    /*** IAudioEndpointVolumeCallback methods ***/
    HRESULT (STDMETHODCALLTYPE *OnNotify)(
        IAudioEndpointVolumeCallback *This,
        AUDIO_VOLUME_NOTIFICATION_DATA *pNotify);

    END_INTERFACE
} IAudioEndpointVolumeCallbackVtbl;

interface IAudioEndpointVolumeCallback {
    CONST_VTBL IAudioEndpointVolumeCallbackVtbl* lpVtbl;
};

#ifdef COBJMACROS
#ifndef WIDL_C_INLINE_WRAPPERS
/*** IUnknown methods ***/
#define IAudioEndpointVolumeCallback_QueryInterface(This,riid,ppvObject) (This)->lpVtbl->QueryInterface(This,riid,ppvObject)
#define IAudioEndpointVolumeCallback_AddRef(This) (This)->lpVtbl->AddRef(This)
#define IAudioEndpointVolumeCallback_Release(This) (This)->lpVtbl->Release(This)
/*** IAudioEndpointVolumeCallback methods ***/
#define IAudioEndpointVolumeCallback_OnNotify(This,pNotify) (This)->lpVtbl->OnNotify(This,pNotify)
#else
/*** IUnknown methods ***/
static inline HRESULT IAudioEndpointVolumeCallback_QueryInterface(IAudioEndpointVolumeCallback* This,REFIID riid,void **ppvObject) {
    return This->lpVtbl->QueryInterface(This,riid,ppvObject);
}
static inline ULONG IAudioEndpointVolumeCallback_AddRef(IAudioEndpointVolumeCallback* This) {
    return This->lpVtbl->AddRef(This);
}
static inline ULONG IAudioEndpointVolumeCallback_Release(IAudioEndpointVolumeCallback* This) {
    return This->lpVtbl->Release(This);
}
/*** IAudioEndpointVolumeCallback methods ***/
static inline HRESULT IAudioEndpointVolumeCallback_OnNotify(IAudioEndpointVolumeCallback* This,AUDIO_VOLUME_NOTIFICATION_DATA *pNotify) {
    return This->lpVtbl->OnNotify(This,pNotify);
}
#endif
#endif

#endif


#endif  /* __IAudioEndpointVolumeCallback_INTERFACE_DEFINED__ */

/*****************************************************************************
 * IAudioEndpointVolume interface
 */
#ifndef __IAudioEndpointVolume_INTERFACE_DEFINED__
#define __IAudioEndpointVolume_INTERFACE_DEFINED__

DEFINE_GUID(IID_IAudioEndpointVolume, 0x5cdf2c82, 0x841e, 0x4546, 0x97,0x22, 0x0c,0xf7,0x40,0x78,0x22,0x9a);
#if defined(__cplusplus) && !defined(CINTERFACE)
MIDL_INTERFACE("5cdf2c82-841e-4546-9722-0cf74078229a")
IAudioEndpointVolume : public IUnknown
{
    virtual HRESULT STDMETHODCALLTYPE RegisterControlChangeNotify(
        IAudioEndpointVolumeCallback *pNotify) = 0;

    virtual HRESULT STDMETHODCALLTYPE UnregisterControlChangeNotify(
        IAudioEndpointVolumeCallback *pNotify) = 0;

    virtual HRESULT STDMETHODCALLTYPE GetChannelCount(
        UINT *pnChannelCount) = 0;

    virtual HRESULT STDMETHODCALLTYPE SetMasterVolumeLevel(
        FLOAT fLevelDB,
        LPCGUID pguidEventContext) = 0;

    virtual HRESULT STDMETHODCALLTYPE SetMasterVolumeLevelScalar(
        FLOAT fLevel,
        LPCGUID pguidEventContext) = 0;

    virtual HRESULT STDMETHODCALLTYPE GetMasterVolumeLevel(
        FLOAT *fLevelDB) = 0;

    virtual HRESULT STDMETHODCALLTYPE GetMasterVolumeLevelScalar(
        FLOAT *fLevel) = 0;

    virtual HRESULT STDMETHODCALLTYPE SetChannelVolumeLevel(
        UINT nChannel,
        FLOAT fLevelDB,
        LPCGUID pguidEventContext) = 0;

    virtual HRESULT STDMETHODCALLTYPE SetChannelVolumeLevelScalar(
        UINT nChannel,
        FLOAT fLevel,
        LPCGUID pguidEventContext) = 0;

    virtual HRESULT STDMETHODCALLTYPE GetChannelVolumeLevel(
        UINT nChannel,
        FLOAT *fLevelDB) = 0;

    virtual HRESULT STDMETHODCALLTYPE GetChannelVolumeLevelScalar(
        UINT nChannel,
        FLOAT *fLevel) = 0;

    virtual HRESULT STDMETHODCALLTYPE SetMute(
        WINBOOL bMute,
        LPCGUID pguidEventContext) = 0;

    virtual HRESULT STDMETHODCALLTYPE GetMute(
        WINBOOL *bMute) = 0;

    virtual HRESULT STDMETHODCALLTYPE GetVolumeStepInfo(
        UINT *pnStep,
        UINT *pnStepCount) = 0;

    virtual HRESULT STDMETHODCALLTYPE VolumeStepUp(
        LPCGUID pguidEventContext) = 0;

    virtual HRESULT STDMETHODCALLTYPE VolumeStepDown(
        LPCGUID pguidEventContext) = 0;

    virtual HRESULT STDMETHODCALLTYPE QueryHardwareSupport(
        DWORD *pdwHardwareSupportMask) = 0;

    virtual HRESULT STDMETHODCALLTYPE GetVolumeRange(
        FLOAT *pflVolumeMindB,
        FLOAT *pflVolumeMaxdB,
        FLOAT *pflVolumeIncrementdB) = 0;

};
#ifdef __CRT_UUID_DECL
__CRT_UUID_DECL(IAudioEndpointVolume, 0x5cdf2c82, 0x841e, 0x4546, 0x97,0x22, 0x0c,0xf7,0x40,0x78,0x22,0x9a)
#endif
#else
typedef struct IAudioEndpointVolumeVtbl {
    BEGIN_INTERFACE

    /*** IUnknown methods ***/
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(
        IAudioEndpointVolume *This,
        REFIID riid,
        void **ppvObject);

    ULONG (STDMETHODCALLTYPE *AddRef)(
        IAudioEndpointVolume *This);

    ULONG (STDMETHODCALLTYPE *Release)(
        IAudioEndpointVolume *This);

    /*** IAudioEndpointVolume methods ***/
    HRESULT (STDMETHODCALLTYPE *RegisterControlChangeNotify)(
        IAudioEndpointVolume *This,
        IAudioEndpointVolumeCallback *pNotify);

    HRESULT (STDMETHODCALLTYPE *UnregisterControlChangeNotify)(
        IAudioEndpointVolume *This,
        IAudioEndpointVolumeCallback *pNotify);

    HRESULT (STDMETHODCALLTYPE *GetChannelCount)(
        IAudioEndpointVolume *This,
        UINT *pnChannelCount);

    HRESULT (STDMETHODCALLTYPE *SetMasterVolumeLevel)(
        IAudioEndpointVolume *This,
        FLOAT fLevelDB,
        LPCGUID pguidEventContext);

    HRESULT (STDMETHODCALLTYPE *SetMasterVolumeLevelScalar)(
        IAudioEndpointVolume *This,
        FLOAT fLevel,
        LPCGUID pguidEventContext);

    HRESULT (STDMETHODCALLTYPE *GetMasterVolumeLevel)(
        IAudioEndpointVolume *This,
        FLOAT *fLevelDB);

    HRESULT (STDMETHODCALLTYPE *GetMasterVolumeLevelScalar)(
        IAudioEndpointVolume *This,
        FLOAT *fLevel);

    HRESULT (STDMETHODCALLTYPE *SetChannelVolumeLevel)(
        IAudioEndpointVolume *This,
        UINT nChannel,
        FLOAT fLevelDB,
        LPCGUID pguidEventContext);

    HRESULT (STDMETHODCALLTYPE *SetChannelVolumeLevelScalar)(
        IAudioEndpointVolume *This,
        UINT nChannel,
        FLOAT fLevel,
        LPCGUID pguidEventContext);

    HRESULT (STDMETHODCALLTYPE *GetChannelVolumeLevel)(
        IAudioEndpointVolume *This,
        UINT nChannel,
        FLOAT *fLevelDB);

    HRESULT (STDMETHODCALLTYPE *GetChannelVolumeLevelScalar)(
        IAudioEndpointVolume *This,
        UINT nChannel,
        FLOAT *fLevel);

    HRESULT (STDMETHODCALLTYPE *SetMute)(
        IAudioEndpointVolume *This,
        WINBOOL bMute,
        LPCGUID pguidEventContext);

    HRESULT (STDMETHODCALLTYPE *GetMute)(
        IAudioEndpointVolume *This,
        WINBOOL *bMute);

    HRESULT (STDMETHODCALLTYPE *GetVolumeStepInfo)(
        IAudioEndpointVolume *This,
        UINT *pnStep,
        UINT *pnStepCount);

    HRESULT (STDMETHODCALLTYPE *VolumeStepUp)(
        IAudioEndpointVolume *This,
        LPCGUID pguidEventContext);

    HRESULT (STDMETHODCALLTYPE *VolumeStepDown)(
        IAudioEndpointVolume *This,
        LPCGUID pguidEventContext);

    HRESULT (STDMETHODCALLTYPE *QueryHardwareSupport)(
        IAudioEndpointVolume *This,
        DWORD *pdwHardwareSupportMask);

    HRESULT (STDMETHODCALLTYPE *GetVolumeRange)(
        IAudioEndpointVolume *This,
        FLOAT *pflVolumeMindB,
        FLOAT *pflVolumeMaxdB,
        FLOAT *pflVolumeIncrementdB);

    END_INTERFACE
} IAudioEndpointVolumeVtbl;

interface IAudioEndpointVolume {
    CONST_VTBL IAudioEndpointVolumeVtbl* lpVtbl;
};

#ifdef COBJMACROS
#ifndef WIDL_C_INLINE_WRAPPERS
/*** IUnknown methods ***/
#define IAudioEndpointVolume_QueryInterface(This,riid,ppvObject) (This)->lpVtbl->QueryInterface(This,riid,ppvObject)
#define IAudioEndpointVolume_AddRef(This) (This)->lpVtbl->AddRef(This)
#define IAudioEndpointVolume_Release(This) (This)->lpVtbl->Release(This)
/*** IAudioEndpointVolume methods ***/
#define IAudioEndpointVolume_RegisterControlChangeNotify(This,pNotify) (This)->lpVtbl->RegisterControlChangeNotify(This,pNotify)
#define IAudioEndpointVolume_UnregisterControlChangeNotify(This,pNotify) (This)->lpVtbl->UnregisterControlChangeNotify(This,pNotify)
#define IAudioEndpointVolume_GetChannelCount(This,pnChannelCount) (This)->lpVtbl->GetChannelCount(This,pnChannelCount)
#define IAudioEndpointVolume_SetMasterVolumeLevel(This,fLevelDB,pguidEventContext) (This)->lpVtbl->SetMasterVolumeLevel(This,fLevelDB,pguidEventContext)
#define IAudioEndpointVolume_SetMasterVolumeLevelScalar(This,fLevel,pguidEventContext) (This)->lpVtbl->SetMasterVolumeLevelScalar(This,fLevel,pguidEventContext)
#define IAudioEndpointVolume_GetMasterVolumeLevel(This,fLevelDB) (This)->lpVtbl->GetMasterVolumeLevel(This,fLevelDB)
#define IAudioEndpointVolume_GetMasterVolumeLevelScalar(This,fLevel) (This)->lpVtbl->GetMasterVolumeLevelScalar(This,fLevel)
#define IAudioEndpointVolume_SetChannelVolumeLevel(This,nChannel,fLevelDB,pguidEventContext) (This)->lpVtbl->SetChannelVolumeLevel(This,nChannel,fLevelDB,pguidEventContext)
#define IAudioEndpointVolume_SetChannelVolumeLevelScalar(This,nChannel,fLevel,pguidEventContext) (This)->lpVtbl->SetChannelVolumeLevelScalar(This,nChannel,fLevel,pguidEventContext)
#define IAudioEndpointVolume_GetChannelVolumeLevel(This,nChannel,fLevelDB) (This)->lpVtbl->GetChannelVolumeLevel(This,nChannel,fLevelDB)
#define IAudioEndpointVolume_GetChannelVolumeLevelScalar(This,nChannel,fLevel) (This)->lpVtbl->GetChannelVolumeLevelScalar(This,nChannel,fLevel)
#define IAudioEndpointVolume_SetMute(This,bMute,pguidEventContext) (This)->lpVtbl->SetMute(This,bMute,pguidEventContext)
#define IAudioEndpointVolume_GetMute(This,bMute) (This)->lpVtbl->GetMute(This,bMute)
#define IAudioEndpointVolume_GetVolumeStepInfo(This,pnStep,pnStepCount) (This)->lpVtbl->GetVolumeStepInfo(This,pnStep,pnStepCount)
#define IAudioEndpointVolume_VolumeStepUp(This,pguidEventContext) (This)->lpVtbl->VolumeStepUp(This,pguidEventContext)
#define IAudioEndpointVolume_VolumeStepDown(This,pguidEventContext) (This)->lpVtbl->VolumeStepDown(This,pguidEventContext)
#define IAudioEndpointVolume_QueryHardwareSupport(This,pdwHardwareSupportMask) (This)->lpVtbl->QueryHardwareSupport(This,pdwHardwareSupportMask)
#define IAudioEndpointVolume_GetVolumeRange(This,pflVolumeMindB,pflVolumeMaxdB,pflVolumeIncrementdB) (This)->lpVtbl->GetVolumeRange(This,pflVolumeMindB,pflVolumeMaxdB,pflVolumeIncrementdB)
#else
/*** IUnknown methods ***/
static inline HRESULT IAudioEndpointVolume_QueryInterface(IAudioEndpointVolume* This,REFIID riid,void **ppvObject) {
    return This->lpVtbl->QueryInterface(This,riid,ppvObject);
}
static inline ULONG IAudioEndpointVolume_AddRef(IAudioEndpointVolume* This) {
    return This->lpVtbl->AddRef(This);
}
static inline ULONG IAudioEndpointVolume_Release(IAudioEndpointVolume* This) {
    return This->lpVtbl->Release(This);
}
/*** IAudioEndpointVolume methods ***/
static inline HRESULT IAudioEndpointVolume_RegisterControlChangeNotify(IAudioEndpointVolume* This,IAudioEndpointVolumeCallback *pNotify) {
    return This->lpVtbl->RegisterControlChangeNotify(This,pNotify);
}
static inline HRESULT IAudioEndpointVolume_UnregisterControlChangeNotify(IAudioEndpointVolume* This,IAudioEndpointVolumeCallback *pNotify) {
    return This->lpVtbl->UnregisterControlChangeNotify(This,pNotify);
}
static inline HRESULT IAudioEndpointVolume_GetChannelCount(IAudioEndpointVolume* This,UINT *pnChannelCount) {
    return This->lpVtbl->GetChannelCount(This,pnChannelCount);
}
static inline HRESULT IAudioEndpointVolume_SetMasterVolumeLevel(IAudioEndpointVolume* This,FLOAT fLevelDB,LPCGUID pguidEventContext) {
    return This->lpVtbl->SetMasterVolumeLevel(This,fLevelDB,pguidEventContext);
}
static inline HRESULT IAudioEndpointVolume_SetMasterVolumeLevelScalar(IAudioEndpointVolume* This,FLOAT fLevel,LPCGUID pguidEventContext) {
    return This->lpVtbl->SetMasterVolumeLevelScalar(This,fLevel,pguidEventContext);
}
static inline HRESULT IAudioEndpointVolume_GetMasterVolumeLevel(IAudioEndpointVolume* This,FLOAT *fLevelDB) {
    return This->lpVtbl->GetMasterVolumeLevel(This,fLevelDB);
}
static inline HRESULT IAudioEndpointVolume_GetMasterVolumeLevelScalar(IAudioEndpointVolume* This,FLOAT *fLevel) {
    return This->lpVtbl->GetMasterVolumeLevelScalar(This,fLevel);
}
static inline HRESULT IAudioEndpointVolume_SetChannelVolumeLevel(IAudioEndpointVolume* This,UINT nChannel,FLOAT fLevelDB,LPCGUID pguidEventContext) {
    return This->lpVtbl->SetChannelVolumeLevel(This,nChannel,fLevelDB,pguidEventContext);
}
static inline HRESULT IAudioEndpointVolume_SetChannelVolumeLevelScalar(IAudioEndpointVolume* This,UINT nChannel,FLOAT fLevel,LPCGUID pguidEventContext) {
    return This->lpVtbl->SetChannelVolumeLevelScalar(This,nChannel,fLevel,pguidEventContext);
}
static inline HRESULT IAudioEndpointVolume_GetChannelVolumeLevel(IAudioEndpointVolume* This,UINT nChannel,FLOAT *fLevelDB) {
    return This->lpVtbl->GetChannelVolumeLevel(This,nChannel,fLevelDB);
}
static inline HRESULT IAudioEndpointVolume_GetChannelVolumeLevelScalar(IAudioEndpointVolume* This,UINT nChannel,FLOAT *fLevel) {
    return This->lpVtbl->GetChannelVolumeLevelScalar(This,nChannel,fLevel);
}
static inline HRESULT IAudioEndpointVolume_SetMute(IAudioEndpointVolume* This,WINBOOL bMute,LPCGUID pguidEventContext) {
    return This->lpVtbl->SetMute(This,bMute,pguidEventContext);
}
static inline HRESULT IAudioEndpointVolume_GetMute(IAudioEndpointVolume* This,WINBOOL *bMute) {
    return This->lpVtbl->GetMute(This,bMute);
}
static inline HRESULT IAudioEndpointVolume_GetVolumeStepInfo(IAudioEndpointVolume* This,UINT *pnStep,UINT *pnStepCount) {
    return This->lpVtbl->GetVolumeStepInfo(This,pnStep,pnStepCount);
}
static inline HRESULT IAudioEndpointVolume_VolumeStepUp(IAudioEndpointVolume* This,LPCGUID pguidEventContext) {
    return This->lpVtbl->VolumeStepUp(This,pguidEventContext);
}
static inline HRESULT IAudioEndpointVolume_VolumeStepDown(IAudioEndpointVolume* This,LPCGUID pguidEventContext) {
    return This->lpVtbl->VolumeStepDown(This,pguidEventContext);
}
static inline HRESULT IAudioEndpointVolume_QueryHardwareSupport(IAudioEndpointVolume* This,DWORD *pdwHardwareSupportMask) {
    return This->lpVtbl->QueryHardwareSupport(This,pdwHardwareSupportMask);
}
static inline HRESULT IAudioEndpointVolume_GetVolumeRange(IAudioEndpointVolume* This,FLOAT *pflVolumeMindB,FLOAT *pflVolumeMaxdB,FLOAT *pflVolumeIncrementdB) {
    return This->lpVtbl->GetVolumeRange(This,pflVolumeMindB,pflVolumeMaxdB,pflVolumeIncrementdB);
}
#endif
#endif

#endif


#endif  /* __IAudioEndpointVolume_INTERFACE_DEFINED__ */

/*****************************************************************************
 * IAudioEndpointVolumeEx interface
 */
#ifndef __IAudioEndpointVolumeEx_INTERFACE_DEFINED__
#define __IAudioEndpointVolumeEx_INTERFACE_DEFINED__

DEFINE_GUID(IID_IAudioEndpointVolumeEx, 0x66e11784, 0xf695, 0x4f28, 0xa5,0x05, 0xa7,0x08,0x00,0x81,0xa7,0x8f);
#if defined(__cplusplus) && !defined(CINTERFACE)
MIDL_INTERFACE("66e11784-f695-4f28-a505-a7080081a78f")
IAudioEndpointVolumeEx : public IAudioEndpointVolume
{
    virtual HRESULT STDMETHODCALLTYPE GetVolumeRangeChannel(
        UINT iChannel,
        FLOAT *pflVolumeMindB,
        FLOAT *pflVolumeMaxdB,
        FLOAT *pflVolumeIncrementdB) = 0;

};
#ifdef __CRT_UUID_DECL
__CRT_UUID_DECL(IAudioEndpointVolumeEx, 0x66e11784, 0xf695, 0x4f28, 0xa5,0x05, 0xa7,0x08,0x00,0x81,0xa7,0x8f)
#endif
#else
typedef struct IAudioEndpointVolumeExVtbl {
    BEGIN_INTERFACE

    /*** IUnknown methods ***/
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(
        IAudioEndpointVolumeEx *This,
        REFIID riid,
        void **ppvObject);

    ULONG (STDMETHODCALLTYPE *AddRef)(
        IAudioEndpointVolumeEx *This);

    ULONG (STDMETHODCALLTYPE *Release)(
        IAudioEndpointVolumeEx *This);

    /*** IAudioEndpointVolume methods ***/
    HRESULT (STDMETHODCALLTYPE *RegisterControlChangeNotify)(
        IAudioEndpointVolumeEx *This,
        IAudioEndpointVolumeCallback *pNotify);

    HRESULT (STDMETHODCALLTYPE *UnregisterControlChangeNotify)(
        IAudioEndpointVolumeEx *This,
        IAudioEndpointVolumeCallback *pNotify);

    HRESULT (STDMETHODCALLTYPE *GetChannelCount)(
        IAudioEndpointVolumeEx *This,
        UINT *pnChannelCount);

    HRESULT (STDMETHODCALLTYPE *SetMasterVolumeLevel)(
        IAudioEndpointVolumeEx *This,
        FLOAT fLevelDB,
        LPCGUID pguidEventContext);

    HRESULT (STDMETHODCALLTYPE *SetMasterVolumeLevelScalar)(
        IAudioEndpointVolumeEx *This,
        FLOAT fLevel,
        LPCGUID pguidEventContext);

    HRESULT (STDMETHODCALLTYPE *GetMasterVolumeLevel)(
        IAudioEndpointVolumeEx *This,
        FLOAT *fLevelDB);

    HRESULT (STDMETHODCALLTYPE *GetMasterVolumeLevelScalar)(
        IAudioEndpointVolumeEx *This,
        FLOAT *fLevel);

    HRESULT (STDMETHODCALLTYPE *SetChannelVolumeLevel)(
        IAudioEndpointVolumeEx *This,
        UINT nChannel,
        FLOAT fLevelDB,
        LPCGUID pguidEventContext);

    HRESULT (STDMETHODCALLTYPE *SetChannelVolumeLevelScalar)(
        IAudioEndpointVolumeEx *This,
        UINT nChannel,
        FLOAT fLevel,
        LPCGUID pguidEventContext);

    HRESULT (STDMETHODCALLTYPE *GetChannelVolumeLevel)(
        IAudioEndpointVolumeEx *This,
        UINT nChannel,
        FLOAT *fLevelDB);

    HRESULT (STDMETHODCALLTYPE *GetChannelVolumeLevelScalar)(
        IAudioEndpointVolumeEx *This,
        UINT nChannel,
        FLOAT *fLevel);

    HRESULT (STDMETHODCALLTYPE *SetMute)(
        IAudioEndpointVolumeEx *This,
        WINBOOL bMute,
        LPCGUID pguidEventContext);

    HRESULT (STDMETHODCALLTYPE *GetMute)(
        IAudioEndpointVolumeEx *This,
        WINBOOL *bMute);

    HRESULT (STDMETHODCALLTYPE *GetVolumeStepInfo)(
        IAudioEndpointVolumeEx *This,
        UINT *pnStep,
        UINT *pnStepCount);

    HRESULT (STDMETHODCALLTYPE *VolumeStepUp)(
        IAudioEndpointVolumeEx *This,
        LPCGUID pguidEventContext);

    HRESULT (STDMETHODCALLTYPE *VolumeStepDown)(
        IAudioEndpointVolumeEx *This,
        LPCGUID pguidEventContext);

    HRESULT (STDMETHODCALLTYPE *QueryHardwareSupport)(
        IAudioEndpointVolumeEx *This,
        DWORD *pdwHardwareSupportMask);

    HRESULT (STDMETHODCALLTYPE *GetVolumeRange)(
        IAudioEndpointVolumeEx *This,
        FLOAT *pflVolumeMindB,
        FLOAT *pflVolumeMaxdB,
        FLOAT *pflVolumeIncrementdB);

    /*** IAudioEndpointVolumeEx methods ***/
    HRESULT (STDMETHODCALLTYPE *GetVolumeRangeChannel)(
        IAudioEndpointVolumeEx *This,
        UINT iChannel,
        FLOAT *pflVolumeMindB,
        FLOAT *pflVolumeMaxdB,
        FLOAT *pflVolumeIncrementdB);

    END_INTERFACE
} IAudioEndpointVolumeExVtbl;

interface IAudioEndpointVolumeEx {
    CONST_VTBL IAudioEndpointVolumeExVtbl* lpVtbl;
};

#ifdef COBJMACROS
#ifndef WIDL_C_INLINE_WRAPPERS
/*** IUnknown methods ***/
#define IAudioEndpointVolumeEx_QueryInterface(This,riid,ppvObject) (This)->lpVtbl->QueryInterface(This,riid,ppvObject)
#define IAudioEndpointVolumeEx_AddRef(This) (This)->lpVtbl->AddRef(This)
#define IAudioEndpointVolumeEx_Release(This) (This)->lpVtbl->Release(This)
/*** IAudioEndpointVolume methods ***/
#define IAudioEndpointVolumeEx_RegisterControlChangeNotify(This,pNotify) (This)->lpVtbl->RegisterControlChangeNotify(This,pNotify)
#define IAudioEndpointVolumeEx_UnregisterControlChangeNotify(This,pNotify) (This)->lpVtbl->UnregisterControlChangeNotify(This,pNotify)
#define IAudioEndpointVolumeEx_GetChannelCount(This,pnChannelCount) (This)->lpVtbl->GetChannelCount(This,pnChannelCount)
#define IAudioEndpointVolumeEx_SetMasterVolumeLevel(This,fLevelDB,pguidEventContext) (This)->lpVtbl->SetMasterVolumeLevel(This,fLevelDB,pguidEventContext)
#define IAudioEndpointVolumeEx_SetMasterVolumeLevelScalar(This,fLevel,pguidEventContext) (This)->lpVtbl->SetMasterVolumeLevelScalar(This,fLevel,pguidEventContext)
#define IAudioEndpointVolumeEx_GetMasterVolumeLevel(This,fLevelDB) (This)->lpVtbl->GetMasterVolumeLevel(This,fLevelDB)
#define IAudioEndpointVolumeEx_GetMasterVolumeLevelScalar(This,fLevel) (This)->lpVtbl->GetMasterVolumeLevelScalar(This,fLevel)
#define IAudioEndpointVolumeEx_SetChannelVolumeLevel(This,nChannel,fLevelDB,pguidEventContext) (This)->lpVtbl->SetChannelVolumeLevel(This,nChannel,fLevelDB,pguidEventContext)
#define IAudioEndpointVolumeEx_SetChannelVolumeLevelScalar(This,nChannel,fLevel,pguidEventContext) (This)->lpVtbl->SetChannelVolumeLevelScalar(This,nChannel,fLevel,pguidEventContext)
#define IAudioEndpointVolumeEx_GetChannelVolumeLevel(This,nChannel,fLevelDB) (This)->lpVtbl->GetChannelVolumeLevel(This,nChannel,fLevelDB)
#define IAudioEndpointVolumeEx_GetChannelVolumeLevelScalar(This,nChannel,fLevel) (This)->lpVtbl->GetChannelVolumeLevelScalar(This,nChannel,fLevel)
#define IAudioEndpointVolumeEx_SetMute(This,bMute,pguidEventContext) (This)->lpVtbl->SetMute(This,bMute,pguidEventContext)
#define IAudioEndpointVolumeEx_GetMute(This,bMute) (This)->lpVtbl->GetMute(This,bMute)
#define IAudioEndpointVolumeEx_GetVolumeStepInfo(This,pnStep,pnStepCount) (This)->lpVtbl->GetVolumeStepInfo(This,pnStep,pnStepCount)
#define IAudioEndpointVolumeEx_VolumeStepUp(This,pguidEventContext) (This)->lpVtbl->VolumeStepUp(This,pguidEventContext)
#define IAudioEndpointVolumeEx_VolumeStepDown(This,pguidEventContext) (This)->lpVtbl->VolumeStepDown(This,pguidEventContext)
#define IAudioEndpointVolumeEx_QueryHardwareSupport(This,pdwHardwareSupportMask) (This)->lpVtbl->QueryHardwareSupport(This,pdwHardwareSupportMask)
#define IAudioEndpointVolumeEx_GetVolumeRange(This,pflVolumeMindB,pflVolumeMaxdB,pflVolumeIncrementdB) (This)->lpVtbl->GetVolumeRange(This,pflVolumeMindB,pflVolumeMaxdB,pflVolumeIncrementdB)
/*** IAudioEndpointVolumeEx methods ***/
#define IAudioEndpointVolumeEx_GetVolumeRangeChannel(This,iChannel,pflVolumeMindB,pflVolumeMaxdB,pflVolumeIncrementdB) (This)->lpVtbl->GetVolumeRangeChannel(This,iChannel,pflVolumeMindB,pflVolumeMaxdB,pflVolumeIncrementdB)
#else
/*** IUnknown methods ***/
static inline HRESULT IAudioEndpointVolumeEx_QueryInterface(IAudioEndpointVolumeEx* This,REFIID riid,void **ppvObject) {
    return This->lpVtbl->QueryInterface(This,riid,ppvObject);
}
static inline ULONG IAudioEndpointVolumeEx_AddRef(IAudioEndpointVolumeEx* This) {
    return This->lpVtbl->AddRef(This);
}
static inline ULONG IAudioEndpointVolumeEx_Release(IAudioEndpointVolumeEx* This) {
    return This->lpVtbl->Release(This);
}
/*** IAudioEndpointVolume methods ***/
static inline HRESULT IAudioEndpointVolumeEx_RegisterControlChangeNotify(IAudioEndpointVolumeEx* This,IAudioEndpointVolumeCallback *pNotify) {
    return This->lpVtbl->RegisterControlChangeNotify(This,pNotify);
}
static inline HRESULT IAudioEndpointVolumeEx_UnregisterControlChangeNotify(IAudioEndpointVolumeEx* This,IAudioEndpointVolumeCallback *pNotify) {
    return This->lpVtbl->UnregisterControlChangeNotify(This,pNotify);
}
static inline HRESULT IAudioEndpointVolumeEx_GetChannelCount(IAudioEndpointVolumeEx* This,UINT *pnChannelCount) {
    return This->lpVtbl->GetChannelCount(This,pnChannelCount);
}
static inline HRESULT IAudioEndpointVolumeEx_SetMasterVolumeLevel(IAudioEndpointVolumeEx* This,FLOAT fLevelDB,LPCGUID pguidEventContext) {
    return This->lpVtbl->SetMasterVolumeLevel(This,fLevelDB,pguidEventContext);
}
static inline HRESULT IAudioEndpointVolumeEx_SetMasterVolumeLevelScalar(IAudioEndpointVolumeEx* This,FLOAT fLevel,LPCGUID pguidEventContext) {
    return This->lpVtbl->SetMasterVolumeLevelScalar(This,fLevel,pguidEventContext);
}
static inline HRESULT IAudioEndpointVolumeEx_GetMasterVolumeLevel(IAudioEndpointVolumeEx* This,FLOAT *fLevelDB) {
    return This->lpVtbl->GetMasterVolumeLevel(This,fLevelDB);
}
static inline HRESULT IAudioEndpointVolumeEx_GetMasterVolumeLevelScalar(IAudioEndpointVolumeEx* This,FLOAT *fLevel) {
    return This->lpVtbl->GetMasterVolumeLevelScalar(This,fLevel);
}
static inline HRESULT IAudioEndpointVolumeEx_SetChannelVolumeLevel(IAudioEndpointVolumeEx* This,UINT nChannel,FLOAT fLevelDB,LPCGUID pguidEventContext) {
    return This->lpVtbl->SetChannelVolumeLevel(This,nChannel,fLevelDB,pguidEventContext);
}
static inline HRESULT IAudioEndpointVolumeEx_SetChannelVolumeLevelScalar(IAudioEndpointVolumeEx* This,UINT nChannel,FLOAT fLevel,LPCGUID pguidEventContext) {
    return This->lpVtbl->SetChannelVolumeLevelScalar(This,nChannel,fLevel,pguidEventContext);
}
static inline HRESULT IAudioEndpointVolumeEx_GetChannelVolumeLevel(IAudioEndpointVolumeEx* This,UINT nChannel,FLOAT *fLevelDB) {
    return This->lpVtbl->GetChannelVolumeLevel(This,nChannel,fLevelDB);
}
static inline HRESULT IAudioEndpointVolumeEx_GetChannelVolumeLevelScalar(IAudioEndpointVolumeEx* This,UINT nChannel,FLOAT *fLevel) {
    return This->lpVtbl->GetChannelVolumeLevelScalar(This,nChannel,fLevel);
}
static inline HRESULT IAudioEndpointVolumeEx_SetMute(IAudioEndpointVolumeEx* This,WINBOOL bMute,LPCGUID pguidEventContext) {
    return This->lpVtbl->SetMute(This,bMute,pguidEventContext);
}
static inline HRESULT IAudioEndpointVolumeEx_GetMute(IAudioEndpointVolumeEx* This,WINBOOL *bMute) {
    return This->lpVtbl->GetMute(This,bMute);
}
static inline HRESULT IAudioEndpointVolumeEx_GetVolumeStepInfo(IAudioEndpointVolumeEx* This,UINT *pnStep,UINT *pnStepCount) {
    return This->lpVtbl->GetVolumeStepInfo(This,pnStep,pnStepCount);
}
static inline HRESULT IAudioEndpointVolumeEx_VolumeStepUp(IAudioEndpointVolumeEx* This,LPCGUID pguidEventContext) {
    return This->lpVtbl->VolumeStepUp(This,pguidEventContext);
}
static inline HRESULT IAudioEndpointVolumeEx_VolumeStepDown(IAudioEndpointVolumeEx* This,LPCGUID pguidEventContext) {
    return This->lpVtbl->VolumeStepDown(This,pguidEventContext);
}
static inline HRESULT IAudioEndpointVolumeEx_QueryHardwareSupport(IAudioEndpointVolumeEx* This,DWORD *pdwHardwareSupportMask) {
    return This->lpVtbl->QueryHardwareSupport(This,pdwHardwareSupportMask);
}
static inline HRESULT IAudioEndpointVolumeEx_GetVolumeRange(IAudioEndpointVolumeEx* This,FLOAT *pflVolumeMindB,FLOAT *pflVolumeMaxdB,FLOAT *pflVolumeIncrementdB) {
    return This->lpVtbl->GetVolumeRange(This,pflVolumeMindB,pflVolumeMaxdB,pflVolumeIncrementdB);
}
/*** IAudioEndpointVolumeEx methods ***/
static inline HRESULT IAudioEndpointVolumeEx_GetVolumeRangeChannel(IAudioEndpointVolumeEx* This,UINT iChannel,FLOAT *pflVolumeMindB,FLOAT *pflVolumeMaxdB,FLOAT *pflVolumeIncrementdB) {
    return This->lpVtbl->GetVolumeRangeChannel(This,iChannel,pflVolumeMindB,pflVolumeMaxdB,pflVolumeIncrementdB);
}
#endif
#endif

#endif


#endif  /* __IAudioEndpointVolumeEx_INTERFACE_DEFINED__ */

/* Begin additional prototypes for all interfaces */


/* End additional prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __endpointvolume_h__ */
