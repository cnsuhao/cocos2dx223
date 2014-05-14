//--------------------------------------------------------------------
#include "LsDialogLayer.h"
#include "SoResolutionAdjust.h"
#include "LsWidgetTagDefine.h"
#include "SoLoadResHelp.h"
#include "LsUIInstanceHelp.h"
//--------------------------------------------------------------------
LsDialogLayer* LsDialogLayer::ms_pInstance = NULL;
//--------------------------------------------------------------------
void LsDialogLayer::CreateDialogLayer(CCNode* pParentNode)
{
	ReleaseDialogLayer(NULL);
	if (pParentNode == NULL)
	{
		CCLOG("LsDialogLayer::CreateDialogLayer : [error] pParentNode == NULL");
		return;
	}
	//
	bool bInit = false;
	ms_pInstance = new LsDialogLayer;
	if (ms_pInstance->LoadDialogUI() == true)
	{
		pParentNode->addChild(ms_pInstance->m_pLayer);
		bInit = true;
	}
	//
	if (bInit == false)
	{
		ReleaseDialogLayer(pParentNode);
	}
}
//--------------------------------------------------------------------
void LsDialogLayer::ReleaseDialogLayer(CCNode* pParentNode)
{
	if (ms_pInstance == NULL)
	{
		return;
	}
	if (pParentNode != NULL && ms_pInstance->m_pLayer != NULL)
	{
		pParentNode->removeChild(ms_pInstance->m_pLayer);
	}
	ms_pInstance->ReleaseDialogUI();
	//
	delete ms_pInstance;
	ms_pInstance = NULL;
}
//--------------------------------------------------------------------
LsDialogLayer::LsDialogLayer()
:m_pLayer(NULL)
,m_pImgDialogLeftUnit(NULL)
{

}	
//--------------------------------------------------------------------
LsDialogLayer::~LsDialogLayer()
{

}
//--------------------------------------------------------------------
bool LsDialogLayer::LoadDialogUI()
{
	//先加载UI界面上会使用到的贴图资源，再加载UI界面。
	//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	SoLoadResHelp::SetPixelFormat(kCCTexture2DPixelFormat_RGBA4444);
	SoLoadResHelp::LoadPlistTexture("UI/UI_Dialog/gui.plist");
	SoLoadResHelp::LoadPlistTexture("UI/UI_Dialog/bg001.plist");
	SoLoadResHelp::LoadPlistTexture("UI/UI_Dialog/unit001.plist");
	SoLoadResHelp::RestorePixelFormat();
	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
	UIWidget* pWidget = NULL;
	pWidget = GUIReader::shareReader()->widgetFromJsonFile("UI/UI_Dialog/UI_Dialog.ExportJson");
	if (pWidget == NULL)
	{
		CCLOG("LsDialogLayer::LoadDialogUI : [error] Load UI Fail!");
		return false;
	}
	
	UILayer* pLayer = UILayer::create();
	pLayer->addWidget(pWidget);
	m_pLayer = pLayer;

	AdjustWidgetWidthHeight();
	AddTouchCallBack(pLayer, Tag_Dialog_Panel_Big);
	AddTouchCallBack(pLayer, Tag_Dialog_Btn_OK);

	m_pImgDialogLeftUnit = dynamic_cast<UIImageView*>(pLayer->getWidgetByTag(Tag_Dialog_Img_LeftUnit));
	if (m_pImgDialogLeftUnit)
	{
		m_kAnimGroup_ImgDialogLeftUnit.SetDestWidget(m_pImgDialogLeftUnit);
		SoAnimGroup::stAnim kAnim;
		kAnim.nAnimID = 1;
		kAnim.kImageList.push_back(std::string("unit001.png"));
		kAnim.kImageList.push_back(std::string("unit002.png"));
		kAnim.theResType = UI_TEX_TYPE_PLIST;
		kAnim.fInterval = 0.5f;
		kAnim.bLoop = true;
		m_kAnimGroup_ImgDialogLeftUnit.RegisterAnim(kAnim);

		kAnim.nAnimID = 2;
		kAnim.bLoop = false;
		m_kAnimGroup_ImgDialogLeftUnit.RegisterAnim(kAnim);
	}

	UILabelAtlas* pNumLabel = dynamic_cast<UILabelAtlas*>(pLayer->getWidgetByTag(Tag_Dialog_NumLabel));
	m_kNumLebel.SetDestWidget(pNumLabel);
	m_kNumLebel.SetNumber(9887);
	return true;
}
//--------------------------------------------------------------------
void LsDialogLayer::ReleaseDialogUI()
{
	m_pLayer = NULL;
	m_pImgDialogLeftUnit = NULL;
	m_kAnimGroup_ImgDialogLeftUnit.SetDestWidget(NULL);
	m_kNumLebel.SetDestWidget(NULL);
	//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	//卸载本界面使用的贴图资源
	SoLoadResHelp::ReleasePlistTexture("UI/UI_Dialog/gui.plist");
	SoLoadResHelp::ReleasePlistTexture("UI/UI_Dialog/bg001.plist");
	SoLoadResHelp::ReleasePlistTexture("UI/UI_Dialog/unit001.plist");
	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
}
//--------------------------------------------------------------------
void LsDialogLayer::AdjustWidgetWidthHeight()
{
	if (m_pLayer == NULL)
	{
		return;
	}
	//
	UIWidget* pPanelBig = m_pLayer->getWidgetByTag(Tag_Dialog_Panel_Big);
	SoResolutionAdjust::AdjustPanelBig(pPanelBig);
}
//--------------------------------------------------------------------
void LsDialogLayer::AddTouchCallBack(UILayer* pLayer, int nTag)
{
	UIWidget* pWidget = pLayer->getWidgetByTag(nTag);
	if (pWidget)
	{
		pWidget->addTouchEventListener(this, toucheventselector(LsDialogLayer::OnTouchCallBack));
	}
	else
	{
		CCLOG("LsDialogLayer::AddTouchCallBack : [error] Can not find widget [%d]!", nTag);
	}
}
//--------------------------------------------------------------------
void LsDialogLayer::OnTouchCallBack(CCObject* obj, TouchEventType type)
{
	if (type == TouchEventType::TOUCH_EVENT_ENDED)
	{
		UIWidget* pWidget = dynamic_cast<UIWidget*>(obj);
		if (pWidget)
		{
			const int nTag = pWidget->getTag();
			switch (nTag)
			{
			case Tag_Dialog_Panel_Big:
				CCLOG("LsDialogLayer::OnTouchCallBack : touch end, widget[%d]", Tag_Dialog_Panel_Big);
				if (false)
				{
					CCNode* pNode = (CCNode*)LsUIInstanceHelp::GetDialogScene();
					LsDialogLayer::ReleaseDialogLayer(pNode);
					CCTextureCache::sharedTextureCache()->removeUnusedTextures();
				}
				break;
			case Tag_Dialog_Btn_OK:
				CCLOG("LsDialogLayer::OnTouchCallBack : touch end, widget[%d]", Tag_Dialog_Btn_OK);
				if (m_kAnimGroup_ImgDialogLeftUnit.IsPlaying() == false)
				{
					m_kAnimGroup_ImgDialogLeftUnit.PlayAnim(1);
				}
				else
				{
					m_kAnimGroup_ImgDialogLeftUnit.PlayAnim(2);
				}
				m_kNumLebel.SetNumber(999);
				break;
			}
		}
	}
}
//--------------------------------------------------------------------
