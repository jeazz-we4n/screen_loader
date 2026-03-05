#include "screen_loader.h"
#include "proxydirectx.h"
#include "color.h"
#include <cstdio>

static ScreenLoader* g_pLoadScreenForPresent = nullptr;

static HRESULT __stdcall PresentThunk(const RECT* pSourceRect, const RECT* pDestRect,
    HWND hDestWindowOverride, const RGNDATA* pDirtyRegion)
{
    if (g_pLoadScreenForPresent)
        return g_pLoadScreenForPresent->Present(pSourceRect, pDestRect, hDestWindowOverride, pDirtyRegion);
    return D3D_OK;
}

ScreenLoader::ScreenLoader()
{
    g_pLoadScreenForPresent = this;
    g_class.DirectX->SetPresentCallback(PresentThunk);
}

ScreenLoader::~ScreenLoader()
{
    if (g_pLoadScreenForPresent == this)
        g_pLoadScreenForPresent = nullptr;
    if (g_class.DirectX) {
        g_class.DirectX->SetPresentCallback(nullptr);
        g_class.DirectX->d3d9_ReleaseRender(pRender);
        g_class.DirectX->d3d9_ReleaseTexture(pTexture);
    }
}

void ScreenLoader::Loop()
{
}

bool ScreenLoader::Event(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    (void)uMsg;
    (void)wParam;
    (void)lParam;
    return true;
}

HRESULT ScreenLoader::Present(const RECT* pSourceRect, const RECT* pDestRect,
    HWND hDestWindowOverride, const RGNDATA* pDirtyRegion)
{
    (void)pSourceRect;
    (void)pDestRect;
    (void)hDestWindowOverride;
    (void)pDirtyRegion;

    if ((g_vars.gameSatate >= 7 && GetModuleHandleA("samp.dll") == 0) || g_vars.gameSatate == 9)
        return D3D_OK;

    if (!init) {
        init = true;
        pTexture = g_class.DirectX->d3d9_CreateTexture(g_class.params->BackBufferWidth,
                                                       g_class.params->BackBufferHeight);
        pTexture->Load(L"screen_loader.png");
        pRender = g_class.DirectX->d3d9_CreateRender(16);
    }

    if (!init)
        return D3D_OK;

    const int screenW = g_class.params->BackBufferWidth;
    const int screenH = g_class.params->BackBufferHeight;

    // Реальный прогресс игры (скачет 0, 11, 22, ... 89, 100)
    float targetProgress = 11.111111f * static_cast<float>(g_vars.gameSatate);
    if (targetProgress > 100.0f) targetProgress = 100.0f;

    // Сброс в начале загрузки
    if (g_vars.gameSatate == 0)
        displayProgress = 0.0f;

    // Плавно догоняем целевой прогресс (без резких скачков)
    const float smoothSpeed = 0.03f;  // чем меньше — тем плавнее
    displayProgress += (targetProgress - displayProgress) * smoothSpeed;

    // Когда игра "зависла" на ~89%, плавно доводим полоску до 100%
    if (targetProgress >= 85.0f && displayProgress < 99.5f)
        displayProgress += (100.0f - displayProgress) * 0.008f;

    if (displayProgress > 100.0f) displayProgress = 100.0f;

    pTexture->Begin();
    pTexture->Clear(eCdBlack);

    // Progress bar at bottom: full width, no text.
    const float barHeight = 14.0f;
    const float barY = static_cast<float>(screenH) - barHeight;
    const float fillW = static_cast<float>(screenW) * (displayProgress / 100.0f);

    // Dark track (semi-transparent dark blue-grey)
    const unsigned int barBg = 0xE0182028u;
    // Fill: bright blue to match the car
    const unsigned int barFill = 0xFF0088FFu;

    pRender->D3DBox(0.0f, barY, static_cast<float>(screenW), barHeight, SRColor(barBg));
    if (fillW > 0.5f)
        pRender->D3DBox(0.0f, barY, fillW, barHeight, SRColor(barFill));

    pTexture->End();
    pTexture->Render(0, 0, screenW, screenH);

    return D3D_OK;
}
