/**
 * @file guiNew.cpp
 * @author kubanec
 * @date 23.7.2012
 *
 */

#include "guiCommon.h"

namespace GuiFramework
{


void * gui_New::operator new(size_t size)
{
	return gui_malloc(size);
}

void gui_New::operator delete(void * data)
{
	gui_freeMemory(data);
}
}
