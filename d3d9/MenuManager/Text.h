#ifndef Text_H
#define Text_H

#include "NodeMenu.h"
#include <string>

class CText : public CNodeMenu
{
public:
    CText( const std::string& text, SRColor color, CNodeMenu* parent = nullptr, POINT pos = { 0, 0 }, CD3DFont* font = nullptr, bool deleteFont = false );

    virtual bool isInizialize();

    virtual void onDraw( int = 0, int = 0 );

    virtual void setText( const std::string& );
    virtual std::string text();

    virtual void setColor( SRColor );
    virtual SRColor color();

protected:
    std::string _text;
    SRColor _color;

private:
    bool _Init = false;
};

#endif // Text_H
