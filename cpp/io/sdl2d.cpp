#include "io/sdl2d.hpp"


Draw2d::Draw2d() {
      if( TTF_Init() == -1 ) {
             cout << "TTF init error!\n";
         } else {
             cout << "TTF ok.\n";
         }
      string path=string(CONFIG_DIR)+DS+string(COMMON_DIR)+DS+string(FONT_DIR)+DS+string("sans.ttf");
      //string path="/home/maciek/ballistic_engine/lazy.ttf";
      font=TTF_OpenFont(path.c_str(), 12 );
      if(font!=0) {
          cout << "Font ok\n";
      } else {
          cout << "Font error!\n";
          cout << path << endl;
      }
  }  

void Draw2d::setSurface(SDL_Surface* surf) {
    this->surf=surf;
}

void Draw2d::text(string text) {
    SDL_Color textColor = { 255, 255, 255 };
    SDL_Surface *message =TTF_RenderText_Solid( font, text.c_str(), textColor );
     SDL_Rect offset;

    //Get offsets
    offset.x = 10;
    offset.y = 10; 
    SDL_BlitSurface( message, 0, this->surf, &offset );
    this->surf=message;
}