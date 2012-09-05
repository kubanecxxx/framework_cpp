/*
 * guiItem.cpp
 *
 *  Created on: 4.7.2012
 *      Author: kubanec
 */

#include "guiCommon.h"

namespace GuiFramework
{

void gui_default_conversion(char* data, int16_t value);

gui_Item::gui_Item(gui_Screen * par, uint8_t idx)
{
	gui_Item();
	Index = idx;
	PrimaryCoor.SetScreen(par);
}

gui_Item::gui_Item()
{
	BackgroundColorActive = 0xf;
	BackgroundColorClicked = 0x8000;
	TextColorActive = 0xffff;
	TextColorClicked = 0xffff;

	HighLimit = 10;
	LowLimit = 0;
	Step = 1;
	ConversionFunction = gui_default_conversion;

	//default callback settings
	Clicked[BUTTON_UP] = gui_EventClickedUp;
	Clicked[BUTTON_DOWN] = gui_EventClickedDown;
	Clicked[BUTTON_ENTER] = gui_EventClickedEnter;
	NotClicked[BUTTON_UP] = gui_EventNotClickedUp;
	NotClicked[BUTTON_DOWN] = gui_EventNotClickedDown;
	NotClicked[BUTTON_ENTER] = gui_EventNotClickedEnter;
}

gui_Item::~gui_Item()
{

}

void gui_Item::printItem()
{
	gui_Screen * screen = GetParentScreen();
	uint16_t tcolor = this->GetTextColor();
	uint16_t bcolor = this->GetBackGroundColor();
	uint16_t val_tcolor = TextColor;
	uint16_t val_bcolor = BackgroundColor;
	uint16_t val_temp;
	uint16_t t_temp;
	char buffer[16];



	if (!screen->IsActive())
		return;

	ConversionFunction(buffer, GetValue());

	if (this->GetUseDefaultBackgroundColor())
		bcolor = screen->GetBackGroundColor();

	if (this->GetUseDefaultTextColor())
		tcolor = screen->GetTextColor();

	if (GetClicked())
	{
		val_tcolor = TextColorClicked;
		val_bcolor = BackgroundColorClicked;
	}
	else if (GetActive())
	{
		val_tcolor = TextColorActive;
		val_bcolor = BackgroundColorActive;
		tcolor = val_tcolor;
		bcolor = val_bcolor;
	}

	if (IsShownGlobal() == false)
	{
		tcolor = bcolor;
		val_tcolor = bcolor;
	}
	else
	{
		t_temp = tcolor;
		val_temp = val_tcolor;
		if (PrimaryCoor.GetShown() == false)
		{
			tcolor = bcolor;
			val_tcolor = bcolor;
		}
		if (PrimaryCoor.GetShownText() == false)
		{
			tcolor = bcolor;
		}
		if (PrimaryCoor.GetShownValue() == false)
		{
			val_tcolor = bcolor;
		}
	}

	//vyblit text
	low_level_lcdPutsStringBackground(Text, PrimaryCoor.GetX(),
			PrimaryCoor.GetY(), tcolor, bcolor, FontSize);

	low_level_lcdPutsStringBackground(buffer,
			PrimaryCoor.GetX() + strlen(Text) * FontSize, PrimaryCoor.GetY(),
			val_tcolor, val_bcolor, FontSize);
	tcolor = t_temp;
	val_tcolor = val_temp;

	for (int i = 0; i < this->CoordinatesCount; i++)
	{
		//pokud je tahle souřadnice ve screenu kterej se zrovna kresli
		if (this->CoordinatesSys[i].GetScreen() == this->GetParentScreen())
		{
			if (IsShownGlobal() == false)
			{
				tcolor = bcolor;
				val_tcolor = bcolor;
			}
			else
			{
				t_temp = tcolor;
				val_temp = val_tcolor;
				if (CoordinatesSys[i].GetShown() == false)
				{
					tcolor = bcolor;
					val_tcolor = bcolor;
				}
				if (CoordinatesSys[i].GetShownText() == false)
				{
					tcolor = bcolor;
				}
				if (CoordinatesSys[i].GetShownValue() == false)
				{
					val_tcolor = bcolor;
				}
			}

			//vyblit text
			low_level_lcdPutsStringBackground(Text, CoordinatesSys[i].GetX(),
					CoordinatesSys[i].GetY(), tcolor, bcolor, FontSize);

			low_level_lcdPutsStringBackground(buffer,
					CoordinatesSys[i].GetX() + strlen(Text) * FontSize,
					CoordinatesSys[i].GetY(), val_tcolor, val_bcolor, FontSize);
			tcolor = t_temp;
			val_tcolor = val_temp;
		}
	}
}

void gui_default_conversion(char* data, int16_t value)
{
	uint8_t i;
	char jo[8];

	data[0] = ' ';
	data[1] = ' ';
	data[2] = ' ';
	data[3] = ' ';
	data[4] = 0;

	if (value == 0)
	{
		data[0] = '0';
	}

	for (i = 0; value; i++)
	{
		jo[i] = value % 10 + '0';
		value /= 10;
	}
	jo[i] = 0;

	for (i = 0; i < strlen(jo); i++)
		data[i] = jo[strlen(jo) - i - 1];

}

bool gui_Item::GetActive()
{
	gui_Screen * screen = (gui_Screen *) GetParentScreen();
	if (screen->GetItemIndex() == Index)
		return true;
	else
		return false;
}

uint16_t gui_Item::GetSize()
{
	uint16_t temp;

	temp = sizeof(gui_Item);
	temp += sizeof(gui_RamPart);
	temp += sizeof(gui_Coordinates) * CoordinatesCount;

	return temp;
}

void gui_Item::Event(Buttons number, CallbackType type)
{
	if (type == CLICKED)
	{
		Clicked[number](this);
	}
	else
	{
		NotClicked[number](this);
	}
}

void gui_Item::SetCallback(Buttons number, CallbackType type,
		gui_ButtonCallbackTypedef callback)
{
	if (type == CLICKED)
	{
		Clicked[number] = callback;
	}
	else
	{
		NotClicked[number] = callback;
	}
}

void gui_Item::operator+=(uint16_t data)
{
	ramPart->Value += data;
}

void gui_Item::operator-=(uint16_t data)
{
	ramPart->Value -= data;
}

void gui_Item::operator--()
{
	if (ramPart->Value + Step <= HighLimit)
	{
		ramPart->Value += Step;
	}
	else
	{
		if (ramPart->bitField.b.ValueRounding == true)
		{
			ramPart->Value = LowLimit;
		}
		else
		{
			ramPart->Value = HighLimit;
		}
	}
	printItem();
}

void gui_Item::operator++()
{
	if (ramPart->Value - Step >= LowLimit)
	{
		ramPart->Value -= Step;
	}
	else
	{
		if (ramPart->bitField.b.ValueRounding == true)
		{
			ramPart->Value = HighLimit;
		}
		else
		{
			ramPart->Value = LowLimit;
		}
	}
	printItem();
}

void gui_Item::NextItem(void)
{
	gui_Screen * screen = (gui_Screen *) GetParentScreen();
	uint8_t count = screen->GetItemCount();

	do
	{
		if (count > screen->GetItemIndex() + 1)
		{
			screen->SetItemIndex(screen->GetItemIndex() + 1);
		}
		else
		{
			screen->SetItemIndex(0);
		}
	} while (!screen->GetActiveItem()->IsShownGlobal()
			|| !screen->GetActiveItem()->GetChoseable());

	printItem();
	screen->GetActiveItem()->printItem();
}

void gui_Item::PrevItem(void)
{
	gui_Screen * screen = (gui_Screen *) GetParentScreen();
	uint8_t count = screen->GetItemCount();

	do
	{
		if (screen->GetItemIndex() > 0)
		{
			screen->SetItemIndex(screen->GetItemIndex() - 1);
		}
		else
		{
			screen->SetItemIndex(count - 1);
		}
	} while (!screen->GetActiveItem()->IsShownGlobal()
			|| !screen->GetActiveItem()->GetChoseable());

	printItem();
	screen->GetActiveItem()->printItem();
}

void gui_Item::Click(void)
{
	ramPart->bitField.b.IsClicked ^= 1;
	printItem();
}

}
