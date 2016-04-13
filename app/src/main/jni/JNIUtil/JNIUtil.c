
#include "JNIUtil.h"
#include "JNIUtilPrint.h"
#include "EncodeTransform.h"

//#if defined( MAKE_FOR_ANDROID )

	//    const jchar *GetStringChars(jstring str, jboolean *isCopy) {
	//        return functions->GetStringChars(this,str,isCopy);
	//    }
	//    void ReleaseStringChars(jstring str, const jchar *chars) {
	//        functions->ReleaseStringChars(this,str,chars);
	//    }
	//	 jsize GetStringLength(jstring str) {
	//	        return functions->GetStringLength(this,str);
	//	    }
	//    jstring NewString(const jchar *unicode, jsize len) {
	//        return functions->NewString(this,unicode,len);
	//    }

int JstringToCChar( JNIEnv* env, jstring jstr, char* cstr, int cstrLen )
{
	int len = 0;
	jsize jstrLen = 0;
	const jchar* pJchar = NULL;
	unsigned char* pSStr = NULL;

	do
	{
		jstrLen = ( *env )->GetStringLength( env, jstr )<<1;
		if( 0 == jstrLen || jstrLen > cstrLen )
		{
			break;
		}

		pSStr = (unsigned char*)malloc( jstrLen + 2 );
		if( NULL == pSStr )
		{
			break;
		}

		memset( (char*)pSStr, 0x00, jstrLen + 2 );

		pJchar = ( *env )->GetStringChars( env, jstr, 0 );

		if( NULL == pJchar )
		{
			break;
		}

		memcpy( (char*)pSStr, (char*)pJchar, jstrLen );

		len = EncodeTransForm( TRANSFORM_TYPE_UNICODE_TO_GB2312, cstr, pSStr );

		( *env )->ReleaseStringChars( env, jstr, pJchar );
	}
	while( 0 );

	if( pSStr != NULL )
	{
		free( (void*)pSStr );
	}

	return len;
}

/** C转JC 哈哈哈*/
jstring CCharToJstring( JNIEnv* env, char* cstr, int cstrLen )
{
	unsigned char* pTStr = NULL;
	jsize len = 0;
	jstring jStr;

	do
	{
		pTStr = (unsigned char*)malloc( ( cstrLen<<1 ) + 2 );
		if( NULL == pTStr )
		{
			break;
		}

		memset( (char*)pTStr, 0x00, ( cstrLen<<1 ) + 2 );

		len = (jsize)EncodeTransForm( TRANSFORM_TYPE_GB2312_To_UNICODE, pTStr, cstr );

		jStr = ( *env )->NewString( env, (jchar*)pTStr, (len>>1) );
	}
	while( 0 );

	if( pTStr != NULL )
	{
		free( (void*)pTStr );
	}

	return jStr;
}

void ChangeNewLineMark( char* cstr, int cstrLen )
{
	if( cstr != NULL )
	{
		int i = 0;
		for( i = 0; i < cstrLen; i++ )
		{
			if( 0x0d == cstr[i] )
			{
				cstr[i] = 0x0a;
			}
		}
	}
}

int GB2312_To_UTF8( unsigned char* pTStr, unsigned char* pSStr )
{
	return EncodeTransForm( TRANSFORM_TYPE_GB2312_To_UTF8, pTStr, pSStr );
}

int UTF8_To_GB2312( unsigned char* pTStr, unsigned char* pSStr )
{
	return EncodeTransForm( TRANSFORM_TYPE_UTF8_To_GB2312, pTStr, pSStr );
}

//#endif
