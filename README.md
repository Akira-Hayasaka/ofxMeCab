# ofxMeCab #

ofx Japanese morphological analyzer MeCab 

### very much WIP ###

コンパイルするには、アドオンとしてプロジェクトに追加した後、以下を設定する必要があります

"HAVE_CONFIG_H"を
Build Setting => Apple LLVM ver - Preprocessing => Preprocessor Macros
にセット
![ofxMeCab](https://github.com/Akira-Hayasaka/ofxMeCab/raw/master/redmeimg/config.png)

"../../../addons/ofxMeCab/libs/mecab/mecab_Prefix.pch"を
Build Setting => Apple LLVM ver - Language => Prefix Header
にセット
![ofxMeCab](https://github.com/Akira-Hayasaka/ofxMeCab/raw/master/redmeimg/prefix.png)
 
http://taku910.github.io/mecab/