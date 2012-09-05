/**
 * @file guiNew.h
 * @author kubanec
 * @date 23.7.2012
 *
 */

#ifndef GUINEW_H_
#define GUINEW_H_

namespace GuiFramework
{


class gui_New
{
public:
	static void * operator new (size_t size);
	static void operator delete(void * data);
};
}
#endif /* GUINEW_H_ */
