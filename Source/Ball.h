#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>


class Ball
{
    private:
        sf::CircleShape shape;
        float speed = 7;
        float radius;
        float horizontalDir = -1; //-1 = left, 1 = right
        float verticalDir = -1; //-1 = up, 1 = down

        void initShape(float x, float y, float radius);

    public:
        Ball(float x, float y, float radius);
        ~Ball();

        float getX();
        float getY();
        float getSpeed();
        float getHorizontalDir();
        float getVerticalDir();
        const float getRadius() const;

        void setPosition2(float x, float y);
        void setSpeed(float speed);
        void setHorizontalDir(float dir);
        void setVerticalDir(float dir);

        void render(sf::RenderTarget& target);
    
};