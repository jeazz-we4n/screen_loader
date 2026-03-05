#include "loader.h"
#include "screen_loader.h"
#include "proxydirectx.h"
#include "MenuManager/Menu.h"
#include <string>
#include <cstdio>

stGlobalHandles g_handle;
stGlobalClasses g_class;
stGlobalPVars g_vars;

static WNDPROC hOrigProc = NULL;
static ScreenLoader *pScreenLoader = static_cast<ScreenLoader*>(nullptr);
static IDirect3DDevice9* device;

void __stdcall InstallD3DHook()
{
    device = new proxyIDirect3DDevice9( *reinterpret_cast<IDirect3DDevice9 **>(0xC97C28));
    *reinterpret_cast<IDirect3DDevice9 **>(0xC97C28) = dynamic_cast<IDirect3DDevice9*>(device);
    g_class.d3d = *reinterpret_cast<IDirect3D9**>(0xC97C20);
    g_class.DirectX = new CDirectX(device);
}

LRESULT APIENTRY WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    if (hwnd == *(HWND*)0xC97C1C)
    {
        for ( int i = static_cast<int>(MenuList.size() - 1); i >= 0; --i )
            if ( MenuList[static_cast<size_t>(i)]->isShowed() )
                if ( !MenuList[static_cast<size_t>(i)]->onEvents( hwnd, uMsg, wParam, lParam ) )
                    break;

        if (pScreenLoader && !pScreenLoader->Event(uMsg, wParam, lParam))
            return 0;
    }
    return CallWindowProc(hOrigProc, hwnd, uMsg, wParam, lParam);
}

void __stdcall GameLoop()
{
    // g_handle.samp = GetModuleHandleA("samp.dll");
    // if (g_handle.samp == nullptr || g_handle.samp == INVALID_HANDLE)
    // 	return;

    g_handle.d3d9 = GetModuleHandleA("d3d9.dll");
    if (g_handle.d3d9 == nullptr || g_handle.d3d9 == INVALID_HANDLE)
        return;

    // g_class.samp = *reinterpret_cast<stSAMP**>(g_handle.dwSAMP + SAMP_INFO_OFFSET);
    // if (g_class.samp == nullptr)
    // 	return;

    static bool hooked = false;
    if (hooked)
        return pScreenLoader->Loop();
    hooked = true;

//    InstallD3DHook();
//    pScreenLoader = new ScreenLoader();
    hOrigProc = reinterpret_cast<WNDPROC>(SetWindowLongA(g_vars.hwnd, GWL_WNDPROC,
                                                         reinterpret_cast<LONG>(WndProc)));
}

void __stdcall WindowInitialize() //007455DB
{
    g_handle.d3d9 = GetModuleHandleA("d3d9.dll");
//    GameLoop();
    InstallD3DHook();
    pScreenLoader = new ScreenLoader();
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD dwReasonForCall, LPVOID)
{
    static CCallHook *gameloopHook;
    static CCallHook *windowInitHook;

    if (dwReasonForCall == DLL_PROCESS_ATTACH){

        if (sizeof(CPed) != 1988){
            char buf[64];
            sprintf_s(buf, "Incorrect CPed == %u", (unsigned)sizeof(CPed));
            MessageBox(buf, PROJECT_NAME, MB_OK);
            return FALSE;
        }
        if (sizeof(CVehicle) != 2584){
            char buf[64];
            sprintf_s(buf, "Incorrect CVehicle == %u", (unsigned)sizeof(CVehicle));
            MessageBox(buf, PROJECT_NAME, MB_OK);
            return FALSE;
        }
        std::string asiName = std::string(PROJECT_NAME) + ".asi";
        if (GetModuleHandleA(asiName.c_str()) != hModule){
            char name[256];
            GetModuleFileNameA(hModule, name, 256);
            std::string fname(name);
            size_t slash = fname.find_last_of("\\/");
            if (slash != std::string::npos) fname = fname.substr(slash + 1);
            std::string msg = "Incorrect file name.\nPlease rename " + fname + " to " + asiName;
            MessageBox(msg.c_str(), PROJECT_NAME, MB_OK);
            return FALSE;
        }


        windowInitHook = new CCallHook(reinterpret_cast<void*>(0x007F67C1),
                                       eSafeCall(sc_registers | sc_flags), 5);
        windowInitHook->enable(WindowInitialize);

        gameloopHook = new CCallHook(reinterpret_cast<void*>(0x00748DA3),
                                     eSafeCall(sc_registers | sc_flags), 6);
        gameloopHook->enable(GameLoop);
    }
    else if (dwReasonForCall == DLL_PROCESS_DETACH){
        delete windowInitHook;
        delete gameloopHook;
        SetWindowLongA(g_vars.hwnd, GWL_WNDPROC, reinterpret_cast<LONG>(hOrigProc));
        delete pScreenLoader;
        pScreenLoader = nullptr;
        delete dynamic_cast<proxyIDirect3DDevice9*>(device);
        delete g_class.DirectX;
    }

    return TRUE;
}

int MessageBox(const char* text, const char* title, UINT type)
{
    return ::MessageBoxA(g_vars.hwnd, text, title, type);
}
