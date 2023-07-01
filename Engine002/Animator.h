#pragma once

#include <vector>
#include <glm/glm.hpp>

class Animator
{
protected:
	int split, index;
	int animation;
	long counter;
	long frames;
	std::vector<std::vector<int>> animations;

public:
	Animator();
	Animator(int split, long frames);
	~Animator();

	void addAnimation(const std::vector<int>& newAnimation);
	void setFrames(long speed);
	void setAnimation(int index);
	void update();
	glm::vec4 getUV();
};

