#include "include/Control.h"

Control::Control(const QString &name,QWidget *parent) : QWidget(parent),
                                                        controlLayout(new QGridLayout),
                                                        sliderBox(new QGroupBox("Slider Control")),
                                                        tripBox(new QGroupBox("Trip Control")),
                                                        sliderLayout(new QGridLayout),
                                                        tripLayout(new QGridLayout),
                                                        speedLineEdit(new QLineEdit),
                                                        revLineEdit(new QLineEdit),
                                                        speedLabel(new QLabel(tr("Speed"))),
                                                        revLabel(new QLabel(tr("Rev/m"))),
                                                        pageLabel(new QLabel(tr("Page"))),
                                                        pageName(new QLabel(tr("Speed"))),
                                                        speedSlider(new QSlider),
                                                        revSlider(new QSlider),
                                                        spinBox(new QSpinBox),
                                                        tripTree(new QTreeWidget) {
#ifdef CPDEBUG
    qDebug() << name;
#endif
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

    connect(tripTree, &QTreeWidget::itemDoubleClicked, this, &Control::onItemDoubleClicked);
    connect(speedSlider, &QSlider::valueChanged, this, &Control::setSpeed);
    connect(revSlider, &QSlider::valueChanged, this, &Control::setRev);
    connect(spinBox, &QSpinBox::valueChanged, this, &Control::processPage);

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

    controlLayout->addWidget(sliderBox);
    controlLayout->addWidget(tripBox);

    setLayout(controlLayout);
}

void Control::setSpeed(int value) {
    speedLineEdit->setText(QString::number((qreal) value/100));
    emit speedChanged(value);
}

void Control::setRev(int value) {
    revLineEdit->setText(QString::number((qreal) value/100));
    emit revChanged(value);
}

void Control::closeEvent(QCloseEvent *event) {
    emit closeSignal();
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
