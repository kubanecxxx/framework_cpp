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
	void printScreen(void);
	uint16_t GetSize();

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
		IndexActive = ScreenIndex;
	}
	inline bool IsActive()
	{
		return (IndexActive == ScreenIndex);
	}
	inline static uint8_t GetScreenCount(void)
	{
		return Count;
	}
	inline static uint8_t GetActiveIndex(void)
	{
		return IndexActive;
	}

private:
	uint8_t ItemIndex;
	uint8_t ScreenIndex;
	uint16_t BackgroundColor; /*!< background color of screen*/
	uint16_t TextColor; /*!< default text color in screen*/

	static uint8_t Count;
	static uint8_t IndexActive;

	gui_Item * FirstItem;
	gui_Label * FirstLabel;
	uint8_t LabelCount;
	uint8_t ItemCount;
};
}
#endif /* GUISCREEN_H_ */
