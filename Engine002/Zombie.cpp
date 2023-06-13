#include "Zombie.h"


Zombie::Zombie() {}

Zombie::~Zombie() {}

void Zombie::init(float speed, glm::vec2 position) {
	this->path = "Textures/circle.png";
	this->speed = speed;
	this->position = position;
	color.set(0, 255, 0, 255);
}

void Zombie::update(const vector<string>& levelData, vector<Human*>& humans,
	vector<Zombie*>& zombies) {

}