#include "main.h"
#include <raylib.h>
#include <raymath.h>
#include <stdio.h>
//#include"GameObject.h"

//Check the different collisions the hero may encounter
bool CheckCollisionMap(GameObject *Acteur)
{
    Acteur->Offset  = Vector2(-TILEW/2,1);//Ground Offset

   
    if(Acteur->Velocity.x <0  )
    {
        Acteur->Offset = Vector2(-TILEW,-TILEH/2); //OffSet Left

    }else if(Acteur->Velocity.x >0  )
    {
        Acteur->Offset = Vector2(1,-TILEH/2);//Offset Right 

    }else if (Acteur->Velocity.y <0)
    {
        Acteur->Offset = Vector2(-8,-8);
    }
    

    int tile = GetTile( Vector2Add(Acteur->Position ,Acteur->Offset) ) ;

    if ( tile !=-1 && tile  )
    {
        return true ;
    }
    return false ;
}

bool CheckCollision(BoxCol *A , BoxCol *B)
{
   
       if((B->x >= A->x + A->w)      // trop à droite
	|| (B->x + B->w <= A->x) // trop à gauche
	|| (B->y >= A->y + A->h) // trop en bas
	|| (B->y + B->h <= A->y))  // trop en haut
        return false; 
   else
        return true; 
}