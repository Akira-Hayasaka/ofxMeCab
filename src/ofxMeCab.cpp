//
//  ofxMeCab.cpp
//  ofxMeCabExample
//
//  Created by Akira on 12/7/15.
//
//

#include "ofxMeCab.hpp"

ofxMeCab::ofxMeCab()
{
    bSetDict = false;
}

void ofxMeCab::setDict(string absDicPath)
{
    string arg = "-d " + absDicPath;
    mecab = mecab_new2(arg.c_str());
    bSetDict = true;    
    
    startThread();
}

void ofxMeCab::parse(string jpTxt)
{
    if (bSetDict)
    {
        lock();
        jpTxtQ.push_back(jpTxt);
        unlock();
    }
    else
    {
        ofLogError("ofxMeCab") << "no dictionary file";
    }
}

void ofxMeCab::exit()
{
    waitForThread();
}

void ofxMeCab::threadedFunction()
{
    while (isThreadRunning())
    {
        if (lock())
        {
            bool bAtleast = false;
            string jpTxt = "";
            if (!jpTxtQ.empty())
            {
                jpTxt = jpTxtQ.front();
                jpTxtQ.pop_front();
                bAtleast = true;
            }
            unlock();
            
            if (bAtleast)
            {
                const mecab_node_t *node;
                const char *buf = jpTxt.c_str();
                node = mecab_sparse_tonode2(mecab, buf, jpTxt.size());
                
                node = node->next;
                for (; node->next != NULL; node = node->next)
                {
                    MorphObj mo;
                    vector<string> features = ofSplitString(node->feature, ",");
                    
                    mo.hyousou = node->surface;
                    mo.hyousou = mo.hyousou.substr(0, node->length);
                    
                    if (features.size() == 9)
                    {
                        mo.genkei = features.at(6);
                        mo.hinshi = features.at(0);
                        mo.hinshiSaibunrui1 = features.at(1);
                        mo.hinshiSaibunrui2 = features.at(2);
                        mo.hinshiSaibunrui3 = features.at(3);
                        mo.katsuyoukei = features.at(4);
                        mo.katsuyougata = features.at(5);
                        mo.yomi = features.at(7);
                        mo.hatsuon = features.at(8);
                    }
                    else
                    {
                        mo.bComplete = false;
                        mo.genkei = "err";
                        mo.hinshi = "err";
                        mo.hinshiSaibunrui1 = "err";
                        mo.hinshiSaibunrui2 = "err";
                        mo.hinshiSaibunrui3 = "err";
                        mo.katsuyoukei = "err";
                        mo.katsuyougata = "err";
                        mo.yomi = "err";
                        mo.hatsuon = "err";
                        ofLogError("ofxMeCab::threadedFunction") << "incomplete feature";
                    }
                    
                    ofNotifyEvent(parseEvent, mo);
                }
            }
        }
    }
}