#include "Bullet.h"

Bullet::Bullet(Sound* sonido,RosalilaGraphics* painter,Receiver* receiver,std::string name,vector<Image*>sprites,vector<Image*>sprites_on_hit,vector<Image*>sprites_raping,vector<Hitbox*> hitboxes,int damage)
{
    this->sonido=sonido;
    this->painter=painter;
    this->receiver=receiver;
    this->sprites=sprites;
    this->sprites_on_hit=sprites_on_hit;
    this->sprites_raping=sprites_raping;
    this->hitboxes=hitboxes;
    this->damage=damage;
    this->name=name;
    type="Bullet";
}

void Bullet::logic()
{
}

void Bullet::render()
{

}

Image* Bullet::getImage(int position)
{
    if(position>=(int)sprites.size())
        return NULL;
    return sprites[position];
}

Image* Bullet::getOnHitImage(int position)
{
    if(position>=(int)sprites_on_hit.size())
        return NULL;
    return sprites_on_hit[position];
}

Image* Bullet::getRapeImage(int position)
{
    if(position>=(int)sprites_raping.size())
        return NULL;
    return sprites_raping[position];
}

int Bullet::spritesSize()
{
    return sprites.size();
}

int Bullet::spritesOnHitSize()
{
    return sprites_on_hit.size();
}

int Bullet::spritesRaping()
{
    return sprites_raping.size();
}

vector<Hitbox*> Bullet::getHitboxes()
{
    return hitboxes;
}

int Bullet::getDamage()
{
    return damage;
}

void Bullet::playSound()
{
    if(sonido->soundExists("bullet."+name))
    {
        sonido->playSound("bullet."+name);
    }
}

void Bullet::playHitSound()
{
    if(sonido->soundExists("bullet_hit."+name))
    {
        sonido->playSound("bullet_hit."+name);
    }
}
