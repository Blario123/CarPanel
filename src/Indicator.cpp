//
// Created by Blair on 03/10/2021.
//

#include <QPainter>
#include <QPainterPath>
#include "../include/Indicator.h"

Indicator::Indicator(int ix, int iy, QColor icolour,float iorientation, QWidget *parent) : QWidget(parent) {
	this->x = ix;
	this->y = iy;
	this->orientation = iorientation;
	this->colour = new QColor(icolour);
	
}

Indicator::~Indicator() = default;

void Indicator::paintEvent(QPaintEvent *p) {
	QPolygon path;
	
	QPoint origin(x + (this->size / 2), y + (this->size / 2));
	
	path 	<< QPoint(origin.x(), origin.y() + this->size / 2)
			<< QPoint(origin.x() + 30, origin.y())
			<< QPoint(origin.x() + 30, origin.y() + 12)
			<< QPoint(origin.x() + this->size, origin.y() + 12)
			<< QPoint(origin.x() + this->size, origin.y() + 52)
			<< QPoint(origin.x() + 30, origin.y() + 52)
			<< QPoint(origin.x() + 30, origin.y() + this->size)
			<< QPoint(origin.x(), origin.y() + (this->size / 2));
	
	path = QTransform().translate(origin.x(), origin.y()).rotate(this->orientation).translate(-origin.x(), -origin.y()).map(path);
	
	QPainterPath indicator;
	indicator.addPolygon(path);
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);
	painter.drawPolygon(path);
	painter.fillPath(indicator, *this->colour);
}

void Indicator::setColour(QColor indColour) {
	*this->colour = indColour;
	this->update();
}
