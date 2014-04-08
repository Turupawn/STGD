#ifndef BULLET_H
#define BULLET_H

#include "TinyXml/tinyxml.h"
#include "RosalilaGraphics/RosalilaGraphics.h"
#include "RosalilaSound/RosalilaSound.h"
#include "RosalilaInputs/RosalilaInputs.h"
#include "Hitbox.h"

class Bullet
{
protected:
    Sound* sonido;
    RosalilaGraphics* painter;
    Receiver* receiver;
    vector<Image*>sprites;
    vector<Image*>sprites_on_hit;
    vector<Image*>sprites_raping;
    vector<Hitbox*> hitboxes;
    int damage;
    std::string name;

public:
string type;
    Bullet(){};
    Bullet(Sound* sonido,RosalilaGraphics* painter,Receiver* receiver,std::string name,vector<Image*>sprites,vector<Image*>sprites_on_hit,vector<Image*>sprites_raping,vector<Hitbox*> hitboxes,int damage);
    virtual void logic();
    void render();
    vector<Hitbox*> getHitboxes();
    int getDamage();
    void playSound();
    void playHitSound();
    Image*getImage(int position);
    Image*getOnHitImage(int position);
    Image*getRapeImage(int position);
    int spritesSize();
    int spritesOnHitSize();
    int spritesRaping();
};

#endif
