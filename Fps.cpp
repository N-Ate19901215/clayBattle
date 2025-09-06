//FPS処理のファイル

#include "Fps.h"



//グローバル変数
FPS fps;





//初期化
void FPSInit(void)
{


	//Windowsが起動してから現在までの時間を得る(マイクロ秒)
	fps.FirstTakeTime = GetNowHiPerformanceCount();

	//他の値も初期化
	fps.NowTakeTime = fps.FirstTakeTime;
	fps.OldTakeTime = fps.FirstTakeTime;
	fps.deltaTime = 0.000001f;
	fps.FrameCount = 1;
	fps.Average = 0.0f;

	return;

}




void FPSCheck(void)
{

	//現在の時刻を取得
	fps.NowTakeTime = GetNowHiPerformanceCount();


	//経過時間を計算
	fps.deltaTime = (fps.NowTakeTime - fps.OldTakeTime) / MicroSecond;


	//現在の時刻を保存
	fps.OldTakeTime = fps.NowTakeTime;

	//現在が最大フレーム目なら
	if (fps.FrameCount == GameFPS)
	{


		//1フレーム目～最大フレーム目までのかかった合計時間を計算。
		float TotalTakeTime = fps.NowTakeTime - fps.FirstTakeTime;


		//合計時間を理想のFPS値で和って平均値を計算
		float CalcAverage = TotalTakeTime / GameFPS;

		//1秒あたりのフレーム数に変換
		fps.Average = MicroSecond / CalcAverage;


		//1フレーム目の時刻を取得
		fps.FirstTakeTime = GetNowHiPerformanceCount();

		//1フレーム目を1に戻す
		fps.FrameCount = 1;


	}
	else
	{
		fps.FrameCount++;
	}




	return;
}




//描画
void FPSDraw(void)
{
	DrawFormatString(0, 0, GetColor(255, 255, 255), "FPS:%3.1f", fps.Average);

	return;

}


//待機
void FPSWait(void)
{

	int wait = 0;

	//待ち時間を計測
	wait = MicroSecond / GameFPS * fps.FrameCount 
		   - (fps.NowTakeTime - fps.FirstTakeTime);  //理想の時間 - 実際の時間


	//マイクロ秒をミリ秒に変換
	wait /= MillSecond;

	//もし待ち時間があるなら
	if (wait > 0 && wait <= WaitTimeMill)
	{


		//「めっせーじ」を処理しながら待つ
		WaitTimer(wait);

	}


	return;
}

