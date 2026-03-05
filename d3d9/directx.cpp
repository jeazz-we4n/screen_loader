#include "directx.h"
#include "proxydirectx.h"
#include "d3drender.h"

CDirectX::CDirectX(IDirect3DDevice9 *dx)
{
    _dx = dx;
}

IDirect3DDevice9 *CDirectX::d3d9_device()
{
    return dynamic_cast<proxyIDirect3DDevice9*>(_dx)->getOriginalDevice();
}

proxyIDirect3DDevice9 *CDirectX::d3d9_this()
{
    return dynamic_cast<proxyIDirect3DDevice9*>(_dx);
}

HRESULT CDirectX::d3d9_GenerateShader(IDirect3DPixelShader9 **pShader, float alpha, float red, float green, float blue)
{
    return dynamic_cast<proxyIDirect3DDevice9*>(_dx)->GenerateShader(pShader, alpha, red, green, blue);
}

CD3DFont *CDirectX::d3d9_CreateFont(const char *szFontName, int fontHeight, DWORD dwCreateFlags)
{
    CD3DFont *pFont = new CD3DFont(szFontName, fontHeight, dwCreateFlags);
    dynamic_cast<proxyIDirect3DDevice9*>(_dx)->RegisterFont(pFont);
    return pFont;
}

CD3DRender *CDirectX::d3d9_CreateRender(int numVertices)
{
    CD3DRender *pRender = new CD3DRender(numVertices);
    dynamic_cast<proxyIDirect3DDevice9*>(_dx)->RegisterRender(pRender);
    return pRender;
}

SRTexture *CDirectX::d3d9_CreateTexture(int width, int height)
{
    SRTexture *pTexture = new SRTexture(width, height);
    dynamic_cast<proxyIDirect3DDevice9*>(_dx)->RegisterTexture(pTexture);
    return pTexture;
}

void CDirectX::d3d9_ReleaseFont(CD3DFont *pFont)
{
    dynamic_cast<proxyIDirect3DDevice9*>(_dx)->ReleaseFont(pFont);
}

void CDirectX::d3d9_ReleaseRender(CD3DRender *pRender)
{
    dynamic_cast<proxyIDirect3DDevice9*>(_dx)->ReleaseRender(pRender);
}

void CDirectX::d3d9_ReleaseTexture(SRTexture *pTexture)
{
    dynamic_cast<proxyIDirect3DDevice9*>(_dx)->ReleaseTexture(pTexture);
}

HRESULT CDirectX::__d3d9_QueryInterface(const IID &riid, void **ppvObj)
{
    (void)riid;
    (void)ppvObj;
    return S_OK;
}

ULONG CDirectX::__d3d9_AddRef()
{
    return 0;
}

ULONG CDirectX::__d3d9_Release()
{
    return 0;
}

HRESULT CDirectX::__d3d9_TestCooperativeLevel()
{
    return D3D_OK;
}

UINT CDirectX::__d3d9_GetAvailableTextureMem()
{
    return 0;
}

HRESULT CDirectX::__d3d9_EvictManagedResources()
{
    return D3D_OK;
}

HRESULT CDirectX::__d3d9_GetDirect3D(IDirect3D9 **ppD3D9)
{
    return D3D_OK;
}

HRESULT CDirectX::__d3d9_GetDeviceCaps(D3DCAPS9 *pCaps)
{
    return D3D_OK;
}

HRESULT CDirectX::__d3d9_GetDisplayMode(UINT iSwapChain, D3DDISPLAYMODE *pMode)
{
    return D3D_OK;
}

HRESULT CDirectX::__d3d9_GetCreationParameters(D3DDEVICE_CREATION_PARAMETERS *pParameters)
{
    return D3D_OK;
}

HRESULT CDirectX::__d3d9_SetCursorProperties(UINT XHotSpot, UINT YHotSpot, IDirect3DSurface9 *pCursorBitmap)
{
    return D3D_OK;
}

