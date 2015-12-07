#include "ofApp.h"

void ofApp::setup()
{
    ofSetLogLevel(OF_LOG_VERBOSE);
    mecab.setDict("/Users/akira/oF/oF090/addons/ofxMeCab/dict/ipadic");
    ofAddListener(mecab.parseEvent, this, &ofApp::onParse);
    
    ofBuffer buf = ofBufferFromFile("sample.txt");
    ofBuffer::Lines lines = buf.getLines();
    for (auto line : lines)
        lineQ.push_back(line);
}

void ofApp::exit()
{
    mecab.exit();
}

void ofApp::update()
{
    if (!morphObjs.empty())
    {
        MorphObj mo = morphObjs.front();
        morphObjs.pop_front();
        mo.dump();
    }
}

void ofApp::draw()
{
    ofDrawBitmapStringHighlight("fps: " + ofToString(ofGetFrameRate(), 2), 10, 20);
}

void ofApp::onParse(MorphObj& mo)
{
    morphObjs.push_back(mo);
}

void ofApp::keyPressed(int key)
{
    if (key == ' ')
    {
        if (!lineQ.empty())
        {
            mecab.parse(lineQ.front());
            lineQ.pop_front();
        }
    }
}

void ofApp::keyReleased(int key){}
void ofApp::mouseMoved(int x, int y){}
void ofApp::mouseDragged(int x, int y, int button){}
void ofApp::mousePressed(int x, int y, int button){}
void ofApp::mouseReleased(int x, int y, int button){}
void ofApp::mouseEntered(int x, int y){}
void ofApp::mouseExited(int x, int y){}
void ofApp::windowResized(int w, int h){}
void ofApp::gotMessage(ofMessage msg){}
void ofApp::dragEvent(ofDragInfo dragInfo){}