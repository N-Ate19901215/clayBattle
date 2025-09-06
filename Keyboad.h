#pragma once


#include "DxLib.h"


//マクロ定義
#define KeyKindMax 256 //キーの種類



//キーボード入力関連のプロトタイプ宣言
extern void KeyInit(void);//キー入力処理の初期化
extern void KeyUpdate(void);//キー入力処理の更新
extern bool KeyDown(int KEY_INPUT_);//特定のキーを押したか
extern bool KeyPush(int KEY_INPUT_);//Iキーを押した瞬間の判定
extern bool KeyClick(int KEY_INPUT_);//特定のキーをクリックしたか
extern int KeyPressFrame(int KEY_INPUT_);//特定のキーを押したフレーム数 



