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
	window_.setView(DEFAULT_VIEW);

	// Create box2d world
	const b2Vec2 gravity(0.0f, GRAVITY_STRENGHT);
	b2World world(gravity);
}

void Game::startMainLoop()
{
#pragma region Locator
	// Init audio locator
	Locator::init();
	auto sfmlAudio = std::make_unique<SfmlAudio>();
	sfmlAudio->init();
	Locator::provide(sfmlAudio.get());

	// Init texture locator
	auto textureService = std::make_unique<TextureService>();
	textureService->init();
	Locator::provide(textureService.get());

	// Init the game manager
	auto gameManager = std::make_unique<GameManager>();
	Locator::provide(gameManager.get());
#pragma endregion

	// Create the entities and get the player
	auto player = createEntities();

	PlayerContactListener playerContactListener;
	world_.SetContactListener(&playerContactListener);

#pragma region Texts
	// Load game font
	sf::Font upheav;
	if (!upheav.loadFromFile(FONT_PATH))
	{
		std::cout << "Error loading font\n";
	}

	// Create win text
	sf::Text winText;
	winText.setFont(upheav);
	winText.setString("You Win");
	winText.setFillColor(sf::Color::Red);
	winText.setCharacterSize(192);
	winText.setScale(SCALE_FACTOR / 8.0f, SCALE_FACTOR / 8.0f);

	// center text
	sf::FloatRect textRect = winText.getLocalBounds();
	winText.setOrigin(textRect.width / 2.0f, textRect.height / 2.0f);
	winText.setPosition(-5, -2);

	// Create replay text
	sf::Text replayText;
	replayText.setFont(upheav);
	replayText.setString("Press space to replay");
	replayText.setFillColor(sf::Color::Red);
	replayText.setCharacterSize(192);
	replayText.setScale(SCALE_FACTOR / 16.0f, SCALE_FACTOR / 16.0f);
	textRect = replayText.getLocalBounds();
	replayText.setOrigin(textRect.width / 2.0f, textRect.height / 2.0f);
	replayText.setPosition(-5, 0);

	// Create dead text
	sf::Text looseText;
	looseText.setFont(upheav);
	looseText.setString("You're Dead");
	looseText.setFillColor(sf::Color::Red);
	looseText.setCharacterSize(192);
	looseText.setScale(SCALE_FACTOR / 8.0f, SCALE_FACTOR / 8.0f);
	textRect = looseText.getLocalBounds();
	looseText.setOrigin(textRect.width / 2.0f, textRect.height / 2.0f);
	looseText.setPosition(-5, -2);
#pragma endregion

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

		// Only startMainLoop with focus
		GameManager* gm = Locator::getGameManager();
		if (window_.hasFocus() && gm->getState() == GameState::Playing)
		{
			// Step the physics
			world_.Step(PHYSICS_STEP, VELOCITY_ITERATIONS, POSITION_ITERATIONS);

			// Update the entites
			for (const auto& entity : entities_)
			{
				entity->update(deltaTime);
			}

			// Move the cam to follow the player
			sf::View view = window_.getView();
			sf::Vector2f viewPos = view.getCenter();
			view.setCenter(player->getPosition().x, viewPos.y);
			window_.setView(view);
		}

		// Clear the window
		window_.clear(sf::Color::Black);

		// Render all the entities
		for (const auto& entity : entities_)
		{
			window_.draw(*entity);
		}

		// Render the colliders
		if (drawColliders_)
		{
			drawColliders();
		}

		if (gm->getState() == GameState::Winning)
		{
			sf::Vector2f oldPos = winText.getPosition();
			winText.setPosition(player->getPosition().x, oldPos.y);

			oldPos = replayText.getPosition();
			replayText.setPosition(player->getPosition().x, oldPos.y);

			window_.draw(winText);
			window_.draw(replayText);
		}
		else if (gm->getState() == GameState::Dead)
		{
			sf::Vector2f oldPos = looseText.getPosition();
			looseText.setPosition(player->getPosition().x, oldPos.y);

			oldPos = replayText.getPosition();
			replayText.setPosition(player->getPosition().x, oldPos.y);

			window_.draw(looseText);
			window_.draw(replayText);

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
			{
				clear();
				player = createEntities();
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) &&
			(gm->getState() == GameState::Dead || gm->getState() == GameState::Winning))
		{
			clear();
			player = createEntities();
		}

		window_.display();
	}
}

void Game::drawColliders()
{
	for (const auto& entity : entities_)
	{
		drawBody(entity->getBody());
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
			convex.setPoint(j, box2dVecToSfml(worldPoint));
		}
		convex.setFillColor(sf::Color::Transparent);
		convex.setOutlineColor(sf::Color::Red);
		convex.setOutlineThickness(0.1f);
		window_.draw(convex);
		fixture = fixture->GetNext();
	}
}

void Game::clear()
{
	// Reset gamestate
	GameManager* gm = Locator::getGameManager();
	gm->setState(GameState::Playing);

	// Reset view
	window_.setView(DEFAULT_VIEW);

	// Clear entities
	entities_.clear();
}

Player* Game::createEntities()
{
	constexpr float groundHalfWidth = 50.0f;
	constexpr float groundHalfHeight = 10.0f;

	// Create ground
	entities_.emplace_back(std::make_unique<Ground>(world_, groundHalfWidth, groundHalfHeight, b2Vec2(groundHalfWidth - 5, -15.0f)));

	// Create block
	entities_.emplace_back(std::make_unique<Block>(world_, b2Vec2(5.0f, 0.0f)));

	// Create finish line
	entities_.emplace_back(std::make_unique<FinishLine>(world_, b2Vec2(15.0f, 0.0f)));

	// Create player, always do the player last
	entities_.emplace_back(std::make_unique<Player>(world_));
	const auto player = dynamic_cast<Player*>(entities_[entities_.size() - 1].get());

	return player;
}
