#include "STG.h"

STG::STG(Sound* sonido,RosalilaGraphics* painter,Receiver* receiver,Player*player,Enemy*enemy,Stage*stage)
{
    this->sonido=sonido;
    this->painter=painter;
    this->receiver=receiver;
    this->player=player;
    this->enemy=enemy;
    this->stage=stage;
    painter->camera_x=0;
    painter->camera_y=0;
    iteration=0;

    //XML Initializations
    char *archivo=new char[255];
    strcpy(archivo,"config.xml");
    TiXmlDocument doc_t( archivo );
    doc_t.LoadFile();
    TiXmlDocument *doc;
    doc=&doc_t;

    TiXmlNode *config_file=doc->FirstChild("ConfigFile");

    TiXmlNode *user_node=config_file->FirstChild("User");
    username=user_node->ToElement()->Attribute("name");

    TiXmlNode *you_loose_node=config_file->FirstChild("YouLoose");

    int you_loose_x=atoi(you_loose_node->ToElement()->Attribute("x"));
    int you_loose_y=atoi(you_loose_node->ToElement()->Attribute("y"));
    int you_loose_animation_velocity=atoi(you_loose_node->ToElement()->Attribute("animation_velocity"));
    you_loose=Animation(you_loose_x,you_loose_y,you_loose_animation_velocity,painter);

    for(TiXmlNode* sprites_node=you_loose_node->FirstChild("sprite");
            sprites_node!=NULL;
            sprites_node=sprites_node->NextSibling("sprite"))
    {
        std::string path=sprites_node->ToElement()->Attribute("path");
        you_loose.addImage(painter->getTexture(path));
    }


    TiXmlNode *you_win_node=config_file->FirstChild("YouWin");

    int you_win_x=atoi(you_win_node->ToElement()->Attribute("x"));
    int you_win_y=atoi(you_win_node->ToElement()->Attribute("y"));
    int you_win_animation_velocity=atoi(you_win_node->ToElement()->Attribute("animation_velocity"));
    you_win=Animation(you_win_x,you_win_y,you_win_animation_velocity,painter);

    for(TiXmlNode* sprites_node=you_win_node->FirstChild("sprite");
            sprites_node!=NULL;
            sprites_node=sprites_node->NextSibling("sprite"))
    {
        std::string path=sprites_node->ToElement()->Attribute("path");
        you_win.addImage(painter->getTexture(path));
    }

    stage->playMusic();

    mainLoop();
}

