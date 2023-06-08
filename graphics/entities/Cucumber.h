#pragma once
#include <graphics/entities/Entity.h>
#include <graphics/input/Controllable.h>
#include <graphics/camera/OrbitalCamera.h>

class Cucumber : public Entity, public Controllable
{
public:
	Cucumber(const glm::vec3& position);
	~Cucumber();

	void update(float deltaTime) override;
	void mouseMoved(float deltaX, float deltaY) override;
	void pollKeyboard(GLFWwindow* window) override;

	const Camera& getCamera() const { return *this->camera; }

private:
	static constexpr float MOVEMENT_SPEED = 5.0f;

	OrbitalCamera* camera;
	std::shared_ptr<glm::vec3> position;
	std::shared_ptr<float> rotation;
	float moveInput = 0.0f; //either -1.0, 0.0 or 1.0
	float strafeInput = 0.0f; //either -1.0, 0.0 or 1.0
};
