#include "ContextMenu.h"
#include "Menu.h"

CContextMenu::CContextMenu(CNodeMenu* parent, SRColor color ) : CNodeMenu( parent )
{
    if (parent == nullptr)
        throw "Parent for CContextMenu can't be null";
    _color = color;
    _width = 0;
    _height = 0;
    _Init = false;
}

CContextMenu::~CContextMenu()
{
    for ( size_t i = 0; i < _vars.size(); ++i )
        delete _vars[i];
}

bool CContextMenu::isInizialize()
{
    if ( _Init )
        return true;

    if ( !CNodeMenu::isInizialize() )
        return false;

    if ( _menu == nullptr )
        return false;

    for ( size_t i = 0; i < _vars.size(); ++i ){
        _vars[i]->SetMenu( _menu );
        if ( !_vars[i]->isInizialize() )
            return false;
    }

    for ( size_t i = 0; i < _vars.size(); ++i ){
        if ( _vars[i]->Width() + 3 > _width )
            _width = _vars[i]->Width() + 3;
    }

    _height = static_cast<int>(_font->DrawHeight() * _vars.size() + 5);

    if ( _pos.y + _height > SCREEN_Y )
        _pos.y = SCREEN_Y - _height;
    if ( _pos.x + _width > SCREEN_X )
        _pos.x = SCREEN_X - _width;

    _Init = true;
    return true;
}

void CContextMenu::AddVariant(const std::string& text, SRColor color )
{
    auto var = new CText( text, color, this );
    var->SetMenu( _menu );
    _vars.push_back( var );

    if ( _Init ){
        if ( var->Width() + 3 > _width )
            _width = var->Width() + 3;
        _height = static_cast<int>(_font->DrawHeight() * _vars.size() + 5);
    }
}

void CContextMenu::SetDescription( const std::string& desc )
{
    _vars[_vars.size() - 1]->SetDescription( desc );
}

void CContextMenu::onDraw( int so_V, int so_H )
{
    if ( !isInizialize() )
        return;

    _draw->D3DBoxBorder( static_cast<float>(_pos.x - 1), static_cast<float>(_pos.y - 1), static_cast<float>(_width), static_cast<float>(_height), _color.invert(), _color );

    for ( size_t i = 0; i < _vars.size(); ++i ){
        if ( isMouseOnVariant( static_cast<int>(i) ) )
            _draw->D3DBox( static_cast<float>(_pos.x + 1), static_cast<float>(_pos.y + i * _font->DrawHeight() + 1),
                           static_cast<float>(_vars[i]->Width() - 1), static_cast<float>(_vars[i]->Height() + 1), _color.invert() );

        _vars[i]->SetPosition( _pos );
        _vars[i]->onDraw( -static_cast<int>(i * _font->DrawHeight()) );
    }
}

bool CContextMenu::onEvents( HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
    if ( !isInizialize() )
        return true;

    SetMousePos( GetMousePos() );
    if ( uMsg == WM_LBUTTONDOWN ){
        for ( size_t i = 0; i < _vars.size(); ++i ){
            if ( isMouseOnVariant( static_cast<int>(i) ) ){
                return false;
            }
        }
        if ( isMouseOnWidget() )
            (void)0;
        return false;
    }

    return true;
}

bool CContextMenu::isMouseOnVariant( int id )
{
    if ( _MP.x > _pos.x &&
         _MP.x < _pos.x + _vars[id]->Width() &&
         _MP.y > _pos.y + id * _font->DrawHeight() &&
         _MP.y < (_pos.y + id * _font->DrawHeight()) + _vars[id]->Height() )
        return true;
    return false;
}

void CContextMenu::SetPosition( POINT pos )
{
    if ( pos.y + _height > SCREEN_Y )
        pos.y = SCREEN_Y - _height;
    if ( pos.x + _width > SCREEN_X )
        pos.x = SCREEN_X - _width;

    return CNodeMenu::SetPosition( pos );
}
