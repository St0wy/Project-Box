#include <box2d/box2d.h>
#include <SFML/Graphics.hpp>

#include "Consts.h"

int main()
{
#pragma region SETUP
	// Create render window
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_NAME, sf::Style::Close);
	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(FRAMERATE);

	// Create view (camera) of the scene and set it to the window
	sf::View view(sf::Vector2f(0, -2), sf::Vector2f(CAM_WIDTH, CAM_HEIGHT));
	window.setView(view);

	// Create box2d world
	const b2Vec2 gravity(0.0f, GRAVITY_STRENGHT);
	b2World world(gravity);

	// Create ground
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0.0f, -10.0f);
	b2Body* groundBody = world.CreateBody(&groundBodyDef);
	b2PolygonShape groundBox;
	groundBox.SetAsBox(50.0f, 10.0f);
	groundBody->CreateFixture(&groundBox, 0.0f);
#pragma endregion

	// Create ball
	b2BodyDef ballBodyDef;
	ballBodyDef.type = b2_dynamicBody;
	ballBodyDef.position.Set(0.0f, 4.0f);
	b2Body* ballBody = world.CreateBody(&ballBodyDef);
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
	while (window.isOpen())
	{
		sf::Time deltaTime = clock.restart();
		sf::Event event{};

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		world.Step(PHYSICS_STEP, VELOCITY_ITERATIONS, POSITION_ITERATIONS);
		b2Vec2 boxPos = ballBody->GetPosition();
		ballCircleShape.setPosition(boxPos.x, -boxPos.y);

		// Rendering
		window.clear(sf::Color::Black);

		// Render all the entities
		window.draw(ballCircleShape);
		window.draw(groundRectangleShape);

		window.display();
	}
}