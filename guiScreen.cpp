/*
 * guiScreen.cpp
 *
 *  Created on: 4.7.2012
 *      Author: kubanec
 */

#include "guiCommon.h"

gui_Screen::gui_Screen(void * parent, uint8_t index)
{
	constructor(parent, index);
}

gui_Screen::~gui_Screen()
{

}

void gui_Screen::constructor(void * paren, uint8_t index)
{
	ItemCount = 0;
	LabelCount = 0;
	LabelField = 0;
	ItemField = 0;
	ScreenIndex = index;
	ItemIndex = 0;

	SetBackgroundColor(0);
	SetTextColor(0xffff);
	parent = paren;
}

void gui_Screen::printScreen()
{
	low_level_FillRGB(BackgroundColor);

	for (int i = 0; i < ItemCount; i++)
		ItemField[i].printItem();

	for (int i = 0; i < LabelCount; i++)
	{
		LabelField[i].printLabel();
	}

}

gui_Label * gui_Screen::AddLabels(gui_Label * labels, uint8_t count, bool lock)
{
	gui_FlashWrite pico;

	LabelField = labels;
	LabelCount = count;
	for (int i = 0; i < count; i++)
	{
		LabelField[i].SetParentScreen(this);
	}
	LabelField = (gui_Label *)pico.Write(labels, count * sizeof(gui_Label));
	return LabelField;
}

gui_Item * gui_Screen::AddItems(gui_Item * items, uint8_t count, bool lock)
{
	gui_FlashWrite pico;
	ItemField = items;
	ItemCount = count;
	for (int i = 0; i < count; i++)
	{
		ItemField[i].SetIndex(i);
		ItemField[i].SetParentScreen(this);
	}
	ItemField= (gui_Item*)pico.Write(items, count * sizeof(gui_Item));
	return ItemField;
}

uint16_t gui_Screen::GetSize()
{
	uint16_t temp;

	temp = sizeof(gui_Screen);
	for (int i = 0; i < ItemCount; i++)
	{
		temp += ItemField[i].GetSize();
	}
	for (int i = 0; i < LabelCount; i++)
		temp += LabelField[i].GetSize();

	return temp;
}

gui_Item * gui_Screen::GetActiveItem()
{
	for (int i = 0; i < ItemCount; i++)
		if (ItemField[i].GetActive())
			return (&ItemField[i]);

	return 0;
}

bool gui_Screen::IsActive()
{
	gui_GuiBase * fotr = (gui_GuiBase *) parent;
	if (ScreenIndex == fotr->GetActiveScreenIndex())
		return true;
	else
		return false;
}

void gui_Screen::SetActive (void)
{
	gui_GuiBase * gui = (gui_GuiBase * )parent;
	gui->SetActiveScreenIndex(ScreenIndex);
}


#ifdef DYNAMIC_ALLOC
gui_Item * gui_Screen::MakeItem()
{
	//musiš si alokovat vicerosouřadnic hned po sobě jinak by to nevalilo vzhledem ke kvalitni správě paměti
	gui_Item* temp2;
	gui_Item* temp = (gui_Item*) super_malloc(sizeof(gui_Item));
	temp->constructor2();
	temp->constructor(this,ItemCount);

	if (ItemField== 0)
	{
		ItemField = temp;
		ItemCount++;
		return temp;
	}

	temp2 = ItemField;
	ItemField += ItemCount;
	if (ItemField != temp)
	while (1)
	;
	ItemField = temp;
	ItemField = temp2;
	ItemCount++;
	return temp;
}

gui_Label * gui_Screen::MakeLabel()
{
	//musiš si alokovat vicerosouřadnic hned po sobě jinak by to nevalilo vzhledem ke kvalitni správě paměti
	gui_Label* temp2;
	gui_Label* temp = (gui_Label*) super_malloc(sizeof(gui_Label));
	temp->constructor2(this);

	if (LabelField== 0)
	{
		LabelField = temp;
		LabelCount++;
		return temp;
	}

	temp2 = LabelField;
	LabelField += LabelCount;
	if (LabelField != temp)
	while (1)
	;
	LabelField = temp;
	LabelField = temp2;
	LabelCount++;
	return temp;
}
#endif
