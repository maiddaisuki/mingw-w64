/*** Autogenerated by WIDL 10.12 from include/mmdeviceapi.idl - Do not edit ***/

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

#ifndef __mmdeviceapi_h__
#define __mmdeviceapi_h__

/* Forward declarations */

#ifndef __IMMNotificationClient_FWD_DEFINED__
#define __IMMNotificationClient_FWD_DEFINED__
typedef interface IMMNotificationClient IMMNotificationClient;
#ifdef __cplusplus
interface IMMNotificationClient;
#endif /* __cplusplus */
#endif

#ifndef __IMMDevice_FWD_DEFINED__
#define __IMMDevice_FWD_DEFINED__
typedef interface IMMDevice IMMDevice;
#ifdef __cplusplus
interface IMMDevice;
#endif /* __cplusplus */
#endif

#ifndef __IMMDeviceCollection_FWD_DEFINED__
#define __IMMDeviceCollection_FWD_DEFINED__
typedef interface IMMDeviceCollection IMMDeviceCollection;
#ifdef __cplusplus
interface IMMDeviceCollection;
#endif /* __cplusplus */
#endif

#ifndef __IMMEndpoint_FWD_DEFINED__
#define __IMMEndpoint_FWD_DEFINED__
typedef interface IMMEndpoint IMMEndpoint;
#ifdef __cplusplus
interface IMMEndpoint;
#endif /* __cplusplus */
#endif

#ifndef __IMMDeviceEnumerator_FWD_DEFINED__
#define __IMMDeviceEnumerator_FWD_DEFINED__
typedef interface IMMDeviceEnumerator IMMDeviceEnumerator;
#ifdef __cplusplus
interface IMMDeviceEnumerator;
#endif /* __cplusplus */
#endif

#ifndef __IMMDeviceActivator_FWD_DEFINED__
#define __IMMDeviceActivator_FWD_DEFINED__
typedef interface IMMDeviceActivator IMMDeviceActivator;
#ifdef __cplusplus
interface IMMDeviceActivator;
#endif /* __cplusplus */
#endif

#ifndef __IActivateAudioInterfaceAsyncOperation_FWD_DEFINED__
#define __IActivateAudioInterfaceAsyncOperation_FWD_DEFINED__
typedef interface IActivateAudioInterfaceAsyncOperation IActivateAudioInterfaceAsyncOperation;
#ifdef __cplusplus
interface IActivateAudioInterfaceAsyncOperation;
#endif /* __cplusplus */
#endif

#ifndef __IActivateAudioInterfaceCompletionHandler_FWD_DEFINED__
#define __IActivateAudioInterfaceCompletionHandler_FWD_DEFINED__
typedef interface IActivateAudioInterfaceCompletionHandler IActivateAudioInterfaceCompletionHandler;
#ifdef __cplusplus
interface IActivateAudioInterfaceCompletionHandler;
#endif /* __cplusplus */
#endif

#ifndef __MMDeviceEnumerator_FWD_DEFINED__
#define __MMDeviceEnumerator_FWD_DEFINED__
#ifdef __cplusplus
typedef class MMDeviceEnumerator MMDeviceEnumerator;
#else
typedef struct MMDeviceEnumerator MMDeviceEnumerator;
#endif /* defined __cplusplus */
#endif /* defined __MMDeviceEnumerator_FWD_DEFINED__ */

/* Headers for imported files */

#include <unknwn.h>
#include <propsys.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef E_NOTFOUND
#define E_NOTFOUND HRESULT_FROM_WIN32(ERROR_NOT_FOUND)
#endif
#ifndef E_UNSUPPORTED_TYPE
#define E_UNSUPPORTED_TYPE HRESULT_FROM_WIN32(ERROR_UNSUPPORTED_TYPE)
#endif
DEFINE_GUID(DEVINTERFACE_AUDIO_RENDER, 0xe6327cad,0xdcec,0x4949,0xae,0x8a,0x99,0x1e,0x97,0x6a,0x79,0xd2);
DEFINE_GUID(DEVINTERFACE_AUDIO_CAPTURE, 0x2eef81be,0x33fa,0x4800,0x96,0x70,0x1c,0xd4,0x74,0x97,0x2c,0x3f);
#define DEVICE_STATE_ACTIVE 0x1
#define DEVICE_STATE_DISABLED 0x2
#define DEVICE_STATE_NOTPRESENT 0x4
#define DEVICE_STATE_UNPLUGGED 0x8
#define DEVICE_STATEMASK_ALL 0xf
DEFINE_PROPERTYKEY(PKEY_AudioEndpoint_FormFactor,0x1da5d803,0xd492,0x4edd,0x8c,0x23,0xe0,0xc0,0xff,0xee,0x7f,0x0e,0);
DEFINE_PROPERTYKEY(PKEY_AudioEndpoint_ControlPanelPageProvider,0x1da5d803,0xd492,0x4edd,0x8c,0x23,0xe0,0xc0,0xff,0xee,0x7f,0x0e,1);
DEFINE_PROPERTYKEY(PKEY_AudioEndpoint_Association,0x1da5d803,0xd492,0x4edd,0x8c,0x23,0xe0,0xc0,0xff,0xee,0x7f,0x0e,2);
DEFINE_PROPERTYKEY(PKEY_AudioEndpoint_PhysicalSpeakers,0x1da5d803,0xd492,0x4edd,0x8c,0x23,0xe0,0xc0,0xff,0xee,0x7f,0x0e,3);
DEFINE_PROPERTYKEY(PKEY_AudioEndpoint_GUID,0x1da5d803,0xd492,0x4edd,0x8c,0x23,0xe0,0xc0,0xff,0xee,0x7f,0x0e,4);
DEFINE_PROPERTYKEY(PKEY_AudioEndpoint_Disable_SysFx,0x1da5d803,0xd492,0x4edd,0x8c,0x23,0xe0,0xc0,0xff,0xee,0x7f,0x0e,5);
#define ENDPOINT_SYSFX_ENABLED 0
#define ENDPOINT_SYSFX_DISABLED 1
DEFINE_PROPERTYKEY(PKEY_AudioEndpoint_FullRangeSpeakers,0x1da5d803,0xd492,0x4edd,0x8c,0x23,0xe0,0xc0,0xff,0xee,0x7f,0x0e,6);
DEFINE_PROPERTYKEY(PKEY_AudioEndpoint_Supports_EventDriven_Mode,0x1da5d803,0xd492,0x4edd,0x8c,0x23,0xe0,0xc0,0xff,0xee,0x7f,0x0e,7);
DEFINE_PROPERTYKEY(PKEY_AudioEndpoint_JackSubType,0x1da5d803,0xd492,0x4edd,0x8c,0x23,0xe0,0xc0,0xff,0xee,0x7f,0x0e,8);
DEFINE_PROPERTYKEY(PKEY_AudioEngine_DeviceFormat,0xf19f064d,0x082c,0x4e27,0xbc,0x73,0x68,0x82,0xa1,0xbb,0x8e,0x4c,0);
DEFINE_PROPERTYKEY(PKEY_AudioEngine_OEMFormat,0xe4870e26,0x3cc5,0x4cd2,0xba,0x46,0xca,0x0a,0x9a,0x70,0xed,0x04,3);
typedef struct tagDIRECTX_AUDIO_ACTIVATION_PARAMS {
    DWORD cbDirectXAudioActivationParams;
    GUID guidAudioSession;
    DWORD dwAudioStreamFlags;
} DIRECTX_AUDIO_ACTIVATION_PARAMS;
typedef struct tagDIRECTX_AUDIO_ACTIVATION_PARAMS *PDIRECTX_AUDIO_ACTIVATION_PARAMS;
typedef enum _EDataFlow {
    eRender = 0,
    eCapture = 1,
    eAll = 2,
    EDataFlow_enum_count = 3
} EDataFlow;
typedef enum _ERole {
    eConsole = 0,
    eMultimedia = 1,
    eCommunications = 2,
    ERole_enum_count = 3
} ERole;
typedef enum _EndpointFormFactor {
    RemoteNetworkDevice = 0,
    Speakers = 1,
    LineLevel = 2,
    Headphones = 3,
    Microphone = 4,
    Headset = 5,
    Handset = 6,
    UnknownDigitalPassthrough = 7,
    SPDIF = 8,
    DigitalAudioDisplayDevice = 9,
    UnknownFormFactor = 10,
    EndpointFormFactor_enum_count = 11
} EndpointFormFactor;
#define HDMI DigitalAudioDisplayDevice
/*****************************************************************************
 * IMMNotificationClient interface
 */
