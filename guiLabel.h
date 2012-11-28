/*
 * guiLabel.h
 *
 *  Created on: 4.7.2012
 *      Author: kubanec
 */

#ifndef GUILABEL_H_
#define GUILABEL_H_

/*
 * @todo hodit ve kterym screenu to je
 */
namespace GuiFramework
{

class gui_Label : public gui_LabelBase, public guiDoubleLinkedListClass<gui_Label>
{
public:
	/**
	 * všechno set,get
	 */
	void print(void);
	uint16_t GetSize() const;

private:

};
}
#endif /* GUILABEL_H_ */
