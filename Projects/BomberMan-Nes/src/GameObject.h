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
;
void DrawGameObject(Texture2D tilset ,Rectangle ListeRectangle[],GameObject*liste[]);