#ifndef __IMMNotificationClient_INTERFACE_DEFINED__
#define __IMMNotificationClient_INTERFACE_DEFINED__

DEFINE_GUID(IID_IMMNotificationClient, 0x7991eec9, 0x7e89, 0x4d85, 0x83,0x90, 0x6c,0x70,0x3c,0xec,0x60,0xc0);
#if defined(__cplusplus) && !defined(CINTERFACE)
MIDL_INTERFACE("7991eec9-7e89-4d85-8390-6c703cec60c0")
IMMNotificationClient : public IUnknown
{
    virtual HRESULT STDMETHODCALLTYPE OnDeviceStateChanged(
        LPCWSTR pwstrDeviceId,
        DWORD dwNewState) = 0;

    virtual HRESULT STDMETHODCALLTYPE OnDeviceAdded(
        LPCWSTR pwstrDeviceId) = 0;

    virtual HRESULT STDMETHODCALLTYPE OnDeviceRemoved(
        LPCWSTR pwstrDeviceId) = 0;

    virtual HRESULT STDMETHODCALLTYPE OnDefaultDeviceChanged(
        EDataFlow flow,
        ERole role,
        LPCWSTR pwstrDeviceId) = 0;

    virtual HRESULT STDMETHODCALLTYPE OnPropertyValueChanged(
        LPCWSTR pwstrDeviceId,
        const PROPERTYKEY key) = 0;

};
#ifdef __CRT_UUID_DECL
__CRT_UUID_DECL(IMMNotificationClient, 0x7991eec9, 0x7e89, 0x4d85, 0x83,0x90, 0x6c,0x70,0x3c,0xec,0x60,0xc0)
#endif
#else
typedef struct IMMNotificationClientVtbl {
    BEGIN_INTERFACE

    /*** IUnknown methods ***/
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(
        IMMNotificationClient *This,
        REFIID riid,
        void **ppvObject);

    ULONG (STDMETHODCALLTYPE *AddRef)(
        IMMNotificationClient *This);

    ULONG (STDMETHODCALLTYPE *Release)(
        IMMNotificationClient *This);

    /*** IMMNotificationClient methods ***/
    HRESULT (STDMETHODCALLTYPE *OnDeviceStateChanged)(
        IMMNotificationClient *This,
        LPCWSTR pwstrDeviceId,
        DWORD dwNewState);

    HRESULT (STDMETHODCALLTYPE *OnDeviceAdded)(
        IMMNotificationClient *This,
        LPCWSTR pwstrDeviceId);

    HRESULT (STDMETHODCALLTYPE *OnDeviceRemoved)(
        IMMNotificationClient *This,
        LPCWSTR pwstrDeviceId);

    HRESULT (STDMETHODCALLTYPE *OnDefaultDeviceChanged)(
        IMMNotificationClient *This,
        EDataFlow flow,
        ERole role,
        LPCWSTR pwstrDeviceId);

    HRESULT (STDMETHODCALLTYPE *OnPropertyValueChanged)(
        IMMNotificationClient *This,
        LPCWSTR pwstrDeviceId,
        const PROPERTYKEY key);

    END_INTERFACE
} IMMNotificationClientVtbl;

interface IMMNotificationClient {
    CONST_VTBL IMMNotificationClientVtbl* lpVtbl;
};

