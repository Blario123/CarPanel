#include "include/Control.h"

Control::Control(const QString &name,QWidget *parent) : QDialog(parent),
                                                        indicatorTimer(new QTimer(this)),
                                                        controlLayout(new QGridLayout),
                                                        sliderBox(new QGroupBox("Slider Control")),
                                                        tripBox(new QGroupBox("Trip Control")),
                                                        indicatorBox(new QGroupBox("Indicator Control")),
                                                        sliderLayout(new QGridLayout),
                                                        tripLayout(new QGridLayout),
                                                        indicatorLayout(new QGridLayout),
                                                        speedLineEdit(new QLineEdit),
                                                        revLineEdit(new QLineEdit),
                                                        speedLabel(new QLabel(tr("Speed"))),
                                                        revLabel(new QLabel(tr("Rev/m"))),
                                                        pageLabel(new QLabel(tr("Page"))),
                                                        pageName(new QLabel(tr("Speed"))),
                                                        speedSlider(new QSlider),
                                                        revSlider(new QSlider),
                                                        spinBox(new QSpinBox),
                                                        tripTree(new QTreeWidget),
                                                        leftIndButton(new QPushButton("Left")),
                                                        rightIndButton(new QPushButton("Right")),
                                                        hazardButton(new QPushButton("Hazard")) {
    indicatorTimer->start(500);
    speedLineEdit->setText(QString::number(speedSlider->value()));
    revLineEdit->setText(QString::number(revSlider->value()));

    speedLineEdit->setReadOnly(true);
    revLineEdit->setReadOnly(true);

    speedSlider->setMaximum(15000);
    revSlider->setMaximum(8000);

    speedSlider->setOrientation(Qt::Horizontal);
    revSlider->setOrientation(Qt::Horizontal);
    speedSlider->setFixedWidth(500);

    spinBox->setSizePolicy(QSizePolicy::Policy::Maximum, QSizePolicy::Policy::Expanding);
    spinBox->setFixedWidth(100);
    spinBox->setRange(0, 8);
    spinBox->setWrapping(true);

    tripTree->setHeaderLabels({"", "Value"});
    auto *tempItem = new QTreeWidgetItem;
    tripTree->addTopLevelItem(tempItem);


    tripLayout->addWidget(tripTree);
    tripBox->setLayout(tripLayout);

    sliderLayout->addWidget(speedLabel, 0, 0);
    sliderLayout->addWidget(speedLineEdit, 0, 1);
    sliderLayout->addWidget(speedSlider, 1, 0, 1, 2);
    sliderLayout->addWidget(revLabel, 2, 0);
    sliderLayout->addWidget(revLineEdit, 2, 1);
    sliderLayout->addWidget(revSlider, 3, 0, 1, 2);
    sliderLayout->addWidget(pageLabel, 0, 2);
    sliderLayout->addWidget(pageName, 3, 2);
    sliderLayout->addWidget(spinBox, 1, 2, 2, 1);
    sliderBox->setLayout(sliderLayout);

    indicatorLayout->addWidget(leftIndButton, 0, 0);
    indicatorLayout->addWidget(rightIndButton, 0, 1);
    indicatorLayout->addWidget(hazardButton, 1, 0, 1, 2);
    indicatorBox->setLayout(indicatorLayout);

    controlLayout->addWidget(sliderBox, 0, 0);
    controlLayout->addWidget(indicatorBox, 0, 1);
    controlLayout->addWidget(tripBox, 1, 0, 1, 2);

    setLayout(controlLayout);
    connect(leftIndButton, &QPushButton::clicked, this, &Control::onLeftIndicatorClicked);
    connect(rightIndButton, &QPushButton::clicked, this, &Control::onRightIndicatorClicked);
    connect(hazardButton, &QPushButton::clicked, this, &Control::onHazardClicked);
    connect(tripTree, &QTreeWidget::itemDoubleClicked, this, &Control::onItemDoubleClicked);
    connect(speedSlider, &QSlider::valueChanged, this, &Control::setSpeed);
    connect(revSlider, &QSlider::valueChanged, this, &Control::setRev);
    connect(spinBox, &QSpinBox::valueChanged, this, &Control::processPage);
}

void Control::setSpeed(int value) {
    speedLineEdit->setText(QString::number((qreal) value/100));
    emit speedChanged(value);
}

void Control::setRev(int value) {
    revLineEdit->setText(QString::number((qreal) value/100));
    emit revChanged(value);
}

void Control::processPage(int value) {
    emit pageChanged(value);
    switch(value) {
        case 0:
            pageName->setText("Speed");
            break;
        case 1:
            pageName->setText("Warning at");
            break;
        case 2:
            pageName->setText("Oil Temperature");
            break;
        case 3:
            pageName->setText("Consumption");
            break;
        case 4:
            pageName->setText("Avg Consumption");
            break;
        case 5:
            pageName->setText("Range");
            break;
        case 6:
            pageName->setText("Travelling Time");
            break;
        case 7:
            pageName->setText("Distance");
            break;
        case 8:
            pageName->setText("Average Speed");
            break;
        default:
            pageName->setText("");
            break;
    }
    update();
}

void Control::onItemDoubleClicked(QTreeWidgetItem *item, int column) {
    if(column == 0) {
        item->setFlags(item->flags() & (~Qt::ItemIsEditable));
    } else {
        item->setFlags(item->flags() | Qt::ItemIsEditable);
    }
}

void Control::onLeftIndicatorClicked() {
    if(!doLeftIndicator) {
        disconnect(connection);
        emit setRInd(Global::IndicatorState::Off);
        doLeftIndicator = true;
        doRightIndicator = false;
        doHazard = false;
        connection = connect(indicatorTimer, &QTimer::timeout, [=](){
            emit toggleLInd();
        });
    } else {
        disconnect(connection);
        doLeftIndicator = false;
        emit setLInd(Global::IndicatorState::Off);
    }
}

void Control::onRightIndicatorClicked() {
    if(!doRightIndicator) {
        disconnect(connection);
        emit setLInd(Global::IndicatorState::Off);
        doLeftIndicator = false;
        doRightIndicator = true;
        doHazard = false;
        connection = connect(indicatorTimer, &QTimer::timeout, [=](){
            emit toggleRInd();
        });
    } else {
        disconnect(connection);
        doRightIndicator = false;
        emit setRInd(Global::IndicatorState::Off);
    }
}

void Control::onHazardClicked() {
    if(!doHazard) {
        disconnect(connection);
        emit setLInd(Global::IndicatorState::Off);
        emit setRInd(Global::IndicatorState::Off);
        doLeftIndicator = false;
        doRightIndicator = false;
        doHazard = true;
        connection = connect(indicatorTimer, &QTimer::timeout, [=]() {
            emit toggleLInd();
            emit toggleRInd();
        });
    } else {
        emit setLInd(Global::IndicatorState::Off);
        emit setRInd(Global::IndicatorState::Off);
        doHazard = false;
        disconnect(connection);
    }
}

void Control::shutdown() {
    qDebug() << "Close";
}
