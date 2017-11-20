#pragma once
#include <SDL.h>
#include <gl\glew.h>
#include <SDL_opengl.h>
#include <gl\glu.h>
#include <vector>
#include <iostream>
#include <string>
#include <SDL_image.h>
#include <map>



class TextureLoader
{
public:

	TextureLoader(int size);
	~TextureLoader();
	GLuint &loadTexture(const char *path);
	GLuint &loadPNG(const char *path);
	GLuint &getTextures()
	{
		return textures;
	}


private:
	GLuint textures;
	int size;
};

