//--------------------------------------------------------------------
#include "LsDialogScene.h"
#include "LsDialogLayer.h"
#include "LsUIInstanceHelp.h"
#include "SoLoadResHelp.h"
//--------------------------------------------------------------------
LsDialogScene::LsDialogScene()
{
	LsUIInstanceHelp::SetDialogScene(this);
}
//--------------------------------------------------------------------
LsDialogScene::~LsDialogScene()
{
	LsUIInstanceHelp::SetDialogScene(NULL);
}
//--------------------------------------------------------------------
bool LsDialogScene::init()
{
	if (!CCScene::init())
	{
		return false;
	}

	LsDialogLayer::CreateDialogLayer(this);
	if (false)
	{
		LsDialogLayer::ReleaseDialogLayer(this);
	}

	schedule(schedule_selector(LsDialogScene::removeUnusedResources), 1.0f);
	return true;
}
//--------------------------------------------------------------------
void LsDialogScene::onEnter()
{
	CCScene::onEnter();
}
//--------------------------------------------------------------------
void LsDialogScene::onEnterTransitionDidFinish()
{
	CCScene::onEnterTransitionDidFinish();
}
//--------------------------------------------------------------------
void LsDialogScene::onExit()
{
	CCScene::onExit();
}
//--------------------------------------------------------------------
void LsDialogScene::removeUnusedResources(float _f)
{

}
//--------------------------------------------------------------------
