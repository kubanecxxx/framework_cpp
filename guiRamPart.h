/*
 * guiRamPart.h
 *
 *  Created on: 4.7.2012
 *      Author: kubanec
 */

#ifndef GUIRAMPART_H_
#define GUIRAMPART_H_

class gui_RamPart: public gui_New
{
public:
	gui_RamPart();
	~gui_RamPart();

	int16_t Value;

	union
	{
		struct
		{
			uint8_t IsShown :1; //použito jako globální show pro všechno všude (cely pole coordinates)
			uint8_t ValueRounding :1;
			uint8_t DefaultBackgroundColor :1;
			uint8_t DefaultTextColor :1;
			uint8_t IsChoseable :1;
			uint8_t IsClicked :1;
		} b;
		uint8_t w;
	} bitField;
private:
};

#endif /* GUIRAMPART_H_ */
