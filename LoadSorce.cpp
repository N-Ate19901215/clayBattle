#include "LoadSorce.h"

/*
今までgame.cppに直接書いていた読み込みの処理を、
恐らくほぼ全てこちらに移動させました。

GraphHandle[]の要素数を変更したい場合には、
LoadSorce.hのマクロ定義「#define TextureNo」の値を変更してください。
※それ以外は基本的に変わっていません。

また「BulletHandle」のように別でHandleを用意したい場合は、
LoadSorce.hに「extern int (変数名);」と書いた後、
cppファイルに変数宣言を行ってください。


なお、サウンドの方も画像と同様です。
サウンドに関しては、共有した7/5時点ではまだ何も登録しておらず、
各初期化関数にもまだ組み込んでいないため注意してください。



最後に、各自コメントアウトを使用して、追加した機能や変数の簡単な説明や、追加項目をわかりやすく強調したりするなどお願いします。
今回α版見せるためだけにドッキング作業を行ったのですが、「ﾅﾆｺﾚ」と事あるごとにショートしそうになりました。
(※こんなの毎回やってたら、港登大先生がそのうち禿げます)
なんで、そこんとこよろしくお願いします。僕も気を付けます。特に変数宣言の位置とか....。
																
																		7/5 比嘉 
追記1---

ドッキング作業をしてくださる方へ
LoadScore.cppの行301に追加したサウンドロード部分が記載されております。
詳しくはそちらへどうぞ
																		7/5 實原
*/


int GraphData[TextureNo];
int AnimData[TextureNo];


int SoundData[SoundNo];


