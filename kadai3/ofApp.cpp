#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    width = 320;
    height = 240;
    
    vidGrabber.listDevices();
    vidGrabber.setDeviceID(1);
    
    vidGrabber.setVerbose(true);
    vidGrabber.setup(width, height);
    
    colorImg.allocate(width, height);
    grayImage.allocate(width, height);
    grayBg.allocate(width, height);
    grayDiff.allocate(width, height);
    
    bLearnBakground = true;
    threshold = 30;
}

//--------------------------------------------------------------
void ofApp::update(){
    
    vidGrabber.update();
    
    if (vidGrabber.isFrameNew()){

        colorImg.setFromPixels(vidGrabber.getPixels());
        
        grayImage = colorImg;
        if (bLearnBakground == true){
            grayBg = grayImage;
            bLearnBakground = false;
        }
        grayDiff.absDiff(grayBg, grayImage);
        grayDiff.threshold(threshold);
        
        contourFinder.findContours(
            grayDiff,    // ofxCvGrayscaleImage&  input,
            20,          // int minArea,
            (320*240)/3, // int maxArea,
            2,          // int nConsidered,
            false        // bool bFindHoles
        );
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    colorImg.draw(10, 10);
    grayImage.draw(width+20, 10);
    grayBg.draw(10, height+20);
    grayDiff.draw(width+20, height+20);
    ofDrawBitmapString(threshold, width+20 + 10, height+20 + 20);
    
    colorImg.draw(10, height*2+30);
    contourFinder.draw(10, height*2+30);
    
    //cout << contourFinder.nBlobs << endl;
    
    for(int i=0; i<contourFinder.nBlobs; i++){
        ofVec2f center = ofVec2f(contourFinder.blobs[i].centroid.x,
                                 contourFinder.blobs[i].centroid.y);
        ofDrawBitmapString(i,
                           center.x + 10,
                           center.y + height*2+30);
//        cout <<
//        (int)colorImg.getPixels()[(center.y * width + center.x)*3] << ", " <<
//        (int)colorImg.getPixels()[(center.y * width + center.x)*3 + 1] << ", " <<
//        (int)colorImg.getPixels()[(center.y * width + center.x)*3 + 2] << endl;
        
        int r = 0;
        int g = 0;
        int b = 0;
        for(int j=0; j<contourFinder.blobs[i].nPts; j++){
            ofVec2f point = ofVec2f(contourFinder.blobs[i].pts[j].x,
                                     contourFinder.blobs[i].pts[j].y);
//            ofDrawBitmapString(j,
//                               point.x + 10,
//                               point.y + height*2+30);
            
            r += colorImg.getPixels()[(point.y * width + point.x)*3];
            g += colorImg.getPixels()[(point.y * width + point.x)*3 + 1];
            b += colorImg.getPixels()[(point.y * width + point.x)*3 + 2];
        }
        r /= contourFinder.blobs[i].nPts;
        g /= contourFinder.blobs[i].nPts;
        b /= contourFinder.blobs[i].nPts;
        
        cout << i << ": " << r << ", " << g << ", " << b << endl;
        
        if ( r < 130 && g > 140 && b > 140){
            ofDrawBitmapString("File",
                               center.x + 20,
                               center.y + height*2+30);
            
            ofDrawCircle(center.x, center.y, 20);
        }
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch (key){
        case ' ':
            bLearnBakground = true;
            break;
        case OF_KEY_UP:
            threshold ++;
            if (threshold > 255) threshold = 255;
            break;
        case OF_KEY_DOWN:
            threshold --;
            if (threshold < 0) threshold = 0;
            break;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

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

//for (int i = 0; i < contourFinder.nBlobs; i++){
//    contourFinder.blobs[i].draw(10, height*2+30);
//
//    ofVec2f center = ofVec2f(contourFinder.blobs[i].boundingRect.getCenter().x,
//                             contourFinder.blobs[i].boundingRect.getCenter().y);
//    ofDrawBitmapString(i, 10 + center.x, height*2+30 + center.y);
//
//    float r = 0;
//    float g = 0;
//    float b = 0;
//    for(int j=0; j<contourFinder.blobs[i].nPts; j++){
//        ofVec2f point = ofVec2f(contourFinder.blobs[i].pts[j].x,
//                                contourFinder.blobs[i].pts[j].y);
//        r += colorImg.getPixels()[(width * point.y + point.x)*3];
//        g += colorImg.getPixels()[(width * point.y + point.x)*3 + 1];
//        b += colorImg.getPixels()[(width * point.y + point.x)*3 + 2];
//    }
//    r /= contourFinder.blobs[i].nPts;
//    g /= contourFinder.blobs[i].nPts;
//    b /= contourFinder.blobs[i].nPts;
//
//    cout << r << ", " << g << ", " << b << endl;
//    }
