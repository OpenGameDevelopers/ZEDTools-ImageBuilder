#include <X11Window.hpp>
#include <iostream>
#include <unistd.h>
#include <string.h>
#include <X11/Xutil.h>
#include <GitVersion.hpp>

namespace ImageBuilder
{
	X11Window::X11Window( )
	{
	}

	X11Window::~X11Window( )
	{
		if( m_pDisplay )
		{
			XCloseDisplay( m_pDisplay );
		}
	}

	int X11Window::Initialise( const WINDOW_RECT &p_WindowRect )
	{
		m_pDisplay = XOpenDisplay( NULL );

		if( !m_pDisplay )
		{
			std::cout << "Unable to open display" << std::endl;
			return 1;
		}

		int Depth;
		XVisualInfo VisualInfoTemplate;
		XVisualInfo VisualInfo;
		Visual		*pVisual;

		int ScreenNum = DefaultScreen( m_pDisplay );

		VisualInfoTemplate.screen = ScreenNum;

		int VisualCount;
		XGetVisualInfo( m_pDisplay, VisualScreenMask,
			&VisualInfoTemplate, &VisualCount );

		if( !XMatchVisualInfo( m_pDisplay, XDefaultScreen( m_pDisplay ), 32,
			TrueColor, &VisualInfo ) )
		{
			return 1;
		}

		XSync( m_pDisplay, True );

		pVisual = VisualInfo.visual;
		Depth = VisualInfo.depth;

		XSetWindowAttributes SetWindowAttributes;
		SetWindowAttributes.colormap = XCreateColormap( m_pDisplay,
			XDefaultRootWindow( m_pDisplay ), pVisual, AllocNone );
		SetWindowAttributes.background_pixmap = None;
		SetWindowAttributes.border_pixel = 0;
		SetWindowAttributes.background_pixel = XWhitePixel( m_pDisplay, 0 );
		SetWindowAttributes.event_mask = StructureNotifyMask | ExposureMask;

		m_WindowRect = p_WindowRect;

		m_Window = XCreateWindow( m_pDisplay,
			RootWindow( m_pDisplay, ScreenNum ),
			m_WindowRect.X, m_WindowRect.Y, m_WindowRect.Width,
			m_WindowRect.Height, 0, Depth, InputOutput, pVisual,	
			CWEventMask | CWBorderPixel | CWBackPixel | CWColormap,
			&SetWindowAttributes );

		XFontStruct	*pFontInfo;
		pFontInfo = XLoadQueryFont( m_pDisplay, "10x20" );
		XGCValues GCValues;
		GCValues.font = pFontInfo->fid;
		GCValues.foreground = XBlackPixel( m_pDisplay, 0 );
		GC GraphicContext;
		GraphicContext = XCreateGC( m_pDisplay, m_Window,
			GCFont + GCForeground, &GCValues );

		XStoreName( m_pDisplay, m_Window, "ZED Image Builder" );
		
		XMapWindow( m_pDisplay, m_Window );
		XMapRaised( m_pDisplay, m_Window );
		XMoveWindow( m_pDisplay, m_Window, m_WindowRect.X, m_WindowRect.Y );
		XRaiseWindow( m_pDisplay, m_Window );

		char MessageString [ 1024 ];
		memset( MessageString, '\0', sizeof( MessageString ) );
		sprintf( MessageString, "Ver. %s | Tag: %s | Branch: %s",
			GIT_BUILD_VERSION, GIT_TAG_NAME, GIT_BRANCH );
		int MessageLength = strlen( MessageString );
		XEvent Event;

		while( 1 )
		{
			XNextEvent( m_pDisplay, ( XEvent * )&Event );

			switch( Event.type )
			{
				case Expose:
				{
					XWindowAttributes WindowAttributes;
					int FontDirection, FontAscent, FontDescent;
					XCharStruct CharStruct;
					XTextExtents( pFontInfo, MessageString, MessageLength,
						&FontDirection, &FontAscent, &FontDescent,
						&CharStruct );
					XGetWindowAttributes( m_pDisplay, m_Window,
						&WindowAttributes );

					int TextX = ( WindowAttributes.width -
						CharStruct.width ) / 2;
					int TextY = ( WindowAttributes.height - (
						CharStruct.ascent + CharStruct.descent ) ) / 2;
					XDrawString( m_pDisplay, m_Window, GraphicContext,
						TextX, TextY,
						MessageString, MessageLength );

					break;
				}
				default:
				{
					break;
				}
			}
		}

		return 0;
	}
}

