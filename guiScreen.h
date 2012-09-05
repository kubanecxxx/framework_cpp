/*
 * guiScreen.h
 *
 *  Created on: 4.7.2012
 *      Author: kubanec
 */

#ifndef GUISCREEN_H_
#define GUISCREEN_H_

/*
 * @todo sem naházet pointery na itemy nebo labely ktery se maji vyjet
 */

namespace GuiFramework
{
class gui_Screen: public gui_New
{
public:
	gui_Screen();
	static void printActiveScreen(void);
	void printScreen(void)
	{
		SetActive();
		printActiveScreen();
	}
	uint16_t GetSize();
	 static bool ButtonScan();

	inline gui_Item * Register(gui_Item * item, bool storeToFlash = false)
	{
		item->SetParentScreen(this);
		if (storeToFlash)
			item = item->WriteToFlash();

		return item->Register(item, ItemCount, FirstItem);
	}

	inline gui_Label * Register(gui_Label * label, bool storeToFlash = false)
	{
		label->SetParentScreen(this);
		if (storeToFlash)
			label = label->WriteToFlash();

		return label->Register(label, LabelCount, FirstLabel);
	}

	inline uint8_t GetItemIndex()
	{
		return ItemIndex;
	}
	inline gui_Item * GetActiveItem(void)
	{
		return gui_Item::GetFromIndex(FirstItem, ItemIndex, ItemCount);
	}
	inline void SetBackgroundColor(uint16_t color)
	{
		BackgroundColor = color;
	}
	inline void SetTextColor(uint16_t color)
	{
		TextColor = color;
	}
	inline uint16_t GetTextColor()
	{
		return TextColor;
	}
	inline uint16_t GetBackGroundColor()
	{
		return BackgroundColor;
	}
	inline void SetItemIndex(uint8_t idx)
	{
		ItemIndex = idx;
	}
	inline uint8_t GetItemCount(void)
	{
		return ItemCount;
	}
	inline void SetActive(void)
	{
		ActiveScreen = this;
	}
	inline bool IsActive()
	{
		return (ActiveScreen == this);
	}
	inline static uint8_t GetScreenCount(void)
	{
		return Count;
	}
	static gui_Screen * GetActiveScreen(void)
	{
		return ActiveScreen;
	}

private:
	uint8_t ItemIndex;
	uint16_t BackgroundColor; /*!< background color of screen*/
	uint16_t TextColor; /*!< default text color in screen*/

	static uint8_t Count;
	static gui_Screen * ActiveScreen;

	gui_Item * FirstItem;
	gui_Label * FirstLabel;
	uint8_t LabelCount;
	uint8_t ItemCount;
};
}
#endif /* GUISCREEN_H_ */
