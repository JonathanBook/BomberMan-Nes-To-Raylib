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

Scale CurentScale = Scale(0,0);

typedef struct SceneManager
{
    int CurentScene ;
   
}SceneManager;


void ScaleUpdate ();
void TileDecoup();
void DrawMenu(Texture2D tilset ,Rectangle ListeRectangle[]);
void InitMenu();
void UpdateCursor(int *Scene);
void CameraLimiteScheck(Camera2D *camera);
void DrawInfoPlayer();

static GameObject GameObjectTable[100]={0};

SceneManager Scene ;



int main()
{
    // Initialization
    //--------------------------------------------------------------------------------------
    int screenWidth = 426;
    int screenHeight = 240;
   
 

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(screenWidth, screenHeight, "BomBer Man Nes");
    SetWindowMinSize(SCREENW,SCREENH);
    
    //CAMERA 2D
    Camera2D camera = { 0 };
    camera.offset = (Vector2){ SCREENW/2, SCREENH/2 };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    SetTargetFPS(60);
    //----------------------------------RESSOURCES LOAD----------------------------------------------------
    tilset = LoadTexture("Assets/Image/TilsetBomberMan.png");
    OverlayImg = LoadTexture("Assets/Image/Nintendo-Entertainment-System-Bezel-16x10-1680x1050.png");
//---------------------------------------------------------------------------------------------------------
    initSound(GetPause());
    TileDecoup();
    InitMenu();
    
    Scene.CurentScene = 0 ;
    RenderTexture2D targetTexture = LoadRenderTexture (SCREENW , SCREENH ) ;
    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        ScaleUpdate() ;
        SoundUpdate(GetPause());
        InitPause();
        if(Scene.CurentScene == GamePlay && !GetPause())
        {
            Vector2 playerPos = GetPlayerPosition();
            camera.target =Vector2(playerPos.x + 20 , playerPos.y + 20 );
            InputPlayer();
            CameraLimiteScheck(&camera);
            BombsUpdate();
            updateInfoEnemy();
            
        }else if(Scene.CurentScene == Menu)
        {
            camera.target = Vector2(SCREENW/2,SCREENH/2);
           
            UpdateCursor(&Scene.CurentScene);

           
        }
        
        
        //CameraManager();
        //----------------------------------------------------------------------------------
    
        // Draw
        //----------------------------------------------------------------------------------
        //Je DESSINE MA TEXTURE
        BeginTextureMode(targetTexture);
            BeginMode2D(camera);
                
                ClearBackground(GREEN);

                if(Scene.CurentScene ==GamePlay)
                {
                    DrawMap(tilset,ListeRectangle);
                    DrawGameObject(tilset,ListeRectangle,&GameObjectTable);
                    DrawExplosion(tilset ,ListeRectangle);
         

                }else if(Scene.CurentScene == Menu)
                {
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

void ScaleUpdate ()
{
    int WinW = GetScreenWidth();
    int WinH = GetScreenHeight();

    if(CurentScale.l != WinW/426|| CurentScale.h != WinH/240 )
    {
      
        CurentScale.l = WinW/426 ;
        CurentScale.h = WinH/240;
    
    }
    if(CurentScale.l ==0 || CurentScale.h == 0 )
    {
        CurentScale.l =1 ;
        CurentScale.h =1 ;
    }
}

void CameraLimiteScheck(Camera2D *camera)
{
    //Camera Limit Manager
    if(camera->target.x <180)
    {
        camera->target.x = 180;
    }
    if(camera->target.x >600)
    {
        camera->target.x = 600;
    }
    if(camera->target.y <107)
    {
        camera->target.y = 107; 
    }
        
    if(camera->target.y >320)
    {
        camera->target.y = 320 ; 
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
        if(Scene.CurentScene == GamePlay)
            GamePlayPause();
    }

   
}



int *GetTableObject()
   {
       return GameObjectTable ;
   }
/*TableGameObject  0 = PLayer de 1 a 10 = bomb 10 a 20 = explosion 20 a 30 = wall destroy*/