#pragma once

#include "DxLib.h"


//マクロ定義
#define GameFPS 60 //最大fps
#define MicroSecond 1000000.0f //1マイクロ秒
#define MillSecond 1000.0f //ミリ秒
#define WaitTimeMill 3000 //最大で持てるミリ数


//構造体の定義＆名前の再定義
typedef struct _FPS
{
	LONGLONG FirstTakeTime = 0; //1フレーム目の計測時間
	LONGLONG NowTakeTime = 0;  //現在の計測時間
	LONGLONG OldTakeTime = 0;; //以前の計測時間

	float deltaTime = 0.000001f; //デルタタイム(経過時間)
	int FrameCount = 1;  //現在のフレーム数(1フレーム～最大フレーム目まで)
	float Average = 0.0f; //平均FPS値
}FPS;

//外部グローバル変数
extern FPS fps;


//フレームレート関連のプロトタイプ宣言
extern void FPSInit(void);
extern void FPSCheck(void);
extern void FPSDraw(void);
extern void FPSWait(void);






