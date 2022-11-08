// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
// (c) 2022 Media Design School
//
// File Name: CWall.cpp
// Description: CWall declaration file
// Authors: Michael Wai Kit Tran

#include "CWall.h"
#include "Box2D/box2d.h"
#include "CPhysicsBody.h"
#include "CManager.h"
#include "CBullet.h"
#include "CSound.h"

std::shared_ptr<sf::Texture> CWall::breakableWallTexture;
std::shared_ptr<sf::Texture> CWall::breakableWallTexture1;
std::shared_ptr<sf::Texture> CWall::breakableWallTexture2;
std::shared_ptr<sf::Texture> CWall::unbreakableWallTexture;

CWall::CWall(sf::Vector2f _pos, float _rotation, bool _isBreakable)
{
    isBreakable = _isBreakable;
    health = 3.0f;
    if (!isBreakable)
    {
        objType = MapPlaceableObjects::UnbreakableWall;
    }
    else
    {
        objType = MapPlaceableObjects::BreakableWall;
    }

    // setup textures
    if (breakableWallTexture.get() == nullptr)
    {
        breakableWallTexture = std::make_shared<sf::Texture>();
        breakableWallTexture->loadFromFile("Assets/Sprites/tileSprites/box_5.png");

        breakableWallTexture1 = std::make_shared<sf::Texture>();
        breakableWallTexture1->loadFromFile("Assets/Sprites/tileSprites/box_5_1.png");

        breakableWallTexture2 = std::make_shared<sf::Texture>();
        breakableWallTexture2->loadFromFile("Assets/Sprites/tileSprites/box_5_2.png");
    }
    if (unbreakableWallTexture.get() == nullptr)
    {
        unbreakableWallTexture = std::make_shared<sf::Texture>();
        unbreakableWallTexture->loadFromFile("Assets/Sprites/tileSprites/metalCrate.png");
    }

    // setup sf::Drawable
    drawable = new sf::RectangleShape(sf::Vector2f(32.0f, 32.0f));
    rectangleShape = (sf::RectangleShape*)drawable;
    rectangleShape->setTexture(isBreakable ? breakableWallTexture.get() : unbreakableWallTexture.get());
    
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

    // setup b2Body
    SetupBody(bodyDef, &fixtureDef, 1);

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

    //change texture based on health
    if (health <= 2)
    {
        rectangleShape->setTexture(isBreakable ? breakableWallTexture1.get() : unbreakableWallTexture.get());
    }
    if (health <= 1)
    {
        rectangleShape->setTexture(isBreakable ? breakableWallTexture2.get() : unbreakableWallTexture.get());
    }

    // delete the wall if it has no health
    if (health <= 0)
    {
        GetManager().ReplaceWithGround(this);
        new CSound("wallBreak.wav");
        DeleteObject();
    }
}
