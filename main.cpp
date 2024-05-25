#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <windows.h>
#include <cstdio>

using namespace sf;

const int height = 22; //висота матриці
const int width = 22; //ширина матриці

int x = 0, y = 20; //позиція героя за матрицею
float x_pos = 0, y_pos = 640, pixel = 32; //позиція героя на екрані

int Maze[width][height] = { //матриця для створення лабіринту, 1 - перешкоди, 0 - вільний шлях
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 1, 1, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 1, 1, 0, 0, 0, 1},
        {1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 0, 0, 1, 0, 0, 1, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 0, 1},
        {1, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 0, 1, 0, 1},
        {1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1},
        {1, 1, 0, 1, 0, 0, 0, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1},
        {1, 0, 0, 1, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1},
        {1, 0, 1, 1, 0, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 1},
        {1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 1, 1, 0, 0, 1},
        {1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 1},
        {1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 1},
        {1, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 1, 0, 0, 0, 1},
        {1, 0, 0, 0, 1, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 1, 0, 1},
        {1, 1, 1, 0, 1, 1, 0, 0, 0, 1, 1, 0, 1, 0, 1, 1, 1, 0, 0, 1, 0, 1},
        {1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 1},
        {1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 1, 0, 1, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 1, 1, 0, 1, 0, 1, 0, 0, 1, 0, 0, 1, 1, 0, 0, 1, 1},
        {1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
};

void Screen(Sprite &maze_sprite, Text &text, RenderWindow &window, Music &music, Clock &time_clock, bool *screen_ptr);

void Finish(Music &music, Sound &finish_sound, Text &text_finish, RenderWindow &window);

void Draw_Maze(RenderWindow &window, Sprite &map_sprite);

void Left_Move(Sound &fly_sound, Sprite &hero_sprite);

void Right_Move(Sound &fly_sound, Sprite &hero_sprite);

void Up_move(Sound &fly_sound, Sprite &hero_sprite);

void Down_Move(Sound &fly_sound, Sprite &hero_sprite);

void Error();

int main() {
    RenderWindow window(VideoMode(704, 704), "MAZE");

    Image map_image, hero_image, maze_image; //створюємо текстури лабіринту, персонажа
    if (!map_image.loadFromFile("images//map.png")) {
        perror("map.png");
        Error();
    }
    if (!hero_image.loadFromFile("images//hero.png")) {
        perror("hero.png");
        Error();
    }
    if (!maze_image.loadFromFile("images//maze.png")) {
        perror("maze.png");
        Error();
    }
    hero_image.createMaskFromColor(hero_image.getPixel(0, 0)); //прозорий фон персонажа
    Texture map_texture, hero_texture, maze_texture;
    map_texture.loadFromImage(map_image);
    hero_texture.loadFromImage(hero_image);
    maze_texture.loadFromImage(maze_image);
    Sprite map_sprite, hero_sprite, maze_sprite;
    map_sprite.setTexture(map_texture);
    hero_sprite.setTexture(hero_texture);
    hero_sprite.setPosition(x_pos, y_pos);
    maze_sprite.setTexture(maze_texture);

    Font font; //створюємо шрифт
    if (!font.loadFromFile("images//CyrilicOld.TTF")) {
        perror("CyrilicOld.TTF");
        Error();
    }

    Text text_finish("you won", font, 50), text("Escape - exit\n Enter - play\n\n\n\n\n\n      MAZE", font,45); //створюємо текст, колір, стиль
    text_finish.setFillColor(Color::White);
    text_finish.setStyle(Text::Bold);
    text.setFillColor(Color::Cyan);
    text.setStyle(Text::Bold);

    Music music; //сворюємо музику
    if (!music.openFromFile("images//music.ogg")) {
        perror("music.ogg");
        Error();
    }
    music.setVolume(15);

    SoundBuffer fly_buffer, finish_buffer; //створюємо звуки переміщення та кінця гри
    if (!fly_buffer.loadFromFile("images//fly.ogg")) {
        perror("fly.ogg");
        Error();
    }
    if (!finish_buffer.loadFromFile("images//finish.ogg")) {
        perror("finish.ogg");
        Error();
    }
    Sound fly_sound, finish_sound;
    fly_sound.setBuffer(fly_buffer);
    fly_sound.setVolume(28);
    finish_sound.setBuffer(finish_buffer);
    finish_sound.setVolume(30);

    Clock time_clock; //створюємо лічильник часу
    float time_game;
    char Time_Game[10000]; //масив для зберігання часу

    bool screen = true;
    bool *screen_ptr = &screen;

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed || Keyboard::isKeyPressed(Keyboard::Escape))
                window.close();
        }

        if (screen) //вивід заставки на екран
            Screen(maze_sprite, text, window, music, time_clock, screen_ptr);

        if (x == 21 && y == 1) //якщо персонаж дійшов до фінішу
            Finish(music, finish_sound, text_finish, window);

        time_game = time_clock.getElapsedTime().asSeconds(); //оновлення пройденого часу

        Draw_Maze(window, map_sprite); //малюємо лабіринт

        if (Keyboard::isKeyPressed(Keyboard::Left)) //через стрілочки пересуваємося вліво
            Left_Move(fly_sound, hero_sprite);
        else if (Keyboard::isKeyPressed(Keyboard::Right)) //через стрілочки пересуваємося вправо
            Right_Move(fly_sound, hero_sprite);
        else if (Keyboard::isKeyPressed(Keyboard::Up)) //через стрілочки пересуваємося вгору
            Up_move(fly_sound, hero_sprite);
        else if (Keyboard::isKeyPressed(Keyboard::Down)) //через стрілочки пересуваємося вниз
            Down_Move(fly_sound, hero_sprite);

        sprintf(Time_Game, "%.1f", time_game); //заносимо час в масив
        text.setString(Time_Game); //заносиво час з масиву
        text.setPosition(pixel, pixel / 2); //позиція лічильника часу

        window.draw(hero_sprite); //вивід героя
        window.draw(text); //вивід часу

        window.display(); //виводимо все на екран
        Sleep(100); //затримка для коректного пересування героя
    }
    return 0;
}

