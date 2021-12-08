#pragma once
#include <box2d/b2_body.h>
#include <SFML/Graphics/RectangleShape.hpp>

class Ground final : public sf::Drawable
{
private:
	b2Body* body_;
	sf::RectangleShape shape_;
public:
	Ground(b2World& world, float groundHalfWidth, float groundHalfHeight, b2Vec2 position);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	b2Body* GetBody() const;
};
