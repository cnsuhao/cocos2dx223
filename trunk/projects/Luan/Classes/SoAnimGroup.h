//--------------------------------------------------------------------
#ifndef _SoAnimGroup_h_
#define _SoAnimGroup_h_
//--------------------------------------------------------------------
#include "LsCommon.h"
//--------------------------------------------------------------------
typedef std::vector<std::string> vecImageNameList;
//--------------------------------------------------------------------
class SoAnimGroup : public CCObject
{
public:
	struct stAnim
	{
		int nAnimID;
		vecImageNameList kImageList;
		TextureResType theResType; //UI_TEX_TYPE_LOCAL;UI_TEX_TYPE_PLIST;
		float fInterval;
		bool bLoop;
	};

public:
	SoAnimGroup();
	~SoAnimGroup();

	//--pImageView 其值可以为NULL
	void SetDestWidget(UIImageView* pImageView);

	void RegisterAnim(const SoAnimGroup::stAnim& kAnim);

	bool PlayAnim(int nAnimID);
	void StopAnim();
	bool IsPlaying() const;

private:
	void RegisterCallBack(float fInterval);
	void UnregisterCallBack();
	void OnCallBack(float t);
	stAnim* GetAnim(int nAnimID);
	void ShowFrameImage(const std::string& strImageName, TextureResType theResType);

private:
	typedef std::vector<stAnim> vecAnimList;

private:
	//本类没有引用计数，本类也不增加 m_pImgView 的引用计数。
	//外界要管理好 m_pImgView 的生存期与本类对象的生存期。
	UIImageView* m_pImgView;
	vecAnimList m_kAnimList;
	//当前播放到了第几帧。取值范围[0, X]。-1为无效值。
	int m_nCurrentFrameIndex;
	//当前播放的动画ID。
	int m_nCurrentAnimID;
};
//--------------------------------------------------------------------
#endif //_SoAnimGroup_h_
//--------------------------------------------------------------------
