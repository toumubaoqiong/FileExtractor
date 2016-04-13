
#include "JNIUtilPrint.h"

#ifdef WIN32
#include <Windows.h>
#endif

#if defined( JNIUTIL_PRINT )

static int JNIUtil_Vprintf( const char *format, va_list arg )
{
#define OUTPUT_BUFFER_SIZE		4096

	static char _outputBuffer[ OUTPUT_BUFFER_SIZE ];

#ifdef WIN32
	_vsnprintf( _outputBuffer, OUTPUT_BUFFER_SIZE - 1, format, arg );
	_outputBuffer[ OUTPUT_BUFFER_SIZE - 1 ] = 0;

	OutputDebugString( _outputBuffer );

	return printf( _outputBuffer );
#else
	vsprintf( _outputBuffer, format, arg );
	return printf( _outputBuffer );
#endif

}

int JNIUtil_Print( const char *format, ... )
{
	va_list va;
	int ret = 0;

	va_start( va, format );
	ret = JNIUtil_Vprintf( format, va );
	va_end( va );

	return ret;
}

#endif
