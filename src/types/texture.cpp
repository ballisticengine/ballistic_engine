#include "types/texture.hpp"
namespace Ballistic {
    namespace Types {

        Texture::Texture() {

        }

        Texture::Texture(string filename, string orig_filename) {
            this->filename = filename;
            this->orig_filename = orig_filename;
        }

        Texture * Texture::clone() {
            Texture *clone = new Texture();
            Uint32 rmask, gmask, bmask, amask;
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
            rmask = 0xff000000;
            gmask = 0x00ff0000;
            bmask = 0x0000ff00;
            amask = 0x000000ff;
#else
            rmask = 0x000000ff;
            gmask = 0x0000ff00;
            bmask = 0x00ff0000;
            amask = 0xff000000;
#endif
            clone->filename = filename;

            SDL_Rect rect;
            rect.x = rect.y = 0;
            rect.w = this->surf->w;
            rect.h = this->surf->h;
            //clone->surf=SDL_CreateRGBSurface(0,this->surf->w,this->surf->h,32,amask,bmask,gmask,rmask);
            clone->surf = SDL_CreateRGBSurfaceFrom(this->surf->pixels, this->surf->w, this->surf->h,
                    32,
                    this->surf->pitch,
                    amask, bmask, gmask, rmask);
            //SDL_BlitSurface(surf,&rect,clone->surf,&rect);
            return clone;

        }

        void Texture::free() {
            delete surf;
        }

        textureFormat Texture::getFormat() {
            string ext = Utils::getExt(this->filename);
            return TF_RGBA;
            if (ext == "bmp") {
                return TF_BGR;
            } else {
                if (this->surf->format->BitsPerPixel == 32) {
                    return TF_RGBA;
                } else {
                    return TF_RGB;
                }
            }
        }

        void Texture::setPixels(void *pixels) {
            this->surf->pixels = pixels;
        }

        void * Texture::getPixels() {
            return surf->pixels;
        }

        SDL_Surface * Texture::getSurface() {
            return this->surf;
        }

        void Texture::setSurface(SDL_Surface *surf) {
            this->surf = surf;
        }

        int Texture::getWidth() {
            return surf->w;
        }

        int Texture::getHeight() {
            return surf->h;
        }


    }
}

