/**
 * @file PlotWidget.h
 * @author kubanec
 * @date 29.11.2012
 *
 */

#ifndef PLOTWIDGET_H_
#define PLOTWIDGET_H_

namespace GuiFramework
{

class PlotWidget: public GuiFramework::gui_Coordinates
{
public:
	PlotWidget();

	void print();
	inline void SetData(const int16_t * data, uint8_t length)
	{
		plotData = data;
		dataLength = length;
	}
	inline void SetXAutoscale(bool dat)
	{
		bitField.b.PlotAutoScaleX = dat;
	}
	inline void SetYAutoscale(bool dat)
	{
		bitField.b.PlotAutoScaleY = dat;
	}
	inline void SetDimensions(uint16_t x, uint16_t y)
	{
		xSize = x;
		ySize = y;
	}
	inline void SetDataColor(uint16_t color)
	{
		dataColor = color;
	}
	inline void SetAxesColor(uint16_t color)
	{
		axeColor = color;
	}
	inline void SetBackgroundColor(uint16_t color)
	{
		backgroundColor = color;
	}
	inline void SetYLimits(uint16_t min, uint16_t max)
	{
		ymin = min;
		ymax = max;
	}
	inline void SetXStep(uint8_t step)
	{
		stepX = step;
	}
	inline uint16_t GetSize() const
	{
		return sizeof(this);
	}

private:
	const int16_t * plotData;
	uint8_t dataLength;
	uint16_t xSize;
	uint16_t ySize;

	uint16_t dataColor;
	uint16_t axeColor;
	uint16_t backgroundColor;

	int16_t ymin, ymax;
	int16_t yDivider;
	uint8_t stepX;

	void printAxes() const;
	void printData() const;
	void ComputeYLimits();
	void ComputeXStep();
};

} /* namespace GuiFramework */
#endif /* PLOTWIDGET_H_ */
