#ifndef SAPIDDK_COMPAT_H
#define SAPIDDK_COMPAT_H

#include <sapi.h>


#ifndef __SPVSKIPTYPE_DEFINED__
#define __SPVSKIPTYPE_DEFINED__
typedef enum SPVSKIPTYPE {
    SPVST_SENTENCE = (1L << 0)
} SPVSKIPTYPE;
#endif

#ifndef __SPVESACTIONS_DEFINED__
#define __SPVESACTIONS_DEFINED__
typedef enum SPVESACTIONS {
    SPVES_CONTINUE = 0,
    SPVES_ABORT    = (1L << 0),
    SPVES_SKIP     = (1L << 1),
    SPVES_RATE     = (1L << 2),
    SPVES_VOLUME   = (1L << 3)
} SPVESACTIONS;
#endif


#ifndef __SPVTEXTFRAG_DEFINED__
#define __SPVTEXTFRAG_DEFINED__
typedef struct SPVTEXTFRAG {
    struct SPVTEXTFRAG *pNext;
    SPVSTATE State;
    LPCWSTR pTextStart;
    ULONG ulTextLen;
    ULONG ulTextSrcOffset;
} SPVTEXTFRAG;
#endif


#ifndef __ISpTTSEngineSite_INTERFACE_DEFINED__
#define __ISpTTSEngineSite_INTERFACE_DEFINED__

EXTERN_C const IID IID_ISpTTSEngineSite;

MIDL_INTERFACE("9880499B-CCE9-11D2-B503-00C04F797396")
ISpTTSEngineSite : public ISpEventSink {
public:
    virtual DWORD STDMETHODCALLTYPE GetActions(void) = 0;
    virtual HRESULT STDMETHODCALLTYPE Write(const void *pBuff, ULONG cb, ULONG *pcbWritten) = 0;
    virtual HRESULT STDMETHODCALLTYPE GetRate(long *pRateAdjust) = 0;
    virtual HRESULT STDMETHODCALLTYPE GetVolume(USHORT *pusVolume) = 0;
    virtual HRESULT STDMETHODCALLTYPE GetSkipInfo(SPVSKIPTYPE *peType, long *plNumItems) = 0;
    virtual HRESULT STDMETHODCALLTYPE CompleteSkip(long lNumSkipped) = 0;
};

#ifdef INITGUID
DEFINE_GUID(IID_ISpTTSEngineSite, 0x9880499b, 0xcce9, 0x11d2, 0xb5, 0x03, 0x00, 0xc0, 0x4f, 0x79, 0x73, 0x96);
#endif

#endif

#ifndef __ISpTTSEngine_INTERFACE_DEFINED__
#define __ISpTTSEngine_INTERFACE_DEFINED__

EXTERN_C const IID IID_ISpTTSEngine;

MIDL_INTERFACE("A74D7C8E-4CC5-4F2F-A6EB-804DEE18500E")
ISpTTSEngine : public IUnknown {
public:
    virtual HRESULT STDMETHODCALLTYPE Speak(
        DWORD dwSpeakFlags,
        REFGUID rguidFormatId,
        const WAVEFORMATEX *pWaveFormatEx,
        const SPVTEXTFRAG *pTextFragList,
        ISpTTSEngineSite *pOutputSite) = 0;

    virtual HRESULT STDMETHODCALLTYPE GetOutputFormat(
        const GUID *pTargetFmtId,
        const WAVEFORMATEX *pTargetWaveFormatEx,
        GUID *pOutputFormatId,
        WAVEFORMATEX **ppCoMemOutputWaveFormatEx) = 0;
};

#ifdef INITGUID
DEFINE_GUID(IID_ISpTTSEngine, 0xa74d7c8e, 0x4cc5, 0x4f2f, 0xa6, 0xeb, 0x80, 0x4d, 0xee, 0x18, 0x50, 0x0e);
#endif

#if defined(__GNUC__) && !defined(__clang__)
__CRT_UUID_DECL(ISpTTSEngine, 0xa74d7c8e, 0x4cc5, 0x4f2f, 0xa6, 0xeb, 0x80, 0x4d, 0xee, 0x18, 0x50, 0x0e)
#endif

#endif

#endif 