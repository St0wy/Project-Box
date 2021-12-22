#pragma once

#include <box2d/box2d.h>
#include <SFML/Graphics.hpp>

/**
 * \brief An entity in the world. The base class for everything that is drawn on screen.
 */
class Entity
	: public sf::Drawable, public sf::Transformable
{
public:
	/**
	 * \brief Creates a new entity.
	 * \param world The box2d world where the body will be created.
	 */
	explicit Entity(b2World& world);

	/**
	 * \brief Destroys the entity. Also removes the body from the world.
	 */
	~Entity() override;

	/**
	 * \brief Gets the body.
	 * \return A pointer to the body of that entity.
	 */
	b2Body* getBody() const;

	/**
	 * \brief Sets the texture.
	 * \param texture The new texture.
	 * \param textureRect The area of that should be used in the texture.
	 */
	void setTexture(const sf::Texture& texture, const sf::IntRect& textureRect);

	/**
	 * \brief Sets the texture.
	 * \param texture The new texture.
	 */
	void setTexture(const sf::Texture& texture);

	/**
	 * \brief Gets the sprite.
	 * \return A reference to the sprite of that entity.
	 */
	sf::Sprite& getSprite();

	/**
	 * \brief The update function that is called at each frame.
	 * \param deltaTime Time elapsed since the last frame.
	 */
	virtual void update(sf::Time deltaTime);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
protected:
	b2World& world_;
	b2Body* body_;
	sf::Sprite sprite_;
};