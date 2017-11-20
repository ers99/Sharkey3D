#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GL\glew.h>
#include <gl\glu.h>
#include <vector>
#include "GameObject.h"

enum CameraDirection {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT,
	UP,
	DOWN
};

const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;


class Camera
{
public:
	Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH);
	Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);
	~Camera();

	void SetPosition(glm::vec3 position);
	glm::vec3 getPosition()
	{
		return cameraPos;
	}

	glm::mat4 getViewMatrix()
	{
		return glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
	}

	float getZoom()
	{
		return zoom;
	}

	void setMovementSpeed(float speed)
	{
		movementSpeed = speed;
	}

	float getMovementSpeed()
	{
		return movementSpeed;
	}


	void jump(float height);


	void ProcessKeyboard(CameraDirection direction, double deltaTime);
	void ProcessMouseMovement(float xoffset, float yoffset, GLboolean contstrainPitch = true);


	void update(float deltaTime);

	glm::vec3 &shoot();

private:

	void updateCameraVectors();


	//Camera Position vector
	glm::vec3 cameraPos;

	//Position vector camera looks at
	glm::vec3 cameraFront;

	//Right axis of camera
	glm::vec3 cameraRight;

	//Up axis of camera
	glm::vec3 cameraUp;

	glm::vec3 worldUp;

	float yaw;
	float pitch;
	float movementSpeed;
	float mouseSensitivity;
	float zoom;
	float yVel;
	bool isJumping;
};


