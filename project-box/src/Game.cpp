#include "Game.h"
#include "Consts.h"
#include "Entity.h"
#include "Player.h"
#include "PlayerContactListener.h"
#include "Ground.h"
#include "Block.h"
#include "FinishLine.h"
#include "GameManager.h"
#include "VecUtils.h"

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

void Game::Update()
{
	constexpr float groundHalfWidth = 50.0f;
	constexpr float groundHalfHeight = 10.0f;

	// Create ground
	Ground ground(world_, groundHalfWidth, groundHalfHeight, b2Vec2(groundHalfWidth - 5, -15.0f));

	// Create block
	//entities_.emplace_back(std::make_unique<Block>(world_, b2Vec2(5.0f, 0.0f)));

	// Create finish line
	//entities_.emplace_back(std::make_unique<FinishLine>(world_, b2Vec2(15.0f, 0.0f)));

	// Create player
	//entities_.emplace_back(std::make_unique<Player>(world_));
	//auto player = dynamic_cast<Player*>(entities_[2].get());

	PlayerContactListener playerContactListener;
	world_.SetContactListener(&playerContactListener);

	// Winning text
	sf::Font upheav;
	if(!upheav.loadFromFile(FONT_PATH))
	{
		std::cout << "Error loading font\n";
	}

	sf::Text text;
	text.setFont(upheav);
	text.setString("You Win");
	text.setFillColor(sf::Color::Red);
	//center text
	//sf::FloatRect textRect = text.getLocalBounds();
	//text.setOrigin(textRect.left + textRect.width / 2.0f,
	//	textRect.top + textRect.height / 2.0f);
	//text.setPosition(sf::Vector2f(WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f));
	text.setCharacterSize(24);
	text.setPosition(0,0);

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

		// Only update with focus
		//if (window_.hasFocus() && GameManager::GetInstance()->GetState() == GameState::Playing)
		//{
		//	// Step the physics
		//	world_.Step(PHYSICS_STEP, VELOCITY_ITERATIONS, POSITION_ITERATIONS);

		//	// Update the entites

		//	for (const auto& entity : entities_)
		//	{
		//		entity->Update(deltaTime);
		//	}

		//	// Move the cam to follow the player
		//	//sf::View view = window_.getView();
		//	//sf::Vector2f viewPos = view.getCenter();
		//	//view.setCenter(player->getPosition().x, viewPos.y);
		//	//window_.setView(view);
		//}

		// Rendering
		window_.clear(sf::Color::Black);

		// Render all the entities
		window_.draw(text);
		//for (const auto& entity : entities_)
		//{
		//	window_.draw(*entity);
		//}
		//window_.draw(ground);

		//if (drawColliders_)
		//{
		//	DrawColliders();
		//}
		//window_.draw(text);

		//if (GameManager::GetInstance()->GetState() == GameState::Winning)
		//{
		//}

		window_.display();
	}
}

void Game::DrawColliders()
{
	for (const auto& entity : entities_)
	{
		DrawBody(entity->GetBody());
	}
}

void Game::DrawBody(b2Body* body)
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
