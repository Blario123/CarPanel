//
// Created by Blair on 02/10/2021.
//

#include "../include/Speedometer.h"

Speedometer::Speedometer(QWidget *parent) : QWidget(parent) {
	dial = new Dial(20, 10, 1000, 100, this);
	kmDial = new DialOuter(1050, 150, 20, 10, 0x666666, 450);
	dial->outer->setIncrements(8.5,3);
	dial->outer->setText(9, {"0", "20", "40", "60", "80", "100", "120", "140"}, 15);
	kmDial->setIncrements(13, 3);
	kmDial->setText(13, {"0", "20", "40", "60", "80", "100", "120", "140", "160", "180", "200", "220", "240"}, 12);
	grid = new QGridLayout(this);
	grid->setContentsMargins(0, 0, 0, 0);
	grid->addWidget(dial, 0, 0);
	grid->addWidget(kmDial, 0, 0);
	setLayout(grid);
}

Speedometer::~Speedometer() {
	delete dial;
	delete kmDial;
	delete grid;
}

void Speedometer::paintEvent(QPaintEvent *event) {

}
