#include "include/Control.h"

Control::Control(QWidget *parent) : QWidget(parent),
									gridBox(new QGridLayout),
									speedLineEdit(new QLineEdit),
									revLineEdit(new QLineEdit),
									speedLabel(new QLabel(tr("Speed"))),
									revLabel(new QLabel(tr("Rev/m"))),
									pageLabel(new QLabel(tr("Page"))),
									pageName(new QLabel(tr("Speed"))),
									speedSlider(new QSlider),
									revSlider(new QSlider),
									spinBox(new QSpinBox) {
	speedLineEdit->setText(QString::number(speedSlider->value()));
	revLineEdit->setText(QString::number(revSlider->value()));
	
	speedLineEdit->setReadOnly(true);
	revLineEdit->setReadOnly(true);
	
	speedSlider->setMaximum(15000);
	revSlider->setMaximum(8000);
	
	speedSlider->setOrientation(Qt::Horizontal);
	revSlider->setOrientation(Qt::Horizontal);

	spinBox->setSizePolicy(QSizePolicy::Policy::Maximum, QSizePolicy::Policy::Expanding);
	spinBox->setFixedWidth(100);
	spinBox->setRange(0, 8);
	spinBox->setWrapping(true);
	
	connect(speedSlider, SIGNAL(valueChanged(int)), this, SLOT(setSpeed(int)));
	connect(revSlider, SIGNAL(valueChanged(int)), this, SLOT(setRev(int)));
	connect(spinBox, SIGNAL(valueChanged(int)), this, SLOT(processPage(int)));
	
	gridBox->addWidget(speedLabel, 0, 0);
	gridBox->addWidget(speedLineEdit, 0, 1);
	gridBox->addWidget(speedSlider, 1, 0, 1, 2);
	gridBox->addWidget(revLabel, 2, 0);
	gridBox->addWidget(revLineEdit, 2, 1);
	gridBox->addWidget(revSlider, 3, 0, 1, 2);
	gridBox->addWidget(pageLabel, 0, 2);
	gridBox->addWidget(pageName, 3, 2);
	gridBox->addWidget(spinBox, 1, 2, 2, 1);
	
	setLayout(gridBox);
}

Control::~Control() = default;

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
