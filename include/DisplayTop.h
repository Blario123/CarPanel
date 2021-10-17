//
// Created by Blair on 06/10/2021.
//

#ifndef CARPANEL_DISPLAYTOP_H
#define CARPANEL_DISPLAYTOP_H

#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>
#include <QDateTime>

class DisplayTop : public QWidget {
Q_OBJECT

public:
	explicit DisplayTop(QWidget *parent = nullptr);
	~DisplayTop() override;

private:
};


#endif //CARPANEL_DISPLAYTOP_H
