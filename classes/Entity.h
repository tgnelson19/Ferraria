#ifndef FERRARIA_ENTITY_H
#define FERRARIA_ENTITY_H
#include <SFML/Graphics.hpp>
#include <cmath>

static float W = 1600;
static float H = 800;

const float dtr = 0.017453f;

class Entity {
public:
    float x, y; /// Position on the screen
    float dx, dy;
    int speed;
    float floor;
    bool interacted;
    float angle; /// Speed of an entity will be based off of POLAR coordinate system, not cartesian
    bool isAlive; /// Determines if entity is alive
    std::string name; /// Determines which entity it is
    sf::RectangleShape sprite; /// Gives the entity a sprite
    
    
    

    Entity() { isAlive = true; dx = 0; dy = 0; } /// Default Constructor

    void settings(sf::RectangleShape &s, float X, float Y, float Angle) { sprite = s; x = X; y = Y; angle = Angle; } /// Changes Settings

    virtual void update() {}; /// Used for future derived classes

    virtual void draw(sf::RenderWindow &app){ /// Draws current entity to the screen
        sprite.setPosition(x,y);
        app.draw(sprite);
    }

    virtual ~Entity() {}; /// Used for future derived classes
    };


#endif //FERRARIA
