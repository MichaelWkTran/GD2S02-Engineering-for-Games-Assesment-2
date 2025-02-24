#include "CWall.h"
#include "Box2D/box2d.h"
#include "CPhysicsBody.h"
#include "CManager.h"
#include "CBullet.h"

//[Delete later on] Tag of the wall has been changed from "UnbreakableWall" to "Wall"
CWall::CWall(sf::Vector2f _pos, float _rotation, bool _isBreakable)
{
    isBreakable = _isBreakable;
    health = 10.0f;
    if (!isBreakable)
    {
        objType = MapPlaceableObjects::UnbreakableWall;
    }
    else
    {
        objType = MapPlaceableObjects::BreakableWall;
    }

    // setup sf::Drawable
    drawable = new sf::RectangleShape(sf::Vector2f(32.0f, 32.0f));
    sf::RectangleShape* rectangleShape = (sf::RectangleShape*)drawable;
    if (!isBreakable)
    {
        rectangleShape->setFillColor(sf::Color().Black);
    }
    else
    {
        rectangleShape->setFillColor(sf::Color().Magenta);
    }

    // set the origin of the SFML transform
    transform.setOrigin(rectangleShape->getSize() / 2.0f);
    transform.setPosition(_pos);
    transform.setRotation(_rotation);

    // setup b2BodyDef
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
    SetupBody(bodyDef, &fixtureDef, 1);
    body->GetUserData().pointer = reinterpret_cast<uintptr_t>(this);

    tags.emplace("Wall");
}

void CWall::BeginContact(CPhysicsBody* _other)
{
    // ensure the wall is breakable
    if (!isBreakable) return;

    // check whether the collided object is a bullet
    CBullet* bullet = dynamic_cast<CBullet*>(_other);
    if (bullet == nullptr) return;

    // damage the wall
    health -= bullet->damage;

    // delete the wall if it has no health
    if (health <= 0) DeleteObject();
}
