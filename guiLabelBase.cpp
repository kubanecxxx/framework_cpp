/*
 * guiLabelBase.cpp
 *
 *  Created on: 4.7.2012
 *      Author: kubanec
 */

#include "guiCommon.h"

namespace GuiFramework
{

/**
 * @brief konstruktor nastaví defaultní vlastnosti, alokuje si ramPart
 */
gui_LabelBase::gui_LabelBase()
{
	CoordinatesSys = NULL;
	CoordinatesCount = 0;

	SetText("je");
	SetBackgroundColor(0);
	SetTextColor(0xffff);
	SetFontSize(8);
	SetCoordinates(0, 0);

	ramPart = new gui_RamPart;
}

/**
 * @brief vytvoři sekundární souřadnice
 *
 * souřadnice sou vytvořeny na heapě, může být aji jinači screen. widget se bude zobrazovat uplně
 * stejně akorát jinde nebo v jinym screenu, dokonce se i bude vybirat jako item zároveň
 */
void gui_LabelBase::AddSecondaryCoor(uint16_t x, uint16_t y, gui_Screen * screen)
{
	//musiš si alokovat vicerosouřadnic hned po sobě jinak by to nevalilo vzhledem ke kvalitni správě paměti
	gui_Coordinates * temp2;
	gui_Coordinates * temp = new gui_Coordinates;

	temp->SetX(x);
	temp->SetY(y);
	temp->Parent = screen;

	if (CoordinatesSys == 0)
	{
		CoordinatesSys = temp;
		CoordinatesCount++;
		return;
	}

	temp2 = CoordinatesSys;
	CoordinatesSys += CoordinatesCount;
	if (CoordinatesSys != temp)
		while (1)
			;
	CoordinatesSys = temp;
	CoordinatesSys = temp2;
	CoordinatesCount++;
}

/**
 * @brief naloadovat text
 * @todo vykašlat se na strcpy a jenom sem střihnout pointer na text co už je ve flašce
 */
void gui_LabelBase::SetText(const char * text)
{
	Text = text;
}
}