#ifdef COBJMACROS
#ifndef WIDL_C_INLINE_WRAPPERS
/*** IUnknown methods ***/
#define IMMNotificationClient_QueryInterface(This,riid,ppvObject) (This)->lpVtbl->QueryInterface(This,riid,ppvObject)
#define IMMNotificationClient_AddRef(This) (This)->lpVtbl->AddRef(This)
#define IMMNotificationClient_Release(This) (This)->lpVtbl->Release(This)
/*** IMMNotificationClient methods ***/
#define IMMNotificationClient_OnDeviceStateChanged(This,pwstrDeviceId,dwNewState) (This)->lpVtbl->OnDeviceStateChanged(This,pwstrDeviceId,dwNewState)
#define IMMNotificationClient_OnDeviceAdded(This,pwstrDeviceId) (This)->lpVtbl->OnDeviceAdded(This,pwstrDeviceId)
#define IMMNotificationClient_OnDeviceRemoved(This,pwstrDeviceId) (This)->lpVtbl->OnDeviceRemoved(This,pwstrDeviceId)
#define IMMNotificationClient_OnDefaultDeviceChanged(This,flow,role,pwstrDeviceId) (This)->lpVtbl->OnDefaultDeviceChanged(This,flow,role,pwstrDeviceId)
#define IMMNotificationClient_OnPropertyValueChanged(This,pwstrDeviceId,key) (This)->lpVtbl->OnPropertyValueChanged(This,pwstrDeviceId,key)
#else
/*** IUnknown methods ***/
static inline HRESULT IMMNotificationClient_QueryInterface(IMMNotificationClient* This,REFIID riid,void **ppvObject) {
    return This->lpVtbl->QueryInterface(This,riid,ppvObject);
}
static inline ULONG IMMNotificationClient_AddRef(IMMNotificationClient* This) {
    return This->lpVtbl->AddRef(This);
}
static inline ULONG IMMNotificationClient_Release(IMMNotificationClient* This) {
    return This->lpVtbl->Release(This);
}
/*** IMMNotificationClient methods ***/
static inline HRESULT IMMNotificationClient_OnDeviceStateChanged(IMMNotificationClient* This,LPCWSTR pwstrDeviceId,DWORD dwNewState) {
    return This->lpVtbl->OnDeviceStateChanged(This,pwstrDeviceId,dwNewState);
}
static inline HRESULT IMMNotificationClient_OnDeviceAdded(IMMNotificationClient* This,LPCWSTR pwstrDeviceId) {
    return This->lpVtbl->OnDeviceAdded(This,pwstrDeviceId);
}
static inline HRESULT IMMNotificationClient_OnDeviceRemoved(IMMNotificationClient* This,LPCWSTR pwstrDeviceId) {
    return This->lpVtbl->OnDeviceRemoved(This,pwstrDeviceId);
}
static inline HRESULT IMMNotificationClient_OnDefaultDeviceChanged(IMMNotificationClient* This,EDataFlow flow,ERole role,LPCWSTR pwstrDeviceId) {
    return This->lpVtbl->OnDefaultDeviceChanged(This,flow,role,pwstrDeviceId);
}
static inline HRESULT IMMNotificationClient_OnPropertyValueChanged(IMMNotificationClient* This,LPCWSTR pwstrDeviceId,const PROPERTYKEY key) {
    return This->lpVtbl->OnPropertyValueChanged(This,pwstrDeviceId,key);
}
#endif
#endif

#endif


#endif  /* __IMMNotificationClient_INTERFACE_DEFINED__ */

/*****************************************************************************
 * IMMDevice interface
 */
#ifndef __IMMDevice_INTERFACE_DEFINED__
#define __IMMDevice_INTERFACE_DEFINED__

DEFINE_GUID(IID_IMMDevice, 0xd666063f, 0x1587, 0x4e43, 0x81,0xf1, 0xb9,0x48,0xe8,0x07,0x36,0x3f);
#if defined(__cplusplus) && !defined(CINTERFACE)
MIDL_INTERFACE("d666063f-1587-4e43-81f1-b948e807363f")
IMMDevice : public IUnknown
{
    virtual HRESULT STDMETHODCALLTYPE Activate(
        REFIID iid,
        DWORD dwClsCtx,
        PROPVARIANT *pActivationParams,
        void **ppv) = 0;

    virtual HRESULT STDMETHODCALLTYPE OpenPropertyStore(
        DWORD stgmAccess,
        IPropertyStore **ppProperties) = 0;

    virtual HRESULT STDMETHODCALLTYPE GetId(
        LPWSTR *ppstrId) = 0;

    virtual HRESULT STDMETHODCALLTYPE GetState(
        DWORD *pdwState) = 0;

};
#ifdef __CRT_UUID_DECL
__CRT_UUID_DECL(IMMDevice, 0xd666063f, 0x1587, 0x4e43, 0x81,0xf1, 0xb9,0x48,0xe8,0x07,0x36,0x3f)
#endif
#else
typedef struct IMMDeviceVtbl {
    BEGIN_INTERFACE

    /*** IUnknown methods ***/
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(
        IMMDevice *This,
        REFIID riid,
        void **ppvObject);

    ULONG (STDMETHODCALLTYPE *AddRef)(
        IMMDevice *This);

    ULONG (STDMETHODCALLTYPE *Release)(
        IMMDevice *This);

    /*** IMMDevice methods ***/
    HRESULT (STDMETHODCALLTYPE *Activate)(
        IMMDevice *This,
        REFIID iid,
        DWORD dwClsCtx,
        PROPVARIANT *pActivationParams,
        void **ppv);

    HRESULT (STDMETHODCALLTYPE *OpenPropertyStore)(
        IMMDevice *This,
        DWORD stgmAccess,
        IPropertyStore **ppProperties);

    HRESULT (STDMETHODCALLTYPE *GetId)(
        IMMDevice *This,
        LPWSTR *ppstrId);

    HRESULT (STDMETHODCALLTYPE *GetState)(
        IMMDevice *This,
        DWORD *pdwState);

    END_INTERFACE
} IMMDeviceVtbl;

interface IMMDevice {
    CONST_VTBL IMMDeviceVtbl* lpVtbl;
};

