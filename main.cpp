#include <SFML/Graphics.hpp>

#include "classes/Entity.h"
#include "classes/Character.h"

const int maxBlocks = 100;

int main()
{
    sf::RenderWindow window(sf::VideoMode(1600, 800), "Ferraria");
    window.setFramerateLimit(60);

    std::vector<Entity *> entities; entities.clear();

    sf::RectangleShape characterThingy; characterThingy.setFillColor(sf::Color::Green); characterThingy.setSize(sf::Vector2f(50,50));

    sf::RectangleShape blockThingy; blockThingy.setFillColor(sf::Color::Blue); blockThingy.setSize(sf::Vector2f(10,10));

    Character *c = new Character();
    c->settings(characterThingy, 800, 400, 0);
    entities.push_back(c);

    sf::Mouse mouse; std::vector<float> mousePos = {0, 0}; ///Mouse position

    int blockCount = 0;

    enum states {START, GAME}; states state = START;

    while (window.isOpen())
    {

        sf::Event event; while (window.pollEvent(event)) { if (event.type == sf::Event::Closed){window.close();} }


        c->dx = 0;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) { c->dx = 10; }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) { c->dx = -10;}
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && c->canJump) { c->dy = -30;}

        
        if(sf::Mouse::isButtonPressed(mouse.Left)){
            Character *b = new Character();
            sf::Vector2i mvec = sf::Mouse::getPosition(window);
            b->settings(blockThingy, mvec.x, mvec.y, 0);
            b->name = "block";
            blockCount += 1;
            entities.push_back(b);
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
        window.display();
    }

    return 0;
}