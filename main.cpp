#include <iostream>
#include <SFML/Graphics.hpp>
#include "map.h" //подключили код с картой

#include <cmath> // Include the cmath library for the sqrt function
using namespace sf;






class Map {
public:
    Map() {
        if (!map_image.loadFromFile("images/map.png")) {
            std::cerr << "Failed to load map image!" << std::endl;
        }
        map.loadFromImage(map_image);
        s_map.setTexture(map);
    }

    void drawMap(RenderWindow &window) {
        for (int i = 0; i < HEIGHT_MAP; i++) {
            for (int j = 0; j < WIDTH_MAP; j++) {
                if (TileMap[i][j] == ' ') {
                    s_map.setTextureRect(IntRect(0, 0, 32, 32));
                } else if (TileMap[i][j] == 's') {
                    s_map.setTextureRect(IntRect(32, 0, 32, 32));
                } else if (TileMap[i][j] == '0') {
                    s_map.setTextureRect(IntRect(64, 0, 32, 32));
                }
                s_map.setPosition(j * 32, i * 32);
                window.draw(s_map);
            }
        }
    }

private:
    Image map_image;
    Texture map;
    Sprite s_map;
};



class Enemy {
public:
    Enemy(Texture& texture, Vector2f position) {
        sprite.setTexture(texture);
        sprite.setScale(0.5f, 0.5f);
        sprite.setTextureRect(IntRect(0, 0, 64, 96));
        sprite.setPosition(position);

    }

    FloatRect getGlobalBounds() const {
            return sprite.getGlobalBounds();
        }
    void draw(RenderWindow& window) {
        window.draw(sprite);
    }


    void move(const Vector2f& offset) {
        sprite.move(offset);
    }

    Vector2f getPosition() const {
        return sprite.getPosition();
    }

private:
    Sprite sprite;
};



