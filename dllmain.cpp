

#define WIN32_LEAN_AND_MEAN
#define _WIN32_DCOM

#include <windows.h>
#include <initguid.h>
#include <sapi.h>
#include "sapiddk_compat.h"
#include <string>
#include <vector>
#include <stdio.h>

#define LOG(msg) OutputDebugStringW((std::wstring(L"[SamSapi] ") + msg + L"\n").c_str())

extern "C" const GUID SPDFID_WaveFormatEx = { 0xc3ad9e44, 0xe84e, 0x44f4, { 0xba, 0x9b, 0xfc, 0xe0, 0x8e, 0xa9, 0x9b, 0xd5 } };

static const CLSID CLSID_SamTTSEngine = { 0xa9234856, 0x7812, 0x4abc, { 0x91, 0x23, 0xab, 0xcd, 0xef, 0x12, 0x34, 0x56 } };

long g_dllRefCount = 0;

HMODULE g_hModule = NULL;

class CSamEngine : public ISpTTSEngine, public ISpObjectWithToken {
private:
    LONG m_refCount;
    ISpObjectToken* m_pToken;

public:
    CSamEngine() : m_refCount(1), m_pToken(nullptr) { 
        InterlockedIncrement(&g_dllRefCount); 
        LOG(L"CSamEngine constructed.");
    }
    virtual ~CSamEngine() {
        if (m_pToken) { m_pToken->Release(); m_pToken = nullptr; }
        InterlockedDecrement(&g_dllRefCount);
        LOG(L"CSamEngine destroyed.");
    }

    STDMETHODIMP QueryInterface(REFIID riid, void** ppv) {
        if (!ppv) return E_POINTER;
        *ppv = nullptr;
        if (riid == IID_IUnknown || IsEqualIID(riid, IID_ISpTTSEngine)) {
            *ppv = static_cast<ISpTTSEngine*>(this);
            LOG(L"QueryInterface requested ISpTTSEngine.");
        } else if (riid == IID_ISpObjectWithToken) {
            *ppv = static_cast<ISpObjectWithToken*>(this);
            LOG(L"QueryInterface requested ISpObjectWithToken.");
        } else {
            LOG(L"QueryInterface requested unknown interface.");
            return E_NOINTERFACE;
        }
        AddRef();
        return S_OK;
    }

    STDMETHODIMP_(ULONG) AddRef() { return InterlockedIncrement(&m_refCount); }
    STDMETHODIMP_(ULONG) Release() {
        ULONG res = InterlockedDecrement(&m_refCount);
        if (res == 0) delete this;
        return res;
    }

    STDMETHODIMP SetObjectToken(ISpObjectToken *pToken) {
        LOG(L"SetObjectToken called.");
        if (m_pToken) m_pToken->Release();
        m_pToken = pToken;
        if (m_pToken) m_pToken->AddRef();
        return S_OK;
    }

    STDMETHODIMP GetObjectToken(ISpObjectToken **ppToken) {
        LOG(L"GetObjectToken called.");
        if (!ppToken) return E_POINTER;
        *ppToken = m_pToken;
        if (*ppToken) (*ppToken)->AddRef();
        return S_OK;
    }

