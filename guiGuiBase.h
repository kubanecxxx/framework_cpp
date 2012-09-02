/*
 * guiGuiBase.h
 *
 *  Created on: 4.7.2012
 *      Author: kubanec
 */

#ifndef GUIGUIBASE_H_
#define GUIGUIBASE_H_



/**
 * třídu si jenom někdo zdědí aby mohl použivat print gui
 */

#include "guiCommon.h"
namespace GuiFramework
{

class gui_GuiBase : public gui_New
{
public:
	gui_GuiBase();
	~gui_GuiBase();

	void print_gui(void);
	/*	void AddScreens(gui_Screen * screens, uint8_t count)
	 {
	 ScreenField = screens;
	 ScreenCount = count;
	 }*/
	gui_Screen * MakeScreen();

	uint16_t GetSize();
	bool ButtonScan();
	uint8_t GetActiveScreenIndex()
	{
		return ScreenIndex;
	}
	void SetActiveScreenIndex(uint8_t data)
	{
		ScreenIndex = data;
	}

private:
	uint8_t ScreenIndex;
	uint8_t ScreenCount;
	gui_Screen * ScreenField;
};
}
#endif /* GUIGUIBASE_H_ */
