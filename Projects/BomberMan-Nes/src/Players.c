#include "main.h"
#include <stdio.h>
#include <raymath.h>
#include "Sound.h"
#include <raylib.h>

//DEFINE DIRECTION


//Declaration function
void InitAnimation() ;
bool Isdead = false;
//Touch Delay
float DelayTouche=0;

//POSITION PlayerOne
struct GameObject Player ;

void Init(GameObject *Acteur,GameObject *liste[],Vector2 Spawn);
void InitAnimationPlayer();


void InitPlayers(GameObject *liste[],Vector2 Spawn)
{  
    InitAnimationPlayer();
    Init(&Player,liste , Spawn);

}



void InitAnimationPlayer()
{
    //Idle Position
    Player.Animation.Frame[0][0] = 4;
    printf("ANIMATION IDLE CHARGER \n") ;
   //Walk Left Right
    Player.Animation.Frame[1][0] = 0 ;
    Player.Animation.Frame[1][1] = 1;
    Player.Animation.Frame[1][2] = 2;
    printf("ANIMATION LEFT AND RIGHT CHARGER \n") ;

     //Walk Up
    Player.Animation.Frame[2][0] = 16 ;
    Player.Animation.Frame[2][1] = 17;
    Player.Animation.Frame[2][2] = 18;
    printf("ANIMATION WALK UP CHARGER \n") ;

     //Walk DOWN
    Player.Animation.Frame[3][0] = 3 ;
    Player.Animation.Frame[3][1] = 4;
    Player.Animation.Frame[3][2] = 5;
    printf("ANIMATION WALK DOWN CHARGER \n") ;

    //DEAD
    Player.Animation.Frame[4][0] = 25 ;
    Player.Animation.Frame[4][1] = 26;
    Player.Animation.Frame[4][2] = 27;
    Player.Animation.Frame[4][3] = 28;
    Player.Animation.Frame[4][4] = 29;
    Player.Animation.Frame[4][5] = 30;
    Player.Animation.Frame[4][6] = 31;
    printf("ANIMATION DEAD CHARGER \n") ;
  
}

void Init(GameObject *Acteur,GameObject *liste[],Vector2 Spawn)
{
    //Init position PlayerOne
    Acteur->isActive = true ;
    Acteur->Position = Spawn;
    //Init speed 
    Acteur->Speed = 8 ;
    Acteur->MaxSpeed = 40 ;
    Acteur->Velocity = Vector2Zero;
    Acteur->Offset = Vector2Zero ;
    Acteur->Animation.Pause = false ;
    Acteur->BoxCollision.w = TILEW ;
    Acteur->BoxCollision.h = TILEW ;
    liste[0] = Acteur ;

}

void InputPlayer()
{ if(!Isdead)
        {
        if(DelayTouche!=0)
        {
            DelayTouche-=0.14f;
            if(DelayTouche <0)
                DelayTouche = 0 ;
        }

        if (IsKeyDown(KEY_W) ||IsGamepadButtonDown(GAMEPAD_PLAYER1 , GAMEPAD_BUTTON_LEFT_FACE_UP)) //UP
        {
        MovActeur(UP,&Player) ;
            AppliqueAnimation(ANIMATIONUP,3,&Player);
        } 
        else if (IsKeyDown(KEY_D)||IsGamepadButtonDown(GAMEPAD_PLAYER1 , GAMEPAD_BUTTON_LEFT_FACE_RIGHT))//RIGHT
        {
            Player.Flip = true ;
            MovActeur(RIGHT,&Player) ;
             AppliqueAnimation(ANIMATIONLEFT,3,&Player);
        }
        else if (IsKeyDown(KEY_A)||IsGamepadButtonDown(GAMEPAD_PLAYER1 , GAMEPAD_BUTTON_LEFT_FACE_LEFT))//LEFT
        {
            Player.Flip = false ;
            MovActeur(LEFT,&Player) ;
             AppliqueAnimation(ANIMATIONLEFT,3,&Player);
        }
        else if (IsKeyDown(KEY_S)||IsGamepadButtonDown(GAMEPAD_PLAYER1 , GAMEPAD_BUTTON_LEFT_FACE_DOWN))//DOWN
        {
            MovActeur(DOWN,&Player) ; 
             AppliqueAnimation(ANIMATIONDOWN,3,&Player);  
        }
        else
        {
        
            MovActeur(Vector2Zero,&Player) ;
        }
    
        if(IsKeyReleased(KEY_SPACE) && DelayTouche ==0 ||IsGamepadButtonDown(GAMEPAD_PLAYER1 , GAMEPAD_BUTTON_RIGHT_FACE_DOWN )){
            InstantiateBomb(Player.Position) ;
            DelayTouche = 1 ;
        }
    
 
    } else if(Isdead)
    {
       

        if(Player.Animation.CurentFrame >=Player.Animation.MaxFrame-1 && !Player.Animation.Pause)
        {
            Player.Animation.Pause = true;
            Player.Animation.CurentFrame =0;
            
            InitGamePlay();
            LoadScene(StageInfo,&CurentScene);
        }
    }
     
        
}


void rezetPlayer()
{
    Player.isActive = false ;
    Isdead = false;
}

Vector2 GetPlayerPosition()
{
    return Player.Position ;
}
 
 BoxCol GetBoxColPlayer (){
    return Player.BoxCollision ; 
 }

void SetPlayerDead()
{
    //Player.Velocity = Vector2Zero;
   // Isdead = true;
    //(ANIMATIONDEAD,7,&Player);
}