//アニメーションデータの読み込み
// Main.cppのゲームループ前に記述しているため、
//アプリケーション起動時に1度だけ読み込まれる。
void AnimDataLoad()
{
	//防衛ターンアニメーション読み込み
	AnimData[11] = LoadGraph("GraphData\\main\\defTurn (1).png");
	AnimData[12] = LoadGraph("GraphData\\main\\defTurn (2).png");
	AnimData[13] = LoadGraph("GraphData\\main\\defTurn (3).png");
	AnimData[14] = LoadGraph("GraphData\\main\\defTurn (4).png");
	AnimData[15] = LoadGraph("GraphData\\main\\defTurn (5).png");
	AnimData[16] = LoadGraph("GraphData\\main\\defTurn (6).png");
	AnimData[17] = LoadGraph("GraphData\\main\\defTurn (7).png");
	AnimData[18] = LoadGraph("GraphData\\main\\defTurn (8).png");
	AnimData[19] = LoadGraph("GraphData\\main\\defTurn (9).png");
	AnimData[20] = LoadGraph("GraphData\\main\\defTurn (10).png");
	AnimData[21] = LoadGraph("GraphData\\main\\defTurn (11).png");
	AnimData[22] = LoadGraph("GraphData\\main\\defTurn (12).png");
	AnimData[23] = LoadGraph("GraphData\\main\\defTurn (13).png");
	AnimData[24] = LoadGraph("GraphData\\main\\defTurn (14).png");
	AnimData[25] = LoadGraph("GraphData\\main\\defTurn (15).png");
	AnimData[26] = LoadGraph("GraphData\\main\\defTurn (16).png");
	AnimData[27] = LoadGraph("GraphData\\main\\defTurn (17).png");
	AnimData[28] = LoadGraph("GraphData\\main\\defTurn (18).png");
	AnimData[29] = LoadGraph("GraphData\\main\\defTurn (19).png");
	AnimData[30] = LoadGraph("GraphData\\main\\defTurn (20).png");
	AnimData[31] = LoadGraph("GraphData\\main\\defTurn (21).png");
	AnimData[32] = LoadGraph("GraphData\\main\\defTurn (22).png");
	AnimData[33] = LoadGraph("GraphData\\main\\defTurn (23).png");
	AnimData[34] = LoadGraph("GraphData\\main\\defTurn (24).png");
	AnimData[35] = LoadGraph("GraphData\\main\\defTurn (25).png");
	AnimData[36] = LoadGraph("GraphData\\main\\defTurn (26).png");
	AnimData[37] = LoadGraph("GraphData\\main\\defTurn (27).png");
	AnimData[38] = LoadGraph("GraphData\\main\\defTurn (28).png");
	AnimData[39] = LoadGraph("GraphData\\main\\defTurn (29).png");
	AnimData[40] = LoadGraph("GraphData\\main\\defTurn (30).png");
	AnimData[41] = LoadGraph("GraphData\\main\\defTurn (31).png");
	AnimData[42] = LoadGraph("GraphData\\main\\defTurn (32).png");
	AnimData[43] = LoadGraph("GraphData\\main\\defTurn (33).png");
	AnimData[44] = LoadGraph("GraphData\\main\\defTurn (34).png");
	AnimData[45] = LoadGraph("GraphData\\main\\defTurn (35).png");
	AnimData[46] = LoadGraph("GraphData\\main\\defTurn (36).png");
	AnimData[47] = LoadGraph("GraphData\\main\\defTurn (37).png");
	AnimData[48] = LoadGraph("GraphData\\main\\defTurn (38).png");
	AnimData[49] = LoadGraph("GraphData\\main\\defTurn (39).png");
	AnimData[50] = LoadGraph("GraphData\\main\\defTurn (40).png");
	AnimData[51] = LoadGraph("GraphData\\main\\defTurn (41).png");
	AnimData[52] = LoadGraph("GraphData\\main\\defTurn (42).png");
	AnimData[53] = LoadGraph("GraphData\\main\\defTurn (43).png");
	AnimData[54] = LoadGraph("GraphData\\main\\defTurn (44).png");
	AnimData[55] = LoadGraph("GraphData\\main\\defTurn (45).png");
	AnimData[56] = LoadGraph("GraphData\\main\\defTurn (46).png");
	AnimData[57] = LoadGraph("GraphData\\main\\defTurn (47).png");
	AnimData[58] = LoadGraph("GraphData\\main\\defTurn (48).png");
	AnimData[59] = LoadGraph("GraphData\\main\\defTurn (49).png");
	AnimData[60] = LoadGraph("GraphData\\main\\defTurn (50).png");
	AnimData[61] = LoadGraph("GraphData\\main\\defTurn (51).png");
	AnimData[62] = LoadGraph("GraphData\\main\\defTurn (52).png");
	AnimData[63] = LoadGraph("GraphData\\main\\defTurn (53).png");
	AnimData[64] = LoadGraph("GraphData\\main\\defTurn (54).png");
	AnimData[65] = LoadGraph("GraphData\\main\\defTurn (55).png");
	AnimData[66] = LoadGraph("GraphData\\main\\defTurn (56).png");
	AnimData[67] = LoadGraph("GraphData\\main\\defTurn (57).png");
	AnimData[68] = LoadGraph("GraphData\\main\\defTurn (58).png");
	AnimData[69] = LoadGraph("GraphData\\main\\defTurn (59).png");
	AnimData[70] = LoadGraph("GraphData\\main\\defTurn (60).png");
	AnimData[71] = LoadGraph("GraphData\\main\\defTurn (61).png");
	AnimData[72] = LoadGraph("GraphData\\main\\defTurn (62).png");
	AnimData[73] = LoadGraph("GraphData\\main\\defTurn (63).png");
	AnimData[74] = LoadGraph("GraphData\\main\\defTurn (64).png");
	AnimData[75] = LoadGraph("GraphData\\main\\defTurn (65).png");
	AnimData[76] = LoadGraph("GraphData\\main\\defTurn (66).png");
	AnimData[77] = LoadGraph("GraphData\\main\\defTurn (67).png");
	AnimData[78] = LoadGraph("GraphData\\main\\defTurn (68).png");
	AnimData[79] = LoadGraph("GraphData\\main\\defTurn (69).png");
	AnimData[80] = LoadGraph("GraphData\\main\\defTurn (70).png");
	AnimData[81] = LoadGraph("GraphData\\main\\defTurn (71).png");
	AnimData[82] = LoadGraph("GraphData\\main\\defTurn (72).png");
	AnimData[83] = LoadGraph("GraphData\\main\\defTurn (73).png");
	AnimData[84] = LoadGraph("GraphData\\main\\defTurn (74).png");
	AnimData[85] = LoadGraph("GraphData\\main\\defTurn (75).png");
	AnimData[86] = LoadGraph("GraphData\\main\\defTurn (76).png");
	AnimData[87] = LoadGraph("GraphData\\main\\defTurn (77).png");



	//攻撃ターンアニメーション読み込み
	AnimData[88] = LoadGraph("GraphData\\atkTrunAnime\\atkTrun (1).png");
	AnimData[89] = LoadGraph("GraphData\\atkTrunAnime\\atkTrun (2).png");

	AnimData[90] = LoadGraph("GraphData\\atkTrunAnime\\atkTrun (3).png");
	AnimData[91] = LoadGraph("GraphData\\atkTrunAnime\\atkTrun (4).png");
	AnimData[92] = LoadGraph("GraphData\\atkTrunAnime\\atkTrun (5).png");
	AnimData[93] = LoadGraph("GraphData\\atkTrunAnime\\atkTrun (6).png");
	AnimData[94] = LoadGraph("GraphData\\atkTrunAnime\\atkTrun (7).png");
	AnimData[95] = LoadGraph("GraphData\\atkTrunAnime\\atkTrun (8).png");
	AnimData[96] = LoadGraph("GraphData\\atkTrunAnime\\atkTrun (9).png");
	AnimData[97] = LoadGraph("GraphData\\atkTrunAnime\\atkTrun (10).png");
	AnimData[98] = LoadGraph("GraphData\\atkTrunAnime\\atkTrun (11).png");
	AnimData[99] = LoadGraph("GraphData\\atkTrunAnime\\atkTrun (12).png");

	AnimData[100] = LoadGraph("GraphData\\atkTrunAnime\\atkTrun (13).png");
	AnimData[101] = LoadGraph("GraphData\\atkTrunAnime\\atkTrun (14).png");
	AnimData[102] = LoadGraph("GraphData\\atkTrunAnime\\atkTrun (15).png");
	AnimData[103] = LoadGraph("GraphData\\atkTrunAnime\\atkTrun (16).png");
	AnimData[104] = LoadGraph("GraphData\\atkTrunAnime\\atkTrun (17).png");
	AnimData[105] = LoadGraph("GraphData\\atkTrunAnime\\atkTrun (18).png");
	AnimData[106] = LoadGraph("GraphData\\atkTrunAnime\\atkTrun (19).png");
	AnimData[107] = LoadGraph("GraphData\\atkTrunAnime\\atkTrun (20).png");
	AnimData[108] = LoadGraph("GraphData\\atkTrunAnime\\atkTrun (21).png");
	AnimData[109] = LoadGraph("GraphData\\atkTrunAnime\\atkTrun (22).png");

	AnimData[110] = LoadGraph("GraphData\\atkTrunAnime\\atkTrun (23).png");
	AnimData[111] = LoadGraph("GraphData\\atkTrunAnime\\atkTrun (24).png");
	AnimData[112] = LoadGraph("GraphData\\atkTrunAnime\\atkTrun (25).png");
	AnimData[113] = LoadGraph("GraphData\\atkTrunAnime\\atkTrun (26).png");
	AnimData[114] = LoadGraph("GraphData\\atkTrunAnime\\atkTrun (27).png");
	AnimData[115] = LoadGraph("GraphData\\atkTrunAnime\\atkTrun (28).png");
	AnimData[116] = LoadGraph("GraphData\\atkTrunAnime\\atkTrun (29).png");
	AnimData[117] = LoadGraph("GraphData\\atkTrunAnime\\atkTrun (30).png");
	AnimData[118] = LoadGraph("GraphData\\atkTrunAnime\\atkTrun (31).png");
	AnimData[119] = LoadGraph("GraphData\\atkTrunAnime\\atkTrun (32).png");

	AnimData[120] = LoadGraph("GraphData\\atkTrunAnime\\atkTrun (33).png");
	AnimData[121] = LoadGraph("GraphData\\atkTrunAnime\\atkTrun (34).png");
	AnimData[122] = LoadGraph("GraphData\\atkTrunAnime\\atkTrun (35).png");
	AnimData[123] = LoadGraph("GraphData\\atkTrunAnime\\atkTrun (36).png");
	AnimData[124] = LoadGraph("GraphData\\atkTrunAnime\\atkTrun (37).png");
	AnimData[125] = LoadGraph("GraphData\\atkTrunAnime\\atkTrun (38).png");
	AnimData[126] = LoadGraph("GraphData\\atkTrunAnime\\atkTrun (39).png");
	AnimData[127] = LoadGraph("GraphData\\atkTrunAnime\\atkTrun (40).png");
	AnimData[128] = LoadGraph("GraphData\\atkTrunAnime\\atkTrun (41).png");
	AnimData[129] = LoadGraph("GraphData\\atkTrunAnime\\atkTrun (42).png");

	AnimData[130] = LoadGraph("GraphData\\atkTrunAnime\\atkTrun (43).png");
	AnimData[131] = LoadGraph("GraphData\\atkTrunAnime\\atkTrun (44).png");
	AnimData[132] = LoadGraph("GraphData\\atkTrunAnime\\atkTrun (45).png");
	AnimData[133] = LoadGraph("GraphData\\atkTrunAnime\\atkTrun (46).png");
	AnimData[134] = LoadGraph("GraphData\\atkTrunAnime\\atkTrun (47).png");
	AnimData[135] = LoadGraph("GraphData\\atkTrunAnime\\atkTrun (48).png");
	AnimData[136] = LoadGraph("GraphData\\atkTrunAnime\\atkTrun (49).png");
	AnimData[137] = LoadGraph("GraphData\\atkTrunAnime\\atkTrun (50).png");
	AnimData[138] = LoadGraph("GraphData\\atkTrunAnime\\atkTrun (51).png");
	AnimData[139] = LoadGraph("GraphData\\atkTrunAnime\\atkTrun (52).png");

	AnimData[140] = LoadGraph("GraphData\\atkTrunAnime\\atkTrun (53).png");
	AnimData[141] = LoadGraph("GraphData\\atkTrunAnime\\atkTrun (54).png");
	AnimData[142] = LoadGraph("GraphData\\atkTrunAnime\\atkTrun (55).png");
	AnimData[143] = LoadGraph("GraphData\\atkTrunAnime\\atkTrun (56).png");
	AnimData[144] = LoadGraph("GraphData\\atkTrunAnime\\atkTrun (57).png");
	AnimData[145] = LoadGraph("GraphData\\atkTrunAnime\\atkTrun (58).png");
	AnimData[146] = LoadGraph("GraphData\\atkTrunAnime\\atkTrun (59).png");
	AnimData[147] = LoadGraph("GraphData\\atkTrunAnime\\atkTrun (60).png");
	AnimData[148] = LoadGraph("GraphData\\atkTrunAnime\\atkTrun (61).png");
	AnimData[149] = LoadGraph("GraphData\\atkTrunAnime\\atkTrun (62).png");

	AnimData[150] = LoadGraph("GraphData\\atkTrunAnime\\atkTrun (63).png");
	AnimData[151] = LoadGraph("GraphData\\atkTrunAnime\\atkTrun (64).png");
	AnimData[152] = LoadGraph("GraphData\\atkTrunAnime\\atkTrun (65).png");
	AnimData[153] = LoadGraph("GraphData\\atkTrunAnime\\atkTrun (66).png");
	AnimData[154] = LoadGraph("GraphData\\atkTrunAnime\\atkTrun (67).png");
	AnimData[155] = LoadGraph("GraphData\\atkTrunAnime\\atkTrun (68).png");
	AnimData[156] = LoadGraph("GraphData\\atkTrunAnime\\atkTrun (69).png");
	AnimData[157] = LoadGraph("GraphData\\atkTrunAnime\\atkTrun (70).png");
	AnimData[158] = LoadGraph("GraphData\\atkTrunAnime\\atkTrun (71).png");
	AnimData[159] = LoadGraph("GraphData\\atkTrunAnime\\atkTrun (72).png");

	AnimData[160] = LoadGraph("GraphData\\atkTrunAnime\\atkTrun (73).png");
	AnimData[161] = LoadGraph("GraphData\\atkTrunAnime\\atkTrun (74).png");
	AnimData[162] = LoadGraph("GraphData\\atkTrunAnime\\atkTrun (75).png");
	AnimData[163] = LoadGraph("GraphData\\atkTrunAnime\\atkTrun (76).png");
	AnimData[164] = LoadGraph("GraphData\\atkTrunAnime\\atkTrun (77).png");

	return;
}


