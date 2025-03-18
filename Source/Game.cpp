#include "Game.h"


void Game::initVariables()
{
    this->window = nullptr;
}

void Game::initWindow()
{
    this->videoMode = sf::VideoMode(this->screenWidth, this->screenHeight);
    this->window = new sf::RenderWindow(this->videoMode, "Pong Clone by Kildoes", sf::Style::Titlebar | sf::Style::Close);
    this->window->setFramerateLimit(90);
}

void Game::initFont()
{
    if (!this->bitFont.loadFromFile("bit5x3.ttf"))
    {
        std::cout << "Font did not load...\n";
    }
}

void Game::initText()
{
    this->p1score.setFont(this->bitFont);
    this->p2score.setFont(this->bitFont);
    this->pausedText.setFont(this->bitFont);
    this->countdownText.setFont(this->bitFont);

    this->p1score.setPosition({ 540 - 5 * this->textSize / 2, 100 });
    this->p1score.setCharacterSize(this->textSize);
    this->p1score.setString(std::to_string(this->player1.getScore()));

    this->p2score.setPosition({ 540 + 2 * this->textSize, 100 });
    this->p2score.setCharacterSize(this->textSize);
    this->p2score.setString(std::to_string(this->player2.getScore()));
    this->p2score.setFillColor(sf::Color::White);

    this->pausedText.setPosition({ 351, 540 });
    this->pausedText.setCharacterSize(this->textSize);
    this->pausedText.setString("Press P to play");
    this->pausedText.setFillColor(sf::Color::White);

    this->countdownText.setPosition({ 526, 540 });
    this->countdownText.setCharacterSize(this->textSize);
    this->countdownText.setFillColor(sf::Color::White);
}

void Game::initSound()
{
    if (!this->hitPaddle.loadFromFile(".\\Sounds\\hitPaddle.wav"))
    {
        std::cout << "ERROR::Game::initSound(): Couldn't load `\\Sounds\\hitPaddle.wav`\n";
    }
    if (!this->hitWall.loadFromFile(".\\Sounds\\hitWall.wav"))
    {
        std::cout << "ERROR::Game::initSound(): Couldn't load `\\Sounds\\hitWall.wav`\n";
    }
    else
    {
        this->soundWall.setBuffer(this->hitWall);
    }
    if (!this->p1scoreSound.loadFromFile(".\\Sounds\\p1score.wav"))
    {
        std::cout << "ERROR::Game::initSound(): Couldn't load `\\Sounds\\p1score.wav`\n";
    }
    if (!this->p2scoreSound.loadFromFile(".\\Sounds\\p2score.wav"))
    {
        std::cout << "ERROR::Game::initSound(): Couldn't load `\\Sounds\\p2score.wav`\n";
    }
}

Game::Game()
{
    this->initWindow();
    this->initFont();
    this->initText();
    this->initSound();
}

Game::~Game()
{
    delete this->window;
    delete this->ball;
}

const bool Game::isWindowOpen() const
{
    return this->window->isOpen();
}

void Game::sleep(float seconds)
{
    sf::Clock clock;
    sf::Time time = sf::milliseconds(1000 * seconds);
    while (true)
    {
        Sleep(20);
        this->update();
        this->render();
        if (time.asMilliseconds() - clock.getElapsedTime().asMilliseconds() < 0)
        {
            return;
        }
    }
}

void Game::countdown()
{
    this->countdownStatus = true;
    this->paused = true;
    this->pausedText.setString(" ");
    this->countdownText.setString("3");
    this->render();
    this->sleep(1);
    this->countdownText.setString("2");
    this->render();
    this->sleep(1);
    this->countdownText.setString("1");
    this->render();
    this->sleep(0.8);
    this->countdownText.setString("GO!");
    this->render();
    this->sleep(0.8);
    this->countdownText.setString(" ");
    this->countdownStatus = false;
    this->paused = false;
}



void Game::pollEvent()
{
    bool exit = false;
    while (this->window->pollEvent(this->e))
    {
        switch (this->e.type)
        {
            case sf::Event::Closed:
            this->window->close();
            exit = true;
            break;
            case sf::Event::KeyPressed:
            if (this->e.key.code == sf::Keyboard::Escape)
            {
                this->window->close();
                exit = true;
            }
            else if (this->e.key.code == sf::Keyboard::P)
            {
                if (this->paused) 
                {
                    if (!this->countdownStatus)
                    {
                        this->countdown();
                    }
                }
                else
                {
                    this->pausedText.setString("Press P to Play");
                    this->paused = true;
                }
            }
            break;
        }
    }
    if (exit)
    {
        std::cout << "The score is " << this->player1.getScore() << " : " << this->player2.getScore() << '\n';
        if (this->player1.getScore() > this->player2.getScore())
        {
            std::cout << "Player 1 Wins!\n";
        }
        else if (this->player2.getScore() > this->player1.getScore())
        {
            std::cout << "Player 2 Wins!\n";
        }
        else
        {
            std::cout << "It's a Draw!\n";
        }
    }
}

