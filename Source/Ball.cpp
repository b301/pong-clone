#include "Ball.h"


void Ball::initShape(float x, float y, float radius)
{
    this->radius = radius;
    this->shape.setRadius(this->radius);
    this->shape.setFillColor(sf::Color::White);
    this->shape.setPosition({ x - this->radius, y - this->radius });
}

Ball::Ball(float x, float y, float radius)
{
    this->initShape(x, y, radius);
}

Ball::~Ball()
{
    
}

float Ball::getX()
{
    return this->shape.getPosition().x;
}

float Ball::getY()
{
    return this->shape.getPosition().y;
}

float Ball::getSpeed()
{
    return this->speed;
}

float Ball::getHorizontalDir()
{
    return this->horizontalDir;
}

float Ball::getVerticalDir()
{
    return this->verticalDir;
}

const float Ball::getRadius() const
{
    return this->radius;
}

void Ball::setPosition2(float x, float y)
{
    this->shape.setPosition({ x, y });
}

void Ball::setSpeed(float speed)
{
    this->speed = speed;
}

void Ball::setHorizontalDir(float dir)
{
    this->horizontalDir = dir;
}

void Ball::setVerticalDir(float dir)
{
    this->verticalDir = dir;
}

void Ball::render(sf::RenderTarget& target)
{
    target.draw(this->shape);
}