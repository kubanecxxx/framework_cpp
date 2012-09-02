/*
 * guiRamPart.cpp
 *
 *  Created on: 4.7.2012
 *      Author: kubanec
 */

#include "guiCommon.h"

namespace GuiFramework
{


gui_RamPart::gui_RamPart()
{
	Value = 0;
	bitField.b.DefaultBackgroundColor = true;
	bitField.b.DefaultTextColor = true;
	bitField.b.IsChoseable = true;
	bitField.b.IsClicked = false;
	bitField.b.IsShown = true;
	bitField.b.ValueRounding = true;
}

gui_RamPart::~gui_RamPart()
{

}
}
