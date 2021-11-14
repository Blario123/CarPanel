//
// Created by Blair on 01/10/2021.
//

#include "../include/CarPanel.h"
#include <QFile>
#include <QTimer>

int indicatorState = 0;

void setNoViewScrollbars(QGraphicsView *pView);

CarPanel::CarPanel(QWidget *parent) : QWidget(parent) {
    this->setWindowFlag(Qt::MSWindowsFixedSizeDialogHint);
    this->setGeometry(window()->width() / 2,window()->height() / 2,1600,800);

	auto *scene = new QGraphicsScene();
	auto *view = new QGraphicsView();
    auto *left = new RevCounter();
    auto *right = new Speedometer();

//	right: dial = new Dial(20, 10, 1000, 100, this);
//  right: kmDial = new DialOuter(1050, 150, 20, 10, 0x666666, 450);
	
	right->dial->setPosition(1000, 100);
	right->kmDial->setPosition(1050, 150);
	
	left->dial->setPosition(50, 100);
	
	setNoViewScrollbars(view);
	scene->setSceneRect(0, 0, 1600, 800);
	
    setBackgroundRole(QPalette::Window);

    layout = new QGridLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setGeometry(QRect(0, 0, 1600, 800));
	
	leftInd = new Indicator(500,150 - 64,0x101010);
	rightInd = new Indicator(1036,150,0x101010,180);

    center = new Display();
	
	scene->addItem(left);
	scene->addItem(right);
	scene->setItemIndexMethod(QGraphicsScene::NoIndex);
	view->setScene(scene);
	view->setRenderHint(QPainter::Antialiasing);
	view->setCacheMode(QGraphicsView::CacheBackground);
	view->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
	view->setDragMode(QGraphicsView::NoDrag);
	view->setStyleSheet("background: transparent");
	
    if (setStyle() != 0) {
        qDebug() << "Error opening stylesheet.";
    }
	
	QFontDatabase::addApplicationFont("qrc:///resouces/CEROM.otf");

    layout->addWidget(center, 0, 0);
	layout->addWidget(leftInd, 0, 0);
	layout->addWidget(rightInd, 0, 0);
	layout->addWidget(view, 0, 0);

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
    delete layout;
	delete leftInd;
	delete rightInd;
}
void CarPanel::paintEvent(QPaintEvent *p) {
  QPixmap pixmap;
  pixmap.load(":/resources/outline.png");
  QPainter paint(this);
  paint.drawPixmap(0, 0, pixmap);
//  QWidget::paintEvent(p);
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

void setNoViewScrollbars(QGraphicsView *pView) {
	pView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	pView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}
