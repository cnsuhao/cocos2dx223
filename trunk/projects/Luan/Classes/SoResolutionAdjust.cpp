//--------------------------------------------------------------------
#include "SoResolutionAdjust.h"
//--------------------------------------------------------------------
const float g_fStandardResolutionWidth = 1024.0f;
const float g_fStandardResolutionHeight = 768.0f;
SoResolutionAdjust::eResolutionScaleType SoResolutionAdjust::ms_theType = ResolutionScale_Max;
float SoResolutionAdjust::ms_fWidthRate = 1.0f;
float SoResolutionAdjust::ms_fHeightRate = 1.0f;
//--------------------------------------------------------------------
void SoResolutionAdjust::AdjustPanelBig(UIWidget* pPanelBig)
{
	if (pPanelBig == 0)
	{
		return;
	}
	//如果一个Widget的SizeType为绝对尺寸，则UI刚加载完毕就可以设置它的宽高；
	//如果一个Widget的SizeType为相对尺寸，则UI加载完毕后必须等一帧，待百分比施加作用后
	//再重置它的宽高，否则提前设置的宽高会被“百分比施加作用”覆盖掉。例如，在CCScene::init()中
	//加载UI后，在CCScene::onEnter()时再设置它的宽高。
	//如果在CCScene::onEnter()时再设置它的宽高，有可能会看到一帧错误宽高状态的UI，然后再看到
	//重置后的正确的UI。这是我的猜测，没验证过。
	//为了保证简单统一，所有需要动态调整宽高的Widget都必须是绝对尺寸。
	if (pPanelBig->getSizeType() != SIZE_ABSOLUTE)
	{
		CCLOG("SoResolutionAdjust::AdjustPanelBig : [error] getSizeType() != SIZE_ABSOLUTE");
		return;
	}
	//
	CalculateResolutionScale();
	//
	if (ms_theType == ResolutionScale_1)
	{
		CCSize WinSize = CCDirector::sharedDirector()->getWinSize();
		pPanelBig->setSize(WinSize);
	}
	else if (ms_theType == ResolutionScale_Width_Big)
	{
		CCSize WidgetSize = pPanelBig->getSize();
		WidgetSize.width *= ms_fHeightRate;
		WidgetSize.height *= ms_fHeightRate;
		pPanelBig->setSize(WidgetSize);
	}
	else
	{
		CCSize WidgetSize = pPanelBig->getSize();
		WidgetSize.width *= ms_fWidthRate;
		WidgetSize.height *= ms_fWidthRate;
		pPanelBig->setSize(WidgetSize);
	}
}
//--------------------------------------------------------------------
void SoResolutionAdjust::CalculateResolutionScale()
{
	if (ms_theType != ResolutionScale_Max)
	{
		return;
	}

	CCSize WinSize = CCDirector::sharedDirector()->getWinSize();
	ms_fWidthRate = WinSize.width / g_fStandardResolutionWidth;
	ms_fHeightRate = WinSize.height / g_fStandardResolutionHeight;
	//
	const float fDelta = ms_fWidthRate - ms_fHeightRate;
	const float fBianJie = 0.01f;
	if (fDelta > -fBianJie && fDelta < fBianJie)
	{
		ms_theType = ResolutionScale_1;
	}
	else if (fDelta >= fBianJie)
	{
		ms_theType = ResolutionScale_Width_Big;
	}
	else
	{
		ms_theType = ResolutionScale_Height_Big;
	}
}
//--------------------------------------------------------------------