#ifdef COBJMACROS
#ifndef WIDL_C_INLINE_WRAPPERS
/*** IUnknown methods ***/
#define IMMDevice_QueryInterface(This,riid,ppvObject) (This)->lpVtbl->QueryInterface(This,riid,ppvObject)
#define IMMDevice_AddRef(This) (This)->lpVtbl->AddRef(This)
#define IMMDevice_Release(This) (This)->lpVtbl->Release(This)
/*** IMMDevice methods ***/
#define IMMDevice_Activate(This,iid,dwClsCtx,pActivationParams,ppv) (This)->lpVtbl->Activate(This,iid,dwClsCtx,pActivationParams,ppv)
#define IMMDevice_OpenPropertyStore(This,stgmAccess,ppProperties) (This)->lpVtbl->OpenPropertyStore(This,stgmAccess,ppProperties)
#define IMMDevice_GetId(This,ppstrId) (This)->lpVtbl->GetId(This,ppstrId)
#define IMMDevice_GetState(This,pdwState) (This)->lpVtbl->GetState(This,pdwState)
#else
/*** IUnknown methods ***/
static inline HRESULT IMMDevice_QueryInterface(IMMDevice* This,REFIID riid,void **ppvObject) {
    return This->lpVtbl->QueryInterface(This,riid,ppvObject);
}
static inline ULONG IMMDevice_AddRef(IMMDevice* This) {
    return This->lpVtbl->AddRef(This);
}
static inline ULONG IMMDevice_Release(IMMDevice* This) {
    return This->lpVtbl->Release(This);
}
/*** IMMDevice methods ***/
static inline HRESULT IMMDevice_Activate(IMMDevice* This,REFIID iid,DWORD dwClsCtx,PROPVARIANT *pActivationParams,void **ppv) {
    return This->lpVtbl->Activate(This,iid,dwClsCtx,pActivationParams,ppv);
}
static inline HRESULT IMMDevice_OpenPropertyStore(IMMDevice* This,DWORD stgmAccess,IPropertyStore **ppProperties) {
    return This->lpVtbl->OpenPropertyStore(This,stgmAccess,ppProperties);
}
static inline HRESULT IMMDevice_GetId(IMMDevice* This,LPWSTR *ppstrId) {
    return This->lpVtbl->GetId(This,ppstrId);
}
static inline HRESULT IMMDevice_GetState(IMMDevice* This,DWORD *pdwState) {
    return This->lpVtbl->GetState(This,pdwState);
}
#endif
#endif

#endif


#endif  /* __IMMDevice_INTERFACE_DEFINED__ */

/*****************************************************************************
 * IMMDeviceCollection interface
 */
#ifndef __IMMDeviceCollection_INTERFACE_DEFINED__
#define __IMMDeviceCollection_INTERFACE_DEFINED__

DEFINE_GUID(IID_IMMDeviceCollection, 0x0bd7a1be, 0x7a1a, 0x44db, 0x83,0x97, 0xcc,0x53,0x92,0x38,0x7b,0x5e);
#if defined(__cplusplus) && !defined(CINTERFACE)
MIDL_INTERFACE("0bd7a1be-7a1a-44db-8397-cc5392387b5e")
IMMDeviceCollection : public IUnknown
{
    virtual HRESULT STDMETHODCALLTYPE GetCount(
        UINT *pcDevices) = 0;

    virtual HRESULT STDMETHODCALLTYPE Item(
        UINT nDevice,
        IMMDevice **ppdevice) = 0;

};
#ifdef __CRT_UUID_DECL
__CRT_UUID_DECL(IMMDeviceCollection, 0x0bd7a1be, 0x7a1a, 0x44db, 0x83,0x97, 0xcc,0x53,0x92,0x38,0x7b,0x5e)
#endif
#else
typedef struct IMMDeviceCollectionVtbl {
    BEGIN_INTERFACE

    /*** IUnknown methods ***/
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(
        IMMDeviceCollection *This,
        REFIID riid,
        void **ppvObject);

    ULONG (STDMETHODCALLTYPE *AddRef)(
        IMMDeviceCollection *This);

    ULONG (STDMETHODCALLTYPE *Release)(
        IMMDeviceCollection *This);

    /*** IMMDeviceCollection methods ***/
    HRESULT (STDMETHODCALLTYPE *GetCount)(
        IMMDeviceCollection *This,
        UINT *pcDevices);

    HRESULT (STDMETHODCALLTYPE *Item)(
        IMMDeviceCollection *This,
        UINT nDevice,
        IMMDevice **ppdevice);

    END_INTERFACE
} IMMDeviceCollectionVtbl;

interface IMMDeviceCollection {
    CONST_VTBL IMMDeviceCollectionVtbl* lpVtbl;
};

#ifdef COBJMACROS
#ifndef WIDL_C_INLINE_WRAPPERS
/*** IUnknown methods ***/
#define IMMDeviceCollection_QueryInterface(This,riid,ppvObject) (This)->lpVtbl->QueryInterface(This,riid,ppvObject)
#define IMMDeviceCollection_AddRef(This) (This)->lpVtbl->AddRef(This)
#define IMMDeviceCollection_Release(This) (This)->lpVtbl->Release(This)
/*** IMMDeviceCollection methods ***/
#define IMMDeviceCollection_GetCount(This,pcDevices) (This)->lpVtbl->GetCount(This,pcDevices)
#define IMMDeviceCollection_Item(This,nDevice,ppdevice) (This)->lpVtbl->Item(This,nDevice,ppdevice)
#else
/*** IUnknown methods ***/
static inline HRESULT IMMDeviceCollection_QueryInterface(IMMDeviceCollection* This,REFIID riid,void **ppvObject) {
    return This->lpVtbl->QueryInterface(This,riid,ppvObject);
}
static inline ULONG IMMDeviceCollection_AddRef(IMMDeviceCollection* This) {
    return This->lpVtbl->AddRef(This);
}
static inline ULONG IMMDeviceCollection_Release(IMMDeviceCollection* This) {
    return This->lpVtbl->Release(This);
}
/*** IMMDeviceCollection methods ***/
static inline HRESULT IMMDeviceCollection_GetCount(IMMDeviceCollection* This,UINT *pcDevices) {
    return This->lpVtbl->GetCount(This,pcDevices);
}
static inline HRESULT IMMDeviceCollection_Item(IMMDeviceCollection* This,UINT nDevice,IMMDevice **ppdevice) {
    return This->lpVtbl->Item(This,nDevice,ppdevice);
}
#endif
#endif

