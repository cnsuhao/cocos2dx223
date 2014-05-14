//--------------------------------------------------------------------
#include "SoLoadResHelp.h"
#include "SoStringHelp.h"
//--------------------------------------------------------------------
CCTexture2DPixelFormat g_oldPixelFormat = kCCTexture2DPixelFormat_Default;
//--------------------------------------------------------------------
void SoLoadResHelp::LoadPlistTexture(const char* pPlistFile)
{
	if (pPlistFile != NULL)
	{
		const char* newFileName = SoStringHelp::PathNormalize(pPlistFile);
		CCLOG("SoLoadResHelp::LoadPlistTexture : [%s]", newFileName);
		CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(newFileName);
	}
}
//--------------------------------------------------------------------
void SoLoadResHelp::ReleasePlistTexture(const char* pPlistFile)
{
	if (pPlistFile != NULL)
	{
		const char* newFileName = SoStringHelp::PathNormalize(pPlistFile);
		CCLOG("SoLoadResHelp::ReleasePlistTexture : [%s]", newFileName);
		CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile(newFileName, CCSpriteFrameCache::TextureOpration_Remove);
	}
}
//--------------------------------------------------------------------
CCSprite* SoLoadResHelp::CreateSpriteWithTex(const char* pTexName, const TextureResType theResType)
{
	if (pTexName == NULL)
	{
		return NULL;
	}

	if (theResType == UI_TEX_TYPE_LOCAL)
	{
		const char* newFileName = SoStringHelp::PathNormalize(pTexName);
		CCLOG("SoLoadResHelp::CreateSpriteWithTex : [local] [%s]", newFileName);
		return CCSprite::create(newFileName);
	}
	else if (theResType == UI_TEX_TYPE_PLIST)
	{
		return CCSprite::createWithSpriteFrameName(pTexName);
	}
	else
	{
		return NULL;
	}
}
//--------------------------------------------------------------------
bool SoLoadResHelp::SetTexForSprite(CCSprite* pSprite, const char* pTexName, const TextureResType theResType)
{
	if (pSprite == NULL)
	{
		return false;
	}
	if (pTexName == NULL)
	{
		return false;
	}

	if (theResType == UI_TEX_TYPE_LOCAL)
	{
		const char* newFileName = SoStringHelp::PathNormalize(pTexName);
		CCLOG("SoLoadResHelp::SetTexForSprite : [local] [%s]", newFileName);
		return pSprite->initWithFile(newFileName);
	}
	else if (theResType == UI_TEX_TYPE_PLIST)
	{
		return pSprite->initWithSpriteFrameName(pTexName);
	}
	else
	{
		return false;
	}
}
//--------------------------------------------------------------------
void SoLoadResHelp::SetTexForImageView(UIImageView* pImageView, const char* pTexName, const TextureResType theResType)
{
	if (pImageView == NULL)
	{
		return;
	}
	if (pTexName == NULL)
	{
		return;
	}

	const char* newFileName = pTexName;
	if (theResType == UI_TEX_TYPE_LOCAL)
	{
		newFileName = SoStringHelp::PathNormalize(pTexName);
		CCLOG("SoLoadResHelp::SetTexForImageView : [local] [%s]", newFileName);
	}
	pImageView->loadTexture(newFileName, theResType);
}
//--------------------------------------------------------------------
void SoLoadResHelp::SetPixelFormat(CCTexture2DPixelFormat theFormat)
{
	g_oldPixelFormat = CCTexture2D::defaultAlphaPixelFormat();
	CCTexture2D::setDefaultAlphaPixelFormat(theFormat);
}
//--------------------------------------------------------------------
void SoLoadResHelp::RestorePixelFormat()
{
	CCTexture2D::setDefaultAlphaPixelFormat(g_oldPixelFormat);
}
//--------------------------------------------------------------------
