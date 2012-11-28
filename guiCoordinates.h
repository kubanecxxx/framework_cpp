/*
 * guiCoordinates.h
 *
 *  Created on: 4.7.2012
 *      Author: kubanec
 */

#ifndef GUICOORDINATES_H_
#define GUICOORDINATES_H_

/*
 * tohle se taky alokuje jako static a nechá se to v ramce,
 * snad to nebude žrat moc mista
 */


namespace GuiFramework
{
class gui_LabelBase;
class gui_Screen;
class gui_Coordinates
{
public:
	gui_Coordinates();
	~gui_Coordinates();
	inline void SetX(uint16_t xcoor)
	{
		x = xcoor;
	}
	inline uint16_t GetX(void) const
	{
		return x;
	}
	inline void SetY(uint16_t ycoor)
	{
		y = ycoor;
	}
	inline uint16_t GetY(void) const
	{
		return y;
	}

	inline gui_Screen * GetScreen(void)
	{
		return Parent;
	}
	inline void SetShown(bool data)
	{
		bitField.b.IsShown = data;
	}
	inline void SetShownText(bool data)
	{
		bitField.b.IsShownText = data;
	}
	inline void SetShownValue(bool data)
	{
		bitField.b.IsShownValue = data;
	}
	inline bool GetShown(void) const
	{
		return bitField.b.IsShown;
	}
	inline bool GetShownText(void) const
	{
		return bitField.b.IsShownText;
	}
	inline bool GetShownValue(void) const
	{
		return bitField.b.IsShownValue;
	}
private:
	uint16_t x;
	uint16_t y;
	gui_Screen * Parent;
	friend class gui_LabelBase;

	union
	{
		struct
		{
			uint8_t IsShown :1;
			uint8_t IsShownText :1;
			uint8_t IsShownValue :1;
		} b;
		uint8_t w;
	} bitField;
};
}
#endif /* GUICOORDINATES_H_ */
