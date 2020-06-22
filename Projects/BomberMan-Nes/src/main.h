#include <raylib.h>
#include "GameObject.h"
#include <raymath.h>
#include "Camera.h"


//MAP DEFINE
//Tile
#define TILEH  16
#define TILEW  16
//Map-Resolution
#define MAPRESOW 416
#define MAPRESOH 214

//Math & Vector
#define Rectangle(x,y,w,h)   (Rectangle){x,y,w,h}
#define Vector2(x,y)   (Vector2){x,y}
#define Vector2Zero  Vector2(0,0)
#define Color(r,g,b,a)  (Color){r,g,b,a}  
#define max(a, b)         ((a) > (b) ? (a) : (b))
#define min(a, b)         ((a) < (b) ? (a) : (b))


//Definition of animation
#define ANIMATIONIDLE 0
#define ANIMATIONLEFT 1
#define ANIMATIONUP 2
#define ANIMATIONDOWN 3
#define ANIMATIONDEAD 4


//Definition of the different tiles
#define WALL 53
#define WALLDESTROY 40
//SceneManager
#define Menu 0 
#define GamePlay 1
#define StageInfo 2 


#define LEFT Vector2(-1,0)
#define RIGHT Vector2(1,0)
#define UP Vector2( 0, -1)
#define DOWN Vector2(0,1)

//Structure
typedef struct Scene
{
  int Numero ;
  char name[20];
  
   
}Scene;

extern Font FontS;
extern Scene ListeScene[3];

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
void rezetPlayer();

//Enemy.c
void updateInfoEnemy() ;
void AddEnemy(GameObject *liste[],Vector2 Spawn);
Enemy *GetEnemyListe() ;
void  SetDeadEnemy(int NumeroEnemy);
void RezetEnemy();

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

 GameObject GameObjectTable[100];
//main.c
void InitMapExecute();


Scene CurentScene;
void RezetTableGaleObject();

//SceneManager.c
void InitScene(Scene *CurentScene);
bool LoadScene( int NumeroScene ,Scene *SceneM);
void updateScene(Scene *SceneM);

//Menu.c
void UpdateCursor(Scene *Scene);


//GameManager.c
void InitGamePlay();
void SetScore(int Points);
int SetBestScore(int Points);
int GetScore();
int GetBestScore();
bool GamePlayPause();
bool GetPause();
int GetStage();
void SetStage(int Numero);
int GetLife();
void SetLife(int i);
int GetTimer();
void SetTime(int i);