void STG::mainLoop()
{
    bool end_key_up_keyboard=false;
    bool end_key_up_joystick=false;
    for (;;)
    {
        if(receiver->IsKeyDownn(SDLK_ESCAPE))
        {
            break;
        }

        render();
        logic();
        if(player->getHP()==0
           || enemy->getHP()==0)
        {
            if(receiver->IsKeyPressed(SDLK_RETURN)
               || (receiver->IsKeyPressed(SDLK_z) && end_key_up_keyboard)
               || (receiver->IsJoyPressed(0,0) && end_key_up_joystick)
               )
            {
                if(player->getHP()>0)
                {
                    Image* image_bg=painter->getTexture("ending/bg.png");
                    Image* image_press_enter=painter->getTexture("ending/press enter.png");

                    Image* image_intro=painter->getTexture("ending/intro.png");

                    bool exit_signal=false;

                    while(!exit_signal)
                    {
                        if(receiver->IsKeyPressed(SDLK_RETURN))
                            exit_signal=true;

                        painter->draw2DImage
                        (   image_bg,
                            1366,768,
                            0,0,
                            1.0,
                            0.0,
                            false,
                            0,0,
                            Color(255,255,255,255),
                            false);

                        painter->draw2DImage
                        (   image_intro,
                            image_intro->getWidth(),image_intro->getHeight(),
                            0,0,
                            1.0,
                            0.0,
                            false,
                            0,0,
                            Color(255,255,255,255),
                            false);

                        painter->draw2DImage
                        (   image_press_enter,
                            image_press_enter->getWidth(),image_press_enter->getHeight(),
                            850,680,
                            1.0,
                            0.0,
                            false,
                            0,0,
                            Color(255,255,255,255),
                            false);

                        painter->updateScreen();
                        receiver->updateInputs();
                    }

                    Image* image1=painter->getTexture("ending/1.png");
                    Image* image2=painter->getTexture("ending/2.png");

                    exit_signal=false;
                    while(!exit_signal)
                    {
                        if(receiver->IsKeyPressed(SDLK_RETURN))
                            exit_signal=true;

                        for(int i=0;i<10;i++)
                        {
                            if(receiver->IsKeyPressed(SDLK_RETURN))
                                exit_signal=true;

                            painter->draw2DImage
                            (   image_bg,
                                1366,768,
                                0,0,
                                1.0,
                                0.0,
                                false,
                                0,0,
                                Color(255,255,255,255),
                                false);

                            painter->draw2DImage
                            (   image1,
                                image1->getWidth(),image1->getHeight(),
                                painter->screen_width/2-image1->getWidth()/2,0,
                                1.0,
                                0.0,
                                false,
                                0,0,
                                Color(255,255,255,255),
                                false);

                            painter->draw2DImage
                            (   image_press_enter,
                                image_press_enter->getWidth(),image_press_enter->getHeight(),
                                850,680,
                                1.0,
                                0.0,
                                false,
                                0,0,
                                Color(255,255,255,255),
                                false);

                            painter->updateScreen();
                            receiver->updateInputs();
                        }

                        for(int i=0;i<10;i++)
                        {
                            if(receiver->IsKeyPressed(SDLK_RETURN))
                                exit_signal=true;

                            painter->draw2DImage
                            (   image_bg,
                                1366,768,
                                0,0,
                                1.0,
                                0.0,
                                false,
                                0,0,
                                Color(255,255,255,255),
                                false);

                            painter->draw2DImage
                            (   image2,
                                image2->getWidth(),image2->getHeight(),
                                painter->screen_width/2-image2->getWidth()/2,0,
                                1.0,
                                0.0,
                                false,
                                0,0,
                                Color(255,255,255,255),
                                false);

                            painter->draw2DImage
                            (   image_press_enter,
                                image_press_enter->getWidth(),image_press_enter->getHeight(),
                                850,680,
                                1.0,
                                0.0,
                                false,
                                0,0,
                                Color(255,255,255,255),
                                false);

                            painter->updateScreen();
                            receiver->updateInputs();
                        }
                    }


                    exit_signal=false;
                    Image* image3=painter->getTexture("ending/3.png");
                    Image* image4=painter->getTexture("ending/4.png");
                    while(!exit_signal)
                    {
                        if(receiver->IsKeyPressed(SDLK_RETURN))
                            exit_signal=true;

                        for(int i=0;i<10;i++)
                        {
                            if(receiver->IsKeyPressed(SDLK_RETURN))
                                exit_signal=true;

                            painter->draw2DImage
                            (   image_bg,
                                1366,768,
                                0,0,
                                1.0,
                                0.0,
                                false,
                                0,0,
                                Color(255,255,255,255),
                                false);

                            painter->draw2DImage
                            (   image3,
                                image3->getWidth(),image3->getHeight(),
                                painter->screen_width/2-image3->getWidth()/2,0,
                                1.0,
                                0.0,
                                false,
                                0,0,
                                Color(255,255,255,255),
                                false);

                            painter->draw2DImage
                            (   image_press_enter,
                                image_press_enter->getWidth(),image_press_enter->getHeight(),
                                850,680,
                                1.0,
                                0.0,
                                false,
                                0,0,
                                Color(255,255,255,255),
                                false);

                            painter->updateScreen();
                            receiver->updateInputs();
                        }

                        for(int i=0;i<10;i++)
                        {
                            if(receiver->IsKeyPressed(SDLK_RETURN))
                                exit_signal=true;

                            painter->draw2DImage
                            (   image_bg,
                                1366,768,
                                0,0,
                                1.0,
                                0.0,
                                false,
                                0,0,
                                Color(255,255,255,255),
                                false);

                            painter->draw2DImage
                            (   image4,
                                image4->getWidth(),image4->getHeight(),
                                painter->screen_width/2-image4->getWidth()/2,0,
                                1.0,
                                0.0,
                                false,
                                0,0,
                                Color(255,255,255,255),
                                false);

                            painter->draw2DImage
                            (   image_press_enter,
                                image_press_enter->getWidth(),image_press_enter->getHeight(),
                                850,680,
                                1.0,
                                0.0,
                                false,
                                0,0,
                                Color(255,255,255,255),
                                false);

                            painter->updateScreen();
                            receiver->updateInputs();
                        }
                    }


                    exit_signal=false;
                    Image* image5=painter->getTexture("ending/5.png");
                    Image* image6=painter->getTexture("ending/6.png");
                    while(!exit_signal)
                    {
                        if(receiver->IsKeyPressed(SDLK_RETURN))
                            exit_signal=true;

                        for(int i=0;i<10;i++)
                        {
                            if(receiver->IsKeyPressed(SDLK_RETURN))
                                exit_signal=true;

                            painter->draw2DImage
                            (   image_bg,
                                1366,768,
                                0,0,
                                1.0,
                                0.0,
                                false,
                                0,0,
                                Color(255,255,255,255),
                                false);

                            painter->draw2DImage
                            (   image5,
                                image5->getWidth(),image5->getHeight(),
                                painter->screen_width/2-image5->getWidth()/2,0,
                                1.0,
                                0.0,
                                false,
                                0,0,
                                Color(255,255,255,255),
                                false);


                            painter->draw2DImage
                            (   image_press_enter,
                                image_press_enter->getWidth(),image_press_enter->getHeight(),
                                850,680,
                                1.0,
                                0.0,
                                false,
                                0,0,
                                Color(255,255,255,255),
                                false);

                            painter->updateScreen();
                            receiver->updateInputs();
                        }

                        for(int i=0;i<10;i++)
                        {
                            if(receiver->IsKeyPressed(SDLK_RETURN))
                                exit_signal=true;

                            painter->draw2DImage
                            (   image_bg,
                                1366,768,
                                0,0,
                                1.0,
                                0.0,
                                false,
                                0,0,
                                Color(255,255,255,255),
                                false);

                            painter->draw2DImage
                            (   image6,
                                image6->getWidth(),image6->getHeight(),
                                painter->screen_width/2-image6->getWidth()/2.0,0,
                                1.0,
                                0.0,
                                false,
                                0,0,
                                Color(255,255,255,255),
                                false);

                            painter->draw2DImage
                            (   image_press_enter,
                                image_press_enter->getWidth(),image_press_enter->getHeight(),
                                850,680,
                                1.0,
                                0.0,
                                false,
                                0,0,
                                Color(255,255,255,255),
                                false);

                            painter->updateScreen();
                            receiver->updateInputs();
                        }
                    }

                    Image* image_end=painter->getTexture("ending/end.png");
                    exit_signal=false;

                    while(!exit_signal)
                    {
                        if(receiver->IsKeyPressed(SDLK_RETURN))
                            exit_signal=true;

                        painter->draw2DImage
                        (   image_bg,
                            1366,768,
                            0,0,
                            1.0,
                            0.0,
                            false,
                            0,0,
                            Color(255,255,255,255),
                            false);

                        painter->draw2DImage
                        (   image_end,
                            image_end->getWidth(),image_end->getHeight(),
                            0,0,
                            1.0,
                            0.0,
                            false,
                            0,0,
                            Color(255,255,255,255),
                            false);

                        painter->draw2DImage
                        (   image_press_enter,
                            image_press_enter->getWidth(),image_press_enter->getHeight(),
                            850,680,
                            1.0,
                            0.0,
                            false,
                            0,0,
                            Color(255,255,255,255),
                            false);

                        painter->updateScreen();
                        receiver->updateInputs();
                    }

                    delete image_bg;
                    delete image_press_enter;
                    delete image_intro;
                    delete image1;
                    delete image2;
                    delete image3;
                    delete image4;
                    delete image5;
                    delete image6;
                    delete image_end;
                }

                break;
            }

            if(!receiver->IsKeyPressed(SDLK_z))
                end_key_up_keyboard=true;
            if(!receiver->IsJoyPressed(0,0))
                end_key_up_joystick=true;

        }
        receiver->updateInputs();
    }
}

