/*
 * guiRamPart.cpp
 *
 *  Created on: 4.7.2012
 *      Author: kubanec
 */

#include "guiCommon.h"

gui_RamPart::gui_RamPart()
{
	constructor();
}

gui_RamPart::~gui_RamPart()
{

}

void gui_RamPart::constructor()
{
	Value = 0;
	bitField.b.DefaultBackgroundColor = true;
	bitField.b.DefaultTextColor = true;
	bitField.b.IsChoseable = true;
	bitField.b.IsClicked = false;
	bitField.b.IsShown = true;
	bitField.b.ValueRounding = true;
}

