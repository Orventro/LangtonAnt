#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include "Ant.h"
#include <random>
#include <memory>
#include <time.h>

using namespace std;
using namespace sf;

int main(){
    string source;
    cin >> source;
    int speed;
    cin >> speed;
    char slen = source.size();
    bool *cmd = str_to_cmd(source);
    int w=600, h=600;
    Ant ant(w, h, slen, cmd);
    RenderWindow window(sf::VideoMode(w, h), "Ant");
    Event event;
    Uint8 *pixels = new Uint8[w * h * 4];
    Texture texture;
    texture.create(w, h);
    Sprite sprite;

    srand (time(NULL));
    Uint8 *colors = new Uint8[slen * 4];
    for(int i = 0; i < slen*4; i++) colors[i] = rand();

    while (window.isOpen())
    {
        while (window.pollEvent(event))
            if (event.type == Event::Closed) window.close();

        window.clear(Color::Black);

        ant.move(speed);

        for(int i = 0; i < w*h; i++)
                for(int j = 0; j < 4; j++)
                    pixels[i*4 + j] = colors[ant.field[i]*4+j];

        texture.update(pixels);
        sprite.setTexture(texture);
        window.draw(sprite);

        window.display();
    }
    delete[] pixels, colors;
}
