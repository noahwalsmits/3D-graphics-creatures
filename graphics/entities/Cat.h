#pragma once
#include <graphics/entities/Entity.h>
#include <graphics/entities/Cucumber.h>

class Cat : public Entity
{
public:
	Cat(const glm::vec3& position, const Cucumber& player);
	~Cat() = default;

	void update(float deltaTime) override;

private:
	static constexpr float DETECTION_RANGE = 3.0f;
	static constexpr float FLEEING_SPEED = 3.0f;

	const Cucumber& player;
	std::shared_ptr<glm::vec3> position;
	std::shared_ptr<float> currentRotation;
	float desiredRotation = 0.0f;
	float movementSpeed = 0.0f;
};
