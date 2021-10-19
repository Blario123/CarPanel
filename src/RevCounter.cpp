//
// Created by Blair on 02/10/2021.
//

#include "../include/RevCounter.h"

RevCounter::RevCounter(QWidget *parent) : QWidget(parent) {
	dial = new Dial(12, 6, 50, 100, this);
	dial->outer->setIncrements(9, 3);
	dial->outer->setText(9, {"0", "10", "20", "30", "40", "50", "60", "70", "80"}, 15);
	layout = new QGridLayout(this);
	layout->setContentsMargins(0, 0 ,0 ,0);
	layout->addWidget(dial);
	setLayout(layout);
}

RevCounter::~RevCounter() = default;

void RevCounter::paintEvent(QPaintEvent *event) {
}
