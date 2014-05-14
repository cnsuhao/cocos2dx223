//--------------------------------------------------------------------
#include "LsUIInstanceHelp.h"
#include "LsDialogScene.h"
//--------------------------------------------------------------------
LsDialogScene* LsUIInstanceHelp::ms_pDialogScene = NULL;
//--------------------------------------------------------------------
void LsUIInstanceHelp::SetDialogScene(LsDialogScene* pDialogScene)
{
	ms_pDialogScene = pDialogScene;
}
//--------------------------------------------------------------------
LsDialogScene* LsUIInstanceHelp::GetDialogScene()
{
	return ms_pDialogScene;
}
//--------------------------------------------------------------------
