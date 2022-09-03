#include "CGround.h"

CGround::CGround(sf::Vector2f _pos)
{
    objType = MapPlaceableObjects::Ground;
    // setup sf::Drawable
    drawable = new sf::RectangleShape(sf::Vector2f(32.0f, 32.0f));
    sf::RectangleShape* rectangleShape = (sf::RectangleShape*)drawable;
    rectangleShape->setFillColor(sf::Color(255, 136, 77, 255));

    //The the origin of the SFML transform
    transform.setOrigin(sf::Vector2f(rectangleShape->getSize().x, rectangleShape->getSize().y) / 2.0f);
    transform.setPosition(_pos);
}
