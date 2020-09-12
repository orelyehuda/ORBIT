#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>

#include "Star.h"

#include <math.h>

#include "Textbox.h"


const int HEIGHT = 800;
const int WIDTH = 1080;

float getDistance(class Star s1, class Star s2);
float getGravity(class Star s1, class Star s2);
sf::Vector2<float> getGVector(class Star s1, class Star s2);
sf::Vector2<float> getVVector(class Star s1);
class Star updateLocation(class Star s1);

sf::CircleShape createStar(class Star s1, sf::Color color);


int main() {

	// Create the main window
	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "ORBIT");
	window.setFramerateLimit(60);

	int type = 0;

	float fps;
	sf::Clock clock = sf::Clock::Clock();
	sf::Time previousTime = clock.getElapsedTime();
	sf::Time currentTime;

	std::vector<class Star> stars;
	std::vector<class Star> orbiters;

	std::vector<sf::CircleShape> starObjects;
	std::vector<sf::CircleShape> orbitObjects;

	int num_stars = 0;
	int num_orbiters = 0;

	Textbox text1(20, sf::Color::Black, true);
	text1.setPosition({ 100, 100 });
	text1.setLimit(true, 30);

	while (window.isOpen()) {

		currentTime = clock.getElapsedTime();
		fps = 1.0f / (currentTime.asSeconds() - previousTime.asSeconds()); // the asSeconds returns a float
	   //std::cout << "fps =" << floor(fps) << std::endl; // flooring it will make the frame rate a rounded number
		previousTime = currentTime;

		sf::Event event;

		while (window.pollEvent(event)) {
			// Close window: exit

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
				type = 1;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::O)) {
				type = 0;
			}
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			
				sf::Vector2i p1 = sf::Mouse::getPosition();

				if (type == 0) {
					Star temp = Star(400.0, 8, { float(p1.x),  float(p1.y) }, 1, { 10,  0 });
					sf::CircleShape new_star(temp.getRadius());
					new_star = createStar(temp, sf::Color::Black);
					orbiters.push_back(temp);
					orbitObjects.push_back(new_star);
					num_orbiters++;
				}
				else if (type == 1) {
					Star temp = Star(10000.0, 30, { float(p1.x),  float(p1.y) }, 1, { 0,  0 });
					sf::CircleShape new_star(temp.getRadius());
					new_star = createStar(temp, sf::Color::Black);
					stars.push_back(temp);
					starObjects.push_back(new_star);
					num_stars++;
				}
			}

			if (event.type == sf::Event::Closed) window.close();

			if (event.type == sf::Event::Resized){
				// update the view to the new size of the window
				sf::FloatRect visibleArea(0.f, 0.f, event.size.width, event.size.height);
				window.setView(sf::View(visibleArea));
			}

		}
		for (int i = 0; i < num_orbiters; i++) {

			for (int k = 0; k < num_stars; k++) orbiters[i].setVelocity(orbiters[i].getVelocity() - getGVector(orbiters[i], stars[k])); // calc new pos for each star force

			orbiters[i].setPosition(orbiters[i].getPosition() + orbiters[i].getVelocity());


			orbitObjects[i].setPosition(orbiters[i].getPosition().x, orbiters[i].getPosition().y);

			orbiters[i].addTrail({ orbiters[i].getPosition().x + orbiters[i].getRadius(),orbiters[i].getPosition().y + orbiters[i].getRadius() });

			sf::Color color(0, 0, 0);

			float dx = orbiters[i].getVelocity().x * orbiters[i].getVelocity().x;
			float dy = orbiters[i].getVelocity().y * orbiters[i].getVelocity().y;

			float c = sqrt(dx + dy) * 5;

			if (c > 255) c = 255;
			color.r = c;
			color.b = 255 - c;
			orbitObjects[i].setFillColor(color);

			for (int m = 0; m < num_stars; m++) {
				sf::FloatRect sunBox = starObjects[m].getGlobalBounds();

				if (sunBox.contains(orbitObjects[i].getPosition())) {
					orbitObjects.erase(orbitObjects.begin() + i);
					orbiters.erase(orbiters.begin() + i);
					num_orbiters--;
					break;
				}
			}

		}

		window.clear(sf::Color::White);

		for (int j = 0; j < num_orbiters; j++) {
			window.draw(orbiters[j].getTrail());
			window.draw(orbitObjects[j]);
		}

		for (int k = 0; k < num_stars; k++) window.draw(starObjects[k]);
		text1.drawTo(window);

		window.display();
	}
	return EXIT_SUCCESS;
}

sf::CircleShape createStar(class Star s1, sf::Color color) {

	sf::CircleShape star1(s1.getRadius());
	//star1.setOrigin(s1.getPosition().x, s1.getPosition().y);
	star1.setFillColor(color);
	star1.setPosition(s1.getPosition().x, s1.getPosition().y);

	return star1;

}

class Star updateLocation(class Star s1) {
	sf::Vector2<float> new_pos;

	new_pos.x = (s1.getPosition().x + s1.getVelocity().x);
	new_pos.y = (s1.getPosition().y + s1.getVelocity().y);

	s1.setPosition(new_pos);

	return s1;
}

sf::Vector2<float> getVVector(class Star s1) {
	sf::Vector2<float> v;
	v.x = s1.getVelocity().x + s1.getRadius();
	v.y = s1.getVelocity().y + s1.getRadius();

	return v;
}

sf::Vector2<float> getGVector(class Star s1, class Star s2) {

	sf::Vector2<float> gVector = { (s1.getPosition().x - s2.getPosition().x) , (s1.getPosition().y - s2.getPosition().y) };

	float mag = sqrt((gVector.x * gVector.x) + (gVector.y * gVector.y));

	float g = getGravity(s1, s2);

	gVector = gVector / mag;

	return gVector * g;
}


float getGravity(class Star s1, class Star s2) {
	float mm = (s1.getMass() * s2.getMass());
	float r = getDistance(s1, s2);

	float g = (mm / (r * r));

	//std::cout << g << std::endl;

	return g / 300;
}


float getDistance(class Star s1, class Star s2) {

	float dx = (s2.getPosition().x - s1.getPosition().x);
	float dy = (s2.getPosition().y - s1.getPosition().y);

	float dist = float(sqrt((dx * dx) + (dy * dy)));

	return dist;
}
