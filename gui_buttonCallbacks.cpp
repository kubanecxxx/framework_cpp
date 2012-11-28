#include "guiCommon.h"

namespace GuiFramework
{

/**
 * @brief Defaultní callbacky pro tlačitka od itemů
 * @defgroup default_callbaks
 * @{
 */

void gui_EventNotClickedDown(void * data)
{
	gui_Item * item = (gui_Item *) data;

	item->PrevItem();
}
void gui_EventNotClickedUp(void * data)
{
	gui_Item * item = (gui_Item *) data;

	item->NextItem();
}
void gui_EventNotClickedEnter(void * data)
{
	gui_Item * item = (gui_Item *) data;

	item->Click();
}
void gui_EventClickedDown(void * data)
{
	gui_Item * item = (gui_Item *) data;

	--(*item);
}
void gui_EventClickedUp(void * data)
{
	gui_Item * item = (gui_Item *) data;

	++(*item);
}
void gui_EventClickedEnter(void * data)
{
	gui_Item * item = (gui_Item *) data;

	item->Click();
}

/**
 * @}
 */

}
//nebudu 
