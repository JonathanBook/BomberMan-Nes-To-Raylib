#include "main.h"
#include <raylib.h>
#include <raymath.h>
#include "Sound.h"

//Ressources
Texture2D tilset ={0} ;
Rectangle ListeRectangle[97] ;

Texture2D OverlayImg ;

//FlachTexte Press Start
float TimeFlachTexte = 0 ;
bool TextIsVisible;

Color BackGround = BLACK ;

void TileDecoup();
void DrawMenu(Texture2D tilset ,Rectangle ListeRectangle[]);
void InitMenu();


void DrawInfoPlayer();

GameObject GameObjectTable[100]={0};
Scene ListeScene[3]={0} ;
Scene CurentScene;

int main()
{
    // Initialization
    //--------------------------------------------------------------------------------------
    int screenWidth = 426;
    int screenHeight = 240;
   
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(screenWidth, screenHeight, "BomBer Man Nes");
    SetWindowMinSize(SCREENW,SCREENH);


    SetTargetFPS(60);

    //----------------------------------RESSOURCES LOAD----------------------------------------------------
    tilset = LoadTexture("Assets/Image/TilsetBomberMan.png");
    OverlayImg = LoadTexture("Assets/Image/Nintendo-Entertainment-System-Bezel-16x10-1680x1050.png");
//---------------------------------------------------------------------------------------------------------
    initSound(GetPause());
    TileDecoup();
    InitMenu();
    InitScene(&CurentScene);
    CameraInit();
    SetLimiteCamera(Vector2(180,107) , Vector2(220,107));
    
    RenderTexture2D targetTexture = LoadRenderTexture (SCREENW , SCREENH ) ;
    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        SoundUpdate(GetPause());
        InitPause();

        if(CurentScene.Numero == GamePlay && !GetPause())
        {
            Vector2 playerPos = GetPlayerPosition();

           // camera.target.x = playerPos.x +20;
            CameraUpdate( playerPos , Vector2( 20.0f , 20.0f ) );
            
           // camera.target.y = 107;

            InputPlayer();
            BombsUpdate();
            updateInfoEnemy();
            
        }else if(CurentScene.Numero !=GamePlay)
        { 
            CameraUpdate( Vector2Zero,Vector2Zero);
            camera.target = Vector2(SCREENW/2,SCREENH/2);
            
            UpdateCursor(&CurentScene);  
            updateScene(&CurentScene) ;
        }
        //----------------------------------------------------------------------------------
    
        // Draw
        //----------------------------------------------------------------------------------
        //Je DESSINE MA TEXTURE
        BeginTextureMode(targetTexture);

            ClearBackground(BackGround);

            if(CurentScene.Numero == GamePlay)
                DrawHud();

            BeginMode2D(camera);
                
                if(CurentScene.Numero == GamePlay)
                {
                    BackGround = GREEN;

                    DrawMap(tilset,ListeRectangle);
                    DrawGameObject(tilset,ListeRectangle,&GameObjectTable);
                    DrawExplosion(tilset ,ListeRectangle);
         
                }else if(CurentScene.Numero == Menu || CurentScene.Numero == StageInfo)
                {
                    BackGround = BLACK ;

                    //Draw BackGround Menu
                    DrawMenu(tilset ,ListeRectangle);
                 
                }
                
            EndMode2D();
              
        EndTextureMode();

        //JAFFICHE MA TEXTURE 
        BeginDrawing();
             ClearBackground(WHITE);

            DrawTexturePro(targetTexture.texture,
                Rectangle(0 ,0,-SCREENW,SCREENH) ,
                Rectangle( (SCREENW +30) * CurentScale.l ,
                SCREENH * CurentScale.h ,
                SCREENW * CurentScale.l  , 
                SCREENH* CurentScale.h  ),
                Vector2Zero ,
                180,
                WHITE
            );

            DrawTexturePro(OverlayImg,
                Rectangle(0,0,1920,1080),
                Rectangle(0,0, (screenWidth+53) *CurentScale.l,
                (screenHeight+15 )* CurentScale.h),
                Vector2Zero,
                0,
                WHITE);
            
            DrawFPS(10,10);
        EndDrawing();
        //----------------------------------------------------------------------------------
    }
    // De-Initialization

    //--------------------------------------------------------------------------------------   
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
void TileDecoup()
{
    //H=hauteur
    //L=Largeur

    int count = -1 ;
    for ( int H = 0; H <tilset.height/TILEH; H++)
    {
        for (int L = 0; L < tilset.width/TILEW; L++)
        {
            count +=1;
            ListeRectangle[count] = Rectangle( L * TILEW , H * TILEH , TILEW , TILEH ) ;
        }
    } 
}

void InitMapExecute()
{
    InitMap(&GameObjectTable);
}
void InitPause()
{
     if(IsKeyReleased(KEY_P))
    {
        if(CurentScene.Numero == GamePlay)
            GamePlayPause();
    } 
}

void RezetTableGaleObject()
{
    for(int i=0;i<100;i++){
        GameObjectTable[i].isActive = false ;
    }  
}

    GameObject GetTableObject()
   {
       return &GameObjectTable ;
   }
/*TableGameObject  0 = PLayer de 1 a 10 = bomb 10 a 20 = explosion 20 a 30 = wall destroy*/