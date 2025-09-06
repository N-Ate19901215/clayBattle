#pragma once


#include "DxLib.h"

#define TextureNo 220	//画像の数
#define SoundNo	  20	//サウンドの数

extern int GraphData[TextureNo];//テクスチャを読み込むための配列
extern int AnimData[TextureNo];//アニメーションだけ独立させる

extern int SoundData[SoundNo]; //音を読み込むための配列

extern int LoadFrame;




extern void TitleTextureLoad();		//Title画像のロード
extern void HomeTextureLoad();		//Home画像のロード
extern void ShopTextureLoad();		//Shop画像のロード
extern void BattleTextureLoad();	//Battle画像のロード
extern void ResultTextureLoad();	//Result画像のロード
extern void OptionTextureLoad();	//Option画像のロード
extern void TutorialTextureLoad();    //Tutorial画像のロード 


extern void AnimDataLoad(); //アニメーション用の画像をロードする関数

extern void SoundLoad() ; 	//Titleサウンドのロード




