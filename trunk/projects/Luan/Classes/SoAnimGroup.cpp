//--------------------------------------------------------------------
#include "SoAnimGroup.h"
#include "SoLoadResHelp.h"
//--------------------------------------------------------------------
SoAnimGroup::SoAnimGroup()
:m_pImgView(NULL)
,m_nCurrentFrameIndex(-1)
,m_nCurrentAnimID(0)
{

}
//--------------------------------------------------------------------
SoAnimGroup::~SoAnimGroup()
{
	m_pImgView = NULL;
}
//--------------------------------------------------------------------
void SoAnimGroup::SetDestWidget(UIImageView* pImageView)
{
	m_pImgView = pImageView;
}
//--------------------------------------------------------------------
void SoAnimGroup::RegisterAnim(const SoAnimGroup::stAnim& kAnim)
{
	if (kAnim.kImageList.empty())
	{
		CCLOG("SoAnimGroup::RegisterAnim :[error] kAnim.kImageList is empty");
		return;
	}
	//
	m_kAnimList.push_back(kAnim);
}
//--------------------------------------------------------------------
bool SoAnimGroup::PlayAnim(int nAnimID)
{
	if (m_pImgView == NULL)
	{
		CCLOG("SoAnimGroup::PlayAnim : m_pImgView == NULL");
		return false;
	}
	//
	if (m_nCurrentFrameIndex != -1)
	{
		StopAnim();
	}
	//
	stAnim* pAnim = GetAnim(nAnimID);
	if (pAnim == NULL)
	{
		CCLOG("SoAnimGroup::PlayAnim : Can not find Anim[%d]", nAnimID);
		return false;
	}
	//
	m_nCurrentFrameIndex = 0;
	m_nCurrentAnimID = nAnimID;
	ShowFrameImage(pAnim->kImageList[m_nCurrentFrameIndex], pAnim->theResType);
	RegisterCallBack(pAnim->fInterval);
}
//--------------------------------------------------------------------
void SoAnimGroup::StopAnim()
{
	m_nCurrentFrameIndex = -1;
	m_nCurrentAnimID = 0;
	UnregisterCallBack();
}
//--------------------------------------------------------------------
bool SoAnimGroup::IsPlaying() const
{
	return (m_pImgView != NULL && m_nCurrentFrameIndex != -1);
}
//--------------------------------------------------------------------
void SoAnimGroup::RegisterCallBack(float fInterval)
{
	CCDirector::sharedDirector()->getScheduler()->scheduleSelector(
		schedule_selector(SoAnimGroup::OnCallBack), this, fInterval, false);
}
//--------------------------------------------------------------------
void SoAnimGroup::UnregisterCallBack()
{
	CCDirector::sharedDirector()->getScheduler()->unscheduleSelector(
		schedule_selector(SoAnimGroup::OnCallBack), this);
}
//--------------------------------------------------------------------
void SoAnimGroup::OnCallBack(float t)
{
	if (m_pImgView == NULL)
	{
		return;
	}
	if (m_nCurrentFrameIndex == -1)
	{
		return;
	}
	//
	stAnim* pAnim = GetAnim(m_nCurrentAnimID);
	if (pAnim == NULL)
	{
		CCLOG("SoAnimGroup::OnCallBack : Can not find Anim[%d]", m_nCurrentAnimID);
		return;
	}
	//
	bool bShouldStop = false;
	++m_nCurrentFrameIndex;
	if (m_nCurrentFrameIndex >= (int)pAnim->kImageList.size())
	{
		m_nCurrentFrameIndex = 0;
		if (pAnim->bLoop == false)
		{
			bShouldStop = true;
		}
	}
	//
	if (bShouldStop)
	{
		StopAnim();
	}
	else
	{
		ShowFrameImage(pAnim->kImageList[m_nCurrentFrameIndex], pAnim->theResType);
	}
}
//--------------------------------------------------------------------
SoAnimGroup::stAnim* SoAnimGroup::GetAnim(int nAnimID)
{
	stAnim* pAnim = NULL;
	for (vecAnimList::iterator it = m_kAnimList.begin();
		it != m_kAnimList.end();
		++it)
	{
		stAnim& kAnim = *it;
		if (kAnim.nAnimID == nAnimID)
		{
			pAnim = &kAnim;
			break;
		}
	}
	return pAnim;
}
//--------------------------------------------------------------------
void SoAnimGroup::ShowFrameImage(const std::string& strImageName, TextureResType theResType)
{
	if (m_pImgView == NULL)
	{
		return;
	}
	//
	SoLoadResHelp::SetTexForImageView(m_pImgView, strImageName.c_str(), theResType);
}
//--------------------------------------------------------------------
