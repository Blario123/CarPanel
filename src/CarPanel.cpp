#include "include/CarPanel.h"

CarPanel::CarPanel(QWidget *parent) : 	QWidget(parent),
										left(new RevCounter),
										right(new Speedometer),
										center(new DisplayMain),
										ctrl(new Control),
										leftInd(new Indicator),
										rightInd(new Indicator),
										layout(new QGridLayout),
										scene(new QGraphicsScene),
										view(new QGraphicsView),
										background(new Background),
										showControl(new QAction) {
    setWindowFlag(Qt::MSWindowsFixedSizeDialogHint);
    setGeometry(0, 0, 1600, 920);

	layout->setContentsMargins(0, 0, 0 , 0);
	
	leftInd->setPosition(500, 75);
	rightInd->setPosition(1036, 75);
	rightInd->toggleOrientation();
	
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
	
	int returnId = QFontDatabase::addApplicationFont(":/resources/CarPanel.otf");
	if(returnId == -1) {
		qDebug() << "Font failed to load";
	}
	
	layout->addWidget(ctrl, 1, 0);
    setLayout(layout);
	
	connect(ctrl, &Control::speedChanged, this->right->dial->needle, &DialNeedle::setAngle);
	connect(ctrl, &Control::speedChanged, this->center->text, &DisplayText::setSpeed);
	connect(ctrl, &Control::revChanged, this->left->dial->needle, &DialNeedle::setAngle);
	connect(ctrl, &Control::pageChanged, this->center->text, &DisplayText::setPage);
	connect(ctrl, &Control::closeSignal, this, &QWidget::deleteLater);
	connect(this, &CarPanel::toggleLInd, leftInd, &Indicator::toggle);
	connect(this, &CarPanel::toggleRInd, rightInd, &Indicator::toggle);
}

void CarPanel::mousePressEvent(QMouseEvent *event) {
	if(event->button() == Qt::LeftButton) {
		emit toggleLInd();
		emit toggleRInd();
	}
	if(event->button() == Qt::RightButton) {
	
	}
}
