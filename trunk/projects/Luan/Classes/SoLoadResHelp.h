//--------------------------------------------------------------------
#ifndef _SoLoadResHelp_h_
#define _SoLoadResHelp_h_
//--------------------------------------------------------------------
#include "LsCommon.h"
//--------------------------------------------------------------------
class SoLoadResHelp
{
public:
	//load plist, including it specified png file
	static void LoadPlistTexture(const char* pPlistFile);
	//remove plist, including it specified png file
	static void ReleasePlistTexture(const char* pPlistFile);

	static CCSprite* CreateSpriteWithTex(const char* pTexName, const TextureResType theResType);
	static bool SetTexForSprite(CCSprite* pSprite, const char* pTexName, const TextureResType theResType);

	static void SetTexForImageView(UIImageView* pImageView, const char* pTexName, const TextureResType theResType);

	//backup old PixelFormat, and set new PixelFormat
	static void SetPixelFormat(CCTexture2DPixelFormat theFormat);
	//restore old PixelFormat
	static void RestorePixelFormat();
};
//--------------------------------------------------------------------
#endif //_SoLoadResHelp_h_
//--------------------------------------------------------------------
