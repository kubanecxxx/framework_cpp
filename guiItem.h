/*
 * guiItem.h
 *
 *  Created on: 4.7.2012
 *      Author: kubanec
 */

#ifndef GUIITEM_H_
#define GUIITEM_H_

namespace GuiFramework
{
class gui_Screen;

/**
 * @brief item, umí všechno co label + má nastavitelnou hodnotu a dá se vybirat a klikat
 */
class gui_Item: public gui_LabelBase, public guiDoubleLinkedListClass<gui_Item>
{
public:
	gui_Item();
	~gui_Item();
	void print(void);
	void operator+=(uint16_t data);
	void operator-=(uint16_t data);
	void operator++(void);
	void operator--(void);
	void NextItem(void);
	void PrevItem(void);
	void Click(void);

	typedef void (*gui_ConverstionValueToText)(char *, int16_t);
	typedef void (*gui_ButtonCallbackTypedef)(void *);
	typedef gui_ButtonCallbackTypedef gui_ButtonCallbackArrayTypedef[BUTTON_COUNT];


	inline uint8_t GetIndex(void) const
	{
		return Index;
	}
	inline void SetBackgroundColorActive(uint16_t data)
	{
		BackgroundColorActive = data;
	}
	inline void SetBackgroundColorClicked(uint16_t data)
	{
		BackgroundColorClicked = data;
	}
	inline void SetTextColorActive(uint16_t data)
	{
		TextColorActive = data;
	}
	inline void SetTextColorClicked(uint16_t data)
	{
		TextColorClicked = data;
	}
	inline void SetStep(uint8_t data)
	{
		Step = data;
	}
	inline void SetLowLimit(int16_t data)
	{
		LowLimit = data;
	}
	inline void SetHighLimit(int16_t data)
	{
		HighLimit = data;
	}
	inline void SetConvFunction(gui_ConverstionValueToText fce)
	{
		ConversionFunction = fce;
	}

	inline uint8_t GetStep() const
	{
		return Step;
	}
	inline int16_t GetLowLimit() const
	{
		return LowLimit;
	}
	inline int16_t GetHighLimit() const
	{
		return HighLimit;
	}
	bool GetActive();
	uint16_t GetSize() const;

	enum Buttons
	{
		BUTTON_UP = 0, BUTTON_DOWN = 1, BUTTON_ENTER = 2
	};

	enum CallbackType
	{
		CLICKED = 1, NOTCLICKED = 0
	};


	void SetCallback(Buttons number, CallbackType type,
			gui_ButtonCallbackTypedef callback);

	/**
	 * @brief vrátí pointer na integer s value - mužou s tim pracovat moduly
	 */
	inline int16_t * GetValuePointer()
	{
		return &(ramPart->Value);
	}
	/**
	 * @brief taky vrátí pointer akorát constantní
	 */
	inline const int16_t * GetValueConstPointer() const
	{
		return &(ramPart->Value);
	}
	///je zapnuty globální zobravání hodnoty
	inline bool IsShowValue() const
	{
		return PrimaryCoor.GetShownValue();
	}
	///zapne globální zobrazování hodnoty pro všechny souřadnice
	inline void SetShownValue(bool data)
	{
		PrimaryCoor.SetShownValue(data);
	}
	inline void SetValue(int16_t value)
	{
		ramPart->Value = value;
	}
	inline int16_t GetValue(void) const
	{
		return ramPart->Value;
	}
	inline void SetValueRounding(bool data)
	{
		ramPart->bitField.b.ValueRounding = data;
	}
	inline void SetChoseable(bool data)
	{
		ramPart->bitField.b.IsChoseable = data;
	}
	inline bool GetValueRounding() const
	{
		return ramPart->bitField.b.ValueRounding;
	}
	inline bool GetChoseable() const
	{
		return ramPart->bitField.b.IsChoseable;
	}
	inline bool GetClicked() const
	{
		return ramPart->bitField.b.IsClicked;
	}
	inline void SetClicked(bool data)
	{
		ramPart->bitField.b.IsClicked = data;
	}

private:

	void Event(Buttons number, CallbackType type);

	inline void SetIndex(uint8_t data)
	{
		Index = data;
	}

	uint8_t Index;

	friend class gui_Screen;

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
}
#endif /* GUIITEM_H_ */
