#ifndef __ZEDTOOL_IMAGEBUILDER_WINDOW_HPP__
#define __ZEDTOOL_IMAGEBUILDER_WINDOW_HPP__

namespace ImageBuilder
{
	typedef struct __tagWINDOW_RECT
	{
		int	X;
		int Y;
		int Width;
		int Height;
	}WINDOW_RECT;

	class Window
	{
	public:
		virtual ~Window( );

		virtual int Initialise( const WINDOW_RECT &p_WindowRect ) = 0;

	protected:
		// There should be a list of attachable UI elements (which are really
		// sub-windows)

		WINDOW_RECT	m_WindowRect;
	};
}

#endif // __ZEDTOOL_IMAGEBUILDER_WINDOW_HPP__

