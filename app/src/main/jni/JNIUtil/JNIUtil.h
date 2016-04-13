
#ifndef __JNI_UTIL_H__
#define __JNI_UTIL_H__

#include <jni.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C"
{
#endif /** __cplusplus*/

int JstringToCChar( JNIEnv* env, jstring jstr, char* cstr, int cstrLen );
jstring CCharToJstring( JNIEnv* env, char* cstr, int cstrLen );
void ChangeNewLineMark( char* cstr, int cstrLen );
int GB2312_To_UTF8( unsigned char* pTStr, unsigned char* pSStr );
int UTF8_To_GB2312( unsigned char* pTStr, unsigned char* pSStr );

#ifdef __cplusplus
}
#endif /** __cplusplus*/

#endif /** __JNI_UTIL_H__*/
