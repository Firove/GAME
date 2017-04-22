#pragma once

#include "ofMain.h"

class myButton
{
public:
	myButton(float x, float y, ofImage _btn);
	void draw();
	bool init(int x, int y);

protected:
	ofImage _BTN;
	float _X;
	float _Y;
};