#include "Camera.h"
#include <iostream>

Camera::Camera(glm::vec3 position, glm::vec3 up, float _yaw, float _pitch) : cameraFront(glm::vec3(0.0f, 0.0f, -1.0f)),
movementSpeed(SPEED), mouseSensitivity(SENSITIVITY), zoom(ZOOM), yVel(0.0f), isJumping(false)
{
	cameraPos = position;
	worldUp = up;
	yaw = _yaw;
	pitch = _pitch;
	updateCameraVectors();
}

Camera::Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float _yaw, float _pitch) : cameraFront(glm::vec3(0.0f, 0.0f, -1.0f)), movementSpeed(SPEED), mouseSensitivity(SENSITIVITY), zoom(ZOOM), yVel(0.0f),
isJumping(false)
{
	cameraPos = glm::vec3(posX, posY, posZ);
	worldUp = glm::vec3(upX, upY, upZ);
	yaw = _yaw;
	pitch = _pitch;
	updateCameraVectors();
}

void Camera::jump(float power)
{
	if (!isJumping)
	{
		yVel = power;
		isJumping = true;
	}
}

void Camera::ProcessKeyboard(CameraDirection direction, double deltaTime)
{
	float velocity = movementSpeed * deltaTime;
	if (direction == FORWARD)
		cameraPos += glm::normalize(glm::vec3(cameraFront.x,0.0f,cameraFront.z)) * velocity;
	if (direction == BACKWARD)
		cameraPos -= glm::normalize(glm::vec3(cameraFront.x, 0.0f, cameraFront.z)) * velocity;
	if (direction == LEFT)
		cameraPos -= glm::normalize(glm::vec3(cameraRight.x, 0.0f, cameraRight.z)) * velocity;
	if (direction == RIGHT)
		cameraPos += glm::normalize(glm::vec3(cameraRight.x, 0.0f, cameraRight.z)) * velocity;
	if (direction == UP)
		cameraPos += worldUp * velocity;
	if (direction == DOWN)
		cameraPos -= worldUp * velocity;
}

void Camera::ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch)
{
	xoffset *= mouseSensitivity;
	yoffset *= mouseSensitivity;

	yaw += xoffset;
	pitch -= yoffset;
	if (constrainPitch)
	{
		if (pitch > 89.0f)
			pitch = 89.0f;
		if (pitch < -89.0f)
			pitch = -89.0f;
	}

	updateCameraVectors();
}

void Camera::update(float deltaTime)
{
	if (cameraPos.y < 2.0f)
	{
		isJumping = false;
		yVel = 0;
		cameraPos.y = 2.0f;
	}

	cameraPos.y += yVel * deltaTime;

	if(isJumping)
		yVel -= 9.8f * deltaTime;
}

glm::vec3 &Camera::shoot()
{
	return cameraFront;
}

void Camera::updateCameraVectors()
{
	// Calculate the new Front vector
	glm::vec3 front;
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	cameraFront = glm::normalize(front);
	// Also re-calculate the Right and Up vector
	cameraRight = glm::normalize(glm::cross(cameraFront, worldUp));  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
	cameraUp = glm::normalize(glm::cross(cameraRight, cameraFront));
}

Camera::~Camera()
{
}

void Camera::SetPosition(glm::vec3 position)
{
	cameraPos = position;
}