    STDMETHODIMP Speak(DWORD dwSpeakFlags, REFGUID rguidFormatId, const WAVEFORMATEX* pWaveFormatEx, const SPVTEXTFRAG* pFragmentList, ISpTTSEngineSite* pOutputSite) {
        LOG(L"Speak() method triggered");
        if (!pFragmentList || !pOutputSite) return E_INVALIDARG;

        wchar_t tempPath[MAX_PATH];
        GetTempPathW(MAX_PATH, tempPath);
        std::wstring wavFile = std::wstring(tempPath) + L"sapi_out.wav";
        wchar_t dllPath[MAX_PATH];
    
        GetModuleFileNameW(g_hModule, dllPath, MAX_PATH);
    
          std::wstring dirPath = dllPath;
          size_t pos = dirPath.find_last_of(L"\\/");
           if (pos != std::wstring::npos) {
               dirPath = dirPath.substr(0, pos);
           }
    
          std::wstring exePath = dirPath + L"\\sam.exe";

            for (const SPVTEXTFRAG* pFrag = pFragmentList; pFrag != nullptr; pFrag = pFrag->pNext) {
              if (pFrag->pTextStart && pFrag->ulTextLen > 0) {
                std::wstring textChunk(pFrag->pTextStart, pFrag->ulTextLen);
                std::wstring cmd = L"\"" + exePath + L"\" -wav \"" + wavFile + L"\" -speed 72 -pitch 64 -throat 128 -mouth 128 " + textChunk;
                LOG(cmd.c_str());
                
                STARTUPINFOW si = { sizeof(si) };
                si.cb = sizeof(si);
                si.dwFlags = STARTF_USESHOWWINDOW;
                si.wShowWindow = SW_HIDE; 
                PROCESS_INFORMATION pi;

                std::vector<wchar_t> cmdBuffer(cmd.begin(), cmd.end());
                cmdBuffer.push_back(0);

                if (CreateProcessW(NULL, cmdBuffer.data(), NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
                    LOG(L"CreateProcess launched sam.exe successfully.");
                    WaitForSingleObject(pi.hProcess, 3000);
                    CloseHandle(pi.hProcess);
                    CloseHandle(pi.hThread);
                } else {
                    DWORD err = GetLastError();
                    wchar_t errBuf[128];
                    swprintf_s(errBuf, L"CreateProcess failed with error code: %lu", err);
                    LOG(errBuf);
                }

                FILE* f = nullptr;
                for (int i = 0; i < 5; ++i) {
                    if (_wfopen_s(&f, wavFile.c_str(), L"rb") == 0 && f) break;
                    Sleep(20);
                }

                if (f) {
                    fseek(f, 0, SEEK_END);
                    long size = ftell(f);
                    if (size > 44) {
                        long dataSize = size - 44;
                        fseek(f, 44, SEEK_SET);

                        char* buffer = new char[dataSize];
                        fread(buffer, 1, dataSize, f);
                        fclose(f);

                        pOutputSite->Write(buffer, dataSize, nullptr);
                        delete[] buffer;
                        LOG(L"Audio successfully written to SAPI output site.");
                    } else {
                        fclose(f);
                        LOG(L"Wav file found, but size was too small or empty.");
                    }
                } else {
                    LOG(L"Failed to open generated wav file.");
                }

                if (!DeleteFileW(wavFile.c_str())) {
                    LOG(L"Failed to delete temp WAV file.");
                } else {
                    LOG(L"Temp WAV file successfully cleaned up.");
                }
            }
        }
        return S_OK;
    }

    STDMETHODIMP GetOutputFormat(const GUID* pTargetFormatId, const WAVEFORMATEX* pTargetWaveFormatEx, GUID* pOutputFormatId, WAVEFORMATEX** ppCoMemOutputFormat) {
        LOG(L"GetOutputFormat() called.");
        if (!pOutputFormatId || !ppCoMemOutputFormat) return E_POINTER;

        *pOutputFormatId = SPDFID_WaveFormatEx;

        WAVEFORMATEX* pWf = (WAVEFORMATEX*)::CoTaskMemAlloc(sizeof(WAVEFORMATEX));
        if (!pWf) return E_OUTOFMEMORY;
        
        pWf->wFormatTag = WAVE_FORMAT_PCM;
        pWf->nChannels = 1;
        pWf->nSamplesPerSec = 22050;
        pWf->wBitsPerSample = 8;
        pWf->nBlockAlign = 1; 
        pWf->nAvgBytesPerSec = 22050; 
        pWf->cbSize = 0;

        *ppCoMemOutputFormat = pWf;
        LOG(L"GetOutputFormat completed successfully.");
        return S_OK;
    }

    STDMETHODIMP SetRate(long) { return S_OK; }
    STDMETHODIMP GetRate(long*) { return S_OK; }
    STDMETHODIMP SetVolume(unsigned short) { return S_OK; }
    STDMETHODIMP GetVolume(unsigned short*) { return S_OK; }
    STDMETHODIMP SpeakComplete(const SPVTEXTFRAG*) { return S_OK; }
};

class CSamClassFactory : public IClassFactory {
private:
    LONG m_refCount;
public:
    CSamClassFactory() : m_refCount(1) {}
    ~CSamClassFactory() {}

    STDMETHODIMP QueryInterface(REFIID riid, void** ppv) {
        if (!ppv) return E_POINTER;
        *ppv = nullptr;
        if (riid == IID_IUnknown || riid == IID_IClassFactory) {
            *ppv = static_cast<IClassFactory*>(this);
        } else {
            return E_NOINTERFACE;
        }
        AddRef();
        return S_OK;
    }

    STDMETHODIMP_(ULONG) AddRef() { return InterlockedIncrement(&m_refCount); }
    STDMETHODIMP_(ULONG) Release() {
        ULONG res = InterlockedDecrement(&m_refCount);
        if (res == 0) delete this;
        return res;
    }

    STDMETHODIMP CreateInstance(LPUNKNOWN pUnkOuter, REFIID riid, void** ppv) {
        LOG(L"CSamClassFactory::CreateInstance called.");
        if (pUnkOuter) return CLASS_E_NOAGGREGATION;
        CSamEngine* pEngine = new CSamEngine();
        if (!pEngine) return E_OUTOFMEMORY;
        HRESULT hr = pEngine->QueryInterface(riid, ppv);
        pEngine->Release();
        return hr;
    }

    STDMETHODIMP LockServer(BOOL) { return S_OK; }
}; 

extern "C" {
BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    switch (ul_reason_for_call) {
    case DLL_PROCESS_ATTACH:
        g_hModule = hModule; // Save the module handle globally here!
        break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

    STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, void** ppv) {
        LOG(L"DllGetClassObject invoked.");
        if (!ppv) return E_POINTER;
        *ppv = nullptr;
        if (rclsid != CLSID_SamTTSEngine) {
            LOG(L"DllGetClassObject: Requested CLSID mismatch!");
            return CLASS_E_CLASSNOTAVAILABLE;
        }
        
        CSamClassFactory* pFactory = new CSamClassFactory();
        if (!pFactory) return E_OUTOFMEMORY;
        
        HRESULT hr = pFactory->QueryInterface(riid, ppv);
        pFactory->Release();
        return hr;
    }

    STDAPI DllCanUnloadNow() {
        return (g_dllRefCount == 0) ? S_OK : S_FALSE;
    }
}