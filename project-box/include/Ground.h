#pragma once
#include "Entity.h"

/**
 * \brief The ground where the player walks.
 */
class Ground final : public Entity
{
public:
	/**
	 * \brief Creates a ground.
	 * \param world The world where the ground is created in.
	 * \param groundHalfWidth The half width of the ground.
	 * \param groundHalfHeight The half height of the ground.
	 * \param position The position of the ground. It is in the middle of it.
	 */
	Ground(b2World& world, float groundHalfWidth, float groundHalfHeight, b2Vec2 position);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
private:
	sf::RectangleShape shape_;
};
