#include "Ball.h"



Ball::Ball(ofVec2f _ctr,
	float _radius /*= 5.0f*/,
	ofColor _color,
	ofVec2f _vel /*= ofVec2f(ofRandomf()*5.0f, ofRandom(5.0f, 15.0f))*/,
	float _decrease) :
	_Center(_ctr),
	_Radius(_radius),
	_DecreaseSpd(_decrease),
	_Velocity(_vel),
	_Color(_color)
{
	_dragSpd = 5.0f;
	_dragged = false;
	abso.loadSound("absorb.mp3");
	abso1.loadSound("bad.mp3");
	eatFoods = false;

}

void Ball::update(float deltaTime)
{
	_Center += _Velocity * deltaTime;
	_Radius -= deltaTime * _DecreaseSpd;
}

void Ball::limit() {
	if (_Center.x - _Radius<0) {
		_Center.x = _Radius;
		_Velocity.x = 0;
	}
	else if (_Center.x + _Radius>ofGetWidth()) {
		_Center.x = ofGetWidth() - _Radius;
		_Velocity.x = 0;

	}
	else if (_Center.y - _Radius<0) {
		_Center.y = _Radius;
		_Velocity.y = 0;
	}
	else if (_Center.y + _Radius>ofGetHeight()) {
		_Center.y = ofGetHeight() - _Radius;
		_Velocity.y = 0;
	}
}


void Ball::init()
{
	ofRectangle Rect(0.0f, 0.0f, ofGetWidth(), ofGetHeight());
	Rect.scaleFromCenter(1.2f);
	if (!Rect.inside(_Center))
	{
		resetPosVel();
	}
}

void Ball::resetPosVel()
{
	_Center.x = ofRandomWidth();
	_Center.y = -10.0f;
	_Radius = 5.0f;
	_Velocity = ofVec2f(
		ofRandomf()*100.0f,
		ofRandom(100.0f, 250.0f));
}

void Ball::draw(
	bool bFill)
{
	ofPushStyle();

	if (bFill)
	{
		ofFill();
	}
	else
	{
		ofNoFill();
		ofSetLineWidth(4.0f);
	}


	ofSetColor(_Color);
	ofCircle(_Center, _Radius);

	if (_dragged)
	{
		ofSetColor(ofColor::green);
		ofNoFill();
		ofSetLineWidth(1.5f);
		ofCircle(_Center, _Radius + 5.0f);
	}

	ofPopStyle();
}

bool Ball::inside(ofVec2f pos)
{
	ofVec2f Offset = pos - _Center;
	bool bIn = Offset.length() <= _Radius;
	return bIn;
}

bool Ball::contact(Ball another)
{
	ofVec2f Offset = another._Center - _Center;
	bool bContact = Offset.length() <= (_Radius + another._Radius);
	return bContact;
}

void Ball::barrier(Floor fl) {
	if (_Center.x >= fl._X - _Radius&&_Center.x <= fl._X + fl._FL.getWidth()+ _Radius&&
		_Center.y >= fl._Y - _Radius + fl._HY&&_Center.y <= fl._Y + fl._FL.getHeight() + _Radius) {

		_Velocity.x = -_Velocity.x;
		_Velocity.y = -_Velocity.y;
		if (_Center.y<fl._Y + fl._HY&&fl._HY != 0) {
			changeRadius(false);
		}
		
	}
}

void Ball::dragTo(ofVec2f pos)
{
	ofVec2f Offset = pos - _Center;
	_Velocity = Offset * exp(-_Radius / 20.0f) *_dragSpd;
	_dragged = true;
}

void Ball::dragOff()
{
	_dragged = false;
}

//////////////////////////////////////////////////////////////////
void Ball::absorb(Ball &another)
{
	bool bContact = contact(another);
	if (bContact)
	{
		bool increase;
		another.resetPosVel();
		if (another._Color == _Color) {
			increase = true;
			changeRadius(increase);
			abso.play();
		}

		else {
			_Color = another._Color;
			increase = false;
			changeRadius(increase);
			abso1.play();
		}
	}
}


void Ball::absorb1(Ball &another)
{
	bool bContact = contact(another);
	if (bContact)
	{
		bool increase;
		if (another._Color == _Color) {
			increase = true;
			changeRadius(increase);
			abso.play();
		}

		else {
			_Color = another._Color;
			increase = false;
			changeRadius(increase);
			abso1.play();
		}

		eatFoods = true;
	}
}


void Ball::changeRadius(
	bool increase /*= true*/)
{
	float amount = 2.0f;/*20.0f / _Radius;*/
	if (increase)
	{
		_Radius += amount;
	}
	else
	{
		_Radius -= amount;
	}
}

void Ball::changeRadius1() {
	_Radius -= 1.2f;
}

float Ball::getRadius()
{
	return _Radius;
}
ofVec2f Ball::getCenter() {
	return _Center;
}
Ball1::Ball1(ofVec2f _ctr /*= ofVec2f()*/, float _radius /*= 5.0f*/, ofColor _color /*= ofColor::black*/, ofVec2f _vel /*= ofVec2f(ofRandomf()*5.0f, ofRandom(5.0f, 15.0f))*/, float _decrease /*= 0.0f*/) :
	Ball(_ctr, _radius, _color, _vel, _decrease)
{
	index = 0;
}

void Ball1::update(float deltaTime)
{
	if (index <= 0) {
		index = 200;

		float col = ofRandom(1.0f);

		if (col<0.2) {
			_Color = ofColor::black;
		}
		else if (col<0.4) {
			_Color = ofColor::red;
		}
		else if (col<0.6) {
			_Color = ofColor::blue;
		}
		else if (col<0.8) {
			_Color = ofColor::yellow;
		}
		else {
			_Color = ofColor::white;
		}
	}
	index--;
	Ball::update(deltaTime);
}



Ball2::Ball2(ofVec2f _ctr /*= ofVec2f()*/, float _radius /*= 5.0f*/, ofColor _color /*= ofColor::black*/, ofVec2f _vel /*= ofVec2f(ofRandomf()*5.0f, ofRandom(5.0f, 15.0f))*/, float _decrease /*= 0.0f*/) :
	Ball(_ctr, _radius, _color, _vel, _decrease)
{}

void Ball2::update(float deltaTime)
{
	_Velocity.rotate(ofRandomf()*1000.0f*deltaTime);
	Ball::update(deltaTime);
}

Ball3::Ball3(ofVec2f _ctr /*= ofVec2f()*/, float _radius /*= 5.0f*/, ofColor _color /*= ofColor::black*/, ofVec2f _vel /*= ofVec2f(ofRandomf()*5.0f, ofRandom(5.0f, 15.0f))*/, float _decrease /*= 0.0f*/) :
	Ball(_ctr, _radius, _color, _vel, _decrease)
{}

void Ball3::update(float deltaTime)
{
	_DecreaseSpd = -2.0f;
	Ball::update(deltaTime);
}

Ball4::Ball4(Ball other) :
	Ball(ofVec2f(other._Center.x, other._Center.y - other._Radius - 6), 5.0f, other._Color, ofVec2f(0, -150.0f), 0)
{}
