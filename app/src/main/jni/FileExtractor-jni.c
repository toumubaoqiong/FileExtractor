#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <jni.h>
#include <android/log.h>

#include "./FileExtractor.h"
#include "./JNIUtil.h"

#define FE_LOG_TAG 							"JNIFEPrint"
#define FE_PRINT(...)						__android_log_print(ANDROID_LOG_INFO,FE_LOG_TAG,__VA_ARGS__)
#define FE_WITHOUT_PATH_PRINT(...)			__android_log_print(ANDROID_LOG_INFO,FE_LOG_TAG,__VA_ARGS__)

#define MAX_WRITE_BUFFLEN					(1024<<4)//16k
static __inline int
error( fex_err_t err )
{
	if ( err != NULL )
	{
		FE_PRINT( "error:%s\n", err );
		return -1;
	}

	return 0;
}

unsigned int
FileExtractor_FileFilter( char* const pFileName )
{
	unsigned int isFilter = 0;
	return isFilter;
}

#define DIR_MODE 		( S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH | S_IXOTH )

unsigned int
FileExtractor_MikDir( char* const pFilePath, const int pathLen )
{
	unsigned int isMikDir = 1;

	do
	{
		int i = 0;

		if ( NULL == pFilePath )
		{
			isMikDir = 0;
			break;
		}

		for ( i = 1; i < pathLen; i++ )
		{
			if ( ( '\\' == pFilePath[i] || '/' == pFilePath[i] ) && ':' != pFilePath[i - 1] )
			{
				pFilePath[i] = '\0';
				if ( -1 == access( (char*) pFilePath, F_OK ) )
				{
					if ( -1 == mkdir( (char*) pFilePath, DIR_MODE ) )
					{
						FE_PRINT( "-1 == mkdir( %s )", pFilePath );
						isMikDir = 0;
						break;
					}
				}

				pFilePath[i] = '/';
			}
		}
	}
	while ( 0 );

	return isMikDir;
}

static int
process_file( fex_t* fex, char* pPath, int isGBk )
{
	int reVal = 0;

	FILE* file = NULL;
	char* pData = (char*) NULL;

	do
	{
		char* pFileName = (char*) fex_name( fex );
		char filePath[1024] =
		{ 0 };
		int pPathSize = (int) strlen( pPath );
		int nameLen = (int) strlen( pFileName );
		char fileNameUtf8[520] =
		{ 0 };

		memcpy( (char*) filePath, pPath, pPathSize );

		if ( 0 != isGBk )
		{
			nameLen = GB2312_To_UTF8( (unsigned char*) fileNameUtf8, (unsigned char*) pFileName );
			pFileName = fileNameUtf8;
		}

		memcpy( (char*) ( filePath + pPathSize ), (char*) pFileName, nameLen );

		if ( FileExtractor_FileFilter( pFileName ) )
		{
			FE_PRINT( "FileExtractor_FileFilter( pFileName )" );
			reVal = -1;
			break;
		}

		if ( !FileExtractor_MikDir( (char*) filePath, ( pPathSize + nameLen ) ) )
		{
			FE_PRINT( "!FileExtractor_MikDir( (char*) filePath, ( pPathSize + nameLen ) )" );
			reVal = -1;
			break;
		}

		/* Must be called before using fex_size() */
		if ( ( reVal = error( fex_stat( fex ) ) ) != 0 )
		{
			break;
		}

		file = fopen( filePath, "wb" );

		FE_PRINT( "\nProcess_file %s\n", pFileName );

		unsigned int curWriteSize = 0;
		unsigned int totalFileSize = fex_size( fex );
		unsigned int buffLen = 0;
		unsigned int writeBytes = 0;
		buffLen = ( MAX_WRITE_BUFFLEN < totalFileSize ) ? MAX_WRITE_BUFFLEN : totalFileSize;

		pData = (char*) malloc( sizeof(char) * buffLen );

		if ( (char*) NULL == pData )
		{
			break;
		}

		//FE_PRINT( ">>>>>>>>>>>>>>>>>>>>>>>Process_file_start<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n" );
		while ( curWriteSize < totalFileSize )
		{
			writeBytes = totalFileSize - curWriteSize;
			if ( writeBytes > buffLen )
			{
				writeBytes = buffLen;
			}

			/* Get pointer to extracted data. Fex will automatically free this later. */
			if ( ( reVal = error( fex_read( fex, pData, writeBytes ) ) ) != 0 )
			{
				break;
			}

			if ( writeBytes != fwrite( pData, 1, writeBytes, file ) )
			{
				reVal = -1;
				break;
			}

			curWriteSize += writeBytes;
		}

		//FE_PRINT( ">>>>>>>>>>>>>>>>>>>>>>>Process_file_end<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n" );
	}
	while ( 0 );

	if ( file != NULL )
	{
		fclose( file );
	}

	if ( pData != (char*) NULL )
	{
		free( pData );
	}

	return reVal;
}

static int
FileExtractor( char* sourcePath, char* targetPath )
{
	int reVal = 0;
	fex_t* fex = NULL;

	FE_PRINT( "FileExtractor...............in\n" );

	do
	{
		if ( ( reVal = error( fex_open( &fex, sourcePath ) ) ) != 0 )
		{
			FE_PRINT( "fex_open...............faild!\n" );
			break;
		}

		int isGBk = 1;
		int srcLen = (int) strlen( sourcePath );
		if ( '.' == sourcePath[srcLen - 3] && '7' == sourcePath[srcLen - 2] && ( 'z' == sourcePath[srcLen - 1] || 'Z' == sourcePath[srcLen - 1] ) )
		{
			isGBk = 0;
		}

		/* Scan archive headers */
		while ( !fex_done( fex ) )
		{
			if ( ( reVal = process_file( fex, targetPath, isGBk ) ) != 0 )
			{
				break;
			}

			if ( ( reVal = error( fex_next( fex ) ) ) != 0 )
			{
				break;
			}
		}
	}
	while ( 0 );

	if ( fex != NULL )
	{
		fex_close( fex );
		fex = (fex_t*) NULL;
	}

	FE_PRINT( "FileExtractor...............Out\n" );

	return !reVal;
}

jint
JNI_OnLoad( JavaVM* vm, void* reserved )
{
	FE_PRINT( "JNI_OnLoad .... " );

	return JNI_VERSION_1_4;
}

JNIEXPORT void JNICALL
JNI_OnUnload( JavaVM *vm, void *reserved )
{
	FE_PRINT( "JNI_OnUnload .... " );
}

//private native static boolean fileextractorNative( byte[] sourcePath, int sourcePathLen, byte[] targetPath, int targetPathLen );
JNIEXPORT jboolean JNICALL

Java_com_vince_fileextractor_FileExtractor_fileextractorNative( JNIEnv* env, jobject thiz, jbyteArray sourcePath, jint sourcePathLen, jbyteArray targetPath, jint targetPathLen )
{
	jboolean isInitSuccess = 0;
	char sourcePathUTF8[1024] =
	{ 0 };
	char targetPathUTF8[1024] =
	{ 0 };

	//获取源文件路径
	( *env )->GetByteArrayRegion( env, sourcePath, 0, sourcePathLen, (jbyte*) sourcePathUTF8 );
	//获取目标文件路径
	( *env )->GetByteArrayRegion( env, targetPath, 0, targetPathLen, (jbyte*) targetPathUTF8 );

	isInitSuccess = FileExtractor( (char*) sourcePathUTF8, (char*) targetPathUTF8 );

	FE_PRINT( "isInitSuccess = %d", isInitSuccess );

	return isInitSuccess;
}