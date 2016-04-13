
#ifndef __ENCODE_TRANSFORM_H__
#define __ENCODE_TRANSFORM_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C"
{
#endif /** __cplusplus*/

enum TRANSFORM_TYPE
{
	TRANSFORM_TYPE_UTF8_TO_UNICODE = 0,
	TRANSFORM_TYPE_UNICODE_TO_UTF8,
	TRANSFORM_TYPE_UNICODE_TO_GB2312,
	TRANSFORM_TYPE_GB2312_To_UNICODE,
	TRANSFORM_TYPE_GB2312_To_UTF8,
	TRANSFORM_TYPE_UTF8_To_GB2312
};

int EncodeTransForm( enum TRANSFORM_TYPE transformType, unsigned char* pTStr, unsigned char* pSStr );

#ifdef __cplusplus
}
#endif  /** __cplusplus*/

#endif  /** __ENCODE_TRANSFORM_H__ */
