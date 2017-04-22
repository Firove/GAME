#pragma once

#include "ofMain.h"

class Floor
{
public:
	Floor();
	void draw();
	void onframe();
	void resetPos();
	friend class Ball;
	virtual void setView();
	ofImage _FL;



protected:
	float _X, _Y, _HY;



};

class Floor1 : public Floor
{
public:
	Floor1();
	virtual void setView() override;
};