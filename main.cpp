#include <SDL.h>
#include <gl\glew.h>
#include <SDL_opengl.h>
#include <gl\glu.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <string>
#include <SDL_image.h>
#include "ShaderLoader.h"
#include "Camera.h"
#include <chrono>
//#include "TextureLoader.h"
#include "GameObject.h"
#include <memory>

typedef std::chrono::high_resolution_clock Clock;

SDL_Window  *init();

int windowWidth = 1366, windowHeight = 768;

float speed = 0;
float bulletSpeed = 10.0f;


struct Timer
{
	std::chrono::time_point<std::chrono::steady_clock> currentTime = Clock::now(), lastTime = Clock::now();
	double fTime = 0;

	void Tick()
	{
		lastTime = currentTime;
		currentTime = Clock::now();
		fTime = 0.000000001 * std::chrono::duration_cast<std::chrono::nanoseconds>(currentTime - lastTime).count();
		SDL_PumpEvents();
	}
} timer;

int main(int argc, char *args[])
{
	std::cout << "Enter resolution width followed by height" << std::endl;
	std::cin >> windowWidth;
	std::cin >> windowHeight;

	SDL_Window *gWindow = init();
	if (!gWindow)
	{
		std::cerr << "Could not initialize" << std::endl;
		return -1;
	}

	float vertices1[] = {
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};

	float vertices2[] = {
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};

	Camera camera(glm::vec3(0.0f, 2.0f, 0.0f));
	speed = camera.getMovementSpeed();

	float mixAmount = 1.0f;

	ShaderLoader shader1("Shaders/vert1.vs", "Shaders/frag1.fs");

	shader1.use();
	shader1.setInt("ourTexture1", 0);
	shader1.setInt("ourTexture2", 1);

	bool quit = false;

	SDL_Event e;
	const Uint8 * keys = SDL_GetKeyboardState(NULL);

	glClearColor(0.4f, 0.2f, 0.4f, 1.0f);

	SDL_SetWindowGrab(gWindow, SDL_TRUE);
	SDL_SetRelativeMouseMode(SDL_TRUE);






	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//GLuint duckTex, wallTex;

	////DEBUG!!!!!!!!!!!!!!
	//glGenTextures(1, &duckTex);
	//glGenTextures(1, &wallTex);

	//glBindTexture(GL_TEXTURE_2D, duckTex);

	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//SDL_Surface *duckImage = IMG_Load("Textures/duck.jpg");
	//if (duckImage)
	//{

	//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, duckImage->w, duckImage->h, 0, GL_RGB, GL_UNSIGNED_BYTE, duckImage->pixels);
	//	glGenerateMipmap(GL_TEXTURE_2D);
	//	SDL_FreeSurface(duckImage);
	//}
	//else
	//{
	//	std::cerr << "Failed to load texture" << std::endl;
	//	exit(-1);
	//}

	//glBindTexture(GL_TEXTURE_2D, wallTex);

	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//SDL_Surface *image = IMG_Load("Textures/wall1.jpg");
	//if (image)
	//{

	//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->w, image->h, 0, GL_RGB, GL_UNSIGNED_BYTE, image->pixels);
	//	glGenerateMipmap(GL_TEXTURE_2D);
	//	SDL_FreeSurface(image);
	//}
	//else
	//{
	//	std::cerr << "Failed to load texture" << std::endl;
	//	exit(-1);
	//}



	TextureLoader textureLoader(2);
	GLuint duckTex = textureLoader.loadPNG("Textures/duck.png");
	GLuint wallTex = textureLoader.loadTexture("Textures/wall1.jpg");
	GLuint swanTex = textureLoader.loadPNG("Textures/swan.png");

	GameObject duck(vertices1, sizeof(vertices1), shader1, duckTex, glm::vec3(5, 3, 5));
	std::vector<GameObject> walls;

	for (int i = 0; i < 50; ++i)
	{
		for (int j = 0; j < 50; ++j)
		{
			GameObject cube(vertices2, sizeof(vertices2), shader1, wallTex, glm::vec3(i * 5, 0, j * 5));
			cube.scale(glm::vec3(5, 1, 5));
			walls.push_back(cube);
		}
	}

	std::vector<GameObject> bullets;


	while (!quit)
	{
		timer.Tick();
		camera.update(timer.fTime);
		for (auto i = bullets.begin(); i != bullets.end(); i++)
		{
			i->update(timer.fTime);
		}
			while (SDL_PollEvent(&e) != 0)
			{
				if (e.type == SDL_QUIT)
				{
					quit = true;
				}
				if (e.type == SDL_KEYDOWN)
				{
					if (e.key.keysym.sym == SDLK_ESCAPE)
					{
						if (SDL_GetRelativeMouseMode() == SDL_FALSE)
						{
							SDL_SetRelativeMouseMode(SDL_TRUE);
						}
						else
						{
							SDL_SetRelativeMouseMode(SDL_FALSE);
							SDL_WarpMouseInWindow(gWindow, windowWidth / 2, windowHeight / 2);
						}
					}
				}
				if (e.type == SDL_MOUSEMOTION)
				{
					if(SDL_GetRelativeMouseMode() == SDL_TRUE)
						camera.ProcessMouseMovement(e.motion.xrel, e.motion.yrel);
				}
				if (e.type == SDL_MOUSEBUTTONDOWN)
				{
					GameObject bullet(vertices1, sizeof(vertices1), shader1, swanTex, camera.getPosition());
					bullet.SetVelocity(camera.shoot() * bulletSpeed);
					bullet.scale(glm::vec3(0.2, 0.2, 0.2));
					bullets.push_back(std::move(bullet));
				}

			}

			if (keys[SDL_SCANCODE_W])
			{
				camera.ProcessKeyboard(CameraDirection::FORWARD, timer.fTime);
			}
			if (keys[SDL_SCANCODE_S])
			{
				camera.ProcessKeyboard(CameraDirection::BACKWARD, timer.fTime);
			}
			if (keys[SDL_SCANCODE_A])
			{
				camera.ProcessKeyboard(CameraDirection::LEFT, timer.fTime);
			}
			if (keys[SDL_SCANCODE_D])
			{
				camera.ProcessKeyboard(CameraDirection::RIGHT, timer.fTime);
			}
			if (keys[SDL_SCANCODE_SPACE])
			{
				camera.jump(5.0f);
			}

			if (keys[SDL_SCANCODE_LSHIFT])
			{
				camera.setMovementSpeed(speed * 2);
			}
			else
			{
				camera.setMovementSpeed(speed);
			}



			//Clear Screen and bind textures
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



			shader1.use();

			//Pass projection matrix
			glm::mat4 projection;
			projection = glm::perspective(glm::radians(camera.getZoom()), windowWidth / (float)windowHeight, 1.f, 100.0f);
			shader1.setMatrix4fv("projection", projection);


			//camera view transformation
			shader1.setMatrix4fv("view", camera.getViewMatrix());

			shader1.setFloat("mixAmount", mixAmount);

			for (auto i = walls.begin(); i != walls.end(); ++i)
			{
				i->Draw();
			}
			duck.Draw();
			for (auto i = bullets.begin(); i != bullets.end(); ++i)
			{
				i->Draw();
			}

			SDL_GL_SwapWindow(gWindow);
		
		
	}
	//bufferLoader.clean();

	SDL_DestroyWindow(gWindow);
	return 0;

}

