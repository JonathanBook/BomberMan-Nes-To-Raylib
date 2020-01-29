#include <raylib.h>
#include "GameObject.h"
#include <raymath.h>

#define SCREENH 240
#define SCREENW 400
#define Rectangle(x,y,w,h)   (Rectangle){x,y,w,h}
#define Vector2(x,y)   (Vector2){x,y}
#define Vector2Zero  Vector2(0,0)
#define Color(r,g,b,a)  (Color){r,g,b,a}  
#define max(a, b)         ((a) > (b) ? (a) : (b))
#define min(a, b)         ((a) < (b) ? (a) : (b))
#define Scale(l,h) (Scale){l,h}

//Definition of animation
#define ANIMATIONIDLE 0
#define ANIMATIONLEFT 1
#define ANIMATIONUP 2
#define ANIMATIONDOWN 3
#define ANIMATIONDEAD 4

//MAP DEFINE
#define TILEH  16
#define TILEW  16
#define MAPRESOW 800
#define MAPRESOH 448
//Definition of the different tiles
#define WALL 53
#define WALLDESTROY 40
//SceneManager
#define Menu 0 
#define GamePlay 1
#define BONUUSIMG 76

#define LEFT Vector2(-1,0)
#define RIGHT Vector2(1,0)
#define UP Vector2( 0, -1)
#define DOWN Vector2(0,1)

typedef struct Scale
{
    float l ;
    float h ;
}Scale;

void InitPause();
//map.c
void InitMap(GameObject *l[]) ;
void DrawMap(Texture2D tilset, Rectangle ListeRectangle[]);
int GetTile(Vector2 Pposition) ;
bool SetTile(Vector2 Pposition , int Ptile) ; 

//player.c
void InitPlayers(GameObject *liste[] ,Vector2 Spawn);
Vector2 GetPlayerPosition();
BoxCol GetBoxColPlayer ();
void InputPlayer();
void SetPlayerDead();

//Enemy.c
void updateInfoEnemy() ;
void AddEnemy(GameObject *liste[],Vector2 Spawn);
Enemy *GetEnemyListe() ;
void  SetDeadEnemy(int NumeroEnemy);

//Mov.c
bool MovActeur(Vector2 Direction , GameObject *Acteur);

//Bomb.c
void InstantiateBomb(Vector2 Position);
void DrawExplosion(Texture2D tilset ,Rectangle ListeRectangle[]);
void BombsUpdate();
Bomb *GetListeBomb();

//Animation.c
void AppliqueAnimation(int NumeroAnimation , int MaxFrame, GameObject *Acteur);
void UpdateAnimation( GameObject *Acteur);

//Collision.c
bool CheckCollisionMap(GameObject *Acteur);
bool CheckCollision(BoxCol *A , BoxCol *B);


//main.c
void InitMapExecute();
int *GetTableObject();


//SceneManager.c
bool LoadScene( int NumeroScene ,int*SceneM);



//GameManager.c
void InitGamePlay();
int SetScore(int Points);
int SetBestScore(int Points);
int GetScore();
int GetBestScore();
bool GamePlayPause();
bool GetPause();

