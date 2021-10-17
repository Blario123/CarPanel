//
// Created by Blair on 01/10/2021.
//

#include "../include/Display.h"


Display::Display(QWidget *parent) : QWidget(parent) {
	
	
    vLayout = new QVBoxLayout(this);
	hLayout = new QHBoxLayout();
	
	top = new DisplayTop();
	
	hSpacer = new QSpacerItem(600, 0);
	displaySpacer = new QSpacerItem(0, 100);
	
	
}

Display::~Display() {
	delete label;
	delete vLayout;
	delete hLayout;
	delete top;
	delete hSpacer;
	delete displaySpacer;
}


