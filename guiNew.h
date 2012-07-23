/**
 * @file guiNew.h
 * @author kubanec
 * @date 23.7.2012
 *
 */

#ifndef GUINEW_H_
#define GUINEW_H_

#include <new>

class gui_New
{
public:
	static void * operator new (size_t size);
};

#endif /* GUINEW_H_ */
