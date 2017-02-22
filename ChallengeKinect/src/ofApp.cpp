#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
//    ofBackground(255,0,0);
    
    video.load("challengeResized_v2.mov");
    video.play();
    
    kinect.setRegistration(true);
    kinect.init();
    kinect.open();
    
    colorImg.allocate(kinect.width, kinect.height);
    grayImage.allocate(kinect.width, kinect.height);
    
    //determines how far or near the kinect can see
    nearThreshold = 230;
    farThreshold = 70;
    
    step = 2;
    far = -1000;
    near = 2000;
    
    size=1600;
    translateX = 850;
    translateY = 350;
    
    angle= 0;
    kinect.setCameraTiltAngle(angle);
}

//--------------------------------------------------------------
void ofApp::update(){
    video.update();
    kinect.update();
    
    
    if(kinect.isFrameNew()) {
        
        mesh.clear();
        
        int width = kinect.width/step;
        int height = kinect.height/step;
        
        for(int y=0; y<height; y++){
            for(int x=0; x<width; x++){
                ofColor color = kinect.getColorAt(x*step, y*step);
                ofVec3f vertex = kinect.getWorldCoordinateAt(x * step, y * step);
                
                if(vertex.z == 0){
                    color.a = 0;
                }
                
                vertex.z = vertex.z * -1;
                vertex.z = vertex.z + size;
                
                if(vertex.z < far|| vertex.z > near){
                    color.a = 0;
                }
                
                mesh.addVertex(vertex);
                mesh.addColor(color);
            }
        }
        
        for(int y=0; y<height-1; y++){
            for(int x=0; x<width-1; x++){
                
                mesh.addIndex(x+y*width);
                mesh.addIndex((x+1)+y*width);
                mesh.addIndex(x+(y+1)*width);
                
                mesh.addIndex((x+1)+y*width);
                mesh.addIndex((x+1)+(y+1)*width);
                mesh.addIndex(x+(y+1)*width);
                
            }
        }
        
        
    }

    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    video.draw(0,0);
    
//    ofSetColor(0);
//    ofDrawEllipse(ofGetWidth()/2, ofGetHeight()/2, 10, 10);
    
//    kinect.draw(0, 0, kinect.width, kinect.height);
    
    ofPushMatrix();
        ofEnableDepthTest();
    
        ofTranslate(translateX, translateY);
    ofScale(-1, 1, 1);
    
    vector<ofMeshFace> faces = mesh.getUniqueFaces();
    for(int i=0; i<faces.size();i++){
        ofVec3f v1 = faces[i].getVertex(0);
        ofVec3f v2 = faces[i].getVertex(1);
        ofVec3f v3 = faces[i].getVertex(2);
        
        ofFloatColor c1 = faces[i].getColor(0);
        ofFloatColor c2 = faces[i].getColor(1);
        ofFloatColor c3 = faces[i].getColor(2);
        
        if(c1.a > 0 && c2.a >0 && c3.a > 0){
            ofSetColor(255);
            int width = 5;
            int height = 5;
            
//            ofDrawTriangle(v1, v2, v3);
            ofDrawEllipse(v1, width, height);
            ofDrawEllipse(v2, width, height);
            ofDrawEllipse(v3, width, height);
        }
    }
    
    ofDisableDepthTest();
    ofPopMatrix();
    
}

void ofApp::exit(){
    kinect.setCameraTiltAngle(0);
    kinect.close();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch (key) {
            
        case OF_KEY_UP:
            angle++;
            
            if(angle>30){
                angle = 30;
            }
            
            kinect.setCameraTiltAngle(angle);

            break;
            
        case OF_KEY_DOWN:
            angle--;
            
            if (angle < -30){
                angle = -30;
            }
            
            kinect.setCameraTiltAngle(angle);
            
            break;
            
    }
    
    if(key == 'a' || key == 'A'){
        translateX-=50;
        cout << translateX;
    } else if(key == 'd' || key =='D'){
        translateX+=50;
        cout << translateX;
    }
    
    
    if(key == 'w' || key == 'W'){
        translateY-=50;
        cout << translateY;
    } else if (key == 's' || key == 'S'){
        translateY+=50;
        cout << translateY;
    }
    
    if(key == '-'){
        size-=100;
        cout << size;
    } else if (key == '+'){
        size+=100;
        cout << size;
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
