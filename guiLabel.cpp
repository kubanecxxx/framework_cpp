/*
 * guiLabel.cpp
 *
 *  Created on: 4.7.2012
 *      Author: kubanec
 */

#include "guiCommon.h"
namespace GuiFramework
{
/**
 * @brief vytiskne label pokud je aktivni jeho screen
 */
void gui_Label::print()
{
	gui_Screen * screen = GetParentScreen();
	uint16_t tcolor = this->GetTextColor();
	uint16_t bcolor = this->GetBackGroundColor();

	if (!screen->IsActive())
		return;

	if (GetUseDefaultBackgroundColor())
		bcolor = screen->GetBackGroundColor();

	if (GetUseDefaultTextColor())
		tcolor = screen->GetTextColor();

	/*
	 //pokud je tahle souřadnice ve screenu kterej se zrovna kresli
	 if (this->PrimaryCoor.GetScreen() == this->GetParentScreen())
	 {
	 */
	if (IsShownGlobal() == false)
	{
		tcolor = bcolor;
	}
	else
	{
		//vyblit text
		port::PutsStringBackground(Text, PrimaryCoor.GetX(),
				PrimaryCoor.GetY(), tcolor, bcolor, FontSize);
	}
	//}

	for (int i = 0; i < this->CoordinatesCount; i++)
	{
		//pokud je tahle souřadnice ve screenu kterej se zrovna kresli
		if (this->CoordinatesSys[i].GetScreen() == this->GetParentScreen())
		{
			if (IsShownGlobal() == false)
			{
				tcolor = bcolor;
			}
			else
			{
				//vyblit text
				port::PutsStringBackground(Text,
						CoordinatesSys[i].GetX(), CoordinatesSys[i].GetY(),
						tcolor, bcolor, FontSize);
			}
		}
	}
}

/**
 * @brief vypočte kolik label žere celkem paměti
 */
uint16_t gui_Label::GetSize() const
{
	uint16_t temp;

	temp = sizeof(gui_Label);
	temp += sizeof(gui_RamPart);
	temp += sizeof(gui_Coordinates) * CoordinatesCount;

	return temp;
}
}
