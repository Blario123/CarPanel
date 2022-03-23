//
// Created by Blair on 01/10/2021.
//

#include "include/CarPanel.h"

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
	leftInd = new Indicator;
	rightInd = new Indicator;
	
	leftInd->setPosition(500, 75);
	rightInd->setPosition(1036, 75);
	rightInd->toggleOrientation();
	
	center = new DisplayMain;
	center->setPosition(650, 100);
	
	left->dial->needle->setAngleLimit(ctrl->revSlider->maximum());
	right->dial->needle->setAngleLimit(ctrl->speedSlider->maximum());
	
	scene->addItem(background);
	scene->addItem(left);
	scene->addItem(right);
	scene->addItem(center);
	scene->addItem(leftInd);
	scene->addItem(rightInd);

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
	
	QFontDatabase::addApplicationFont("qrc:///resouces/CEROM.otf");
	
	layout->addWidget(ctrl, 1, 0);
    setLayout(layout);
	
	connect(ctrl, SIGNAL(speedChanged(qreal)), this->right->dial->needle, SLOT(setAngle(qreal)));
	connect(ctrl, SIGNAL(speedChanged(qreal)), this->center->text, SLOT(setSpeed(qreal)));
	connect(ctrl, SIGNAL(revChanged(qreal)), this->left->dial->needle, SLOT(setAngle(qreal)));
	connect(ctrl, SIGNAL(pageChanged(int)), this->center->text, SLOT(setPage(int)));
	connect(ctrl, SIGNAL(closeSignal()), this, SLOT(deleteLater()));
	connect(this, SIGNAL(toggleLInd()), leftInd, SLOT(toggle()));
	connect(this, SIGNAL(toggleRInd()), rightInd, SLOT(toggle()));
}

void CarPanel::mousePressEvent(QMouseEvent *event) {
	emit toggleLInd();
	emit toggleRInd();
}
