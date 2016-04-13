
#ifndef __JNIUTIL_PRINT_H__
#define __JNIUTIL_PRINT_H__

#ifdef __cplusplus
extern "C"
{
#endif  /* __cplusplus */

#include <stdio.h>
#include <stdarg.h>

#define JNIUTIL_PRINT	//打印宏总开关


#if defined( JNIUTIL_PRINT ) && defined( MAKE_FOR_ANDROID )

#ifdef JU_PRINT
#undef JU_PRINT
#endif

#ifdef JU_WITHOUT_PATH_PRINT
#undef JU_WITHOUT_PATH_PRINT
#endif

#include <android/log.h>
#define JU_LOG_TAG 							"JNIUtilPrint"
#define JU_PRINT(...)						__android_log_print(ANDROID_LOG_INFO,JU_LOG_TAG,__VA_ARGS__)
#define JU_WITHOUT_PATH_PRINT(...)			__android_log_print(ANDROID_LOG_INFO,JU_LOG_TAG,__VA_ARGS__)

//#define LOGE(...)							__android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)
//#define FP_PRINT							LOGI
//#define FP_WITHOUT_PATH_PRINT				LOGI

#endif

#if !defined( MAKE_FOR_ANDROID )

#ifndef JNIUTIL_PRINT
#	define JU_PRINT
#else
#	ifdef WIN32
#		define JU_PRINT JNIUtil_Print("%s_%d:", __FILE__, __LINE__);JNIUtil_Print
#	else
#		define JU_PRINT printf("%s_%d:", __FILE__, __LINE__);printf
#	endif
#endif

#ifndef JNIUTIL_PRINT
#	define JU_WITHOUT_PATH_PRINT
#else
#	ifdef WIN32
#		define JU_WITHOUT_PATH_PRINT JNIUtil_Print
#	else
#		define JU_WITHOUT_PATH_PRINT printf
#	endif
#endif


#ifdef JNIUTIL_PRINT_PRINTF
int JNIUtil_Print( const char *format, ... );
#endif

#endif /* !defined( MAKE_FOR_ANDROID ) */

#ifdef __cplusplus
}
#endif  /* __cplusplus */

#endif