void TitleTextureLoad()
{
	//----------------------------追加場所------------------
	GraphData[0] = LoadGraph("GraphData\\title.png");
	GraphData[0] = LoadGraph("GraphData\\kusakusa.PNG");//草原
	GraphData[1] = LoadGraph("GraphData\\ice.PNG");//氷山
	GraphData[2] = LoadGraph("GraphData\\dezart.png");//砂漠
	GraphData[3] = LoadGraph("GraphData\\hall.png");//洞窟


	GraphData[4] = LoadGraph("GraphData\\titleLogo.png");

	GraphData[5] = LoadGraph("GraphData\\sky.png");   //空
	GraphData[6] = LoadGraph("GraphData\\kumo.png");   //雲

	GraphData[7] = LoadGraph("GraphData\\titleAo.png");  
	GraphData[8] = LoadGraph("GraphData\\titleAka.png");  

	return;
}


void HomeTextureLoad()
{

	GraphData[0] = LoadGraph("GraphData\\home.png");
	GraphData[1] = LoadGraph("GraphData\\UI_Finish.png");
	GraphData[2] = LoadGraph("GraphData\\UI_Option.png");
	GraphData[3] = LoadGraph("GraphData\\UI_Shop.png");
	GraphData[4] = LoadGraph("GraphData\\UI_Title.png");
	GraphData[5] = LoadGraph("GraphData\\UI_Tutorial.png");
	GraphData[6] = LoadGraph("Graphdata\\battle.png");//バトルUI
	GraphData[7] = LoadGraph("Graphdata\\UI_battleSelectH.png");//バトル選択時
	GraphData[9] = LoadGraph("GraphData\\UI_finishSelectH.png");
	GraphData[10] = LoadGraph("GraphData\\UI_optionSelectH.png");
	GraphData[11] = LoadGraph("GraphData\\UI_shopSelectH.png");
	GraphData[12] = LoadGraph("GraphData\\UI_titleSelectH.png");
	GraphData[13] = LoadGraph("GraphData\\UI_tutorialSelectH.png");
	GraphData[14] = LoadGraph("GraphData\\UI_battleReady.png");
	GraphData[15] = LoadGraph("GraphData\\homeBack.png");
	GraphData[16] = LoadGraph("GraphData\\mode_back.png");
	GraphData[17] = LoadGraph("GraphData\\mode_jouzan.png");
	GraphData[18] = LoadGraph("GraphData\\mode_Text.png");
	GraphData[19] = LoadGraph("GraphData\\mode_SelectL.png");
	GraphData[20] = LoadGraph("GraphData\\mode_SelectR.png");
	GraphData[21] = LoadGraph("GraphData\\black.png");
	GraphData[22] = LoadGraph("GraphData\\result\\ReturnLight.png");
	GraphData[23] = LoadGraph("GraphData\\result\\ReturnDark.png");

	return;
}