void CDirectX::__d3d9_SetCursorPosition(int X, int Y, DWORD Flags)
{
    (void)X;
    (void)Y;
    (void)Flags;
}

BOOL CDirectX::__d3d9_ShowCursor(BOOL bShow)
{
    return FALSE;
}

HRESULT CDirectX::__d3d9_CreateAdditionalSwapChain(D3DPRESENT_PARAMETERS *pPresentationParameters, IDirect3DSwapChain9 **pSwapChain)
{
    return D3D_OK;
}

HRESULT CDirectX::__d3d9_GetSwapChain(UINT iSwapChain, IDirect3DSwapChain9 **pSwapChain)
{
    return D3D_OK;
}

UINT CDirectX::__d3d9_GetNumberOfSwapChains()
{
    return 0;
}

HRESULT CDirectX::__d3d9_Reset(D3DPRESENT_PARAMETERS *pPresentationParameters)
{
    return D3D_OK;
}

HRESULT CDirectX::__d3d9_Present(const RECT *pSourceRect, const RECT *pDestRect, HWND hDestWindowOverride, const RGNDATA *pDirtyRegion)
{
    if (m_presentCallback)
        return m_presentCallback(pSourceRect, pDestRect, hDestWindowOverride, pDirtyRegion);
    return D3D_OK;
}

HRESULT CDirectX::__d3d9_GetBackBuffer(UINT iSwapChain, UINT iBackBuffer, D3DBACKBUFFER_TYPE Type, IDirect3DSurface9 **ppBackBuffer)
{
    return D3D_OK;
}

HRESULT CDirectX::__d3d9_GetRasterStatus(UINT iSwapChain, D3DRASTER_STATUS *pRasterStatus)
{
    return D3D_OK;
}

HRESULT CDirectX::__d3d9_SetDialogBoxMode(BOOL bEnableDialogs)
{
    return D3D_OK;
}

void CDirectX::__d3d9_SetGammaRamp(UINT iSwapChain, DWORD Flags, const D3DGAMMARAMP *pRamp)
{
    (void)iSwapChain;(void)Flags;(void)pRamp;
}

void CDirectX::__d3d9_GetGammaRamp(UINT iSwapChain, D3DGAMMARAMP *pRamp)
{
    (void)iSwapChain;(void)pRamp;
}

HRESULT CDirectX::__d3d9_CreateTexture(UINT Width, UINT Height, UINT Levels, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DTexture9 **ppTexture, HANDLE *pSharedHandle)
{
    return D3D_OK;
}

HRESULT CDirectX::__d3d9_CreateVolumeTexture(UINT Width, UINT Height, UINT Depth, UINT Levels, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DVolumeTexture9 **ppVolumeTexture, HANDLE *pSharedHandle)
{
    return D3D_OK;
}

HRESULT CDirectX::__d3d9_CreateCubeTexture(UINT EdgeLength, UINT Levels, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DCubeTexture9 **ppCubeTexture, HANDLE *pSharedHandle)
{
    return D3D_OK;
}

HRESULT CDirectX::__d3d9_CreateVertexBuffer(UINT Length, DWORD Usage, DWORD FVF, D3DPOOL Pool, IDirect3DVertexBuffer9 **ppVertexBuffer, HANDLE *pSharedHandle)
{
    return D3D_OK;
}

HRESULT CDirectX::__d3d9_CreateIndexBuffer(UINT Length, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DIndexBuffer9 **ppIndexBuffer, HANDLE *pSharedHandle)
{
    return D3D_OK;
}

HRESULT CDirectX::__d3d9_CreateRenderTarget(UINT Width, UINT Height, D3DFORMAT Format, D3DMULTISAMPLE_TYPE MultiSample, DWORD MultisampleQuality, BOOL Lockable, IDirect3DSurface9 **ppSurface, HANDLE *pSharedHandle)
{
    return D3D_OK;
}

