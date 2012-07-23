/*
 * guiLabelBase.cpp
 *
 *  Created on: 4.7.2012
 *      Author: kubanec
 */

#include <string.h>
#include "guiCommon.h"

gui_LabelBase::gui_LabelBase(gui_Screen * par)
{
	gui_LabelBase();
	PrimaryCoor.SetScreen(par);

	SetText("je");
	SetBackgroundColor(0);
	SetTextColor(0xffff);
	SetFontSize(8);
	SetRamPart(0);
	SetCoordinates(0, 0);

	ramPart = new gui_RamPart;
}

gui_LabelBase::~gui_LabelBase()
{

}

void gui_LabelBase::print(void)
{

}

void gui_LabelBase::AddSecondaryCoor(uint16_t x, uint16_t y, gui_Screen * screen)
{
	//musiš si alokovat vicerosouřadnic hned po sobě jinak by to nevalilo vzhledem ke kvalitni správě paměti
	gui_Coordinates * temp2;
	gui_Coordinates * temp = new gui_Coordinates;

	temp->SetX(x);
	temp->SetY(y);
	temp->SetScreen(screen);

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

void gui_LabelBase::SetText(const char * text)
{
	strcpy(Text, text);
}
