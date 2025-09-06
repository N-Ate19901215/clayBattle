//キー入力のソースファイル


#include "Keyboad.h"





//----------グローバル変数--------------------

//現在のキーを押しているフレーム数
int NowKeyPressFrame[KeyKindMax];

//ひとつ前のキーを押しているフレーム数
int OldKeyPressFrame[KeyKindMax];







//入力処理の初期化
void KeyInit(void)
{

	//配列の初期化
	for (int i = 0; i < KeyKindMax; i++)
	{
		NowKeyPressFrame[i] = 0;
		OldKeyPressFrame[i] = 0;
	}

	return;
}




//入力処理の更新
void KeyUpdate(void)
{
	//一時的に保持するキー情報
	char KeyState[KeyKindMax];

	//全てのキーの状態を一度に確認
	GetHitKeyStateAll(&KeyState[0]);

	//キー情報を更新
	for (int i = 0; i < KeyKindMax; i++)
	{

		//1つ前のキー情報の入力を保存
		OldKeyPressFrame[i] = NowKeyPressFrame[i];

		//現在キーが押されている時、押したフレーム数をカウント。
		if (KeyState[i] != 0)
		{
			NowKeyPressFrame[i]++;

		}
		else if (KeyState[i] == 0) //押されていないのなら、カウントを0に。
		{
			NowKeyPressFrame[i] = 0;
		}


	}

	return;
}


/*



押してる時何かしらの変数が大きくなってく。

何かしらの変数が別のところに１だったとき、押してる判定を出す。

それ以外の時にfalseを返す。


*/



//特定のキーを押したかどうか
bool KeyDown(int KEY_INPUT_)
{



	//引数の[KEY_INPUT_]はDXライブラリにマクロ定義されてる、各キーのコード

	//現在押されているキーのフレームカウントが0より大きかったら、「押している」と判断
	if (NowKeyPressFrame[KEY_INPUT_] > 0)
	{
		return true;
	}



	return false; //押していない
}







//特定のキーをクリックしたかどうか　(押したあと、指を離すまでの動作を検知するのを　クリックとする)
bool KeyClick(int KEY_INPUT_)
{

	if (NowKeyPressFrame[KEY_INPUT_] == 0 && OldKeyPressFrame[KEY_INPUT_] > 0)
	{
		return true;
	}

	return false;
}


//キーダウンを検知する...?
// 

bool KeyPush(int KEY_INPUT_)
{
	if (OldKeyPressFrame[KEY_INPUT_] == 0 && NowKeyPressFrame[KEY_INPUT_] > 0)
	{
		return true;
	}

	return false;

}



//　特定のキーを押したフレーム数
//　※返す値はフレーム数なので、使う際必要であればちゃんと変換すること。
int KeyPressFrame(int KEY_INPUT_)
{



	return NowKeyPressFrame[KEY_INPUT_];
}










