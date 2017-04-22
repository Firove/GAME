#include "myButton.h"
myButton::myButton(float x, float y, ofImage _btn) :
	_X(x), _Y(y), _BTN(_btn)
{
	_X = x;
	_Y = y;
};

void myButton::draw() {
	_BTN.draw(_X, _Y);
}

bool myButton::init(int x, int y) {
	if (x>_X&&x<_X + _BTN.getWidth()&&y>_Y&&y<_Y + _BTN.getHeight()) {
		return true;
	}
	else {
		return false;
	}
}