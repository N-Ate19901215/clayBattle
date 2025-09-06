#include "Game.h"
#include "Keyboad.h"
#include "Mouse.h"
#include "math.h"
#include "LoadSorce.h"
#include "Fps.h"

//ここから先、人生行路難し




//現在のシーン
enum GameScene NowGameScene;

//移行後のゲームシーン
enum GameScene ChangeGameScene;



//シーン識別名
char GameSceneName[GameSceneCount][GameSceneNameMax]
{
	"タイトル",
	"メイン",
	"攻撃",
	"防衛",
	"リザルト"
};

//シーン切り替わり後の経過フレーム数を管理
int GameSceneFrameCount[GameSceneCount];

bool MainBGM = false; //Main画面でBGMを１回だけ流したいので、mainに入った瞬間trueにし、防衛でfalseにする。


//--------------------------射撃-------------------------------

//珠関連
VERTEX3D Bullet1Vertex[6];
VERTEX3D Bullet2Vertex[6];
MATRIX Bullet1TransformMatrix;//トランスフォーム
MATRIX Bullet2TransformMatrix;//トランスフォーム
//VECTOR Angle;			//角度

float BulletSpeed;		//速度


bullet Bullet1;
bullet Bullet2;

/*
bool IsMoving = false;  // 発射済みか否か
int StartTime = 0;      // 飛ばし始めた時間
VECTOR Position;		//弾の位置

*/


//[座標系の変換用]

VECTOR camPos;	//カメラの位置
VECTOR camDir;	//カメラの向き
VECTOR camTop; //カメラの頭の向き
VECTOR Ps;//スクリーン座標　(x, y, near)
VECTOR PsToCam;//変換後の座標系

VECTOR GunDir1;//銃の角度(　「スクリーン座標　- カメラ座標」による方向ベクトル)
VECTOR GunDir2;//銃の角度(　「スクリーン座標　- カメラ座標」による方向ベクトル)

int mouseX = 0;//マウスX座標取得
int mouseY = 0;//マウスY座標取得

float MbMouseX  = 0;//スクリーン上(Mobile座標)のマウス座標　x
float MbMouseY  = 0;//y




//バトルシーンのアニメーション画像の読み込みを、１回に制限するための変数。
//(初期値はfalse。最初に防衛に飛んでロードしたタイミングでLoadMovieはtrueになり、その後はリザルトに飛んだ時にfalseになる)
bool LoadMovie = false; 


float AtackScore;		//攻撃のスコア
float DefenceScore;	//防衛のスコア


hasya hasyaL;//発射台L(構造体)
hasya hasyaR;//発射台R(構造体)

bool hasyaLR = true;
int fontSize = 0;

int animeF, animeN;	//攻撃、防衛のアニメーション再生時に使用する変数。値の上昇に伴ってパラパラ漫画のように再生する。

int mainAnime;
float UIanime[] = { 1,1,1,1,1,1,1,1 };
int shopAnime = 0;
float speedCtrl;
float niconico1, niconico2;
int shopGOAnime, shopGOAnimeCtrl;
bool modeSelect;






//---------------- -----------------------------
float kumoMove[2] = { 0,0 };

//ランダム背景変数
int BackgroundImages[4];
int SelectedBackgroundIndex;





int MovieGraphHandle;		//

int cR;		//

int GunStatus;//銃の種類

//リザルト処理--------------------------
//int AtScore = 0;
//int DfScore = 0;

int debugGraph;		//

int  ResultState = 0;		//リザルトシーンの状態　[0の時 =>   ]  
							//						[1の時 =>  ]


//音の大きさ





int breakAnime1;
int breakAnime2;
int battleRound;

int SoundVolume = 50;
int oldMouse = 0;
int newMouse = 0;
int VolumeBall = 0;
int OptionMousePos = 0;

float titleAnimeLogo = -1000;
float titleAnimeChara[2];
float titleAnimeGravity = 0;
float titleTime;
float titleLogoTime;
bool shopYes;
bool optionYes;
int animeN2 = 0;


int TutorialState = 0;
int TimeCount = 0;

//
// 
// 
//クレイ関連のグローバル変数

cley Cley1;
cley Cley2;


/*

VECTOR CleyPosition1;//位置
VECTOR CleyVelocity1;//移動の速さ
VECTOR CleyAngle1;	//角度
VECTOR CleyDir1;	//クレイの方向
VECTOR CleyBreakPosition1;//1壊れた位置
int CleyBreak1;//1のクレーが壊れたか否か
float CleyBreakMove1X;//1が壊れた後のアニメーション処理X
float CleyBreakMove1Y;//1が壊れた後のアニメーション処理Y
float CleyBreakMove1Ygravity; //1が壊れた後のアニメーション処理Y重力
int CleyColor1;		//色 (1 => 青色、　2 => 赤色　)
bool IsCleyMoving1 = false;	//動いている状態か否か
int CleyStartTime1 = 0;		//撃ち出した最初の時間
*/

/*
VECTOR CleyPosition2;//位置
VECTOR CleyVelocity2;//移動の速さ
VECTOR CleyAngle2;	//角度
VECTOR CleyBreakPosition2;//2壊れた位置
VECTOR CleyDir2;	//クレイの方向
int CleyColor2;	 	//色 (1 => 青色、　2 => 赤色　)
bool IsCleyMoving2  = false;	//動いている状態か否か
int CleyBreak2; //2のクレーが壊れたか否か

float CleyBreakMove2X;//2が壊れた後のアニメーション処理X
float CleyBreakMove2 Y;//2が壊れた後のアニメーション処理Y
float CleyBreakMove2Ygravity; //2が壊れた後のアニメーション処理Y重力
int CleyStartTime2 = 0;		//撃ち出した最初の時間
*/



//float CleySpeed = 20.0f;		//速度
float AirResistance = 0.995f; // 空気抵抗の影響を軽減
float Gravity = 9.8f;        // 重力加速度
int CollisionDisplayStartTime = -1; // 衝突メッセージの表示開始時間

// 縮小する新しいサイズを指定
int newWidth = 250;  // 新しい幅
int newHeight = 200; // 新しい高さ
//　=>　説明求ム。ナニコレ

bool solo;//ソロモードか否か


//メモリーを解放
void Releace()
{
	InitGraph();
	InitSoundMem();

	return;
}



//2点間の線分を作り、取得したマウスの座標との距離を図る。
int SetLineToMouse(float x1, float y1, float x2, float y2)
{
	int mouseX, mouseY;
	GetMousePoint(&mouseX, &mouseY);

	float kari = (y1 - y2) * (x1 - static_cast<float>(mouseX)) + (x1 - x2) * (static_cast<float>(mouseY) - y1);
	
	return static_cast<int>(kari);
}


bool SetUI(float L_up_x, float L_up_y, float R_up_x, float R_up_y, float L_down_x, float L_down_y, float R_down_x, float R_down_y)
{
	//上の辺
	SetLineToMouse(L_up_x, L_up_y, R_up_x, R_up_y);
	//下の辺
	SetLineToMouse(L_down_x, L_down_y, R_down_x, R_down_y);

	//左の辺
	SetLineToMouse(L_up_x, L_up_y, L_down_x, L_down_y);

	//右の辺
	SetLineToMouse(R_up_x, R_up_y, L_down_x, L_down_y);

	if (SetLineToMouse(L_up_x, L_up_y, R_up_x, R_up_y) < 0)
	{
		if (SetLineToMouse(L_down_x, L_down_y, R_down_x, R_down_y) > 0)
		{
			if (SetLineToMouse(L_up_x, L_up_y, L_down_x, L_down_y) > 0)
			{
				if (SetLineToMouse(R_up_x, R_up_y, R_down_x, R_down_y) < 0)
				{
					return true;
				}
			}
		}
	}

	return false;
}





//タイトル初期化
void TitleInit(void)
{
	if (DebugMode == true)
	{
		DrawFormatString(width - 200, 0, GetColor(255, 255, 255), "%s%s", GameSceneName[ChangeGameScene], "初期化");




	}


	//------------------- -----------------------
	SelectedBackgroundIndex = GetRand(3);

	StopSoundMem(SoundData[2]);
	StopSoundMem(SoundData[3]);

			//メモリに格納されているアニメーション以外のデータを解放
			for (int i = 0; i < 201; i++) { DeleteGraph(GraphData[i]); }


			TitleTextureLoad();


			//シーン切り替え後の経過フレーム数を初期化
			GameSceneFrameCount[ChangeGameScene] = 0;

			MainBGM = false;

			titleAnimeLogo = -10000;
			titleAnimeChara[0] = -900;
			titleAnimeChara[1] = 900;
			titleAnimeGravity = 1;
			titleTime = 0;
			titleLogoTime = 0;
			kumoMove[0] = -1770;
			kumoMove[1] = 0;

	return;
}



//タイトル管理
void TitleCtrl(void)
{

	TitleProc();
	TitleDraw();
	return;
}



//タイトル処理(キー入力など)
void TitleProc(void)
{

	

	GameSceneFrameCount[NowGameScene]++;

	if (GameSceneFrameCount[NowGameScene] >= 70)
	{
		if (CheckHitKeyAll() != 0)
		{
			//シーン切り替え
			ChangeGameScene = MainScene;

			//GameSceneFrameCount[NowGameScene]++;

			//すぐに切り替える
			return;

		}

		GameSceneFrameCount[NowGameScene] = 70;

	}


	titleTime ++ ;
	titleLogoTime++;
	titleAnimeGravity = 10;

	if (titleTime >= 50 && titleTime <= 62) {
		titleAnimeLogo += 80;
	}
	

	kumoMove[1] += 1;
	kumoMove[0] += 1;

	if (kumoMove[0] > -620 && kumoMove[0] < -610) kumoMove[1] = -1920;
	if (kumoMove[1] > -200 && kumoMove[1] < -190) kumoMove[0] = -1770;


	titleAnimeLogo =  -1000 + ( titleAnimeGravity * titleTime * titleTime);
	
	if (titleAnimeLogo > 0)
	{
		titleAnimeLogo = 0;
	}
	

	if (titleTime >= 70) {

		titleAnimeChara[0] += 20;
		titleAnimeChara[1] -= 20;

		if (titleAnimeChara[0] >= 0) titleAnimeChara[0] = 0;
		if (titleAnimeChara[1] <= 0) titleAnimeChara[1] = 0;
		return;
	}
}



//タイトル描画(文字やイラスト)
void TitleDraw(void)
{

	DrawGraph(0, 0, GraphData[5], true);
	DrawGraph(kumoMove[1] * 1.1, kumoMove[1], GraphData[6], true);
	DrawGraph(kumoMove[0] * 1.1, kumoMove[0], GraphData[6], true);
	DrawGraph(0, 0, GraphData[SelectedBackgroundIndex], true);
	
	DrawGraph(titleAnimeChara[1] - 10, 0, GraphData[7], true);
	DrawGraph(titleAnimeChara[0], 0, GraphData[8], true);

	DrawGraph(0, titleAnimeLogo, GraphData[4], true);


	
	DrawFormatString(120, 0, GetColor(255, 255, 255), "ver0.75");

	if (DebugMode == true)
	{
		DrawFormatString(width - 200, 0, GetColor(255, 255, 255), "%s%s", GameSceneName[NowGameScene], "描画中");

		DrawFormatString(700, 0, GetColor(255, 255, 255), "%d", GameSceneFrameCount[NowGameScene]);

		DrawFormatString(700, 0, GetColor(255, 255, 255), "%d", titleAnimeLogo);
	}

	return;
}


//メイン初期化
void MainInit(void)
{
	if (DebugMode == true)
	{
		DrawFormatString(width - 200, 0, GetColor(255, 255, 255), "%s%s", GameSceneName[ChangeGameScene], "初期化");

	}
	//----------------------------------------------------------------
	//DX_TEST_0704以降のサンプルに移行するべきデータ
	//----------------------------------------------------------------

		//すでに読み込んだサウンドを停止
	StopSoundMem(SoundData[4]);
	StopSoundMem(SoundData[10]);
	//StopSoundMem(SoundData[3]);

	//----------------------------------------------------------------
	//DX_TEST_0704以降のサンプルに移行するべきデータ（ここまで）
	//----------------------------------------------------------------

	AtackScore = 0;
	DefenceScore = 0;

	mainAnime = 0;
	UIanime[1] = -600;
	UIanime[5] = -500;
	UIanime[6] = -500;
	UIanime[2] = 800;
	UIanime[3] = 800;
	speedCtrl = 1.2;
	shopAnime = 1;
	niconico1 = 0;
	niconico2 = 1030;
	shopGOAnime, shopGOAnimeCtrl = 0;
	SetFontSize(20);
	shopGOAnime = 0;
	modeSelect = false;
	solo = false;
	battleRound = 1;

	for (int i = 0; i < 201; i++) { DeleteGraph(GraphData[i]); }
	HomeTextureLoad();

	//----------------------------------------------------------------
	//DX_TEST_0704以降のサンプルに移行するべきデータ
	//----------------------------------------------------------------


			//音量設定
	ChangeVolumeSoundMem(255 * 65 / 100, SoundData[2]);

	ChangeVolumeSoundMem(255 * 40 / 100, SoundData[3]);

	//ボイスを再生  voice => [2],  BGM => [3]
	PlaySoundMem(SoundData[2], DX_PLAYTYPE_BACK, true);

	SetLoopPosSoundMem(0, SoundData[3]);
	//BGM再生
	if (MainBGM != true)
	{
		PlaySoundMem(SoundData[3], DX_PLAYTYPE_BACK, true);

		MainBGM = true;
	}
		/*
	//すでに読み込んだサウンドを停止
	StopSoundMem(SoundData[0]);

	//----------------------------------------------------------------
	//DX_TEST_0704以降のサンプルに移行するべきデータ（ここまで）
	//----------------------------------------------------------------

			AtackScore = 0;
			DefenceScore = 0;

			//メモリに格納されているアニメーション以外のデータを解放
			for (int i = 0; i < 201; i++) { DeleteGraph(GraphData[i]); }

			HomeTextureLoad();

	//----------------------------------------------------------------
	//DX_TEST_0704以降のサンプルに移行するべきデータ
	//----------------------------------------------------------------
	
			//サウンドの占有されてるメモリを解放
			InitSoundMem();
			//ホーム用の画像をメモリに格納
			HomeSoundLoad();

			//音量設定
			ChangeVolumeSoundMem(255 * 65 / 100, SoundData[0]);

			//ボイスを再生
			PlaySoundMem(SoundData[0], DX_PLAYTYPE_BACK, true);

	//----------------------------------------------------------------
	//DX_TEST_0704以降のサンプルに移行するべきデータ
	//----------------------------------------------------------------
	*/
			//シーン切り替え後の経過フレーム数を初期化
			GameSceneFrameCount[ChangeGameScene] = 0;


	return;
}



//メイン管理
void MainCtrl(void)
{
	MainProc();
	MainDraw();



	return;
}



