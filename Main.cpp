#include "DxLib.h"
#include "Fps.h"
#include "Game.h"
#include "Keyboad.h"
#include "Mouse.h"
#include "LoadSorce.h"









int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{



	ChangeWindowMode(true);  //ウィンドウ表示モード

	SetGraphMode(width, height, bit);	//解像度指定

	SetWindowSize(width, height);  //ウィンドウサイズ

	SetMainWindowText("CreyShooting");   //ウィンドウ名(ゲーム名)

	//SetBackgroundColor(0, 0, 0);

	SetWaitVSyncFlag(GameVsync);

	//SetAlwaysRunFlag(true);




	//-------------------------------初期化-------------------------------------------------


	//DXライブラリの初期化
	if (DxLib_Init() == -1) return -1;

	//裏画面に描画する(ダブルバッファリング用)
	SetDrawScreen(DX_SCREEN_BACK);


	//FPSの初期化
	FPSInit();




	

	//タイトルの初期化
	TitleInit();

	//最初に読み込まれるシーン(タイトル)
	NowGameScene = TitleScene;

	ChangeGameScene = TitleScene;



	//キー入力の初期化
	KeyInit();

	//マウス入力の初期化
	MouseInit();


	AnimDataLoad();
	SoundLoad();


	//----------------------------------------------------------------------------------------





	//ゲームループ
	while (true)
	{



		//メッセージ処理
		if (ProcessMessage() != 0)
		{
			break;
		}//無限ループから抜け出す(ゲーム終了)




		//ESCを押したとき、強制終了
		if (KeyClick(KEY_INPUT_ESCAPE) == true)
		{
			break;
		}
	
	


		//画面をクリアする
		if (ClearDrawScreen() != 0)
		{

			break;
		}


		//ゲーム内動作
		{


			//fps計測
			FPSCheck();

			//キー処理の更新
			KeyUpdate();

			//マウス処理の更新
			MouseUpdate();





			//次のシーンを初期化
			if (NowGameScene != ChangeGameScene)
			{

				switch (ChangeGameScene)
				{
				case TitleScene:
					TitleInit();
					break;

				case MainScene:
					MainInit();
					break;

				case ShopScene:
					ShopInit();
					break;

				case AtackScene:
					AtackInit();
					break;

				case DefScene:
					DefInit();
					break;

				case SoloScene:
					SoloInit();
					break;

				case ResultScene:
					ResultInit();
					break;

				case OptionScene:
					OptionInit();
					break;

				case TutorialScene:
					TutorialInit();
					break;

				
				default:
					break;
				}

				//シーン切り替え後のシーンを現在のシーンにする
				NowGameScene = ChangeGameScene;


			}


			//シーン切り替え
			switch (NowGameScene)
			{
			case TitleScene:
				TitleCtrl();
				break;

			case MainScene:
				MainCtrl();
				break;


			case ShopScene:
				ShopCtrl();
				break;


			case AtackScene:
				AtackCtrl();
				break;

			case DefScene:
				DefCtrl();
				break;

			
			case ResultScene:
				ResultCtrl();
				break;

			case SoloScene:
				SoloCtrl();
				break;

			case OptionScene:
				OptionCtrl();
				break;

			case TutorialScene:
				TutorialCtrl();
				break;
			
			
			default:
				break;
			}



			//fps表示
			FPSDraw();




			//fps待機
			FPSWait();



		}


		ScreenFlip();
		
	
	
	
	}










	//アプリケーション終了時に、メモリーに格納された画像と音の全てのデータを解放する
	Releace();


	//終了
	DxLib_End();






	return 0;
}