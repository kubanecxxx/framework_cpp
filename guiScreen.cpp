/*
 * guiScreen.cpp
 *
 *  Created on: 4.7.2012
 *      Author: kubanec
 */

#include "guiCommon.h"
namespace GuiFramework
{

///počet screenů
uint8_t gui_Screen::Count = 0;
///pointer na aktivní screen
gui_Screen * gui_Screen::ActiveScreen = NULL;

/**
 * @brief defaultní setup - žádny widgety a tak
 */
gui_Screen::gui_Screen()
{
	ItemCount = 0;
	LabelCount = 0;
	FirstItem = NULL;
	FirstLabel = NULL;
	ItemIndex = 0;

	SetBackgroundColor(0);
	SetTextColor(0xffff);

	if (Count == 0)
		SetActive();

	Count++;
}

/**
 * @brief vytiskne aktivní screen
 *
 * projde všechny jeho widgety a vytiskne je
 */
void gui_Screen::printActiveScreen()
{
	port::FillRGB(ActiveScreen->BackgroundColor);

	gui_Item * temp = ActiveScreen->FirstItem;
	for (int i = 0; i < ActiveScreen->ItemCount; i++)
	{
		temp->print();
		temp = temp->GetNext();
	}

	gui_Label * lab = ActiveScreen->FirstLabel;
	for (int i = 0; i < ActiveScreen->LabelCount; i++)
	{
		lab->print();
		lab = lab->GetNext();
	}
}

/**
 * @brief vyblije kolik celé screen už zežral paměti
 */
uint16_t gui_Screen::GetSize() const
{
	uint16_t temp = sizeof(gui_Screen);
	gui_Item * item = FirstItem;

	for (int i = 0; i < ItemCount; i++)
	{
		temp += item->GetSize();
		item = item->GetNext();
	}

	gui_Label * label = FirstLabel;
	for (int i = 0; i < LabelCount; i++)
	{
		temp += label->GetSize();
		label = label->GetNext();
	}
	return temp;
}

/**
 * @brief funkce na skenování tlačítek, uživatel si ju musi periodicky sám volat
 *
 * funkce už si sama pošefi callbacky od itemu a tak
 *
 * @return pokud se zmačklo nějaky tlačitko vrátí true
 */
bool gui_Screen::ButtonScan()
{
	volatile gui_Item::Buttons input =
			(gui_Item::Buttons) port::input_buttons();

	gui_Item * item;
	item = ActiveScreen->GetActiveItem();

	if (input != gui_Item::BUTTON_DOWN && input != gui_Item::BUTTON_UP
			&& input != gui_Item::BUTTON_ENTER)
		return false;

	if (item->GetClicked())
		item->Event(input, gui_Item::CLICKED);
	else
		item->Event(input, gui_Item::NOTCLICKED);

	return true;

}

/**
 * @todo
 * vytvořit funkce na newlabel a newitem from heap, i s uvolňováním
 */
#if 0
gui_Label * gui_Screen::AddLabels(gui_Label * labels, uint8_t count, bool lock)
{
	gui_FlashWrite pico;

	LabelField = labels;
	LabelCount = count;
	for (int i = 0; i < count; i++)
	{
		LabelField[i].SetParentScreen(this);
	}
	LabelField = (gui_Label *) pico.Write(labels, count * sizeof(gui_Label));
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
	ItemField = (gui_Item*) pico.Write(items, count * sizeof(gui_Item));
	return ItemField;
}
#endif

}
