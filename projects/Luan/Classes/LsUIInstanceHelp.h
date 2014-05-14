//--------------------------------------------------------------------
#ifndef _LsUIInstanceHelp_h_
#define _LsUIInstanceHelp_h_
//--------------------------------------------------------------------

//--------------------------------------------------------------------
class LsDialogScene;
//--------------------------------------------------------------------
class LsUIInstanceHelp
{
public:
	static void SetDialogScene(LsDialogScene* pDialogScene);
	static LsDialogScene* GetDialogScene();
	
private:
	static LsDialogScene* ms_pDialogScene;
};
//--------------------------------------------------------------------
#endif //_LsUIInstanceHelp_h_
//--------------------------------------------------------------------
