// Separate file to avoid linking to f* functions unless user calls unrar_open_file()

#include "unrar.h"
#include "rar.hpp"
#include <stdio.h>

extern "C" {
	static unrar_err_t unrar_read_file( void* user_data, void* out, int* count, unrar_pos_t pos )
	{
		FS_FILE* file = (FS_FILE*)user_data;
		unsigned int readBytes = *count;
		// most of the time, seeking won't be necessary
		if ( (int)pos != fs_ftell( file ) && fs_fseek( file, (int)pos, SEEK_SET ) != 0 )
			return unrar_err_corrupt;
		
		*count = (int)fs_fread( out, 1, readBytes, file );
		
		if ( *count != (int)readBytes )
			return unrar_err_io;
		
		return unrar_ok;
	}
}

static void unrar_close_file( void* user_data )
{
	fs_fclose( (FS_FILE*)user_data );
}

unrar_err_t unrar_open( unrar_t** arc_out, char* path )
{
	*arc_out = (unrar_t*)NULL;
	
	FS_FILE* file = fs_fopen( path, (char*)"rb" );
	if ( NULL == file )
		return unrar_err_open;
	
	unrar_err_t err = unrar_open_custom( arc_out, &unrar_read_file, (void*)file );
	if ( err != unrar_ok )
		fs_fclose( file );
	else
		(*arc_out)->close_file = &unrar_close_file;
	
	return err;
}
