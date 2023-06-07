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
	OrbitalCamera* camera;
	std::shared_ptr<glm::vec3> position;
	float rotation = 0.0f;
	float moveSpeed = 0.0f;
	float strafeSpeed = 0.0f;
};
