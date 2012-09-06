/*
 * guiFlashWrite.h
 *
 *  Created on: 5.7.2012
 *      Author: kubanec
 */

#ifndef GUIFLASHWRITE_H_
#define GUIFLASHWRITE_H_

namespace GuiFramework
{

class gui_FlashWrite
{
public:
	static uint32_t GetSector(uint32_t Address);
	static void Erase(uint32_t start, uint32_t stop);
	static void * Write(void * datas, uint32_t size)
	{
		return Write(LastAddress, datas, size);
	}

	typedef enum
	{
		SEC_0 = 0x08000000,
		SEC_1 = 0x08004000,
		SEC_2 = 0x08008000,
		SEC_3 = 0x0800C000,
		SEC_4 = 0x08010000,
		SEC_5 = 0x08020000,
		SEC_6 = 0x08040000,
		SEC_7 = 0x08060000,
		SEC_8 = 0x08080000,
		SEC_9 = 0x080A0000,
		SEC_10 = 0x080C0000,
		SEC_11 = 0x080E0000,
	} ADDR;

private:
	static void * Write(uint32_t start_address, void * data, uint32_t size);
	static uint32_t LastAddress;
	static uint32_t EndAddress;

	static const uint32_t sectors[12];

	//gui_FlashWrite();
	//~gui_FlashWrite();
};
}
#endif /* GUIFLASHWRITE_H_ */
