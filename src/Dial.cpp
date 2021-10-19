//
// Created by Blair on 02/10/2021.
//

#include "../include/Dial.h"

Dial::Dial(int majW, int minW, int dx, int dy, QWidget *parent) : QWidget(parent) {
	this->x = dx;
	this->y = dy;
	
	layout = new QGridLayout(this);
	outer = new DialOuter(dx, dy, majW, minW);
	
	layout->setContentsMargins(0, 0, 0, 0);
	
	layout->addWidget(outer);
	
	setLayout(layout);
}

Dial::~Dial() {
	delete layout;
	delete outer;
};

void Dial::paintEvent(QPaintEvent *event) {
	QPainter dialOuter(this);
	
	dialOuter.setPen(QPen(QBrush(0xC0C0C0), 10));
	dialOuter.setBrush(QColor(Qt::black));
	dialOuter.setRenderHint(QPainter::Antialiasing);
	
	QPainterPath dialOutline;
	dialOutline.addEllipse(this->x, this->y, this->radius, this->radius);
	dialOuter.drawPath(dialOutline);
}

