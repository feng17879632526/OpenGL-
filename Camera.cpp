#include "Camera.h"

glm::mat4 Camera::GetViewMatrix() 
{
	return glm::lookAt(Position, Position + Front, Up);
}

void Camera::ProcessKeyboard(Camera_Movement direction, float deltaTime)
{
	float velocity=MovementSpeed*deltaTime;
	if (direction == FORWARD)
		Position+= velocity*Front;
	if (direction == BACKWARD)
		Position -= velocity * Front;
	if (direction == RIGHT)
		Position += velocity * Right;
	if (direction == LEFT)
		Position -= velocity * Right;
}

void Camera::ProcessMouseMovemenet(float xOffset, float yOffset,bool constrainPitch)
{
	xOffset *= MouseSensitivity;
	Yaw += xOffset;
	
	yOffset *= MouseSensitivity;
	Pitch += yOffset;

	if (constrainPitch) {
	if (Pitch > 80)
		Pitch = 80;
	else if (Pitch < -80)
		Pitch = -80;
	}

	UpdateCameraVectors();
}

void Camera::ProcessMouseScroll(float yOffset)
{
	Zoom -= yOffset;
	if (Zoom > 80.0f)
		Zoom = 80.0f;
	else if (Zoom < 1.0f)
		Zoom = 1.0f;
}

void Camera::UpdateCameraVectors()
{
	glm::vec3 direction;
	direction.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	direction.y = sin(glm::radians(Pitch));
	direction.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	Front = glm::normalize(direction);

	Right = glm::normalize(glm::cross(Front, WorldUp));
	Up = glm::normalize(glm::cross(Right, Front));
}

Camera::Camera(glm::vec3 position , glm::vec3 up ,
	float yaw , float pitch)
	:Front(glm::vec3(0.0f,0.0f,-1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
{
	Position = position;
	WorldUp = up;
	Yaw = yaw;
	Pitch = pitch;
	UpdateCameraVectors();
}

Camera::Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch)
	:Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
{
	Position = glm::vec3(posX, posY, posZ);
	WorldUp = glm::vec3(upX, upY, upZ);
	Yaw = yaw;
	Pitch = pitch;
	UpdateCameraVectors();
}