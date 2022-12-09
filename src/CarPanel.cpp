#include <QMenu>
#include "CarPanel.h"

CarPanel::CarPanel(const QString &name,QWidget *parent) : 	QWidget(parent),
                                                             left(new RevCounter("RevCounter")),
                                                             right(new Speedometer("Speedometer")),
                                                             center(new DisplayMain("Display")),
                                                             ctrl(new Control("Control")),
                                                             leftInd(new Indicator("LeftIndicator")),
                                                             rightInd(new Indicator("RightIndicator")),
                                                             layout(new QGridLayout),
                                                             scene(new QGraphicsScene),
                                                             view(new QGraphicsView),
                                                             background(new Background("Background")),
                                                             showControl(new QAction("Show Control")),
                                                             parser(new XMLParser("Parser")) {
    setWindowFlags(windowFlags() | Qt::MSWindowsFixedSizeDialogHint);
    setContextMenuPolicy(Qt::CustomContextMenu);

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

    scene->setItemIndexMethod(QGraphicsScene::BspTreeIndex);

    view->setContentsMargins(0, 0, 0, 0);
    view->setScene(scene);
    view->setSceneRect(scene->itemsBoundingRect());
    view->setRenderHint(QPainter::Antialiasing);
    view->setCacheMode(QGraphicsView::CacheNone);
    view->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    view->setStyleSheet("background: transparent");

    layout->addWidget(view, 0, 0);

    if(QFontDatabase::addApplicationFont(":/resources/CarPanel.otf") == -1) {
        qDebug() << "Font failed to load";
    }

    setLayout(layout);

    connect(ctrl, &Control::speedChanged, right->dial->needle, &DialNeedle::setAngle);
    connect(ctrl, &Control::speedChanged, center->text, &DisplayText::setSpeed);
    connect(ctrl, &Control::revChanged, left->dial->needle, &DialNeedle::setAngle);
    connect(ctrl, &Control::pageChanged, center->text, &DisplayText::setPage);
    connect(this, &CarPanel::closeSignal, ctrl, &Control::deleteLater);

    connect(ctrl, &Control::toggleLInd, leftInd, &Indicator::toggle);
    connect(ctrl, &Control::setLInd, leftInd, &Indicator::setState);
    connect(ctrl, &Control::toggleRInd, rightInd, &Indicator::toggle);
    connect(ctrl, &Control::setRInd, rightInd, &Indicator::setState);
    connect(this, &CarPanel::customContextMenuRequested, this, &CarPanel::showRClickMenu);
    connect(ctrl, &Control::rangeChanged, center->text, &DisplayText::setValueRange);
    connect(ctrl, &Control::valueChanged, center->text, &DisplayText::setValue);
    connect(ctrl, &Control::valueChanged, parser, &XMLParser::writeValue);
    connect(parser, &XMLParser::setValue, center->text, &DisplayText::setValue);
    connect(parser, &XMLParser::setValueFromPage, ctrl, &Control::setValueFromPage);

    parser->parseXML();
}

void CarPanel::showRClickMenu(const QPoint &p) {
    QMenu rClickMenu("", this);
    connect(showControl, &QAction::triggered, ctrl, (ctrl->isVisible()) ? &Control::activateWindow : &Control::show);
    rClickMenu.addAction(showControl);
    rClickMenu.exec(mapToGlobal(p));
}

void CarPanel::closeEvent(QCloseEvent *event) {
    emit closeSignal();
    QWidget::closeEvent(event);
    exit(0);
}