#endif


#endif  /* __IMMDeviceCollection_INTERFACE_DEFINED__ */

/*****************************************************************************
 * IMMEndpoint interface
 */
#ifndef __IMMEndpoint_INTERFACE_DEFINED__
#define __IMMEndpoint_INTERFACE_DEFINED__

DEFINE_GUID(IID_IMMEndpoint, 0x1be09788, 0x6894, 0x4089, 0x85,0x86, 0x9a,0x2a,0x6c,0x26,0x5a,0xc5);
#if defined(__cplusplus) && !defined(CINTERFACE)
MIDL_INTERFACE("1be09788-6894-4089-8586-9a2a6c265ac5")
IMMEndpoint : public IUnknown
{
    virtual HRESULT STDMETHODCALLTYPE GetDataFlow(
        EDataFlow *pDataFlow) = 0;

};
#ifdef __CRT_UUID_DECL
__CRT_UUID_DECL(IMMEndpoint, 0x1be09788, 0x6894, 0x4089, 0x85,0x86, 0x9a,0x2a,0x6c,0x26,0x5a,0xc5)
#endif
#else
typedef struct IMMEndpointVtbl {
    BEGIN_INTERFACE

    /*** IUnknown methods ***/
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(
        IMMEndpoint *This,
        REFIID riid,
        void **ppvObject);

    ULONG (STDMETHODCALLTYPE *AddRef)(
        IMMEndpoint *This);

    ULONG (STDMETHODCALLTYPE *Release)(
        IMMEndpoint *This);

    /*** IMMEndpoint methods ***/
    HRESULT (STDMETHODCALLTYPE *GetDataFlow)(
        IMMEndpoint *This,
        EDataFlow *pDataFlow);

    END_INTERFACE
} IMMEndpointVtbl;

interface IMMEndpoint {
    CONST_VTBL IMMEndpointVtbl* lpVtbl;
};

#ifdef COBJMACROS
#ifndef WIDL_C_INLINE_WRAPPERS
/*** IUnknown methods ***/
#define IMMEndpoint_QueryInterface(This,riid,ppvObject) (This)->lpVtbl->QueryInterface(This,riid,ppvObject)
#define IMMEndpoint_AddRef(This) (This)->lpVtbl->AddRef(This)
#define IMMEndpoint_Release(This) (This)->lpVtbl->Release(This)
/*** IMMEndpoint methods ***/
#define IMMEndpoint_GetDataFlow(This,pDataFlow) (This)->lpVtbl->GetDataFlow(This,pDataFlow)
#else
/*** IUnknown methods ***/
static inline HRESULT IMMEndpoint_QueryInterface(IMMEndpoint* This,REFIID riid,void **ppvObject) {
    return This->lpVtbl->QueryInterface(This,riid,ppvObject);
}
static inline ULONG IMMEndpoint_AddRef(IMMEndpoint* This) {
    return This->lpVtbl->AddRef(This);
}
static inline ULONG IMMEndpoint_Release(IMMEndpoint* This) {
    return This->lpVtbl->Release(This);
}
/*** IMMEndpoint methods ***/
static inline HRESULT IMMEndpoint_GetDataFlow(IMMEndpoint* This,EDataFlow *pDataFlow) {
    return This->lpVtbl->GetDataFlow(This,pDataFlow);
}
#endif
#endif

#endif


#endif  /* __IMMEndpoint_INTERFACE_DEFINED__ */

/*****************************************************************************
 * IMMDeviceEnumerator interface
 */
#ifndef __IMMDeviceEnumerator_INTERFACE_DEFINED__
#define __IMMDeviceEnumerator_INTERFACE_DEFINED__

DEFINE_GUID(IID_IMMDeviceEnumerator, 0xa95664d2, 0x9614, 0x4f35, 0xa7,0x46, 0xde,0x8d,0xb6,0x36,0x17,0xe6);
#if defined(__cplusplus) && !defined(CINTERFACE)
MIDL_INTERFACE("a95664d2-9614-4f35-a746-de8db63617e6")
IMMDeviceEnumerator : public IUnknown
{
    virtual HRESULT STDMETHODCALLTYPE EnumAudioEndpoints(
        EDataFlow dataFlow,
        DWORD dwStateMask,
        IMMDeviceCollection **ppDevices) = 0;

    virtual HRESULT STDMETHODCALLTYPE GetDefaultAudioEndpoint(
        EDataFlow dataFlow,
        ERole role,
        IMMDevice **ppEndpoint) = 0;

    virtual HRESULT STDMETHODCALLTYPE GetDevice(
        LPCWSTR pwstrId,
        IMMDevice **ppDevice) = 0;

    virtual HRESULT STDMETHODCALLTYPE RegisterEndpointNotificationCallback(
        IMMNotificationClient *pClient) = 0;

    virtual HRESULT STDMETHODCALLTYPE UnregisterEndpointNotificationCallback(
        IMMNotificationClient *pClient) = 0;

};
#ifdef __CRT_UUID_DECL
__CRT_UUID_DECL(IMMDeviceEnumerator, 0xa95664d2, 0x9614, 0x4f35, 0xa7,0x46, 0xde,0x8d,0xb6,0x36,0x17,0xe6)
#endif
#else
typedef struct IMMDeviceEnumeratorVtbl {
    BEGIN_INTERFACE

    /*** IUnknown methods ***/
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(
        IMMDeviceEnumerator *This,
        REFIID riid,
        void **ppvObject);

    ULONG (STDMETHODCALLTYPE *AddRef)(
        IMMDeviceEnumerator *This);

    ULONG (STDMETHODCALLTYPE *Release)(
        IMMDeviceEnumerator *This);

    /*** IMMDeviceEnumerator methods ***/
    HRESULT (STDMETHODCALLTYPE *EnumAudioEndpoints)(
        IMMDeviceEnumerator *This,
        EDataFlow dataFlow,
        DWORD dwStateMask,
        IMMDeviceCollection **ppDevices);

    HRESULT (STDMETHODCALLTYPE *GetDefaultAudioEndpoint)(
        IMMDeviceEnumerator *This,
        EDataFlow dataFlow,
        ERole role,
        IMMDevice **ppEndpoint);

    HRESULT (STDMETHODCALLTYPE *GetDevice)(
        IMMDeviceEnumerator *This,
        LPCWSTR pwstrId,
        IMMDevice **ppDevice);

    HRESULT (STDMETHODCALLTYPE *RegisterEndpointNotificationCallback)(
        IMMDeviceEnumerator *This,
        IMMNotificationClient *pClient);

    HRESULT (STDMETHODCALLTYPE *UnregisterEndpointNotificationCallback)(
        IMMDeviceEnumerator *This,
        IMMNotificationClient *pClient);

    END_INTERFACE
} IMMDeviceEnumeratorVtbl;

