/*
 * guiFlashWrite.cpp
 *
 *  Created on: 5.7.2012
 *      Author: kubanec
 */

#include "guiFlashWrite.h"

namespace GuiFramework
{

uint32_t gui_FlashWrite::LastAddress = 0;
uint32_t gui_FlashWrite::EndAddress = 0;

gui_FlashWrite::gui_FlashWrite()
{

}

gui_FlashWrite::~gui_FlashWrite()
{

}
void * gui_FlashWrite::Write(void * datas, uint32_t size)
{
	return Write(LastAddress,datas,size);
}

void * gui_FlashWrite::Write(uint32_t Address, void * datas, uint32_t size)
{
#if 0
	uint32_t * data = (uint32_t *) datas;
	uint32_t temp = Address;

	FLASH_Unlock();
	size /= 4;
	while (size--)
	{
		if (FLASH_ProgramWord(Address, *(data++)) == FLASH_COMPLETE)
		{
			Address += 4;
		}
		else
		{
			/* Error occurred while writing data in Flash memory.
			 User can add here some code to deal with this error */
			while (1)
			{
			}
		}
	}
	LastAddress = Address;
	FLASH_Lock();

	return (void *)temp;
#endif
}

void gui_FlashWrite::Erase(uint32_t start, uint32_t stop)
{
#if 0
	FLASH_Unlock();
	FLASH_ClearFlag(
			FLASH_FLAG_EOP | FLASH_FLAG_OPERR | FLASH_FLAG_WRPERR
					| FLASH_FLAG_PGAERR | FLASH_FLAG_PGPERR | FLASH_FLAG_PGSERR);

	/* Get the number of the start and end sectors */
	uint32_t StartSector = GetSector(start);
	uint32_t EndSector = GetSector(stop);

	for (uint32_t SectorCounter = StartSector; SectorCounter < EndSector;
			SectorCounter += 8)
	{
		/* Device voltage range supposed to be [2.7V to 3.6V], the operation will
		 be done by word */
		if (FLASH_EraseSector(SectorCounter, VoltageRange_3) != FLASH_COMPLETE)
		{
			/* Error occurred while sector erase.
			 User can add here some code to deal with this error  */
			while (1)
			{
			}
		}
	}
	LastAddress = start;
	EndAddress = stop;
	FLASH_Lock();
#endif
}

uint32_t gui_FlashWrite::GetSector(uint32_t Address)
{
#if 0
	uint32_t sector = 0;

	if ((Address < ADDR_FLASH_SECTOR_1) && (Address >= ADDR_FLASH_SECTOR_0))
	{
		sector = FLASH_Sector_0;
	}
	else if ((Address < ADDR_FLASH_SECTOR_2)
			&& (Address >= ADDR_FLASH_SECTOR_1))
	{
		sector = FLASH_Sector_1;
	}
	else if ((Address < ADDR_FLASH_SECTOR_3)
			&& (Address >= ADDR_FLASH_SECTOR_2))
	{
		sector = FLASH_Sector_2;
	}
	else if ((Address < ADDR_FLASH_SECTOR_4)
			&& (Address >= ADDR_FLASH_SECTOR_3))
	{
		sector = FLASH_Sector_3;
	}
	else if ((Address < ADDR_FLASH_SECTOR_5)
			&& (Address >= ADDR_FLASH_SECTOR_4))
	{
		sector = FLASH_Sector_4;
	}
	else if ((Address < ADDR_FLASH_SECTOR_6)
			&& (Address >= ADDR_FLASH_SECTOR_5))
	{
		sector = FLASH_Sector_5;
	}
	else if ((Address < ADDR_FLASH_SECTOR_7)
			&& (Address >= ADDR_FLASH_SECTOR_6))
	{
		sector = FLASH_Sector_6;
	}
	else if ((Address < ADDR_FLASH_SECTOR_8)
			&& (Address >= ADDR_FLASH_SECTOR_7))
	{
		sector = FLASH_Sector_7;
	}
	else if ((Address < ADDR_FLASH_SECTOR_9)
			&& (Address >= ADDR_FLASH_SECTOR_8))
	{
		sector = FLASH_Sector_8;
	}
	else if ((Address < ADDR_FLASH_SECTOR_10)
			&& (Address >= ADDR_FLASH_SECTOR_9))
	{
		sector = FLASH_Sector_9;
	}
	else if ((Address < ADDR_FLASH_SECTOR_11)
			&& (Address >= ADDR_FLASH_SECTOR_10))
	{
		sector = FLASH_Sector_10;
	}
	else/*(Address < FLASH_END_ADDR) && (Address >= ADDR_FLASH_SECTOR_11))*/
	{
		sector = FLASH_Sector_11;
	}

	return sector;
#endif
}

}
