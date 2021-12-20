#pragma once

#include "Entity.h"
#include "Player.h"

#include <box2d/box2d.h>
#include <SFML/Graphics.hpp>

class Game
{
public:
	Game();

	void startMainLoop();
	void drawColliders();
	void drawBody(b2Body* body);
	void clear();
	Player* createEntities();
private:
	sf::RenderWindow window_;
	b2Vec2 gravity_;
	b2World world_;
	bool drawColliders_ = true;
	std::vector<std::unique_ptr<Entity>> entities_;
};
