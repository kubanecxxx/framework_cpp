/*
 * common.h
 *
 *  Created on: 4.7.2012
 *      Author: kubanec
 */

#ifndef _GUI_COMMON_H_
#define _GUI_COMMON_H_

#include "inttypes.h"
#include "guiDoubleLinkedListClass.h"
#include "guiNew.h"
#include "port/framework_port.h"
#include "guiCoordinates.h"
#include "guiRamPart.h"
#include "guiLabelBase.h"
#include "guiLabel.h"
#include "guiItem.h"
#include "guiScreen.h"
//#include "guiGuiBase.h"
#include "gui_buttonCallbacks.h"
#include "guiFlashWrite.h"


#define BASE_TYPE uint8_t

typedef union
{
	struct
	{
		BASE_TYPE bit7:1;
		BASE_TYPE bit6:1;
		BASE_TYPE bit5:1;
		BASE_TYPE bit4:1;
		BASE_TYPE bit3:1;
		BASE_TYPE bit2:1;
		BASE_TYPE bit1:1;
		BASE_TYPE bit0:1;
	} b;
	BASE_TYPE w;
} bitFieldType;


#endif /* _GUI_COMMON_H_ */
