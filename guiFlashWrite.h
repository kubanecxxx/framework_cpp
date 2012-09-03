/*
 * guiFlashWrite.h
 *
 *  Created on: 5.7.2012
 *      Author: kubanec
 */

#ifndef GUIFLASHWRITE_H_
#define GUIFLASHWRITE_H_

#include "guiCommon.h"

/* Base address of the Flash sectors */
#define ADDR_FLASH_SECTOR_0     ((uint32_t)0x08000000) /* Base @ of Sector 0, 16 Kbytes */
#define ADDR_FLASH_SECTOR_1     ((uint32_t)0x08004000) /* Base @ of Sector 1, 16 Kbytes */
#define ADDR_FLASH_SECTOR_2     ((uint32_t)0x08008000) /* Base @ of Sector 2, 16 Kbytes */
#define ADDR_FLASH_SECTOR_3     ((uint32_t)0x0800C000) /* Base @ of Sector 3, 16 Kbytes */
#define ADDR_FLASH_SECTOR_4     ((uint32_t)0x08010000) /* Base @ of Sector 4, 64 Kbytes */
#define ADDR_FLASH_SECTOR_5     ((uint32_t)0x08020000) /* Base @ of Sector 5, 128 Kbytes */
#define ADDR_FLASH_SECTOR_6     ((uint32_t)0x08040000) /* Base @ of Sector 6, 128 Kbytes */
#define ADDR_FLASH_SECTOR_7     ((uint32_t)0x08060000) /* Base @ of Sector 7, 128 Kbytes */
#define ADDR_FLASH_SECTOR_8     ((uint32_t)0x08080000) /* Base @ of Sector 8, 128 Kbytes */
#define ADDR_FLASH_SECTOR_9     ((uint32_t)0x080A0000) /* Base @ of Sector 9, 128 Kbytes */
#define ADDR_FLASH_SECTOR_10    ((uint32_t)0x080C0000) /* Base @ of Sector 10, 128 Kbytes */
#define ADDR_FLASH_SECTOR_11    ((uint32_t)0x080E0000) /* Base @ of Sector 11, 128 Kbytes */
namespace GuiFramework
{

class gui_FlashWrite
{
public:
	gui_FlashWrite();
	~gui_FlashWrite();
	static uint32_t GetSector(uint32_t Address);
	static void Erase(uint32_t start, uint32_t stop);
	static void * Write(void * datas, uint32_t size);

private:
	static void * Write(uint32_t start_address, void * data, uint32_t size);
	static uint32_t LastAddress;
	static uint32_t EndAddress;

	static const uint32_t sectors[12];
};
}
#endif /* GUIFLASHWRITE_H_ */
