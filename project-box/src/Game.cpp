#include "Game.h"
#include "Consts.h"
#include "Entity.h"
#include "Player.h"
#include "PlayerContactListener.h"
#include "Ground.h"
#include "Block.h"
#include "FinishLine.h"
#include "GameManager.h"
#include "Locator.h"
#include "VecUtils.h"
#include "Audio/SfmlAudio.h"

#include <iostream>

Game::Game()
	: window_(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_NAME, sf::Style::Close),
	gravity_(0.0f, GRAVITY_STRENGHT),
	world_(gravity_)
{
	window_.setVerticalSyncEnabled(true);
	window_.setFramerateLimit(FRAMERATE);

	// Create view (camera) of the scene and set it to the window
	window_.setView(sf::View(sf::Vector2f(0, 0), sf::Vector2f(CAM_WIDTH, CAM_HEIGHT)));

	// Create box2d world
	const b2Vec2 gravity(0.0f, GRAVITY_STRENGHT);
	b2World world(gravity);
}

void Game::startMainLoop()
{
	constexpr float groundHalfWidth = 50.0f;
	constexpr float groundHalfHeight = 10.0f;

	// Init audio locator
	Locator::init();
	auto sfmlAudio = std::make_unique<SfmlAudio>();
	sfmlAudio->init();
	Locator::provide(sfmlAudio.get());

	// Create ground
	Ground ground(world_, groundHalfWidth, groundHalfHeight, b2Vec2(groundHalfWidth - 5, -15.0f));

	// Create block
	entities_.emplace_back(std::make_unique<Block>(world_, b2Vec2(5.0f, 0.0f)));

	// Create finish line
	entities_.emplace_back(std::make_unique<FinishLine>(world_, b2Vec2(15.0f, 0.0f)));

	// Create player
	entities_.emplace_back(std::make_unique<Player>(world_));
	auto player = dynamic_cast<Player*>(entities_[2].get());

	PlayerContactListener playerContactListener;
	world_.SetContactListener(&playerContactListener);

	// Winning text
	sf::Font upheav;
	if (!upheav.loadFromFile(FONT_PATH))
	{
		std::cout << "Error loading font\n";
	}

	sf::Text text;
	text.setFont(upheav);
	text.setString("You Win");
	text.setFillColor(sf::Color::Red);
	text.setScale(SCALE_FACTOR / 8.0f, SCALE_FACTOR / 8.0f);
	//center text
	sf::FloatRect textRect = text.getLocalBounds();
	text.setOrigin(textRect.width / 2.0f, textRect.height / 2.0f);
	text.setCharacterSize(192);
	text.setPosition(-5, -2);

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
			if (event.type == sf::Event::KeyPressed)
			{
			}
		}

		// Only startMainLoop with focus
		if (window_.hasFocus() && GameManager::GetInstance()->GetState() == GameState::Playing)
		{
			// Step the physics
			world_.Step(PHYSICS_STEP, VELOCITY_ITERATIONS, POSITION_ITERATIONS);

			// Update the entites

			for (const auto& entity : entities_)
			{
				entity->Update(deltaTime);
			}

			// Move the cam to follow the player
			sf::View view = window_.getView();
			sf::Vector2f viewPos = view.getCenter();
			view.setCenter(player->getPosition().x, viewPos.y);
			window_.setView(view);
		}

		// Rendering
		window_.clear(sf::Color::Black);

		// Render all the entities
		for (const auto& entity : entities_)
		{
			window_.draw(*entity);
		}
		window_.draw(ground);

		if (drawColliders_)
		{
			drawColliders();
		}

		if (GameManager::GetInstance()->GetState() == GameState::Winning)
		{
			sf::Vector2f oldPos = text.getPosition();
			// minus 5 on the player pos to aproximatively center the text. Idk why the origin is not in the center
			text.setPosition(player->getPosition().x - 5, oldPos.y);
			window_.draw(text);
		}

		window_.display();
	}
}

void Game::drawColliders()
{
	for (const auto& entity : entities_)
	{
		drawBody(entity->GetBody());
	}
}

void Game::drawBody(b2Body* body)
{
	b2Fixture* fixture = body->GetFixtureList();
	while (fixture != nullptr)
	{
		b2Shape* shape = fixture->GetShape();
		const auto polygonShape = dynamic_cast<b2PolygonShape*>(shape);
		sf::ConvexShape convex;
		convex.setPointCount(4);
		for (int j = 0; j < 4; j++)
		{
			b2Vec2 point = polygonShape->m_vertices[j];
			auto worldPoint = body->GetWorldPoint(point);
			convex.setPoint(j, Box2dVecToSfml(worldPoint));
		}
		convex.setFillColor(sf::Color::Transparent);
		convex.setOutlineColor(sf::Color::Red);
		convex.setOutlineThickness(0.1f);
		window_.draw(convex);
		fixture = fixture->GetNext();
	}
}