HRESULT CDirectX::__d3d9_CreateDepthStencilSurface(UINT Width, UINT Height, D3DFORMAT Format, D3DMULTISAMPLE_TYPE MultiSample, DWORD MultisampleQuality, BOOL Discard, IDirect3DSurface9 **ppSurface, HANDLE *pSharedHandle)
{
    return D3D_OK;
}

HRESULT CDirectX::__d3d9_UpdateSurface(IDirect3DSurface9 *pSourceSurface, const RECT *pSourceRect, IDirect3DSurface9 *pDestinationSurface, const POINT *pDestPoint)
{
    return D3D_OK;
}

HRESULT CDirectX::__d3d9_UpdateTexture(IDirect3DBaseTexture9 *pSourceTexture, IDirect3DBaseTexture9 *pDestinationTexture)
{
    return D3D_OK;
}

HRESULT CDirectX::__d3d9_GetRenderTargetData(IDirect3DSurface9 *pRenderTarget, IDirect3DSurface9 *pDestSurface)
{
    return D3D_OK;
}

HRESULT CDirectX::__d3d9_GetFrontBufferData(UINT iSwapChain, IDirect3DSurface9 *pDestSurface)
{
    return D3D_OK;
}

HRESULT CDirectX::__d3d9_StretchRect(IDirect3DSurface9 *pSourceSurface, const RECT *pSourceRect, IDirect3DSurface9 *pDestSurface, const RECT *pDestRect, D3DTEXTUREFILTERTYPE Filter)
{
    return D3D_OK;
}

HRESULT CDirectX::__d3d9_ColorFill(IDirect3DSurface9 *pSurface, const RECT *pRect, D3DCOLOR color)
{
    return D3D_OK;
}

HRESULT CDirectX::__d3d9_CreateOffscreenPlainSurface(UINT Width, UINT Height, D3DFORMAT Format, D3DPOOL Pool, IDirect3DSurface9 **ppSurface, HANDLE *pSharedHandle)
{
    return D3D_OK;
}

HRESULT CDirectX::__d3d9_SetRenderTarget(DWORD RenderTargetIndex, IDirect3DSurface9 *pRenderTarget)
{
    return D3D_OK;
}

HRESULT CDirectX::__d3d9_GetRenderTarget(DWORD RenderTargetIndex, IDirect3DSurface9 **ppRenderTarget)
{
    return D3D_OK;
}

HRESULT CDirectX::__d3d9_SetDepthStencilSurface(IDirect3DSurface9 *pNewZStencil)
{
    return D3D_OK;
}

HRESULT CDirectX::__d3d9_GetDepthStencilSurface(IDirect3DSurface9 **ppZStencilSurface)
{
    return D3D_OK;
}

HRESULT CDirectX::__d3d9_BeginScene()
{
    return D3D_OK;
}

HRESULT CDirectX::__d3d9_EndScene()
{
    return D3D_OK;
}

HRESULT CDirectX::__d3d9_Clear(DWORD Count, const D3DRECT *pRects, DWORD Flags, D3DCOLOR Color, float Z, DWORD Stencil)
{
    return D3D_OK;
}

HRESULT CDirectX::__d3d9_SetTransform(D3DTRANSFORMSTATETYPE State, const D3DMATRIX *pMatrix)
{
    return D3D_OK;
}

HRESULT CDirectX::__d3d9_GetTransform(D3DTRANSFORMSTATETYPE State, D3DMATRIX *pMatrix)
{
    return D3D_OK;
}

HRESULT CDirectX::__d3d9_MultiplyTransform(D3DTRANSFORMSTATETYPE State, const D3DMATRIX *pMatrix)
{
    return D3D_OK;
}

HRESULT CDirectX::__d3d9_SetViewport(const D3DVIEWPORT9 *pViewport)
{
    return D3D_OK;
}

HRESULT CDirectX::__d3d9_GetViewport(D3DVIEWPORT9 *pViewport)
{
    return D3D_OK;
}

HRESULT CDirectX::__d3d9_SetMaterial(const D3DMATERIAL9 *pMaterial)
{
    return D3D_OK;
}

