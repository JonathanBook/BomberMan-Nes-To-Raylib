#include <raylib.h>
#include "main.h"

void AddAnimation(GameObject *Acteur);
void InitEnemy(GameObject *Acteur,GameObject *liste[],Vector2 Spawn);

 enum State{
    MOVE,
    Check,
    Choix
}State;

typedef struct Enemy
{
    GameObject Object;
   enum State State ;

}Enemy;


//VARIABLES
Enemy ListeEnemy[10];

void AddEnemy(GameObject *liste[],Vector2 Spawn)
{
    for(int i =0;i<10;i++)
    {
        if( !ListeEnemy[i].Object.isActive )
        {
            InitEnemy( &ListeEnemy[i].Object , liste , Spawn ) ;
           
        }
        break ;
    }
}

void InitEnemy(GameObject *Acteur,GameObject *liste[],Vector2 Spawn)
{
    //Init position PlayerOne
    Acteur->isActive = true ;
    Acteur->Position = Spawn;
    //Init speed 
    Acteur->Speed = 8 ;
    Acteur->MaxSpeed = 40 ;
    Acteur->Velocity = Vector2Zero;
    Acteur->Offset = Vector2Zero ;
    Acteur->Animation.Pause = false ;
    Acteur->BoxCollision.w = TILEW ;
    Acteur->BoxCollision.h = TILEW ;
    AddAnimation(Acteur) ;
    for(int B =30;B<40;B++)
    {
        if(!liste[B]->isActive){liste[0] = Acteur ;}
    }
    
  

}
 enum State state = MOVE ;
void updateInfoEnemy()
{
   
    for(int i=0;i<10;i++){

      Enemy *Acteur = &ListeEnemy[i];

         Acteur->State = MOVE;

        
    }  
}

void AddAnimation(GameObject *Acteur)
{
    //WALK LEFT RIGHT
    Acteur->Animation.Frame[0][0] = 60 ;
    Acteur->Animation.Frame[0][1] = 61 ;
    Acteur->Animation.Frame[0][2] = 62 ;

    //DEAD
    Acteur->Animation.Frame[1][0] = 63 ;
    Acteur->Animation.Frame[1][1] = 64 ;
    Acteur->Animation.Frame[1][2] = 65 ;
    Acteur->Animation.Frame[1][3] = 66 ;
    Acteur->Animation.Frame[1][4] = 67 ;
}