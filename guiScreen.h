/*
 * guiScreen.h
 *
 *  Created on: 4.7.2012
 *      Author: kubanec
 */

#ifndef GUISCREEN_H_
#define GUISCREEN_H_

#include "guiCommon.h"

/*
 * @todo sem naházet pointery na itemy nebo labely ktery se maji vyjet
 */

class gui_Screen
{
public:
	gui_Screen(void * parent,uint8_t index);
	~gui_Screen();
	void printScreen(void);
	void constructor(void * parent,uint8_t index);
#ifdef DYNAMIC_ALLOC
	gui_Item * MakeItem();
	gui_Label * MakeLabel();
#endif

	gui_Item * AddItems(gui_Item * items, uint8_t count, bool lock = true);
	gui_Label * AddLabels(gui_Label * labels, uint8_t count, bool lock = true);
	bool IsActive();
	uint8_t GetItemIndex()
	{
		return ItemIndex;
	}
	void SetBackgroundColor(uint16_t color)
	{
		BackgroundColor = color;
	}
	void SetTextColor(uint16_t color)
	{
		TextColor = color;
	}
	uint16_t GetTextColor()
	{
		return TextColor;
	}
	uint16_t GetBackGroundColor()
	{
		return BackgroundColor;
	}
	uint16_t GetSize();
	gui_Item * GetActiveItem();
	void SetItemIndex(uint8_t idx)
	{
		ItemIndex = idx;
	}
	uint8_t GetItemCount(void)
	{
		return ItemCount;
	}

	void SetActive (void);

private:
	uint8_t ItemIndex;
	uint8_t ScreenIndex;
	uint16_t BackgroundColor; /*!< background color of screen*/
	uint16_t TextColor; /*!< default text color in screen*/
	uint8_t LabelCount;
	uint8_t ItemCount;
	gui_Label * LabelField;
	void * parent;
	/*
	 * sem se pošle sada pole pointerů na jednotlivy item aby se to nemuselo
	 * alokovat dynamicky tak si to každé alokuje staticky ještě předtim než
	 * to zavolá a hodi to do konstruktoru
	 * musi se dat pozor na to aby si to nejdřiv poukládal do flašky a pak
	 * teprv to hodil sem jinak to nepovali
	 */
	gui_Item * ItemField;
};

#endif /* GUISCREEN_H_ */
