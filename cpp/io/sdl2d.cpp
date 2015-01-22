#include "io/sdl2d.hpp"


Draw2d::Draw2d() {
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

void Draw2d::setSurface(SDL_Surface* surf) {
    this->surf=surf;
}

void Draw2d::text(string text) {
    SDL_Color textColor = { 255, 0, 0 };
    surf =TTF_RenderText_Solid( font, "DUPA", textColor );
    this->surf= SDL_ConvertSurfaceFormat(this->surf,SDL_PIXELFORMAT_ABGR8888,0); 
    SDL_Rect offset;

    //Get offsets
    offset.x = 0;
    offset.y = 0; 
    // SDL_SetSurfaceBlendMode(msg,SDL_BLENDMODE_MOD);
   //  SDL_SetSurfaceBlendMode(this->surf,SDL_BLENDMODE_BLEND);
    //SDL_BlitSurface( this->surf, 0, msg, &offset );
   // this->surf=msg;
}