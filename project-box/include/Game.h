#pragma once

#include "Entity.h"

#include <box2d/box2d.h>
#include <SFML/Graphics.hpp>

class Game
{
private:
	sf::RenderWindow window_;
	b2Vec2 gravity_;
	b2World world_;
	bool drawColliders_ = false;
	std::vector<std::unique_ptr<Entity>> entities_;
public:
	Game();

	void Update();
};
