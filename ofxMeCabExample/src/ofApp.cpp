#include "ofApp.h"

void ofApp::setup()
{
    ofSetLogLevel(OF_LOG_VERBOSE);
    
    // 辞書をフルパスで登録。ofxMeCab/dict/ipadicに入っているので、
    // コンパイルするマシンのパスに変更してください。
    mecab.setDict("/Users/akira/oF/oF090/addons/ofxMeCab/dict/ipadic");
    ofAddListener(mecab.parseEvent, this, &ofApp::onParse);
    
    ofBuffer buf = ofBufferFromFile("sample.txt");
    ofBuffer::Lines lines = buf.getLines();
    for (auto line : lines)
        lineQ.push_back(line);
    
    startThread();
}

void ofApp::exit()
{
    mecab.exit();
    waitForThread();
}

void ofApp::draw()
{
    ofDrawBitmapStringHighlight("fps:" + ofToString(ofGetFrameRate(), 2), 10, 20);
    ofDrawBitmapStringHighlight("press space bar to read next line", 10, 40);
    ofDrawBitmapStringHighlight("example dumps morph obj fields on console", 10, 60);
}

void ofApp::threadedFunction()
{
    while (isThreadRunning())
    {
        if (lock())
        {
            bool bAtleast = false;
            MorphObj mo;
            if (!morphObjs.empty())
            {
                mo = morphObjs.front();
                morphObjs.pop_front();
                bAtleast = true;
            }
            unlock();
            
            if (bAtleast)
            {
                if (mo.bComplete)
                {
                    mo.dump();
                    
                    if (bSpeak)
                    {
                        if (mo.hinshi != "記号")
                        {
                            string voice = "Kyoko";//"Otoya";
                            string cmd = "say -v " + voice + " " + mo.hatsuon + " ";
                            system(cmd.c_str());
                            
                            if (mo.hinshiSaibunrui1 == "固有名詞")
                            {
                                voice = "Kyoko";
                                cmd = "say -v " + voice + " " + mo.hinshiSaibunrui2 + ", " + mo.hinshiSaibunrui3;
                                system(cmd.c_str());
                            }
                        }
                    }
                }
            }
        }
    }
}

void ofApp::onParse(MorphObj& mo)
{
    lock();
    morphObjs.push_back(mo);
    unlock();
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

void ofApp::update(){}
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