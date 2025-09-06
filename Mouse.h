#pragma once

#include "DxLib.h"


#define MouseKindMax 3 //マウスボタンの種類
#define MouseErrorIndex 999

typedef struct mousepoint
{
	int x;
	int y;
}MousePoint;


//関数のプロトタイプ宣言

extern void MouseNowIntoOld(void);				//Nowﾅﾝﾁｬﾗ系の変数の値をOldﾅﾝﾁｬﾗ系の変数へ入れる
extern int MouseCodeToIndex(int MOUSE_INPUT_);  //マウスのぼたんこーどを配列の要素数に変換する

extern void MouseInit(void);//まうす入力処理の初期化
extern void MouseUpdate(void);//マウス入力処理の更新
extern bool MouseDown(int MOUSE_INPUT_);//特定のマウスボタンを押したか
extern bool MousePush(int MOUSE_INPUT_);//マウスボタンを押した瞬間の判定
extern bool MouseClick(int MOUSE_INPUT_);//特定のマウスボタンをクリックしたか
extern int  MousePressFrame(int MOUSE_INPUT_);//特定の牡丹を押したフレーム数 


extern MousePoint NowMousePos(void);
extern MousePoint OldMousePos(void);
extern MousePoint DifMousePos(void);
