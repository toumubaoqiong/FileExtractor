
#include "Code_Conversion.h"
#include "Code_Conversion_Common.h"

#define CODE_CONVERSION_BIG_MODE

namespace Code_Conversion
{
	int CodeConversion::Conversion( enum SCHEME_MODE shcemeMode, unsigned char* pTStr, unsigned char* pSStr )
	{
		int tStrlen = 0;

		do
		{
			if( NULL == pSStr || NULL == pTStr )
			{
				break;
			}
			switch( shcemeMode )
			{
				case UTF8_To_Unicode:
				{
					tStrlen = _Conversion_UTF8_To_Unicode( pTStr, pSStr );
					break;
				}

				case Unicode_To_UTF8:
				{
					tStrlen = _Conversion_Unicode_To_UTF8( pTStr, pSStr );
					break;
				}

				case Unicode_To_GB2312:
				{
					tStrlen = _Conversion_Unicode_To_GB2312( pTStr, pSStr );
					break;
				}

				case GB2312_To_Unicode:
				{
					tStrlen = _Conversion_GB2312_To_Unicode( pTStr, pSStr );
					break;
				}

				case UTF8_To_GB2312:
				{
					tStrlen = _Conversion_UTF8_To_GB2312( pTStr, pSStr );
					break;
				}

				case GB2312_To_UTF8:
				{
					tStrlen = _Conversion_GB2312_To_UTF8( pTStr, pSStr );
					break;
				}

				default:
				{
					break;
				}
			}
		}
		while( 0 );

		return tStrlen;
	}

	int CodeConversion::_UTF8_GetBytes( unsigned char ch )
	{
		unsigned char c = 0x80;
		int count = 0;
		while(ch&c)
		{
			count++;
			c>>=1;
		}

		return count;
	}

	int CodeConversion::
		_Conversion_UTF8_To_Unicode( unsigned char* pTStr, unsigned char* pSStr )
	{
		int sStrLen = strlen(reinterpret_cast<const char*>(pSStr));
		int i = 0;
		int nBytes = 0;
		int tStrLen = 0;

		do
		{
			while(i < sStrLen)
			{
				nBytes = _UTF8_GetBytes(pSStr[i]);
				switch(nBytes)
				{
					case 0: //0xxxxxxx
					{
#ifdef CODE_CONVERSION_BIG_MODE
					    pTStr[tStrLen++] = 0;
                        pTStr[tStrLen++] = pSStr[i];
#else
						pTStr[tStrLen++] = pSStr[i];
						pTStr[tStrLen++] = 0;
#endif
						nBytes = 1;
						break;
					}

					case 1:
					{
						break;
					}

					case 2: //110xxxxx 10xxxxxx
					{
#ifdef CODE_CONVERSION_BIG_MODE
					    pTStr[tStrLen++] = (pSStr[i]>>2)&0x07;
                        pTStr[tStrLen++] = ((pSStr[i]<<6)&0xC0) | (pSStr[i + 1]&0x3F);
#else
						pTStr[tStrLen++] = ((pSStr[i]<<6)&0xC0) | (pSStr[i + 1]&0x3F);
						pTStr[tStrLen++] = (pSStr[i]>>2)&0x07;
#endif
						break;
					}

					case 3: //1110xxxx 10xxxxxx 10xxxxxx 
					{
#ifdef CODE_CONVERSION_BIG_MODE
					    pTStr[tStrLen++] = (pSStr[i]<<4)&0xF0 | ((pSStr[i + 1]>>2)&0x0F);
                        pTStr[tStrLen++] = ((pSStr[i + 1]<<6)&0xC0) | (pSStr[i + 2]&0x3F);
#else
						pTStr[tStrLen++] = ((pSStr[i + 1]<<6)&0xC0) | (pSStr[i + 2]&0x3F);
						pTStr[tStrLen++] = (pSStr[i]<<4)&0xF0 | ((pSStr[i + 1]>>2)&0x0F);
#endif
						break;
					}

					case 4: //11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
					{
#ifdef CODE_CONVERSION_BIG_MODE
					    pTStr[tStrLen++] = 0;
                        pTStr[tStrLen++] = (pSStr[i]<<2)&0x1C | ((pSStr[i + 1]>>4)&0x03);
                        pTStr[tStrLen++] = ((pSStr[i + 1]<<4)&0xF0) | ((pSStr[i + 2]>>2)&0x0F);
                        pTStr[tStrLen++] = ((pSStr[i + 2]<<6)&0xC0) | (pSStr[i + 3]&0x3F);
#else
						pTStr[tStrLen++] = (pSStr[i]<<2)&0x1C | ((pSStr[i + 1]>>4)&0x03);
						pTStr[tStrLen++] = 0;
						pTStr[tStrLen++] = ((pSStr[i + 2]<<6)&0xC0) | (pSStr[i + 3]&0x3F);
						pTStr[tStrLen++] = ((pSStr[i + 1]<<4)&0xF0) | ((pSStr[i + 2]>>2)&0x0F);
#endif
						break;
					}

					case 5: //1111110x 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx
					{
#ifdef CODE_CONVERSION_BIG_MODE
					    pTStr[tStrLen++] = pSStr[i]&0x01;
                        pTStr[tStrLen++] = ((pSStr[i + 1]<<2)&0xFC) | ((pSStr[i + 2]>>4)&0x03);
                        pTStr[tStrLen++] = (pSStr[i + 2]<<4)&0xF0 | ((pSStr[i + 3]>>2)&0x0F);
                        pTStr[tStrLen++] = ((pSStr[i + 3]<<6)&0xC0) | (pSStr[i + 4]&0x3F);
#else
						pTStr[tStrLen++] = ((pSStr[i + 1]<<2)&0xFC) | ((pSStr[i + 2]>>4)&0x03);
						pTStr[tStrLen++] = pSStr[i]&0x01;
						pTStr[tStrLen++] = ((pSStr[i + 3]<<6)&0xC0) | (pSStr[i + 4]&0x3F);
						pTStr[tStrLen++] = (pSStr[i + 2]<<4)&0xF0 | ((pSStr[i + 3]>>2)&0x0F);
#endif
						break;
					}

					case 6: //1111110x 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx 
					{
#ifdef CODE_CONVERSION_BIG_MODE
					    pTStr[tStrLen++] = ((pSStr[i]<<6)&0x40) | (pSStr[i + 1]&0x3F);
                        pTStr[tStrLen++] = ((pSStr[i + 2]<<2)&0xFC) | ((pSStr[i + 3]>>4)&0x03);
                        pTStr[tStrLen++] = (pSStr[i + 3]<<4)&0xF0 | ((pSStr[i + 4]>>2)&0x0F);
                        pTStr[tStrLen++] = ((pSStr[i + 4]<<6)&0xC0) | (pSStr[i + 5]&0x3F);
#else
						pTStr[tStrLen++] = ((pSStr[i + 2]<<2)&0xFC) | ((pSStr[i + 3]>>4)&0x03);
						pTStr[tStrLen++] = ((pSStr[i]<<6)&0x40) | (pSStr[i + 1]&0x3F);
						pTStr[tStrLen++] = ((pSStr[i + 4]<<6)&0xC0) | (pSStr[i + 5]&0x3F);
						pTStr[tStrLen++] = (pSStr[i + 3]<<4)&0xF0 | ((pSStr[i + 4]>>2)&0x0F);
#endif
						break;
					}

					default:
					{
						break;
					}
				}
				i += nBytes;
			}

			pTStr[tStrLen] = 0;
			pTStr[tStrLen + 1] = 0;
		}
		while( 0 );

		return tStrLen;
	}

