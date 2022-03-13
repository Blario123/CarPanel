//
// Created by Blair on 01/10/2021.
//

#include "include/CarPanel.h"
#include <QTimer>
#include <QFontDatabase>

int indicatorState = 0;

CarPanel::CarPanel(QWidget *parent) : QWidget(parent) {
    this->setWindowFlag(Qt::MSWindowsFixedSizeDialogHint);
    this->setGeometry(0, 0, 1600, 920);

	layout = new QGridLayout;
	layout->setContentsMargins(0, 0, 0 , 0);
	
	auto *scene = new QGraphicsScene;
	auto *view = new QGraphicsView;
	auto *background = new Background;
	
	ctrl = new Control;
	left = new RevCounter;
    right = new Speedometer;
	
	center = new Display;
	center->setPosition(650, 100);
	
	left->dial->needle->setAngleLimit(ctrl->revSlider->maximum());
	right->dial->needle->setAngleLimit(ctrl->speedSlider->maximum());
	
	scene->addItem(background);
	scene->addItem(left);
	scene->addItem(right);
	scene->addItem(center);

	scene->setItemIndexMethod(QGraphicsScene::NoIndex);
	
	view->setContentsMargins(0, 0, 0, 0);
	view->setScene(scene);
	view->setRenderHint(QPainter::Antialiasing);
	view->setCacheMode(QGraphicsView::CacheNone);
	view->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
	view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	view->setAlignment(Qt::AlignTop | Qt::AlignLeft);
	view->setStyleSheet("background: transparent");

	layout->addWidget(view, 0, 0);
/****
	leftInd = new Indicator(500,150 - 64,0x101010);
	rightInd = new Indicator(1036,150,0x101010,180);
****/
	QFontDatabase::addApplicationFont("qrc:///resouces/CEROM.otf");
	
	layout->addWidget(ctrl, 1, 0);
    setLayout(layout);
	
	connect(ctrl, SIGNAL(speedChanged(qreal)), this->right->dial->needle, SLOT(setAngle(qreal)));
	connect(ctrl, SIGNAL(speedChanged(qreal)), this->center, SLOT(setSpeed(qreal)));
	connect(ctrl, SIGNAL(revChanged(qreal)), this->left->dial->needle, SLOT(setAngle(qreal)));
	connect(ctrl, SIGNAL(closeSignal()), this, SLOT(deleteLater()));
	
}

CarPanel::~CarPanel() = default;

void CarPanel::mousePressEvent(QMouseEvent *event) {
	if(indicatorState == 0) {
//		leftInd->setColour(0x00ff00);
//		rightInd->setColour(0x00ff00);
		indicatorState = 1;
	} else {
//		leftInd->setColour(0x101010);
//		rightInd->setColour(0x101010);
		indicatorState = 0;
	}
}
