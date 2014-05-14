//--------------------------------------------------------------------
#ifndef _LsDialogLayer_h_
#define _LsDialogLayer_h_
//--------------------------------------------------------------------
#include "LsCommon.h"
#include "SoAnimGroup.h"
#include "SoNumberLabel.h"
//--------------------------------------------------------------------
//为了能够响应触摸消息，必须继承自CCObject。
class LsDialogLayer : public CCObject
{
public:
	static void CreateDialogLayer(CCNode* pParentNode);
	static void ReleaseDialogLayer(CCNode* pParentNode);

private:
	LsDialogLayer();
	~LsDialogLayer();

	bool LoadDialogUI();
	void ReleaseDialogUI();

	void AdjustWidgetWidthHeight();
	void AddTouchCallBack(UILayer* pLayer, int nTag);
	void OnTouchCallBack(CCObject* obj, TouchEventType type);

private:
	static LsDialogLayer* ms_pInstance;
private:
	UILayer* m_pLayer;
	UIImageView* m_pImgDialogLeftUnit;
	SoAnimGroup m_kAnimGroup_ImgDialogLeftUnit;
	SoNumberLabel m_kNumLebel;
};
//--------------------------------------------------------------------
#endif //_LsDialogLayer_h_
//--------------------------------------------------------------------
