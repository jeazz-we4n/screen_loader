#ifndef ContextMenu_H
#define ContextMenu_H

#include <vector>
#include "NodeMenu.h"
#include "Text.h"

class CContextMenu : public CNodeMenu
{
public:
    CContextMenu( CNodeMenu* parent = nullptr, SRColor color = 0xE8283848 );
    virtual ~CContextMenu();

    virtual void onDraw( int = 0, int = 0 );
    virtual bool onEvents( HWND, UINT, WPARAM, LPARAM );

    virtual bool isInizialize();

    virtual void SetPosition( POINT );

    virtual void AddVariant( const std::string& text, SRColor = (SRColor)-1 );
    virtual void SetDescription( const std::string& );

protected:
    std::vector<CText*> _vars;

    SRColor _color;

    bool isMouseOnVariant( int );

private:
    bool _Init = false;
};

#endif // ContextMenu_H
