/*
 * guiLabel.cpp
 *
 *  Created on: 4.7.2012
 *      Author: kubanec
 */

#include "guiCommon.h"

gui_Label::gui_Label()
{


}

gui_Label::~gui_Label()
{

}

void gui_Label::printLabel()
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
		low_level_lcdPutsStringBackground(Text, PrimaryCoor.GetX(),
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
				low_level_lcdPutsStringBackground(Text,
						CoordinatesSys[i].GetX(), CoordinatesSys[i].GetY(),
						tcolor, bcolor, FontSize);
			}
		}
	}
}

uint16_t gui_Label::GetSize()
{
	uint16_t temp;

	temp = sizeof(gui_Label);
	temp += sizeof(gui_RamPart);
	temp += sizeof(gui_Coordinates) * CoordinatesCount;

	return temp;
}