	int CodeConversion::
		_Conversion_Unicode_To_UTF8( unsigned char* pTStr, unsigned char* pSStr )
	{
		int sStrLen = 0;
		int tStrLen = 0;
		int i = 0;
		unsigned short int	unicode = 0;

		do
		{
			sStrLen = 0;
			while( pSStr[sStrLen] || pSStr[sStrLen + 1] )
			{
				sStrLen += 2;
			}

			for( i = 0; i < sStrLen; i += 2 )
			{
#ifdef CODE_CONVERSION_BIG_MODE
                unicode = pSStr[i + 1];
                unicode = ((unicode<<8)&0xFF00) | (pSStr[i]&0x00FF);
#else
				unicode = pSStr[i];
				unicode = ((unicode<<8)&0xFF00) | (pSStr[i + 1]&0x00FF);
#endif
				//0xxxxxxx 
				if( unicode <= 0x007F )
				{
					pTStr[tStrLen++] = static_cast<unsigned char>(unicode&0x00FF);
				}
				//110xxxxx 10xxxxxx 
				else if(unicode >= 0x0080 && unicode <= 0x07FF)
				{
					pTStr[tStrLen++] = 0xC0 | (static_cast<unsigned char>((unicode>>6)&0x001F));
					pTStr[tStrLen++] = 0x80 | (static_cast<unsigned char>(unicode&0x003F));
				}
				//1110xxxx 10xxxxxx 10xxxxxx 
				else //if(unicode >= 0x0800 && unicode <= 0xFFFF)
				{
                    pTStr[tStrLen++] = 0xE0 | (static_cast<unsigned char>((unicode>>12)&0x000F));
					pTStr[tStrLen++] = 0x80 | (static_cast<unsigned char>((unicode>>6)&0x003F));
					pTStr[tStrLen++] = 0x80 | (static_cast<unsigned char>(unicode&0x003F));
				}
			}

			pTStr[tStrLen] = 0;
		}
		while( 0 );

		return tStrLen;
	}

