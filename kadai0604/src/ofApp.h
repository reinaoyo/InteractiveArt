#pragma once

#include "ofMain.h"
#include "ofxCv.h"
using namespace ofxCv;
using namespace cv;

#include "ofxFaceTrackerThreaded.h"

#define INPUT_MOVIE_WSIZE   640
#define INPUT_MOVIE_HSIZE   480


class ofApp : public ofBaseApp {
public:
    void setup();
    void exit();
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
    ofVideoGrabber cam;
    ofxFaceTrackerThreaded tracker;
    ofVec2f position;
    float scale;
    ofVec3f orientation;
    ofMatrix4x4 rotationMatrix;
    
    Mat translation, rotation;
    ofImage nose,cheekleft,cheekright,heart1,heart2,happy,love,cute,star;
    cv::Mat noseMat,cheekleftMat,cheekrightMat;
    ofMatrix4x4 pose;
    
    bool isFirstRead = true;
    
    ofEasyCam easyCam;
    
 
    
    float heart1_x;
    float heart1_y;
    float heart2_x;
    float heart2_y;
    float happy_x;
    float happy_y;
    float love_x;
    float love_y;
    float cute_x;
    float cute_y;
    float star_x;
    float star_y;
    int check;
    float heart1_scale;
    float heart2_scale;
    float happy_scale;
    float love_scale;
    float cute_scale;
    float star_scale;

};

