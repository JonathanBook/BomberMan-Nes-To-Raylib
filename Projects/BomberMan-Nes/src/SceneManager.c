#include "main.h"
#include <raylib.h>
#include <stdio.h>
#include "Sound.h"
#include <string.h>

float timeInfoStage = 0;

void InitScene(Scene *CurentScene)
{
  ListeScene[Menu].Numero =0 ;
  strcpy(ListeScene[Menu].name,"Menu");

  ListeScene[StageInfo].Numero =2 ;
  strcpy(ListeScene[StageInfo].name,"StageInfo");

  ListeScene[GamePlay].Numero =1 ;
  strcpy(ListeScene[GamePlay].name,"GamePlay");

//Scene Par default Menu
  *CurentScene = ListeScene[Menu];

}

bool LoadScene( int Numero ,Scene *SceneM)
{   
  *SceneM = ListeScene[Numero] ;
  if( Numero == StageInfo){ stopMusic(0); stopMusic(1); PlayFx(0); }else
  if( Numero == GamePlay){ stopMusic(0); PlayMusique(1); }
  return true;
}

void updateScene(Scene *SceneM)
{
  if(SceneM->Numero == StageInfo){

    if(timeInfoStage >=1.5f)
    {
      LoadScene(GamePlay,SceneM) ;

      timeInfoStage = 0.0f;

    }
    else
    {
      timeInfoStage +=0.0080f;
    }    
  }
}
