/*
 * guiLabelBase.cpp
 *
 *  Created on: 4.7.2012
 *      Author: kubanec
 */

#include <string.h>
#include "guiCommon.h"

gui_LabelBase::gui_LabelBase(void * par)
{
	constructor2(par);
}

gui_LabelBase::gui_LabelBase()
{
	constructor2();
}

gui_LabelBase::~gui_LabelBase()
{

}

void gui_LabelBase::constructor2(void * par)
{
	constructor2();
	PrimaryCoor.SetScreen(par);
}

void gui_LabelBase::constructor2(void)
{
	SetText("je");
	SetBackgroundColor(0);
	SetTextColor(0xffff);
	SetFontSize(8);
	SetRamPart(0);
	SetCoordinates(0, 0);

	ramPart = (gui_RamPart *) super_malloc(sizeof(gui_RamPart));
	ramPart->constructor();
}

void gui_LabelBase::print(void)
{

}

void gui_LabelBase::AddSecondaryCoor(uint16_t x, uint16_t y, void * screen)
{
	//musiš si alokovat vicerosouřadnic hned po sobě jinak by to nevalilo vzhledem ke kvalitni správě paměti
	gui_Coordinates * temp2;
	gui_Coordinates * temp = (gui_Coordinates *) super_malloc(
			sizeof(gui_Coordinates));
	temp->constructor2();
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