interface IMMDeviceEnumerator {
    CONST_VTBL IMMDeviceEnumeratorVtbl* lpVtbl;
};

#ifdef COBJMACROS
#ifndef WIDL_C_INLINE_WRAPPERS
/*** IUnknown methods ***/
#define IMMDeviceEnumerator_QueryInterface(This,riid,ppvObject) (This)->lpVtbl->QueryInterface(This,riid,ppvObject)
#define IMMDeviceEnumerator_AddRef(This) (This)->lpVtbl->AddRef(This)
#define IMMDeviceEnumerator_Release(This) (This)->lpVtbl->Release(This)
/*** IMMDeviceEnumerator methods ***/
#define IMMDeviceEnumerator_EnumAudioEndpoints(This,dataFlow,dwStateMask,ppDevices) (This)->lpVtbl->EnumAudioEndpoints(This,dataFlow,dwStateMask,ppDevices)
#define IMMDeviceEnumerator_GetDefaultAudioEndpoint(This,dataFlow,role,ppEndpoint) (This)->lpVtbl->GetDefaultAudioEndpoint(This,dataFlow,role,ppEndpoint)
#define IMMDeviceEnumerator_GetDevice(This,pwstrId,ppDevice) (This)->lpVtbl->GetDevice(This,pwstrId,ppDevice)
#define IMMDeviceEnumerator_RegisterEndpointNotificationCallback(This,pClient) (This)->lpVtbl->RegisterEndpointNotificationCallback(This,pClient)
#define IMMDeviceEnumerator_UnregisterEndpointNotificationCallback(This,pClient) (This)->lpVtbl->UnregisterEndpointNotificationCallback(This,pClient)
#else
/*** IUnknown methods ***/
static inline HRESULT IMMDeviceEnumerator_QueryInterface(IMMDeviceEnumerator* This,REFIID riid,void **ppvObject) {
    return This->lpVtbl->QueryInterface(This,riid,ppvObject);
}
static inline ULONG IMMDeviceEnumerator_AddRef(IMMDeviceEnumerator* This) {
    return This->lpVtbl->AddRef(This);
}
static inline ULONG IMMDeviceEnumerator_Release(IMMDeviceEnumerator* This) {
    return This->lpVtbl->Release(This);
}
/*** IMMDeviceEnumerator methods ***/
static inline HRESULT IMMDeviceEnumerator_EnumAudioEndpoints(IMMDeviceEnumerator* This,EDataFlow dataFlow,DWORD dwStateMask,IMMDeviceCollection **ppDevices) {
    return This->lpVtbl->EnumAudioEndpoints(This,dataFlow,dwStateMask,ppDevices);
}
static inline HRESULT IMMDeviceEnumerator_GetDefaultAudioEndpoint(IMMDeviceEnumerator* This,EDataFlow dataFlow,ERole role,IMMDevice **ppEndpoint) {
    return This->lpVtbl->GetDefaultAudioEndpoint(This,dataFlow,role,ppEndpoint);
}
static inline HRESULT IMMDeviceEnumerator_GetDevice(IMMDeviceEnumerator* This,LPCWSTR pwstrId,IMMDevice **ppDevice) {
    return This->lpVtbl->GetDevice(This,pwstrId,ppDevice);
}
static inline HRESULT IMMDeviceEnumerator_RegisterEndpointNotificationCallback(IMMDeviceEnumerator* This,IMMNotificationClient *pClient) {
    return This->lpVtbl->RegisterEndpointNotificationCallback(This,pClient);
}
static inline HRESULT IMMDeviceEnumerator_UnregisterEndpointNotificationCallback(IMMDeviceEnumerator* This,IMMNotificationClient *pClient) {
    return This->lpVtbl->UnregisterEndpointNotificationCallback(This,pClient);
}
#endif
#endif

#endif


#endif  /* __IMMDeviceEnumerator_INTERFACE_DEFINED__ */

/*****************************************************************************
 * IMMDeviceActivator interface
 */
#ifndef __IMMDeviceActivator_INTERFACE_DEFINED__
#define __IMMDeviceActivator_INTERFACE_DEFINED__

DEFINE_GUID(IID_IMMDeviceActivator, 0x3b0d0ea4, 0xd0a9, 0x4b0e, 0x93,0x5b, 0x09,0x51,0x67,0x46,0xfa,0xc0);
#if defined(__cplusplus) && !defined(CINTERFACE)
MIDL_INTERFACE("3b0d0ea4-d0a9-4b0e-935b-09516746fac0")
IMMDeviceActivator : public IUnknown
{
    virtual HRESULT STDMETHODCALLTYPE Activate(
        REFIID iid,
        IMMDevice *pDevice,
        PROPVARIANT *pActivationParams,
        void **ppv) = 0;

};
#ifdef __CRT_UUID_DECL
__CRT_UUID_DECL(IMMDeviceActivator, 0x3b0d0ea4, 0xd0a9, 0x4b0e, 0x93,0x5b, 0x09,0x51,0x67,0x46,0xfa,0xc0)
#endif
#else
typedef struct IMMDeviceActivatorVtbl {
    BEGIN_INTERFACE

    /*** IUnknown methods ***/
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(
        IMMDeviceActivator *This,
        REFIID riid,
        void **ppvObject);

    ULONG (STDMETHODCALLTYPE *AddRef)(
        IMMDeviceActivator *This);

    ULONG (STDMETHODCALLTYPE *Release)(
        IMMDeviceActivator *This);

    /*** IMMDeviceActivator methods ***/
    HRESULT (STDMETHODCALLTYPE *Activate)(
        IMMDeviceActivator *This,
        REFIID iid,
        IMMDevice *pDevice,
        PROPVARIANT *pActivationParams,
        void **ppv);

    END_INTERFACE
} IMMDeviceActivatorVtbl;