HRESULT CDirectX::__d3d9_GetMaterial(D3DMATERIAL9 *pMaterial)
{
    return D3D_OK;
}

HRESULT CDirectX::__d3d9_SetLight(DWORD Index, const D3DLIGHT9 *pLight)
{
    return D3D_OK;
}

HRESULT CDirectX::__d3d9_GetLight(DWORD Index, D3DLIGHT9 *pLight)
{
    return D3D_OK;
}

HRESULT CDirectX::__d3d9_LightEnable(DWORD Index, BOOL Enable)
{
    return D3D_OK;
}

HRESULT CDirectX::__d3d9_GetLightEnable(DWORD Index, BOOL *pEnable)
{
    return D3D_OK;
}

HRESULT CDirectX::__d3d9_SetClipPlane(DWORD Index, const float *pPlane)
{
    return D3D_OK;
}

HRESULT CDirectX::__d3d9_GetClipPlane(DWORD Index, float *pPlane)
{
    return D3D_OK;
}

HRESULT CDirectX::__d3d9_SetRenderState(D3DRENDERSTATETYPE State, DWORD Value)
{
    return D3D_OK;
}

HRESULT CDirectX::__d3d9_GetRenderState(D3DRENDERSTATETYPE State, DWORD *pValue)
{
    return D3D_OK;
}

HRESULT CDirectX::__d3d9_CreateStateBlock(D3DSTATEBLOCKTYPE Type, IDirect3DStateBlock9 **ppSB)
{
    return D3D_OK;
}

HRESULT CDirectX::__d3d9_BeginStateBlock()
{
    return D3D_OK;
}

HRESULT CDirectX::__d3d9_EndStateBlock(IDirect3DStateBlock9 **ppSB)
{
    return D3D_OK;
}

HRESULT CDirectX::__d3d9_SetClipStatus(const D3DCLIPSTATUS9 *pClipStatus)
{
    return D3D_OK;
}

HRESULT CDirectX::__d3d9_GetClipStatus(D3DCLIPSTATUS9 *pClipStatus)
{
    return D3D_OK;
}

HRESULT CDirectX::__d3d9_GetTexture(DWORD Stage, IDirect3DBaseTexture9 **ppTexture)
{
    return D3D_OK;
}

HRESULT CDirectX::__d3d9_SetTexture(DWORD Stage, IDirect3DBaseTexture9 *pTexture)
{
    return D3D_OK;
}

HRESULT CDirectX::__d3d9_GetTextureStageState(DWORD Stage, D3DTEXTURESTAGESTATETYPE Type, DWORD *pValue)
{
    return D3D_OK;
}

HRESULT CDirectX::__d3d9_SetTextureStageState(DWORD Stage, D3DTEXTURESTAGESTATETYPE Type, DWORD Value)
{
    return D3D_OK;
}

HRESULT CDirectX::__d3d9_GetSamplerState(DWORD Sampler, D3DSAMPLERSTATETYPE Type, DWORD *pValue)
{
    return D3D_OK;
}

HRESULT CDirectX::__d3d9_SetSamplerState(DWORD Sampler, D3DSAMPLERSTATETYPE Type, DWORD Value)
{
    return D3D_OK;
}

HRESULT CDirectX::__d3d9_ValidateDevice(DWORD *pNumPasses)
{
    return D3D_OK;
}

HRESULT CDirectX::__d3d9_SetPaletteEntries(UINT PaletteNumber, const PALETTEENTRY *pEntries)
{
    return D3D_OK;
}

HRESULT CDirectX::__d3d9_GetPaletteEntries(UINT PaletteNumber, PALETTEENTRY *pEntries)
{
    return D3D_OK;
}

HRESULT CDirectX::__d3d9_SetCurrentTexturePalette(UINT PaletteNumber)
{
    return D3D_OK;
}

HRESULT CDirectX::__d3d9_GetCurrentTexturePalette(UINT *PaletteNumber)
{
    return D3D_OK;
}