SDL_Window *init()
{

	

	SDL_Window *gWindow = nullptr;

	//Create context
	SDL_GLContext gContext = SDL_GL_CreateContext(gWindow);

	bool success = true;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "SDL Not initialized\n" << SDL_GetError() << std::endl;
		success = false;
	}
	// load support for the JPG and PNG image formats
	int flags = IMG_INIT_JPG | IMG_INIT_PNG;
	int initted = IMG_Init(flags);
	if ((initted&flags) != flags) {
		printf("IMG_Init: Failed to init required jpg and png support!\n");
		printf("IMG_Init: %s\n", IMG_GetError());
		// handle error
		success = false;
	}

	//Use OpenGL 3.1 core
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);

	gWindow = SDL_CreateWindow("SDL Works!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windowWidth, windowHeight, SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN);
	if (gWindow == nullptr)
	{
		std::cout << "Window not created\n" << SDL_GetError() << std::endl;
		success = false;
	}

	gContext = SDL_GL_CreateContext(gWindow);
	if (gContext == NULL)
	{
		std::cout << "OpenGL context could not be created! SDL Error: \n" << SDL_GetError() << std::endl;
		success = false;
	}

	//Initialize GLEW
	glewExperimental = GL_TRUE;
	GLenum glewError = glewInit();
	if (glewError != GLEW_OK)
	{
		std::cout << "Error initializing GLEW! \n" << glewGetErrorString(glewError) << std::endl;
		success = false;
	}

	//Use Vsync
	if (SDL_GL_SetSwapInterval(1) < 0)
	{
		std::cout << "Warning: Unable to set VSync! SDL Error: \n" << SDL_GetError() << std::endl;
		success = false;
	}

	//Enable depth testing
	glEnable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_MULTISAMPLE);

	if (success)
	{
		return gWindow;
	}
	else
	{
		throw std::logic_error("Initialization failed");
		return nullptr;
	}
}


