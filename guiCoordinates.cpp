/*
 * guiCoordinates.cpp
 *
 *  Created on: 4.7.2012
 *      Author: kubanec
 */

#include "guiCommon.h"

namespace GuiFramework
{

gui_Coordinates::gui_Coordinates()
{
	SetX(10);
	SetY(20);
	this->SetScreen(0);
	this->SetShown(true);
	this->SetShownText(true);
	this->SetShownValue(true);
}

gui_Coordinates::~gui_Coordinates()
{

}

}