void Game::updateMovement()
{
    float x1 = this->p1x;
    float y1 = this->player1.getY();
    float x2 = this->p2x;
    float y2 = this->player2.getY();
    float bx = this->ball->getX();
    float by = this->ball->getY();
    float speed = this->ball->getSpeed();
    float r = this->ball->getRadius();


    //Ball Vertical Direction
    if (by < r)
    {
        this->ball->setVerticalDir(1); //Up -> Down
        this->soundWall.play();
    }
    else if (by > this->screenHeight - 2 * r)
    {
        this->ball->setVerticalDir(-1); //Down -> Up
        this->soundWall.play();
    }

    //Player 1
    if (y1 < 0)
    {
        this->player1.setY(0);
    }
    else if (y1 > this->screenHeight - this->playerHeight)
    {
        this->player1.setY(this->screenHeight - this->playerHeight);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        if (y1 > 0)
        {
            this->player1.setY(y1 - 20);
        }
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        if (y1 < this->screenHeight - this->playerHeight)
        {
            this->player1.setY(y1 + 20);
        }
    }

    //Player 2
    if (y2 < 0)
    {
        this->player2.setY(0);
    }
    else if (y2 > this->screenHeight - this->playerHeight)
    {
        this->player2.setY(this->screenHeight - this->playerHeight);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        if (y2 > 0)
        {
            this->player2.setY(y2 - 20);
        }
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        if (y2 < this->screenHeight - this->playerHeight)
        {
            this->player2.setY(y2 + 20);
        }
    }
    
    if (this->ball->getHorizontalDir() == -1) //Left
    {   
        if (x1 <= bx && bx <= x1 + this->playerWidth && y1 - r <= by && by <= y1 + this->playerHeight - r)
        {
            this->ball->setHorizontalDir(1); //Left -> Right
            this->sound.setBuffer(this->hitPaddle);
            this->sound.play();
            if (speed < 15)
            {
                this->ball->setSpeed(speed + 0.5);
            }
        }
        else if (x1 > bx)
        {
            this->ball = new Ball(this->screenWidth / 2 - r, this->screenHeight / 2 - r, r);
            this->sound.setBuffer(this->p2scoreSound);
            this->sound.play();
            this->player2.addScore();
            this->p2score.setString(std::to_string(this->player2.getScore()));
            this->ball->setHorizontalDir(1);
            this->ball->setSpeed(7);
            this->countdown();
        }
        else
        {
            this->ball->setPosition2(bx - speed, by + speed * this->ball->getVerticalDir());
        }
    }
    else //Right
    {
        if (x2 - this->playerWidth <= bx && bx <= x2 && y2 - r <= by && by <= y2 + this->playerHeight - r)
        {
            this->ball->setHorizontalDir(-1); //Right -> Left
            this->sound.setBuffer(this->hitPaddle);
            this->sound.play();
            if (speed < 15)
            {
                this->ball->setSpeed(speed + 0.5);
            }
        }
        else if (bx > x2 + r)
        {
            this->ball = new Ball(this->screenWidth / 2 - r, this->screenHeight / 2 - r, r);
            this->player1.addScore();
            this->sound.setBuffer(this->p1scoreSound);
            this->sound.play();
            this->p1score.setString(std::to_string(this->player1.getScore()));
            this->ball->setHorizontalDir(-1);
            this->ball->setSpeed(7);
            this->countdown();
        }
        else
        {
            this->ball->setPosition2(bx + speed, by + speed * this->ball->getVerticalDir());
        }
    }
}

void Game::update()
{
    if (!this->paused && !this->countdownStatus)
    {
        this->updateMovement();
    }
    this->pollEvent();
}

void Game::render()
{
    this->window->clear(sf::Color::Black);
    this->player1.render(*this->window);
    this->player2.render(*this->window);
    this->ball->render(*this->window);
    this->window->draw(this->p1score);
    this->window->draw(this->p2score);
    this->window->draw(this->pausedText);
    this->window->draw(this->countdownText);
    this->window->display();
}
