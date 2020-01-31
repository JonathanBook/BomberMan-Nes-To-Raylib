#include <raylib.h>

//Screen Game Define
#define SCREENH 240
#define SCREENW 400

#define WINDOWSW 1280
#define WINDOWSH 720
#define Scale(l,h) (Scale){l,h}

typedef struct Scal
{
    float l ;
    float h ;
}Scal;

//Variables
extern  Scal CurentScale ;
extern Camera2D camera ;


void SetLimiteCamera( Vector2 Min , Vector2 Max ) ;
void CameraUpdate( Vector2 Follow , Vector2 Offset ) ;
void CameraInit();
Camera2D GetCamera();