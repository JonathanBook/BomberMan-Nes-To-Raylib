#include "main.h"

void RezetScore();
//Pause
bool isPause = false;

//Score
int TotalScore = 0 ;
int BestScore ;
int CurentStage =0 ;
int MaximumStage ;
int Life = 3 ;
int Timer = 200;



void InitGamePlay()
{
    RezetScore() ;
    RezetEnemy();
    rezetPlayer();
    RezetTableGaleObject();
    InitMapExecute();
   CurentStage =1;
}

void SetScore(int Points)
{
    TotalScore += Points;
   
}

int SetBestScore(int Points)
{
    BestScore = Points ;
}

int GetScore()
{
    return TotalScore;
}

int GetBestScore()
{
    return BestScore;
}

void RezetScore()
{
    TotalScore = 0 ;
}

bool GamePlayPause()
{
    isPause = !isPause;
    return isPause ;
}

bool GetPause()
{
    return isPause ;
}
int GetStage()
{
    return CurentStage ;
}
void SetStage(int Numero)
{
    CurentStage = Numero ;
}
int GetLife()
{
    return Life ;
}
void SetLife(int i)
{
    Life = i;
}
int GetTimer()
{
    return Timer ;
}
void SetTime(int i)
{
    Timer = i;
}