HRESULT CDirectX::__d3d9_SetScissorRect(const RECT *pRect)
{
    return D3D_OK;
}

HRESULT CDirectX::__d3d9_GetScissorRect(RECT *pRect)
{
    return D3D_OK;
}

HRESULT CDirectX::__d3d9_SetSoftwareVertexProcessing(BOOL bSoftware)
{
    return D3D_OK;
}

BOOL CDirectX::__d3d9_GetSoftwareVertexProcessing()
{
    return D3D_OK;
}

HRESULT CDirectX::__d3d9_SetNPatchMode(float nSegments)
{
    return D3D_OK;
}

float CDirectX::__d3d9_GetNPatchMode()
{
    return D3D_OK;
}

HRESULT CDirectX::__d3d9_DrawPrimitive(D3DPRIMITIVETYPE PrimitiveType, UINT StartVertex, UINT PrimitiveCount)
{
    return D3D_OK;
}

HRESULT CDirectX::__d3d9_DrawIndexedPrimitive(D3DPRIMITIVETYPE PrimitiveType, INT BaseVertexIndex, UINT MinVertexIndex, UINT NumVertices, UINT startIndex, UINT primCount)
{
    return D3D_OK;
}

HRESULT CDirectX::__d3d9_DrawPrimitiveUP(D3DPRIMITIVETYPE PrimitiveType, UINT PrimitiveCount, const void *pVertexStreamZeroData, UINT VertexStreamZeroStride)
{
    return D3D_OK;
}

HRESULT CDirectX::__d3d9_DrawIndexedPrimitiveUP(D3DPRIMITIVETYPE PrimitiveType, UINT MinVertexIndex, UINT NumVertices, UINT PrimitiveCount, const void *pIndexData, D3DFORMAT IndexDataFormat, const void *pVertexStreamZeroData, UINT VertexStreamZeroStride)
{
    return D3D_OK;
}

HRESULT CDirectX::__d3d9_ProcessVertices(UINT SrcStartIndex, UINT DestIndex, UINT VertexCount, IDirect3DVertexBuffer9 *pDestBuffer, IDirect3DVertexDeclaration9 *pVertexDecl, DWORD Flags)
{
    return D3D_OK;
}

HRESULT CDirectX::__d3d9_CreateVertexDeclaration(const D3DVERTEXELEMENT9 *pVertexElements, IDirect3DVertexDeclaration9 **ppDecl)
{
    return D3D_OK;
}

HRESULT CDirectX::__d3d9_SetVertexDeclaration(IDirect3DVertexDeclaration9 *pDecl)
{
    return D3D_OK;
}

HRESULT CDirectX::__d3d9_GetVertexDeclaration(IDirect3DVertexDeclaration9 **ppDecl)
{
    return D3D_OK;
}

HRESULT CDirectX::__d3d9_SetFVF(DWORD FVF)
{
    return D3D_OK;
}

HRESULT CDirectX::__d3d9_GetFVF(DWORD *pFVF)
{
    return D3D_OK;
}

HRESULT CDirectX::__d3d9_CreateVertexShader(const DWORD *pFunction, IDirect3DVertexShader9 **ppShader)
{
    return D3D_OK;
}

HRESULT CDirectX::__d3d9_SetVertexShader(IDirect3DVertexShader9 *pShader)
{
    return D3D_OK;
}

HRESULT CDirectX::__d3d9_GetVertexShader(IDirect3DVertexShader9 **ppShader)
{
    return D3D_OK;
}

HRESULT CDirectX::__d3d9_SetVertexShaderConstantF(UINT StartRegister, const float *pConstantData, UINT Vector4fCount)
{
    return D3D_OK;
}

HRESULT CDirectX::__d3d9_GetVertexShaderConstantF(UINT StartRegister, float *pConstantData, UINT Vector4fCount)
{
    return D3D_OK;
}

HRESULT CDirectX::__d3d9_SetVertexShaderConstantI(UINT StartRegister, const int *pConstantData, UINT Vector4iCount)
{
    return D3D_OK;
}

