
#ifndef __CODE_CONVERSION_H__
#define __CODE_CONVERSION_H__

namespace Code_Conversion
{
	enum SCHEME_MODE
	{
		UTF8_To_Unicode = 0,
		Unicode_To_UTF8,
		Unicode_To_GB2312,
		GB2312_To_Unicode,
		GB2312_To_UTF8,
		UTF8_To_GB2312,
	};

	class CodeConversion
	{
		public:
			CodeConversion(){ };
			~CodeConversion(){ };
			
			static int Conversion( enum SCHEME_MODE shcemeMode, unsigned char* pTStr, unsigned char* pSStr );

		private:
			CodeConversion( const CodeConversion& );
			CodeConversion operator = ( const CodeConversion& );

			static int _Conversion_UTF8_To_Unicode( unsigned char* pTargetStr, unsigned char* pSourceStr );
			static int _Conversion_Unicode_To_UTF8( unsigned char* pTargetStr, unsigned char* pSourceStr );
			static int _Conversion_Unicode_To_GB2312( unsigned char* pTargetStr,unsigned char* pSourceStr );
			static int _Conversion_GB2312_To_Unicode( unsigned char* pTargetStr, unsigned char* pSourceStr );
			static int _Conversion_GB2312_To_UTF8( unsigned char* pTargetStr, unsigned char* pSourceStr );
			static int _Conversion_UTF8_To_GB2312( unsigned char* pTargetStr, unsigned char* pSourceStr );
			static int _UTF8_GetBytes( unsigned char ch );
	};
}

#endif
