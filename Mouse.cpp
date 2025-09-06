#include "Mouse.h"
#include "Game.h"


//グローバル変数
MousePoint NowPoint;	//現在の位置
MousePoint OldPoint;	//ひとつ前の位置



int NowMousePressFrame[MouseKindMax];	//現在のボタンの押してるフレーム数を管理
int OldMousePressFrame[MouseKindMax];	//過去の牡丹の押してるフレーム数を管理



int MouseCodeIndex[MouseKindMax]
{
	MOUSE_INPUT_LEFT,
	MOUSE_INPUT_RIGHT,
	MOUSE_INPUT_MIDDLE
};


void MouseNowIntoOld(void)				//Nowﾅﾝﾁｬﾗ系の変数の値をOldﾅﾝﾁｬﾗ系の変数へ入れる
{

	OldPoint = NowPoint;

	for (int i = 0; i < MouseKindMax; i++)
	{
		OldMousePressFrame[i] = NowMousePressFrame[i];
	}



	return;
}


int MouseCodeToIndex(int MOUSE_INPUT_)  //マウスのぼたんこーどを配列の要素数に変換する
{


	for (int i = 0; i < MouseKindMax; i++)
	{
		if (MouseCodeIndex[i] == MOUSE_INPUT_)//マウスコードが紐づけされてるなら
		{
			return i;	//その要素数を返す
		}
	}

	
	//マウスコードが無ければエラー(999)
	return MouseErrorIndex;
}





void MouseInit(void)//まうす入力処理の初期化
{

	//マウス位置の初期化(現在と以前)
	NowPoint.x = 0;
	NowPoint.y = 0;

	//入力フレームの初期化
	for (int i = 0; i < MouseKindMax; i++)
	{
		NowMousePressFrame[i] = 0;	
	}



	
	//初期化したNowをOldにコピー(Old系も初期化)
	MouseNowIntoOld();	




	return;
}

void MouseUpdate(void)//マウス入力処理の更新
{
	//マウスの全てのボタンの情報を取得

	//現在の情報を以前の情報として保存。
	MouseNowIntoOld();


	//現在のクライアント座標を保存
	GetMousePoint(&NowPoint.x, &NowPoint.y);

	//もし、マウスポインターがゲームウィンドウの外にあるなら、座標をウィンドウの端の座標で保持。

	if (NowPoint.x < 0)//左
	{
		NowPoint.x = 0;
	} 
	else if (NowPoint.x > width) //右
	{
		NowPoint.x = width;
	}


	if (NowPoint.y < 0)//上
	{
		NowPoint.y = 0; 
	}
	else if (NowPoint.y < height)//下
	{
		NowPoint.y = height; 
	}


	int MouseInput;

	MouseInput = GetMouseInput();

	for (int i = 0; i < MouseKindMax; i++)
	{


		if ((MouseInput & MouseCodeIndex[i]) == MouseCodeIndex[i])
		{
			NowMousePressFrame[i]++;
		}
		else if ((MouseInput & MouseCodeIndex[i]) != MouseCodeIndex[i])
		{
			NowMousePressFrame[i] = 0;
		}


	}




	return;
}

bool MouseDown(int MOUSE_INPUT_)//特定のマウスボタンを押したか
{

	int index = MouseCodeToIndex(MOUSE_INPUT_);

	if (index != MouseErrorIndex)
	{
		if (NowMousePressFrame[index] > 0)
		{
			return true;
		}

	}


	return false;
}


 bool MousePush(int MOUSE_INPUT_)			//マウスボタンを押した瞬間の判定
{
	 int index = MouseCodeToIndex(MOUSE_INPUT_);

	 if (index != MouseErrorIndex)
	 {
		 if (NowMousePressFrame[index] > 0 && OldMousePressFrame[index] == 0)
		 {
			 return true;
		 }

	 }



	return false;
}

 bool MouseClick(int MOUSE_INPUT_)		//特定のマウスボタンをクリックしたか
{
	 int index = MouseCodeToIndex(MOUSE_INPUT_);

	 if (index != MouseErrorIndex)
	 {
		 if (NowMousePressFrame[index] == 0 && OldMousePressFrame[index] > 0)
		 {
			 return true;
		 }

	 }


	return false;
}

 int  MousePressFrame(int MOUSE_INPUT_)	//特定のボタンを押したフレーム数
{
	return NowMousePressFrame[MOUSE_INPUT_];
}



 //現在のポインター座標を取得
MousePoint NowMousePos(void)
{
	return NowPoint;
}

//以前のポインター座標を取得
MousePoint OldMousePos(void)
{
	return OldPoint;
}

MousePoint DifMousePos(void)
{	
	MousePoint dif;

	dif.x = NowPoint.x - OldPoint.x;
	dif.y = NowPoint.y - OldPoint.y;

	return dif;
}

