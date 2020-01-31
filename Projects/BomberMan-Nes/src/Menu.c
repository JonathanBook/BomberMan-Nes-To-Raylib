#include "main.h"
#include <raylib.h>
#include "Sound.h"

#define CCURSORH 160
#define CURSORW 100

struct Cursor
{
    Vector2 Position[2] ;
  
    int CurentPos ;
};

struct Cursor cursor ;
Vector2 cursorPos ;
Scene scene ;
Texture2D MenuTexture = {0};
Font FontS;

void InitMenu()
{
    FontS = LoadFontEx( "Assets/Font/ARCADE_N.ttf" , 64 , 0 , 0 ); 
    MenuTexture = LoadTexture( "Assets/Image/ecranTitre.png" ) ;

    cursor.Position[0] = Vector2(CURSORW,CCURSORH) ;//START
    cursor.Position[1] = Vector2( (CURSORW + 120 ) , CCURSORH ); //CONTINUE

    cursor.CurentPos = 0;
    cursorPos = cursor.Position[cursor.CurentPos] ;
    PlayMusique(0);
}

void UpdateCursor(Scene *Scene)
{
    //Recup Scene Courente
    scene.Numero = Scene->Numero ;

    if (IsKeyPressed(KEY_A)||
        IsGamepadButtonReleased(GAMEPAD_PLAYER1 ,
        GAMEPAD_BUTTON_LEFT_FACE_UP)
    ) //UP
    {

        if(cursor.CurentPos <= 0 )
        {
            cursor.CurentPos = 1 ;
            cursorPos = cursor.Position[cursor.CurentPos] ;
            return;
        }
    
        cursor.CurentPos -= 1 ;
        cursorPos = cursor.Position[ cursor.CurentPos ] ;
        return ;

    }
    else if (IsKeyPressed(KEY_D)||
            IsGamepadButtonReleased(GAMEPAD_PLAYER1 ,
            GAMEPAD_BUTTON_LEFT_FACE_DOWN)
        ) //DOWN
    {
        if(cursor.CurentPos >=1)
        {
            cursor.CurentPos = 0;
            cursorPos = cursor.Position[ cursor.CurentPos ] ;
            return;
        }
    
        cursor.CurentPos +=1 ;
        cursorPos = cursor.Position[cursor.CurentPos] ;
        return ;
    }
    else if (IsKeyPressed(KEY_ENTER)||
            IsGamepadButtonReleased(GAMEPAD_PLAYER1 ,
            GAMEPAD_BUTTON_MIDDLE_RIGHT)
        ) //Validate
    {
        if(cursor.CurentPos == 0)
        {
            InitGamePlay();
            LoadScene(StageInfo,Scene);
            return;
        }
        else if(cursor.CurentPos == 1)
        { 
            LoadScene(StageInfo,Scene);
            return; 
        }
    }         
  
}

void DrawMenu(Texture2D tilset ,Rectangle ListeRectangle[])
{
    if(scene.Numero == Menu)
    {
        DrawTexturePro(MenuTexture,
            Rectangle(0,0,MenuTexture.width , MenuTexture.height),
            Rectangle(90,10,MenuTexture.width ,MenuTexture.height),
            Vector2Zero,
            0,
            WHITE
        ) ;
        
        DrawTextEx(FontS,"START",Vector2(110,160),10,0,WHITE); 
        DrawTextEx(FontS,"CONTINUE",Vector2(230,160),10,0,WHITE); 
        DrawTextEx(FontS,">",cursorPos,10,0,WHITE); 

    }
    else  if(scene.Numero == StageInfo)
    {
        DrawTextEx(FontS,FormatText("STAGE: %d",GetStage()),
            Vector2((SCREENW/2) -35,SCREENH/2),
            10,
            0,
            WHITE
        ); 
    }
    
   
}