#pragma once

#include "ofMain.h"
class Ball;
class Floor;
class myButton;



class ofDragBall2App : public ofBaseApp {
private:
	ofPtr<Ball> ptrPlayerBall;

	vector<ofPtr<Ball> > Balls;
	vector<ofPtr<Ball> >::iterator iterB;
	vector<ofPtr<Floor> > Floors;
	ofPtr<Floor> floorAuto;

	vector<ofPtr<Ball> > Foods;
	vector<ofPtr<Ball> >::iterator iterF;



	// interaction
	bool _MouseLeftDragging;

	ofVec2f _PrevMousePos;


	// npc;
	bool npcAlive;
	Ball *npc;
	ofVec2f npcCenter;


	// text
	ofTrueTypeFont _Font;

	// player performance
	float _PlayTime;

	ofImage im;
	ofImage back1;
	ofImage btnLevel1;
	ofImage btnLevel2;
	ofImage btnBack;
	ofImage Tips;
	ofImage Name;


	int FLOOR_AMOUNT;
	int BALL_AMOUNT;
	float FLAUTO_TIME;

	ofSoundPlayer sound;
	ofSoundPlayer go;

	ofPtr<myButton> _btn1;
	ofPtr<myButton> _btn2;
	ofPtr<myButton> _btn3;
	bool select;//select是bool值，判断当前是否是选关界面
	bool rePlay;//判断游戏结束界面是否点击了返回按钮
	int level;


public:
	void setup();
	void update();
	void draw();
	void drawElapseTime();
	void drawGameOver();
	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);
	void level1();
	void level2();
	void initData();

};
