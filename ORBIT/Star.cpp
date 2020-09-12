#include "Star.h"


Star::Star() {
	this->radius = 100;
	this->mass = 100;

}
Star::Star(float mass, float radius, sf::Vector2<float> position, float speed, sf::Vector2<float> velocity) {
	this->position = position;
	this->speed = speed;
	this->radius = radius;
	this->mass = mass;
	this->velocity = velocity;
	this->num_trails = 0;
	this->trail.setPrimitiveType(sf::LinesStrip);
}
void Star::setMass(float mass) {
	this->mass = mass;
}

float Star::getMass() {
	return this->mass;
}

void Star::setRadius(float radius) {
	this->radius = radius;
}

float Star::getRadius() {
	return this->radius;
}

sf::Vector2<float> Star::getPosition() {
	sf::Vector2<float> p;
	p.x = this->position.x + this->radius;
	p.y = this->position.y + this->radius;
	return this->position;
}
void Star::setPosition(sf::Vector2<float> position) {
	this->position = position;
}

sf::Vector2<float> Star::getVelocity() {

	return this->velocity;
}
void Star::setVelocity(sf::Vector2<float> velocity) {
	this->velocity = velocity;
}

void Star::setSpeed(float speed) {
	this->speed = speed;
}
float Star::getSpeed() {
	return this->speed;
}

sf::VertexArray Star::getTrail() {
	return this->trail;
}
void Star::setTrail(sf::VertexArray trail) {
	this->trail = trail;
}
void Star::addTrail(sf::Vector2f pos) {
	if (num_trails >= 100) {
		this->trail = resizeTrail();
	}

	this->trail.append(pos);
	this->trail[this->num_trails].color = sf::Color(100, 0, 200);
	this->num_trails++;


	 
}

sf::VertexArray Star::resizeTrail() {
	int i;
	sf::VertexArray new_a;


	for (i = 0; i < this->num_trails-2; i++) {
		new_a.append(this->trail[i + 2]);
	}
	//this->trail.resize(num_trails);
	this->num_trails-= 2;

	return new_a;

}