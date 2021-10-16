//
// Created by Blair on 02/10/2021.
//

#include "../include/RevCounter.h"

RevCounter::RevCounter(QWidget *parent) : QWidget(parent) {
	dial = new Dial(1000, 100, this);
	dial->outer->setIncrements(9, 3);
	layout = new QGridLayout(this);
	layout->setContentsMargins(0, 0 ,0 ,0);
	layout->addWidget(dial);
	setLayout(layout);
}

RevCounter::~RevCounter() {}

void RevCounter::paintEvent(QPaintEvent *event) {
}
