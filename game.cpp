#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

// Global window declaration
RenderWindow window(VideoMode(800, 300), "Game Window");
Clock clock1;
// Background class
class Background
{
private:
    Texture background1, background2;
    Sprite sprite, sprite1;

    float speed_background = 0.15f;
    int width_background = 800;

public:
    Background()
    {
        background1.loadFromFile("c:/Users/sbato/Downloads/back1.jpg");
        background2.loadFromFile("c:/Users/sbato/Downloads/back2.jpg");

        sprite.setTexture(background1);
        sprite1.setTexture(background2);

        set_background();
    }

    void reset_background()
    {
        if (sprite.getPosition().x <= (-800))
        {
            sprite.setPosition(width_background, 0);
            cout << "background1   " << sprite.getPosition().x << endl;
        }
        if (sprite1.getPosition().x <= (-800))
        {
            sprite1.setPosition(width_background, 0);
            cout << "background2  " << sprite1.getPosition().x << endl;
        }
    }

    void move_background()
    {
        sprite.move(-speed_background, 0);
        sprite1.move(-speed_background, 0);
        reset_background();
    }

    void set_background()
    {
        sprite.setPosition(0, 0);
        sprite1.setPosition(width_background, 0);
    }

    void draw(RenderWindow &window)
    {
        window.draw(sprite);
        window.draw(sprite1);
    }
};
// class obstacle

class obstacle
{
private:
    int x;

    Texture Barrel;
    Sprite barrel;
    float speed_barrel = 0.2f;
    int width_background = 800;
    const int y = 10; // Ground level
public:
    obstacle()
    {

        Barrel.loadFromFile("c:/Users/sbato/Downloads/bareel.png");
        barrel.setTexture(Barrel);
        set_barrel();
        barrel.setScale(0.1f, 0.08f);
    }
    Sprite &get_barrel()
    {
        return barrel;
    }
    void set_barrel()
    {
        barrel.setPosition(800, 200);
    }
    void draw_Barrel(RenderWindow &window)
    {
        window.draw(barrel);
    }

    void move_Barrel()
    {
        barrel.move(-speed_barrel, 0);
    }
    bool detect_collision(Sprite &player)
    {
        return barrel.getGlobalBounds().intersects(player.getGlobalBounds());
    }
};

// Dino (Player)
class character
{
public:
    float frame_time = 0.2f; // Change frame every 0.2 seconds
    int frameindex = 0;
    int counter;
    Texture Police[6];
    Sprite police;
    Clock clock;

    bool isJumping = false;
    double velocity = 0;
    character()
    {
        Police[0].loadFromFile("C:/Users/sbato/Downloads/runnig char/SalesMan Running00.png");
        Police[1].loadFromFile("C:/Users/sbato/Downloads/runnig char/SalesMan Running02.png");
        Police[2].loadFromFile("C:/Users/sbato/Downloads/runnig char/SalesMan Running04.png");
        Police[3].loadFromFile("C:/Users/sbato/Downloads/runnig char/SalesMan Running06.png");
        Police[4].loadFromFile("C:/Users/sbato/Downloads/runnig char/SalesMan Running08.png");
        Police[5].loadFromFile("C:/Users/sbato/Downloads/runnig char/SalesMan Running10.png");
    }
    Sprite &get_police()
    {
        return police;
    }
    bool get_jump_state()
    {
        return isJumping;
    }
    void change_frame()
    {
        if (clock.getElapsedTime().asSeconds() >= frame_time)
        {
            frameindex = (frameindex + 1) % 6;
            police.setTexture(Police[frameindex]);

            if (isJumping)
            {
                // Debug: Check if jump timing works
                cout << "Elapsed time: " << clock1.getElapsedTime().asSeconds() << endl;

                if (clock1.getElapsedTime().asSeconds() >= 2.1)
                { // Jumping duration
                    police.setPosition(0, 100);
                    isJumping = false; // Reset jumping state
                    clock1.restart();  // Restart jump timer
                }
            }
            else
            {
                police.setPosition(0, 100); // Default position
            }

            police.setScale(0.15f, 0.15f);
            clock.restart(); // Restart frame timer, independent of jumping
        }
    }

    void draw_police(RenderWindow &window)
    {
        window.draw(police);
    }

    void jump()
    {
        if (!isJumping)
        {

            isJumping = true;
        }
    }

    void update_position()
    {
        if (isJumping)
        {

            police.setPosition(police.getPosition().x, 0);
        }
    }
    ~character()
    {
    }
};

// Game class
class Game
{
private:
    bool Game_is_running = true;
    Background background; // Creating an object
    obstacle barrel;
    character police;
    Font font;
    Text gameOverText;
    Text scoreText;
    int score = 0;
    bool obstaclePassed = false;

public:
    Game()
    {
    }

    void loop()
    {
        Event event;
        Clock clock;
        while (window.isOpen())
        {

            while (window.pollEvent(event))
            {
                if (event.type == Event::Closed)
                {
                    window.close();
                }
                if (event.type == Event::KeyPressed && event.key.code == Keyboard::Space)
                    police.jump();
            }
            if (barrel.detect_collision(police.police))
            {
                Game_is_running = false;
            }


            if (Game_is_running)
            {

                background.move_background(); // Move the background
                barrel.move_Barrel();

                window.clear();

                background.draw(window); // Draw the background
                barrel.draw_Barrel(window);
                // Update character position every frame
                police.update_position();

                police.change_frame();

                police.draw_police(window);

                window.display();
            }
        }
    }
};

int main()
{
    Game game;
    game.loop();
    return 0;
}
