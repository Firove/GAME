#include "Floor.h"
#include"ofImage.h"

Floor::Floor()
{

	setView();

	_X = abs(ofRandomf())*(ofGetWidth()-_FL.getWidth());
	_Y = abs(ofRandomf()*0.7)*(ofGetHeight()-_FL.getHeight());

}

void Floor::draw() {

	_FL.draw(_X, _Y);

}

void Floor::onframe() {
	_Y -= 0.2f;
}

void Floor::resetPos() {
	if (_Y<-50) {
		_Y = ofGetHeight()+ _FL.getHeight();
	}
}


void Floor::setView() {
	_HY = 0;
	_FL.loadImage("floor0.png");
}

Floor1::Floor1() :Floor() {
	setView();
}

void Floor1::setView() {
	_HY = 10;
	_FL.loadImage("floor1.png");
}