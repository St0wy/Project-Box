#pragma once

#include <box2d/box2d.h>
#include <SFML/Graphics.hpp>

class Entity
	: public sf::Drawable, public sf::Transformable
{
protected:
	b2Body* body_;
	sf::Sprite sprite_;
public:
	Entity();
	explicit Entity(b2World& world);

	b2Body* getBody() const;
	void setBody(b2Body* body);

	void setTexture(const sf::Texture& texture, const sf::IntRect& textureRect);
	void setTexture(const sf::Texture& texture);

	sf::Sprite& getSprite();

	virtual void update(sf::Time deltaTime);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};