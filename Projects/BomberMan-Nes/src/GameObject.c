#include "main.h"
#include <raylib.h>
#include <string.h>
//#include "GameObject.h"
typedef struct ScoreMobe
{
  String Texte;
  Vector2 Position;
  bool isActive ;
  float Timer;

}ScoreMobe;

struct ScoreMobe ScoreTemp[10] = {0}  ;

void DrawGameObject(Texture2D tilset ,Rectangle ListeRectangle[],GameObject *liste[])
{
   for (int G = 0; G < 100; G++)
   {
       if(liste[G]!=NULL && liste[G]->isActive)
       {
            int numGameObject = G ;

            int i = liste[G]->Animation.Frame[liste[G]->Animation.NumeroAnimation][liste[G]->Animation.CurentFrame] ;

            Rectangle targetRect =  ListeRectangle[i];

            //Flip management
            if(liste[G]->Flip)
            {
                targetRect = Rectangle( ListeRectangle[i].x, ListeRectangle[i].y,- ListeRectangle[i].width, ListeRectangle[i].height);
            }    

            DrawTexturePro (tilset ,
                targetRect ,
                Rectangle( liste[G]->Position.x , liste[G]->Position.y ,TILEW , TILEH ),
                Vector2Zero,
                0 ,
                WHITE ) ;

           /* --------------------------------PARTIE DEBUG GAMEOBJECT-------------------------------------------------
            BoxCol  C = GetBoxColPlayer();
             DrawRectangleLines(C.x,C.y,C.w,C.h,RED);
             DrawPixel(liste[G]->Position.x,liste[G]->Position.y,BLUE);*/
            UpdateAnimation(liste[G]);
            /* --------------------------------PARTIE DRAW TEXTE-------------------------------------------------*/
            for(int i=0;i<10;i++)
            {    
                if(ScoreTemp[i].isActive)
                {
                    DrawTextEx(FontS,FormatText("%s", ScoreTemp[i].Texte.string),ScoreTemp[i].Position,8,0,WHITE);
                    if(ScoreTemp[i].Timer <=0.0f)
                    {
                        ScoreTemp[i].isActive = false;
                    }else
                    {
                        ScoreTemp[i].Timer-=0.0080f;
                    }
                    
                }
                
            }   
       }
   }    
}

void DrawHud() 
{
     /* --------------------------------PARTIE DRAW HUD SCORE LIFE CURENT STAGE-------------------------------------------------*/
    DrawRectangle(0,0,SCREENW,30,GRAY);
    DrawTextEx(FontS,FormatText("TIME:%d",GetTimer()),Vector2(70,15),8,0,WHITE);
    DrawTextEx(FontS,FormatText("SCORE:%d",GetScore()),Vector2(150,15),8,0,WHITE);
    DrawTextEx(FontS,FormatText("LIFE:%d",GetLife()),Vector2(270,15),8,0,WHITE);
}

void SetScoreToScreen(char texte[] ,Vector2 P,float timer)
{
    for(int i=0;i<10;i++)
    {    
        if(!ScoreTemp[i].isActive){
            strcpy(ScoreTemp[i].Texte.string, texte);
            ScoreTemp[i].Position = P ;
            ScoreTemp[i].Timer = timer ;
            ScoreTemp[i].isActive = true;
        }
    }
}