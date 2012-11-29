#pragma once

#include <QObject>
#include <QSize>
#include <QList>
//------------------------------------------------------------------------------
class DisplayMode
{
public:
    DisplayMode( int width, int height, int bpp = 0 )
        : m_size( QSize(width, height) )
        , m_bpp( bpp )
    {}

    DisplayMode( const DisplayMode& mode )
        : m_size( mode.m_size )
        , m_bpp( mode.m_bpp )
    {}

    inline QSize size() const {
        return m_size;
    }
    inline int width() const {
        return m_size.width();
    }
    inline int height() const {
        return m_size.height();
    }
    inline int bitsPerPixel() const {
        return m_bpp;
    }

private:
    QSize m_size;
    quint16 m_bpp;
};
//------------------------------------------------------------------------------
class UFullscreenWrapper
{
public:
    typedef QList<DisplayMode> DisplayModes;
public:
    explicit UFullscreenWrapper(QWidget* parent);

    DisplayModes enumModes();
    bool changeToMode( const DisplayMode& mode );
    bool changeToMode( int width, int height, int bpp = 0 );
    bool restoreMode();


private:
    DisplayModes m_displayModes;
    QWidget* m_parent;
};
//------------------------------------------------------------------------------
