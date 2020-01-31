#include "main.h"
#include <math.h>
#include <stdio.h>


//Height and width in number of tiles
#define MAPW  26 
#define MAPH  14 

#define TILEMAPW 16
#define TILEMAPH 16

int Map[] ={53,53,53,53,53,53,53,53,53,53,53,53,53,53,53,53,53,53,53,53,53,53,53,53,53,53,
53,0,40,0,0,0,0,0,0,40,0,0,0,0,0,0,0,0,0,0,0,40,0,0,0,53,
53,0,40,0,0,40,40,0,66,40,0,0,40,40,0,40,40,0,66,0,40,40,40,0,40,53,
53,0,0,0,0,40,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,53,
53,0,40,0,53,40,40,40,40,40,53,0,40,0,40,53,40,40,40,40,53,40,0,40,40,53,
53,0,40,0,40,0,0,0,0,0,0,0,40,0,0,0,0,0,0,0,0,0,0,0,40,53,
53,0,0,0,40,40,40,40,40,40,0,0,0,0,0,40,40,40,0,40,40,40,40,0,40,53,
53,0,1,0,40,0,0,0,0,40,0,0,40,0,0,0,0,40,0,40,0,0,0,0,40,53,
53,0,0,0,40,0,0,0,0,0,0,0,40,0,66,0,0,40,0,0,0,0,66,0,40,53,
53,40,40,40,53,0,40,40,40,40,53,40,40,40,40,53,40,40,40,0,53,0,40,40,40,53,
53,0,0,0,0,0,40,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,40,0,53,
53,0,40,0,66,0,40,0,40,40,0,40,0,40,40,0,40,0,40,40,40,0,0,40,0,53,
53,0,40,0,0,0,0,0,0,0,0,40,0,0,0,0,40,0,0,0,0,66,0,0,0,53,
53,53,53,53,53,53,53,53,53,53,53,53,53,53,53,53,53,53,53,53,53,53,53,53,53,53};


int TableMap[MAPW][MAPH] = {0} ;

void InitMap(GameObject *l[])
{
    for (int y = 0; y < MAPH; y++)
    {
        for (int x = 0; x < MAPW; x++)
        {
            int tile = Map[ x + y * MAPW ] ;
            if (tile !=0 && tile!=1 && tile!=66  )
            {
                
                TableMap[x][y] = tile ;
            }
            else 
            {

                if(tile == 1)
                {
                   InitPlayers( l,Vector2 (x * TILEW , y * TILEH));
                }else if(tile == 66)
                {
                    AddEnemy(l,Vector2 (x * TILEW , y * TILEH));
                }
               
                TableMap[x][y] = -1  ;
            }
            
        }
    }
  //  DefineGameObjectTable(&l);
}

//Lets you know which tile is at a given position
int GetTile(Vector2 Pposition)
{
    int x = ceil ( Pposition.x / TILEMAPW ) ;  
    int y = ceil ( Pposition.y / TILEMAPH );

    return TableMap[x][y-1] ;

}

//Allows you to modify a tile at a given position
bool SetTile(Vector2 Pposition , int Ptile)
{   

    if(GetTile(Pposition)!=NULL)
    {
        int x = ceil ( Pposition.x / TILEMAPW ) ;  
        int y = ceil ( Pposition.y / TILEMAPH );

        TableMap[x][y-1] = Ptile ;
       
        return true ;
       
    }

    printf("HEREUR TILE NOT SET POSITION INVALIDE \n ") ;
    return false ;

}

//Draw the map on the screen
void DrawMap(Texture2D tilset, Rectangle ListeRectangle[])
{


    for (int y =  0; y < MAPH; y++)
    {
        for (int x =  0; x < MAPW; x++)
        {

            int tile = TableMap[x][y];
            if (tile !=NULL && tile !=-1)
            {
                /* code */
                  DrawTexturePro(tilset ,
                   ListeRectangle[tile-1 ],
                   Rectangle(x * TILEW , (y+1) * TILEH, TILEW , TILEH ),
                   Vector2Zero,0,WHITE);

            }
        }
    }    
}