void ShopTextureLoad()
{

	GraphData[0] = LoadGraph("GraphData\\home.png");
	GraphData[1] = LoadGraph("GraphData\\Shop01.png");
	GraphData[2] = LoadGraph("GraphData\\Shop02.png");
	GraphData[3] = LoadGraph("GraphData\\Shop03.png");
	GraphData[4] = LoadGraph("GraphData\\Shop04.png");
	GraphData[5] = LoadGraph("GraphData\\Shop05.png");
	GraphData[6] = LoadGraph("GraphData\\shopGunSelect.png");
	GraphData[7] = LoadGraph("GraphData\\Shop07.png");
	GraphData[8] = LoadGraph("GraphData\\Shop07Select.png");
	GraphData[9] = LoadGraph("GraphData\\homeBack.png");

	return;
}


void OptionTextureLoad()
{

	GraphData[0] = LoadGraph("GraphData\\Option\\optionDesu.PNG");
	GraphData[1] = LoadGraph("GraphData\\Option\\Option_Bar.PNG");
	GraphData[2] = LoadGraph("GraphData\\Option\\Option_circle.PNG");
	GraphData[3] = LoadGraph("GraphData\\home.png");
	GraphData[4] = LoadGraph("GraphData\\homeBack.png");
	GraphData[6] = LoadGraph("GraphData\\Result\\returnDark.PNG");
	GraphData[7] = LoadGraph("GraphData\\Result\\returnLight.PNG");

}


