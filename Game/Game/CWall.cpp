#include "CWall.h"
#include "Box2D/box2d.h"
#include "CPhysicsBody.h"
#include "CManager.h"

//[Delete later on] Tag of the wall has been changed from "UnbreakableWall" to "Wall"
CWall::CWall(sf::Vector2f _pos, float _rotation, bool _isBreakable)
{
    isBreakable = _isBreakable;
    health = -1.0f;
    objType = MapPlaceableObjects::UnbreakableWall;

    // setup sf::Drawable
    drawable = new sf::RectangleShape(sf::Vector2f(32.0f, 32.0f));
    sf::RectangleShape* rectangleShape = (sf::RectangleShape*)drawable;
    rectangleShape->setFillColor(sf::Color().Black);

    //The the origin of the SFML transform
    transform.setOrigin(rectangleShape->getSize() / 2.0f);
    transform.setPosition(_pos);
    transform.setRotation(_rotation);

    // setup b2BodyDef
    physicsBody = new CPhysicsBody;
    b2BodyDef bodyDef;
    bodyDef.type = b2_staticBody;
    bodyDef.position = GetManager().pixelToWorldScale * b2Vec2(transform.getPosition().x, transform.getPosition().y);

    // setup b2Shape
    b2PolygonShape shape;
    shape.SetAsBox
    (
        (rectangleShape->getSize().x * GetManager().pixelToWorldScale) / 2.0f,
        (rectangleShape->getSize().y * GetManager().pixelToWorldScale) / 2.0f
    );
    
    // setup b2FixtureDef
    b2FixtureDef fixtureDef;
    fixtureDef.density = 1.0f;
    fixtureDef.shape = &shape;
    fixtureDef.userData.pointer = reinterpret_cast<uintptr_t>(this);

    // setup b2Body
    physicsBody->SetupBody(bodyDef, &fixtureDef, 1); 
    physicsBody->GetBody().GetUserData().pointer = reinterpret_cast<uintptr_t>(this);

    tags.emplace("Wall");
}

void CWall::TakeDamage(float _damage)
{
    health -= _damage;

    //Delete the wall if it is breakable and it have no health
    if (isBreakable && health <= 0) DeleteObject();
}