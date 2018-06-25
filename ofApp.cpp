#include "ofApp.h"
float risu_x;
float risu_y;
int n;

//--------------------------------------------------------------
void ofApp::setup() {

	risu_right.load("img/risu_right-8.png");
	autumn.load("img/autum.png");
	donguri.load("img/donguri-8.png");
	count.load("img/count-8.png");


	ofSetFrameRate(60);
	camera.setVerbose(true);
	ofSetBackgroundColor(255, 255, 255);

	ofSetWindowShape(1024, 768);
	n = 0;

	//box2d
	box2d.init();
	box2d.setGravity(0, 10);//重力設定
	box2d.setFPS(60);
	//box2d.registerGrabbing();//掴んで投げれる
	box2d.createBounds();//バウンドする


						 // donguri
	donguri.setAnchorPercent(0.5, 0.5);
	box2d.createGround(0, 568, 1024, 768);
	//circle.setPhysics(1.0,0.8,0.5);//重さ、反発、摩擦
	//circle.setup(box2d.getWorld(),ofGetWidth()/2,ofGetHeight()/2,50);


	risu_x = 0;
	risu_y =480;

	mySound.load("sound/v5.mp3");
	piro.load("sound/btn15.mp3");
	mySound.play();
	mySound.setLoop(true);

	ofTrueTypeFont::setGlobalDpi(72);

	verdana14.load("font/verdana.ttf", 40, true, true);
	verdana14.setLineHeight(18.0f);
	verdana14.setLetterSpacing(1.037);

	//camera.initGrabber(320, 240);
	camera.initGrabber(ofGetWidth(), ofGetHeight());
	colorImg.allocate(ofGetWidth(), ofGetHeight());
	grayImage.allocate(ofGetWidth(), ofGetHeight());
	grayBg.allocate(ofGetWidth(), ofGetHeight());
	grayDiff.allocate(ofGetWidth(), ofGetHeight());
	//colorImg.allocate(320, 240);
	//grayImage.allocate(320, 240);
	//grayBg.allocate(320, 240);
	//grayDiff.allocate(320, 240);
	bLearnBackground = true;
	threshold = 80;
	for (int cnt = 0; cnt < BLOB_NUM; cnt++) {
		edges[cnt] = ofPtr<ofxBox2dPolygon>(new ofxBox2dPolygon);
	}
}

//--------------------------------------------------------------
void ofApp::update() {
	bool bNewFrame = false;

	camera.update();
	bNewFrame = camera.isFrameNew();

	if (bNewFrame) {

		colorImg.setFromPixels(camera.getPixels());
		colorImg.mirror(false, true);
		colorImg.blur();
		grayImage = colorImg;
		if (bLearnBackground == true) {
			grayBg = grayImage;		// the = sign copys the pixels from grayImage into grayBg (operator overloading)
			bLearnBackground = false;
		}

		// take the abs value of the difference between background and incoming and then threshold:
		grayDiff.absDiff(grayBg, grayImage);
		grayDiff.threshold(threshold);

		// find contours which are between the size of 20 pixels and 1/3 the w*h pixels.
		// also, find holes is set to true so we will get interior contours as well....
		contourFinder.findContours(grayDiff, 20, (ofGetWidth()*ofGetHeight()) / 4, 10, true);	// find holes

		int num = contourFinder.nBlobs;
		for (int cnt = 0; cnt < BLOB_NUM; cnt++) {
			edgeLines[cnt].clear();
			edges[cnt].get()->clear();

			// ループで落ちないように
			if (cnt < num) {

				// 検出した物体にアクセス
				for (int cnt2 = 0; cnt2<contourFinder.blobs[cnt].pts.size(); cnt2++) {
					// エッジ 輪郭線を引く
					edgeLines[cnt].addVertex(contourFinder.blobs[cnt].pts[cnt2]);
				}
				// エッジを閉じる
				edgeLines[cnt].close();
				// エッジの簡易化
				edgeLines[cnt].simplify();

				//box2dの線（ポリゴン）に変換
				edges[cnt].get()->addVertexes(edgeLines[cnt]);
				//box2dの世界に放り込む
				edges[cnt].get()->create(box2d.getWorld());
			}

		}

	}

	box2d.update();
}

//--------------------------------------------------------------
void ofApp::draw() {
	// draw the incoming, the grayscale, the bg and the thresholded difference
	ofSetHexColor(0xffffff);

	autumn.draw(0, 0, ofGetWidth(), ofGetHeight());


	//colorImg.draw(20, 20);
	//grayImage.draw(360, 20);
	//grayBg.draw(20, 280);
	//grayDiff.draw(360, 280);


	// then draw the contours:

	//ofFill();
	//ofSetHexColor(0x333333);
	//ofDrawRectangle(360, 540, 320, 240);
	ofSetHexColor(0xffffff);
	ofSetColor(255, 255, 0);
	ofSetLineWidth(3);
	for (int cnt = 0; cnt < BLOB_NUM; cnt++) {
		edgeLines[cnt].draw();
	}


	ofSetColor(255, 229, 153); // 文字色を指定
	verdana14.drawString(ofToString(n, 0) , 102, 748);

	ofSetColor(255, 255, 255);
	//count.draw(250, 650);
	for (int i = 0; i<circles.size(); i++) {
		ofPoint pos = circles[i].get()->getPosition();

		if (risu_x + 300 > pos.x&&risu_x< pos.x) {
			if (risu_y + 170>pos.y&&risu_y<pos.y) {
				circles[i]->setup(box2d.getWorld(), 10000, 1000, 10);
				piro.play();
				n++;
			}
		}

		donguri.draw(pos);

		//circles[i].get()->draw();//<shared_ptr<ofxBox2dCircle>>を追加するとエラーが出る　circles[i].draw();-->その場合circles[i].get()->draw();ポインタになると.ではアクセスできない->になる

	}//circles生成

	risu_right.draw(risu_x, risu_y);
	ofSetColor(50, 50);



	// draw the ground
	box2d.drawGround();


}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	switch (key) {
	case ' ':
		bLearnBackground = true;
		break;
	case '+':
		threshold++;
		if (threshold > 255) threshold = 255;
		break;
	case '-':
		threshold--;
		if (threshold < 0) threshold = 0;
		break;
	}



	if (key == 't') ofToggleFullscreen();
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {


}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
	if (mouseX>200) {
		float r = ofRandom(10, 30);
		//ポインタ型で新しい円を作成
		shared_ptr<ofxBox2dCircle> circle = shared_ptr<ofxBox2dCircle>(new ofxBox2dCircle);//shared_ptr<ofxBox2dCircle>はint 的なもの
																						   //ポインタになると.ではなく->でメンバにアクセス
		circle->setPhysics(1.0, 0.8, 0.5);
		circle->setup(box2d.getWorld(), mouseX, mouseY, r);
		circle->setVelocity(0, 15);
		circles.push_back(circle);
	}
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}
