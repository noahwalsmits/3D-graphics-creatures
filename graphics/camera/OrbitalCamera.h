#pragma once
#include<graphics/camera/Camera.h>
#include<graphics/input/Controllable.h>

class OrbitalCamera : public Camera, public Controllable
{
public:
	OrbitalCamera(glm::vec3 target);
	~OrbitalCamera() = default;

	virtual glm::mat4 getViewMatrix() const override;
	void mouseMoved(float deltaX, float deltaY) override;
	void pollKeyboard(GLFWwindow* window) override;

	const float& getDistance() { return this->distance; }
	void setDistance(const float& distance) { this->distance = distance; }
	const float& getYaw() { return this->yaw; }
	void setYaw(const float& yaw) { this->yaw = yaw; }
	const float& getPitch() { return this->pitch; }
	void setPitch(const float& pitch) { this->pitch = pitch; }

private:
	static constexpr float MOUSE_SENSITIVITY = 0.1f;
	static constexpr float MIN_PITCH = -89.0f;
	static constexpr float MAX_PITCH = 89.0f;

	const glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 target; //the position the camera is looking at
	glm::vec3 position; //the current position of the camera
	float distance = 5.0f; //distance between the camera and target positions
	float yaw = -90.0f; //in degrees
	float pitch = 0.0f; //in degrees

	/*Updates the position of the camera based on its yaw and pitch rotations.*/
	void updateViewingAngle();
};

