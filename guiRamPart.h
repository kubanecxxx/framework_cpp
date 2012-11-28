/*
 * guiRamPart.h
 *
 *  Created on: 4.7.2012
 *      Author: kubanec
 */

#ifndef GUIRAMPART_H_
#define GUIRAMPART_H_

/**
 * @brief framework jak sviňa
 *
 * zatim to umi jenom vytvořit screeny a do nich dávat 2 typy widgetů item a label
 */
namespace GuiFramework
{

/**
 * @brief část vlastností v ramce
 *
 * scvhálně jsou tyhle vlastnosti ve zvláštní třídě aby se celá maminka třída mohla uložit
 * do flašky ať nežere ramku a tohle jenom zustane v ramce aby se to mohlo ještě v runtimu měnit
 */
class gui_RamPart
{
public:
	gui_RamPart();

	///hodnota, která se zobrazuje přes funkcu pro konverze na string
	int16_t Value;

	union
	{
		struct
		{
			///použito jako globální show pro všechny dílčí souřadnice
			uint8_t IsShown :1;
			///protáčení hodnoty
			uint8_t ValueRounding :1;
			///používat defaultní barvu pozadí
			uint8_t DefaultBackgroundColor :1;
			///používat defaultní barvu textu
			uint8_t DefaultTextColor :1;
			///může se na něho najet tlačitkama
			uint8_t IsChoseable :1;
			///je rozkliknuté
			uint8_t IsClicked :1;
		}
		///bitovy vlastosti pro přistup po jednotlivech bitech
		b;
		///pro přístup jako k celymu bitu
		uint8_t w;
	}
	///bitovy vlastnosti
	bitField;
private:
};
}
#endif /* GUIRAMPART_H_ */
