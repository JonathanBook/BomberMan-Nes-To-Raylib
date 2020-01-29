#include <raylib.h>
#include "main.h"

bool MovActeur(Vector2 Direction , GameObject *Acteur)
{
    if(Direction.x ==0 && Direction.y == 0)
    {
        AppliqueAnimation(ANIMATIONIDLE,1,Acteur);
        Acteur->Velocity = Vector2Zero ;
        return false;
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

    //Update POstion Box Collission
    Acteur->BoxCollision.x = Acteur->Position.x ;
    Acteur->BoxCollision.y = Acteur->Position.y;
    
    //Check Colision Decore
    if(CheckCollisionMap( Acteur ))
    {
        //if Collision true Aplique Old position
        Acteur->Position = OldPosition ;
        return true;
    }
    return false ;

}