void STG::logic()
{
    if(receiver->IsKeyPressed(SDLK_1))
    {
        player->setType("1");
    }
    if(receiver->IsKeyPressed(SDLK_2))
    {
        player->setType("2");
    }
    if(receiver->IsKeyPressed(SDLK_3))
    {
        player->setType("3");
    }
    if(receiver->IsKeyPressed(SDLK_4))
    {
        player->setType("4");
    }
    if(receiver->IsKeyPressed(SDLK_5))
    {
        player->setType("5");
    }
    if(receiver->IsKeyPressed(SDLK_6))
    {
        player->setType("6");
    }
    if(receiver->IsKeyPressed(SDLK_7))
    {
        player->setType("7");
    }
    if(receiver->IsKeyPressed(SDLK_8))
    {
        player->setType("8");
    }
    if(receiver->IsKeyPressed(SDLK_9))
    {
        player->setType("9");
    }

    int stage_displacement = stage->getVelocity();
    if(isSlowActive())
        stage_displacement/=3;
    painter->camera_x+=stage_displacement;
    player->logic(stage_displacement);
    player->setX(player->getX()+stage_displacement);
    enemy->logic(stage_displacement,stage->getName(),iteration,username);
    //enemy->setX(enemy->getX()+stage_displacement);
    stage->logic();

    deletePatterns();
    checkCharacterOutOfBounds();
    slowExtraControl();

    if(enemy->getHP()>0)
        iteration++;
}

