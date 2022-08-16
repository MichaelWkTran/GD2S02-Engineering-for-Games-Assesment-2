#include "CPlayer.h"
#include "CManager.h"
#include "CPhysicsBody.h"

CPlayer::CPlayer()
{
	health = 100.0f;
	moveSpeed = 6.0f;
	coolDown = 0.0f;

    // setup CGameObject
	float radius = 16.0f;

    // set the origin of the SFML transform
	transform.setOrigin(sf::Vector2f(radius, radius));

    // setup sf::Drawable
	//m_pDrawable = new sf::RectangleShape(sf::Vector2f(radius, radius) * 2.0f);
	//((sf::RectangleShape*)m_pDrawable)->setFillColor(sf::Color().Red);
    drawable = new sf::CircleShape(radius);
    sf::CircleShape* pSFCircleShape = (sf::CircleShape*)drawable;
    pSFCircleShape->setFillColor(sf::Color().Red);

    // setup b2BodyDef
    physicsBody = new CPhysicsBody;
    physicsBody->m_BodyDef.type = b2_dynamicBody;

    //m_pPhysicsBody->m_BodyDef.position.x = 100.0f * GetManager().pixelToWorldScale;
    //m_pPhysicsBody->m_BodyDef.position.y = 100.0f * GetManager().pixelToWorldScale;

    // setup b2Shape
    physicsBody->SetupShape<b2CircleShape>();
    physicsBody->GetShape().m_radius = radius * GetManager().pixelToWorldScale;

    // setup b2FixtureDef
    physicsBody->m_FixtureDef.density = 1.0f;

    // setup b2Body
    physicsBody->SetupBody();
}

CPlayer::~CPlayer()
{
}

void CPlayer::Update()
{
    b2Vec2 movement = b2Vec2
    (
        sf::Keyboard::isKeyPressed(sf::Keyboard::Right) - sf::Keyboard::isKeyPressed(sf::Keyboard::Left), 
        sf::Keyboard::isKeyPressed(sf::Keyboard::Down) - sf::Keyboard::isKeyPressed(sf::Keyboard::Up)
    );
    movement.Normalize();
    movement *= moveSpeed;
    
    physicsBody->GetBody().SetLinearVelocity(movement);
}
