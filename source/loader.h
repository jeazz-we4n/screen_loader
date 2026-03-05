#ifndef LOADER_H
#define LOADER_H

typedef unsigned int uint;
typedef unsigned char byte;

#include "llmo/ccallhook.h"
#include <d3d9.h>
#include <d3dx9.h>
#include <wingdi.h>
#include <d3dx9core.h>
#include "directx.h"

#include "Types.h"
#include "CPlaceable.h"
#include "CEntity.h"
#include "CPhysical.h"
#include "CObject.h"
#include "CHAnimIFrame.h"
#include "CBone.h"
#include "CPedIK.h"
#include "CParticleData.h"
#include "CWeaponSlot.h"
#include "CPed.h"
#include "CVehicle.h"
// #include "samp.h"

const HANDLE INVALID_HANDLE = reinterpret_cast<HANDLE>(-1);
const char PROJECT_NAME[]   = "screen_loader";
const char PROJECT_NAME_l[] = "screen_loader";
const char PROJECT_NAME_u[] = "SCREEN_LOADER";

struct stGlobalHandles{
    // union{
    //     HANDLE samp;
    //     DWORD dwSAMP;
    // };
    union{
        HANDLE d3d9;
        DWORD dwD3D9;
    };
};
struct stGlobalClasses{
    IDirect3D9* d3d = static_cast<IDirect3D9*>(nullptr);
    D3DPRESENT_PARAMETERS* params = reinterpret_cast<D3DPRESENT_PARAMETERS*>(0xC9C040);
    // stSAMP* samp = static_cast<stSAMP*>(nullptr);
    CDirectX* DirectX;
};
struct stGlobalPVars{
    uint& gameSatate = *reinterpret_cast<uint*>(0xC8D4C0);
    bool& isMenuOpened = *reinterpret_cast<bool*>(0xBA67A4);
    byte& activeMenuID = *reinterpret_cast<byte*>(0xBA68A5);
    HWND& hwnd = *reinterpret_cast<HWND*>(0xC97C1C);
};

extern stGlobalHandles g_handle;
extern stGlobalClasses g_class;
extern stGlobalPVars g_vars;

int MessageBox(const char* text, const char* title = PROJECT_NAME, UINT type = MB_OK);

#endif // LOADER_H
