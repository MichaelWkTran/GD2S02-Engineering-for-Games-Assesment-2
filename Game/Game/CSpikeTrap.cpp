#include "CSpikeTrap.h"
#include "CPhysicsBody.h"
#include "Box2D/box2d.h"
#include "CManager.h"

float CSpikeTrap::damage = 10.0f;

CSpikeTrap::CSpikeTrap(sf::Vector2f _pos)
{
    // setup sf::Drawable
    drawable = new sf::RectangleShape(sf::Vector2f(32.0f, 32.0f));
    sf::RectangleShape* rectangleShape = (sf::RectangleShape*)drawable;
    rectangleShape->setFillColor(sf::Color().Red);

    //The the origin of the SFML transform
    transform.setOrigin(rectangleShape->getSize() / 2.0f);
    transform.setPosition(_pos);

    // setup b2BodyDef
    physicsBody = new CPhysicsBody;
    physicsBody->bodyDef.type = b2_staticBody;

    // setup b2Shape
    physicsBody->SetupShape<b2PolygonShape>();
    b2PolygonShape* pPolygonShape = (b2PolygonShape*)&physicsBody->GetShape();
    pPolygonShape->SetAsBox
    (
        (rectangleShape->getSize().x * GetManager().pixelToWorldScale) / 2.0f,
        (rectangleShape->getSize().y * GetManager().pixelToWorldScale) / 2.0f
    );
    // setup b2Shape
    physicsBody->bodyDef.position = b2Vec2(transform.getPosition().x * GetManager().pixelToWorldScale, transform.getPosition().y * GetManager().pixelToWorldScale);

    // setup b2FixtureDef
    physicsBody->fixtureDef.isSensor = true;
    physicsBody->fixtureDef.density = 1.0f;

    // setup b2Body
    physicsBody->SetupBody();
    physicsBody->GetBody().SetFixedRotation(true);
    physicsBody->GetBody().GetUserData().pointer = (uintptr_t)static_cast<void*>(this);

    // setup b2Body
    physicsBody->SetupBody();

    tags.emplace("SpikeTrap");
}
