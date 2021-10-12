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
        dy = 0;
        dx = 0;

    }

    void update() {

        if(!interacted){
            floor = 775 - sprite.getSize().y;
        }

        if(floor > 775 - sprite.getSize().y){
            floor = 775 - sprite.getSize().y;
        }

        if(y < floor){
            canJump = false;
        } else {
            canJump = true;
        }

        if (y <= floor){
           dy += 0.75;
       } else {
           y = floor;
           dy = 0;
       }

       if (x > 1600) {
           x = 0;
       }else if (x < 0) {
           x = 1600;
       }

       if (name == "block" && dy <= -1) { 
            dy = 0;
            y = floor;
        }

        x += dx;
        y += dy;

       

       

    }

};


#endif //FERRARIA_CHARACTER_H