void Screen(Sprite &maze_sprite, Text &text, RenderWindow &window, Music &music, Clock &time_clock, bool *screen_ptr) { //заставка
    maze_sprite.setPosition(0, 0);
    text.setPosition(210, 50);
    window.draw(maze_sprite);
    window.draw(text);
    window.display();
    while (*screen_ptr == true) {
        if (Keyboard::isKeyPressed(Keyboard::Enter)) {
            *screen_ptr = false;
            break;
        }
        if (Keyboard::isKeyPressed(Keyboard::Escape)) {
            window.close();
            break;
        }
    }
    music.play(); //початок роботи музики
    music.setLoop(true);
    time_clock.restart(); //початок роботи лічильника часу
}

void Finish(Music &music, Sound &finish_sound, Text &text_finish, RenderWindow &window) { //кінець гри
    music.pause(); //зупиняємо музику
    finish_sound.play();  //грає музика перемоги
    text_finish.setPosition(280, 330);
    window.draw(text_finish); //вивід повідомлення про перемогу
    window.display();
    while (x == 21 && y == 1)
        if (finish_sound.getStatus() == Sound::Stopped || Keyboard::isKeyPressed(Keyboard::Escape)) {
            window.close();
            break;
        }
}

void Draw_Maze(RenderWindow &window, Sprite &map_sprite) {
    for (int i = 0; i < height; i++) //малюємо лабіринт
        for (int j = 0; j < width; j++) {
            if (Maze[i][j] == 0) //шлях
                map_sprite.setTextureRect(IntRect(0, 0, pixel, pixel));
            if (Maze[i][j] == 1) //перешкоди
                map_sprite.setTextureRect(IntRect(pixel, 0, pixel, pixel));

            map_sprite.setPosition(i * pixel, j * pixel);

            window.draw(map_sprite); //вивід лабіринта
        }
}

void Left_Move(Sound &fly_sound, Sprite &hero_sprite) { //переміщення вліво
    if (x > 0 && Maze[x - 1][y] == 0) {
        x--; //якщо зсунулися, змінюємо позицію за матриццею вліво
        x_pos = x_pos - pixel; //змінюємо позицію на екрані на один блок вліво
        hero_sprite.setPosition(x_pos, y_pos);
        fly_sound.play(); //звук пересування
    }
}

void Right_Move(Sound &fly_sound, Sprite &hero_sprite) { //переміщення вправо
    if (x < width && Maze[x + 1][y] == 0) {
        x++; //якщо зсунулися, змінюємо позицію за матриццею вправо
        x_pos = x_pos + pixel; //змінюємо позицію на екрані на один блок вправо
        hero_sprite.setPosition(x_pos, y_pos);
        fly_sound.play(); //звук пересування
    }
}

void Up_move(Sound &fly_sound, Sprite &hero_sprite) { //переміщення вгору
    if (y > 0 && Maze[x][y - 1] == 0) {
        y--; //якщо зсунулися, змінюємо позицію за матриццею вниз
        y_pos = y_pos - pixel; //змінюємо позицію на екрані на один блок вгору
        hero_sprite.setPosition(x_pos, y_pos);
        fly_sound.play(); //звук пересування
    }
}

void Down_Move(Sound &fly_sound, Sprite &hero_sprite) { //переміщення вниз
    if (y < height && Maze[x][y + 1] == 0) {
        y++; //якщо зсунулися, змінюємо позицію за матриццею вгору
        y_pos = y_pos + pixel; //змінюємо позицію на екрані на один блок вниз
        hero_sprite.setPosition(x_pos, y_pos);
        fly_sound.play(); //звук пересування
    }
}

void Error() { //помилка
    printf("\n");
    system("pause");
    exit(1);
}