interface IMMDeviceActivator {
    CONST_VTBL IMMDeviceActivatorVtbl* lpVtbl;
};

#ifdef COBJMACROS
#ifndef WIDL_C_INLINE_WRAPPERS
/*** IUnknown methods ***/
#define IMMDeviceActivator_QueryInterface(This,riid,ppvObject) (This)->lpVtbl->QueryInterface(This,riid,ppvObject)
#define IMMDeviceActivator_AddRef(This) (This)->lpVtbl->AddRef(This)
#define IMMDeviceActivator_Release(This) (This)->lpVtbl->Release(This)
/*** IMMDeviceActivator methods ***/
#define IMMDeviceActivator_Activate(This,iid,pDevice,pActivationParams,ppv) (This)->lpVtbl->Activate(This,iid,pDevice,pActivationParams,ppv)
#else
/*** IUnknown methods ***/
static inline HRESULT IMMDeviceActivator_QueryInterface(IMMDeviceActivator* This,REFIID riid,void **ppvObject) {
    return This->lpVtbl->QueryInterface(This,riid,ppvObject);
}
static inline ULONG IMMDeviceActivator_AddRef(IMMDeviceActivator* This) {
    return This->lpVtbl->AddRef(This);
}
static inline ULONG IMMDeviceActivator_Release(IMMDeviceActivator* This) {
    return This->lpVtbl->Release(This);
}
/*** IMMDeviceActivator methods ***/
static inline HRESULT IMMDeviceActivator_Activate(IMMDeviceActivator* This,REFIID iid,IMMDevice *pDevice,PROPVARIANT *pActivationParams,void **ppv) {
    return This->lpVtbl->Activate(This,iid,pDevice,pActivationParams,ppv);
}
#endif
#endif

#endif


#endif  /* __IMMDeviceActivator_INTERFACE_DEFINED__ */

typedef struct _AudioExtensionParams {
    LPARAM AddPageParam;
    IMMDevice *pEndPoint;
    IMMDevice *pPnpInterface;
    IMMDevice *pPnpDevnode;
} AudioExtensionParams;
/*****************************************************************************
 * IActivateAudioInterfaceAsyncOperation interface
 */
#ifndef __IActivateAudioInterfaceAsyncOperation_INTERFACE_DEFINED__
#define __IActivateAudioInterfaceAsyncOperation_INTERFACE_DEFINED__

DEFINE_GUID(IID_IActivateAudioInterfaceAsyncOperation, 0x72a22d78, 0xcde4, 0x431d, 0xb8,0xcc, 0x84,0x3a,0x71,0x19,0x9b,0x6d);
#if defined(__cplusplus) && !defined(CINTERFACE)
MIDL_INTERFACE("72a22d78-cde4-431d-b8cc-843a71199b6d")
IActivateAudioInterfaceAsyncOperation : public IUnknown
{
    virtual HRESULT STDMETHODCALLTYPE GetActivateResult(
        HRESULT *result,
        IUnknown **iface) = 0;

};
#ifdef __CRT_UUID_DECL
__CRT_UUID_DECL(IActivateAudioInterfaceAsyncOperation, 0x72a22d78, 0xcde4, 0x431d, 0xb8,0xcc, 0x84,0x3a,0x71,0x19,0x9b,0x6d)
#endif
#else
typedef struct IActivateAudioInterfaceAsyncOperationVtbl {
    BEGIN_INTERFACE

    /*** IUnknown methods ***/
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(
        IActivateAudioInterfaceAsyncOperation *This,
        REFIID riid,
        void **ppvObject);

    ULONG (STDMETHODCALLTYPE *AddRef)(
        IActivateAudioInterfaceAsyncOperation *This);

    ULONG (STDMETHODCALLTYPE *Release)(
        IActivateAudioInterfaceAsyncOperation *This);

    /*** IActivateAudioInterfaceAsyncOperation methods ***/
    HRESULT (STDMETHODCALLTYPE *GetActivateResult)(
        IActivateAudioInterfaceAsyncOperation *This,
        HRESULT *result,
        IUnknown **iface);

    END_INTERFACE
} IActivateAudioInterfaceAsyncOperationVtbl;

interface IActivateAudioInterfaceAsyncOperation {
    CONST_VTBL IActivateAudioInterfaceAsyncOperationVtbl* lpVtbl;
};

#ifdef COBJMACROS
#ifndef WIDL_C_INLINE_WRAPPERS
/*** IUnknown methods ***/
#define IActivateAudioInterfaceAsyncOperation_QueryInterface(This,riid,ppvObject) (This)->lpVtbl->QueryInterface(This,riid,ppvObject)
#define IActivateAudioInterfaceAsyncOperation_AddRef(This) (This)->lpVtbl->AddRef(This)
#define IActivateAudioInterfaceAsyncOperation_Release(This) (This)->lpVtbl->Release(This)
/*** IActivateAudioInterfaceAsyncOperation methods ***/
#define IActivateAudioInterfaceAsyncOperation_GetActivateResult(This,result,iface) (This)->lpVtbl->GetActivateResult(This,result,iface)
#else
/*** IUnknown methods ***/
static inline HRESULT IActivateAudioInterfaceAsyncOperation_QueryInterface(IActivateAudioInterfaceAsyncOperation* This,REFIID riid,void **ppvObject) {
    return This->lpVtbl->QueryInterface(This,riid,ppvObject);
}
static inline ULONG IActivateAudioInterfaceAsyncOperation_AddRef(IActivateAudioInterfaceAsyncOperation* This) {
    return This->lpVtbl->AddRef(This);
}
static inline ULONG IActivateAudioInterfaceAsyncOperation_Release(IActivateAudioInterfaceAsyncOperation* This) {
    return This->lpVtbl->Release(This);
}
/*** IActivateAudioInterfaceAsyncOperation methods ***/
static inline HRESULT IActivateAudioInterfaceAsyncOperation_GetActivateResult(IActivateAudioInterfaceAsyncOperation* This,HRESULT *result,IUnknown **iface) {
    return This->lpVtbl->GetActivateResult(This,result,iface);
}
#endif
#endif

