#include "Game.h"
#include "Consts.h"
#include "Entity.h"
#include "Player.h"
#include "PlayerContactListener.h"
#include "VecUtils.h"

Game::Game()
	: window_(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_NAME, sf::Style::Close),
	view_(sf::Vector2f(0, -2), sf::Vector2f(CAM_WIDTH, CAM_HEIGHT)),
	gravity_(0.0f, GRAVITY_STRENGHT),
	world_(gravity_)
{
	window_.setVerticalSyncEnabled(true);
	window_.setFramerateLimit(FRAMERATE);

	// Create view (camera) of the scene and set it to the window
	window_.setView(view_);

	// Create box2d world
	const b2Vec2 gravity(0.0f, GRAVITY_STRENGHT);
	b2World world(gravity);
}

void Game::Update()
{
	// Create ground
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0.0f, -10.0f);
	b2Body* groundBody = world_.CreateBody(&groundBodyDef);
	b2PolygonShape groundBox;
	groundBox.SetAsBox(50.0f, 10.0f);
	groundBody->CreateFixture(&groundBox, 0.0f);

	// Create ground shape
	sf::RectangleShape groundRectangleShape;
	auto size = sf::Vector2f(100, 20);
	groundRectangleShape.setSize(size);
	groundRectangleShape.setOrigin(size / 2.0f);
	groundRectangleShape.setPosition(Box2dVecToSfml(groundBody->GetWorldCenter()));
	groundRectangleShape.setFillColor(sf::Color::Green);

	// Create hero
	sf::Texture playerTexture;
	playerTexture.loadFromFile("./data/hero.png");
	
	Player player(world_);
	float factor = 2.0f / 16.0f;
	player.setScale(factor, factor);
	player.SetTexture(playerTexture);

	PlayerContactListener playerContactListener;
	world_.SetContactListener(&playerContactListener);

	// Main loop
	sf::Clock clock;
	while (window_.isOpen())
	{
		sf::Time deltaTime = clock.restart();
		sf::Event event{};

		while (window_.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window_.close();
		}

		world_.Step(PHYSICS_STEP, VELOCITY_ITERATIONS, POSITION_ITERATIONS);
		player.Update(deltaTime);

		// Rendering
		window_.clear(sf::Color::Blue);

		// Render all the entities
		window_.draw(player);
		window_.draw(groundRectangleShape);

		window_.display();
	}
}
