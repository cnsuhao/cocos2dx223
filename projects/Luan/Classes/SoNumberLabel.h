//--------------------------------------------------------------------
#ifndef _SoNumberLabel_h_
#define _SoNumberLabel_h_
//--------------------------------------------------------------------
#include "LsCommon.h"
//--------------------------------------------------------------------
class SoNumberLabel
{
public:
	SoNumberLabel();
	~SoNumberLabel();

	//--pLabel 其值可以为NULL
	void SetDestWidget(UILabelAtlas* pLabel);

	void SetNumber(int nNumber);
	void SetNumString(const char* pString);

private:
	//本类没有引用计数，本类也不增加 m_pNumLabel 的引用计数。
	//外界要管理好 m_pNumLabel 的生存期与本类对象的生存期。
	UILabelAtlas* m_pNumLabel;
	//记录当前控件上有几个字符。
	int m_nCharacterCount;
};
//--------------------------------------------------------------------
#endif //_SoNumberLabel_h_
//--------------------------------------------------------------------
