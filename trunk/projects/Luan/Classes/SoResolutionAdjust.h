//--------------------------------------------------------------------
#ifndef _SoResolutionAdjust_h_
#define _SoResolutionAdjust_h_
//--------------------------------------------------------------------
#include "LsCommon.h"
//--------------------------------------------------------------------
class SoResolutionAdjust
{
public:
	static void AdjustPanelBig(UIWidget* pPanelBig);

private:
	static void CalculateResolutionScale();

private:
	enum eResolutionScaleType
	{
		ResolutionScale_1,
		ResolutionScale_Width_Big,
		ResolutionScale_Height_Big,
		ResolutionScale_Max,
	};

private:
	static eResolutionScaleType ms_theType;
	static float ms_fWidthRate;
	static float ms_fHeightRate;
};
//--------------------------------------------------------------------
#endif //_SoResolutionAdjust_h_
//--------------------------------------------------------------------
