/* ------------------------------------------------------------------------*/
/*                                                                         */
/*   DRAWBUF.H                                                             */
/*                                                                         */
/*   defines the class TDrawBuffer, which provides the high-level          */
/*   interface to the Screen Manager.                                      */
/*                                                                         */
/* ------------------------------------------------------------------------*/
/*
 *      Turbo Vision - Version 2.0
 *
 *      Copyright (c) 1994 by Borland International
 *      All Rights Reserved.
 *
 */

#pragma option -Vo-
#if defined( __BCOPT__ ) && !defined (__FLAT__)
#pragma option -po-
#endif

#if defined( Uses_TDrawBuffer ) && !defined( __TDrawBuffer )
#define __TDrawBuffer

class TDrawBuffer
{

    friend class TSystemError;
    friend class TView;
    friend void genRefs();

public:

    void moveChar( ushort indent, char c, ushort attr, ushort count );
    void moveStr( ushort indent, const char _FAR *str, ushort attrs );
    void moveStr( ushort indent, TStringView str, ushort attrs );
    void moveStr( ushort indent, TStringView str, ushort attr, ushort width, ushort begin=0 );
    void moveCStr( ushort indent, const char _FAR *str, ushort attrs );
    void moveCStr( ushort indent, TStringView str, ushort attrs );
    void moveBuf( ushort indent, const void _FAR *source,
                  ushort attr, ushort count );
    void moveBuf( ushort indent, const TScreenCell _FAR *source, ushort count );

    void putAttribute( ushort indent, ushort attr );
    void putChar( ushort indent, ushort c );
    size_t length() const;

#ifdef __FLAT__
    static TSpan<TScreenCell> allocData();
    TDrawBuffer();
    ~TDrawBuffer();
#endif

protected:

#ifdef __FLAT__
    const TSpan<TScreenCell> data;
#else
    TScreenCell data[maxViewWidth];
#endif

};

#define loByte(w)    (((uchar *)&w)[0])
#define hiByte(w)    (((uchar *)&w)[1])

inline void TDrawBuffer::putAttribute( ushort indent, ushort attr )
{
    if (indent < length())
    {
        ::setAttr(data[indent], (uchar) attr);
    }
}

inline void TDrawBuffer::putChar( ushort indent, ushort c )
{
    if (indent < length())
    {
        ::setChar(data[indent], (uchar) c);
    }
}

inline size_t TDrawBuffer::length() const
{
#ifdef __FLAT__
    return data.size();
#else
    return maxViewWidth;
#endif
}

#endif  // Uses_TDrawBuffer

#pragma option -Vo.
#if defined( __BCOPT__ ) && !defined (__FLAT__)
#pragma option -po.
#endif

