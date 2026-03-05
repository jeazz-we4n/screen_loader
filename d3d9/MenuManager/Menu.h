#ifndef Menu_H
#define Menu_H

#define SCREEN_X *(int*)0x00C9C040
#define SCREEN_Y *(int*)0x00C9C044

#include "Node.h"
#include "ContextMenu.h"
#include <vector>
#include <string>

template<typename T> void VectorErase( std::vector<T> &vec, T v );
template<typename T> void myswap( T &a, T &b );

class CMenu;
extern std::vector<CMenu*> MenuList;

class CMenu : public CNodeMenu
{
    friend class CNodeMenu;
public:
    CMenu( const std::string& title, POINT size, CNodeMenu* parent = nullptr, CNode* node = nullptr );
    ~CMenu();

    virtual void onDraw( int = 0, int = 0 );
    virtual bool onEvents( HWND, UINT, WPARAM, LPARAM );

    virtual bool isInizialize();

    virtual void SetSize( POINT );
    virtual POINT Size();

    virtual CNode* Node();

    virtual void SetContextMenu( CContextMenu* );

    virtual bool isActive();

protected:
    SRTexture *_texture = nullptr;
    CNode *_node = nullptr;
    CContextMenu *_context = nullptr;

    std::string _title;
    POINT _size;
    int _header = 0;

    bool isMouseOnHeader();
    bool isMouseOnClose();

    virtual void SetMenuHelper( const std::string& );

    std::vector<std::string> p_helper;

private:
    bool _Init;

    bool _move;
    POINT _mvOffset;
};

void SetForeground( CMenu* menu );
bool IsForeground( CMenu*menu );

template<typename T>
inline void VectorErase( std::vector<T> &vec, T v )
{
    for ( size_t i = 0; i < vec.size(); ++i ){
        if ( vec[i] == v ){
            vec.erase( vec.begin() + static_cast<ptrdiff_t>(i) );
            break;
        }
    }
}

template<typename T>
inline void myswap( T &a, T &b )
{
    T c = a;
    a = b;
    b = c;
}

#endif // Menu_H
