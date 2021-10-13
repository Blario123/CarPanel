//
// Created by Blair on 02/10/2021.
//

#include "../include/Speedometer.h"

Speedometer::Speedometer(QWidget *parent) : QWidget(parent) {
	dial = new Dial(50, 100, this);
	grid = new QGridLayout(this);
	grid->setContentsMargins(0, 0, 0, 0);
	grid->addWidget(dial);
	setLayout(grid);
}

Speedometer::~Speedometer() {
	delete dial;
	delete grid;
}

void Speedometer::paintEvent(QPaintEvent *event) {

}
