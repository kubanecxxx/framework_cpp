/*
 * guiFlashWrite.cpp
 *
 *  Created on: 5.7.2012
 *      Author: kubanec
 */

#include "inttypes.h"
#include "guiFlashWrite.h"
//#include "stm32f4xx_flash.h"

namespace GuiFramework
{

uint32_t gui_FlashWrite::LastAddress = 0;
uint32_t gui_FlashWrite::EndAddress = 0;

const uint32_t gui_FlashWrite::sectors[12] =
{ SEC_0, SEC_1, SEC_2, SEC_3, SEC_4, SEC_5, SEC_6, SEC_7, SEC_8, SEC_9, SEC_10,
		SEC_11 };

//@todo předělat do portingu

void * gui_FlashWrite::Write(uint32_t Address,const void * datas, uint32_t size)
{
#if 0
	const uint32_t * data = (uint32_t *) datas;
	uint32_t temp = Address;

	while (size % 4 != 0)
		size++;

	size /= 4;

	FLASH_Unlock();
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

	return (void *) temp;
#endif
}

void gui_FlashWrite::Erase(uint32_t start, uint32_t stop)
{
#if 0
	FLASH_Unlock();
	FLASH_ClearFlag(
			FLASH_FLAG_EOP | FLASH_FLAG_OPERR | FLASH_FLAG_WRPERR
					| FLASH_FLAG_PGAERR | FLASH_FLAG_PGPERR
					| FLASH_FLAG_PGSERR );

	/* Get the number of the start and end sectors */
	uint32_t StartSector = GetSector(start);
	uint32_t EndSector = GetSector(stop);

	for (uint32_t SectorCounter = StartSector; SectorCounter < EndSector;
			SectorCounter += 8)
	{
		/* Device voltage range supposed to be [2.7V to 3.6V], the operation will
		 be done by word */
		if (FLASH_EraseSector(SectorCounter, VoltageRange_3 ) != FLASH_COMPLETE)
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
	uint32_t i;

	for (i = 11; i != 0; i--)
	{
		if (Address >= sectors[i])
			break;
	}

	return (i  * 8);
}
}
