#pragma once

#include "ofMain.h"
#include "ofxBox2d.h"
#include "ofxOpenCv.h"


class ofApp : public ofBaseApp {

public:
	void setup();
	void update();
	void draw();

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


	static const int BLOB_NUM = 10;
	ofPtr<ofxBox2dPolygon> edges[BLOB_NUM];
	ofVideoGrabber camera;
	ofxCvColorImage colorImg;
	ofxCvGrayscaleImage grayImage;
	ofxCvGrayscaleImage grayBg;
	ofxCvGrayscaleImage grayDiff;
	ofxCvContourFinder contourFinder;

	ofPolyline edgeLines[BLOB_NUM]; //検出したエッジ（輪郭線）

	int threshold;
	bool bLearnBackground;

	//box2dの空間を作る
	ofxBox2d box2d;
	//物理計算の円
	vector <ofPtr<ofxBox2dCircle> > circles;
	//vector <shared_ptr<ofxBox2dCircle> > circles;//vector配列＝長さが決まってない配列 ofxBox2dCircle circle;元のやつ <shared_ptr<ofxBox2dCircle>>を使うとうまく実行できる
	//vector <shared_ptr<ofxBox2dRect> > boxes;



	ofImage donguri;
	ofImage autumn;

	ofImage risu_right;
	ofImage count;
	ofSoundPlayer mySound;
	ofSoundPlayer piro;
	
	ofTrueTypeFont	verdana14;
};
