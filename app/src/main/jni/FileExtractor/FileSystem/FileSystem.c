
#include "FileSystem.h"
#include "./../Print/Print.h"

void fs_fclose( FS_FILE* pFile )
{
	if( pFile != NULL )
	{
		fclose( pFile );
	}
}

FS_FILE* fs_fopen( char* const pPath, char* const pMode )
{
	int i = 0;
	int pathLen = 0;
	char newPath[1024] = {0};

	if( NULL == pPath || NULL == pMode )
	{
		return NULL;
	}

	pathLen = strlen(pPath);
	for( i = 0; i < pathLen; i ++ )
	{
		if( '\\' == pPath[i] )
		{
			newPath[i] = '/';
		}
		else
		{
			newPath[i] = pPath[i];
		}
	}

	return fopen( newPath, pMode );
}

size_t fs_abs_read( void* buff, unsigned int long offset, unsigned long len, FS_FILE* pFile )
{
	fs_fseek( pFile, offset, SEEK_SET );
	return fs_fread( buff, len, 1, pFile );
}

int fs_fseek( FS_FILE *pFile, long offset, int fromwhere )
{
	return fseek( pFile, offset, fromwhere );
}

size_t fs_fread( void *buffer, size_t size, size_t count, FS_FILE *pFile )
{
	if( NULL == buffer || NULL == pFile )
	{
		return 0;
	}

	return fread( buffer, size, count, pFile );
}

size_t fs_fwrite( const void* buffer, size_t size, size_t count, FS_FILE* pFile )
{
	if( NULL == buffer || NULL == pFile )
	{
		return 0;
	}

	return fwrite( buffer, size, count, pFile );
}

long fs_ftell( FS_FILE *pFile )
{
	if( NULL == pFile )
	{
		return 0;
	}

	return ftell( pFile );
}
