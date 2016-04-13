
#include "EncodeTransform.h"
#include "Code_Conversion.h"

int EncodeTransForm( enum TRANSFORM_TYPE transformType, unsigned char* pTStr, unsigned char* pSStr )
{
	Code_Conversion::SCHEME_MODE schemeMode = (Code_Conversion::SCHEME_MODE)transformType;

	return Code_Conversion::CodeConversion::Conversion( schemeMode, pTStr, pSStr );
}