void STG::render()
{
    stage->dibujarBack();
    player->render();
    enemy->render();

    stage->render();
    stage->dibujarFront();

    for (std::list<Pattern*>::iterator pattern = enemy->getActivePatterns()->begin(); pattern != enemy->getActivePatterns()->end(); pattern++)
    {
        Pattern*p=(Pattern*)*pattern;
        if(!p->isHit())
        {
            for(int i=0;i<(int)p->getBullet()->getHitboxes().size();i++)
            {
                p->getBullet()->getHitboxes()[i];
                Hitbox h=p->getBullet()->getHitboxes()[i]->getPlacedHitbox(Point(p->getX(),p->getY()),p->getBulletAngle());
                if(player->collides(h,0,0,0))
                {
                    if(p->rapes && p->player_raping==NULL)
                    {
                        p->player_raping=player;
                        player->cont_release_rape=10;
                        player->raped=true;
                    }else
                    {
                        p->hit();
                        player->hit(p->getDamage());
                    }
                }
            }
        }
    }

    for (std::list<Pattern*>::iterator pattern = player->getActivePatterns()->begin(); pattern != player->getActivePatterns()->end(); pattern++)
    {
        Pattern*p=(Pattern*)*pattern;
        if(!p->isHit())
        {
            for(int i=0;i<(int)p->getBullet()->getHitboxes().size();i++)
            {
                p->getBullet()->getHitboxes()[i];
                Hitbox h=p->getBullet()->getHitboxes()[i]->getPlacedHitbox(Point(p->getX(),p->getY()),p->getBulletAngle());
                if(enemy->collides(h,0,0,0))
                {
                    p->hit();
                    enemy->hit(p->getDamage());
                }
            }
        }
    }

    if(enemy->getHP()==0)
        you_win.render();
    if(player->getHP()==0)
        you_loose.render();

    painter->drawText("Time: "+toString(iteration),0,65);


    painter->updateScreen();
}

bool STG::isOutOfBounds(int pos_x,int pos_y)
{
    int bullet_bound_addition_x = (stage->getBoundX2()-stage->getBoundX1())/2;
    int bullet_bound_addition_y = (stage->getBoundY2()-stage->getBoundY1())/2;
    if(pos_x<stage->getBoundX1()+painter->camera_x-bullet_bound_addition_x
       ||pos_x>stage->getBoundX2()+painter->camera_x+bullet_bound_addition_x
       ||pos_y<stage->getBoundY1()-bullet_bound_addition_y
       ||pos_y>stage->getBoundY2()+bullet_bound_addition_y
       )
    {
        return true;
    }
    return false;
}

void STG::deletePatterns()
{
    std::list<Pattern*>* active_patterns=player->getActivePatterns();
    std::list<Pattern*>::iterator i = active_patterns->begin();
    while (i != active_patterns->end())
    {
        Pattern*p=(Pattern*)*i;
        if (isOutOfBounds(p->getX(),p->getY()) || p->destroyFlag())
        {
            active_patterns->erase(i++);
            delete p;
        }
        else
        {
            ++i;
        }
    }


    active_patterns=enemy->getActivePatterns();
    i = active_patterns->begin();
    while (i != active_patterns->end())
    {
        Pattern*p=(Pattern*)*i;
        if (isOutOfBounds(p->getX(),p->getY())
                        || p->destroyFlag())
        {
            active_patterns->erase(i++);
            delete p;
        }else if(((!player->raped) && p->player_raping!=NULL))
        {
            p->hit();
            p->player_raping=NULL;
        }
        else
        {
            ++i;
        }
    }
}

void STG::checkCharacterOutOfBounds()
{
    if(player->getX()<stage->getBoundX1()+painter->camera_x)
        player->setX(stage->getBoundX1()+painter->camera_x);
    if(player->getX()>stage->getBoundX2()+painter->camera_x)
        player->setX(stage->getBoundX2()+painter->camera_x);
    if(player->getY()<stage->getBoundY1())
        player->setY(stage->getBoundY1());
    if(player->getY()>stage->getBoundY2())
        player->setY(stage->getBoundY2());
}
