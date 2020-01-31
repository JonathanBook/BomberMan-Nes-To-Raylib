#include <raylib.h>
#include "main.h"
#include <stdio.h>

void AddAnimation(GameObject *Acteur);
void InitEnemy(GameObject *Acteur,GameObject *liste[],Vector2 Spawn);
bool GetColBomb(Enemy *E);
//Compare de vector2 
bool Vector2Compare(Vector2 a ,Vector2 b)
{
    if(a.x == b.x && a.y == b.y)
        return true ;
    return false;
}
 



int ContEnemy = 30 ;
//VARIABLES
 Enemy ListeEnemy[10]={0};

void AddEnemy(GameObject *liste[],Vector2 Spawn)
{
    for(int i =0;i<10;i++)
    {
     
        InitEnemy( &ListeEnemy[ContEnemy-30].Object , liste , Spawn ) ;
        ListeEnemy[ContEnemy-30].State = MOVE;
        ListeEnemy[ContEnemy-30].Direction = LEFT ;
        
        return ;
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
    Acteur->BoxCollision.x = Spawn.x ;
    Acteur->BoxCollision.y = Spawn.y;
    Acteur->Animation.NumeroAnimation =0 ;
    Acteur->Animation.MaxFrame = 3;
    Acteur->Animation.CurentFrame = 2;
    
    AddAnimation(Acteur) ;
  
    
    liste[ContEnemy] = Acteur ;
    ContEnemy +=1;
    
    
    
  

}
int V=0;
void updateInfoEnemy()
{
   
   for(int i=0;i<10;i++){

        if(ListeEnemy[i].Object.isActive)
        {
            
            Enemy *Acteur = &ListeEnemy[i] ;

            if(Acteur->isDead){
                if(Acteur->Object.Animation.CurentFrame >= Acteur->Object.Animation.MaxFrame-1)
                {
                    Acteur->Object.isActive = false ;
                    SetScoreToScreen("400",ListeEnemy[i].Object.Position,1);
                    SetScore(400) ;
                }
            }
            else
            {
                
            
             // printf("n: %d \n",Acteur->State);
                switch (Acteur->State)
                {
                case MOVE :
                    //Check Collision player 
                    
                    if(CheckCollision(&Acteur->Object.BoxCollision ,&GetBoxColPlayer() ))
                    {
                        //Player Dead
                        SetPlayerDead();

                    }else if(GetColBomb(Acteur))//Check Collision to Bombs
                    {
                        if(Vector2Compare(Acteur->Direction , LEFT)){
                            
                            Acteur->Direction = RIGHT;

                        }else if(Vector2Compare(Acteur->Direction , RIGHT))
                        {
                            Acteur->Direction = LEFT;

                        }else if(Vector2Compare(Acteur->Direction , UP))
                        {
                            Acteur->Direction = DOWN;

                        }else if(Vector2Compare(Acteur->Direction , DOWN))
                        {
                            Acteur->Direction = UP;
                        }
                        if(MovActeur(Acteur->Direction,Acteur)){//if Mov Acteur Emet Collision 
                            //Enemie Doit CHoisre 
                            Acteur->State = CHOIX ;
                            return;
                        }
                        
                    } else //Mov Enemy is NOt Collision Player
                    {
                        if(MovActeur(Acteur->Direction,Acteur)){//if Mov Acteur Emet Collision 
                            //Enemie Doit CHoisre 
                            Acteur->State = CHOIX ;

                        }else
                        {
                            //if not COllision 1Chance Sur 50 De Choisire une Autre Direction 
                            V= GetRandomValue(0,50);
                            if(V == 2){ Acteur->State = CHOIX ;}
                        } 
                    }
                    break;
                
                case CHECK :
                    break;    

                case CHOIX :
                    
                    if(GetTile(Vector2Add(Acteur->Object.Position , Vector2(-TILEW,-TILEH/2)) ) == -1 &&
                        GetTile(Vector2Add(Acteur->Object.Position , Vector2(8,-TILEH/2))) == -1 &&
                        GetTile(Vector2Add(Acteur->Object.Position , Vector2(-8,-16))) == -1 &&
                        GetTile(Vector2Add(Acteur->Object.Position , Vector2(-8,8))) == -1
                    )//Left  Right Up DownCHECK
                    {
                        V = GetRandomValue(0,5);
                        if(V == 1){Acteur->Direction = LEFT;}else
                        if(V == 2){Acteur->Direction = RIGHT;}else
                        if(V == 3){Acteur->Direction = UP;}else
                        if(V == 4){Acteur->Direction = DOWN;}
                    

                    }else if(GetTile(Vector2Add(Acteur->Object.Position , Vector2(8,-TILEH/2))) == -1 &&
                        GetTile(Vector2Add(Acteur->Object.Position , Vector2(-8,-16))) == -1 &&
                        GetTile(Vector2Add(Acteur->Object.Position , Vector2(-8,8))) == -1
                    )//Right Up DownCHECK
                    {
                        V = GetRandomValue(0,4);
                        if(V == 1){Acteur->Direction = RIGHT;}else
                        if(V == 2){Acteur->Direction = UP;}else
                        if(V == 3){Acteur->Direction = DOWN;}


                    }else if(GetTile(Vector2Add(Acteur->Object.Position , Vector2(-8,-16))) == -1 &&
                        GetTile(Vector2Add(Acteur->Object.Position , Vector2(-8,8))) == -1
                    )// Up DownCHECK

                    {
                        V = GetRandomValue(0,3);
                        if(V == 1){Acteur->Direction = UP;}else
                        if(V == 2){Acteur->Direction = DOWN;}

                    }else if (GetTile(Vector2Add(Acteur->Object.Position , Vector2(-TILEW,-TILEH/2)) ) == -1 &&
                        GetTile(Vector2Add(Acteur->Object.Position , Vector2(-8,8))) == -1
                        )//Left Down Check
                    {
                        
                        V = GetRandomValue(0,3);
                        if(V == 1){Acteur->Direction = LEFT;}else
                        if(V == 2){Acteur->Direction = DOWN;}

                    }else if(GetTile(Vector2Add(Acteur->Object.Position , Vector2(-8,8))) == -1 )//Down CHeck
                    {
                        Acteur->Direction = DOWN;

                    }else if(GetTile(Vector2Add(Acteur->Object.Position , Vector2(-8,-16))) == -1)//Up Check
                    {
                        Acteur->Direction = UP;

                    }else if (GetTile(Vector2Add(Acteur->Object.Position , Vector2(-TILEW,-TILEH/2)) ) == -1 )// Left Check
                    {
                        Acteur->Direction = LEFT ;

                    }else if(GetTile(Vector2Add(Acteur->Object.Position , Vector2(8,-TILEH/2))) == -1) //Right Check
                    {
                        Acteur->Direction = RIGHT ;
                    }
                    
                    Acteur->State = MOVE ;
                    break; 

                default: 
                    break;
                }
            }  
        }      
    }       
     
}

Enemy *GetEnemyListe()
{
    return ListeEnemy ;
}


void AddAnimation(GameObject *Acteur)
{
    //WALK LEFT RIGHT
    Acteur->Animation.Frame[0][0] = 65 ;
    Acteur->Animation.Frame[0][1] = 66 ;
    Acteur->Animation.Frame[0][2] = 67 ;

    //DEAD
    Acteur->Animation.Frame[1][0] = 68 ;
    Acteur->Animation.Frame[1][1] = 69 ;
    Acteur->Animation.Frame[1][2] = 70 ;
    Acteur->Animation.Frame[1][3] = 71 ;
    Acteur->Animation.Frame[1][4] = 72 ;
}

bool GetColBomb(Enemy *E)
{
    Bomb *liste = GetListeBomb();

    for(int i=0;i<10;i++)
    {
        Bomb B = liste[i];
        if(B.Objet.isActive)
        {
            if(CheckCollision(&E->Object.BoxCollision ,&B.Objet.BoxCollision)){
                
                return true ;
            }
        }

        
    }
    return false;
}
void SetDeadEnemy(int NumeroEnemy)
{
    Enemy *E = &ListeEnemy[NumeroEnemy] ;
    AppliqueAnimation(1,4,E);
    E->isDead= true ;
    
}

void RezetEnemy()
{
    ContEnemy = 30;
    for(int i=0;i<10;i++)
    {
         ListeEnemy[i].Object.isActive = false ;
         ListeEnemy[i].isDead = false;

    }
   
}