
#ifndef __FILE_SYSTEM_H__
#define __FILE_SYSTEM_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C"
{
#endif

#ifdef FS_FILE
#undef FS_FILE
#endif

#ifdef FS_O_RDONLY
#undef FS_O_RDONLY
#endif

#ifdef fs_fopen
#undef fs_fopen
#endif

#ifdef fs_fclose
#undef fs_fclose
#endif

#ifdef fs_fseek
#undef fs_fseek
#endif

#ifdef fs_fread
#undef fs_fread
#endif

#ifdef fs_fwrite
#undef fs_fwrite
#endif

#ifdef fs_ftell
#undef fs_ftell
#endif

#define FS_FILE				FILE
#define FS_O_RDONLY			"rb"

void fs_fclose( FS_FILE* pFile );
FS_FILE* fs_fopen( char* const pPath, char* const pMode );
unsigned int fs_abs_read( void* buff, unsigned int long offset, unsigned long len, FS_FILE* pFile );
int fs_fseek( FS_FILE *pFile, long offset, int fromwhere );
size_t fs_fread( void *buffer, size_t size, size_t count, FS_FILE *pFile );
size_t fs_fwrite( const void* buffer, size_t size, size_t count, FS_FILE* pFile );
long fs_ftell( FS_FILE *pFile );

#ifdef __cplusplus
}
#endif

#endif
