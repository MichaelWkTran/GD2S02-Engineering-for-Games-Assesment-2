// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
// (c) 2022 Media Design School
//
// File Name: CSpikeTrap.cpp
// Description: CSpikeTrap declaration file
// Authors: Michael Wai Kit Tran

#include "CSpikeTrap.h"
#include "CPhysicsBody.h"
#include "Box2D/box2d.h"
#include "CManager.h"
#include "CPlayer.h"

std::shared_ptr<sf::Texture> CSpikeTrap::spikeTexture;
float CSpikeTrap::damage = 0.5f;

CSpikeTrap::CSpikeTrap(sf::Vector2f _pos)
{
    // setup textures
    if (spikeTexture.get() == nullptr)
    {
        spikeTexture = std::make_shared<sf::Texture>();
        spikeTexture->loadFromFile("Assets/Sprites/tileSprites/Spikes.png");
    }

    // setup sf::Drawable
    drawable = new sf::RectangleShape(sf::Vector2f(32.0f, 32.0f));
    sf::RectangleShape* rectangleShape = (sf::RectangleShape*)drawable;
    rectangleShape->setTexture(spikeTexture.get());

    objType = MapPlaceableObjects::SpikeTrap;

    //The the origin of the SFML transform
    transform.setOrigin(rectangleShape->getSize() / 2.0f);
    transform.setPosition(_pos);

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
    fixtureDef.isSensor = true;
    fixtureDef.density = 1.0f;
    fixtureDef.shape = &shape;

    // setup b2Body
    SetupBody(bodyDef, &fixtureDef, 1);

    tags.emplace("SpikeTrap");
}

void CSpikeTrap::Update()
{
    // gradually damage the player
    for (auto& player : playersCollidedWith)
    {
        if (player->GetDeleteObject())
        {
            playersCollidedWith.erase(player);
            break;
        }
        player->TakeDamage(GetManager().deltaTime * damage);
    }
}

void CSpikeTrap::BeginContact(CPhysicsBody* _contact)
{
    CPlayer* player = dynamic_cast<CPlayer*>(_contact);
    if (player == nullptr) return;

    playersCollidedWith.insert(player);
}

void CSpikeTrap::EndContact(CPhysicsBody* _contact)
{
    CPlayer* player = dynamic_cast<CPlayer*>(_contact);
    if (player == nullptr) return;

    playersCollidedWith.erase(player);
}