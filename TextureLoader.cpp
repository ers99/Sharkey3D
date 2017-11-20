#include "TextureLoader.h"



TextureLoader::TextureLoader(int _size)
{

}


TextureLoader::~TextureLoader()
{

}

GLuint &TextureLoader::loadTexture(const char * path)
{
	glGenTextures(1, &textures);



	glBindTexture(GL_TEXTURE_2D, textures);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	SDL_Surface *image = IMG_Load(path);
	if (image)
	{

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->w, image->h, 0, GL_RGB, GL_UNSIGNED_BYTE, image->pixels);
		glGenerateMipmap(GL_TEXTURE_2D);
		SDL_FreeSurface(image);
		return textures;
	}
	else
	{
		std::cerr << "Failed to load texture" << std::endl;
		exit(-1);
	}
}

GLuint& TextureLoader::loadPNG(const char* path)
{
	glGenTextures(1, &textures);



	glBindTexture(GL_TEXTURE_2D, textures);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	SDL_Surface *image = IMG_Load(path);
	if (image)
	{

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image->w, image->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, image->pixels);
		glGenerateMipmap(GL_TEXTURE_2D);
		SDL_FreeSurface(image);
		return textures;
	}
	else
	{
		std::cerr << "Failed to load texture" << std::endl;
		exit(-1);
	}
}
