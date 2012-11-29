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
/**
 * @brief zastřešuje celé screen
 *
 * má v sobě pointery na widgety ve screenu
 * samotny screeny už si musi pohlidat uživatel
 * <br>
 * uživatel si alokuje screen a někam si ho uloži a pak muže mezi něma přepinat a tisknout je
 */
class gui_Screen
{
public:
	gui_Screen();
	static void printActiveScreen(void);
	///@brief nastavi screen jako aktivní a vytiskne ho
	void printScreen(void)
	{
		SetActive();
		printActiveScreen();
	}
	uint16_t GetSize() const;
	static bool ButtonScan();

	///@brief zaregistruje item do screenu a může ho rovnou narvat do flašky
	gui_Item * Register(gui_Item * item, bool storeToFlash = false)
	{
		gui_Item * temp = item;
		item->SetParentScreen(this);
		item->SetIndex(ItemCount);
		if (storeToFlash)
			temp = item->WriteToFlash();

		return temp->Register(temp, ItemCount, FirstItem);
	}

	///@brief zaregistruje label do screenu a může ho rovnou narvat do flašky
	gui_Label * Register(gui_Label * label, bool storeToFlash = false)
	{
		gui_Label * temp = label;
		label->SetParentScreen(this);
		if (storeToFlash)
			temp = label->WriteToFlash();

		return temp->Register(temp, LabelCount, FirstLabel);
	}

	inline uint8_t GetItemIndex() const
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
	inline uint16_t GetTextColor() const
	{
		return TextColor;
	}
	inline uint16_t GetBackGroundColor() const
	{
		return BackgroundColor;
	}
	inline void SetItemIndex(uint8_t idx)
	{
		ItemIndex = idx;
	}
	inline uint8_t GetItemCount(void) const
	{
		return ItemCount;
	}
	inline void SetActive(void)
	{
		ActiveScreen = this;
	}
	///@brief jesli je tenhle screen aktivní
	inline bool IsActive() const
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
