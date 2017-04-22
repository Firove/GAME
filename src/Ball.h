#pragma once

#include "ofMain.h"
#include "Floor.h"


class Ball
{
public:
	bool eatFoods;//该值判断玩家是否吃掉了子弹
	Ball(ofVec2f _ctr = ofVec2f(),
		float _radius = 5.0f,
		ofColor _color = ofColor::black,
		ofVec2f _vel = ofVec2f(ofRandomf()*5.0f, ofRandom(5.0f, 15.0f)),
		float _decrease = 0.0f);

	friend class Ball4;

	virtual void update(float deltaTime);
	void init();
	void resetPosVel();
	void draw(bool bFill = true);
	bool inside(ofVec2f pos);
	bool contact(Ball another);
	void dragTo(ofVec2f pos);
	void dragOff();
	void absorb(Ball &another);
	void absorb1(Ball &another);
	void changeRadius(bool increase = true);
	void changeRadius1();
	float getRadius();
	ofVec2f getCenter();
	void setup();
	void barrier(Floor fl);
	void limit();

protected:
	ofVec2f _Center;

	float _Radius;
	float _DecreaseSpd;
	ofVec2f _Velocity;
	ofColor _Color;
	float _dragSpd;
	bool _dragged;
	ofSoundPlayer abso;
	ofSoundPlayer abso1;
	int index;

};

class Ball1 : public Ball
{
public:
	Ball1(ofVec2f _ctr = ofVec2f(),
		float _radius = 5.0f,
		ofColor _color = ofColor::black,
		ofVec2f _vel = ofVec2f(ofRandomf()*5.0f, ofRandom(5.0f, 15.0f)),
		float _decrease = 0.0f);
	virtual void update(float deltaTime) override;
};



class Ball2 : public Ball
{
public:
	Ball2(ofVec2f _ctr = ofVec2f(),
		float _radius = 5.0f,
		ofColor _color = ofColor::black,
		ofVec2f _vel = ofVec2f(ofRandomf()*5.0f, ofRandom(5.0f, 15.0f)),
		float _decrease = 0.0f);
	virtual void update(float deltaTime) override;
};

class Ball3 : public Ball
{
public:
	Ball3(ofVec2f _ctr = ofVec2f(),
		float _radius = 5.0f,
		ofColor _color = ofColor::black,
		ofVec2f _vel = ofVec2f(ofRandomf()*5.0f, ofRandom(5.0f, 15.0f)),
		float _decrease = 0.0f);
	virtual void update(float deltaTime) override;
};

class Ball4 : public Ball
{
public:
	Ball4(Ball other);

};