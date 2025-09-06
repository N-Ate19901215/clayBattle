#pragma once




#include "DxLib.h"
#include "Mouse.h"

//マクロ定義
#define width  1920
#define height 1080
#define bit		32
#define GameTitle "CreyShooting"
#define GameVsync true

#define DebugMode false //デバッグモード

#define GameSceneCount 8 //シーンの数
#define GameSceneNameMax 20 //シーン名の文字数

#define GameSceneChangeFrame 60 //シーン切り替えが可能になる経過フレーム数

#define WinScore 5 // 勝利スコア

//線分を作る関数用のマクロ定義











//ゲームシーン
enum GameScene{
	TitleScene,
	MainScene,
	AtackScene,
	DefScene,
	ResultScene,
	ShopScene,
	SoloScene,
	OptionScene,
	TutorialScene,
};




//グローバル変数
extern enum GameScene NowGameScene; //現在のゲームシーン
extern enum GameScene ChangeGameScene; //移行先のゲームシーン


extern float AtackScore;//攻撃側のスコア
extern float DefenceScore;//防衛側のスコア

//発射台構造体
typedef struct _hasya {
	bool color = true;
	int v = 1;
	int r = 1;
	//----------------------材質　---------------------
	bool zaisitu = false;
	//int cost = 0;
}hasya;

extern hasya hasyaL;
extern hasya hasyaR;

//クレイの構造体
typedef struct _cley 
{
	VECTOR Position;//位置
	VECTOR Velocity;//移動の速さ
	VECTOR Angle;	//角度
	VECTOR BreakPosition;//2壊れた位置
	VECTOR Dir;	//クレイの方向
	int Color = 0;		//色 (1 => 青色、　2 => 赤色　)
	bool IsMoving = false;	//動いている状態か否か
	int Break;//2のクレーが壊れたか否か
	float BreakMoveX;//2が壊れた後のアニメーション処理X
	float BreakMoveY;//2が壊れた後のアニメーション処理Y
	float BreakMoveYgravity; //2が壊れた後のアニメーション処理Y重力
	int StartTime = 0;		//撃ち出した最初の時間
	float Speed = 0;		//速度
	bool Shooted = false;


}cley;

extern cley Cley1;
extern cley Cley2;

//弾の構造体
typedef struct _bullet {


	bool IsMoving = false;  // 変数の初期化
	int StartTime = 0;      // 変数の初期化
	VECTOR Position;	//弾の位置
	VECTOR Angle;			//角度
	int Color; //色　　1 => 青色　, 2 => 赤色



}bullet;

extern bullet Bullet1;//弾１
extern bullet Bullet2;//弾２




//アプリケーション終了時に、メモリーに格納された音と画像のデータを解放する
extern void Releace();


//グラフィックを読み込む

extern void TitleTextureLoad(void); //タイトル
extern void HomeTextureLoad(void);	//ホーム
extern void ResultTextureLoad(void);//リザルト
extern void ShopTextureLoad(void);//ショップ


//入力したx1,y1,x2,y2の２点間の直線を作りだす。
extern int SetLineToMouse(float x1, float y1, float x2, float y2);

//4つの点の座標からUiの範囲を創り出す。
extern bool SetUI(float L_up_X, float L_up_Y, float R_up_x, float R_up_y, float L_down_x, float L_down_y, float R_down_x, float R_down_y);

extern bool CheckCollision(VECTOR spherePos, float sphereRadius, VECTOR boxPos, VECTOR boxSize);





//シーン関連の関数のプロトタイプ宣言
extern void TitleInit(void); //タイトル初期化
extern void TitleCtrl(void); //タイトル管理
extern void TitleProc(void); //タイトル処理
extern void TitleDraw(void); //タイトル描画

extern void MainInit(void); //メイン初期化
extern void MainCtrl(void); //メイン管理
extern void MainProc(void); //メイン処理
extern void MainDraw(void); //メイン描画

//防衛画面
extern void DefInit(void); //防衛初期化
extern void DefCtrl(void);	//防衛管理
extern void DefProc(void);	//防衛処理
extern void DefDraw(void);	//防衛描画

//攻撃画面
extern void AtackInit(void);//攻撃初期化
extern void AtackCtrl(void);//攻撃管理
extern void AtackProc(void);//攻撃処理
extern void AtackDraw(void);//攻撃描画

//リザルト画面
extern void ResultInit(void); //リザルト初期化
extern void ResultCtrl(void); //リザルト管理
extern void ResultProc(void); //リザルト処理
extern void ResultDraw(void); //リザルト描画


//ショップ画面
extern void ShopInit(void); //リザルト初期化
extern void ShopCtrl(void); //リザルト管理
extern void ShopProc(void); //リザルト処理
extern void ShopDraw(void); //リザルト描画


//solo画面
extern void SoloInit(void); //ソロ初期化
extern void SoloCtrl(void); //ソロ管理
extern void SoloProc(void); //ソロ処理
extern void SoloDraw(void); //ソロ描画


//オプション画面
extern void OptionInit(void); //リザルト初期化
extern void OptionCtrl(void); //リザルト管理
extern void OptionProc(void); //リザルト処理
extern void OptionDraw(void); //リザルト描画



//オプション画面
extern void TutorialInit(void); //リザルト初期化
extern void TutorialCtrl(void); //リザルト管理
extern void TutorialProc(void); //リザルト処理
extern void TutorialDraw(void); //リザルト描画
