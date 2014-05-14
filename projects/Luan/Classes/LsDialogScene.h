//--------------------------------------------------------------------
#ifndef _LsDialogScene_h_
#define _LsDialogScene_h_
//--------------------------------------------------------------------
#include "LsCommon.h"
#include "SoAnimGroup.h"
//--------------------------------------------------------------------
class LsDialogScene : public CCScene
{
public:
	CREATE_FUNC(LsDialogScene);
	LsDialogScene();
	virtual ~LsDialogScene();

protected:
	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	void removeUnusedResources(float _f);

private:

	
};
//--------------------------------------------------------------------
#endif //_LsDialogScene_h_
//--------------------------------------------------------------------
