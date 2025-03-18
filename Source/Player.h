#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>


class Player 
{
    private:
        sf::RectangleShape shape;
        float w, h, x, y;
        int score = 0;
        void initShape();
        void initVariables(float w, float h, float x, float y);

    public:
        Player(float w, float h, float x, float y);
        ~Player();

        float getY();
        float getH();
        int getScore();
        void setY(float y);
        void addScore();
        
        void render(sf::RenderTarget& target);
    
};
