/*
 * guiGuiBase.cpp
 *
 *  Created on: 4.7.2012
 *      Author: kubanec
 */

#include "ch.h"
#include "guiCommon.h"
namespace GuiFramework
{

gui_GuiBase::gui_GuiBase()
{
	ScreenCount = 0;
	ScreenIndex = 0;
	ScreenField = 0;
	low_level_button_init();


}

gui_GuiBase::~gui_GuiBase()
{

}

void gui_GuiBase::print_gui(void)
{
	if (ScreenCount == 0)
		return;

	if (ScreenIndex >= ScreenCount)
		return;

	ScreenField[ScreenIndex].printScreen();
}

uint16_t gui_GuiBase::GetSize()
{
	uint16_t size;

	size = sizeof(gui_GuiBase);
	for (int i = 0; i < ScreenCount; i++)
	{
		size += ScreenField[i].GetSize();
	}
	return size;
}

gui_Screen * gui_GuiBase::MakeScreen()
{
	static uint8_t cislo = 0;
	//musiš si alokovat vicerosouřadnic hned po sobě jinak by to nevalilo vzhledem ke kvalitni správě paměti
	gui_Screen * temp2;
	gui_Screen * temp = new gui_Screen(this,cislo);

	if (ScreenField == 0)
	{
		ScreenField = temp;
		ScreenCount++;
		return temp;
	}

	temp2 = ScreenField;
	ScreenField += ScreenCount;
	if (ScreenField != temp)
		while (1)
			;
	ScreenField = temp;
	ScreenField = temp2;
	ScreenCount++;
	return temp;
}

bool gui_GuiBase::ButtonScan()
{
	volatile gui_Item::Buttons input = (gui_Item::Buttons) low_level_input_buttons();
	gui_Item * item = ScreenField[ScreenIndex].GetActiveItem();

	if (input != gui_Item::BUTTON_DOWN && input != gui_Item::BUTTON_UP
			&& input != gui_Item::BUTTON_ENTER)
		return false;

	if (item->GetClicked())
		item->Event(input, gui_Item::CLICKED);
	else
		item->Event(input, gui_Item::NOTCLICKED);

	return true;
}
}