void BattleTextureLoad()
{

	GraphData[0] = LoadGraph("GraphData\\kusakusa.PNG");//草原
	GraphData[1] = LoadGraph("GraphData\\ice.PNG");//氷山
	GraphData[2] = LoadGraph("GraphData\\dezart.png");//砂漠
	GraphData[3] = LoadGraph("GraphData\\hall.png");//洞窟
	GraphData[4] = LoadGraph("GraphData\\hasyaLRed.png");//発射台左　赤
	GraphData[5] = LoadGraph("GraphData\\hasyaRRed.png");//発射台右　赤
	GraphData[6] = LoadGraph("GraphData\\pc.PNG");//ｐｃ
	GraphData[7] = LoadGraph("GraphData\\madoL.png");//左選択時ウィンドウ
	GraphData[8] = LoadGraph("GraphData\\madoSub.png");//サブウィンドウ
	GraphData[9] = LoadGraph("GraphData\\madoR.png");//右選択時ウィンドウ
	





	//発射台赤青、選択時画像読み込み
	GraphData[165] = LoadGraph("GraphData\\hasyaLRedSelect.png");//発射台　左　赤　選択時
	GraphData[166] = LoadGraph("GraphData\\readySelect.png");
	GraphData[167] = LoadGraph("GraphData\\hasyaRRedSelect.png");//発射台　右　赤　選択時
	GraphData[168] = LoadGraph("GraphData\\hasyaLBlue.png");//発射台　左　青
	GraphData[169] = LoadGraph("GraphData\\hasyaRBlue.png");//発射台　右　青
	GraphData[170] = LoadGraph("GraphData\\hasyaLBlueSelect.png");//発射台　左　青　選択時
	GraphData[171] = LoadGraph("GraphData\\hasyaRBlueSelect.png");//発射台　左　青　選択時


	GraphData[172] = LoadGraph("GraphData\\CrossHair.png");		//クロスヘア
	GraphData[173] = LoadGraph("GraphData\\BlueBullet.png");		//青色の弾
	GraphData[174] = LoadGraph("GraphData\\RedBullet.png");		//赤色の弾
	GraphData[175] = LoadGraph("GraphData\\RedCrey.png");		//クレイ用画像	赤
	GraphData[176] = LoadGraph("GraphData\\BlueCrey.png");		//クレイ用画像	青
	GraphData[177] = LoadGraph("GraphData\\RedBreakR.png");     //赤壊れたクレー右
	GraphData[178] = LoadGraph("GraphData\\RedBreakL.png");		//赤クレー壊れた左
	GraphData[179] = LoadGraph("GraphData\\BlueBreakR.png");	//蒼クレー壊れた右
	GraphData[180] = LoadGraph("GraphData\\BlueBreakL.png");	//蒼クレー壊れた左

	GraphData[181] = LoadGraph("GraphData\\sky.png");   //空
	GraphData[182] = LoadGraph("GraphData\\kumo.png");   //雲

	GraphData[183] = LoadGraph("GraphData\\breakAnime\\break (1).png");
	GraphData[184] = LoadGraph("GraphData\\breakAnime\\break (2).png");
	GraphData[185] = LoadGraph("GraphData\\breakAnime\\break (3).png");
	GraphData[186] = LoadGraph("GraphData\\breakAnime\\break (4).png");
	GraphData[187] = LoadGraph("GraphData\\breakAnime\\break (5).png");
	GraphData[188] = LoadGraph("GraphData\\breakAnime\\break (6).png");
	GraphData[189] = LoadGraph("GraphData\\breakAnime\\break (7).png");
	GraphData[190] = LoadGraph("GraphData\\breakAnime\\break (8).png");
	GraphData[191] = LoadGraph("GraphData\\breakAnime\\break (9).png");

	GraphData[192] = LoadGraph("GraphData\\battleBlack.png");
	GraphData[193] = LoadGraph("GraphData\\battleUIVS.png");

	GraphData[194] = LoadGraph("GraphData\\battleUIVSAlpha.png");
	GraphData[195] = LoadGraph("GraphData\\battleBlackAlpha.png");

	GraphData[196] = LoadGraph("GraphData\\battleBlack2.png");
	GraphData[197] = LoadGraph("GraphData\\battleUIVS2.png");

	GraphData[198] = LoadGraph("GraphData\\battleUIVSAlpha2.png");
	GraphData[199] = LoadGraph("GraphData\\battleBlackAlpha2.png");
	GraphData[200] = LoadGraph("GraphData\\AtkUI.png");
	GraphData[201] = LoadGraph("GraphData\\stayBullet.png");


	//クレー種類
	GraphData[202] = LoadGraph("GraphData\\Clay\\clayGrassRed.PNG");
	GraphData[203] = LoadGraph("GraphData\\Clay\\clayIceRed.PNG");
	GraphData[204] = LoadGraph("GraphData\\Clay\\claySandRed.PNG");
	GraphData[205] = LoadGraph("GraphData\\Clay\\clayWoodRed.PNG");
			  
	GraphData[206] = LoadGraph("GraphData\\Clay\\clayGrassBlue.PNG");
	GraphData[207] = LoadGraph("GraphData\\Clay\\clayIceBlue.PNG");
	GraphData[208] = LoadGraph("GraphData\\Clay\\claySandBlue.PNG");
	GraphData[209] = LoadGraph("GraphData\\Clay\\clayWoodBlue.PNG");
	return;
}

