//--------------------------------------------------------------------
#include "SoNumberLabel.h"
//--------------------------------------------------------------------
SoNumberLabel::SoNumberLabel()
:m_pNumLabel(NULL)
,m_nCharacterCount(0)
{

}
//--------------------------------------------------------------------
SoNumberLabel::~SoNumberLabel()
{
	m_pNumLabel = NULL;
}
//--------------------------------------------------------------------
void SoNumberLabel::SetDestWidget(UILabelAtlas* pLabel)
{
	m_pNumLabel = pLabel;
	if (m_pNumLabel != NULL)
	{
		const char* pString = m_pNumLabel->getStringValue();
		if (pString != NULL)
		{
			int nStrLen = (int)strlen(pString);
			if (nStrLen > 0)
			{
				m_nCharacterCount = nStrLen;
			}
			else
			{
				CCLOG("SoNumberLabel::SetDestWidget :[error] default string is empty");
			}
		}
	}
}
//--------------------------------------------------------------------
void SoNumberLabel::SetNumber(int nNumber)
{
	if (m_pNumLabel == NULL)
	{
		return;
	}
	//
	char szBuff[30] = {0};
	sprintf(szBuff, "%d", nNumber);
	SetNumString(szBuff);
}
//--------------------------------------------------------------------
void SoNumberLabel::SetNumString(const char* pString)
{
	if (m_pNumLabel == NULL)
	{
		return;
	}
	if (pString == NULL)
	{
		return;
	}
	//
	m_pNumLabel->setStringValue(pString);
	//
	if (m_nCharacterCount > 0) //除数不能是0
	{
		int nStrLen = (int)strlen(pString);
		CCPoint WidgetSizePercent = m_pNumLabel->getSizePercent();
		WidgetSizePercent.x = WidgetSizePercent.x / m_nCharacterCount * nStrLen;
		m_pNumLabel->setSizePercent(WidgetSizePercent);
		m_nCharacterCount = nStrLen;
	}
}
//--------------------------------------------------------------------
