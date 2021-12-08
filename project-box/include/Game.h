#pragma once

#include <box2d/box2d.h>
#include <SFML/Graphics.hpp>

class Game
{
private:
	sf::RenderWindow window_;
	b2Vec2 gravity_;
	b2World world_;
	bool drawColliders_ = true;
public:
	Game();

	void Update();
};
