/*
 * guiCoordinates.cpp
 *
 *  Created on: 4.7.2012
 *      Author: kubanec
 */

#include "guiCommon.h"

gui_Coordinates::gui_Coordinates()
{
	constructor2();
}

gui_Coordinates::~gui_Coordinates()
{

}

void gui_Coordinates::constructor2()
{
	SetX(10);
	SetY(20);
	this->SetScreen(0);
	this->SetShown(true);
	this->SetShownText(true);
	this->SetShownValue(true);
}
