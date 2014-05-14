//--------------------------------------------------------------------
#include "SoStringHelp.h"
//--------------------------------------------------------------------
#define Global_Buff_Size 2048
//
char g_szBuff[Global_Buff_Size] = {0};
//--------------------------------------------------------------------
const char* SoStringHelp::PathNormalize(const char* pszString)
{
	int nCount = 0;
	while (pszString[nCount] != 0)
	{
		char theC = pszString[nCount];
		if (theC >= 'A' && theC <= 'Z')
		{
			//大写字母转换为小写字母
			theC += 32;
		}
		else if (theC == '\\')
		{
			theC = '/';
		}
		g_szBuff[nCount] = theC;
		//
		++nCount;
		if (nCount >= Global_Buff_Size)
		{
			g_szBuff[Global_Buff_Size-1] = 0;
			break;
		}
	}
	if (nCount < Global_Buff_Size)
	{
		g_szBuff[nCount] = 0;
	}
	return g_szBuff;
}
//--------------------------------------------------------------------
