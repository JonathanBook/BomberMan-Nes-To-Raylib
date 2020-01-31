#include "Camera.h"
#include <stdio.h>

#define Vector2(x,y)   (Vector2){x,y}
#define Vector2Zero  Vector2(0,0)

//CAMERA 2D
Camera2D camera= {0};

/*------------------------------*/
Vector2 MiniMum = Vector2Zero ;
Vector2 MaxiMum = Vector2Zero ;
Scal CurentScale = {0};

void CameraLimiteScheck() ;
void ScaleUpdate ();

void CameraInit()
{
    camera.offset = Vector2( SCREENW/2, SCREENH/2 );
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;
}

void CameraUpdate(Vector2 Follow , Vector2 Offset)

{
    camera.target =Vector2(Follow.x + Offset.x , Follow.y + Offset.y );
    CameraLimiteScheck();
    ScaleUpdate ();
}


void CameraLimiteScheck()
{
    //Camera Limit Manager
    
    if( camera.target.x < MiniMum.x )
    {
        camera.target.x = MiniMum.x ;
    }
    else if( camera.target.x > MaxiMum.x )
    {
        camera.target.x = MaxiMum.x ;
    }
    if( camera.target.y < MiniMum.y )
    {
        camera.target.y = MiniMum.y ;
    }
    else if( camera.target.y > MaxiMum.y )
    {
        camera.target.y = MaxiMum.y ;
    }
}

void ScaleUpdate ()
{
    int WinW = GetScreenWidth();
    int WinH = GetScreenHeight();

    if( CurentScale.l != WinW/SCREENW || CurentScale.h != WinH/SCREENH )
    {
        CurentScale.l = WinW/SCREENW ;
        CurentScale.h = WinH/SCREENH;
    
    }
    if(CurentScale.l ==0 || CurentScale.h == 0 )
    {
        CurentScale.l =1 ;
        CurentScale.h =1 ;
    }
}
void SetLimiteCamera(Vector2 Min , Vector2 Max)
{
    MiniMum = Min ;
    MaxiMum = Max ;

}

Camera2D GetCamera()
{
    return camera ;
}