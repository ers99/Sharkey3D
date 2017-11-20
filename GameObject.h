#pragma once
#include <SDL.h>
#include <gl\glew.h>
#include <SDL_opengl.h>
#include <gl\glu.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include <iostream>
#include <string>
#include "ShaderLoader.h"
#include "TextureLoader.h"

class GameObject
{
public:
	GameObject(float vertices[], int size, ShaderLoader &shader, GLuint &_tex, glm::vec3 position = glm::vec3(0, 0, 0));
	~GameObject();
	void Draw();
	void update(float deltaTime);
	GameObject &scale(glm::vec3 _scale);

	GLuint &getVBO()
	{
		return VBO;
	}
	GLuint &getVAO()
	{
		return VAO;
	}

	GLuint &getTexture()
	{
		return GLTexture;
	}

	void SetVelocity(glm::vec3 vel)
	{
		mVelocity = vel;
	}

private:
	GLuint VAO, VBO;
	GLuint GLTexture;
	//std::vector<float> vertices;
	
	glm::vec3 mVelocity;
	glm::vec3 mPosition;
	glm::vec3 mAcceleration;
	glm::vec3 mScale;
	ShaderLoader mShader;
	glm::vec3 frictionVec;
	bool onGround;
	bool isUpdating;

};

