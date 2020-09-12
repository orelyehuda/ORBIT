#pragma once

#include <SFML/Graphics.hpp>

class Star
{
private:
	float mass;
	float radius;

	float speed;

	int num_trails;
	
	sf::Vector2<float> position;

	sf::Vector2<float> velocity;

	sf::VertexArray trail;

	
public:
	Star();
	Star(float mass, float radius, sf::Vector2<float> position, float speed, sf::Vector2<float> velocity);
	void setMass(float);
	float getMass();
	
	void setRadius(float);
	float getRadius();

	void setSpeed(float);
	float getSpeed();

	sf::Vector2<float> getPosition();
	void setPosition(sf::Vector2<float> vel);

	sf::Vector2<float> getVelocity();
	void setVelocity(sf::Vector2<float> vel);

	sf::VertexArray getTrail();
	void setTrail(sf::VertexArray trail);
	void addTrail( sf::Vector2f);

	sf::VertexArray resizeTrail();
	

};

