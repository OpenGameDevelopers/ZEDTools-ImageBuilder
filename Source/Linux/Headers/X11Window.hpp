#ifndef __ZEDTOOL_IMAGEBUILDER_X11WINDOW_HPP__
#define __ZEDTOOL_IMAGEBUILDER_X11WINDOW_HPP__

#include <Window.hpp>
#include <X11/Xlib.h>

namespace ImageBuilder
{
	class X11Window : Window
	{
	public:
		X11Window( );
		virtual ~X11Window( );

		virtual int Initialise( const WINDOW_RECT &p_WindowRect );

	private:
		::Window	m_Window;
		Display		*m_pDisplay;
	};
}

#endif // __ZEDTOOL_IMAGEBUILDER_X11WINDOW_HPP__

