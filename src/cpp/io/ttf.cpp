#include "io/ttf.hpp"


TTF::TTF() {
      if( TTF_Init() == -1 ) {
             cout << "TTF init error!\n";
         } else {
             cout << "TTF ok.\n";
         }
      string path=string(CONFIG_DIR)+DS+string(COMMON_DIR)+DS+string(FONT_DIR)+DS+string("Anonymous.ttf");
      //string path="/home/maciek/ballistic_engine/lazy.ttf";
      font=TTF_OpenFont(path.c_str(), 48 );
      if(font!=0) {
          cout << "Font ok\n";
      } else {
          cout << "Font error!\n";
          cout << path << endl;
      }
  }  

