//
// Created by Blair on 01/10/2021.
//

#include "../include/CarPanel.h"
#include <QFile>

int indicatorState = 0;

CarPanel::CarPanel(QWidget *parent) : QWidget(parent) {
    this->setWindowFlag(Qt::MSWindowsFixedSizeDialogHint);
    this->setGeometry(window()->width() / 2,window()->height() / 2,1600,800);

    setBackgroundRole(QPalette::Window);

    layout = new QGridLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setGeometry(QRect(0, 0, 1600, 800));
	
	leftInd = new Indicator(500,150 - 64,0x101010);
	rightInd = new Indicator(1036,150,0x101010,180);

    left = new RevCounter();
    center = new Display();
    right = new Speedometer();
	
    if (setStyle() != 0) {
        qDebug() << "Error opening stylesheet.";
    }
	
	QFontDatabase::addApplicationFont("qrc:///resouces/CEROM.otf");

    layout->addWidget(center, 0, 0);
    layout->addWidget(left, 0, 0);
    layout->addWidget(right, 0, 0);
	layout->addWidget(leftInd, 0, 0);
	layout->addWidget(rightInd, 0, 0);

    setLayout(layout);
}

int CarPanel::setStyle() {
    QFile file(":/resources/CarPanel.qss");
    if (file.open(QFile::ReadOnly)) {
        this->setStyleSheet(QString::fromUtf8(file.readAll()));
        return 0;
    } else {
        return 1;
    }
}

CarPanel::~CarPanel() {
    delete center;
    delete left;
    delete right;
    delete layout;
	delete leftInd;
	delete rightInd;
}
void CarPanel::paintEvent(QPaintEvent *p) {
  QPixmap pixmap;
  pixmap.load(":/resources/outline.png");
  QPainter paint(this);
  paint.drawPixmap(0, 0, pixmap);
  QWidget::paintEvent(p);
}

void CarPanel::mousePressEvent(QMouseEvent *event) {
	if(indicatorState == 0) {
		leftInd->setColour(0x00ff00);
		rightInd->setColour(0x00ff00);
		indicatorState = 1;
	} else {
		leftInd->setColour(0x101010);
		rightInd->setColour(0x101010);
		indicatorState = 0;
	}
}
