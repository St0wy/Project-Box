#include "Game.h"
#include "Consts.h"

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

	// Create ball
	b2BodyDef ballBodyDef;
	ballBodyDef.type = b2_dynamicBody;
	ballBodyDef.position.Set(0.0f, 4.0f);
	b2Body* ballBody = world_.CreateBody(&ballBodyDef);
	b2PolygonShape ballDynamicBox;
	ballDynamicBox.SetAsBox(1.0f, 1.0f);

	// Create ball fixture
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &ballDynamicBox;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;

	ballBody->CreateFixture(&fixtureDef);

	// Create ball sfml
	sf::CircleShape ballCircleShape;
	ballCircleShape.setFillColor(sf::Color::Red);
	ballCircleShape.setRadius(0.5f);

	// Create ground shape
	sf::RectangleShape groundRectangleShape;
	groundRectangleShape.setSize(sf::Vector2f(2, 2));
	b2Vec2 groundPos = groundBody->GetPosition();
	b2Vec2 groundOrig = groundBody->GetWorldCenter();
	groundRectangleShape.setOrigin(groundOrig.x, -groundOrig.y);
	groundRectangleShape.setPosition(groundPos.x, -groundPos.y);
	groundRectangleShape.setFillColor(sf::Color::Magenta);

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
		b2Vec2 boxPos = ballBody->GetPosition();
		ballCircleShape.setPosition(boxPos.x, -boxPos.y);

		// Rendering
		window_.clear(sf::Color::Black);

		// Render all the entities
		window_.draw(ballCircleShape);
		window_.draw(groundRectangleShape);

		window_.display();
	}
}
