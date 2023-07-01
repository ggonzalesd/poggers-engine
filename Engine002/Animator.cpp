#include "Animator.h"

Animator::Animator() {
	split = 1;
	frames = 0;
	animation = 0;
	animations = { {0} };
};

Animator::Animator(int split, long frames) {
	this->split = split;
	this->frames = frames;
	this->counter = 0;
	this->index = 0;
	this->animation = 0;
	this->animations = { {0} };
}

Animator::~Animator() {
}

void Animator::addAnimation(const std::vector<int>& newAnimation) {
	animations.push_back(newAnimation);
}

void Animator::setFrames(long frames) {
	this->frames = frames;
}

void Animator::setAnimation(int index) {
	if (index > animations.size()) {
		animation = 0;
	}
	else {
		animation = index;
	}
}


void Animator::update() {
	counter++;
	if (counter > frames) {
		index++;
		counter = 0;
	}
	if (index >= animations[animation].size())
		index = 0;
}

glm::vec4 Animator::getUV() {
	int frame = animations[animation][index];
	int x = frame % split;
	int y = frame / split;
	float step = 1.0f / split;

	glm::vec4 uv = { step * x, 1.0f - (step * (y+1)), step, step };
	return uv;
}