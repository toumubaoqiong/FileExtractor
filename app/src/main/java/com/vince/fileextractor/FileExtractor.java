package com.vince.fileextractor;

import java.io.UnsupportedEncodingException;

public class FileExtractor
{
	public static boolean fileExtractor( String sourcePath, String targetPath )
	{
		byte[] sourcePathBytes = null;
		byte[] targetPathBytes = null;
		
		try
		{
			sourcePathBytes = sourcePath.getBytes( "UTF-8" );
			targetPathBytes = targetPath.getBytes( "UTF-8" );
		}
		catch ( UnsupportedEncodingException e )
		{
			e.printStackTrace( );
		}
		
		return fileextractorNative( sourcePathBytes, sourcePathBytes.length, targetPathBytes, targetPathBytes.length );
	}

	private FileExtractor( )
	{
		
	}
	
	static
	{
		System.loadLibrary( "FileExtractor" );
		System.loadLibrary( "JNIUtil" );
		System.loadLibrary( "FileExtractor-jni" );
	}
	
	private native static boolean fileextractorNative( byte[] sourcePath, int sourcePathLen, byte[] targetPath, int targetPathLen );
}
