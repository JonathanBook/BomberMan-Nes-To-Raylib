#include <raylib.h>
#include "main.h"
#include <stdio.h>
#include <raymath.h>
//VARIABLE
typedef  struct TileExplos
{
    Vector2 Position;
    int ImgExplo;
    BoxCol Box ;
}TileExplos;

typedef struct Explosion
{
    float Timer;
    bool isActive;
    TileExplos ListeTile[5][5];
    
}Explosion;



typedef struct Bomb
{
    GameObject Objet ;
    float Timer ;
}Bomb;

Bomb ListeBomb[10]={0};
Explosion ListeExplosion[10] ={0};
GameObject ListeWallDestroy[10]={0};

//DECLARE FUNCTION
void InitBomb( Vector2 Position, GameObject *Acteur) ;
void InitAnimationBomb(GameObject *B);
void GenerateExplosion( Vector2 Position);
void GenerateWallDestroy( Vector2 *Position);

int *liste ;
int contWall = 20 ;
//LOGIQUE
void InstantiateBomb( Vector2 Position)
{
    
    
    for (int i = 0; i < 10; i++)
    {   
        
        if(!ListeBomb[i].Objet.isActive)
        {
            InitAnimationBomb(&ListeBomb[i].Objet) ;
            InitBomb(Position,&ListeBomb[i].Objet);
            liste = GetTableObject();
            liste[i+1] = &ListeBomb[i].Objet ;
            printf("New Bomb\n");
            
            return;
        }
    }
    return;
}


void InitBomb(Vector2 Position,GameObject *Acteur)
{
     //Init position PlayerOne
    Acteur->isActive = true ;
    Position = Vector2( ceil((Position.x -8)/TILEW)*TILEW , ceil((Position.y -8)/TILEH)*TILEH ) ;
    Acteur->Position = Position;
    //Init speed 
    Acteur->Speed = 0 ;
    Acteur->MaxSpeed = 0 ;
    Acteur->Velocity = Vector2Zero;
    Acteur->Offset = Vector2Zero ;
    //Animation Init
    Acteur->Animation.Pause = false ;
    Acteur->Animation.NumeroAnimation =0;
    Acteur->Animation.MaxFrame = 3 ;
    Acteur->BoxCollision.h = TILEH;
    Acteur->BoxCollision.w = TILEW;
    Acteur->BoxCollision.x = Acteur->Position.x;
    Acteur->BoxCollision.y = Acteur->Position.y;
    
}

void InitAnimationBomb(GameObject *B)
{
    B->Animation.Frame[0][0] = 53 ;
    B->Animation.Frame[0][1] = 54 ;
    B->Animation.Frame[0][2] = 55 ;
}

void GenerateExplosion( Vector2 Position)
{
    //Temp Direction
    Vector2 Direction = Vector2Zero ;

    for (int i = 0; i < 10; i++)
    {  
        if(!ListeExplosion[i].isActive )     
        {   
            for (int D=0; D <5; D++)
            {   
                //Select Direction
                if(D == 1) { Direction = LEFT; }
                if(D == 2 ){ Direction = RIGHT; }
                if(D == 3 ){ Direction = UP; }
                if(D == 4 ){ Direction = DOWN ; }


                for ( int L = 1; L < 5; L++)
                {
                    //CalCul Direction
                   Vector2 NewDirection  = Vector2Add( Position ,
                        Vector2((16 * Direction.x) * L ,
                        (16 * Direction.y) * L  )) ;

                    //Save Direction
                    ListeExplosion[i].ListeTile[D][L].Position = NewDirection ;
                    //Init BoxCollision TileExplos
                    ListeExplosion[i].ListeTile[D][L].Box.x = NewDirection.x;
                    ListeExplosion[i].ListeTile[D][L].Box.y = NewDirection.y;
                    ListeExplosion[i].ListeTile[D][L].Box.w = TILEW;
                    ListeExplosion[i].ListeTile[D][L].Box.h = TILEH;
                    
                    BoxCol Player  = GetBoxColPlayer() ;
                    
                    if( CheckCollision( &Player , &ListeExplosion[i].ListeTile[D][L].Box ) )
                    { SetPlayerDead();}

                    int Tile = GetTile(NewDirection);

                    if(Tile== WALL || Tile == WALLDESTROY || L == 4)
                    {

                        if(D==1){ListeExplosion[i].ListeTile[D][L].ImgExplo = 8; }//End Left
                        if(D==2){ListeExplosion[i].ListeTile[D][L].ImgExplo = 10;}//End Right
                        if(D==3){ListeExplosion[i].ListeTile[D][L].ImgExplo = 6; }//End Up
                        if(D==4){ListeExplosion[i].ListeTile[D][L].ImgExplo = 11;//End Down
                            ListeExplosion[i].isActive = true;//Explosion Complete Ative Explosion
                            ListeExplosion[i].Timer = 5.0f ;}//Define Time Destroy Explosion ;

                            //TODO:TENPS PARAMETRE TEST
                        if(Tile == WALLDESTROY)
                        {
                            SetTile(NewDirection,-1);
                            GenerateWallDestroy( &NewDirection);
                        }

                        break ;
                    }
                    else
                    {


                        if(D==1 || D==2){ListeExplosion[i].ListeTile[D][L].ImgExplo = 9; }
                        if(D==3 || D==4){ListeExplosion[i].ListeTile[D][L].ImgExplo = 7; }
                        
                        if(D==0){ListeExplosion[i].ListeTile[D][L].ImgExplo = 12; break;}                        
                    }
                
                }
                
            }
            return;
        }
    }         
}