void ResultTextureLoad()
{
	GraphData[0] = LoadGraph("GraphData\\result\\Screen02.png");
	GraphData[1] = LoadGraph("GraphData\\result\\Screen03.png");
	GraphData[2] = LoadGraph("GraphData\\result\\Checkmark.png");
	//GraphData[3] = LoadGraph("GraphData\\grass.png");
	GraphData[4] = LoadGraph("GraphData\\result\\ReturnDark.png");
	GraphData[5] = LoadGraph("GraphData\\result\\Draw.png");
	GraphData[6] = LoadGraph("GraphData\\result\\ReturnLight.png");
	GraphData[7] = LoadGraph("GraphData\\result\\Screen02CPU.png");
	GraphData[8] = LoadGraph("GraphData\\result\\Screen03CPU.png");
	GraphData[9] = LoadGraph("GraphData\\result\\DrawCPU.png");
	GraphData[10] = LoadGraph("GraphData\\result\\drawText.png");
	GraphData[11] = LoadGraph("GraphData\\result\\DefWin.png");
	GraphData[12] = LoadGraph("GraphData\\result\\CpuWin.png");
	GraphData[13] = LoadGraph("GraphData\\result\\PlayerWin.png");
	GraphData[14] = LoadGraph("GraphData\\result\\AtkWin.png");

	return;
}




