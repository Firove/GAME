#include "ofDragBall2App.h"
#include "Ball.h"
#include "Floor.h"
#include "myButton.h"
using namespace std;

//--------------------------------------------------------------
void ofDragBall2App::setup() {
	//Ball ball =Ball();//这种方式声明局部变量
	FLAUTO_TIME = 3.0f;//自动扶梯出现的时间
	select = true;
	rePlay = false;
	ofSetVerticalSync(true);
	im.loadImage("back.png");
	back1.loadImage("back1.png");
	btnLevel1.loadImage("btnlevel1.png");
	btnLevel2.loadImage("btnlevel2.png");
	btnBack.loadImage("btnback.png");
	Tips.loadImage("Tips.png");
	Name.loadImage("1.png");
	sound.loadSound("Always With Me.mp3");
	go.loadSound("start.mp3");
	sound.setLoop(true);
	sound.play();
	_btn1.reset(new myButton(50, 340, btnLevel1));
	_btn2.reset(new myButton(ofGetWidth() - 250, 335, btnLevel2));
	_btn3.reset(new myButton(200, 300, btnBack));
	_MouseLeftDragging = false;
	_PlayTime = 0.0f;

	_Font.loadFont("vag.ttf", 24);




	/*
	enemyCenter=ofVec2f(ofGetWidth()/2,-50);
	enemy.reset(new Ball(enemyCenter,50,enemyColor,enemyVec,0));
	float col=ofRandom(1.0f);
	if(col<0.2){
	enemyColor=ofColor::black;
	}else if(col<0.4){
	enemyColor=ofColor::red;
	}else if(col<0.6){
	enemyColor=ofColor::blue;
	}else if(col<0.8){
	enemyColor=ofColor::yellow;
	}else{
	enemyColor=ofColor::white;
	}

	enemy.reset(new Ball(enemyCenter,50,enemyColor,enemyVec,0));
	*/
}

//--------------------------------------------------------------
void ofDragBall2App::update() {

	ofSoundUpdate();

	if (!select) {
		if (_PlayTime >= FLAUTO_TIME) {
			floorAuto->onframe();
			floorAuto->resetPos();
			ptrPlayerBall->barrier(*floorAuto);
		}

		float deltaTime = ofGetLastFrameTime();
		//如果npc存在，主角躲进去屏幕上的敌人就全部重置，如果半径减为零，就删除npc的内存空间
		if (npcAlive) {

			npc->update(deltaTime);

			float m = npc->getRadius();

			if (ptrPlayerBall->contact(*npc)) {
				for (int i = 0;i<Balls.size();i++)
				{
					Balls[i]->resetPosVel();
				}
			}

			if (m <= 0.0f) {
				delete npc;
				npcAlive = false;
			}

		}






		ofRectangle Rect(0.0f, 0.0f, ofGetWidth(), ofGetHeight());
		Rect.scaleFromCenter(1.2f);



		ptrPlayerBall->limit();

		float playerBallRadius = ptrPlayerBall->getRadius();
		if (playerBallRadius >= 0.0f)
		{
			for (int i = 0;i<Floors.size();i++) {
				ptrPlayerBall->barrier(*Floors[i]);
			}

			ptrPlayerBall->update(deltaTime);

			for (int i = 0;i<Balls.size();i++) {
				Balls[i]->update(deltaTime);
				ptrPlayerBall->absorb(*Balls[i]);

				Balls[i]->init();
			}


			if (_MouseLeftDragging)
			{
				ptrPlayerBall->dragTo(_PrevMousePos);

			}

			//Foods.begin()是Foods的第一个元素，那如果有且仅有的一个元素被erase()掉了，那iterF=Foods.begin()还对吗？
			for (iterF = Foods.begin();iterF != Foods.end();iterF++) {
				bool k = false;//该值让玩家在吃了敌人以后跳出外层循环
				ptrPlayerBall->eatFoods = false;

				ofVec2f center;
				center = (*iterF)->getCenter();

				ptrPlayerBall->absorb1(*(*iterF));
				if (ptrPlayerBall->eatFoods) {
					Foods.erase(iterF);
					break;
				}

				if (!Rect.inside(center)) {
					Foods.erase(iterF);
					iterF = Foods.begin();
					break;
				}

				(*iterF)->update(deltaTime);
				for (int j = 0;j<Balls.size();j++) {
					bool m = (*iterF)->contact(*Balls[j]);
					if (m) {
						Balls[j]->resetPosVel();
						Foods.erase(iterF);
						iterF = Foods.begin();
						k = true;
						break;

					}
				}
				//如果有且仅有一颗子弹并且打中了敌人，子弹会被iterF=Foods.begin();，如果此时不跳出循环，会执行iterF++，此时会出错
				if (k) {
					break;
				}

			}

			_PlayTime += deltaTime;
		}
	}
}


//--------------------------------------------------------------
void ofDragBall2App::draw() {
	im.draw(0, 0, ofGetWidth(), ofGetHeight());

	if (select) {
		back1.draw((ofGetWidth() - back1.getWidth()) / 2, 50);
		Tips.draw((ofGetWidth() - Tips.getWidth()) / 2, (ofGetHeight() - Tips.getHeight()) / 2 + 40);
		_btn1->draw();
		_btn2->draw();
		Name.draw(10, 10);
	}
	if (!select) {

		if (npcAlive) {
			npc->draw(false);
		}



		for (int i = 0;i<Floors.size();i++) {
			Floors[i]->draw();
		}
		if (_PlayTime >= FLAUTO_TIME) {
			floorAuto->draw();
		}


		if (ptrPlayerBall->getRadius() >= 0.0f)
		{
			ptrPlayerBall->draw();
			for (int i = 0;i<Balls.size();i++)
			{
				Balls[i]->draw();
			}

			for (int i = 0;i<Foods.size();i++) {
				Foods[i]->draw();
			}
		}
		else
		{
			drawGameOver();
		}

		drawElapseTime();
	}

}

