//
// Created by Blair on 03/10/2021.
//

#ifndef CARPANEL_INDICATOR_H
#define CARPANEL_INDICATOR_H

#include <QWidget>

class Indicator : public QWidget {
	Q_OBJECT
	
public:
	explicit Indicator(int ix, int iy, QColor icolour, QWidget *parent = nullptr, float dorientation = 0 );
	~Indicator() override;

public slots:
	void setColour(QColor indColour);

private:
	int x;
	int y;
	int size = 64;
	float orientation;
	QColor colour;
	void paintEvent(QPaintEvent *p) override;
	
};

#endif // CARPANEL_INDICATOR_H
