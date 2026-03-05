#ifndef SCREEN_LOADER_H
#define SCREEN_LOADER_H

#include "loader.h"
#include "d3drender.h"
#include "texture.h"

class ScreenLoader
{
public:
    ScreenLoader();
    virtual ~ScreenLoader();

    void Loop();
    bool Event(UINT uMsg, WPARAM wParam, LPARAM lParam);

    HRESULT Present(const RECT* pSourceRect, const RECT* pDestRect, HWND hDestWindowOverride,
                    const RGNDATA* pDirtyRegion);

private:
    SRTexture* pTexture = nullptr;
    CD3DRender* pRender = nullptr;
    bool init = false;
    float displayProgress = 0.0f;  // плавно догоняем реальный прогресс
};

#endif
