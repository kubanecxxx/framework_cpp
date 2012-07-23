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

class gui_Screen;

class gui_Coordinates: public gui_New
{
public:
	gui_Coordinates();
	~gui_Coordinates();
	void SetX(uint16_t xcoor)
	{
		x = xcoor;
	}
	uint16_t GetX(void)
	{
		return x;
	}
	void SetY(uint16_t ycoor)
	{
		y = ycoor;
	}
	uint16_t GetY(void)
	{
		return y;
	}
	void SetScreen(gui_Screen * screen)
	{
		Parent = screen;
	}
	gui_Screen * GetScreen(void)
	{
		return Parent;
	}
	void SetShown(bool data)
	{
		bitField.b.IsShown = data;
	}
	void SetShownText(bool data)
	{
		bitField.b.IsShownText = data;
	}
	void SetShownValue(bool data)
	{
		bitField.b.IsShownValue = data;
	}
	bool GetShown(void)
	{
		return bitField.b.IsShown;
	}
	bool GetShownText(void)
	{
		return bitField.b.IsShownText;
	}
	bool GetShownValue(void)
	{
		return bitField.b.IsShownValue;
	}
private:
	uint16_t x;
	uint16_t y;
	gui_Screen * Parent;

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

#endif /* GUICOORDINATES_H_ */
