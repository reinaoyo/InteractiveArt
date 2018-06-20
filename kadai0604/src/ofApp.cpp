#include "ofApp.h"

using namespace ofxCv;
using namespace FACETRACKER;

void ofApp::setup() {
    ofBackground(255,252,226);
    ofSetWindowShape(INPUT_MOVIE_WSIZE, INPUT_MOVIE_HSIZE);
        ofEnableAlphaBlending();
    ofSetVerticalSync(true);
    ofSetDrawBitmapMode(OF_BITMAPMODE_MODEL_BILLBOARD);
    cam.initGrabber(INPUT_MOVIE_WSIZE, INPUT_MOVIE_HSIZE);
    tracker.setup();
    ofSetFrameRate(60);//フレームレートの設定
    
   ofSetBackgroundAuto(true);
    nose.load("image/nose-8.png");
    noseMat = toCv(nose);
    cheekleft.load("image/cheek-8.png");
    cheekleftMat = toCv(cheekleft);
    cheekright.load("image/cheek-8.png");
    cheekrightMat = toCv(cheekright);


    heart1.load("image/heart1-8.png");
    heart2.load("image/heart2-8.png");
    happy.load("image/happy-8.png");
    love.load("image/love-8.png");
    cute.load("image/cute-8.png");
    star.load("image/star-8.png");
    
    heart1_x =10;
    heart1_y= ofGetHeight()/10;
    heart2_x = 10;
    heart2_y= ofGetHeight()/2;
    happy_x = 10;
    happy_y = 4*(ofGetHeight()/5);
    check=1;
    heart1_scale = 0;
    heart2_scale =0;
    happy_scale=0;
    
    love_x =ofGetWidth();
    love_y= ofGetHeight()/10;
    cute_x = ofGetWidth();
    cute_y= ofGetHeight()/2;
    star_x = ofGetWidth();
    star_y = 4*(ofGetHeight()/5);
    love_scale = 0;
    cute_scale =0;
    star_scale=0;
    

}

void ofApp::exit() {
    tracker.waitForThread();
}

void ofApp::update() {
    cam.update();
    
    if(cam.isFrameNew()) {
        tracker.update(toCv(cam));
        position = tracker.getPosition();
        scale = tracker.getScale();
        orientation = tracker.getOrientation();
        rotationMatrix = tracker.getRotationMatrix();
    }

}

void ofApp::draw() {
    ofSetHexColor(0xffffff);
    cam.draw(0, 0);
    
    ofDrawBitmapString(ofToString((int) ofGetFrameRate()), 10, 20);
    
    if(tracker.getFound()) {
        ofSetLineWidth(1);
  
        nose.setFromPixels(noseMat.data, noseMat.cols,noseMat.rows, OF_IMAGE_COLOR_ALPHA);
        cheekright.setFromPixels(cheekrightMat.data, cheekrightMat.cols,cheekrightMat.rows, OF_IMAGE_COLOR_ALPHA);
        cheekleft.setFromPixels(cheekleftMat.data, cheekleftMat.cols,cheekleftMat.rows, OF_IMAGE_COLOR_ALPHA);
    
        //リングパーツと顔パーツの描画位置を決定
        int noseCenterX = (int)tracker.getImagePoint(30).x - nose.getWidth()/2;
        int noseCenterY = (int)tracker.getImagePoint(30).y - nose.getHeight()/2;
        int cheekrightCenterX = (int)tracker.getImagePoint(3).x - cheekright.getWidth()/2;
        int cheekrightCenterY = (int)tracker.getImagePoint(29).y - cheekright.getHeight()/2;
        int cheekleftCenterX = (int)tracker.getImagePoint(14).x - cheekleft.getWidth()/2;
        int cheekleftCenterY = (int)tracker.getImagePoint(29).y - cheekleft.getHeight()/2;
 
        cheekleft.draw(cheekleftCenterX,cheekleftCenterY);
        cheekright.draw(cheekrightCenterX,cheekrightCenterY);
        nose.draw(noseCenterX,noseCenterY);
    }
    ofSetColor(255,252,226);
    ofDrawRectangle(0, 0, ofGetWidth()/8, ofGetHeight());
    ofDrawRectangle(7*ofGetWidth()/8, 0, ofGetWidth()/8, ofGetHeight());
    ofSetColor(255,255,255);
    heart1.draw(heart1_x,heart1_y,heart1.getWidth()+heart1_scale,heart1.getHeight()+heart1_scale);
    heart2.draw(heart2_x,heart2_y,heart2.getWidth()+heart2_scale,heart2.getHeight()+heart2_scale);
    happy.draw(happy_x,happy_y,150+happy_scale,100+happy_scale);
    love.draw(love_x,love_y,150+love_scale,100+love_scale);
    cute.draw(cute_x,cute_y,150+cute_scale,100+cute_scale);
    star.draw(star_x,star_y,150+star_scale,100+star_scale);
}

