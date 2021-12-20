#pragma once
#include "Entity.h"

class Ground final : public Entity
{
public:
	Ground(b2World& world, float groundHalfWidth, float groundHalfHeight, b2Vec2 position);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
private:
	sf::RectangleShape shape_;
};
