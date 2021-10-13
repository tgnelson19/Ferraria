#include <SFML/Graphics.hpp>
#include <ctime>
#include <cstdlib>

#include "classes/Entity.h"
#include "classes/Character.h"

const int maxBlocks = 100;

int main()
{

    srand(time(0));
    sf::RenderWindow window(sf::VideoMode(1600, 800), "Ferraria");
    window.setFramerateLimit(60);

    sf::Font font;
    if (!font.loadFromFile("fonts/Oswald-Bold.ttf")) { /// Free for commercial use from fontsquirrel.com
        return EXIT_FAILURE;
    }

    sf::Text score("Score: 0", font, 30); score.setFillColor(sf::Color::White); score.setPosition(1450, 10);


    std::vector<Entity *> entities; entities.clear();

    sf::RectangleShape characterThingy; characterThingy.setFillColor(sf::Color::Green); characterThingy.setSize(sf::Vector2f(40,40));
    sf::RectangleShape blockThingy; blockThingy.setFillColor(sf::Color::Blue); blockThingy.setSize(sf::Vector2f(10,10));
    sf::RectangleShape red; red.setFillColor(sf::Color::Red); red.setSize(sf::Vector2f(1600,25));
    sf::RectangleShape platform; platform.setFillColor(sf::Color::White); platform.setSize(sf::Vector2f(160,25));
    sf::RectangleShape gold; gold.setFillColor(sf::Color::Yellow); gold.setSize(sf::Vector2f(25,25));

    Entity *r = new Entity();
    r->settings(red, 0, 775, 0); r->name = "red";
    entities.push_back(r);

    Entity *p = new Entity();
    p->settings(platform, 740, 425, 0); p->name = "platform";
    entities.push_back(p);

    Entity *g = new Entity();
    g->settings(gold, 600, 500, 0); g->isAlive = true; g->name = "gold";
    entities.push_back(g);

    Character *c = new Character();
    c->settings(characterThingy, 800, 325, 0);
    entities.push_back(c);

    sf::Mouse mouse; std::vector<float> mousePos = {0, 0}; ///Mouse position

    int blockCount = 0;
    int scoreInt = 0;
    bool glive = false;

    enum states {START, GAME}; states state = START;

    while (window.isOpen())
    {

        sf::Event event; while (window.pollEvent(event)) { if (event.type == sf::Event::Closed){window.close();} }


        c->dx = 0;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) { c->dx = 5; }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) { c->dx = -5;}
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && c->canJump) { c->dy = -15;}

        
        if(sf::Mouse::isButtonPressed(mouse.Left)){
            Character *b = new Character();
            sf::Vector2i mvec = sf::Mouse::getPosition(window);
            

            /* Code to make the water gun effect
            mousePos.at(0) = mvec.x - c->x; ///Mouse position relative to the character
            mousePos.at(1) = mvec.y - c->y;
            if(mousePos.at(0) <= 0) {
                b->dy = -15*sin(atan(mousePos.at(1) / mousePos.at(0)));
                b->dx = -15*cos(atan(mousePos.at(1) / mousePos.at(0)));
            } else {
                b->dy = 15*sin(atan(mousePos.at(1) / mousePos.at(0)));
                b->dx = 15*cos(atan(mousePos.at(1) / mousePos.at(0)));
            }

            b->settings(blockThingy, c->x + 20, c->y - 50, 0);
            */

            b->settings(blockThingy, mvec.x, mvec.y, 0);

            b->name = "block";
            blockCount += 1;
            entities.push_back(b);
        }
        
        if (!glive){
            int randX = rand() % 1600; int randY = rand() % 800 - 25;
            g->settings(gold, randX, randY, 0);
            glive = true;
        }
        
        for(auto i:entities){
            i->interacted = false;
            if(blockCount > maxBlocks && i->name == "block"){
                i->isAlive = false;
                blockCount -= 1;
            }
        }

        for (auto p:entities) { 
            for (auto q:entities) { 
                if (p != q){
                    sf::FloatRect aBox = p->sprite.getGlobalBounds();
                    sf::FloatRect bBox = q->sprite.getGlobalBounds();
                    if(aBox.intersects(bBox)){
                        if(p->name == "red" && q->name == "character" ){
                            c->settings(characterThingy, 800, 325, 0);
                            scoreInt = 0;
                            score.setString("Score: " + std::to_string(scoreInt));
                        }
                        if(p->name == "gold" && q->name == "character" ){
                            glive = false;
                            scoreInt++;
                            score.setString("Score: " + std::to_string(scoreInt));
                        }

                        p->interacted = true; q->interacted = true;
                        if (aBox.top < bBox.top){
                            p->floor = bBox.top - p->sprite.getSize().y;
                        } else if (bBox.top < aBox.top){
                            q->floor = aBox.top - q->sprite.getSize().y;
                        }
                    }
                }
            }
        }







        
        for (auto i = entities.begin(); i != entities.end();) { ///Entity update logic
            Entity *e = *i; //*i is an Entity pointer, using * on an iterator returns the element from the list
            e->update(); // Uses polymorphism to call the proper update method
            if (!e->isAlive) {
                i = entities.erase(i); delete e; 
            } else i++; //Move iterator to the next element in the list
        }

        window.clear();
        for (auto i:entities) { i->draw(window); } ///Draw Logic
        window.draw(score);
        window.display();
    }

    return 0;
}