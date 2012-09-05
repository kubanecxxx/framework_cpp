/*
 * gui_buttonCallbacks.h
 *
 *  Created on: 5.7.2012
 *      Author: kubanec
 */

#ifndef GUI_BUTTONCALLBACKS_H_
#define GUI_BUTTONCALLBACKS_H_

namespace GuiFramework
{

void gui_EventNotClickedDown(void * data);
void gui_EventNotClickedUp(void * data);
void gui_EventNotClickedEnter(void * data);
void gui_EventClickedDown(void * data);
void gui_EventClickedUp(void * data);
void gui_EventClickedEnter(void * data);

}

#endif /* GUI_BUTTONCALLBACKS_H_ */