void TutorialTextureLoad()
{

	GraphData[7] = LoadGraph("GraphData\\home.png");    //背景
	GraphData[8] = LoadGraph("GraphData\\homeBack.png");
	GraphData[9] = LoadGraph("GraphData\\result\\returnDark.png");
	GraphData[10] = LoadGraph("GraphData\\result\\returnLight.png");


	GraphData[0] = LoadGraph("GraphData\\Tutorial\\L_Arrow.png");        //左矢印
	GraphData[1] = LoadGraph("GraphData\\Tutorial\\L_Arrow 2.png");        //左矢印 洗濯
	GraphData[2] = LoadGraph("GraphData\\Tutorial\\R_Arrow.png");        //右矢印 
	GraphData[3] = LoadGraph("GraphData\\Tutorial\\R_Arrow 2.png");        //右矢印 洗濯

	GraphData[4] = LoadGraph("GraphData\\Tutorial\\tutorial1.png");        //攻撃攻撃説明
	GraphData[5] = LoadGraph("GraphData\\Tutorial\\tutorial2.png");        //防衛操作説明
	GraphData[6] = LoadGraph("GraphData\\Tutorial\\tutorial3.png");        //防衛ステータス説明



	return;
}


/*


サウンドのロードを一括にして、アプリケーション起動時に読み込む


*/



