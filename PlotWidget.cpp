/**
 * @file PlotWidget.cpp
 * @author kubanec
 * @date 29.11.2012
 *
 */

#include "guiCommon.h"

const int16_t mata[] =
{ 4, 1, 2, 3 };

namespace GuiFramework
{

PlotWidget::PlotWidget()
{
	dataColor = 0xffff;
	backgroundColor = 0x0;
	axeColor = 0x07E0;

	xSize = 100;
	ySize = 50;
	plotData = NULL;
	dataLength = 0;

	bitField.b.PlotAutoScaleX = true;
	bitField.b.PlotAutoScaleY = false;
	bitField.b.PlotOnlyPoints = false;
	bitField.b.PlotTitleX = false;
	bitField.b.PlotTitleY = false;

	SetData(mata, 4, 1);
	SetYLimits(0, 5);
	SetXStep(15);
}

/**
 * @brief vytiskne graf podle jeho nastaveni pokud je aktivni jeho parent screen
 */
void PlotWidget::print()
{
	if (!Parent->IsActive())
		return;

	port::drawRectangle(x, y, x + xSize + 1, y + ySize + 1, backgroundColor);
	ComputeYLimits();
	ComputeXStep();
	printAxes();
	if (plotData == NULL || dataLength == 0 || firstIndex >= dataLength)
		return;
	printData();
}

/**
 * @brief vytiskne osy
 *
 * osa Y je vždycky na začátku grafu, počitá se stim že se bude zobrazovat jenom kladna
 * osa X se vypočte podle limit hodnoty y
 */
void PlotWidget::printAxes() const
{
	///osa y bude dycky na začátku, počitá se s tim že to bude pruběh v čase
	///osa x by se mohla nějak podle rozsahu dat vypočitat

	//y axe
	port::drawLine(x, y, x, y + ySize, axeColor);
	//x axe

	if (ymax >= 0 && ymin <= 0)
	{
		int16_t avg;
		int32_t shift;

		shift = (((ymax) << 4) / (ymax - ymin) * ySize) >> 4;
		avg = y + shift;
		port::drawLine(x, avg, x + xSize, avg, axeColor);
	}
}

void PlotWidget::printData() const
{
	/**
	 * když dat bude vic než je rozlišeni grafu?
	 * pruměrovat X nevykreslit vic
	 *
	 * v y zpruměrovat podle size a rozsahu maxima a minima
	 * nebo měřitko natvrdo
	 *
	 * @todo promyslet podporu kruhovyho bufferu
	 */

	int16_t avg;
	int32_t shift;

	shift = (((ymax) << 4) / (ymax - ymin) * ySize) >> 4;
	avg = y + shift;

	for (int i = 0; i < dataLength; i++)
	{
		//modulo adresování
		int j = i + firstIndex;
		if (j >= dataLength)
			j -= dataLength;

		uint16_t yp = avg - ((plotData[j] * yDivider) >> 4);
		uint16_t ex = x + i * stepX;
		//pokud je hodnota mimo rozsah tak se nevykresli
		if (yp >= y && yp <= y + ySize && ex <= x + xSize)
		{
			uint16_t y_prev;
			uint16_t x_prev;

			if (!bitField.b.PlotOnlyPoints && i > 0)
			{
				port::drawLine(x_prev, y_prev, ex, yp, dataColor);
			}
			port::putPixel(ex, yp, dataColor);
			y_prev = yp;
			x_prev = ex;
		}
	}
}

void PlotWidget::ComputeYLimits()
{
	//pokud je vypnuty automaticky měřitko nic se nepřepočte
	if (bitField.b.PlotAutoScaleY)
	{
		//najit maxima a minima a z velikosti y vpixelech vypočitat limity
		///@todo dodělat výpočet automatickyho měřitka v ose Y
	}

	yDivider = (ySize << 4) / (ymax - ymin);
}

///pokud je vypnuty automaticky měřitko v X nic neudělá
///jinak vypočte přimo krok z počtu hodnot a velikosti grafu
void PlotWidget::ComputeXStep()
{
	if (bitField.b.PlotAutoScaleX)
	{
		stepX = xSize / dataLength;
	}
}

} /* namespace GuiFramework */