	int CodeConversion::
		_Conversion_Unicode_To_GB2312( unsigned char* pTStr, unsigned char* pSStr )
	{
		int sStrLen = 0;
		int i = 0;
		int tStrLen = 0;
		unsigned short int temp = 0;
		do
		{
			sStrLen = 0;
			while( pSStr[sStrLen] || pSStr[sStrLen + 1] )
			{
				sStrLen += 2;
			}

			while( i < sStrLen )
			{
				if( 0x00 == pSStr[i + 1] )
				{
					/*
					** ���飬GB2312��ʾΪ gb=0xa4a1 ת��Ϊ unicode=0x00b7����Ӧ�� unicode=0x00b7 ҪתΪ  gb=0xa4a1
					*/
					if ( 0xb7 == pSStr[i])
					{
						pTStr[tStrLen++] = 0xa1;
						pTStr[tStrLen++] = 0xa4;
					}
					else
					{
						pTStr[tStrLen++] = pSStr[i];
					}
				}	
				else
				{
					temp = pSStr[i + 1];
					temp = ((temp<<8) | pSStr[i]);
					temp = Unicode2Gbk_Table[temp];
					pTStr[tStrLen++] = static_cast<unsigned char>(temp&0x00FF);
					pTStr[tStrLen++] = static_cast<unsigned char>((temp>>8)&0x00FF);
				}

				i += 2;
			}

			pTStr[tStrLen] = 0;
		}
		while( 0 );

		return tStrLen;
	}

	int CodeConversion::
		_Conversion_GB2312_To_Unicode( unsigned char* pTStr, unsigned char* pSStr )
	{
		int sStrLen = strlen(reinterpret_cast<const char*>(pSStr));
		int i = 0;
		int tStrLen = 0;
		unsigned short int temp = 0;

		do
		{
			while( i < sStrLen )
			{
				if( pSStr[i] < 0x80 )
				{
#ifdef CODE_CONVERSION_BIG_MODE
			        pTStr[tStrLen++] = pSStr[i++];
                    pTStr[tStrLen++] = 0;
#else
				    pTStr[tStrLen++] = 0;
				    pTStr[tStrLen++] = pSStr[i++];
#endif
				}	
				else
				{
					temp = pSStr[i + 1];
					temp = ((temp<<8) | pSStr[i]);
					temp = Gbk2Unicode_Table[temp];
#ifdef CODE_CONVERSION_BIG_MODE
                    pTStr[tStrLen++] = static_cast<unsigned char>(temp&0x00FF);
                    pTStr[tStrLen++] = static_cast<unsigned char>((temp>>8)&0x00FF);
#else
					pTStr[tStrLen++] = static_cast<unsigned char>((temp>>8)&0x00FF);
					pTStr[tStrLen++] = static_cast<unsigned char>(temp&0x00FF);
#endif
					i += 2;
				}
			}

			pTStr[tStrLen] = 0;
			pTStr[tStrLen + 1] = 0;
		}
		while( 0 );

		return tStrLen;
	}

	int CodeConversion::_Conversion_GB2312_To_UTF8( unsigned char* pTStr, unsigned char* pSStr )
	{
		int sStrLen = strlen( reinterpret_cast<const char*>(pSStr) );
		int tempStrLen = (sStrLen<<3) + 2;
		unsigned char* pTempStr = new unsigned char[tempStrLen];
		int tStrLen = 0;

		do
		{
			if(NULL == pTempStr)
			{
				break;
			}

			memset( (char*)pTempStr, 0, tempStrLen );
			if( ( tStrLen = _Conversion_GB2312_To_Unicode( pTempStr, pSStr ) ) != 0 )
			{
				tStrLen = _Conversion_Unicode_To_UTF8( pTStr, pTempStr );
			}

			delete[] pTempStr;
			pTempStr = ( unsigned char* )NULL;
		}while(0);

		return tStrLen;
	}

	int CodeConversion::_Conversion_UTF8_To_GB2312( unsigned char* pTStr, unsigned char* pSStr )
	{
		int sStrLen = strlen( reinterpret_cast<const char*>(pSStr) );
		int tempStrLen = (sStrLen<<3) + 2;
		unsigned char* pTempStr = new unsigned char[tempStrLen];
		int tStrLen = 0;

		do
		{
			if( NULL == pTempStr )
			{
				break;
			}

			memset( (char*)pTempStr, 0, tempStrLen );
			if( ( tStrLen = _Conversion_UTF8_To_Unicode( pTempStr, pSStr ) ) != 0 )
			{
				tStrLen = _Conversion_Unicode_To_GB2312( pTStr, pTempStr );
			}

			delete[] pTempStr;
			pTempStr = (unsigned char* )NULL;
		}
		while( 0 );

		return tStrLen;
	}
}
