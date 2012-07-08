/*
 * guiItem.h
 *
 *  Created on: 4.7.2012
 *      Author: kubanec
 */

#ifndef GUIITEM_H_
#define GUIITEM_H_

#include "guiCommon.h"

typedef void (*gui_ButtonCallbackTypedef)(void *);
typedef gui_ButtonCallbackTypedef gui_ButtonCallbackArrayTypedef[BUTTON_COUNT];

typedef void (*gui_ConverstionValueToText)(char *, int16_t);

class gui_Item: public gui_LabelBase
{
public:
	gui_Item();
	gui_Item(void * par, uint8_t idx);
	~gui_Item();
	void printItem(void);
	void constructor();
	void constructor(void * par, uint8_t idx);

	void operator+=(uint16_t data);
	void operator-=(uint16_t data);
	void operator++(void);
	void operator--(void);
	void NextItem(void);
	void PrevItem(void);
	void Click(void);

	void SetIndex(uint8_t data)
	{
		Index = data;
	}
	uint8_t GetIndex(void)
	{
		return Index;
	}
	void SetBackgroundColorActive(uint16_t data)
	{
		BackgroundColorActive = data;
	}
	void SetBackgroundColorClicked(uint16_t data)
	{
		BackgroundColorClicked = data;
	}
	void SetTextColorActive(uint16_t data)
	{
		TextColorActive = data;
	}
	void SetTextColorClicked(uint16_t data)
	{
		TextColorClicked = data;
	}
	void SetStep(uint8_t data)
	{
		Step = data;
	}
	void SetLowLimit(int16_t data)
	{
		LowLimit = data;
	}
	void SetHighLimit(int16_t data)
	{
		HighLimit = data;
	}
	void SetConvFunction(gui_ConverstionValueToText fce)
	{
		ConversionFunction = fce;
	}

	uint8_t GetStep()
	{
		return Step;
	}
	int16_t GetLowLimit()
	{
		return LowLimit;
	}
	int16_t GetHighLimit()
	{
		return HighLimit;
	}
	bool GetActive();
	uint16_t GetSize();

	enum Buttons
	{
		BUTTON_UP = 0, BUTTON_DOWN = 1, BUTTON_ENTER = 2
	};

	enum CallbackType
	{
		CLICKED = 1, NOTCLICKED = 0
	};

	void Event(Buttons number, CallbackType type);
	void SetCallback(Buttons number, CallbackType type,
			gui_ButtonCallbackTypedef callback);

private:
	uint8_t Index;

	//properties
	uint16_t BackgroundColorActive; /*!< background color of active(chosen) item */
	uint16_t BackgroundColorClicked; /*!< background color of clicked item*/
	uint16_t TextColorActive; /*!< textcolor of active(chosen) item*/
	uint16_t TextColorClicked; /*!< textcolor of clicked item*/
	uint8_t Step; /*!< step of value increasing/decreasing by default up/down button callbacks*/
	int16_t LowLimit; /*!< low limit of value by button callbacks*/
	int16_t HighLimit; /*!< high limit of value by button callbacks*/

	//funkce na převod Value na String
	gui_ConverstionValueToText ConversionFunction; /*!< conversion function for conversion between value and textvalue*/

	gui_ButtonCallbackArrayTypedef Clicked;
	gui_ButtonCallbackArrayTypedef NotClicked;
};

#endif /* GUIITEM_H_ */
