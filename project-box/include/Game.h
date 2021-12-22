#pragma once

#include "Entity.h"
#include "Player.h"

#include <box2d/box2d.h>
#include <SFML/Graphics.hpp>

/**
 * \brief The main class of that program. Contains the window and the main loop for example.
 */
class Game
{
public:
	/**
	 * \brief Creates a new game.
	 */
	Game();

	/**
	 * \brief Starts the main loop. The loop continues until the window is closed.
	 */
	void startMainLoop();

	/**
	 * \brief Draws the colliders on the screen.
	 */
	void drawColliders();

	/**
	 * \brief Draws the colliders of the provided body.
	 * \param body The body whose colliders should be drawn.
	 */
	void drawBodyColliders(b2Body* body);

	/**
	 * \brief Clears all the entities of the current scene.
	 */
	void clear();

	/**
	 * \brief Creates the entities of the scene.
	 * \return A pointer to the player of that scene.
	 */
	Player* createEntities();
private:
	sf::RenderWindow window_;
	b2Vec2 gravity_;
	b2World world_;
	bool drawColliders_ = false;
	std::vector<std::unique_ptr<Entity>> entities_;
};