void SoundLoad() 	//サウンドのロード
{
	//タイトル用BGM
	SoundData[0] = LoadSoundMem("SoundData\\Bgm\\Title\\PerituneMaterial_Rapid_loop.mp3");

	SoundData[1] = LoadSoundMem("SoundData\\SoundEffect\\GameUI\\GameUI.wav");



	//Home画面のボイス
	SoundData[2] = LoadSoundMem("SoundData\\Guide_Voice\\Home\\homegaido.wav");

	//同シーンBGM
	SoundData[3] = LoadSoundMem("SoundData\\Bgm\\Main\\maou_bgm_cyber38.mp3");


	//ショップ用めたんボイス
	SoundData[4] = LoadSoundMem("SoundData\\Guide_Voice\\Shop\\misegaido.wav");


	//バトル時アニメーションの効果音
	SoundData[6] = LoadSoundMem("SoundData\\SoundEffect\\Animation");
	//バトル時ディフェンスのめたん説明ボイス
	SoundData[7] = LoadSoundMem("SoundData\\Guide_Voice\\Defense");
	//バトル時ディフェンスのBGM
	SoundData[8] = LoadSoundMem("SoundData\\Bgm\\Defense\\Virus_Entry.mp3");
	//バトル時銃発射サウンドエフェクト
	SoundData[9] = LoadSoundMem("SoundData\\SoundEffect\\Gun\\Fire.mp3");
	SoundData[11] = LoadSoundMem("SoundData\\SoundEffect\\Crey\\CreySE.mp3");

	//リザルト用BGM
	SoundData[10] = LoadSoundMem("SoundData\\Bgm\\Result\\maou_bgm_cyber13.mp3");


	//クレー破壊音
	SoundData[12] = LoadSoundMem("SoundData\\Clay_Break\\Clay_Break.mp3");
	SoundData[13] = LoadSoundMem("SoundData\\Clay_Break\\Clay_Break_Grass.mp3");
	SoundData[14] = LoadSoundMem("SoundData\\Clay_Break\\Clay_Break_Ice.mp3");
	SoundData[15] = LoadSoundMem("SoundData\\Clay_Break\\Clay_Break_Stone.mp3");
	SoundData[16] = LoadSoundMem("SoundData\\Clay_Break\\Clay_Break_Wood.mp3");

	return;
}