void ofDragBall2App::drawElapseTime()
{
	ofPushStyle();
	ofSetColor(ofColor::black);
	_Font.drawString(ofToString(_PlayTime), 10.0f, 30.0f);
	ofPopStyle();
}

//--------------------------------------------------------------
void ofDragBall2App::keyPressed(int key) {
	if (!select) {
		if (key == '1') {
			ofPtr<Ball> food;
			food.reset(new Ball4(*ptrPlayerBall));
			Foods.push_back(food);
			ptrPlayerBall->changeRadius1();

		}
	}


}

//--------------------------------------------------------------
void ofDragBall2App::keyReleased(int key) {

}

//--------------------------------------------------------------
void ofDragBall2App::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofDragBall2App::mouseDragged(int x, int y, int button) {
	if (!select) {
		_PrevMousePos = ofVec2f(x, y);
	}
}

//--------------------------------------------------------------
void ofDragBall2App::mousePressed(int x, int y, int button) {
	if (select) {
		if (_btn1->init(x, y)) {
			select = false;
			//_btn1.reset(new myButton(0,-100));
			level = 1;
			level1();
		}

		if (_btn2->init(x, y)) {
			select = false;
			level = 2;
			level2();
		}

	}

	if (rePlay) {
		if (_btn3->init(x, y)) {
			Floors.clear();
			Balls.clear();
			Foods.clear();
			select = true;
			rePlay = false;
			sound.play();
		}
	}
	if (!select) {

		if (button == 0) {
			_MouseLeftDragging = true;
			_PrevMousePos = ofVec2f(x, y);
		}
	}

}


void ofDragBall2App::level1() {
	go.play();
	FLOOR_AMOUNT = 3;
	BALL_AMOUNT = 15;
	initData();
	floorAuto.reset(new Floor());
}


void ofDragBall2App::level2() {
	go.play();
	FLOOR_AMOUNT = 5;
	BALL_AMOUNT = 23;
	initData();
	floorAuto.reset(new Floor1());
}


void ofDragBall2App::initData() {

	npcAlive = true;

	npcCenter = ofVec2f(ofGetWidth() / 2, 240);

	npc = new Ball(npcCenter, 50, ofColor::green, ofVec2f(0, 0), 1.5f);

	ptrPlayerBall.reset(new Ball(ofVec2f(ofGetWidth() / 2.0f, ofGetHeight() * 0.8f), 30.0f,
		ofColor::black,
		ofVec2f(0.0f, 0.0f),
		1.0f));
	floorAuto.reset(new Floor1());

	for (int i = 0; i < FLOOR_AMOUNT; i++)
	{
		ofPtr<Floor> pFloor;
		if (i<2) {

			pFloor.reset(new Floor());

		}
		else
		{
			pFloor.reset(new Floor1());
		}

		Floors.push_back(pFloor);

	}

	ofColor cr;

	for (int i = 0; i < BALL_AMOUNT; i++)
	{
		ofPtr<Ball> pBall;
		if (ofRandom(1.0f)>0.8f) {
			cr = ofColor::black;
		}

		else if (ofRandom(1.0f)>0.6f) {
			cr = ofColor::red;
		}
		else if (ofRandom(1.0f)>0.4f) {
			cr = ofColor::blue;
		}
		else if (ofRandom(1.0f)>0.2f) {
			cr = ofColor::yellow;
		}
		else {
			cr = ofColor::white;
		}
		/*ofColor cr = i<2 ? ofColor::black : ofColor::white;*/
		if (ofRandom(1.0f)>0.8f)
		{
			pBall.reset(new Ball1(ofVec2f(ofRandomWidth(), -10.0f), 5.0f));
		}
		else if (ofRandom(1.0f)>0.6f) {
			pBall.reset(new Ball2(ofVec2f(ofRandomWidth(), -10.0f), 5.0f, cr));
		}
		else if (ofRandom(1.0f)>0.4f) {
			pBall.reset(new Ball3(ofVec2f(ofRandomWidth(), -10.0f), 5.0f, cr));
		}
		else
		{
			pBall.reset(new Ball(ofVec2f(ofRandomWidth(), -10.0f), 5.0f, cr));
		}

		pBall->resetPosVel();
		Balls.push_back(pBall);
	}
}



//--------------------------------------------------------------
void ofDragBall2App::mouseReleased(int x, int y, int button) {
	if (!select) {
		if (button == 0)
		{
			_MouseLeftDragging = false;
			ptrPlayerBall->dragOff();
		}

	}

}

//--------------------------------------------------------------
void ofDragBall2App::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void ofDragBall2App::mouseExited(int x, int y) {

}

//--------------------------------------------------------------
void ofDragBall2App::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofDragBall2App::gotMessage(ofMessage msg) {

}


void ofDragBall2App::drawGameOver()
{
	ofPushStyle();
	ofSetColor(ofColor::white);
	string GameOverString = "Game Over";
	float txtWidth = _Font.stringWidth(GameOverString);
	_Font.drawString(GameOverString, ofGetWidth() / 2.0f - txtWidth / 2.0f, ofGetHeight() / 2.0f);
	ofPopStyle();
	ofSoundStopAll();
	rePlay = true;

	_btn3->draw();
	_PlayTime = 0;

}

//--------------------------------------------------------------
void ofDragBall2App::dragEvent(ofDragInfo dragInfo) {

}
