#include "Player.h"


void Player::initVariables(float w, float h, float x, float y)
{
    this->w = w;
    this->h = h;
    this->x = x;
    this->y = y;
}

void Player::initShape()
{
    this->shape = sf::RectangleShape({ this->w, this->h });
    this->shape.setFillColor(sf::Color::White);
    this->shape.setPosition({ this->x, this->y });
}

Player::Player(float w, float h, float x, float y)
{
    this->initVariables(w, h, x, y);
    this->initShape();
}

Player::~Player()
{
    
}

float Player::getY()
{
    return this->shape.getPosition().y;
}

float Player::getH()
{
    return this->h;
}

int Player::getScore()
{
    return this->score;
}

void Player::setY(float y)
{
    this->shape.setPosition({ this->x, y });
}

void Player::addScore()
{
    this->score++;
}

void Player::render(sf::RenderTarget& target)
{
    target.draw(this->shape);
}

