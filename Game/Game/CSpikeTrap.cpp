#include "CSpikeTrap.h"
#include "CPhysicsBody.h"
#include "Box2D/box2d.h"
#include "CManager.h"
#include "CPlayer.h"

float CSpikeTrap::damage = 1.0f;

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
    fixtureDef.isSensor = true;
    fixtureDef.density = 1.0f;
    fixtureDef.shape = &shape;

    // setup b2Body
    physicsBody->SetupBody(bodyDef, &fixtureDef, 1);
    physicsBody->GetBody().GetUserData().pointer = reinterpret_cast<uintptr_t>(this);

    tags.emplace("SpikeTrap");
}

void CSpikeTrap::Update()
{
    // gradually damage the player
    for (b2ContactEdge* edge = physicsBody->GetBody().GetContactList(); edge; edge = edge->next)
    {
        CPlayer* player = nullptr;
        
        // Get the object that the trap has collided with
        {
            b2Contact* contact = edge->contact;
            player = static_cast<CPlayer*>
            (
                (void*)contact->GetFixtureA()->GetUserData().pointer != this ?
                (void*)contact->GetFixtureA()->GetUserData().pointer :
                (void*)contact->GetFixtureB()->GetUserData().pointer
            );
        }
        

        // if the found object is not a player, ignore it
        if (player == nullptr) continue;

        // damage the player
        player->health -= GetManager().deltatime * damage;
    }
}
