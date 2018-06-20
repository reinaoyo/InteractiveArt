#include "ofApp.h"
float risu_x;
float risu_y;
bool risuRight;
bool risuLeft;
int n;

//--------------------------------------------------------------
void ofApp::setup(){
    //imageload
    risu_left.load("img/risu_left-8.png");
    risu_right.load("img/risu_right-8.png");
    autumn.load("img/autum.png");
    donguri.load("img/donguri-8.png");
    count.load("img/count-8.png");
    
    risuRight = true;
    risuLeft= false;

    ofSetBackgroundColor(255,255,255);
    ofSetWindowShape(1024,768);
    
    n=0;
    //box2d
    box2d.init();
    box2d.setGravity(0,5);//重力設定
    box2d.setFPS(60);
    //box2d.registerGrabbing();//掴んで投げれる
    box2d.createBounds();//バウンドする
    
    // donguri
    donguri.setAnchorPercent(0.5, 0.5);
     box2d.createGround(0, 568, 1024, 768);
    //circle.setPhysics(1.0,0.8,0.5);//重さ、反発、摩擦
    //circle.setup(box2d.getWorld(),ofGetWidth()/2,ofGetHeight()/2,50);
    risu_x=0;
    risu_y=480;
   
    mySound.load("sound/v5.mp3");
    piro.load("sound/btn15.mp3");
    mySound.play();
    mySound.setLoop(true);
    
    ofTrueTypeFont::setGlobalDpi(72);
    
    font1.load("font/001Shirokuma-Regular.otf", 30,true,true); // フォントのデータを指定する
    font1.setLineHeight(24);       // 行間を指定する
    font1.setLetterSpacing(1.0);   // 文字間を指定する

}

//--------------------------------------------------------------
void ofApp::update(){
    if(risuRight){
        risu_x++;
    }
    if(risuLeft){
        risu_x--;
    }
    if(risu_x<0){
        risuRight =true;
        risuLeft = false;
    }
    if(risu_x>ofGetWidth()-300){
        risuRight =false;
        risuLeft = true;
    }

    box2d.update();
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    autumn.draw(0,0,ofGetWidth(),ofGetHeight());
    ofSetColor(255,229,153); // 文字色を指定
    font1.drawString(ofToString(n,0)+"こ", 102,748);
    
    ofSetColor(255,255, 255);
    count.draw(250,650);
    for(int i=0;i<circles.size();i++){
        ofPoint pos = circles[i].get()->getPosition();
        
            if(risu_x+300>pos.x&&risu_x<pos.x){
                if(risu_y+170>pos.y&&risu_y<pos.y){
                    //don=false;
                    circles[i]->setup(box2d.getWorld(),10000,1000, 10);
                    piro.play();
                    n++;
                }
            }
        
                donguri.draw(pos);
        
        //circles[i].get()->draw();//<shared_ptr<ofxBox2dCircle>>を追加するとエラーが出る　circles[i].draw();-->その場合circles[i].get()->draw();ポインタになると.ではアクセスできない->になる
 
    }//circles生成

    
    if(risuRight){
        risu_right.draw(risu_x,risu_y);
    }
    if(risuLeft){
        risu_left.draw(risu_x,risu_y);
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
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
   float r = ofRandom(10,30);
    //ポインタ型で新しい円を作成
    shared_ptr<ofxBox2dCircle> circle =shared_ptr<ofxBox2dCircle>(new ofxBox2dCircle);//shared_ptr<ofxBox2dCircle>はint 的なもの
    //ポインタになると.ではなく->でメンバにアクセス
   circle->setPhysics(1.0, 0.8, 0.5);
    circle->setup(box2d.getWorld(), mouseX, mouseY, r);
    
    circles.push_back(circle);
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
