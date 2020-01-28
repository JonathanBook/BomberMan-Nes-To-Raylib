#include <raylib.h>
#include "main.h"

void MovActeur(Vector2 Direction , GameObject *Acteur)
{
    if(Direction.x ==0 && Direction.y == 0)
    {
        AppliqueAnimation(ANIMATIONIDLE,1,Acteur);
        Acteur->Velocity = Vector2Zero ;
        return;
    }
    //Sav Old Position
    Vector2 OldPosition = Acteur->Position ;
    //Aplique speed to Direction
    Direction = Vector2(Acteur->Speed * Direction.x , Acteur->Speed * Direction.y);
    //Change Value Velocity
    Acteur->Velocity = Direction ;
    //Mov Acteur
    Acteur->Position.x += Acteur->Velocity.x * 0.14f;
    Acteur->Position.y += Acteur->Velocity.y * 0.14f;
    //Check Colision Decore
    if(CheckCollisionMap( Acteur ))
    {
        //if Collision true Aplique Old position
        Acteur->Position = OldPosition ;
        return ;
    }else 
    {//ANIMATION SELECTED
        //Left And Right
        if(Direction.x!=0)
        {
            AppliqueAnimation(ANIMATIONLEFT,3,Acteur);
        //Up
        }else if (Direction.y<0)
        {
            AppliqueAnimation(ANIMATIONUP,3,Acteur);
        //Down
        }else if (Direction.y>0)
        {
            AppliqueAnimation(ANIMATIONDOWN,3,Acteur);
        }
        
        
    }
    


}