//メイン処理
void MainProc(void)
{
	mainAnime++;
	niconico1 -= 2;
	niconico2 -= 2;
	if (niconico1 <= -2000) niconico1 = 500;
	if (niconico2 <= -1530) niconico2 = 1000;

	if (mainAnime > 45 && mainAnime <= 100) UIanime[1] += 100;
	if (mainAnime > 55 && mainAnime <= 100) UIanime[5] += 100;
	if (mainAnime > 65 && mainAnime <= 100) UIanime[6] += 100;

	if (mainAnime > 35 && mainAnime <= 100)	UIanime[2] -= 70;

	if (mainAnime > 15 && mainAnime <= 100) UIanime[3] -= 70;

	if (UIanime[1] > 0 && mainAnime <= 100) UIanime[1] = 0;
	if (UIanime[2] < 0 && mainAnime <= 100) UIanime[2] = 0;
	if (UIanime[3] < 0 && mainAnime <= 100) UIanime[3] = 0;
	if (UIanime[5] > 0 && mainAnime <= 100) UIanime[5] = 0;
	if (UIanime[6] > 0 && mainAnime <= 100) UIanime[6] = 0;

	if (shopGOAnime == 1) {
		shopGOAnimeCtrl++;
		if (shopGOAnimeCtrl >= 1) {
			UIanime[1] -= 100;
			UIanime[5] -= 100;
			UIanime[6] -= 100;
			UIanime[2] += 70;
			UIanime[3] += 70;
		}
		if (shopGOAnimeCtrl >= 30 && shopYes == true)
			ChangeGameScene = ShopScene;
		if (shopGOAnimeCtrl >= 30 && optionYes == true)
			ChangeGameScene = OptionScene;
	}



	switch (shopAnime) {
	case 1:
	{
		UIanime[4] += 0.2;
		if (UIanime[4] > 20)
			shopAnime = 2;
		break;
	}
	case 2: {
		UIanime[4] -= 0.2;
		if (UIanime[4] < -20)
			shopAnime = 1;
		break;
	}
	}










	if (mainAnime > 100) {

		if (modeSelect == true)
		{
			if (SetUI(265, 135, 905, 135, 265, 852, 905, 852) && MousePush(MOUSE_INPUT_LEFT))
			{
				solo = false;
				ChangeGameScene = DefScene;//防衛シーンに移行する
			}

			if (SetUI(1001, 135, 1646, 135, 1001, 852, 1646, 852) && MousePush(MOUSE_INPUT_LEFT))
			{
				solo = true;
				ChangeGameScene = SoloScene;//ソロシーン移行後攻撃シーンに移行する
			}

			
		}
		//カーソルがタイトルUIの中に合って、左クリックが押された瞬間にシーンを変える。モードセレクトが開かれてないときにね
		if (modeSelect == false)
		{
			if (SetUI(29, 874, 494, 874, 29, 960, 457, 960) == true)
			{
				if (MousePush(MOUSE_INPUT_LEFT) == true)
				{
					MainBGM = false;
					ChangeGameScene = TitleScene;

					//すぐに切り替える
					return;

				}
			}

			if (SetUI(22, 979, 457, 979, 22, 1059, 443, 1059) == true)
			{
				if (MousePush(MOUSE_INPUT_LEFT) == true)
				{

					Releace();
					DxLib_End();

					return;
					//DrawFormatString(700, 0, GetColor(255, 255, 255), "ゲーム終了選択");


				}
			}

			if (SetUI(1370, 536, 1885, 591, 1360, 807, 1885, 881) == true)
			{
				if (MousePush(MOUSE_INPUT_LEFT))
				{
					ChangeGameScene = TutorialScene;
					return;
				}
			}


			/*

			if (SetUI(29, 874, 494, 874, 29, 960, 457, 960) == true)
			{
				if (MousePush(MOUSE_INPUT_LEFT) == true)
				{
					ChangeGameScene = TitleScene;

					//すぐに切り替える
					return;

				}
			}
			*/

			cR = sqrt((mouseX - 964) * (mouseX - 964) + (mouseY - 1050) * (mouseY - 1050));

			if (cR < 447)
			{
				if (MousePush(MOUSE_INPUT_LEFT) == true) 
				{
					modeSelect = true;//モードセレクトの画面に飛ぶ
					PlaySoundMem(SoundData[1], DX_PLAYTYPE_BACK, true);//クリックした際UIのサウンドを再生
				}
				MainBGM = false;
			}



			if (SetUI(1192, 90, 1841, 165, 1192, 464, 1841, 537) && MousePush(MOUSE_INPUT_LEFT))
			{
				shopYes = true;//shopを開いています

				shopGOAnime = 1;

				//クリックした際UIのサウンドを再生
				PlaySoundMem(SoundData[1], DX_PLAYTYPE_BACK, true);

				return;
			}

			if (SetUI(27, 742, 587, 742, 27, 869, 490, 869) && MousePush(MOUSE_INPUT_LEFT))
			{
				//クリックした際UIのサウンドを再生
				PlaySoundMem(SoundData[1], DX_PLAYTYPE_BACK, true);

				optionYes = true;
				shopGOAnime = 1;

				return;
			}
		}


		if (modeSelect == true) {
			if (SetUI(223, 865, 480, 865, 229, 992, 480, 992) && MousePush(MOUSE_INPUT_LEFT))
			{
				modeSelect = false;//モード選択から戻る

			}
		}

		
	}
	GetMousePoint(&mouseX, &mouseY);

	return;
}



