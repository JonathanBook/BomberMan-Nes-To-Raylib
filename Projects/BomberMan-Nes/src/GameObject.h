#include <raylib.h>
 typedef struct BoxCol{
    float x;
    float y;
    int w;
    int h;
  }BoxCol;
typedef struct GameObject
{
  //MOOV
  float Speed  ;
  Vector2 Velocity  ;
  float MaxSpeed  ;
  Vector2 Position  ;
  Vector2 Offset ;

  
  struct Animation{
    int Frame[10][10] ;
    int MaxFrame  ;
    int NumeroAnimation  ;
    int CurentFrame  ;
    float TimeAnimation ;
    bool Pause  ;
  }Animation ;   
  
 BoxCol BoxCollision ;

  bool Flip  ;

//STATES
  bool isActive;
  bool isGround ;

  
   

}GameObject;

typedef struct Enemy
{
    GameObject Object;
    Vector2 Direction ;
    bool isDead ;
    enum state{
        MOVE,
        CHECK,
        CHOIX
    }State;

}Enemy;

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

typedef struct String{
  char string[50] ;
}String;

typedef struct Bomb
{
    GameObject Objet ;
    float Timer ;
}Bomb;



void DrawGameObject(Texture2D tilset ,Rectangle ListeRectangle[],GameObject*liste[]);
void DrawHud() ;
void SetScoreToScreen(char texte[] ,Vector2 P,float timer);
