/*
 * guiLabelBase.h
 *
 *  Created on: 4.7.2012
 *      Author: kubanec
 */

#ifndef GUILABELBASE_H_
#define GUILABELBASE_H_

namespace GuiFramework
{
class gui_Screen;

/**
 * @brief základní třída použitá pro label a item
 *
 * label v podstatě jenom implementuje print a getsize, kdyby šly virtuální metody, nemusela
 * by vůbec být třída label a jenom item by ju dědil a dopsal si svoje věci
 * @bug nemůžu použít virtuální ani pure virtuální metody, pak vymrzne zápis do flašky
 */
class gui_LabelBase
{
	/**
	 * @brief nastaví parent screen
	 */
	inline void SetParentScreen(gui_Screen * par)
	{
		PrimaryCoor.Parent = par;
	}
public:
	gui_LabelBase();
	void AddSecondaryCoor(uint16_t x, uint16_t y, gui_Screen * screen);

	inline gui_Screen * GetParentScreen(void)
	{
		return PrimaryCoor.GetScreen();
	}
	void SetText(const char * text);
	inline const char * GetText(void) const
	{
		return Text;
	}
	inline void SetBackgroundColor(uint16_t color)
	{
		BackgroundColor = color;
	}
	inline uint16_t GetBackGroundColor(void) const
	{
		return BackgroundColor;
	}
	inline void SetTextColor(uint16_t color)
	{
		TextColor = color;
	}
	inline uint16_t GetTextColor(void) const
	{
		return TextColor;
	}
	inline void SetFontSize(uint8_t size)
	{
		FontSize = size;
	}
	inline uint8_t GetFontSize(void) const
	{
		return FontSize;
	}

	inline gui_RamPart * GetRamPart(void)
	{
		return ramPart;
	}
	inline void SetCoordinates(gui_Coordinates * coor, uint8_t cunt = 1)
	{
		CoordinatesSys = coor;
		CoordinatesCount = cunt;
	}
	inline gui_Coordinates * GetSecondaryCoordinates(void)
	{
		return CoordinatesSys;
	}
	inline gui_Coordinates * GetSecondaryCoordinates(uint16_t * cunt)
	{
		*cunt = CoordinatesCount;
		return CoordinatesSys;
	}
	inline uint16_t GetPrimaryX(void) const
	{
		return PrimaryCoor.x;
	}
	inline uint16_t GetPrimaryY(void) const
	{
		return PrimaryCoor.y;
	}
	inline void SetPrimaryX(uint16_t data)
	{
		PrimaryCoor.SetX(data);
	}
	inline void SetPrimaryY(uint16_t dta)
	{
		PrimaryCoor.SetY(dta);
	}
	///je zapnuty zobrazování lokální pro jedny souřadnice
	inline bool IsShown() const
	{
		return PrimaryCoor.GetShown();
	}
	///je  zapnuty globální zobrazování textu
	inline bool IsShownText() const
	{
		return PrimaryCoor.GetShownText();
	}
	///zapne lokální zobrazování pro primární souřadnice
	inline void SetShown(bool data)
	{
		PrimaryCoor.SetShown(data);
	}
	///zapne globální zobrazování textu pro všechny souřadnice
	inline void SetShownText(bool data)
	{
		PrimaryCoor.SetShownText(data);
	}
	///zapne globální zobrazování widgetu pro všechny souřanice
	inline void SetShownGlobal(bool data)
	{
		ramPart->bitField.b.IsShown = data;
	}
	inline void SetUseDefaultBackgroundColor(bool data)
	{
		ramPart->bitField.b.DefaultBackgroundColor = data;
	}

	inline void SetUseDefaultTextColor(bool data)
	{
		ramPart->bitField.b.DefaultTextColor = data;
	}
	///je zapnuty globální zobrazování
	inline bool IsShownGlobal() const
	{
		return ramPart->bitField.b.IsShown;
	}
	inline bool GetUseDefaultBackgroundColor() const
	{
		return ramPart->bitField.b.DefaultBackgroundColor;
	}
	inline bool GetUseDefaultTextColor() const
	{
		return ramPart->bitField.b.DefaultTextColor;
	}
	//odvozená třída musí implementovat print

#if 0
	virtual void print() = 0;
	virtual uint16_t GetSize() const = 0;
#endif

protected:
	///pointer na text co už je ve flašce nebo jinde v ramce ale musi si to alokovat user
	const char * Text;
	///barva pozadí
	uint16_t BackgroundColor;
	///barva textu
	uint16_t TextColor;
	///velikost fontu
	uint8_t FontSize;

	friend class gui_Screen;
	/**
	 * třída rampart se alokuje na heapě a nebude se mazat
	 * zůstane dycky v ramce a nebude se zapisovat do flašky
	 */
	gui_RamPart * ramPart;
	/// primární souřadnice - taky se uložijou do flašky
	gui_Coordinates PrimaryCoor;
	///sekundární se už neuložijou
	gui_Coordinates * CoordinatesSys;
	uint8_t CoordinatesCount; /*!< number of secondary coordinates, enable show secondary items*/
};
}
#endif /* GUILABELBASE_H_ */
