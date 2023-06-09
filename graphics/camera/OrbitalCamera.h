#pragma once
#include<graphics/camera/Camera.h>
#include<graphics/input/Controllable.h>

class OrbitalCamera : public Camera, public Controllable
{
public:
	OrbitalCamera(glm::vec3& target, const float& distance, const float& minPitch = -89.0f, const float&maxPitch = 89.0f);
	~OrbitalCamera() = default;

	virtual glm::mat4 getViewMatrix() const override;
	void mouseMoved(float deltaX, float deltaY) override;
	void pollKeyboard(GLFWwindow* window) override;

	const float& getDistance() const { return this->distance; }
	void setDistance(const float& distance) { this->distance = distance; }
	const float& getYaw() const { return this->yaw; }
	void setYaw(const float& yaw) { this->yaw = yaw; }
	const float& getPitch() const { return this->pitch; }
	void setPitch(const float& pitch) { this->pitch = pitch; }

private:
	static constexpr float MOUSE_SENSITIVITY = 0.1f;
	const glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
	
	glm::vec3& target; //the position the camera is looking at
	float distance; //distance between the camera and target positions
	float minPitch;
	float maxPitch;

	glm::vec3 position; //the current position of the camera
	float yaw = 0.0f; //in degrees
	float pitch = 0.0f; //in degrees

	/*Updates the position of the camera based on its yaw and pitch rotations.*/
	void updateViewingAngle();
};

