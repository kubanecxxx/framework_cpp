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

/**
 * @brief label, jenom implementuje print a getsize
 */
class gui_Label : public gui_LabelBase, public guiDoubleLinkedListClass<gui_Label>
{
public:
	void print(void);
	uint16_t GetSize() const;

private:

};
}
#endif /* GUILABEL_H_ */