//メイン描画
void MainDraw(void)
{

	DrawGraph(0, 0, GraphData[15], true);

	DrawFormatString(niconico1 + 700, 400, GetColor(0, 0, 0), "wktk");
	DrawFormatString(niconico1 + 1000, 450, GetColor(0, 0, 0), "たのしみ");
	DrawFormatString(niconico1 + 1200, 500, GetColor(0, 0, 0), "今北産業");
	DrawFormatString(niconico1 + 1210, 320, GetColor(0, 0, 0), "令和の神ゲー！");
	//DrawFormatString(niconico1 + 1300, 210, GetColor(0, 0, 0), "クソゲー過ぎる");
	DrawFormatString(niconico1 + 1300, 210, GetColor(0, 0, 0), "神ゲーktkr");
	DrawFormatString(niconico1 + 1280, 450, GetColor(0, 0, 0), "UI好き");
	//DrawFormatString(niconico1 + 1420, 310, GetColor(0, 0, 0), "オワコンクレーバトル");
	DrawFormatString(niconico1 + 1420, 310, GetColor(0, 0, 0), "学生作品ってマ？");
	//DrawFormatString(niconico1 + 1700, 400, GetColor(0, 0, 0), "金返せ");
	DrawFormatString(niconico1 + 1700, 400, GetColor(0, 0, 0), "おもろいよなこれ");
	//DrawFormatString(niconico1 + 1100, 450, GetColor(0, 0, 0), "詐欺広告");
	DrawFormatString(niconico1 + 1100, 450, GetColor(0, 0, 0), "今日の大会楽しみ");
	DrawFormatString(niconico1 + 1610, 450, GetColor(0, 0, 0), "難易度高い;;");
	DrawFormatString(niconico1 + 1660, 480, GetColor(0, 0, 0), "盛り上がりえぐい");
	DrawFormatString(niconico1 + 1830, 290, GetColor(0, 0, 0), "最高");
	DrawFormatString(niconico1 + 1980, 450, GetColor(0, 0, 0), "人生の縮図");
	DrawFormatString(niconico1 + 1800, 310, GetColor(0, 0, 0), "結構楽しい");

	DrawFormatString(niconico2 + 700, 350, GetColor(0, 0, 0), "今一番アツいわ");
	//DrawFormatString(niconico2 + 1000, 290, GetColor(0, 0, 0), "チェソンーマンのパクリやん");
	DrawFormatString(niconico2 + 1000, 290, GetColor(0, 0, 0), "友達ガチでうまかった");
	//DrawFormatString(niconico2 + 1200, 500, GetColor(0, 0, 0), "ふざけんな");
	DrawFormatString(niconico2 + 1200, 500, GetColor(0, 0, 0), "誰か対戦しよー！");
	DrawFormatString(niconico2 + 1210, 370, GetColor(0, 0, 0), "これDXライブラリなんか");
	//DrawFormatString(niconico2 + 1300, 380, GetColor(0, 0, 0), "過疎ゲー");
	DrawFormatString(niconico2 + 1300, 380, GetColor(0, 0, 0), "これIPUT製ゲームか");
	//DrawFormatString(niconico2 + 1280, 400, GetColor(0, 0, 0), "しかのこのこのこどしたんたん");
	DrawFormatString(niconico2 + 1280, 400, GetColor(0, 0, 0), "新作まだ？");
	DrawFormatString(niconico2 + 1420, 350, GetColor(0, 0, 0), "武器のスキンほしい");
	DrawFormatString(niconico2 + 1700, 320, GetColor(0, 0, 0), "時間を忘れてやってた");
	DrawFormatString(niconico2 + 1100, 300, GetColor(0, 0, 0), "おもろっ！");
	DrawFormatString(niconico2 + 1610, 420, GetColor(0, 0, 0), "リアルのクレー射撃やりたくなるわ");
	DrawFormatString(niconico2 + 1740, 410, GetColor(0, 0, 0), "重い");
	DrawFormatString(niconico2 + 1830, 320, GetColor(0, 0, 0), "コンピューターつええ...");
	DrawFormatString(niconico2 + 1980, 390, GetColor(0, 0, 0), "ミニガン実装はよ");
	DrawFormatString(niconico2 + 1800, 340, GetColor(0, 0, 0), "世界観好き");



	//UI表示
	DrawGraph(0, 0, GraphData[0], true);
	DrawGraph(UIanime[6], 0, GraphData[1], true);
	DrawGraph(UIanime[1], 0, GraphData[2], true);

		
	DrawGraph(UIanime[2], UIanime[4], GraphData[3], true);
	DrawGraph(UIanime[5], 0, GraphData[4], true);
	DrawGraph(UIanime[2], UIanime[4], GraphData[5], true);
	DrawGraph(0, 0, GraphData[14], true);
	DrawGraph(0, UIanime[3], GraphData[6], true);//バトル


	
	if (modeSelect == false) {
		if (cR < 447) 	DrawGraph(0, UIanime[3], GraphData[7], true);
		if (SetUI(1192, 90, 1841, 165, 1192, 464, 1841, 537) == true)	DrawGraph(UIanime[2], UIanime[4], GraphData[11], true);//ショップ選択時
		if (SetUI(1370, 536, 1885, 591, 1360, 807, 1885, 881) == true)	DrawGraph(UIanime[2], UIanime[4], GraphData[13], true);//チュートリアル選択時
		if (SetUI(27, 742, 587, 742, 27, 869, 490, 869) == true)		DrawGraph(UIanime[1], 0, GraphData[10], true);//オプション選択時
		if (SetUI(29, 874, 494, 874, 29, 960, 457, 960) == true)		DrawGraph(UIanime[5], 0, GraphData[12], true);//タイトル選択時
		if (SetUI(22, 979, 457, 979, 22, 1059, 443, 1059) == true)		DrawGraph(UIanime[6], 0, GraphData[9], true); //ゲーム終了選択時
	}







	//----------------------------- -------------------------------------------------------------
	
	if (modeSelect == true) {

		SetDrawBlendMode(DX_BLENDMODE_MULA, 150);
		DrawGraph(0, 0, GraphData[21], true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		DrawGraph(0, 0, GraphData[16], true);
	//	SetDrawBlendMode(DX_BLENDMODE_MULA, 255);
		DrawGraph(0, 0, GraphData[17], true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		DrawGraph(0, 0, GraphData[18], true);
		DrawExtendGraph(0 - 700, 0 + 350, 1920 * 2 / 3 - 700, 1080 * 2 / 3 + 350, GraphData[23], true);
		if(SetUI(223, 865, 480, 865, 229, 992, 480, 992))
		DrawExtendGraph(0 - 700, 0 + 350, 1920 * 2 / 3 - 700, 1080 * 2 / 3 + 350, GraphData[22], true);


		if (SetUI(265, 135, 905, 135, 265, 852, 905, 852))				DrawGraph(0, 0, GraphData[19], true); //ダブル選択時
		if (SetUI(1001, 135, 1646, 135, 1001, 852, 1646, 852))				DrawGraph(0, 0, GraphData[20], true); //ソロ選択時

	}






	//デバッグ用表示
	if (DebugMode == true)
	{
		DrawFormatString(width - 200, 0, GetColor(255, 255, 255), "%s%s", GameSceneName[NowGameScene], "描画中");



		DrawFormatString(100, 100, GetColor(255, 255, 255), "マウスX:%d", mouseX);
		DrawFormatString(300, 100, GetColor(255, 255, 255), "Y:%d", mouseY);
		//if(MainBGM != true)DrawFormatString(200, 400, GetColor(255, 255, 255), "BGM");


		
		if (SetUI(1192, 90, 1841, 165, 1192, 464, 1841, 537) == true)	DrawFormatString(700, 0, GetColor(255, 255, 255), "ショップ選択");

		if (SetUI(1370, 536, 1885, 591, 1360, 807, 1885, 881) == true) DrawFormatString(700, 0, GetColor(255, 255, 255), "チュートリアル選択");
		
		if (SetUI(27, 742, 587, 742, 27, 869, 490, 869) == true) DrawFormatString(700, 0, GetColor(255, 255, 255), "オプション選択");
		
		if (SetUI(29, 874, 494, 874, 29, 960, 457, 960) == true) DrawFormatString(700, 0, GetColor(255, 255, 255), "タイトルUI選択");

		if (SetUI(22, 979, 457, 979, 22, 1059, 443, 1059) == true) DrawFormatString(700, 0, GetColor(255, 255, 255), "ゲーム終了選択");


	}

	
	return;
}





//ショップ初期化
void ShopInit(void)
{
//----------------------------------------------------------------
//DX_TEST_0704以降のサンプルに移行するべきデータ
//----------------------------------------------------------------
	//すでに読み込んだサウンドを停止
	StopSoundMem(SoundData[2]);

//----------------------------------------------------------------
//DX_TEST_0704以降のサンプルに移行するべきデータ（ここまで）
//----------------------------------------------------------------

			//メモリに格納されているアニメーション以外のデータを解放
	for (int i = 0; i < 201; i++) { DeleteGraph(GraphData[i]); }

	ShopTextureLoad();

//----------------------------------------------------------------
//DX_TEST_0704以降のサンプルに移行するべきデータ
//----------------------------------------------------------------


	//音量設定
	ChangeVolumeSoundMem(255 * 65 / 100, SoundData[4]);

	//ボイスを再生（ショップ用めたんボイス）
	PlaySoundMem(SoundData[4], DX_PLAYTYPE_BACK, true);

//----------------------------------------------------------------
//DX_TEST_0704以降のサンプルに移行するべきデータ（ここまで）
//----------------------------------------------------------------

	GameSceneFrameCount[ChangeGameScene] = 0;
	GunStatus = 0;//銃種類初期化（ショットガン）

	return;
}



//ショップ管理
void ShopCtrl(void)
{

	ShopProc();
	ShopDraw();

	return;
}



//ショップ処理
void ShopProc(void)
{
	//マウス座標取得
	GetMousePoint(&mouseX, &mouseY);

	if (SetUI(220, 388, 1012, 388, 245, 488, 1011, 488) == true || SetUI(212, 373, 341, 338, 216, 390, 357, 390) == true)
	{

		GunStatus = 0;

	}

		//準備完了からホーム画面遷移
		if (SetUI(1190,687,1838,687,1305,1026,1838,1026) == true && MousePush(MOUSE_INPUT_LEFT) == true)
		{
			ChangeGameScene = MainScene;

			return;
		}

		niconico1 -= 2;
		niconico2 -= 2;
		if (niconico1 <= -2000) niconico1 = 500;
		if (niconico2 <= -1530) niconico2 = 1000;

	return;
}



//ショップ画面描画
void ShopDraw(void)
{

	//----------------------------------画面画像表示-------------------------------------


	DrawGraph(0, 0, GraphData[9], true);

	DrawFormatString(niconico1 + 700, 400, GetColor(0, 0, 0), "wktk");
	DrawFormatString(niconico1 + 1000, 450, GetColor(0, 0, 0), "たのしみ");
	DrawFormatString(niconico1 + 1200, 500, GetColor(0, 0, 0), "今北産業");
	DrawFormatString(niconico1 + 1210, 320, GetColor(0, 0, 0), "令和の神ゲー！");
	//DrawFormatString(niconico1 + 1300, 210, GetColor(0, 0, 0), "クソゲー過ぎる");
	DrawFormatString(niconico1 + 1300, 210, GetColor(0, 0, 0), "神ゲーktkr");
	DrawFormatString(niconico1 + 1280, 450, GetColor(0, 0, 0), "UI好き");
	//DrawFormatString(niconico1 + 1420, 310, GetColor(0, 0, 0), "オワコンクレーバトル");
	DrawFormatString(niconico1 + 1420, 310, GetColor(0, 0, 0), "学生作品ってマ？");
	//DrawFormatString(niconico1 + 1700, 400, GetColor(0, 0, 0), "金返せ");
	DrawFormatString(niconico1 + 1700, 400, GetColor(0, 0, 0), "おもろいよなこれ");
	//DrawFormatString(niconico1 + 1100, 450, GetColor(0, 0, 0), "詐欺広告");
	DrawFormatString(niconico1 + 1100, 450, GetColor(0, 0, 0), "今日の大会楽しみ");
	DrawFormatString(niconico1 + 1610, 450, GetColor(0, 0, 0), "難易度高い;;");
	DrawFormatString(niconico1 + 1660, 480, GetColor(0, 0, 0), "盛り上がりえぐい");
	DrawFormatString(niconico1 + 1830, 290, GetColor(0, 0, 0), "最高");
	DrawFormatString(niconico1 + 1980, 450, GetColor(0, 0, 0), "人生の縮図");
	DrawFormatString(niconico1 + 1800, 310, GetColor(0, 0, 0), "結構楽しい");

	DrawFormatString(niconico2 + 700, 350, GetColor(0, 0, 0), "今一番アツいわ");
	//DrawFormatString(niconico2 + 1000, 290, GetColor(0, 0, 0), "チェソンーマンのパクリやん");
	DrawFormatString(niconico2 + 1000, 290, GetColor(0, 0, 0), "友達ガチでうまかった");
	//DrawFormatString(niconico2 + 1200, 500, GetColor(0, 0, 0), "ふざけんな");
	DrawFormatString(niconico2 + 1200, 500, GetColor(0, 0, 0), "誰か対戦しよー！");
	DrawFormatString(niconico2 + 1210, 370, GetColor(0, 0, 0), "これDXライブラリなんか");
	//DrawFormatString(niconico2 + 1300, 380, GetColor(0, 0, 0), "過疎ゲー");
	DrawFormatString(niconico2 + 1300, 380, GetColor(0, 0, 0), "これIPUT製ゲームか");
	//DrawFormatString(niconico2 + 1280, 400, GetColor(0, 0, 0), "しかのこのこのこどしたんたん");
	DrawFormatString(niconico2 + 1280, 400, GetColor(0, 0, 0), "新作まだ？");
	DrawFormatString(niconico2 + 1420, 350, GetColor(0, 0, 0), "武器のスキンほしい");
	DrawFormatString(niconico2 + 1700, 320, GetColor(0, 0, 0), "時間を忘れてやってた");
	DrawFormatString(niconico2 + 1100, 300, GetColor(0, 0, 0), "おもろっ！");
	DrawFormatString(niconico2 + 1610, 420, GetColor(0, 0, 0), "リアルのクレー射撃やりたくなるわ");
	DrawFormatString(niconico2 + 1740, 410, GetColor(0, 0, 0), "重い");
	DrawFormatString(niconico2 + 1830, 320, GetColor(0, 0, 0), "コンピューターつええ...");
	DrawFormatString(niconico2 + 1980, 390, GetColor(0, 0, 0), "ミニガン実装はよ");
	DrawFormatString(niconico2 + 1800, 340, GetColor(0, 0, 0), "世界観好き");


	DrawGraph(0, 0, GraphData[0], true);
	DrawGraph(0, 0, GraphData[1], true);
	DrawGraph(0, 0, GraphData[2], true);
	DrawGraph(0, 0, GraphData[3], true);
	DrawGraph(0, 0, GraphData[4], true);
	DrawGraph(0, 0, GraphData[5], true);
	DrawGraph(0, 0, GraphData[6], true);
	DrawGraph(0, 0, GraphData[7], true);


	if (SetUI(1190, 687, 1838, 687, 1305, 1026, 1838, 1026) == true) DrawGraph(0, 0, GraphData[8], true);


	//デバック機能
	if (DebugMode == true)
	{
		if (SetUI(220, 388, 1012, 388, 245, 488, 1011, 488) == true || SetUI(212, 373, 341, 338, 216, 390, 357, 390) == true)	DrawFormatString(700, 0, GetColor(255, 255, 255), "ショットガン選択中");

		DrawFormatString(width - 200, 0, GetColor(255, 255, 255), "%s%s", GameSceneName[NowGameScene], "ショップ描画中");

		DrawFormatString(100, 100, GetColor(255, 255, 255), "マウスX:%d", mouseX);
		DrawFormatString(200, 100, GetColor(255, 255, 255), "マウスY:%d", mouseY);
	}
	return;
}



//オプション初期化
void OptionInit(void)
{

	for (int i = 0; i < 201; i++) { DeleteGraph(GraphData[i]); }
	OptionTextureLoad();


	GameSceneFrameCount[ChangeGameScene] = 0;

	return;
}

//オプション管理
void OptionCtrl(void)
{
	OptionProc();
	OptionDraw();

	return;
}

//オプション処理
void OptionProc(void)
{
	//マウス座標取得
	GetMousePoint(&mouseX, &mouseY);

	mouseX = oldMouse;


	OptionMousePos = newMouse - oldMouse;

	SoundVolume = OptionMousePos / 10;


	if (SetUI(1385, 769, 1773, 769, 1385, 967, 1773, 967) && MousePush(MOUSE_INPUT_LEFT)) {
		optionYes = false;
		ChangeGameScene = MainScene;
	}


	niconico1 -= 2;
	niconico2 -= 2;
	if (niconico1 <= -2000) niconico1 = 500;
	if (niconico2 <= -1530) niconico2 = 1000;
	return;
}

//オプション描画
void OptionDraw(void)
{


	DrawGraph(0, 0, GraphData[4], TRUE);//背景


	SetFontSize(20);

	DrawFormatString(niconico1 + 700, 400, GetColor(0, 0, 0), "wktk");
	DrawFormatString(niconico1 + 1000, 450, GetColor(0, 0, 0), "たのしみ");
	DrawFormatString(niconico1 + 1200, 500, GetColor(0, 0, 0), "今北産業");
	DrawFormatString(niconico1 + 1210, 320, GetColor(0, 0, 0), "令和の神ゲー！");
	//DrawFormatString(niconico1 + 1300, 210, GetColor(0, 0, 0), "クソゲー過ぎる");
	DrawFormatString(niconico1 + 1300, 210, GetColor(0, 0, 0), "神ゲーktkr");
	DrawFormatString(niconico1 + 1280, 450, GetColor(0, 0, 0), "UI好き");
	//DrawFormatString(niconico1 + 1420, 310, GetColor(0, 0, 0), "オワコンクレーバトル");
	DrawFormatString(niconico1 + 1420, 310, GetColor(0, 0, 0), "学生作品ってマ？");
	//DrawFormatString(niconico1 + 1700, 400, GetColor(0, 0, 0), "金返せ");
	DrawFormatString(niconico1 + 1700, 400, GetColor(0, 0, 0), "おもろいよなこれ");
	//DrawFormatString(niconico1 + 1100, 450, GetColor(0, 0, 0), "詐欺広告");
	DrawFormatString(niconico1 + 1100, 450, GetColor(0, 0, 0), "今日の大会楽しみ");
	DrawFormatString(niconico1 + 1610, 450, GetColor(0, 0, 0), "難易度高い;;");
	DrawFormatString(niconico1 + 1660, 480, GetColor(0, 0, 0), "盛り上がりえぐい");
	DrawFormatString(niconico1 + 1830, 290, GetColor(0, 0, 0), "最高");
	DrawFormatString(niconico1 + 1980, 450, GetColor(0, 0, 0), "人生の縮図");
	DrawFormatString(niconico1 + 1800, 310, GetColor(0, 0, 0), "結構楽しい");

	DrawFormatString(niconico2 + 700, 350, GetColor(0, 0, 0), "今一番アツいわ");
	//DrawFormatString(niconico2 + 1000, 290, GetColor(0, 0, 0), "チェソンーマンのパクリやん");
	DrawFormatString(niconico2 + 1000, 290, GetColor(0, 0, 0), "友達ガチでうまかった");
	//DrawFormatString(niconico2 + 1200, 500, GetColor(0, 0, 0), "ふざけんな");
	DrawFormatString(niconico2 + 1200, 500, GetColor(0, 0, 0), "誰か対戦しよー！");
	DrawFormatString(niconico2 + 1210, 370, GetColor(0, 0, 0), "これDXライブラリなんか");
	//DrawFormatString(niconico2 + 1300, 380, GetColor(0, 0, 0), "過疎ゲー");
	DrawFormatString(niconico2 + 1300, 380, GetColor(0, 0, 0), "これIPUT製ゲームか");
	//DrawFormatString(niconico2 + 1280, 400, GetColor(0, 0, 0), "しかのこのこのこどしたんたん");
	DrawFormatString(niconico2 + 1280, 400, GetColor(0, 0, 0), "新作まだ？");
	DrawFormatString(niconico2 + 1420, 350, GetColor(0, 0, 0), "武器のスキンほしい");
	DrawFormatString(niconico2 + 1700, 320, GetColor(0, 0, 0), "時間を忘れてやってた");
	DrawFormatString(niconico2 + 1100, 300, GetColor(0, 0, 0), "おもろっ！");
	DrawFormatString(niconico2 + 1610, 420, GetColor(0, 0, 0), "リアルのクレー射撃やりたくなるわ");
	DrawFormatString(niconico2 + 1740, 410, GetColor(0, 0, 0), "重い");
	DrawFormatString(niconico2 + 1830, 320, GetColor(0, 0, 0), "コンピューターつええ...");
	DrawFormatString(niconico2 + 1980, 390, GetColor(0, 0, 0), "ミニガン実装はよ");
	DrawFormatString(niconico2 + 1800, 340, GetColor(0, 0, 0), "世界観好き");






	DrawGraph(0, 0, GraphData[3], TRUE);//背景
	DrawGraph(0, 0, GraphData[0], TRUE);//hidariue
	DrawGraph(0, 0, GraphData[1], TRUE);//サウンドバー
	DrawGraph(0, 0, GraphData[6], TRUE);//戻る
	if(SetUI(1385, 769, 1773, 769, 1385, 967, 1773, 967))
		DrawGraph(0, 0, GraphData[7], TRUE);//戻る

	//DrawGraph(935, 448, GraphData[2], true);//ボール

	//マウス座標取得
	GetMousePoint(&mouseX, &mouseY);

	if (SetUI(115, 553, 1850, 553, 115, 590, 1850, 590) && MousePush(MOUSE_INPUT_LEFT))
	{
		VolumeBall = 0;
		newMouse = mouseX;
		VolumeBall++;
	}

	
		DrawGraph(newMouse - 950, 175, GraphData[2], TRUE);//ボール
		SetFontSize(60);
		DrawFormatString(670, 380, GetColor(255, 255, 255), ":%d", SoundVolume);
	
	

	if (oldMouse < 115) oldMouse = 115;
	if (oldMouse > 1850)oldMouse = 1850;

	if (SoundVolume > 160)SoundVolume = 160;
	//ホーム画面遷移
	if (MousePush(MOUSE_INPUT_RIGHT) == true)
	{
		ChangeGameScene = MainScene;

		return;
	}
	//デバック機能
	if (DebugMode == true)
	{
		GetMousePoint(&mouseX, &mouseY);

		SetFontSize(15);
		DrawFormatString(width - 200, 0, GetColor(255, 255, 255), "%s%s", GameSceneName[NowGameScene], "オプション描画中");

		DrawFormatString(100, 100, GetColor(255, 255, 255), "マウスX:%d", mouseX);
		DrawFormatString(200, 100, GetColor(255, 255, 255), "マウスY:%d", mouseY);
	}
}



//チュートリアル初期化  
void TutorialInit(void)
{
	//すでに読み込んだサウンドを停止
	StopSoundMem(SoundData[2]);
	StopSoundMem(SoundData[3]);


	//メモリに格納されているアニメーション以外のデータを解放
	for (int i = 0; i < 201; i++) { DeleteGraph(GraphData[i]); }


	TutorialTextureLoad();

	TutorialState = 0;
	TimeCount = 0;

	return;
}
//チュートリアル管理	
void TutorialCtrl(void)
{
	TutorialProc();
	TutorialDraw();

	return;
}
//チュートリアル処理	
void TutorialProc(void)
{

	GetMousePoint(&mouseX, &mouseY);

	TimeCount++;

	if (SetUI(1592, 838, 1850, 838, 1592, 941, 1850, 941) == true)
	{
		if (MousePush(MOUSE_INPUT_LEFT) == true)
		{
			TutorialState++;
			if (TutorialState <= 2)TimeCount = 0;
		}
	}

	if (SetUI(60, 838, 327, 838, 60, 941, 327, 941) == true)
	{
		if (MousePush(MOUSE_INPUT_LEFT) == true)
		{
			TutorialState--;
			TimeCount = 0;
		}

	}

	if (TutorialState < 0)TutorialState = 0;
	if (TutorialState > 2)TutorialState = 2;

	if (TutorialState == 2)
	{


		if (SetUI(1385, 769, 1773, 769, 1385, 967, 1773, 967) && MousePush(MOUSE_INPUT_LEFT) && TimeCount > 80)
		{

			ChangeGameScene = MainScene;

			return;
		}
	}

	return;
}
//チュートリアル描画	
void TutorialDraw(void)
{




	DrawGraph(0, 0, GraphData[7], TRUE);//説明



	if (TutorialState == 0)
	{
		DrawGraph(350, 100, GraphData[4], TRUE);//説明

		if (SetUI(1592, 838, 1850, 838, 1592, 941, 1850, 941) == true)
		{
			DrawGraph(0, 0, GraphData[3], TRUE);//矢印選択
		}
		else DrawGraph(0, 0, GraphData[2], TRUE);//右矢印





	}
	else if (TutorialState == 1)
	{
		DrawGraph(350, 100, GraphData[5], TRUE);//説明


		if (SetUI(1592, 838, 1850, 838, 1592, 941, 1850, 941) == true)
		{
			DrawGraph(0, 0, GraphData[3], TRUE);//左矢印選択
		}
		else DrawGraph(0, 0, GraphData[2], TRUE);//右矢印


		if (SetUI(60, 838, 327, 838, 60, 941, 327, 941) == true)
		{
			DrawGraph(0, 0, GraphData[1], TRUE);//左矢印選択
		}
		else DrawGraph(0, 0, GraphData[0], TRUE);//左矢印



	}
	else if (TutorialState == 2)
	{

		DrawGraph(350, 100, GraphData[6], TRUE);//説明

		if (SetUI(60, 838, 327, 838, 60, 941, 327, 941) == true)
		{
			DrawGraph(0, 0, GraphData[1], TRUE);//矢印選択
		}
		else DrawGraph(0, 0, GraphData[0], TRUE);//右矢印

		DrawGraph(0, 0, GraphData[9], TRUE);
		if(TimeCount > 80) DrawGraph(0, 0, GraphData[10], TRUE);

	}



	return;
}







//防衛初期化
void DefInit(void)
{

//----------------------------------------------------------------
//DX_TEST_0704以降のサンプルに移行するべきデータ
//----------------------------------------------------------------
	//すでに読み込んだサウンドを停止
	StopSoundMem(SoundData[2]);
	StopSoundMem(SoundData[3]);

//----------------------------------------------------------------
//DX_TEST_0704以降のサンプルに移行するべきデータ(ここまで）
//----------------------------------------------------------------

	if (LoadMovie != true)
	{
		//メモリに格納されているアニメーション以外のデータを解放
		for (int i = 0; i < 201; i++) { DeleteGraph(GraphData[i]); }
		BattleTextureLoad();
		LoadMovie = true;

		// ランダムに背景画像を選択
		SelectedBackgroundIndex = GetRand(3);

		

	}

		//音量設定
		ChangeVolumeSoundMem(255 * 40 / 100, SoundData[8]);

		//ループ位置の変更←これがないとプログラム動かん(´;ω;｀)
		SetLoopPosSoundMem(0, SoundData[8]);

		//ボイスを再生
		PlaySoundMem(SoundData[8], DX_PLAYTYPE_BACK, FALSE);

	hasyaLR = true;			//発射台選択分けtrueで左選択、falseで右選択
	hasyaL.color = true;    //左クレー色選択trueで赤クレー、falseで青クレー
	hasyaL.v = 1;			//左クレー速度　v == 0,1,2 遅、普通、早
	hasyaL.r = 1;			//左クレー角度　r == 0,1,2 30,45,60　
	hasyaR.color = true;	//右クレー色選択trueで赤クレー、falseで青クレー
	hasyaR.v = 1;			//右クレー速度　v == 0,1,2 遅、普通、早
	hasyaR.r = 1;			//右クレー角度　r == 0,1,2 30,45,60　
	animeF = 0;				//アニメーションフレーム調節
	animeN = 1;				//アニメーション
	kumoMove[0] = -1770;
	kumoMove[1] = 0;

	Cley1.Position = VGet(0, 0, 0);
	Cley2.Position = VGet(0, 0, 0);



	if (DebugMode == true)
	{
		DrawFormatString(width - 200, 0, GetColor(255, 255, 255), "%s%s", GameSceneName[ChangeGameScene], "初期化");




	}





		return;
	}



//防衛管理	
void DefCtrl(void)
	{

	DefProc();
	DefDraw();

		return;
	}



//防衛処理	
void DefProc(void)
{

	if (DebugMode == true)
	{

		//DrawFormatString(300, 300, GetColor(255, 255, 255), "まうすX%d", DebugMouseX);
		//DrawFormatString(300, 320, GetColor(255, 255, 255), "まうすY%d", DebugMouseY);



		if (KeyClick(KEY_INPUT_A) == true)
		{
			AtackScore++;
		}

		if (KeyClick(KEY_INPUT_D) == true)
		{
			DefenceScore++;
		}

	}



	if (animeN >= 1000)
	{


		//左の発射台クリックで左発射台用設定に変更
		if (SetUI(-1, 613, 150, 550, -1, 973, 149, 967) || SetUI(147, 550, 355, 560, 147, 967, 355, 960))
			if (MouseDown(MOUSE_INPUT_LEFT) == true)
				hasyaLR = true;
		//右の発射台クリックで右発射台用設定に変更
		if (SetUI(1573, 570, 1785, 560, 1578, 970, 1780, 970) || SetUI(1782, 464, 1930, 560, 1780, 970, 1930, 984))
			if (MouseDown(MOUSE_INPUT_LEFT) == true)
				hasyaLR = false;


		//左発射台用設定時にそれぞれのUI押した際に対応した変数を変更
		if (hasyaLR == true && MouseDown(MOUSE_INPUT_LEFT)) {
			if (SetUI(754, 311, 938, 311, 754, 354, 938, 354)) hasyaL.color = false;
			if (SetUI(1010, 311, 1192, 311, 1010, 354, 1192, 354)) hasyaL.color = true;

			if (SetUI(918, 377, 965, 377, 918, 420, 965, 420)) hasyaL.v = 0;
			if (SetUI(1036, 377, 1130, 377, 1036, 420, 1130, 420)) hasyaL.v = 1;
			if (SetUI(1201, 377, 1250, 377, 1201, 420, 1250, 420)) hasyaL.v = 2;

			if (SetUI(917, 443, 986, 443, 917, 486, 986, 486)) hasyaL.r = 0;
			if (SetUI(1059, 443, 1129, 443, 1059, 486, 1129, 486)) hasyaL.r = 1;
			if (SetUI(1200, 443, 1270, 443, 1200, 486, 1270, 486)) hasyaL.r = 2;



			//----------------------材質追加---------------------
			if (SetUI(960, 503, 1050, 503, 960, 543, 1050, 543)) hasyaL.zaisitu =true;
			if (SetUI(1125, 503, 1214, 503, 1125, 543, 1214, 543)) hasyaL.zaisitu = false;
		}

		//右発射台用設定時にそれぞれのUI押した際に対応した変数を変更
		if (hasyaLR == false && MouseDown(MOUSE_INPUT_LEFT)) {
			if (SetUI(754, 311, 938, 311, 754, 354, 938, 354)) hasyaR.color = false;
			if (SetUI(1010, 311, 1192, 311, 1010, 354, 1192, 354)) hasyaR.color = true;

			if (SetUI(918, 377, 965, 377, 918, 420, 965, 420)) hasyaR.v = 0;
			if (SetUI(1036, 377, 1130, 377, 1036, 420, 1130, 420)) hasyaR.v = 1;
			if (SetUI(1201, 377, 1250, 377, 1201, 420, 1250, 420)) hasyaR.v = 2;

			if (SetUI(917, 443, 986, 443, 917, 486, 986, 486)) hasyaR.r = 0;
			if (SetUI(1059, 443, 1129, 443, 1059, 486, 1129, 486)) hasyaR.r = 1;
			if (SetUI(1200, 443, 1270, 443, 1200, 486, 1270, 486))hasyaR.r = 2;


			//----------------------材質追加---------------------
			if (SetUI(960, 503, 1050, 503, 960, 543, 1050, 543)) hasyaR.zaisitu = true;
			if (SetUI(1125, 503, 1214, 503, 1125, 543, 1214, 543)) hasyaR.zaisitu = false;
		}

		//準備完了押したとき攻撃ターン遷移
		if (SetUI(1204, 635, 1511, 653, 1041, 797, 1513, 796) && MouseClick(MOUSE_INPUT_LEFT))
			ChangeGameScene = AtackScene;

	}


	if (AtackScore >= WinScore || DefenceScore >= WinScore)
	{
		ChangeGameScene = ResultScene;

		return;
	}
	
	
	kumoMove[1] += 1;
	kumoMove[0] += 1;

	if (kumoMove[0] > -620 && kumoMove[0] < -610) kumoMove[1] = -1920;
	if (kumoMove[1] > -200 && kumoMove[1] < -190) kumoMove[0] = -1770;



		return;
	}


//防衛描画	
void DefDraw(void) 
	{

	// 選択された背景画像の描画

	DrawGraph(0, 0, GraphData[181], true);
	DrawGraph(kumoMove[1]*1.1, kumoMove[1], GraphData[182], true);
	DrawGraph(kumoMove[0] * 1.1, kumoMove[0], GraphData[182], true);

	DrawGraph(0, 0, GraphData[SelectedBackgroundIndex], true);
	

	if (hasyaL.color == true) DrawGraph(0, 0, GraphData[4], true);//発射台　左　赤
	if (hasyaR.color == true)DrawGraph(0, 0, GraphData[5], true);//発射台　右　赤
	if (hasyaL.color == false) DrawGraph(0, 0, GraphData[168], true);//発射台　左　青
	if (hasyaR.color == false)DrawGraph(0, 0, GraphData[169], true);//発射台　右　青

	DrawGraph(10, 0, GraphData[6], true);//pc

	if (SetUI(1204, 635, 1511, 653, 1041, 797, 1513, 796)) DrawGraph(0, 0, GraphData[166], true);

	
	if (hasyaLR == true) //左の発射台がクリックされている＝　hasya==true
	{
		DrawGraph(1450, 0, GraphData[8], true);//右上にサブウィンドウ
		DrawGraph(0, 0, GraphData[7], true);//真ん中のメインウィンドウ

		if (hasyaL.color == true) DrawGraph(0, 0, GraphData[165], true);//発射台　左　赤　選択時発光
		if (hasyaL.color == false) DrawGraph(0, 0, GraphData[170], true);//発射台　左　青　選択時発光


		SetFontSize(45);

		//左の発射台選択時のメインウィンドウ処理 color==true 赤クレー、false==青クレー　v == 0,1,2 遅、普通、早　r == 30,45,60
		if (hasyaL.color == true) { DrawFormatString(750, 312, GetColor(255, 255, 255), "青クレー / "); DrawFormatString(750, 312, GetColor(255, 30, 30), "　　　　   赤クレー"); }
		else { DrawFormatString(750, 312, GetColor(255, 255, 255), "　　　　 / 赤クレー"); DrawFormatString(750, 312, GetColor(255, 30, 30), "青クレー"); }

		if (hasyaL.v == 0) { DrawFormatString(920, 375, GetColor(255, 255, 255), "　 - 普通 - 早");	DrawFormatString(920, 375, GetColor(255, 30, 30), "遅"); }
		if (hasyaL.v == 1) { DrawFormatString(920, 375, GetColor(255, 255, 255), "遅 - 　　 - 早");	DrawFormatString(920, 375, GetColor(255, 30, 30), "　   普通"); }
		if (hasyaL.v == 2) { DrawFormatString(920, 375, GetColor(255, 255, 255), "遅 - 普通 - ");    DrawFormatString(920, 375, GetColor(255, 30, 30), "　   　     早"); }

		if (hasyaL.r == 0) { DrawFormatString(920, 445, GetColor(255, 255, 255), "    - 45°- 60°"); DrawFormatString(920, 445, GetColor(255, 30, 30), "30°"); }
		if (hasyaL.r == 1) { DrawFormatString(920, 445, GetColor(255, 255, 255), "30°-     - 60°");   DrawFormatString(920, 445, GetColor(255, 30, 30), "      45°"); }
		if (hasyaL.r == 2) { DrawFormatString(920, 445, GetColor(255, 255, 255), "30°- 45°-     ");   DrawFormatString(920, 445, GetColor(255, 30, 30), "            60°"); }
 


		//----------------------材質 ---------------------
		if (hasyaL.zaisitu == true) { DrawFormatString(960, 500, GetColor(255, 255, 255), "　　 / オフ");	DrawFormatString(960, 500, GetColor(255, 30, 30), "オン"); }
		else						{ DrawFormatString(960, 500, GetColor(255, 255, 255), "オン / ");		DrawFormatString(960, 500, GetColor(255, 30, 30), "　　   オフ"); }


		//左の発射台選択時のサブウィンドウ処理 color==true 赤クレー、false==青クレー　v == 0,1,2 遅、普通、早　r == 30,45,60


		//----------------------材質 　　　　ここらへんyの値変更した---------------------
		DrawFormatString(1515, 85, GetColor(255, 255, 255), "発射台【右】");

		if (hasyaR.color == true)	DrawFormatString(1515, 160, GetColor(255, 255, 255), "赤クレー");
		else 						DrawFormatString(1515, 160, GetColor(255, 255, 255), "青クレー"); // X座標がイチゴイチゴになっている　　<= やかましいわ

		if (hasyaR.v == 0)	DrawFormatString(1490, 210, GetColor(255, 255, 255), "【速度】遅");
		if (hasyaR.v == 1)	DrawFormatString(1490, 210, GetColor(255, 255, 255), "【速度】普通");
		if (hasyaR.v == 2)	DrawFormatString(1490, 210, GetColor(255, 255, 255), "【速度】早");


		if (hasyaR.r == 0)	DrawFormatString(1490, 270, GetColor(255, 255, 255), "【角度】30°");
		if (hasyaR.r == 1)	DrawFormatString(1490, 270, GetColor(255, 255, 255), "【角度】45°");
		if (hasyaR.r == 2)	DrawFormatString(1490, 270, GetColor(255, 255, 255), "【角度】60°");

		if (hasyaR.zaisitu == false)	DrawFormatString(1490, 330, GetColor(255, 255, 255), "【材質】オフ");
		if (hasyaR.zaisitu == true)		DrawFormatString(1490, 330, GetColor(255, 255, 255), "【材質】オン");
	}

	if (hasyaLR == false) //右の発射台がクリックされている＝　hasya== false

	{
		DrawGraph(0, 0, GraphData[8], true);//左上サブウィンドウ
		DrawGraph(0, 0, GraphData[9], true);//真ん中のメインウィンドウ
		SetFontSize(45);

		if (hasyaR.color == true) DrawGraph(0, 0, GraphData[167], true);//赤　選択時発光
		if (hasyaR.color == false) DrawGraph(0, 0, GraphData[171], true);//青　選択時発光



		//右の発射台選択時のメインウィンドウ処理　color==true 赤クレー、false==青クレー　v == 0,1,2 遅、普通、早　r == 30,45,60
		if (hasyaR.color == true) 
		{ 
			DrawFormatString(750, 312, GetColor(255, 255, 255), "青クレー / "); 
			DrawFormatString(750, 312, GetColor(255, 30, 30), "　　　　   赤クレー"); 
		}
		else 
		{
			DrawFormatString(750, 312, GetColor(255, 255, 255), "　　　　 / 赤クレー"); 
			DrawFormatString(750, 312, GetColor(255, 30, 30), "青クレー");
		}

		if (hasyaR.v == 0) { DrawFormatString(920, 375, GetColor(255, 255, 255), "　 - 普通 - 早");	DrawFormatString(920, 375, GetColor(255, 30, 30), "遅"); }
		if (hasyaR.v == 1) { DrawFormatString(920, 375, GetColor(255, 255, 255), "遅 - 　　 - 早");	DrawFormatString(920, 375, GetColor(255, 30, 30), "　   普通"); }
		if (hasyaR.v == 2) { DrawFormatString(920, 375, GetColor(255, 255, 255), "遅 - 普通 - ");   DrawFormatString(920, 375, GetColor(255, 30, 30), "　   　     早"); }


		if (hasyaR.r == 0) { DrawFormatString(920, 445, GetColor(255, 255, 255), "    - 45°- 60°"); DrawFormatString(920, 445, GetColor(255, 30, 30), "30°"); }
		if (hasyaR.r == 1) { DrawFormatString(920, 445, GetColor(255, 255, 255), "30°-     - 60°");   DrawFormatString(920, 445, GetColor(255, 30, 30), "      45°"); }
		if (hasyaR.r == 2) { DrawFormatString(920, 445, GetColor(255, 255, 255), "30°- 45°-     ");   DrawFormatString(920, 445, GetColor(255, 30, 30), "            60°"); }


		//----------------------材質 ---------------------
		if (hasyaR.zaisitu == true) {
			DrawFormatString(960, 500, GetColor(255, 255, 255), "　　 / オフ");
			DrawFormatString(960, 500, GetColor(255, 30, 30), "オン"); 
		}
		else { DrawFormatString(960, 500, GetColor(255, 255, 255), "オン / ");		DrawFormatString(960, 500, GetColor(255, 30, 30), "　　   オフ"); }




		//右の発射台選択時のサブウィンドウ処理 color==true 赤クレー、false==青クレー　v == 0,1,2 遅、普通、早　r == 30,45,60

		//----------------------材質 　　　　ここらへんyの値変更した---------------------
		DrawFormatString(50, 85, GetColor(255, 255, 255), "発射台【左】");

		if (hasyaL.color == true)	DrawFormatString(50, 160, GetColor(255, 255, 255), "赤クレー");
		else 						DrawFormatString(50, 160, GetColor(255, 255, 255), "青クレー");

		if (hasyaL.v == 0)	DrawFormatString(25, 210, GetColor(255, 255, 255), "【速度】遅");
		if (hasyaL.v == 1)	DrawFormatString(25, 210, GetColor(255, 255, 255), "【速度】普通");
		if (hasyaL.v == 2)	DrawFormatString(25, 210, GetColor(255, 255, 255), "【速度】早");


		if (hasyaL.r == 0)	DrawFormatString(25, 270, GetColor(255, 255, 255), "【角度】30°");
		if (hasyaL.r == 1)	DrawFormatString(25, 270, GetColor(255, 255, 255), "【角度】45°");
		if (hasyaL.r == 2)	DrawFormatString(25, 270, GetColor(255, 255, 255), "【角度】60°");

		if (hasyaL.zaisitu == false)	DrawFormatString(25, 330, GetColor(255, 255, 255), "【材質】オフ");
		if (hasyaL.zaisitu == true)		DrawFormatString(25, 330, GetColor(255, 255, 255), "【材質】オン");
	}


	//スコア表示

	SetDrawBlendMode(DX_BLENDMODE_MULA, 150);
	DrawGraph(0, 0, GraphData[192], true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	DrawGraph(0, 0, GraphData[193], true);


	/*
	SetDrawBlendMode(DX_BLENDMODE_MULA, 150);
	DrawGraph(0, 0, GraphData[195], true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	DrawGraph(0, 0, GraphData[194], true);
	*/




	SetFontSize(100);
	DrawFormatString(1030, 75, GetColor(255, 255, 255), "%.1lf", AtackScore);
	DrawFormatString(720, 75, GetColor(255, 255, 255), "%.1lf", DefenceScore);
	SetFontSize(45);
	DrawFormatString(1080, 15, GetColor(255, 255, 255), "%d", battleRound);

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);


	//防衛ターンアニメーション時間調節
	if (animeN <= 77)
	{
		animeN++;
		if (animeN >= 78) {
			animeN = 1000;
		}

	}

	

	DrawGraph(0, -50, AnimData[(animeN + 10)], true);//防衛ターンアニメーション描画

		GetMousePoint(&mouseX, &mouseY);
		SetFontSize(30);

	if (DebugMode == true)
	{
		

		DrawFormatString(width - 200, 0, GetColor(255, 255, 255), "%s%s", GameSceneName[NowGameScene], "描画中");

		DrawFormatString(300, 300, GetColor(255, 255, 255), "まうすX%d", mouseX);
		DrawFormatString(300, 320, GetColor(255, 255, 255), "まうすY%d", mouseY);

		DrawFormatString(100, 100, GetColor(255, 255, 255), "攻撃の点数%f", AtackScore);
		DrawFormatString(100, 110, GetColor(255, 255, 255), "防衛の点数%f", DefenceScore);

		DrawFormatString(1000, 110, GetColor(255, 255, 255), "kumoMove[1] %d", kumoMove[1]);


		/*if (hasyaLR == true)
		{
			DrawFormatString(100, 200, GetColor(0, 0, 0), "左の発射台クリックです");
		}

		if (hasyaLR == false)
		{
			DrawFormatString(100, 200, GetColor(0, 0, 0), "右の発射台クリックです");
		}
		
		*/

	}

		
		return;
	}

	// カプセル型の定義
	struct Capsule 
	{
		VECTOR pointA;
		VECTOR pointB;
		float radius;
	};

	// カプセル型の衝突判定関数
	bool CheckCapsuleCollision(Capsule capsule, VECTOR spherePos, float sphereRadius) 
	{
		VECTOR AB = VSub(capsule.pointB, capsule.pointA);
		VECTOR AP = VSub(spherePos, capsule.pointA);
		float AB_AB = VDot(AB, AB);
		float AP_AB = VDot(AP, AB);

		float t = AP_AB / AB_AB;
		if (t < 0.0f) t = 0.0f;
		if (t > 1.0f) t = 1.0f;

		VECTOR closestPoint = VAdd(capsule.pointA, VScale(AB, t));
		VECTOR closestToSphere = VSub(spherePos, closestPoint);
		float distanceSquared = VDot(closestToSphere, closestToSphere);

		float combinedRadius = capsule.radius + sphereRadius;
		return distanceSquared <= (combinedRadius * combinedRadius);
	}

	// 3D空間での円を描画する関数
	void DrawCircle3D(VECTOR center, float radius, VECTOR normal, int segments, int color) 
	{
		VECTOR up = VGet(0.0f, 1.0f, 0.0f);
		if (VDot(normal, up) > 0.99f) {
			up = VGet(1.0f, 0.0f, 0.0f);
		}

		VECTOR right = VNorm(VCross(normal, up));
		up = VNorm(VCross(right, normal));

		for (int i = 0; i < segments; ++i) {
			float theta1 = 2.0f * DX_PI_F * i / segments;
			float theta2 = 2.0f * DX_PI_F * (i + 1) / segments;

			VECTOR p1 = VAdd(center, VAdd(VScale(right, radius * cosf(theta1)), VScale(up, radius * sinf(theta1))));
			VECTOR p2 = VAdd(center, VAdd(VScale(right, radius * cosf(theta2)), VScale(up, radius * sinf(theta2))));

			DrawLine3D(p1, p2, color);
		}
	}

	// カプセルを描画する関数
	void DrawCapsule(Capsule capsule, int color) 
	{
		// カプセルの端点を結ぶ線を描画
		DrawLine3D(capsule.pointA, capsule.pointB, color);

		// カプセルの端点に円を描画
		VECTOR normal = VNorm(VSub(capsule.pointB, capsule.pointA));
		DrawCircle3D(capsule.pointA, capsule.radius, normal, 32, color);
		DrawCircle3D(capsule.pointB, capsule.radius, normal, 32, color);
	}


	// クレーのカプセル定義
	Capsule frisbeeCapsule1;
	Capsule frisbeeCapsule2;


	int shootCo = 0;

	float CreyPosX_kari = 0;
	bool BreakCrey1 = false;
	bool BreakCrey2 = false;


















	//----------------------- -------------------
	
		void SoloInit(void) {
			if (LoadMovie != true)
			{
				//メモリに格納されているアニメーション以外のデータを解放
				for (int i = 0; i < 201; i++) 
				{ 
					DeleteGraph(GraphData[i]); 
				}
				BattleTextureLoad();
				LoadMovie = true;


				// ランダムに背景画像を選択
				SelectedBackgroundIndex = GetRand(2);


			}
			return;
		}

		void SoloCtrl(void) {

			Cley1.Position = VGet(0, 0, 0);
			Cley2.Position = VGet(0, 0, 0);

			GetRand(2);
			if (GetRand(2) == 0) hasyaR.color = true;
			if (GetRand(2) == 1) hasyaR.color = false;
			hasyaR.v = GetRand(3);
			hasyaR.r = GetRand(3);


			GetRand(2);
			if (GetRand(2) == 0) hasyaL.color = true;
			if (GetRand(2) == 1) hasyaL.color = false;
			hasyaL.v = GetRand(3);
			hasyaL.r = GetRand(3);


			ChangeGameScene = AtackScene;
			return;

		}
	


		float Cley1Time = 0;



//攻撃初期化
void AtackInit(void)
{
	Cley1Time = 0;

	//発射可能回数の初期値(2回)
	shootCo = 2;

	BreakCrey1 = false;	//ヒットフラグはoff
	BreakCrey2 = false;	//ヒットフラグはoff

	Cley1.Shooted = false;
	Cley2.Shooted = false;


	if (DebugMode == true)
	{
		DrawFormatString(width - 200, 0, GetColor(255, 255, 255), "%s%s", GameSceneName[ChangeGameScene], "初期化");

	}

	//すでに読み込んだサウンドを停止
	StopSoundMem(SoundData[7]);

	//すでに読み込んだサウンドを停止
	StopSoundMem(SoundData[8]);


	//-------------[座標系の変換]---------------------
	camPos = VGet(0, 0, 0);    //原点に置く
	camDir = VGet(0, 0, 1.0f); //Z軸正面
	camTop = VGet(0, 1.0f, 0); //頭はy咆哮を無垢
	//-------------------------------------------------

	
	//==================================================================
	//以下の長いやつ //絶対に消すな！！！！！！！特に比嘉！お前だよ！！
	//==================================================================
	
		// 回転( x, y, z軸回転の順 )＋座標移動行列の作成
	Bullet1TransformMatrix = MGetRotX(Bullet1.Angle.x);
	Bullet1TransformMatrix = MMult(Bullet1TransformMatrix, MGetRotY(Bullet1.Angle.y));
	Bullet1TransformMatrix = MMult(Bullet1TransformMatrix, MGetRotZ(Bullet1.Angle.z));
	Bullet1TransformMatrix = MMult(Bullet1TransformMatrix, MGetTranslate(VGet(Bullet1.Position.x, Bullet1.Position.y, Bullet1.Position.z)));

	// 行列を使ってワールド座標を算出
	Bullet1Vertex[0].pos = VTransform(VGet(-100.0f, 100.0f, 0.0f), Bullet1TransformMatrix);
	Bullet1Vertex[1].pos = VTransform(VGet(100.0f, 100.0f, 0.0f), Bullet1TransformMatrix);
	Bullet1Vertex[2].pos = VTransform(VGet(-100.0f, -100.0f, 0.0f), Bullet1TransformMatrix);
	Bullet1Vertex[3].pos = VTransform(VGet(100.0f, -100.0f, 0.0f), Bullet1TransformMatrix);

	Bullet1Vertex[4].pos = Bullet1Vertex[2].pos;
	Bullet1Vertex[5].pos = Bullet1Vertex[1].pos;

	// 行列を使って法線を算出
	Bullet1Vertex[0].norm = VTransformSR(VGet(0.0f, 0.0f, -1.0f), Bullet1TransformMatrix);
	Bullet1Vertex[1].norm = Bullet1Vertex[0].norm;
	Bullet1Vertex[2].norm = Bullet1Vertex[0].norm;
	Bullet1Vertex[3].norm = Bullet1Vertex[0].norm;
	Bullet1Vertex[4].norm = Bullet1Vertex[0].norm;
	Bullet1Vertex[5].norm = Bullet1Vertex[0].norm;


	// ２ポリゴン分の頂点の座標と法線以外のデータをセット
	Bullet1Vertex[0].dif = GetColorU8(255, 255, 255, 255);
	Bullet1Vertex[0].spc = GetColorU8(0, 0, 0, 0);
	Bullet1Vertex[0].u = 0.0f;
	Bullet1Vertex[0].v = 0.0f;
	Bullet1Vertex[0].su = 0.0f;
	Bullet1Vertex[0].sv = 0.0f;

	Bullet1Vertex[1].dif = GetColorU8(255, 255, 255, 255);
	Bullet1Vertex[1].spc = GetColorU8(0, 0, 0, 0);
	Bullet1Vertex[1].u = 1.0f;
	Bullet1Vertex[1].v = 0.0f;
	Bullet1Vertex[1].su = 0.0f;
	Bullet1Vertex[1].sv = 0.0f;

	Bullet1Vertex[2].dif = GetColorU8(255, 255, 255, 255);
	Bullet1Vertex[2].spc = GetColorU8(0, 0, 0, 0);
	Bullet1Vertex[2].u = 0.0f;
	Bullet1Vertex[2].v = 1.0f;
	Bullet1Vertex[2].su = 0.0f;
	Bullet1Vertex[2].sv = 0.0f;

	Bullet1Vertex[3].dif = GetColorU8(255, 255, 255, 255);
	Bullet1Vertex[3].spc = GetColorU8(0, 0, 0, 0);
	Bullet1Vertex[3].u = 1.0f;
	Bullet1Vertex[3].v = 1.0f;
	Bullet1Vertex[3].su = 0.0f;
	Bullet1Vertex[3].sv = 0.0f;

	Bullet1Vertex[4] = Bullet1Vertex[2];
	Bullet1Vertex[5] = Bullet1Vertex[1];

	//=================================================================

	//２発目用


		// 回転( x, y, z軸回転の順 )＋座標移動行列の作成
	Bullet2TransformMatrix = MGetRotX(Bullet2.Angle.x);
	Bullet2TransformMatrix = MMult(Bullet2TransformMatrix, MGetRotY(Bullet2.Angle.y));
	Bullet2TransformMatrix = MMult(Bullet2TransformMatrix, MGetRotZ(Bullet2.Angle.z));
	Bullet2TransformMatrix = MMult(Bullet2TransformMatrix, MGetTranslate(VGet(Bullet2.Position.x, Bullet2.Position.y, Bullet2.Position.z)));

	// 行列を使ってワールド座標を算出
	Bullet2Vertex[0].pos = VTransform(VGet(-100.0f, 100.0f, 0.0f), Bullet2TransformMatrix);
	Bullet2Vertex[1].pos = VTransform(VGet(100.0f, 100.0f, 0.0f), Bullet2TransformMatrix);
	Bullet2Vertex[2].pos = VTransform(VGet(-100.0f, -100.0f, 0.0f), Bullet2TransformMatrix);
	Bullet2Vertex[3].pos = VTransform(VGet(100.0f, -100.0f, 0.0f), Bullet2TransformMatrix);

	Bullet2Vertex[4].pos = Bullet2Vertex[2].pos;
	Bullet2Vertex[5].pos = Bullet2Vertex[1].pos;

	// 行列を使って法線を算出
	Bullet2Vertex[0].norm = VTransformSR(VGet(0.0f, 0.0f, -1.0f), Bullet2TransformMatrix);
	Bullet2Vertex[1].norm = Bullet2Vertex[0].norm;
	Bullet2Vertex[2].norm = Bullet2Vertex[0].norm;
	Bullet2Vertex[3].norm = Bullet2Vertex[0].norm;
	Bullet2Vertex[4].norm = Bullet2Vertex[0].norm;
	Bullet2Vertex[5].norm = Bullet2Vertex[0].norm;


	// ２ポリゴン分の頂点の座標と法線以外のデータをセット
	Bullet2Vertex[0].dif = GetColorU8(255, 255, 255, 255);
	Bullet2Vertex[0].spc = GetColorU8(0, 0, 0, 0);
	Bullet2Vertex[0].u = 0.0f;
	Bullet2Vertex[0].v = 0.0f;
	Bullet2Vertex[0].su = 0.0f;
	Bullet2Vertex[0].sv = 0.0f;

	Bullet2Vertex[1].dif = GetColorU8(255, 255, 255, 255);
	Bullet2Vertex[1].spc = GetColorU8(0, 0, 0, 0);
	Bullet2Vertex[1].u = 1.0f;
	Bullet2Vertex[1].v = 0.0f;
	Bullet2Vertex[1].su = 0.0f;
	Bullet2Vertex[1].sv = 0.0f;

	Bullet2Vertex[2].dif = GetColorU8(255, 255, 255, 255);
	Bullet2Vertex[2].spc = GetColorU8(0, 0, 0, 0);
	Bullet2Vertex[2].u = 0.0f;
	Bullet2Vertex[2].v = 1.0f;
	Bullet2Vertex[2].su = 0.0f;
	Bullet2Vertex[2].sv = 0.0f;

	Bullet2Vertex[3].dif = GetColorU8(255, 255, 255, 255);
	Bullet2Vertex[3].spc = GetColorU8(0, 0, 0, 0);
	Bullet2Vertex[3].u = 1.0f;
	Bullet2Vertex[3].v = 1.0f;
	Bullet2Vertex[3].su = 0.0f;
	Bullet2Vertex[3].sv = 0.0f;

	Bullet2Vertex[4] = Bullet2Vertex[2];
	Bullet2Vertex[5] = Bullet2Vertex[1];



	//----------弾の初期化------------------

	//１発目
	Bullet1.Angle.x = 0.0f;
	Bullet1.Angle.y = 0.0f;
	Bullet1.Angle.z = 0.0f;
	Bullet1.Position.x = 0;
	Bullet1.Position.y = 0;
	Bullet1.Position.z = 0;
	Bullet1.IsMoving = false;

	//２発目
	Bullet2.Angle.x = 0.0f;
	Bullet2.Angle.y = 0.0f;
	Bullet2.Angle.z = 0.0f;
	Bullet2.Position.x = 0;
	Bullet2.Position.y = 0;
	Bullet2.Position.z = 0;
	Bullet2.IsMoving = false;


	BulletSpeed = 500.0f; // 銃弾の移動速度



	//シーン切り替え後の経過フレーム数を初期化
	GameSceneFrameCount[ChangeGameScene] = 0;


	animeF = 0;
	animeN = 0;
	animeN2 = 0;


	//==================================
	//防衛のステ‐タスを反映

		//発射台：左

	//yだけ変化するため、それら以外は以下で一気に初期化
	Cley1.Position.x = -1300;
	Cley1.Position.z = 300;

	Cley2.Position.x = 1300;
	Cley2.Position.z = 300;


	Cley1.Dir.x = 1;
	Cley1.Dir.z = 1;

	Cley2.Dir.x = -1;
	Cley2.Dir.z = 1;


	//発射台：左
	
		//速さ
	if (hasyaL.v == 0)	
	{
		Cley1.Speed = 40; //速度40

		if (hasyaL.r == 0)//30°の時の
		{					
			Cley1.Position.y = -100;
			Cley1.Dir.y = 0.9f;
		}		
		else if (hasyaL.r == 1)//45°の時の位置
		{
			Cley1.Position.y = 0;
			Cley1.Dir.y = 1.0;

		}
		else if (hasyaL.r == 2)//60°の時の位置
		{
			Cley1.Position.y = 200;
			Cley1.Dir.y = 1.0;

		}
	}
	else if (hasyaL.v == 1)		
	{

		Cley1.Speed = 60;	//速さ60

		if (hasyaL.r == 0)		//30°の時の位置
		{
			Cley1.Position.y = -300;
			Cley1.Dir.y = 0.8;

		}
		else if (hasyaL.r == 1)			//45°	の時の位置 
		{
			Cley1.Position.y = -150;
			Cley1.Dir.y = 0.9;

		}
		else if (hasyaL.r == 2)		  //60°	の時の位置
		{
			Cley1.Position.y = 0;
			Cley1.Dir.y = 1.0;

		}
	}
	else if (hasyaL.v == 2)		//早い
	{
		Cley1.Speed = 80;

		if (hasyaL.r == 0)					//30°の時の位置
		{
			Cley1.Position.y = -400;
			Cley1.Dir.y = 0.8;

		}
		else if (hasyaL.r == 1)		//45°	の時の位置 
		{
			Cley1.Position.y = -200;
			Cley1.Dir.y = 0.9;

		}
		else if (hasyaL.r == 2)		 //60°	の時の位置
		{
			Cley1.Position.y = 0;
			Cley1.Dir.y = 1.0;

		}
	}

			if (hasyaL.color == true) Cley1.Color = 2; //赤が選ばれてた場合、hasyaL.color(bool) = true  よって、フリスビーカラーを青色に
			else Cley1.Color = 1;

	//----------------------------------------------------------------------------------------------------
	//発射台：右　　
			
	if (hasyaR.v == 0)
	{
		Cley2.Speed = 40; //速度40

		if (hasyaR.r == 0)//30°の時の
		{
			Cley2.Position.y = -100;
			Cley2.Dir.y = 0.9f;
		}
		else if (hasyaR.r == 1)//45°の時の位置
		{
			Cley2.Position.y = 0;
			Cley2.Dir.y = 1.0;

		}
		else if (hasyaR.r == 2)//60°の時の位置
		{
			Cley2.Position.y = 200;
			Cley2.Dir.y = 1.0;

		}
	}
	else if (hasyaR.v == 1)
	{

		Cley2.Speed = 60;	//速さ60

		if (hasyaR.r == 0)		//30°の時の位置
		{
			Cley2.Position.y = -300;
			Cley2.Dir.y = 0.8;

		}
		else if (hasyaR.r == 1)			//45°	の時の位置
		{
			Cley2.Position.y = -150;
			Cley2.Dir.y = 0.9;

		}
		else if (hasyaR.r == 2)		  //60°	の時の位置
		{
			Cley2.Position.y = 0;
			Cley2.Dir.y = 1.0;

		}
	}
	else if (hasyaR.v == 2)		//早い
	{
		Cley2.Speed = 80;

		if (hasyaR.r == 0)					//30°の時の位置
		{
			Cley2.Position.y = -400;
			Cley2.Dir.y = 0.8;

		}
		else if (hasyaR.r == 1)		//45°	の時の位置
		{
			Cley2.Position.y = -200;
			Cley2.Dir.y = 0.9;

		}
		else if (hasyaR.r == 2)		 //60°	の時の位置
		{
			Cley2.Position.y = 0;
			Cley2.Dir.y = 1.0;

		}
	}

	if (hasyaR.color == true) Cley2.Color = 2; //赤が選ばれてた場合、hasyaL.color(bool) = true  よって、フリスビーカラーを青色に
	else Cley2.Color = 1;



			Cley1.IsMoving = false;
			Cley2.IsMoving = false;


			Cley1.BreakPosition = VGet(0, 0, 0);
			Cley1.Break = 0;
			Cley1.BreakMoveYgravity = 0;
			Cley1.BreakMoveX = 0;
			Cley1.BreakMoveY = 0;

			Cley2.BreakPosition = VGet(0, 0, 0);
			Cley2.Break = 0;
			Cley2.BreakMoveYgravity = 0;
			Cley2.BreakMoveX = 0;
			Cley2.BreakMoveY = 0;

			breakAnime1 = 0;
			breakAnime2 = 0;

//===========================================================================================================================


	int AtScore_keep = 0;
	int DfScore_keep = 0;


	//右側のクレイのx座標をとっておく。



	return;
}


//攻撃管理	
void AtackCtrl(void)
{

	AtackProc();
	AtackDraw();

	return;
}


//攻撃処理	
void AtackProc(void)
{
	//画面遷移用点数保持変数
	float AtScore_keep = AtackScore;
	float DfScore_keep = DefenceScore;


	MATRIX Mv;//ビュー行列
	MATRIX Mp;//ぷろじぇくしょｎ行列
	MATRIX MvMp; //上二つを乗算させたのを入れる
	MATRIX InversMvMp;//それの逆行列をとる。


	//マウスの位置を取る
	GetMousePoint(&mouseX, &mouseY);

	//カメラの生成
	SetCameraPositionAndTargetAndUpVec(camPos, camDir, camTop);
	SetCameraNearFar(1.0f, 10000.0f);//

	Mv = GetCameraViewMatrix();			//ビュー行列を格納
	Mp = GetCameraProjectionMatrix();   //プロジェクション行列を格納

	//================================================================
	// 計算
	//
	Ps.x = (float)((float)mouseX - (width / 2)) / (width / 2);
	Ps.y = float((height / 2) - (float)mouseY) / (height / 2);
	Ps.z = 0;

	MbMouseX = (float)mouseX - (width / 2);
	MbMouseY = (height / 2) - (mouseY);

	MvMp = MMult(Mp, Mv);
	InversMvMp = MInverse(MvMp);

	//Psベクトルをビュー行列とプロジェクション行列で変換(?)　＝＞　ベクトルを 1x4の行列 としてみなしてInversMpMv行列と乗算。
	PsToCam = VTransform(Ps, InversMvMp);

	VECTOR GunKari;


	GunKari = VSub(PsToCam, camPos);

	float GunKariSq = sqrt(pow(GunKari.x, 2) + pow(GunKari.y, 2) + (GunKari.z, 2));

	//===================================================================

	if (Cley2.Break == true) shootCo = 0;

	if (Cley1.Shooted == true)
	{
		if (MouseClick(MOUSE_INPUT_RIGHT) == true || MouseClick(MOUSE_INPUT_LEFT))
		{
			if(Cley2.Break != true) shootCo -= 1;
		}

		if (Bullet1.IsMoving != true && shootCo == 2)
		{

			//左クリックの時、Colorを蒼色に。そうでなければ、赤色で発射。
			if (MousePush(MOUSE_INPUT_LEFT) == true)
			{

				//音量設定
				ChangeVolumeSoundMem(255 * 45 / 100, SoundData[9]);
				//銃サウンドエフェクト
				PlaySoundMem(SoundData[9], DX_PLAYTYPE_BACK, true);

				//発射の方向を決定
				GunDir1.x = GunKari.x / GunKariSq;
				GunDir1.y = GunKari.y / GunKariSq;
				GunDir1.z = GunKari.z / GunKariSq;

				//Bullet1が動いている状態とする。
				Bullet1.IsMoving = true;
				Bullet1.Color = 1; // 1 => 青
				Bullet1.StartTime = GetNowCount();


			}
			else if (MousePush(MOUSE_INPUT_RIGHT) == true)
			{
				//音量設定
				ChangeVolumeSoundMem(255 * 45 / 100, SoundData[9]);
				//銃サウンドエフェクト
				PlaySoundMem(SoundData[9], DX_PLAYTYPE_BACK, true);

				//発射の方向を決定
				GunDir1.x = GunKari.x / GunKariSq;
				GunDir1.y = GunKari.y / GunKariSq;
				GunDir1.z = GunKari.z / GunKariSq;

				//Bullet1が動いている状態とする。
				Bullet1.IsMoving = true;
				Bullet1.Color = 2; // 2 => 赤
				Bullet1.StartTime = GetNowCount();



			}


		}



		if (Bullet1.IsMoving)
		{

			//if (MouseClick(MOUSE_INPUT_LEFT) == true || MouseClick(MOUSE_INPUT_RIGHT) == true) shootCo -= 1;

			//Angle.x += 0.25;
			Bullet1.Position.x += GunDir1.x * BulletSpeed;
			Bullet1.Position.y += GunDir1.y * BulletSpeed;
			Bullet1.Position.z += GunDir1.z * BulletSpeed;

			if (GetNowCount() - Bullet1.StartTime > 3000)//初期状態に戻す
			{
				Bullet1.Position.x = 0;
				Bullet1.Position.y = 0;
				Bullet1.Position.z = 0;
				Bullet1.IsMoving = false;
			}

		}

		//２発目
		if (Bullet2.IsMoving != true && shootCo == 1)
		{

			//左クリックの時、Colorを蒼色に。そうでなければ、赤色で発射。
			if (MousePush(MOUSE_INPUT_LEFT) == true)
			{
				//音量設定
				ChangeVolumeSoundMem(255 * 45 / 100, SoundData[9]);
				//銃サウンドエフェクト
				PlaySoundMem(SoundData[9], DX_PLAYTYPE_BACK, true);

				//発射の方向を決定
				GunDir2.x = GunKari.x / GunKariSq;
				GunDir2.y = GunKari.y / GunKariSq;
				GunDir2.z = GunKari.z / GunKariSq;

				//Bullet1が動いている状態とする。
				Bullet2.IsMoving = true;
				Bullet2.Color = 1; // 1 => 青
				Bullet2.StartTime = GetNowCount();


			}
			else if (MousePush(MOUSE_INPUT_RIGHT) == true)
			{
				//音量設定
				ChangeVolumeSoundMem(255 * 45 / 100, SoundData[9]);
				//銃サウンドエフェクト
				PlaySoundMem(SoundData[9], DX_PLAYTYPE_BACK, true);

				//発射の方向を決定
				GunDir2.x = GunKari.x / GunKariSq;
				GunDir2.y = GunKari.y / GunKariSq;
				GunDir2.z = GunKari.z / GunKariSq;

				//Bullet1が動いている状態とする。
				Bullet2.IsMoving = true;
				Bullet2.Color = 2; // 2 => 赤
				Bullet2.StartTime = GetNowCount();


			}


		}
	}

	if (Bullet2.IsMoving)
	{

		//Angle.x += 0.25;
		Bullet2.Position.x += GunDir2.x * BulletSpeed;
		Bullet2.Position.y += GunDir2.y * BulletSpeed;
		Bullet2.Position.z += GunDir2.z * BulletSpeed;

		if (GetNowCount() - Bullet1.StartTime > 3000)//初期状態に戻す
		{
			Bullet2.Position.x = 0;
			Bullet2.Position.y = 0;
			Bullet2.Position.z = 0;
			Bullet2.IsMoving = false;
		}

	}






	// クレーの半径を設定
	float FrisbeeRadius = 300.0f; // クレーの当たり判定の半径を設定

	// 銃弾の半径を設定
	float BulletRadius = 200.0f; // 銃弾の当たり判定の半径を設定


	if (animeN >= 1050)//アニメーション終了後
	{
		// クレー（フリスビー）の初期位置と速度を設定
		void InitializeFrisbee();
		{

			if (Cley1.Shooted == false)
			{
				// スペースキーを押して、フリスビーの位置や状態を初期化する。	Movingがtrueのため、後のUpdata()関数でクレイが動く
				if (KeyPush(KEY_INPUT_SPACE) == true)
				{
					Cley1.IsMoving = true;
					Cley1.StartTime = GetNowCount();
					//FrisbeeVelocity1 = VGet(FrisbeeSpeed, 60, FrisbeeSpeed);// 初速度設定
					Cley1.Velocity.x = Cley1.Dir.x * Cley1.Speed;
					Cley1.Velocity.y = Cley1.Dir.y * Cley1.Speed;
					Cley1.Velocity.z = Cley1.Dir.z * Cley1.Speed;

					frisbeeCapsule1.pointA = Cley1.Position;
					frisbeeCapsule1.pointB = VAdd(Cley1.Position, VScale(Cley1.Velocity, 0.1f)); // 長さを調整
					frisbeeCapsule1.radius = FrisbeeRadius; // カプセルの半径を設定

					//音量設定
					ChangeVolumeSoundMem(255 * 45 / 100, SoundData[9]);
					//クレイサウンドエフェクト
					PlaySoundMem(SoundData[11], DX_PLAYTYPE_BACK, true);

					Cley1.Shooted = true;

				}
			}

			if (Cley1.Shooted == true) Cley1Time +=  1 * fps.deltaTime;

			if (Cley1Time >= 1 && Cley2.Shooted != true) Cley2.Shooted = true;

			
			if (Cley2.Shooted == true && Cley2.IsMoving != true && Cley2.Break != true)		//右側のクレイ。　左側が発射された後、n秒後に発射する。
			{
				Cley2.IsMoving = true;
				Cley2.StartTime = GetNowCount();
				//FrisbeeVelocity2 = VGet(FrisbeeSpeed, 60, FrisbeeSpeed);// 初速度設定
				Cley2.Velocity.x = Cley2.Dir.x * Cley2.Speed;
				Cley2.Velocity.y = Cley2.Dir.y * Cley2.Speed;
				Cley2.Velocity.z = Cley2.Dir.z * Cley2.Speed;

				frisbeeCapsule2.pointA = Cley2.Position;
				frisbeeCapsule2.pointB = VAdd(Cley2.Position, VScale(Cley2.Velocity, 0.1f)); // 長さを調整
				frisbeeCapsule2.radius = FrisbeeRadius; // カプセルの半径を設定

				//音量設定
				ChangeVolumeSoundMem(255 * 45 / 100, SoundData[9]);
				//クレイサウンドエフェクト
				PlaySoundMem(SoundData[11], DX_PLAYTYPE_BACK, true);


				
				/*
				IsFrisbeeMoving2 = true;
				FrisbeeStartTime2 = GetNowCount();
				FrisbeeVelocity2 = VGet(FrisbeeSpeed, 60, FrisbeeSpeed);// 初速度設定
				frisbeeCapsule2.pointA = FrisbeePosition2;
				frisbeeCapsule2.pointB = VAdd(FrisbeePosition2, VScale(FrisbeeVelocity2, 0.1f)); // 長さを調整
				frisbeeCapsule2.radius = FrisbeeRadius; // カプセルの半径を設定
				*/

					
						
							

			}
			




		}

		void UpdateFrisbee();
		{
			if (Cley1.IsMoving)
			{
				float t = (GetNowCount() - Cley1.StartTime) / 1000.0f;	//クレイの動きの更新
				Cley1.Velocity.y -= Gravity * t;	//重力による加速
				Cley1.Position = VAdd(Cley1.Position, Cley1.Velocity);	//速度に基づいた位置の更新(移動)
				Cley1.Velocity.x *= 0.99f;	//空気抵抗
				Cley1.Velocity.z *= 0.99f;	//空気抵抗

				// カプセルの更新
				frisbeeCapsule1.pointA = Cley1.Position;
				frisbeeCapsule1.pointB = VAdd(Cley1.Position, VScale(Cley1.Velocity, 0.1f));

				if (GetNowCount() - Cley1.StartTime > 6000) {
					Cley1.IsMoving = false;
				}
			}

			
			//クレイ二つ目
			if (Cley2.IsMoving)
			{
				float t = (GetNowCount() - Cley2.StartTime) / 1000.0f;	//クレイの動きの更新
				Cley2.Velocity.y -= Gravity * t;	//重力による加速
				Cley2.Position = VAdd(Cley2.Position, Cley2.Velocity);	//速度に基づいた位置の更新(移動)
				Cley2.Velocity.x *= 0.99f;	//空気抵抗
				Cley2.Velocity.z *= 0.99f;	//空気抵抗

				// カプセルの更新
				frisbeeCapsule2.pointA = Cley2.Position;
				frisbeeCapsule2.pointB = VAdd(Cley2.Position, VScale(Cley2.Velocity, 0.1f));

				if (GetNowCount() - Cley2.StartTime > 6000) {
					Cley2.IsMoving = false;
				}



			}
			


		}
	}




	//弾1,2の行列の生成↓
	{

		// 回転( x, y, z軸回転の順 )＋座標移動行列の作成
		Bullet1TransformMatrix = MGetRotX(Bullet1.Angle.x);
		Bullet1TransformMatrix = MMult(Bullet1TransformMatrix, MGetRotY(Bullet1.Angle.y));
		Bullet1TransformMatrix = MMult(Bullet1TransformMatrix, MGetRotZ(Bullet1.Angle.z));
		Bullet1TransformMatrix = MMult(Bullet1TransformMatrix, MGetTranslate(VGet(Bullet1.Position.x, Bullet1.Position.y, Bullet1.Position.z)));

		// 行列を使ってワールド座標を算出
		Bullet1Vertex[0].pos = VTransform(VGet(-100.0f, 100.0f, 0.0f), Bullet1TransformMatrix);
		Bullet1Vertex[1].pos = VTransform(VGet(100.0f, 100.0f, 0.0f), Bullet1TransformMatrix);
		Bullet1Vertex[2].pos = VTransform(VGet(-100.0f, -100.0f, 0.0f), Bullet1TransformMatrix);
		Bullet1Vertex[3].pos = VTransform(VGet(100.0f, -100.0f, 0.0f), Bullet1TransformMatrix);

		Bullet1Vertex[4].pos = Bullet1Vertex[2].pos;
		Bullet1Vertex[5].pos = Bullet1Vertex[1].pos;

		// 行列を使って法線を算出
		Bullet1Vertex[0].norm = VTransformSR(VGet(0.0f, 0.0f, -1.0f), Bullet1TransformMatrix);
		Bullet1Vertex[1].norm = Bullet1Vertex[0].norm;
		Bullet1Vertex[2].norm = Bullet1Vertex[0].norm;
		Bullet1Vertex[3].norm = Bullet1Vertex[0].norm;
		Bullet1Vertex[4].norm = Bullet1Vertex[0].norm;
		Bullet1Vertex[5].norm = Bullet1Vertex[0].norm;

		//２発目
	// 回転( x, y, z軸回転の順 )＋座標移動行列の作成
		Bullet2TransformMatrix = MGetRotX(Bullet2.Angle.x);
		Bullet2TransformMatrix = MMult(Bullet2TransformMatrix, MGetRotY(Bullet2.Angle.y));
		Bullet2TransformMatrix = MMult(Bullet2TransformMatrix, MGetRotZ(Bullet2.Angle.z));
		Bullet2TransformMatrix = MMult(Bullet2TransformMatrix, MGetTranslate(VGet(Bullet2.Position.x, Bullet2.Position.y, Bullet2.Position.z)));

		// 行列を使ってワールド座標を算出
		Bullet2Vertex[0].pos = VTransform(VGet(-100.0f, 100.0f, 0.0f), Bullet2TransformMatrix);
		Bullet2Vertex[1].pos = VTransform(VGet(100.0f, 100.0f, 0.0f), Bullet2TransformMatrix);
		Bullet2Vertex[2].pos = VTransform(VGet(-100.0f, -100.0f, 0.0f), Bullet2TransformMatrix);
		Bullet2Vertex[3].pos = VTransform(VGet(100.0f, -100.0f, 0.0f), Bullet2TransformMatrix);

		Bullet2Vertex[4].pos = Bullet2Vertex[2].pos;
		Bullet2Vertex[5].pos = Bullet2Vertex[1].pos;

		// 行列を使って法線を算出
		Bullet2Vertex[0].norm = VTransformSR(VGet(0.0f, 0.0f, -1.0f), Bullet2TransformMatrix);
		Bullet2Vertex[1].norm = Bullet2Vertex[0].norm;
		Bullet2Vertex[2].norm = Bullet2Vertex[0].norm;
		Bullet2Vertex[3].norm = Bullet2Vertex[0].norm;
		Bullet2Vertex[4].norm = Bullet2Vertex[0].norm;
		Bullet2Vertex[5].norm = Bullet2Vertex[0].norm;
	}



	//=======================================================================================

	//弾１とクレイ1の当たり判定
	if (Cley1.IsMoving && Bullet1.IsMoving && BreakCrey1 != true) 
	{
		if (CheckCapsuleCollision(frisbeeCapsule1, Bullet1.Position, BulletRadius)) 
		{

			if (Cley1.Color == Bullet1.Color)
			{

				Cley1.BreakPosition = Cley1.Position; //壊れた場所を記録
				Cley1.Break = 1;//１が壊れた状態が=1ですよ

				CollisionDisplayStartTime = GetNowCount(); // 衝突が発生した時間を記録
				Cley1.IsMoving = false;
				Bullet1.IsMoving = false;
				Bullet1.Position = VGet(0, 0, 0);
				Cley1.Position = VGet(0, 0, 0);
				BreakCrey1 = true;
			}
			//PlaySoundMem(CollisionSoundHandle, DX_PLAYTYPE_BACK);
		}
	}

	//弾２とクレイ1の判定
	if (Cley1.IsMoving && Bullet2.IsMoving && BreakCrey1 != true)
	{
		if (CheckCapsuleCollision(frisbeeCapsule1, Bullet2.Position, BulletRadius))
		{

			if (Cley1.Color == Bullet2.Color)
			{

				Cley1.BreakPosition = Cley1.Position; //2壊れた場所を記録
				Cley1.Break = 1;//2が壊れた状態が=1ですよ

				CollisionDisplayStartTime = GetNowCount(); // 衝突が発生した時間を記録
				Cley1.IsMoving = false;
				Bullet2.IsMoving = false;
				Bullet2.Position = VGet(0, 0, 0);
				Cley1.Position = VGet(0, 0, 0);
				BreakCrey1 = true;
			}
			//PlaySoundMem(CollisionSoundHandle, DX_PLAYTYPE_BACK);
		}
	}



	

//弾１とクレイ2の当たり判定
if (Cley2.IsMoving && Bullet1.IsMoving && BreakCrey2 != true)
{
	if (CheckCapsuleCollision(frisbeeCapsule2, Bullet1.Position, BulletRadius))
	{

		if (Cley2.Color == Bullet1.Color)
		{

			Cley2.BreakPosition = Cley2.Position; //壊れた場所を記録
			Cley2.Break = 1;//１が壊れた状態が=1ですよ
			CollisionDisplayStartTime = GetNowCount(); // 衝突が発生した時間を記録
			Cley2.IsMoving = false;
			Bullet1.IsMoving = false;
			Bullet1.Position = VGet(0, 0, 0);
			Cley2.Position = VGet(0, 0, 0);
			BreakCrey2 = true;
		
		}
		//PlaySoundMem(CollisionSoundHandle, DX_PLAYTYPE_BACK);
	}
}


//弾２とクレイ２の判定
if (Cley2.IsMoving && Bullet2.IsMoving && BreakCrey2 != true)
{
	if (CheckCapsuleCollision(frisbeeCapsule2, Bullet2.Position, BulletRadius))
	{

		if (Cley2.Color == Bullet2.Color)
		{

			Cley2.BreakPosition = Cley2.Position; //壊れた場所を記録
			Cley2.Break = 1;//１が壊れた状態が=1ですよ

			CollisionDisplayStartTime = GetNowCount(); // 衝突が発生した時間を記録
			Cley2.IsMoving = false;
			Bullet2.IsMoving = false;
			Bullet2.Position = VGet(0, 0, 0);
			Cley2.Position = VGet(0, 0, 0);
			BreakCrey2 = true;
		}
		//PlaySoundMem(CollisionSoundHandle, DX_PLAYTYPE_BACK);
	}
}







	if (Cley1.Break == 1) {
		Cley1.BreakMoveYgravity++;
		Cley1.BreakMoveX++;
		Cley1.BreakMoveY -= 30 - (2 * Cley1.BreakMoveYgravity);
	}//当たってからの壊れるアニメーション1

	if (Cley2.Break == 1) {
		Cley2.BreakMoveYgravity++;
		Cley2.BreakMoveX++;
		Cley2.BreakMoveY -= 30 - (2 * Cley2.BreakMoveYgravity);
	}//当たってからの壊れるアニメーション1
	


	kumoMove[1] += 1;
	kumoMove[0] += 1;

	if (kumoMove[0] > -620 && kumoMove[0] < -610) kumoMove[1] = -1920;
	if (kumoMove[1] > -200 && kumoMove[1] < -190) kumoMove[0] = -1770;






//---------------------------------------------------------------------------


	if (BreakCrey1 == true)Cley1.Position = VGet(0, 0, -10);	//クレイ1が破壊された場合、位置を(0, 0, -10)に固定し、高度が下がって得点がバグったり描画されたりしないようにする
	//if (BreakCrey2 == true)FrisbeePosition2 = VGet(0, 0, -10);	//クレイ２も同様

	//========================================================================================


	//デバッグ用のコード
	if (DebugMode == true)
	{

		


		if (KeyClick(KEY_INPUT_A) == true)
		{
			AtackScore++;
		}

		if (KeyClick(KEY_INPUT_D) == true)
		{
			DefenceScore++;
		}


		//if (FrisbeePosition1.y < -3000) FrisbeePosition1.y = -3000;


	}

	//else if (Cley1.Position.y < -3000 && Cley1.IsMoving == true) DefenceScore++;	//クレイが画面下に行ったとき防衛側に加点。

	//if (BreakCrey1 == true  && IsFrisbeeMoving1 == true)	AtackScore++;	//破壊されたときアタックに加点
	if (Cley1.BreakMoveX >  70 && Cley2.BreakMoveX > 70)	AtackScore++;//破壊されたときアタックに加点。

	if (Cley1.BreakMoveX > 70)
	{
		if (Cley2.Position.y < -3000 && Cley2.Break != true)	//クレイ１が破壊された状態で、クレイ２が画面外に沈んだ時、両者に0.5点
		{
			DefenceScore += 0.5f;
			AtackScore += 0.5f;
		}
	}
	else if (Cley2.BreakMoveX > 70)
	{
		if (Cley1.Position.y < -3000 && Cley1.IsMoving == true)	//クレイ２が破壊されたが、クレイ１が画面下に沈んだ時、両者に加点0.5
		{
			DefenceScore += 0.5f;
			AtackScore += 0.5f;
		}
	}

	if (Cley2.Break != true && Cley1.Break != true)	//両者ともに破壊されておらず、両者ともに画面下に沈んだ場合、防衛に1点加点
	{
		if (Cley2.Position.y < -3000 && Cley1.Position.y < -3000)
		{
			DefenceScore++;
		}

	}





	
	//if (BreakCrey1 == true  && BreakCrey2 == true)	AtackScore++;						//二つとも破壊されたときアタックに加点
	
	//if (BreakCrey1 = true && FrisbeePosition2.y < -3000)	DefenceScore++;				//クレイ１が破壊されたが、２が画面下に行ったため防衛に加点
	//if (BreakCrey2 = true && FrisbeePosition1.y < -3000)	DefenceScore++;				//クレイ2が破壊されたが、1が画面下に行ったため防衛に加点
	
	//if (FrisbeePosition1.y < -3000 && FrisbeePosition2.y < -3000)	DefenceScore++;		//クレイ２とクレイ１の両方が画面下に言ったため防衛に加点。


	
	//-------------------------------------------------
	//どちらかに点数が入った場合、防衛に画面遷移	(１点入る、もしくは0.5点入る。)

		if (AtackScore == AtScore_keep + 1 || AtackScore == AtScore_keep + 0.5f)
		{
			//if (Cley1.Break >= 1)
			//{
			battleRound++;
				if (solo == true) ChangeGameScene = SoloScene;
				else ChangeGameScene = DefScene;



				return;

			//}

		}

		if (DefenceScore == DfScore_keep + 1 || DefenceScore == DfScore_keep + 0.5f) 
		{
			battleRound++;
			if(solo == true)	ChangeGameScene = SoloScene;
			if (solo == false)				ChangeGameScene = DefScene;
			


			return;

		}
	


	
		//五点取得時にリザルトに遷移
			if (AtackScore >= WinScore || DefenceScore >= WinScore)
			{

				ChangeGameScene = ResultScene;

				return;
			}









	return;
}


//攻撃描画	
void AtackDraw(void)
{


	// 選択された背景画像の描画
	DrawGraph(0, 0, GraphData[181], true);
	DrawGraph(kumoMove[1] * 1.1, kumoMove[1], GraphData[182], true);
	DrawGraph(kumoMove[0] * 1.1, kumoMove[0], GraphData[182], true);

	DrawGraph(0, 0, GraphData[SelectedBackgroundIndex], true);

	//if (animeN + 78 <= 164) {
		animeN++;
	if(animeN <= 10)
		animeN2 += 20;
		if (animeN + 78 == 165)
			animeN = 1000;
	//}

	if (animeN >= 1030)
		animeN2 -= 20;

	DrawString(0, 480, "SPACEキー:クレイを飛ばす", GetColor(255, 255, 255));

	DrawGraph(0, -50, AnimData[animeN + 78], true);

	if (DebugMode == true)
	{
		SetUseLighting(FALSE);

		DrawFormatString(width - 200, 0, GetColor(255, 255, 255), "%s%s", GameSceneName[NowGameScene], "描画中");

		if (Bullet2.IsMoving == true) DrawFormatString(500, 500, GetColor(255, 255, 255), "%s%s", GameSceneName[NowGameScene], "Bullet2true");
		if (Bullet2.IsMoving != true) DrawFormatString(500, 500, GetColor(255, 255, 255), "%s%s", GameSceneName[NowGameScene], "Bullet2false");

		if (Bullet1.IsMoving == true) DrawFormatString(500, 800, GetColor(255, 255, 255), "%s%s", GameSceneName[NowGameScene], "Bullet1true");
		if (Bullet1.IsMoving != true) DrawFormatString(500, 800, GetColor(255, 255, 255), "%s%s", GameSceneName[NowGameScene], "Bullet1false");


		DrawFormatString(100, 100, GetColor(255, 255, 255), "攻撃の点数%f", AtackScore);
		DrawFormatString(100, 110, GetColor(255, 255, 255), "防衛の点数%f", DefenceScore);



		// 画面にパラメータを表示
		//DrawFormatString(0, 0, GetColor(255, 255, 255), "x:%.3f y:%.3f z:%.3f", Angle.x, Angle.y, Angle.z);
		//DrawString(0, 460, "Sキー:前進", GetColor(255, 255, 255));
		DrawFormatString(0, 700, GetColor(255, 255, 255), "shootco:%d", shootCo);



		DrawFormatString(0, 600, GetColor(255, 255, 255), "PosX:%f\nPosY:%f\nPosZ%n", Cley1.Position.x, Cley1.Position.y, Cley1.Position.z);

		// カプセルを描画
		DrawCapsule(frisbeeCapsule1, GetColor(255, 0, 0));
		DrawCapsule(frisbeeCapsule2, GetColor(255, 0, 0));

		//if(Cley2.Shooted == true)DrawFormatString(0, 500, GetColor(255, 0, 0), "クレイ１発射ぁaaaaaaaaaaaaaaaaaaaaaaaa！");


	// 衝突メッセージの表示
		if (CollisionDisplayStartTime != -1 && GetNowCount() - CollisionDisplayStartTime < 2000)
		{
			DrawFormatString(0, 500, GetColor(255, 0, 0), "衝突検出！");


		}
	}


	// ２ポリゴンの描画
		//DrawPolygon3D(Bullet1Vertex, 2, GraphData[173], TRUE);




		// 弾の描画
		if (Bullet1.Color == 1) DrawPolygon3D(Bullet1Vertex, 2, GraphData[173], TRUE);
		else if (Bullet1.Color == 2)DrawPolygon3D(Bullet1Vertex, 2, GraphData[174], true);

		if (Bullet2.Color == 1) DrawPolygon3D(Bullet2Vertex, 2, GraphData[173], TRUE);
		else if (Bullet2.Color == 2)DrawPolygon3D(Bullet2Vertex, 2, GraphData[174], true);


		//材質ごとの表示1
		if (Cley1.IsMoving)
		{
			//右赤クレー変化
			if (Cley1.Color == 2)
			{
				DrawExtendGraph(150 * 10, 150 * 10, 150 * 10, 150 * 10, GraphData[202], TRUE);
				if (hasyaL.zaisitu == true)DrawRotaGraph3D(Cley1.Position.x, Cley1.Position.y, Cley1.Position.z, 1.0, Cley1.Angle.x, GraphData[202 + SelectedBackgroundIndex], TRUE, FALSE);
				else 	DrawRotaGraph3D(Cley1.Position.x, Cley1.Position.y, Cley1.Position.z, 1.0, Cley1.Angle.x, GraphData[175], TRUE, FALSE);

			}

			//左青クレー変化
			if (Cley1.Color == 1)
			{
				if (hasyaL.zaisitu == true) DrawRotaGraph3D(Cley1.Position.x, Cley1.Position.y, Cley1.Position.z, 1.0, Cley1.Angle.x, GraphData[206 + SelectedBackgroundIndex], TRUE, FALSE);
				else    DrawRotaGraph3D(Cley1.Position.x, Cley1.Position.y, Cley1.Position.z, 1.0, Cley1.Angle.x, GraphData[176], TRUE, FALSE);
			}
		}

		//材質ごとの表示2
		if (Cley2.IsMoving)
		{
			//右赤クレー変化
			if (Cley2.Color == 2)
			{
				if (hasyaR.zaisitu == true)DrawRotaGraph3D(Cley2.Position.x, Cley2.Position.y, Cley2.Position.z, 1.0, Cley2.Angle.x, GraphData[202 + SelectedBackgroundIndex], TRUE, FALSE);
				else 	DrawRotaGraph3D(Cley2.Position.x, Cley2.Position.y, Cley2.Position.z, 1.0, Cley2.Angle.x, GraphData[175], TRUE, FALSE);

			}

			//左青クレー変化
			if (Cley2.Color == 1)
			{
				if (hasyaR.zaisitu == true) DrawRotaGraph3D(Cley2.Position.x, Cley2.Position.y, Cley2.Position.z, 1.0, Cley2.Angle.x, GraphData[206 + SelectedBackgroundIndex], TRUE, FALSE);
				else    DrawRotaGraph3D(Cley2.Position.x, Cley2.Position.y, Cley2.Position.z, 1.0, Cley2.Angle.x, GraphData[176], TRUE, FALSE);
			}
		}








		/*
		// フリスビーの描画
		if (Cley1.IsMoving)
		{
			if (Cley1.Color == 1)DrawRotaGraph3D(Cley1.Position.x, Cley1.Position.y, Cley1.Position.z, 1.0, Cley1.Angle.x, GraphData[176], TRUE, FALSE);
			if (Cley1.Color == 2)DrawRotaGraph3D(Cley1.Position.x, Cley1.Position.y, Cley1.Position.z, 1.0, Cley1.Angle.x, GraphData[175], TRUE, FALSE);
		}

		// フリスビーの描画
		if (Cley2.IsMoving)
		{
			if (Cley2.Color == 1)DrawRotaGraph3D(Cley2.Position.x, Cley2.Position.y, Cley2.Position.z, 1.0, Cley2.Angle.x, GraphData[176], TRUE, FALSE);
			if (Cley2.Color == 2)DrawRotaGraph3D(Cley2.Position.x, Cley2.Position.y, Cley2.Position.z, 1.0, Cley2.Angle.x, GraphData[175], TRUE, FALSE);
		}
		*/





		/*
		if (Cley1.Break == 1 && Cley1.Color == 2) {
			DrawRotaGraph3D(Cley1.BreakPosition.x + Cley1.BreakMoveX, Cley1.BreakPosition.y - Cley1.BreakMoveY, Cley1.BreakPosition.z, 1.0, Cley1.Angle.x, GraphData[177], TRUE, FALSE);
			DrawRotaGraph3D(Cley1.BreakPosition.x - Cley1.BreakMoveX, Cley1.BreakPosition.y - Cley1.BreakMoveY, Cley1.BreakPosition.z, 1.0, Cley1.Angle.x, GraphData[178], TRUE, FALSE);
		}
		if (Cley1.Break == 1 && Cley1.Color == 1) {
			DrawRotaGraph3D(Cley1.BreakPosition.x + Cley1.BreakMoveX, Cley1.BreakPosition.y - Cley1.BreakMoveY, Cley1.BreakPosition.z, 1.0, Cley1.Angle.x, GraphData[179], TRUE, FALSE);
			DrawRotaGraph3D(Cley1.BreakPosition.x - Cley1.BreakMoveX, Cley1.BreakPosition.y - Cley1.BreakMoveY, Cley1.BreakPosition.z, 1.0, Cley1.Angle.x, GraphData[180], TRUE, FALSE);
		}

		if (Cley2.Break == 1 && Cley2.Color == 2) {
			DrawRotaGraph3D(Cley2.BreakPosition.x + Cley2.BreakMoveX, Cley2.BreakPosition.y - Cley2.BreakMoveY, Cley2.BreakPosition.z, 1.0, Cley2.Angle.x, GraphData[177], TRUE, FALSE);
			DrawRotaGraph3D(Cley2.BreakPosition.x - Cley2.BreakMoveX, Cley2.BreakPosition.y - Cley2.BreakMoveY, Cley2.BreakPosition.z, 1.0, Cley2.Angle.x, GraphData[178], TRUE, FALSE);
		}
		if (Cley2.Break == 1 && Cley2.Color == 1) {
			DrawRotaGraph3D(Cley2.BreakPosition.x + Cley2.BreakMoveX, Cley2.BreakPosition.y - Cley2.BreakMoveY, Cley2.BreakPosition.z, 1.0, Cley2.Angle.x, GraphData[179], TRUE, FALSE);
			DrawRotaGraph3D(Cley2.BreakPosition.x - Cley2.BreakMoveX, Cley2.BreakPosition.y - Cley2.BreakMoveY, Cley2.BreakPosition.z, 1.0, Cley2.Angle.x, GraphData[180], TRUE, FALSE);
		}
		*/


		//ブレイク演出描画
		
		
		if (Cley1.Break == 1 && Cley1.Color == 2) {
			DrawRotaGraph3D(Cley1.BreakPosition.x + Cley1.BreakMoveX, Cley1.BreakPosition.y - Cley1.BreakMoveY, Cley1.BreakPosition.z, 1.0, Cley1.Angle.x, GraphData[177], TRUE, FALSE);
			DrawRotaGraph3D(Cley1.BreakPosition.x - Cley1.BreakMoveX, Cley1.BreakPosition.y - Cley1.BreakMoveY, Cley1.BreakPosition.z, 1.0, Cley1.Angle.x, GraphData[178], TRUE, FALSE);
		}
		if (Cley1.Break == 1 && Cley1.Color == 1) {
			DrawRotaGraph3D(Cley1.BreakPosition.x + Cley1.BreakMoveX, Cley1.BreakPosition.y - Cley1.BreakMoveY, Cley1.BreakPosition.z, 1.0, Cley1.Angle.x, GraphData[179], TRUE, FALSE);
			DrawRotaGraph3D(Cley1.BreakPosition.x - Cley1.BreakMoveX, Cley1.BreakPosition.y - Cley1.BreakMoveY, Cley1.BreakPosition.z, 1.0, Cley1.Angle.x, GraphData[180], TRUE, FALSE);
		}
		
		if (Cley2.Break == 1 && Cley2.Color == 2) {
			DrawRotaGraph3D(Cley2.BreakPosition.x + Cley2.BreakMoveX, Cley2.BreakPosition.y - Cley2.BreakMoveY, Cley2.BreakPosition.z, 1.0, Cley2.Angle.x, GraphData[177], TRUE, FALSE);
			DrawRotaGraph3D(Cley2.BreakPosition.x - Cley2.BreakMoveX, Cley2.BreakPosition.y - Cley2.BreakMoveY, Cley2.BreakPosition.z, 1.0, Cley2.Angle.x, GraphData[178], TRUE, FALSE);
		}
		if (Cley2.Break == 1 && Cley2.Color == 1) {
			DrawRotaGraph3D(Cley2.BreakPosition.x + Cley2.BreakMoveX, Cley2.BreakPosition.y - Cley2.BreakMoveY, Cley2.BreakPosition.z, 1.0, Cley2.Angle.x, GraphData[179], TRUE, FALSE);
			DrawRotaGraph3D(Cley2.BreakPosition.x - Cley2.BreakMoveX, Cley2.BreakPosition.y - Cley2.BreakMoveY, Cley2.BreakPosition.z, 1.0, Cley2.Angle.x, GraphData[180], TRUE, FALSE);
		}
		

		
		if (Cley1.BreakMoveX >= 1) {

			if (breakAnime1 <= 9)
				breakAnime1++;
			if (breakAnime1 + 182 >= 192) breakAnime1 = 10000;
			DrawRotaGraph3D(Cley1.BreakPosition.x, Cley1.BreakPosition.y, Cley1.BreakPosition.z, 1.0, Cley1.Angle.x, GraphData[breakAnime1 + 182], TRUE, FALSE);
		}
		
		if (Cley2.BreakMoveX >= 1) {

			if (breakAnime2 <= 9)
				breakAnime2++;
			if (breakAnime2 + 182 >= 192) breakAnime2 = 10000;
			DrawRotaGraph3D(Cley2.BreakPosition.x, Cley2.BreakPosition.y, Cley2.BreakPosition.z, 1.0, Cley2.Angle.x, GraphData[breakAnime2 + 182], TRUE, FALSE);
		}
		


		//scoreと
		
		SetDrawBlendMode(DX_BLENDMODE_MULA, 150);
		DrawExtendGraph(0 - 170, animeN2 - 100, 1920 * 6 / 5 - 170, 1080 * 6 / 5, GraphData[192], true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		DrawExtendGraph(0-170, animeN2-100, 1920 * 6 / 5 - 170, 1080 * 6 / 5, GraphData[193], true);
		

		DrawGraph(0, 0, GraphData[200], true);

		if (shootCo >= 1)	DrawGraph(0, 0, GraphData[201], true);
		if (shootCo == 2)	DrawGraph(100, 0, GraphData[201], true);




		SetFontSize(130);
		DrawFormatString(1060, animeN2+75-100, GetColor(255, 255, 255), "%.1lf", AtackScore);
		DrawFormatString(690, animeN2+75-100, GetColor(255, 255, 255), "%.1lf", DefenceScore);
		SetFontSize(50);
		DrawFormatString(1130, animeN2 + 15 - 100, GetColor(255, 255, 255), "%d", battleRound);
		SetFontSize(25);

		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

		// マウスカーソル位置に画像を描画
		DrawExtendGraph(mouseX - newWidth / 2, mouseY - newHeight / 2, mouseX + newWidth / 2, mouseY + newHeight / 2, GraphData[172], TRUE);


	return;
}


//リザルト初期化
void ResultInit(void)
{
	if (DebugMode == true)
	{
	
		DrawFormatString(width - 200, 0, GetColor(255, 255, 255), "%s%s", GameSceneName[ChangeGameScene], "初期化");
	
	
	}

	//すでに読み込んだサウンドを停止
	StopSoundMem(SoundData[8]);

	for (int i = 0; i < 201; i++) { DeleteGraph(GraphData[i]); }
	ResultTextureLoad();


		//音量設定
	ChangeVolumeSoundMem((255 * 20 / 100) / SoundVolume, SoundData[10]);

	//ループ位置の変更←これがないとプログラム動かん(´;ω;｀)
	SetLoopPosSoundMem(0, SoundData[10]);


	PlaySoundMem(SoundData[10], DX_PLAYTYPE_BACK, FALSE);



	debugGraph = 0;

	ResultState = 0;

	//シーン切り替え後の経過フレーム数を初期化
	GameSceneFrameCount[ChangeGameScene] = 0;

	LoadMovie = false;

	return;
}



//リザルト管理
void ResultCtrl(void)
{

	ResultProc();
	ResultDraw();


	return;
}



//リザルト処理
void ResultProc(void)
{

		//スペースキーが押されたとき

	GetMousePoint(&mouseX, &mouseY);

		//シーン初期化
		//TitleInit();


	if (SetUI(40, 872, 422, 872, 40, 1060, 422, 1060) == true && MousePush(MOUSE_INPUT_LEFT) == true)
	{//シーン切り替え
		ChangeGameScene = MainScene;


		LoadMovie = false;

		//すぐに切り替える
		return;
	}

	switch (shopAnime) {
	case 1:
	{
		UIanime[4] += 0.4;
		if (UIanime[4] > 20)
			shopAnime = 2;
		break;
	}
	case 2: {
		UIanime[4] -= 0.4;
		if (UIanime[4] < -20)
			shopAnime = 1;
		break;
	}
	}


	//AtScore = AtackScore - 1;
	//DfScore = DefenceScore - 1;

	return;
}




//リザルト描画
void ResultDraw(void)
{

	DrawGraph(0, 0, GraphData[3], true); //背景


	//攻撃が防衛よりも点が高くて、攻撃が勝利した場合
	if (AtackScore > DefenceScore && AtackScore >= WinScore)
	{
		if (solo == false) {
			DrawGraph(0, 0, GraphData[1], false); //背景 A Win
			DrawGraph(0, UIanime[4], GraphData[14], true); //背景 A Win
		}

		if (solo == true) {
			DrawGraph(0, 0, GraphData[8], false); //背景 A Win
			DrawGraph(0, UIanime[4], GraphData[13], true); //背景 A Win
		}

		for (int i = 0; i <= 4; i++)
		{
			DrawGraph(-40 + (i * 170), 0, GraphData[2], true); //チェックマーク表示
		}

		

		//for (int i = 0; i <= DfScore; i++)
		for (int i = 0; i <= DefenceScore - 1; i++)
		{
			DrawGraph(580 + (i * 170), 180, GraphData[2], true);
		}
		
		SetFontSize(100);
		DrawFormatString(1600, 780, GetColor(255, 255, 255), "%0.1lf", DefenceScore);

		SetFontSize(200);
		DrawFormatString(750, 480, GetColor(255, 255, 255), "%0.1lf", AtackScore);
		SetFontSize(15);
	}
	else if (DefenceScore > AtackScore && DefenceScore >= WinScore)	//防衛が攻撃よりも高く、防衛が勝利した場合。
	{
		if (solo == false) {
			DrawGraph(0, 0, GraphData[0], false); //背景 D Win
			DrawGraph(0, UIanime[4], GraphData[11], true); //背景 D Win
		}

		if (solo == true) {
			DrawGraph(0, 0, GraphData[7], false); //背景 D Win
			DrawGraph(0, UIanime[4], GraphData[12], true); //背景 D Win
		}

		for (int i = 0; i <= 4; i++)
		{
			DrawGraph(-40 + (i * 170), 0, GraphData[2], true);
		}

		//for (int i = 0; i <= AtScore; i++)
		for (int i = 0; i <= AtackScore - 1; i++)
		{
			DrawGraph(580 + (i * 170), 180, GraphData[2], true); //チェックマーク
		}

		SetFontSize(100);
		DrawFormatString(1600, 780, GetColor(255, 255, 255), "%0.1lf", AtackScore);

		SetFontSize(200);
		DrawFormatString(750, 480, GetColor(255, 255, 255), "%0.1lf", DefenceScore);
		SetFontSize(15);
	}

	else if (DefenceScore == AtackScore)
	{

		//ドロー時背景
		if (solo == false) DrawGraph(0, 0, GraphData[5], false); //背景 A Win
		if (solo == true) DrawGraph(0, 0, GraphData[9], false); //背景 A Win

		DrawGraph(0, UIanime[4], GraphData[10], true);

		SetFontSize(150);
		DrawFormatString(1370, 640, GetColor(255, 255, 255), "%0.1lf", AtackScore);
		DrawFormatString(560, 640, GetColor(255, 255, 255), "%0.1lf", DefenceScore);
		SetFontSize(15);
	}

	 
	DrawGraph(0-1350, 100,GraphData[4], true); //背景
	if (SetUI(40, 872, 422, 872, 40, 1060, 422, 1060)) {
		DrawGraph(0 - 1350, 100, GraphData[6], true); //背景
	}



	if (DebugMode == true)
	{
		DrawFormatString(width - 200, 0, GetColor(255, 255, 255), "%s%s", GameSceneName[NowGameScene], "描画中");

		DrawFormatString(100, 100, GetColor(0, 0, 0), "攻撃の点数%d", AtackScore);
		DrawFormatString(100, 110, GetColor(0, 0, 0), "防衛の点数%d", DefenceScore);


		DrawFormatString(100, 300, GetColor(0, 0, 0), "マウスのx%d", mouseX);
		DrawFormatString(100, 330, GetColor(0, 0, 0), "マウスのy%d", mouseY);

	}



	return;
}