void ofApp::keyPressed(int key) {
    if(key == 'r') {
        tracker.reset();
    }
    if(key == 'c') {
        heart1_x =10;
        heart1_y= ofGetHeight()/10;
        heart2_x = 10;
        heart2_y= ofGetHeight()/2;
        happy_x = 10;
        happy_y = 4*(ofGetHeight()/5);
        heart1_scale = 0;
        heart2_scale =0;
        happy_scale=0;
        love_x =ofGetWidth()/10*9;
        love_y= ofGetHeight()/10;
        cute_x =ofGetWidth()/10*9;
        cute_y= ofGetHeight()/2;
        star_x = ofGetWidth()/10*9;
        star_y = 4*(ofGetHeight()/5);
        love_scale = 0;
        cute_scale = 0;
        star_scale= 0;
    }
  
    if(check == 1){
            if(key == OF_KEY_DOWN) {
                heart1_scale=heart1_scale-10;
            }
            if(key == OF_KEY_UP){
                heart1_scale=heart1_scale+10;
            }
    }
    if(check==2){
        if(key == OF_KEY_DOWN) {
            heart2_scale=heart2_scale-10;
        }
        if(key == OF_KEY_UP){
            heart2_scale=heart2_scale+10;
        }
    }
    if(check==3){
        if(key == OF_KEY_DOWN) {
            happy_scale=happy_scale-10;
        }
        if(key == OF_KEY_UP){
            happy_scale=happy_scale+10;
        }
    }
    if(check == 4){
        if(key == OF_KEY_DOWN) {
            love_scale=love_scale-10;
        }
        if(key == OF_KEY_UP){
            love_scale=love_scale+10;
        }
    }
    if(check == 5){
        if(key == OF_KEY_DOWN) {
            cute_scale=cute_scale-10;
        }
        if(key == OF_KEY_UP){
            cute_scale=cute_scale+10;
        }
    }
    if(check == 6){
        if(key == OF_KEY_DOWN) {
            star_scale=star_scale-10;
        }
        if(key == OF_KEY_UP){
            star_scale=star_scale+10;
        }
    }
}

void ofApp::keyReleased(int key){
    if(key == '1') {
        check=1;
    }
    if(key == '2') {
        check=2;
    }
    if(key == '3') {
        check=3;
    }
    if(key == '4') {
        check=4;
    }
    if(key == '5') {
        check=5;
    }
    if(key == '6') {
        check=6;
    }
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    if(mouseX>heart1_x-heart1.getWidth() && mouseX<heart1_x+heart1.getWidth()){
        if(mouseY>heart1_y-heart1.getHeight() && mouseY<heart1_y+heart1.getHeight()){

            heart1_x= mouseX;
            heart1_y= mouseY;
        }
    }
    if(mouseX>heart2_x-heart2.getWidth() && mouseX<heart2_x+heart2.getWidth()){
        if(mouseY>heart2_y-heart2.getHeight() && mouseY<heart2_y+heart2.getHeight()){
            heart2_x= mouseX;
            heart2_y= mouseY;
        }
    }
    if(mouseX>happy_x-happy.getWidth() && mouseX<happy_x+happy.getWidth()){
        if(mouseY>happy_y-happy.getHeight() && mouseY<happy_y+happy.getHeight()){
            happy_x= mouseX;
            happy_y= mouseY;
        }
    }
    if(mouseX>love_x-love.getWidth() && mouseX<love_x+love.getWidth()){
        if(mouseY>love_y-love.getHeight() && mouseY<love_y+love.getHeight()){
            love_x= mouseX;
            love_y= mouseY;
        }
    }
    if(mouseX>cute_x-cute.getWidth() && mouseX<cute_x+cute.getWidth()){
        if(mouseY>cute_y-cute.getHeight() && mouseY<cute_y+cute.getHeight()){
            cute_x= mouseX;
            cute_y= mouseY;
        }
    } if(mouseX>star_x-star.getWidth() && mouseX<star_x+star.getWidth()){
        if(mouseY>star_y-star.getHeight() && mouseY<star_y+star.getHeight()){
            star_x= mouseX;
            star_y= mouseY;
        }
    }


  
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    if(mouseX>heart1_x-heart1.getWidth() && mouseX<heart1_x+heart1.getWidth()){
        if(mouseY>heart1_y-heart1.getHeight() && mouseY<heart1_y+heart1.getHeight()){
            check=0;
        }
    }
    if(mouseX>heart2_x-heart2.getWidth() && mouseX<heart2_x+heart2.getWidth()){
        if(mouseY>heart2_y-heart2.getHeight() && mouseY<heart2_y+heart2.getHeight()){
            check=0;
        }
    }
    if(mouseX>happy_x-happy.getWidth() && mouseX<happy_x+happy.getWidth()){
        if(mouseY>happy_y-happy.getHeight() && mouseY<happy_y+happy.getHeight()){
            check=0;
        }
    }
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
    
}

