/*
 * guiLabelBase.h
 *
 *  Created on: 4.7.2012
 *      Author: kubanec
 */

#ifndef GUILABELBASE_H_
#define GUILABELBASE_H_

#include "guiCommon.h"

namespace GuiFramework
{
class gui_Screen;

class gui_LabelBase: public gui_New
{
public:

	gui_LabelBase(gui_Screen * par = 0);
	~gui_LabelBase();
	void print(void);
	void AddSecondaryCoor(uint16_t x, uint16_t y, gui_Screen * screen);

	int16_t * GetValuePointer()
	{
		return &(ramPart->Value);
	}

	const int16_t * GetValueConstPointer()
	{
		return &(ramPart->Value);
	}

	void SetParentScreen(gui_Screen * par)
	{
		PrimaryCoor.SetScreen(par);
	}
	gui_Screen * GetParentScreen(void)
	{
		return PrimaryCoor.GetScreen();
	}
	void SetText(const char * text);
	const char * GetText(void)
	{
		return Text;
	}
	void SetBackgroundColor(uint16_t color)
	{
		BackgroundColor = color;
	}
	uint16_t GetBackGroundColor(void)
	{
		return BackgroundColor;
	}
	void SetTextColor(uint16_t color)
	{
		TextColor = color;
	}
	uint16_t GetTextColor(void)
	{
		return TextColor;
	}
	void SetFontSize(uint8_t size)
	{
		FontSize = size;
	}
	uint8_t GetFontSize(void)
	{
		return FontSize;
	}
	void SetRamPart(gui_RamPart * part)
	{
		ramPart = part;
	}
	gui_RamPart * GetRamPart(void)
	{
		return ramPart;
	}
	void SetCoordinates(gui_Coordinates * coor, uint8_t cunt = 1)
	{
		CoordinatesSys = coor;
		CoordinatesCount = cunt;
	}
	gui_Coordinates * GetSecondaryCoordinates(void)
	{
		return CoordinatesSys;
	}
	gui_Coordinates * GetSecondaryCoordinates(uint16_t * cunt)
	{
		*cunt = CoordinatesCount;
		return CoordinatesSys;
	}
	uint16_t GetPrimaryX(void)
	{
		return PrimaryCoor.GetX();
	}
	uint16_t GetPrimaryY(void)
	{
		return PrimaryCoor.GetY();
	}
	void SetPrimaryX(uint16_t data)
	{
		PrimaryCoor.SetX(data);
	}
	void SetPrimaryY(uint16_t dta)
	{
		PrimaryCoor.SetY(dta);
	}

	bool IsShown()
	{
		return PrimaryCoor.GetShown();
	}
	bool IsShownText()
	{
		return PrimaryCoor.GetShownText();
	}
	bool IsShowValue()
	{
		return PrimaryCoor.GetShownValue();
	}
	void SetShown(bool data)
	{
		PrimaryCoor.SetShown(data);
	}
	void SetShownText(bool data)
	{
		PrimaryCoor.SetShownText(data);
	}
	void SetShownValue(bool data)
	{
		PrimaryCoor.SetShownValue(data);
	}

	void SetValue(int16_t value)
	{
		ramPart->Value = value;
	}
	int16_t GetValue(void)
	{
		return ramPart->Value;
	}
	void SetShownGlobal(bool data)
	{
		ramPart->bitField.b.IsShown = data;
	}

	void SetValueRounding(bool data)
	{
		ramPart->bitField.b.ValueRounding = data;
	}

	void SetUseDefaultBackgroundColor(bool data)
	{
		ramPart->bitField.b.DefaultBackgroundColor = data;
	}

	void SetUseDefaultTextColor(bool data)
	{
		ramPart->bitField.b.DefaultTextColor = data;
	}

	void SetChoseable(bool data)
	{
		ramPart->bitField.b.IsChoseable = data;
	}
	void SetClicked(bool data)
	{
		ramPart->bitField.b.IsClicked = data;
	}
	bool IsShownGlobal()
	{
		return ramPart->bitField.b.IsShown;
	}
	bool GetValueRounding()
	{
		return ramPart->bitField.b.ValueRounding;
	}
	bool GetUseDefaultBackgroundColor()
	{
		return ramPart->bitField.b.DefaultBackgroundColor;
	}
	bool GetUseDefaultTextColor()
	{
		return ramPart->bitField.b.DefaultTextColor;
	}
	bool GetChoseable()
	{
		return ramPart->bitField.b.IsChoseable;
	}
	bool GetClicked()
	{
		return ramPart->bitField.b.IsClicked;
	}
protected:
	char Text[16];

	uint16_t BackgroundColor;
	uint16_t TextColor;
	uint8_t FontSize; /*!< font size */

	/*
	 * třída rampart se alokuje na heapě a nebude se mazat
	 * z ramky a pak se v konstruktoru hodi pointer sem
	 */
	gui_RamPart * ramPart;

	gui_Coordinates PrimaryCoor;
	gui_Coordinates * CoordinatesSys;
	uint8_t CoordinatesCount; /*!< number of secondary coordinates, enable show secondary items*/
};
}
#endif /* GUILABELBASE_H_ */
