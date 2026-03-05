#ifndef CCREATETEXTURE_H
#define CCREATETEXTURE_H

#include "d3drender.h"
#include "color.h"
#include <string>

class SRTexture
{
    enum eTextureSource{
        eTS_none,
        eTS_file,
        eTS_mem
    };

    friend class proxyIDirect3DDevice9;
public:
    SRTexture(int width, int height);
    virtual ~SRTexture();

    virtual void Begin();
    virtual void End();

    virtual bool Clear( SRColor color = 0 );
    virtual bool Render( int X, int Y, int W = -1, int H = -1, float R = 0.0f );
    virtual HRESULT Save( const wchar_t* fileName );
    virtual HRESULT Load( const wchar_t* fileName );
    virtual HRESULT Load( unsigned int addr, unsigned int size );
    virtual bool textureSizeAsBkg();

    virtual void ReInit( int width, int height );

    virtual ID3DXSprite* GetSprite();
    virtual IDirect3DTexture9* GetTexture();

protected:
    void Release();
    void Initialize( IDirect3DDevice9 *pDevice = nullptr );
    virtual void LoadTexture( const wchar_t* fileName );
    virtual void LoadTexture( unsigned int addr, unsigned int size );
    virtual bool Draw(IDirect3DTexture9 *texture, int X, int Y, int W = -1, int H = -1, float R = 0.0f );

    ID3DXSprite*			pSprite = nullptr;
    IDirect3DTexture9*		pTexture = nullptr;
    POINT					textureSize;
    IDirect3DDevice9*		pDevice = nullptr;

    IDirect3DTexture9*		pTexture_bkg = nullptr;
    POINT					textureSize_bkg;
    eTextureSource          source_bkg = eTS_none;
    std::wstring             path_bkg;
    unsigned int            addr_bkg = 0;
    unsigned int            size_bkg = 0;

    bool					isRenderToTexture = false;
    bool					isReleased = true;
    bool                    kIsCalledFirstInitialize = false;

private:
    LPDIRECT3DSURFACE9      PP1S = NULL;
    LPDIRECT3DSURFACE9      DS = NULL;
    LPDIRECT3DSURFACE9		OldRT = NULL, OldDS = NULL;

    CD3DRender              *render = nullptr;
};

#endif // CCREATETEXTURE_H
