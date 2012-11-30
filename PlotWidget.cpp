/**
 * @file PlotWidget.cpp
 * @author kubanec
 * @date 29.11.2012
 *
 */

#include "guiCommon.h"

const int16_t mata[] =
{ 1, 5, 6, -6, -10, 10, 12, -10 };

namespace GuiFramework
{

PlotWidget::PlotWidget()
{
	dataColor = 0xffff;
	backgroundColor = 0x8000;
	axeColor = 0x07E0;

	xSize = 50;
	ySize = 50;
	plotData = NULL;
	dataLength = 0;

	bitField.b.PlotAutoScaleX = true;
	bitField.b.PlotAutoScaleY = true;
	bitField.b.PlotOnlyPoints = true;
	bitField.b.PlotTitleX = false;
	bitField.b.PlotTitleY = false;

	SetData(mata, sizeof(mata));
	SetYLimits(-10, 15);
	SetXStep(5);
}

void PlotWidget::print()
{
	//eště vyplnit pozadí

	ComputeYLimits();
	ComputeXStep();
	printAxes();
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
		port::drawLine(x - 5, avg, x + xSize, avg, axeColor);
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
	 */

	int16_t avg;
	int32_t shift;

	shift = (((ymax) << 4) / (ymax - ymin) * ySize) >> 4;
	avg = y + shift;

	for (int i = 0; i < dataLength; i++)
	{
		uint16_t yp = avg - ((plotData[i] * yDivider) >> 4);
		//pokud je hodnota mimo rozsah tak se nevykresli
		if (yp >= y && yp <= y+ySize)
			port::putPixel(x + i * stepX, yp, dataColor);
	}
}

void PlotWidget::ComputeYLimits()
{
	//pokud je vypnuty automaticky měřitko nic se nepřepočte
	if (bitField.b.PlotAutoScaleY)
	{
		//najit maxima a minima a z velikosti y vpixelech vypočitat limity
	}

	yDivider =  (ySize << 4) / (ymax - ymin);
}

void PlotWidget::ComputeXStep()
{
	//pokud je vypnuty automaticky měřitko v X nic neudělá
	//jinak vypočte přimo krok z počtu hodnot a velikosti grafu
	if (bitField.b.PlotAutoScaleX)
	{
		stepX = xSize / dataLength;
	}
}

} /* namespace GuiFramework */
