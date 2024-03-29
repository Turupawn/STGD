#ifndef PLAYER_H
#define PLAYER_H

#include <map>
#include <list>
#include <vector>

#include "TinyXml/tinyxml.h"
#include "RosalilaGraphics/RosalilaGraphics.h"
#include "RosalilaSound/RosalilaSound.h"
#include "RosalilaInputs/RosalilaInputs.h"
#include "../Spells/Bullet.h"
#include "../Spells/Pattern.h"
#include "Character.h"

class Player : public Character
{
    Image*life_bar;

    //Slow bar variables
    Image*slow_bar;
    int slow_decrement;
    int slow_increment;
    int slow_cooldown_increment;
    bool slow_in_cooldown;
    int slow_bar_x;
    int slow_bar_y;
    int slow_bar_rect_offset_x;
    int slow_bar_rect_offset_y;
    int slow_bar_rect_height;
    int slow_bar_rect_width;
    Color slow_bar_color;
    Color slow_bar_cooldown_color;

public:
bool raped;
int cont_release_rape;
bool unbind_right_press;
    Player(Sound* sonido,RosalilaGraphics* painter,Receiver* receiver,std::string name);
    void logic(int stage_velocity);
    void inputControl();
    void render();
    void loadPlayerFromXML();
};

#endif
