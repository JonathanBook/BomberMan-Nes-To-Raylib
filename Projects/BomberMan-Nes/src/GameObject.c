#include "main.h"
#include <raylib.h>
//#include "GameObject.h"

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

           /* --------------------------------PARTIE DEBUG GAMEOBJECT-------------------------------------------------*/
            BoxCol  C = GetBoxColPlayer();
             DrawRectangleLines(C.x,C.y,C.w,C.h,RED);
             DrawPixel(liste[G]->Position.x,liste[G]->Position.y,BLUE);
              UpdateAnimation(liste[G]);
       }
        
        

   }
   
    
  

    
    
    

    
   


    
}