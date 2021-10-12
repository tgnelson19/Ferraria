#ifndef FERRARIA_CHARACTER_H
#define FERRARIA_CHARACTER_H

#include "Entity.h"
#include <SFML/Graphics.hpp>
#include <iostream>

class Character : public Entity{
public:

    float gravMod;
    bool canJump;


    Character(){

        name = "character";
        canJump = false;
        floor = 800 - sprite.getSize().y;
        interacted = false;

    }

    void update() {

        if(!interacted){
            floor = 800 - sprite.getSize().y;
        }

        if(floor > 800 - sprite.getSize().y){
            floor = 800 - sprite.getSize().y;
        }


        if(y != floor){
            canJump = false;
        } else {
            canJump = true;
        }

        x += dx;
        y += dy;

       if (y < floor){
           dy += 1;
       } else {
           y = floor;
           dy = 0;
       }

    }

};


#endif //FERRARIA_CHARACTER_H