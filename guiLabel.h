/*
 * guiLabel.h
 *
 *  Created on: 4.7.2012
 *      Author: kubanec
 */

#ifndef GUILABEL_H_
#define GUILABEL_H_

#include "guiCommon.h"

/*
 * @todo hodit ve kterym screenu to je
 */

class gui_Label : public gui_LabelBase
{
public:
	/**
	 * všechno set,get
	 */
	gui_Label();
	~gui_Label();
	void printLabel(void);
	uint16_t GetSize();

private:

};

#endif /* GUILABEL_H_ */
