//
// Created by Blair on 02/10/2021.
//

#include "../include/Dial.h"

Dial::Dial(int dx, int dy, QWidget *parent) : QWidget(parent) {
	setGeometry(dx, dy, radius, radius);
	this->x = dx;
	this->y = dy;
	
	layout = new QGridLayout(this);
	outer = new DialOuter(dx, dy, this);
	
	layout->setContentsMargins(0, 0, 0, 0);
	
	layout->addWidget(outer);
	
	setLayout(layout);
}

Dial::~Dial() = default;

void Dial::paintEvent(QPaintEvent *event) {
	QPainter dialOuter(this);
	
	dialOuter.setPen(QPen(QBrush(0xC0C0C0), 10));
	dialOuter.setBrush(QColor(Qt::black));
	dialOuter.setRenderHint(QPainter::Antialiasing);
	
	QPainterPath dialOutline;
	dialOutline.addEllipse(this->x, this->y, radius, radius);
	dialOuter.drawPath(dialOutline);
#if 0
	QLine vert(this->x + radius/2, this->y, this->x + radius/2, this->y + radius);
	QLine hoz(this->x, this->y + radius/2, this->x + radius, this->y + radius/2);
	dialOuter.setBrush(Qt::NoBrush);
	dialOuter.setPen(QPen(QBrush(0xC0C0C0), 2));
	dialOuter.drawLine(vert);
	dialOuter.drawLine(hoz);
#endif
}

