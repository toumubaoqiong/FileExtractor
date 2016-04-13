
#ifndef __PRINT_H__
#define __PRINT_H__

#include <stdio.h>
#include <stdarg.h>

#ifdef __cplusplus
extern "C"
{
#endif  /* __cplusplus */

//#define PRINT_PRINTF

#if defined( PRINT_PRINTF ) && defined( MAKE_FOR_ANDROID )

#ifdef FE_PRINT
#undef FE_PRINT
#endif

#ifdef FE_WITHOUT_PATH_PRINT
#undef FE_WITHOUT_PATH_PRINT
#endif

#include <android/log.h>
#define LOG_TAG 							"FileExtractorPrint"
#define FE_PRINT(...)						__android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define FE_WITHOUT_PATH_PRINT(...)			__android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)

//#define LOGE(...)				__android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)
//#define FE_PRINT				LOGI
//#define FE_WITHOUT_PATH_PRINT	LOGI

#endif

#if !defined( MAKE_FOR_ANDROID )

#ifndef PRINT_PRINTF
#	define FE_PRINT
#else
#	ifdef WIN32
#		define FE_PRINT FE_Print("%s_%d:", __FILE__, __LINE__);FE_Print
#	else
#		define FE_PRINT printf("%s_%d:", __FILE__, __LINE__);printf
#	endif
#endif

#ifndef PRINT_PRINTF
#	define FE_WITHOUT_PATH_PRINT
#else
#	ifdef WIN32
#		define FE_WITHOUT_PATH_PRINT Print
#	else
#		define FE_WITHOUT_PATH_PRINT printf
#	endif
#endif

#ifdef PRINT_PRINTF
int FE_Print( const char *format, ... );
#endif

#endif /* !defined( MAKE_FOR_ANDROID ) */

#if !defined( PRINT_PRINTF )
#	define FE_PRINT
#	define FE_WITHOUT_PATH_PRINT
#endif

#ifdef __cplusplus
}
#endif  /* __cplusplus */

#endif