HRESULT CDirectX::__d3d9_GetVertexShaderConstantI(UINT StartRegister, int *pConstantData, UINT Vector4fCount)
{
    return D3D_OK;
}

HRESULT CDirectX::__d3d9_SetVertexShaderConstantB(UINT StartRegister, const BOOL *pConstantData, UINT Vector4iCount)
{
    return D3D_OK;
}

HRESULT CDirectX::__d3d9_GetVertexShaderConstantB(UINT StartRegister, BOOL *pConstantData, UINT Vector4fCount)
{
    return D3D_OK;
}

HRESULT CDirectX::__d3d9_SetStreamSource(UINT StreamNumber, IDirect3DVertexBuffer9 *pStreamData, UINT OffsetInBytes, UINT Stride)
{
    return D3D_OK;
}

HRESULT CDirectX::__d3d9_GetStreamSource(UINT StreamNumber, IDirect3DVertexBuffer9 **ppStreamData, UINT *OffsetInBytes, UINT *pStride)
{
    return D3D_OK;
}

HRESULT CDirectX::__d3d9_SetStreamSourceFreq(UINT StreamNumber, UINT Divider)
{
    return D3D_OK;
}

HRESULT CDirectX::__d3d9_GetStreamSourceFreq(UINT StreamNumber, UINT *Divider)
{
    return D3D_OK;
}

HRESULT CDirectX::__d3d9_SetIndices(IDirect3DIndexBuffer9 *pIndexData)
{
    return D3D_OK;
}

HRESULT CDirectX::__d3d9_GetIndices(IDirect3DIndexBuffer9 **ppIndexData)
{
    return D3D_OK;
}

HRESULT CDirectX::__d3d9_CreatePixelShader(const DWORD *pFunction, IDirect3DPixelShader9 **ppShader)
{
    return D3D_OK;
}

HRESULT CDirectX::__d3d9_SetPixelShader(IDirect3DPixelShader9 *pShader)
{
    return D3D_OK;
}

HRESULT CDirectX::__d3d9_GetPixelShader(IDirect3DPixelShader9 **ppShader)
{
    return D3D_OK;
}

HRESULT CDirectX::__d3d9_SetPixelShaderConstantF(UINT StartRegister, const float *pConstantData, UINT Vector4fCount)
{
    return D3D_OK;
}

HRESULT CDirectX::__d3d9_GetPixelShaderConstantF(UINT StartRegister, float *pConstantData, UINT Vector4fCount)
{
    return D3D_OK;
}

HRESULT CDirectX::__d3d9_SetPixelShaderConstantI(UINT StartRegister, const int *pConstantData, UINT Vector4fCount)
{
    return D3D_OK;
}

HRESULT CDirectX::__d3d9_GetPixelShaderConstantI(UINT StartRegister, int *pConstantData, UINT Vector4fCount)
{
    return D3D_OK;
}

HRESULT CDirectX::__d3d9_SetPixelShaderConstantB(UINT StartRegister, const BOOL *pConstantData, UINT Vector4fCount)
{
    return D3D_OK;
}

HRESULT CDirectX::__d3d9_GetPixelShaderConstantB(UINT StartRegister, BOOL *pConstantData, UINT Vector4fCount)
{
    return D3D_OK;
}

HRESULT CDirectX::__d3d9_DrawRectPatch(UINT Handle, const float *pNumSegs, const D3DRECTPATCH_INFO *pRectPatchInfo)
{
    return D3D_OK;
}

HRESULT CDirectX::__d3d9_DrawTriPatch(UINT Handle, const float *pNumSegs, const D3DTRIPATCH_INFO *pTriPatchInfo)
{
    return D3D_OK;
}

HRESULT CDirectX::__d3d9_DeletePatch(UINT Handle)
{
    return D3D_OK;
}

HRESULT CDirectX::__d3d9_CreateQuery(D3DQUERYTYPE Type, IDirect3DQuery9 **ppQuery)
{
    return D3D_OK;
}
