#include "Game.h"
#include "Consts.h"
#include "Entity.h"
#include "Player.h"
#include "PlayerContactListener.h"
#include "Ground.h"
#include "RessourceManager.h"
#include "Block.h"
#include "VecUtils.h"

Game::Game()
	: window_(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_NAME, sf::Style::Close),
	gravity_(0.0f, GRAVITY_STRENGHT),
	world_(gravity_)
{
	window_.setVerticalSyncEnabled(true);
	window_.setFramerateLimit(FRAMERATE);

	// Create view (camera) of the scene and set it to the window
	window_.setView(sf::View(sf::Vector2f(0, -2), sf::Vector2f(CAM_WIDTH, CAM_HEIGHT)));

	// Create box2d world
	const b2Vec2 gravity(0.0f, GRAVITY_STRENGHT);
	b2World world(gravity);
}

void Game::Update()
{
	constexpr float groundHalfWidth = 50.0f;
	constexpr float groundHalfHeight = 10.0f;
	constexpr float factor = 2.0f / 16.0f;

	// Create ground
	Ground ground(world_, groundHalfWidth, groundHalfHeight, b2Vec2(groundHalfWidth - 5, -15.0f));

	// Create block
	Block block(world_, b2Vec2(5.0f, 0.0f));
	block.setScale(factor, factor);

	// Create player
	auto playerTextureResult = RessourceManager::GetInstance()->GetTexture(SPRITESHEET_PATH);
	sf::Texture* playerTexture = playerTextureResult.value();

	Player player(world_);
	player.setScale(factor, factor);
	player.SetTexture(*playerTexture, sf::IntRect(0, 80, 16, 16));

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
		block.Update(deltaTime);
		sf::View view = window_.getView();
		sf::Vector2f viewPos = view.getCenter();
		view.setCenter(player.getPosition().x, viewPos.y);
		window_.setView(view);

		// Rendering
		window_.clear(sf::Color::Blue);

		// Render all the entities
		window_.draw(player);
		window_.draw(ground);
		window_.draw(block);

		if (drawColliders_)
		{
			// Draw player
			auto body = player.GetBody();
			b2Fixture* fixture = player.GetBody()->GetFixtureList();
			while (fixture != nullptr)
			{
				for (int i = 0; i < 2; i++)
				{
					b2Shape* shape = fixture->GetShape();
					auto polygonShape = dynamic_cast<b2PolygonShape*>(shape);
					sf::ConvexShape convex;
					convex.setPointCount(4);
					for (int j = 0; j < 4; j++)
					{
						b2Vec2 point = polygonShape->m_vertices[j];
						auto worldPoint = player.GetBody()->GetWorldPoint(point);
						convex.setPoint(j, Box2dVecToSfml(worldPoint));
					}
					convex.setFillColor(sf::Color::Transparent);
					convex.setOutlineColor(sf::Color::Red);
					convex.setOutlineThickness(0.1f);
					window_.draw(convex);
				}
				fixture = fixture->GetNext();
			}

		}

		window_.display();
	}
}