#endif


#endif  /* __IActivateAudioInterfaceAsyncOperation_INTERFACE_DEFINED__ */

/*****************************************************************************
 * IActivateAudioInterfaceCompletionHandler interface
 */
#ifndef __IActivateAudioInterfaceCompletionHandler_INTERFACE_DEFINED__
#define __IActivateAudioInterfaceCompletionHandler_INTERFACE_DEFINED__

DEFINE_GUID(IID_IActivateAudioInterfaceCompletionHandler, 0x41d949ab, 0x9862, 0x444a, 0x80,0xf6, 0xc2,0x61,0x33,0x4d,0xa5,0xeb);
#if defined(__cplusplus) && !defined(CINTERFACE)
MIDL_INTERFACE("41d949ab-9862-444a-80f6-c261334da5eb")
IActivateAudioInterfaceCompletionHandler : public IUnknown
{
    virtual HRESULT STDMETHODCALLTYPE ActivateCompleted(
        IActivateAudioInterfaceAsyncOperation *op) = 0;

};
#ifdef __CRT_UUID_DECL
__CRT_UUID_DECL(IActivateAudioInterfaceCompletionHandler, 0x41d949ab, 0x9862, 0x444a, 0x80,0xf6, 0xc2,0x61,0x33,0x4d,0xa5,0xeb)
#endif
#else
typedef struct IActivateAudioInterfaceCompletionHandlerVtbl {
    BEGIN_INTERFACE

    /*** IUnknown methods ***/
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(
        IActivateAudioInterfaceCompletionHandler *This,
        REFIID riid,
        void **ppvObject);

    ULONG (STDMETHODCALLTYPE *AddRef)(
        IActivateAudioInterfaceCompletionHandler *This);

    ULONG (STDMETHODCALLTYPE *Release)(
        IActivateAudioInterfaceCompletionHandler *This);

    /*** IActivateAudioInterfaceCompletionHandler methods ***/
    HRESULT (STDMETHODCALLTYPE *ActivateCompleted)(
        IActivateAudioInterfaceCompletionHandler *This,
        IActivateAudioInterfaceAsyncOperation *op);

    END_INTERFACE
} IActivateAudioInterfaceCompletionHandlerVtbl;

interface IActivateAudioInterfaceCompletionHandler {
    CONST_VTBL IActivateAudioInterfaceCompletionHandlerVtbl* lpVtbl;
};

#ifdef COBJMACROS
#ifndef WIDL_C_INLINE_WRAPPERS
/*** IUnknown methods ***/
#define IActivateAudioInterfaceCompletionHandler_QueryInterface(This,riid,ppvObject) (This)->lpVtbl->QueryInterface(This,riid,ppvObject)
#define IActivateAudioInterfaceCompletionHandler_AddRef(This) (This)->lpVtbl->AddRef(This)
#define IActivateAudioInterfaceCompletionHandler_Release(This) (This)->lpVtbl->Release(This)
/*** IActivateAudioInterfaceCompletionHandler methods ***/
#define IActivateAudioInterfaceCompletionHandler_ActivateCompleted(This,op) (This)->lpVtbl->ActivateCompleted(This,op)
#else
/*** IUnknown methods ***/
static inline HRESULT IActivateAudioInterfaceCompletionHandler_QueryInterface(IActivateAudioInterfaceCompletionHandler* This,REFIID riid,void **ppvObject) {
    return This->lpVtbl->QueryInterface(This,riid,ppvObject);
}
static inline ULONG IActivateAudioInterfaceCompletionHandler_AddRef(IActivateAudioInterfaceCompletionHandler* This) {
    return This->lpVtbl->AddRef(This);
}
static inline ULONG IActivateAudioInterfaceCompletionHandler_Release(IActivateAudioInterfaceCompletionHandler* This) {
    return This->lpVtbl->Release(This);
}
/*** IActivateAudioInterfaceCompletionHandler methods ***/
static inline HRESULT IActivateAudioInterfaceCompletionHandler_ActivateCompleted(IActivateAudioInterfaceCompletionHandler* This,IActivateAudioInterfaceAsyncOperation *op) {
    return This->lpVtbl->ActivateCompleted(This,op);
}
#endif
#endif

#endif


#endif  /* __IActivateAudioInterfaceCompletionHandler_INTERFACE_DEFINED__ */

HRESULT WINAPI ActivateAudioInterfaceAsync(
        const WCHAR *path, REFIID riid, PROPVARIANT *params,
        IActivateAudioInterfaceCompletionHandler *done_handler,
        IActivateAudioInterfaceAsyncOperation **op);
#ifndef __MMDeviceAPILib_LIBRARY_DEFINED__
#define __MMDeviceAPILib_LIBRARY_DEFINED__

DEFINE_GUID(LIBID_MMDeviceAPILib, 0x2fdaafa3, 0x7523, 0x4f66, 0x99,0x57, 0x9d,0x5e,0x7f,0xe6,0x98,0xf6);

/*****************************************************************************
 * MMDeviceEnumerator coclass
 */

DEFINE_GUID(CLSID_MMDeviceEnumerator, 0xbcde0395, 0xe52f, 0x467c, 0x8e,0x3d, 0xc4,0x57,0x92,0x91,0x69,0x2e);

#ifdef __cplusplus
class DECLSPEC_UUID("bcde0395-e52f-467c-8e3d-c4579291692e") MMDeviceEnumerator;
#ifdef __CRT_UUID_DECL
__CRT_UUID_DECL(MMDeviceEnumerator, 0xbcde0395, 0xe52f, 0x467c, 0x8e,0x3d, 0xc4,0x57,0x92,0x91,0x69,0x2e)
#endif
#endif

#endif /* __MMDeviceAPILib_LIBRARY_DEFINED__ */
/* Begin additional prototypes for all interfaces */


/* End additional prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __mmdeviceapi_h__ */