void GenerateWallDestroy( Vector2 *Position)
{
    for (int i = 0; i < 10; i++)
    {
        if(!ListeWallDestroy[i].isActive)
        {
            ListeWallDestroy[i].isActive = true;
            ListeWallDestroy[i].Animation.Frame[0][0] = 41 ;
            ListeWallDestroy[i].Animation.Frame[0][1] = 42 ;
            ListeWallDestroy[i].Animation.Frame[0][2] = 43 ;
            ListeWallDestroy[i].Animation.Frame[0][3] = 44 ;
            ListeWallDestroy[i].Animation.Frame[0][4] = 45 ;
            ListeWallDestroy[i].Animation.Frame[0][5] = 46 ;
            ListeWallDestroy[i].Position = *Position ;
            ListeWallDestroy[i].Speed = 0 ;
            ListeWallDestroy[i].MaxSpeed = 0 ;
            ListeWallDestroy[i].Velocity = Vector2Zero;
            ListeWallDestroy[i].Offset = Vector2Zero ;
            //Animation Init
            ListeWallDestroy[i].Animation.Pause = false ;
            ListeWallDestroy[i].Animation.CurentFrame =0 ;
            ListeWallDestroy[i].Animation.NumeroAnimation =0;
            ListeWallDestroy[i].Animation.MaxFrame = 5 ;
            if(contWall >30){contWall = 20;}    
            
            liste[contWall] = &ListeWallDestroy[i];
            contWall++;
            return;


        }
    }
}

void BombsUpdate()
{
     for (int i = 0; i < 10; i++)
     {
        if( ListeBomb[i].Objet.isActive )
        {
            if(ListeBomb[i].Timer >10 )
            {
                ListeBomb[i].Objet.isActive = false ;
                ListeBomb[i].Timer = 0 ;
                GenerateExplosion(ListeBomb[i].Objet.Position);
             
            }//Update Time       
            else { ListeBomb[i].Timer+=0.14f; }

        }
     }

     for (int i = 0; i < 10; i++)
     {
        if( ListeWallDestroy[i].isActive )
        {
           if( ListeWallDestroy[i].Animation.CurentFrame >= ListeWallDestroy[i].Animation.MaxFrame -1 )
           {
                ListeWallDestroy[i].Animation.Pause = true ;
                ListeWallDestroy[i].isActive = false ;
           }
        }
     }
}

void DrawExplosion(Texture2D tilset ,Rectangle ListeRectangle[])
{
    for (int i = 0; i < 10; i++)
    {
        if(ListeExplosion[i].isActive)
        {

            ListeExplosion[i].Timer -=0.14f;
            if(ListeExplosion[i].Timer <0)
            {
                ListeExplosion[i].Timer =0 ;
                ListeExplosion[i].isActive = false;
            }

           
           for (int D = 0; D < 5; D++)
            { 
                for ( int L = 0; L < 5; L++)
                {
                    if(ListeExplosion[i].ListeTile[D][L].ImgExplo !=0)
                    {
                        Rectangle targetRect = ListeRectangle[ListeExplosion[i].ListeTile[D][L].ImgExplo];

                        DrawTexturePro (tilset ,
                        targetRect ,
                        Rectangle( ListeExplosion[i].ListeTile[D][L].Position.x ,
                            ListeExplosion[i].ListeTile[D][L].Position.y ,TILEW , TILEH ),
                        Vector2Zero,
                        0 ,
                        WHITE ) ;
                    }
                     if(!ListeExplosion[i].isActive)
                     {
                         ListeExplosion[i].ListeTile[D][L].ImgExplo = 0;
                     }
                }
                
            }
        }   
    }
    
}