int main()
{
    RenderWindow window(VideoMode(700, 700), "Game");
        window.setFramerateLimit(60);

        Map map;



    Texture texture;
    if (!texture.loadFromFile("images/image.png")) {
        std::cerr << "Failed to load texture!" << std::endl;
        return 1;
    }

    Sprite sprite;
    sprite.setTexture(texture);
    sprite.setScale(0.5f, 0.5f);
    sprite.setPosition(50, 59);
    sprite.setTextureRect(IntRect(0, 0, 64, 96));
    float currentframe = 0;
    float currentframe1 = 0;
    int speed = 5;
    int nom;
    Clock clock;


    Texture playerTexture;
        if (!playerTexture.loadFromFile("images/hero.png")) {
            std::cerr << "Failed to load player texture!" << std::endl;
            return 1;
        }

        Sprite player1;
        player1.setTexture(playerTexture);
        player1.setScale(1.35f, 1.35f);
        player1.setTextureRect(IntRect(0, 0, 31, 32));
        player1.setPosition(200, 200);

        Texture enemyTexture;
            if (!enemyTexture.loadFromFile("images/vrag.png")) {
                std::cerr << "Failed to load enemy texture!" << std::endl;
                return 1;
            }

            Enemy enemy1(enemyTexture, Vector2f(114, 600)); // Create enemy at specific position
            Enemy enemy2(enemyTexture, Vector2f(470, 600)); // Create another enemy at a different position


    while (window.isOpen())
    {
        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time = time / 800;
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }



        // Вычислить направление каждого врага к игроку
        Vector2f player1Position = player1.getPosition();
        Vector2f spritePosition = sprite.getPosition();
        Vector2f enemyToPlayer = player1Position - enemy1.getPosition();
        Vector2f enemyToPlayer2 = spritePosition - enemy2.getPosition();

        // Нормализовать векторы направления
        float length = std::sqrt(enemyToPlayer.x * enemyToPlayer.x + enemyToPlayer.y * enemyToPlayer.y);
        float length2 = std::sqrt(enemyToPlayer2.x * enemyToPlayer2.x + enemyToPlayer2.y * enemyToPlayer2.y);
        enemyToPlayer /= length;
        enemyToPlayer2 /= length2;

        // Переместить врагов, умножив нормализованный вектор направления на скорость
        float enemySpeed = 1.0f; // Подстройте скорость по необходимости
        enemy1.move(enemyToPlayer * enemySpeed);
        enemy2.move(enemyToPlayer2 * enemySpeed);



        // Движение персонажа

        if (Keyboard::isKeyPressed(Keyboard::A))
        {if ((TileMap[int((sprite.getPosition().y + 32) / 32)][int((sprite.getPosition().x - speed) / 32)] != '0') && (TileMap[int((sprite.getPosition().y + 32) / 32)][int((sprite.getPosition().x - speed) / 32)] != 's'))

            {
            nom = 1;
            currentframe += 0.005 * time;
            if (currentframe > 4)
            {
                currentframe -= 4;
            }
            sprite.setTextureRect(IntRect(int(currentframe) * 64, 96, 64, 96));
            sprite.move(-speed, 0);
        }
        }
        if (Keyboard::isKeyPressed(Keyboard::D))
        { if ((TileMap[int((sprite.getPosition().y + 32) / 32)][int((sprite.getPosition().x + 32 + speed) / 32)] != '0')&&(TileMap[int((sprite.getPosition().y + 32) / 32)][int((sprite.getPosition().x + 32 + speed) / 32)] != 's') )
            {
            nom = 2;
            currentframe += 0.005 * time;
            if (currentframe > 4)
            {
                currentframe -= 4;
            }
            sprite.setTextureRect(IntRect(int(currentframe) * 64, 192, 64, 96));
            sprite.move(speed, 0);
        }
        }
        if (Keyboard::isKeyPressed(Keyboard::W))
        {if ((TileMap[int((sprite.getPosition().y + speed) / 32)][int(sprite.getPosition().x / 32)] != '0') && (TileMap[int((sprite.getPosition().y + speed) / 32)][int(sprite.getPosition().x / 32)] != 's'))
            {
            nom = 3;
            currentframe += 0.005 * time;
            if (currentframe > 4)
            {
                currentframe -= 4;
            }
            sprite.setTextureRect(IntRect(int(currentframe) * 64, 288, 64, 96));
            sprite.move(0, -speed);
        }
        }
        if (Keyboard::isKeyPressed(Keyboard::S))
        {if ((TileMap[int((sprite.getPosition().y + 32 + speed) / 32)][int(sprite.getPosition().x / 32)] != '0') && (TileMap[int((sprite.getPosition().y + 32 + speed) / 32)][int(sprite.getPosition().x / 32)] != 's'))
            {
            nom = 4;
            currentframe += 0.005 * time;
            if (currentframe > 4)
            {
                currentframe -= 4;
            }
            sprite.setTextureRect(IntRect(int(currentframe) * 64, 0, 64, 96));
            sprite.move(0, speed);
        }
        }







        if (Keyboard::isKeyPressed(Keyboard::Left))
        {
            if ((TileMap[int((player1.getPosition().y + 32) / 32)][int((player1.getPosition().x - speed) / 32)] != '0') && (TileMap[int((player1.getPosition().y + 32) / 32)][int((player1.getPosition().x - speed) / 32)] != 's'))

            {
                nom = 5;
                currentframe1 += 0.005 * time;
                if (currentframe1 > 2)
                {
                    currentframe1 -= 2;
                }
                player1.setTextureRect(IntRect(int(currentframe1) * 31, 96, 31, 32));
                player1.move(-speed, 0);
            }
        }
        if (Keyboard::isKeyPressed(Keyboard::Right))
        {
            // Проверка наличия ненулевого следующего элемента по оси X
            if ((TileMap[int((player1.getPosition().y + 32) / 32)][int((player1.getPosition().x + 32 + speed) / 32)] != '0') && (TileMap[int((player1.getPosition().y + 32) / 32)][int((player1.getPosition().x + 32 + speed) / 32)] != 's'))

            {
                nom = 6;
                currentframe1 += 0.005 * time;
                if (currentframe1 > 2)
                {
                    currentframe1 -= 2;
                }
                player1.setTextureRect(IntRect(int(currentframe1) * 31, 32, 31, 32));
                player1.move(speed, 0);
            }
        }
        if (Keyboard::isKeyPressed(Keyboard::Down))
        {if ((TileMap[int((player1.getPosition().y + 32 + speed) / 32)][int(player1.getPosition().x / 32)] != '0') && (TileMap[int((player1.getPosition().y + 32 + speed) / 32)][int(player1.getPosition().x / 32)] != 's'))
            {
            nom = 7;
            currentframe1 += 0.005 * time;
            if (currentframe1 > 2)
            {
                currentframe1 -= 2;
            }
            player1.setTextureRect(IntRect(int(currentframe1) * 31, 64, 31, 32));
            player1.move(0,speed);
        }
        }
        if (Keyboard::isKeyPressed(Keyboard::Up))
        {
           if ((TileMap[int((player1.getPosition().y + speed) / 32)][int(player1.getPosition().x / 32)] != '0' && TileMap[int((player1.getPosition().y + speed) / 32)][int(player1.getPosition().x / 32)] != 's'))
                {
            nom = 8;
            currentframe1 += 0.005 * time;
            if (currentframe1 > 2)
            {
                currentframe1 -= 2;
            }
            player1.setTextureRect(IntRect(int(currentframe1) * 31, 0, 31, 32));
             player1.move(0, -speed);
        }
        }



        window.clear();
        map.drawMap(window);
        window.draw(sprite);  // Нарисовать первого игрока
        window.draw(player1); // Нарисовать второго игрока
        enemy1.draw(window);   // Draw the first enemy
                enemy2.draw(window);   // Draw the second enemy
        window.display();
    }

    return 0;
}

