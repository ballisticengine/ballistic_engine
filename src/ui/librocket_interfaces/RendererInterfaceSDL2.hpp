#ifndef RENDERINTERFACESDL2_H
#define RENDERINTERFACESDL2_H

#include <Rocket/Core/RenderInterface.h>

#include <iostream>
#include <cmath>

using namespace std;

#include <SDL2/SDL.h>
#include <GL/glew.h>

#if !(SDL_VIDEO_RENDER_OGL)
    #error "Only the opengl sdl backend is supported. To add support for others, see http://mdqinc.com/blog/2013/01/integrating-librocket-with-sdl-2/"
#endif


#include "renderer/RendererInterface.hpp"
#include "config/Config.hpp"

class RocketSDL2Renderer : public Rocket::Core::RenderInterface
{
public:
	RocketSDL2Renderer(RendererInterface *renderer, SDL_Renderer* mRenderer,  SDL_Window* mScreen);

	/// Called by Rocket when it wants to render geometry that it does not wish to optimise.
	virtual void RenderGeometry(Rocket::Core::Vertex* vertices, int num_vertices, int* indices, int num_indices, Rocket::Core::TextureHandle texture, const Rocket::Core::Vector2f& translation);

	/// Called by Rocket when it wants to enable or disable scissoring to clip content.
	virtual void EnableScissorRegion(bool enable);
	/// Called by Rocket when it wants to change the scissor region.
	virtual void SetScissorRegion(int x, int y, int width, int height);

	/// Called by Rocket when a texture is required by the library.
	virtual bool LoadTexture(Rocket::Core::TextureHandle& texture_handle, Rocket::Core::Vector2i& texture_dimensions, const Rocket::Core::String& source);
	/// Called by Rocket when a texture is required to be built from an internally-generated sequence of pixels.
	virtual bool GenerateTexture(Rocket::Core::TextureHandle& texture_handle, const Rocket::Core::byte* source, const Rocket::Core::Vector2i& source_dimensions);
	/// Called by Rocket when a loaded texture is no longer required.
	virtual void ReleaseTexture(Rocket::Core::TextureHandle texture_handle);

private:
    SDL_Renderer* mRenderer;
    SDL_Window* mScreen;
    RendererInterface *renderer;
    int width,height;
};

#endif
