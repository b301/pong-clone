#pragma once

#include <windows.h>
#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

#include "Player.h"
#include "Ball.h"


class Game {
    private:
        sf::RenderWindow* window;
        const float screenWidth = 1080;
        const float screenHeight = 720;
        const float playerHeight = 160;
        const float playerWidth = 20;
        const float p1x = 60;
        const float p2x = 1000;
        const float textSize = 48;
        const float radius = 8;
        sf::VideoMode videoMode;
        sf::Event e;
        Ball* ball = new Ball(this->screenWidth / 2 - this->radius, this->screenHeight / 2 - this->radius, this->radius);
        Player player1 = Player(this->playerWidth, this->playerHeight, this->p1x, 50);
        Player player2 = Player(this->playerWidth, this->playerHeight, this->p2x, 50);

        sf::Font bitFont;
        sf::Text p1score;
        sf::Text p2score;

        sf::Text pausedText;
        sf::Text countdownText;
        bool paused = true;
        bool countdownStatus = false;

        sf::Clock clock;
        sf::SoundBuffer hitPaddle;
        sf::SoundBuffer hitWall;
        sf::SoundBuffer p1scoreSound;
        sf::SoundBuffer p2scoreSound;

        sf::Sound soundWall;
        sf::Sound sound;

        void initVariables();
        void initWindow();
        void initFont();
        void initText();
        void initSound();
        void sleep(float seconds);

    public:
        Game();
        ~Game();

        const bool isWindowOpen() const;

        void pollEvent();
        void updateMovement();
        void update();
        void render();
        void countdown();
};