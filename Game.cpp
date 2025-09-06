#include "Game.h"
#include "Keyboad.h"
#include "Mouse.h"
#include "math.h"
#include "LoadSorce.h"
#include "Fps.h"

//���������A�l���s�H�




//���݂̃V�[��
enum GameScene NowGameScene;

//�ڍs��̃Q�[���V�[��
enum GameScene ChangeGameScene;



//�V�[�����ʖ�
char GameSceneName[GameSceneCount][GameSceneNameMax]
{
	"�^�C�g��",
	"���C��",
	"�U��",
	"�h�q",
	"���U���g"
};

//�V�[���؂�ւ���̌o�߃t���[�������Ǘ�
int GameSceneFrameCount[GameSceneCount];

bool MainBGM = false; //Main��ʂ�BGM���P�񂾂����������̂ŁAmain�ɓ������u��true�ɂ��A�h�q��false�ɂ���B


//--------------------------�ˌ�-------------------------------

//��֘A
VERTEX3D Bullet1Vertex[6];
VERTEX3D Bullet2Vertex[6];
MATRIX Bullet1TransformMatrix;//�g�����X�t�H�[��
MATRIX Bullet2TransformMatrix;//�g�����X�t�H�[��
//VECTOR Angle;			//�p�x

float BulletSpeed;		//���x


bullet Bullet1;
bullet Bullet2;

/*
bool IsMoving = false;  // ���ˍς݂��ۂ�
int StartTime = 0;      // ��΂��n�߂�����
VECTOR Position;		//�e�̈ʒu

*/


//[���W�n�̕ϊ��p]

VECTOR camPos;	//�J�����̈ʒu
VECTOR camDir;	//�J�����̌���
VECTOR camTop; //�J�����̓��̌���
VECTOR Ps;//�X�N���[�����W�@(x, y, near)
VECTOR PsToCam;//�ϊ���̍��W�n

VECTOR GunDir1;//�e�̊p�x(�@�u�X�N���[�����W�@- �J�������W�v�ɂ������x�N�g��)
VECTOR GunDir2;//�e�̊p�x(�@�u�X�N���[�����W�@- �J�������W�v�ɂ������x�N�g��)

int mouseX = 0;//�}�E�XX���W�擾
int mouseY = 0;//�}�E�XY���W�擾

float MbMouseX  = 0;//�X�N���[����(Mobile���W)�̃}�E�X���W�@x
float MbMouseY  = 0;//y




//�o�g���V�[���̃A�j���[�V�����摜�̓ǂݍ��݂��A�P��ɐ������邽�߂̕ϐ��B
//(�����l��false�B�ŏ��ɖh�q�ɔ��Ń��[�h�����^�C�~���O��LoadMovie��true�ɂȂ�A���̌�̓��U���g�ɔ�񂾎���false�ɂȂ�)
bool LoadMovie = false; 


float AtackScore;		//�U���̃X�R�A
float DefenceScore;	//�h�q�̃X�R�A


hasya hasyaL;//���ˑ�L(�\����)
hasya hasyaR;//���ˑ�R(�\����)

bool hasyaLR = true;
int fontSize = 0;

int animeF, animeN;	//�U���A�h�q�̃A�j���[�V�����Đ����Ɏg�p����ϐ��B�l�̏㏸�ɔ����ăp���p������̂悤�ɍĐ�����B

int mainAnime;
float UIanime[] = { 1,1,1,1,1,1,1,1 };
int shopAnime = 0;
float speedCtrl;
float niconico1, niconico2;
int shopGOAnime, shopGOAnimeCtrl;
bool modeSelect;






//---------------- -----------------------------
float kumoMove[2] = { 0,0 };

//�����_���w�i�ϐ�
int BackgroundImages[4];
int SelectedBackgroundIndex;





int MovieGraphHandle;		//

int cR;		//

int GunStatus;//�e�̎��

//���U���g����--------------------------
//int AtScore = 0;
//int DfScore = 0;

int debugGraph;		//

int  ResultState = 0;		//���U���g�V�[���̏�ԁ@[0�̎� =>   ]  
							//						[1�̎� =>  ]


//���̑傫��





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
//�N���C�֘A�̃O���[�o���ϐ�

cley Cley1;
cley Cley2;


/*

VECTOR CleyPosition1;//�ʒu
VECTOR CleyVelocity1;//�ړ��̑���
VECTOR CleyAngle1;	//�p�x
VECTOR CleyDir1;	//�N���C�̕���
VECTOR CleyBreakPosition1;//1��ꂽ�ʒu
int CleyBreak1;//1�̃N���[����ꂽ���ۂ�
float CleyBreakMove1X;//1����ꂽ��̃A�j���[�V��������X
float CleyBreakMove1Y;//1����ꂽ��̃A�j���[�V��������Y
float CleyBreakMove1Ygravity; //1����ꂽ��̃A�j���[�V��������Y�d��
int CleyColor1;		//�F (1 => �F�A�@2 => �ԐF�@)
bool IsCleyMoving1 = false;	//�����Ă����Ԃ��ۂ�
int CleyStartTime1 = 0;		//�����o�����ŏ��̎���
*/

/*
VECTOR CleyPosition2;//�ʒu
VECTOR CleyVelocity2;//�ړ��̑���
VECTOR CleyAngle2;	//�p�x
VECTOR CleyBreakPosition2;//2��ꂽ�ʒu
VECTOR CleyDir2;	//�N���C�̕���
int CleyColor2;	 	//�F (1 => �F�A�@2 => �ԐF�@)
bool IsCleyMoving2  = false;	//�����Ă����Ԃ��ۂ�
int CleyBreak2; //2�̃N���[����ꂽ���ۂ�

float CleyBreakMove2X;//2����ꂽ��̃A�j���[�V��������X
float CleyBreakMove2 Y;//2����ꂽ��̃A�j���[�V��������Y
float CleyBreakMove2Ygravity; //2����ꂽ��̃A�j���[�V��������Y�d��
int CleyStartTime2 = 0;		//�����o�����ŏ��̎���
*/



//float CleySpeed = 20.0f;		//���x
float AirResistance = 0.995f; // ��C��R�̉e�����y��
float Gravity = 9.8f;        // �d�͉����x
int CollisionDisplayStartTime = -1; // �Փ˃��b�Z�[�W�̕\���J�n����

// �k������V�����T�C�Y���w��
int newWidth = 250;  // �V������
int newHeight = 200; // �V��������
//�@=>�@���������B�i�j�R��

bool solo;//�\�����[�h���ۂ�


//�������[�����
void Releace()
{
	InitGraph();
	InitSoundMem();

	return;
}



//2�_�Ԃ̐��������A�擾�����}�E�X�̍��W�Ƃ̋�����}��B
int SetLineToMouse(float x1, float y1, float x2, float y2)
{
	int mouseX, mouseY;
	GetMousePoint(&mouseX, &mouseY);

	float kari = (y1 - y2) * (x1 - static_cast<float>(mouseX)) + (x1 - x2) * (static_cast<float>(mouseY) - y1);
	
	return static_cast<int>(kari);
}


bool SetUI(float L_up_x, float L_up_y, float R_up_x, float R_up_y, float L_down_x, float L_down_y, float R_down_x, float R_down_y)
{
	//��̕�
	SetLineToMouse(L_up_x, L_up_y, R_up_x, R_up_y);
	//���̕�
	SetLineToMouse(L_down_x, L_down_y, R_down_x, R_down_y);

	//���̕�
	SetLineToMouse(L_up_x, L_up_y, L_down_x, L_down_y);

	//�E�̕�
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





//�^�C�g��������
void TitleInit(void)
{
	if (DebugMode == true)
	{
		DrawFormatString(width - 200, 0, GetColor(255, 255, 255), "%s%s", GameSceneName[ChangeGameScene], "������");




	}


	//------------------- -----------------------
	SelectedBackgroundIndex = GetRand(3);

	StopSoundMem(SoundData[2]);
	StopSoundMem(SoundData[3]);

			//�������Ɋi�[����Ă���A�j���[�V�����ȊO�̃f�[�^�����
			for (int i = 0; i < 201; i++) { DeleteGraph(GraphData[i]); }


			TitleTextureLoad();


			//�V�[���؂�ւ���̌o�߃t���[������������
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



//�^�C�g���Ǘ�
void TitleCtrl(void)
{

	TitleProc();
	TitleDraw();
	return;
}



//�^�C�g������(�L�[���͂Ȃ�)
void TitleProc(void)
{

	

	GameSceneFrameCount[NowGameScene]++;

	if (GameSceneFrameCount[NowGameScene] >= 70)
	{
		if (CheckHitKeyAll() != 0)
		{
			//�V�[���؂�ւ�
			ChangeGameScene = MainScene;

			//GameSceneFrameCount[NowGameScene]++;

			//�����ɐ؂�ւ���
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



//�^�C�g���`��(������C���X�g)
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
		DrawFormatString(width - 200, 0, GetColor(255, 255, 255), "%s%s", GameSceneName[NowGameScene], "�`�撆");

		DrawFormatString(700, 0, GetColor(255, 255, 255), "%d", GameSceneFrameCount[NowGameScene]);

		DrawFormatString(700, 0, GetColor(255, 255, 255), "%d", titleAnimeLogo);
	}

	return;
}


//���C��������
void MainInit(void)
{
	if (DebugMode == true)
	{
		DrawFormatString(width - 200, 0, GetColor(255, 255, 255), "%s%s", GameSceneName[ChangeGameScene], "������");

	}
	//----------------------------------------------------------------
	//DX_TEST_0704�ȍ~�̃T���v���Ɉڍs����ׂ��f�[�^
	//----------------------------------------------------------------

		//���łɓǂݍ��񂾃T�E���h���~
	StopSoundMem(SoundData[4]);
	StopSoundMem(SoundData[10]);
	//StopSoundMem(SoundData[3]);

	//----------------------------------------------------------------
	//DX_TEST_0704�ȍ~�̃T���v���Ɉڍs����ׂ��f�[�^�i�����܂Łj
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
	//DX_TEST_0704�ȍ~�̃T���v���Ɉڍs����ׂ��f�[�^
	//----------------------------------------------------------------


			//���ʐݒ�
	ChangeVolumeSoundMem(255 * 65 / 100, SoundData[2]);

	ChangeVolumeSoundMem(255 * 40 / 100, SoundData[3]);

	//�{�C�X���Đ�  voice => [2],  BGM => [3]
	PlaySoundMem(SoundData[2], DX_PLAYTYPE_BACK, true);

	SetLoopPosSoundMem(0, SoundData[3]);
	//BGM�Đ�
	if (MainBGM != true)
	{
		PlaySoundMem(SoundData[3], DX_PLAYTYPE_BACK, true);

		MainBGM = true;
	}
		/*
	//���łɓǂݍ��񂾃T�E���h���~
	StopSoundMem(SoundData[0]);

	//----------------------------------------------------------------
	//DX_TEST_0704�ȍ~�̃T���v���Ɉڍs����ׂ��f�[�^�i�����܂Łj
	//----------------------------------------------------------------

			AtackScore = 0;
			DefenceScore = 0;

			//�������Ɋi�[����Ă���A�j���[�V�����ȊO�̃f�[�^�����
			for (int i = 0; i < 201; i++) { DeleteGraph(GraphData[i]); }

			HomeTextureLoad();

	//----------------------------------------------------------------
	//DX_TEST_0704�ȍ~�̃T���v���Ɉڍs����ׂ��f�[�^
	//----------------------------------------------------------------
	
			//�T�E���h�̐�L����Ă郁���������
			InitSoundMem();
			//�z�[���p�̉摜���������Ɋi�[
			HomeSoundLoad();

			//���ʐݒ�
			ChangeVolumeSoundMem(255 * 65 / 100, SoundData[0]);

			//�{�C�X���Đ�
			PlaySoundMem(SoundData[0], DX_PLAYTYPE_BACK, true);

	//----------------------------------------------------------------
	//DX_TEST_0704�ȍ~�̃T���v���Ɉڍs����ׂ��f�[�^
	//----------------------------------------------------------------
	*/
			//�V�[���؂�ւ���̌o�߃t���[������������
			GameSceneFrameCount[ChangeGameScene] = 0;


	return;
}



//���C���Ǘ�
void MainCtrl(void)
{
	MainProc();
	MainDraw();



	return;
}



//���C������
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
				ChangeGameScene = DefScene;//�h�q�V�[���Ɉڍs����
			}

			if (SetUI(1001, 135, 1646, 135, 1001, 852, 1646, 852) && MousePush(MOUSE_INPUT_LEFT))
			{
				solo = true;
				ChangeGameScene = SoloScene;//�\���V�[���ڍs��U���V�[���Ɉڍs����
			}

			
		}
		//�J�[�\�����^�C�g��UI�̒��ɍ����āA���N���b�N�������ꂽ�u�ԂɃV�[����ς���B���[�h�Z���N�g���J����ĂȂ��Ƃ��ɂ�
		if (modeSelect == false)
		{
			if (SetUI(29, 874, 494, 874, 29, 960, 457, 960) == true)
			{
				if (MousePush(MOUSE_INPUT_LEFT) == true)
				{
					MainBGM = false;
					ChangeGameScene = TitleScene;

					//�����ɐ؂�ւ���
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
					//DrawFormatString(700, 0, GetColor(255, 255, 255), "�Q�[���I���I��");


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

					//�����ɐ؂�ւ���
					return;

				}
			}
			*/

			cR = sqrt((mouseX - 964) * (mouseX - 964) + (mouseY - 1050) * (mouseY - 1050));

			if (cR < 447)
			{
				if (MousePush(MOUSE_INPUT_LEFT) == true) 
				{
					modeSelect = true;//���[�h�Z���N�g�̉�ʂɔ��
					PlaySoundMem(SoundData[1], DX_PLAYTYPE_BACK, true);//�N���b�N������UI�̃T�E���h���Đ�
				}
				MainBGM = false;
			}



			if (SetUI(1192, 90, 1841, 165, 1192, 464, 1841, 537) && MousePush(MOUSE_INPUT_LEFT))
			{
				shopYes = true;//shop���J���Ă��܂�

				shopGOAnime = 1;

				//�N���b�N������UI�̃T�E���h���Đ�
				PlaySoundMem(SoundData[1], DX_PLAYTYPE_BACK, true);

				return;
			}

			if (SetUI(27, 742, 587, 742, 27, 869, 490, 869) && MousePush(MOUSE_INPUT_LEFT))
			{
				//�N���b�N������UI�̃T�E���h���Đ�
				PlaySoundMem(SoundData[1], DX_PLAYTYPE_BACK, true);

				optionYes = true;
				shopGOAnime = 1;

				return;
			}
		}


		if (modeSelect == true) {
			if (SetUI(223, 865, 480, 865, 229, 992, 480, 992) && MousePush(MOUSE_INPUT_LEFT))
			{
				modeSelect = false;//���[�h�I������߂�

			}
		}

		
	}
	GetMousePoint(&mouseX, &mouseY);

	return;
}



//���C���`��
void MainDraw(void)
{

	DrawGraph(0, 0, GraphData[15], true);

	DrawFormatString(niconico1 + 700, 400, GetColor(0, 0, 0), "wktk");
	DrawFormatString(niconico1 + 1000, 450, GetColor(0, 0, 0), "���̂���");
	DrawFormatString(niconico1 + 1200, 500, GetColor(0, 0, 0), "���k�Y��");
	DrawFormatString(niconico1 + 1210, 320, GetColor(0, 0, 0), "�ߘa�̐_�Q�[�I");
	//DrawFormatString(niconico1 + 1300, 210, GetColor(0, 0, 0), "�N�\�Q�[�߂���");
	DrawFormatString(niconico1 + 1300, 210, GetColor(0, 0, 0), "�_�Q�[ktkr");
	DrawFormatString(niconico1 + 1280, 450, GetColor(0, 0, 0), "UI�D��");
	//DrawFormatString(niconico1 + 1420, 310, GetColor(0, 0, 0), "�I���R���N���[�o�g��");
	DrawFormatString(niconico1 + 1420, 310, GetColor(0, 0, 0), "�w����i���ă}�H");
	//DrawFormatString(niconico1 + 1700, 400, GetColor(0, 0, 0), "���Ԃ�");
	DrawFormatString(niconico1 + 1700, 400, GetColor(0, 0, 0), "�����낢��Ȃ���");
	//DrawFormatString(niconico1 + 1100, 450, GetColor(0, 0, 0), "���\�L��");
	DrawFormatString(niconico1 + 1100, 450, GetColor(0, 0, 0), "�����̑��y����");
	DrawFormatString(niconico1 + 1610, 450, GetColor(0, 0, 0), "��Փx����;;");
	DrawFormatString(niconico1 + 1660, 480, GetColor(0, 0, 0), "����オ�肦����");
	DrawFormatString(niconico1 + 1830, 290, GetColor(0, 0, 0), "�ō�");
	DrawFormatString(niconico1 + 1980, 450, GetColor(0, 0, 0), "�l���̏k�}");
	DrawFormatString(niconico1 + 1800, 310, GetColor(0, 0, 0), "���\�y����");

	DrawFormatString(niconico2 + 700, 350, GetColor(0, 0, 0), "����ԃA�c����");
	//DrawFormatString(niconico2 + 1000, 290, GetColor(0, 0, 0), "�`�F�\���[�}���̃p�N�����");
	DrawFormatString(niconico2 + 1000, 290, GetColor(0, 0, 0), "�F�B�K�`�ł��܂�����");
	//DrawFormatString(niconico2 + 1200, 500, GetColor(0, 0, 0), "�ӂ������");
	DrawFormatString(niconico2 + 1200, 500, GetColor(0, 0, 0), "�N���ΐ킵��[�I");
	DrawFormatString(niconico2 + 1210, 370, GetColor(0, 0, 0), "����DX���C�u�����Ȃ�");
	//DrawFormatString(niconico2 + 1300, 380, GetColor(0, 0, 0), "�ߑa�Q�[");
	DrawFormatString(niconico2 + 1300, 380, GetColor(0, 0, 0), "����IPUT���Q�[����");
	//DrawFormatString(niconico2 + 1280, 400, GetColor(0, 0, 0), "�����̂��̂��̂��ǂ����񂽂�");
	DrawFormatString(niconico2 + 1280, 400, GetColor(0, 0, 0), "�V��܂��H");
	DrawFormatString(niconico2 + 1420, 350, GetColor(0, 0, 0), "����̃X�L���ق���");
	DrawFormatString(niconico2 + 1700, 320, GetColor(0, 0, 0), "���Ԃ�Y��Ă���Ă�");
	DrawFormatString(niconico2 + 1100, 300, GetColor(0, 0, 0), "��������I");
	DrawFormatString(niconico2 + 1610, 420, GetColor(0, 0, 0), "���A���̃N���[�ˌ���肽���Ȃ��");
	DrawFormatString(niconico2 + 1740, 410, GetColor(0, 0, 0), "�d��");
	DrawFormatString(niconico2 + 1830, 320, GetColor(0, 0, 0), "�R���s���[�^�[����...");
	DrawFormatString(niconico2 + 1980, 390, GetColor(0, 0, 0), "�~�j�K�������͂�");
	DrawFormatString(niconico2 + 1800, 340, GetColor(0, 0, 0), "���E�ύD��");



	//UI�\��
	DrawGraph(0, 0, GraphData[0], true);
	DrawGraph(UIanime[6], 0, GraphData[1], true);
	DrawGraph(UIanime[1], 0, GraphData[2], true);

		
	DrawGraph(UIanime[2], UIanime[4], GraphData[3], true);
	DrawGraph(UIanime[5], 0, GraphData[4], true);
	DrawGraph(UIanime[2], UIanime[4], GraphData[5], true);
	DrawGraph(0, 0, GraphData[14], true);
	DrawGraph(0, UIanime[3], GraphData[6], true);//�o�g��


	
	if (modeSelect == false) {
		if (cR < 447) 	DrawGraph(0, UIanime[3], GraphData[7], true);
		if (SetUI(1192, 90, 1841, 165, 1192, 464, 1841, 537) == true)	DrawGraph(UIanime[2], UIanime[4], GraphData[11], true);//�V���b�v�I����
		if (SetUI(1370, 536, 1885, 591, 1360, 807, 1885, 881) == true)	DrawGraph(UIanime[2], UIanime[4], GraphData[13], true);//�`���[�g���A���I����
		if (SetUI(27, 742, 587, 742, 27, 869, 490, 869) == true)		DrawGraph(UIanime[1], 0, GraphData[10], true);//�I�v�V�����I����
		if (SetUI(29, 874, 494, 874, 29, 960, 457, 960) == true)		DrawGraph(UIanime[5], 0, GraphData[12], true);//�^�C�g���I����
		if (SetUI(22, 979, 457, 979, 22, 1059, 443, 1059) == true)		DrawGraph(UIanime[6], 0, GraphData[9], true); //�Q�[���I���I����
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


		if (SetUI(265, 135, 905, 135, 265, 852, 905, 852))				DrawGraph(0, 0, GraphData[19], true); //�_�u���I����
		if (SetUI(1001, 135, 1646, 135, 1001, 852, 1646, 852))				DrawGraph(0, 0, GraphData[20], true); //�\���I����

	}






	//�f�o�b�O�p�\��
	if (DebugMode == true)
	{
		DrawFormatString(width - 200, 0, GetColor(255, 255, 255), "%s%s", GameSceneName[NowGameScene], "�`�撆");



		DrawFormatString(100, 100, GetColor(255, 255, 255), "�}�E�XX:%d", mouseX);
		DrawFormatString(300, 100, GetColor(255, 255, 255), "Y:%d", mouseY);
		//if(MainBGM != true)DrawFormatString(200, 400, GetColor(255, 255, 255), "BGM");


		
		if (SetUI(1192, 90, 1841, 165, 1192, 464, 1841, 537) == true)	DrawFormatString(700, 0, GetColor(255, 255, 255), "�V���b�v�I��");

		if (SetUI(1370, 536, 1885, 591, 1360, 807, 1885, 881) == true) DrawFormatString(700, 0, GetColor(255, 255, 255), "�`���[�g���A���I��");
		
		if (SetUI(27, 742, 587, 742, 27, 869, 490, 869) == true) DrawFormatString(700, 0, GetColor(255, 255, 255), "�I�v�V�����I��");
		
		if (SetUI(29, 874, 494, 874, 29, 960, 457, 960) == true) DrawFormatString(700, 0, GetColor(255, 255, 255), "�^�C�g��UI�I��");

		if (SetUI(22, 979, 457, 979, 22, 1059, 443, 1059) == true) DrawFormatString(700, 0, GetColor(255, 255, 255), "�Q�[���I���I��");


	}

	
	return;
}





//�V���b�v������
void ShopInit(void)
{
//----------------------------------------------------------------
//DX_TEST_0704�ȍ~�̃T���v���Ɉڍs����ׂ��f�[�^
//----------------------------------------------------------------
	//���łɓǂݍ��񂾃T�E���h���~
	StopSoundMem(SoundData[2]);

//----------------------------------------------------------------
//DX_TEST_0704�ȍ~�̃T���v���Ɉڍs����ׂ��f�[�^�i�����܂Łj
//----------------------------------------------------------------

			//�������Ɋi�[����Ă���A�j���[�V�����ȊO�̃f�[�^�����
	for (int i = 0; i < 201; i++) { DeleteGraph(GraphData[i]); }

	ShopTextureLoad();

//----------------------------------------------------------------
//DX_TEST_0704�ȍ~�̃T���v���Ɉڍs����ׂ��f�[�^
//----------------------------------------------------------------


	//���ʐݒ�
	ChangeVolumeSoundMem(255 * 65 / 100, SoundData[4]);

	//�{�C�X���Đ��i�V���b�v�p�߂���{�C�X�j
	PlaySoundMem(SoundData[4], DX_PLAYTYPE_BACK, true);

//----------------------------------------------------------------
//DX_TEST_0704�ȍ~�̃T���v���Ɉڍs����ׂ��f�[�^�i�����܂Łj
//----------------------------------------------------------------

	GameSceneFrameCount[ChangeGameScene] = 0;
	GunStatus = 0;//�e��ޏ������i�V���b�g�K���j

	return;
}



//�V���b�v�Ǘ�
void ShopCtrl(void)
{

	ShopProc();
	ShopDraw();

	return;
}



//�V���b�v����
void ShopProc(void)
{
	//�}�E�X���W�擾
	GetMousePoint(&mouseX, &mouseY);

	if (SetUI(220, 388, 1012, 388, 245, 488, 1011, 488) == true || SetUI(212, 373, 341, 338, 216, 390, 357, 390) == true)
	{

		GunStatus = 0;

	}

		//������������z�[����ʑJ��
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



//�V���b�v��ʕ`��
void ShopDraw(void)
{

	//----------------------------------��ʉ摜�\��-------------------------------------


	DrawGraph(0, 0, GraphData[9], true);

	DrawFormatString(niconico1 + 700, 400, GetColor(0, 0, 0), "wktk");
	DrawFormatString(niconico1 + 1000, 450, GetColor(0, 0, 0), "���̂���");
	DrawFormatString(niconico1 + 1200, 500, GetColor(0, 0, 0), "���k�Y��");
	DrawFormatString(niconico1 + 1210, 320, GetColor(0, 0, 0), "�ߘa�̐_�Q�[�I");
	//DrawFormatString(niconico1 + 1300, 210, GetColor(0, 0, 0), "�N�\�Q�[�߂���");
	DrawFormatString(niconico1 + 1300, 210, GetColor(0, 0, 0), "�_�Q�[ktkr");
	DrawFormatString(niconico1 + 1280, 450, GetColor(0, 0, 0), "UI�D��");
	//DrawFormatString(niconico1 + 1420, 310, GetColor(0, 0, 0), "�I���R���N���[�o�g��");
	DrawFormatString(niconico1 + 1420, 310, GetColor(0, 0, 0), "�w����i���ă}�H");
	//DrawFormatString(niconico1 + 1700, 400, GetColor(0, 0, 0), "���Ԃ�");
	DrawFormatString(niconico1 + 1700, 400, GetColor(0, 0, 0), "�����낢��Ȃ���");
	//DrawFormatString(niconico1 + 1100, 450, GetColor(0, 0, 0), "���\�L��");
	DrawFormatString(niconico1 + 1100, 450, GetColor(0, 0, 0), "�����̑��y����");
	DrawFormatString(niconico1 + 1610, 450, GetColor(0, 0, 0), "��Փx����;;");
	DrawFormatString(niconico1 + 1660, 480, GetColor(0, 0, 0), "����オ�肦����");
	DrawFormatString(niconico1 + 1830, 290, GetColor(0, 0, 0), "�ō�");
	DrawFormatString(niconico1 + 1980, 450, GetColor(0, 0, 0), "�l���̏k�}");
	DrawFormatString(niconico1 + 1800, 310, GetColor(0, 0, 0), "���\�y����");

	DrawFormatString(niconico2 + 700, 350, GetColor(0, 0, 0), "����ԃA�c����");
	//DrawFormatString(niconico2 + 1000, 290, GetColor(0, 0, 0), "�`�F�\���[�}���̃p�N�����");
	DrawFormatString(niconico2 + 1000, 290, GetColor(0, 0, 0), "�F�B�K�`�ł��܂�����");
	//DrawFormatString(niconico2 + 1200, 500, GetColor(0, 0, 0), "�ӂ������");
	DrawFormatString(niconico2 + 1200, 500, GetColor(0, 0, 0), "�N���ΐ킵��[�I");
	DrawFormatString(niconico2 + 1210, 370, GetColor(0, 0, 0), "����DX���C�u�����Ȃ�");
	//DrawFormatString(niconico2 + 1300, 380, GetColor(0, 0, 0), "�ߑa�Q�[");
	DrawFormatString(niconico2 + 1300, 380, GetColor(0, 0, 0), "����IPUT���Q�[����");
	//DrawFormatString(niconico2 + 1280, 400, GetColor(0, 0, 0), "�����̂��̂��̂��ǂ����񂽂�");
	DrawFormatString(niconico2 + 1280, 400, GetColor(0, 0, 0), "�V��܂��H");
	DrawFormatString(niconico2 + 1420, 350, GetColor(0, 0, 0), "����̃X�L���ق���");
	DrawFormatString(niconico2 + 1700, 320, GetColor(0, 0, 0), "���Ԃ�Y��Ă���Ă�");
	DrawFormatString(niconico2 + 1100, 300, GetColor(0, 0, 0), "��������I");
	DrawFormatString(niconico2 + 1610, 420, GetColor(0, 0, 0), "���A���̃N���[�ˌ���肽���Ȃ��");
	DrawFormatString(niconico2 + 1740, 410, GetColor(0, 0, 0), "�d��");
	DrawFormatString(niconico2 + 1830, 320, GetColor(0, 0, 0), "�R���s���[�^�[����...");
	DrawFormatString(niconico2 + 1980, 390, GetColor(0, 0, 0), "�~�j�K�������͂�");
	DrawFormatString(niconico2 + 1800, 340, GetColor(0, 0, 0), "���E�ύD��");


	DrawGraph(0, 0, GraphData[0], true);
	DrawGraph(0, 0, GraphData[1], true);
	DrawGraph(0, 0, GraphData[2], true);
	DrawGraph(0, 0, GraphData[3], true);
	DrawGraph(0, 0, GraphData[4], true);
	DrawGraph(0, 0, GraphData[5], true);
	DrawGraph(0, 0, GraphData[6], true);
	DrawGraph(0, 0, GraphData[7], true);


	if (SetUI(1190, 687, 1838, 687, 1305, 1026, 1838, 1026) == true) DrawGraph(0, 0, GraphData[8], true);


	//�f�o�b�N�@�\
	if (DebugMode == true)
	{
		if (SetUI(220, 388, 1012, 388, 245, 488, 1011, 488) == true || SetUI(212, 373, 341, 338, 216, 390, 357, 390) == true)	DrawFormatString(700, 0, GetColor(255, 255, 255), "�V���b�g�K���I��");

		DrawFormatString(width - 200, 0, GetColor(255, 255, 255), "%s%s", GameSceneName[NowGameScene], "�V���b�v�`�撆");

		DrawFormatString(100, 100, GetColor(255, 255, 255), "�}�E�XX:%d", mouseX);
		DrawFormatString(200, 100, GetColor(255, 255, 255), "�}�E�XY:%d", mouseY);
	}
	return;
}



//�I�v�V����������
void OptionInit(void)
{

	for (int i = 0; i < 201; i++) { DeleteGraph(GraphData[i]); }
	OptionTextureLoad();


	GameSceneFrameCount[ChangeGameScene] = 0;

	return;
}

//�I�v�V�����Ǘ�
void OptionCtrl(void)
{
	OptionProc();
	OptionDraw();

	return;
}

//�I�v�V��������
void OptionProc(void)
{
	//�}�E�X���W�擾
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

//�I�v�V�����`��
void OptionDraw(void)
{


	DrawGraph(0, 0, GraphData[4], TRUE);//�w�i


	SetFontSize(20);

	DrawFormatString(niconico1 + 700, 400, GetColor(0, 0, 0), "wktk");
	DrawFormatString(niconico1 + 1000, 450, GetColor(0, 0, 0), "���̂���");
	DrawFormatString(niconico1 + 1200, 500, GetColor(0, 0, 0), "���k�Y��");
	DrawFormatString(niconico1 + 1210, 320, GetColor(0, 0, 0), "�ߘa�̐_�Q�[�I");
	//DrawFormatString(niconico1 + 1300, 210, GetColor(0, 0, 0), "�N�\�Q�[�߂���");
	DrawFormatString(niconico1 + 1300, 210, GetColor(0, 0, 0), "�_�Q�[ktkr");
	DrawFormatString(niconico1 + 1280, 450, GetColor(0, 0, 0), "UI�D��");
	//DrawFormatString(niconico1 + 1420, 310, GetColor(0, 0, 0), "�I���R���N���[�o�g��");
	DrawFormatString(niconico1 + 1420, 310, GetColor(0, 0, 0), "�w����i���ă}�H");
	//DrawFormatString(niconico1 + 1700, 400, GetColor(0, 0, 0), "���Ԃ�");
	DrawFormatString(niconico1 + 1700, 400, GetColor(0, 0, 0), "�����낢��Ȃ���");
	//DrawFormatString(niconico1 + 1100, 450, GetColor(0, 0, 0), "���\�L��");
	DrawFormatString(niconico1 + 1100, 450, GetColor(0, 0, 0), "�����̑��y����");
	DrawFormatString(niconico1 + 1610, 450, GetColor(0, 0, 0), "��Փx����;;");
	DrawFormatString(niconico1 + 1660, 480, GetColor(0, 0, 0), "����オ�肦����");
	DrawFormatString(niconico1 + 1830, 290, GetColor(0, 0, 0), "�ō�");
	DrawFormatString(niconico1 + 1980, 450, GetColor(0, 0, 0), "�l���̏k�}");
	DrawFormatString(niconico1 + 1800, 310, GetColor(0, 0, 0), "���\�y����");

	DrawFormatString(niconico2 + 700, 350, GetColor(0, 0, 0), "����ԃA�c����");
	//DrawFormatString(niconico2 + 1000, 290, GetColor(0, 0, 0), "�`�F�\���[�}���̃p�N�����");
	DrawFormatString(niconico2 + 1000, 290, GetColor(0, 0, 0), "�F�B�K�`�ł��܂�����");
	//DrawFormatString(niconico2 + 1200, 500, GetColor(0, 0, 0), "�ӂ������");
	DrawFormatString(niconico2 + 1200, 500, GetColor(0, 0, 0), "�N���ΐ킵��[�I");
	DrawFormatString(niconico2 + 1210, 370, GetColor(0, 0, 0), "����DX���C�u�����Ȃ�");
	//DrawFormatString(niconico2 + 1300, 380, GetColor(0, 0, 0), "�ߑa�Q�[");
	DrawFormatString(niconico2 + 1300, 380, GetColor(0, 0, 0), "����IPUT���Q�[����");
	//DrawFormatString(niconico2 + 1280, 400, GetColor(0, 0, 0), "�����̂��̂��̂��ǂ����񂽂�");
	DrawFormatString(niconico2 + 1280, 400, GetColor(0, 0, 0), "�V��܂��H");
	DrawFormatString(niconico2 + 1420, 350, GetColor(0, 0, 0), "����̃X�L���ق���");
	DrawFormatString(niconico2 + 1700, 320, GetColor(0, 0, 0), "���Ԃ�Y��Ă���Ă�");
	DrawFormatString(niconico2 + 1100, 300, GetColor(0, 0, 0), "��������I");
	DrawFormatString(niconico2 + 1610, 420, GetColor(0, 0, 0), "���A���̃N���[�ˌ���肽���Ȃ��");
	DrawFormatString(niconico2 + 1740, 410, GetColor(0, 0, 0), "�d��");
	DrawFormatString(niconico2 + 1830, 320, GetColor(0, 0, 0), "�R���s���[�^�[����...");
	DrawFormatString(niconico2 + 1980, 390, GetColor(0, 0, 0), "�~�j�K�������͂�");
	DrawFormatString(niconico2 + 1800, 340, GetColor(0, 0, 0), "���E�ύD��");






	DrawGraph(0, 0, GraphData[3], TRUE);//�w�i
	DrawGraph(0, 0, GraphData[0], TRUE);//hidariue
	DrawGraph(0, 0, GraphData[1], TRUE);//�T�E���h�o�[
	DrawGraph(0, 0, GraphData[6], TRUE);//�߂�
	if(SetUI(1385, 769, 1773, 769, 1385, 967, 1773, 967))
		DrawGraph(0, 0, GraphData[7], TRUE);//�߂�

	//DrawGraph(935, 448, GraphData[2], true);//�{�[��

	//�}�E�X���W�擾
	GetMousePoint(&mouseX, &mouseY);

	if (SetUI(115, 553, 1850, 553, 115, 590, 1850, 590) && MousePush(MOUSE_INPUT_LEFT))
	{
		VolumeBall = 0;
		newMouse = mouseX;
		VolumeBall++;
	}

	
		DrawGraph(newMouse - 950, 175, GraphData[2], TRUE);//�{�[��
		SetFontSize(60);
		DrawFormatString(670, 380, GetColor(255, 255, 255), ":%d", SoundVolume);
	
	

	if (oldMouse < 115) oldMouse = 115;
	if (oldMouse > 1850)oldMouse = 1850;

	if (SoundVolume > 160)SoundVolume = 160;
	//�z�[����ʑJ��
	if (MousePush(MOUSE_INPUT_RIGHT) == true)
	{
		ChangeGameScene = MainScene;

		return;
	}
	//�f�o�b�N�@�\
	if (DebugMode == true)
	{
		GetMousePoint(&mouseX, &mouseY);

		SetFontSize(15);
		DrawFormatString(width - 200, 0, GetColor(255, 255, 255), "%s%s", GameSceneName[NowGameScene], "�I�v�V�����`�撆");

		DrawFormatString(100, 100, GetColor(255, 255, 255), "�}�E�XX:%d", mouseX);
		DrawFormatString(200, 100, GetColor(255, 255, 255), "�}�E�XY:%d", mouseY);
	}
}



//�`���[�g���A��������  
void TutorialInit(void)
{
	//���łɓǂݍ��񂾃T�E���h���~
	StopSoundMem(SoundData[2]);
	StopSoundMem(SoundData[3]);


	//�������Ɋi�[����Ă���A�j���[�V�����ȊO�̃f�[�^�����
	for (int i = 0; i < 201; i++) { DeleteGraph(GraphData[i]); }


	TutorialTextureLoad();

	TutorialState = 0;
	TimeCount = 0;

	return;
}
//�`���[�g���A���Ǘ�	
void TutorialCtrl(void)
{
	TutorialProc();
	TutorialDraw();

	return;
}
//�`���[�g���A������	
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
//�`���[�g���A���`��	
void TutorialDraw(void)
{




	DrawGraph(0, 0, GraphData[7], TRUE);//����



	if (TutorialState == 0)
	{
		DrawGraph(350, 100, GraphData[4], TRUE);//����

		if (SetUI(1592, 838, 1850, 838, 1592, 941, 1850, 941) == true)
		{
			DrawGraph(0, 0, GraphData[3], TRUE);//���I��
		}
		else DrawGraph(0, 0, GraphData[2], TRUE);//�E���





	}
	else if (TutorialState == 1)
	{
		DrawGraph(350, 100, GraphData[5], TRUE);//����


		if (SetUI(1592, 838, 1850, 838, 1592, 941, 1850, 941) == true)
		{
			DrawGraph(0, 0, GraphData[3], TRUE);//�����I��
		}
		else DrawGraph(0, 0, GraphData[2], TRUE);//�E���


		if (SetUI(60, 838, 327, 838, 60, 941, 327, 941) == true)
		{
			DrawGraph(0, 0, GraphData[1], TRUE);//�����I��
		}
		else DrawGraph(0, 0, GraphData[0], TRUE);//�����



	}
	else if (TutorialState == 2)
	{

		DrawGraph(350, 100, GraphData[6], TRUE);//����

		if (SetUI(60, 838, 327, 838, 60, 941, 327, 941) == true)
		{
			DrawGraph(0, 0, GraphData[1], TRUE);//���I��
		}
		else DrawGraph(0, 0, GraphData[0], TRUE);//�E���

		DrawGraph(0, 0, GraphData[9], TRUE);
		if(TimeCount > 80) DrawGraph(0, 0, GraphData[10], TRUE);

	}



	return;
}







//�h�q������
void DefInit(void)
{

//----------------------------------------------------------------
//DX_TEST_0704�ȍ~�̃T���v���Ɉڍs����ׂ��f�[�^
//----------------------------------------------------------------
	//���łɓǂݍ��񂾃T�E���h���~
	StopSoundMem(SoundData[2]);
	StopSoundMem(SoundData[3]);

//----------------------------------------------------------------
//DX_TEST_0704�ȍ~�̃T���v���Ɉڍs����ׂ��f�[�^(�����܂Łj
//----------------------------------------------------------------

	if (LoadMovie != true)
	{
		//�������Ɋi�[����Ă���A�j���[�V�����ȊO�̃f�[�^�����
		for (int i = 0; i < 201; i++) { DeleteGraph(GraphData[i]); }
		BattleTextureLoad();
		LoadMovie = true;

		// �����_���ɔw�i�摜��I��
		SelectedBackgroundIndex = GetRand(3);

		

	}

		//���ʐݒ�
		ChangeVolumeSoundMem(255 * 40 / 100, SoundData[8]);

		//���[�v�ʒu�̕ύX�����ꂪ�Ȃ��ƃv���O����������(�L;��;�M)
		SetLoopPosSoundMem(0, SoundData[8]);

		//�{�C�X���Đ�
		PlaySoundMem(SoundData[8], DX_PLAYTYPE_BACK, FALSE);

	hasyaLR = true;			//���ˑ�I�𕪂�true�ō��I���Afalse�ŉE�I��
	hasyaL.color = true;    //���N���[�F�I��true�ŐԃN���[�Afalse�ŐN���[
	hasyaL.v = 1;			//���N���[���x�@v == 0,1,2 �x�A���ʁA��
	hasyaL.r = 1;			//���N���[�p�x�@r == 0,1,2 30,45,60�@
	hasyaR.color = true;	//�E�N���[�F�I��true�ŐԃN���[�Afalse�ŐN���[
	hasyaR.v = 1;			//�E�N���[���x�@v == 0,1,2 �x�A���ʁA��
	hasyaR.r = 1;			//�E�N���[�p�x�@r == 0,1,2 30,45,60�@
	animeF = 0;				//�A�j���[�V�����t���[������
	animeN = 1;				//�A�j���[�V����
	kumoMove[0] = -1770;
	kumoMove[1] = 0;

	Cley1.Position = VGet(0, 0, 0);
	Cley2.Position = VGet(0, 0, 0);



	if (DebugMode == true)
	{
		DrawFormatString(width - 200, 0, GetColor(255, 255, 255), "%s%s", GameSceneName[ChangeGameScene], "������");




	}





		return;
	}



//�h�q�Ǘ�	
void DefCtrl(void)
	{

	DefProc();
	DefDraw();

		return;
	}



//�h�q����	
void DefProc(void)
{

	if (DebugMode == true)
	{

		//DrawFormatString(300, 300, GetColor(255, 255, 255), "�܂���X%d", DebugMouseX);
		//DrawFormatString(300, 320, GetColor(255, 255, 255), "�܂���Y%d", DebugMouseY);



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


		//���̔��ˑ�N���b�N�ō����ˑ�p�ݒ�ɕύX
		if (SetUI(-1, 613, 150, 550, -1, 973, 149, 967) || SetUI(147, 550, 355, 560, 147, 967, 355, 960))
			if (MouseDown(MOUSE_INPUT_LEFT) == true)
				hasyaLR = true;
		//�E�̔��ˑ�N���b�N�ŉE���ˑ�p�ݒ�ɕύX
		if (SetUI(1573, 570, 1785, 560, 1578, 970, 1780, 970) || SetUI(1782, 464, 1930, 560, 1780, 970, 1930, 984))
			if (MouseDown(MOUSE_INPUT_LEFT) == true)
				hasyaLR = false;


		//�����ˑ�p�ݒ莞�ɂ��ꂼ���UI�������ۂɑΉ������ϐ���ύX
		if (hasyaLR == true && MouseDown(MOUSE_INPUT_LEFT)) {
			if (SetUI(754, 311, 938, 311, 754, 354, 938, 354)) hasyaL.color = false;
			if (SetUI(1010, 311, 1192, 311, 1010, 354, 1192, 354)) hasyaL.color = true;

			if (SetUI(918, 377, 965, 377, 918, 420, 965, 420)) hasyaL.v = 0;
			if (SetUI(1036, 377, 1130, 377, 1036, 420, 1130, 420)) hasyaL.v = 1;
			if (SetUI(1201, 377, 1250, 377, 1201, 420, 1250, 420)) hasyaL.v = 2;

			if (SetUI(917, 443, 986, 443, 917, 486, 986, 486)) hasyaL.r = 0;
			if (SetUI(1059, 443, 1129, 443, 1059, 486, 1129, 486)) hasyaL.r = 1;
			if (SetUI(1200, 443, 1270, 443, 1200, 486, 1270, 486)) hasyaL.r = 2;



			//----------------------�ގ��ǉ�---------------------
			if (SetUI(960, 503, 1050, 503, 960, 543, 1050, 543)) hasyaL.zaisitu =true;
			if (SetUI(1125, 503, 1214, 503, 1125, 543, 1214, 543)) hasyaL.zaisitu = false;
		}

		//�E���ˑ�p�ݒ莞�ɂ��ꂼ���UI�������ۂɑΉ������ϐ���ύX
		if (hasyaLR == false && MouseDown(MOUSE_INPUT_LEFT)) {
			if (SetUI(754, 311, 938, 311, 754, 354, 938, 354)) hasyaR.color = false;
			if (SetUI(1010, 311, 1192, 311, 1010, 354, 1192, 354)) hasyaR.color = true;

			if (SetUI(918, 377, 965, 377, 918, 420, 965, 420)) hasyaR.v = 0;
			if (SetUI(1036, 377, 1130, 377, 1036, 420, 1130, 420)) hasyaR.v = 1;
			if (SetUI(1201, 377, 1250, 377, 1201, 420, 1250, 420)) hasyaR.v = 2;

			if (SetUI(917, 443, 986, 443, 917, 486, 986, 486)) hasyaR.r = 0;
			if (SetUI(1059, 443, 1129, 443, 1059, 486, 1129, 486)) hasyaR.r = 1;
			if (SetUI(1200, 443, 1270, 443, 1200, 486, 1270, 486))hasyaR.r = 2;


			//----------------------�ގ��ǉ�---------------------
			if (SetUI(960, 503, 1050, 503, 960, 543, 1050, 543)) hasyaR.zaisitu = true;
			if (SetUI(1125, 503, 1214, 503, 1125, 543, 1214, 543)) hasyaR.zaisitu = false;
		}

		//���������������Ƃ��U���^�[���J��
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


//�h�q�`��	
void DefDraw(void) 
	{

	// �I�����ꂽ�w�i�摜�̕`��

	DrawGraph(0, 0, GraphData[181], true);
	DrawGraph(kumoMove[1]*1.1, kumoMove[1], GraphData[182], true);
	DrawGraph(kumoMove[0] * 1.1, kumoMove[0], GraphData[182], true);

	DrawGraph(0, 0, GraphData[SelectedBackgroundIndex], true);
	

	if (hasyaL.color == true) DrawGraph(0, 0, GraphData[4], true);//���ˑ�@���@��
	if (hasyaR.color == true)DrawGraph(0, 0, GraphData[5], true);//���ˑ�@�E�@��
	if (hasyaL.color == false) DrawGraph(0, 0, GraphData[168], true);//���ˑ�@���@��
	if (hasyaR.color == false)DrawGraph(0, 0, GraphData[169], true);//���ˑ�@�E�@��

	DrawGraph(10, 0, GraphData[6], true);//pc

	if (SetUI(1204, 635, 1511, 653, 1041, 797, 1513, 796)) DrawGraph(0, 0, GraphData[166], true);

	
	if (hasyaLR == true) //���̔��ˑ䂪�N���b�N����Ă��遁�@hasya==true
	{
		DrawGraph(1450, 0, GraphData[8], true);//�E��ɃT�u�E�B���h�E
		DrawGraph(0, 0, GraphData[7], true);//�^�񒆂̃��C���E�B���h�E

		if (hasyaL.color == true) DrawGraph(0, 0, GraphData[165], true);//���ˑ�@���@�ԁ@�I��������
		if (hasyaL.color == false) DrawGraph(0, 0, GraphData[170], true);//���ˑ�@���@�@�I��������


		SetFontSize(45);

		//���̔��ˑ�I�����̃��C���E�B���h�E���� color==true �ԃN���[�Afalse==�N���[�@v == 0,1,2 �x�A���ʁA���@r == 30,45,60
		if (hasyaL.color == true) { DrawFormatString(750, 312, GetColor(255, 255, 255), "�N���[ / "); DrawFormatString(750, 312, GetColor(255, 30, 30), "�@�@�@�@   �ԃN���["); }
		else { DrawFormatString(750, 312, GetColor(255, 255, 255), "�@�@�@�@ / �ԃN���["); DrawFormatString(750, 312, GetColor(255, 30, 30), "�N���["); }

		if (hasyaL.v == 0) { DrawFormatString(920, 375, GetColor(255, 255, 255), "�@ - ���� - ��");	DrawFormatString(920, 375, GetColor(255, 30, 30), "�x"); }
		if (hasyaL.v == 1) { DrawFormatString(920, 375, GetColor(255, 255, 255), "�x - �@�@ - ��");	DrawFormatString(920, 375, GetColor(255, 30, 30), "�@   ����"); }
		if (hasyaL.v == 2) { DrawFormatString(920, 375, GetColor(255, 255, 255), "�x - ���� - ");    DrawFormatString(920, 375, GetColor(255, 30, 30), "�@   �@     ��"); }

		if (hasyaL.r == 0) { DrawFormatString(920, 445, GetColor(255, 255, 255), "    - 45��- 60��"); DrawFormatString(920, 445, GetColor(255, 30, 30), "30��"); }
		if (hasyaL.r == 1) { DrawFormatString(920, 445, GetColor(255, 255, 255), "30��-     - 60��");   DrawFormatString(920, 445, GetColor(255, 30, 30), "      45��"); }
		if (hasyaL.r == 2) { DrawFormatString(920, 445, GetColor(255, 255, 255), "30��- 45��-     ");   DrawFormatString(920, 445, GetColor(255, 30, 30), "            60��"); }
 


		//----------------------�ގ� ---------------------
		if (hasyaL.zaisitu == true) { DrawFormatString(960, 500, GetColor(255, 255, 255), "�@�@ / �I�t");	DrawFormatString(960, 500, GetColor(255, 30, 30), "�I��"); }
		else						{ DrawFormatString(960, 500, GetColor(255, 255, 255), "�I�� / ");		DrawFormatString(960, 500, GetColor(255, 30, 30), "�@�@   �I�t"); }


		//���̔��ˑ�I�����̃T�u�E�B���h�E���� color==true �ԃN���[�Afalse==�N���[�@v == 0,1,2 �x�A���ʁA���@r == 30,45,60


		//----------------------�ގ� �@�@�@�@������ւ�y�̒l�ύX����---------------------
		DrawFormatString(1515, 85, GetColor(255, 255, 255), "���ˑ�y�E�z");

		if (hasyaR.color == true)	DrawFormatString(1515, 160, GetColor(255, 255, 255), "�ԃN���[");
		else 						DrawFormatString(1515, 160, GetColor(255, 255, 255), "�N���["); // X���W���C�`�S�C�`�S�ɂȂ��Ă���@�@<= �₩�܂�����

		if (hasyaR.v == 0)	DrawFormatString(1490, 210, GetColor(255, 255, 255), "�y���x�z�x");
		if (hasyaR.v == 1)	DrawFormatString(1490, 210, GetColor(255, 255, 255), "�y���x�z����");
		if (hasyaR.v == 2)	DrawFormatString(1490, 210, GetColor(255, 255, 255), "�y���x�z��");


		if (hasyaR.r == 0)	DrawFormatString(1490, 270, GetColor(255, 255, 255), "�y�p�x�z30��");
		if (hasyaR.r == 1)	DrawFormatString(1490, 270, GetColor(255, 255, 255), "�y�p�x�z45��");
		if (hasyaR.r == 2)	DrawFormatString(1490, 270, GetColor(255, 255, 255), "�y�p�x�z60��");

		if (hasyaR.zaisitu == false)	DrawFormatString(1490, 330, GetColor(255, 255, 255), "�y�ގ��z�I�t");
		if (hasyaR.zaisitu == true)		DrawFormatString(1490, 330, GetColor(255, 255, 255), "�y�ގ��z�I��");
	}

	if (hasyaLR == false) //�E�̔��ˑ䂪�N���b�N����Ă��遁�@hasya== false

	{
		DrawGraph(0, 0, GraphData[8], true);//����T�u�E�B���h�E
		DrawGraph(0, 0, GraphData[9], true);//�^�񒆂̃��C���E�B���h�E
		SetFontSize(45);

		if (hasyaR.color == true) DrawGraph(0, 0, GraphData[167], true);//�ԁ@�I��������
		if (hasyaR.color == false) DrawGraph(0, 0, GraphData[171], true);//�@�I��������



		//�E�̔��ˑ�I�����̃��C���E�B���h�E�����@color==true �ԃN���[�Afalse==�N���[�@v == 0,1,2 �x�A���ʁA���@r == 30,45,60
		if (hasyaR.color == true) 
		{ 
			DrawFormatString(750, 312, GetColor(255, 255, 255), "�N���[ / "); 
			DrawFormatString(750, 312, GetColor(255, 30, 30), "�@�@�@�@   �ԃN���["); 
		}
		else 
		{
			DrawFormatString(750, 312, GetColor(255, 255, 255), "�@�@�@�@ / �ԃN���["); 
			DrawFormatString(750, 312, GetColor(255, 30, 30), "�N���[");
		}

		if (hasyaR.v == 0) { DrawFormatString(920, 375, GetColor(255, 255, 255), "�@ - ���� - ��");	DrawFormatString(920, 375, GetColor(255, 30, 30), "�x"); }
		if (hasyaR.v == 1) { DrawFormatString(920, 375, GetColor(255, 255, 255), "�x - �@�@ - ��");	DrawFormatString(920, 375, GetColor(255, 30, 30), "�@   ����"); }
		if (hasyaR.v == 2) { DrawFormatString(920, 375, GetColor(255, 255, 255), "�x - ���� - ");   DrawFormatString(920, 375, GetColor(255, 30, 30), "�@   �@     ��"); }


		if (hasyaR.r == 0) { DrawFormatString(920, 445, GetColor(255, 255, 255), "    - 45��- 60��"); DrawFormatString(920, 445, GetColor(255, 30, 30), "30��"); }
		if (hasyaR.r == 1) { DrawFormatString(920, 445, GetColor(255, 255, 255), "30��-     - 60��");   DrawFormatString(920, 445, GetColor(255, 30, 30), "      45��"); }
		if (hasyaR.r == 2) { DrawFormatString(920, 445, GetColor(255, 255, 255), "30��- 45��-     ");   DrawFormatString(920, 445, GetColor(255, 30, 30), "            60��"); }


		//----------------------�ގ� ---------------------
		if (hasyaR.zaisitu == true) {
			DrawFormatString(960, 500, GetColor(255, 255, 255), "�@�@ / �I�t");
			DrawFormatString(960, 500, GetColor(255, 30, 30), "�I��"); 
		}
		else { DrawFormatString(960, 500, GetColor(255, 255, 255), "�I�� / ");		DrawFormatString(960, 500, GetColor(255, 30, 30), "�@�@   �I�t"); }




		//�E�̔��ˑ�I�����̃T�u�E�B���h�E���� color==true �ԃN���[�Afalse==�N���[�@v == 0,1,2 �x�A���ʁA���@r == 30,45,60

		//----------------------�ގ� �@�@�@�@������ւ�y�̒l�ύX����---------------------
		DrawFormatString(50, 85, GetColor(255, 255, 255), "���ˑ�y���z");

		if (hasyaL.color == true)	DrawFormatString(50, 160, GetColor(255, 255, 255), "�ԃN���[");
		else 						DrawFormatString(50, 160, GetColor(255, 255, 255), "�N���[");

		if (hasyaL.v == 0)	DrawFormatString(25, 210, GetColor(255, 255, 255), "�y���x�z�x");
		if (hasyaL.v == 1)	DrawFormatString(25, 210, GetColor(255, 255, 255), "�y���x�z����");
		if (hasyaL.v == 2)	DrawFormatString(25, 210, GetColor(255, 255, 255), "�y���x�z��");


		if (hasyaL.r == 0)	DrawFormatString(25, 270, GetColor(255, 255, 255), "�y�p�x�z30��");
		if (hasyaL.r == 1)	DrawFormatString(25, 270, GetColor(255, 255, 255), "�y�p�x�z45��");
		if (hasyaL.r == 2)	DrawFormatString(25, 270, GetColor(255, 255, 255), "�y�p�x�z60��");

		if (hasyaL.zaisitu == false)	DrawFormatString(25, 330, GetColor(255, 255, 255), "�y�ގ��z�I�t");
		if (hasyaL.zaisitu == true)		DrawFormatString(25, 330, GetColor(255, 255, 255), "�y�ގ��z�I��");
	}


	//�X�R�A�\��

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


	//�h�q�^�[���A�j���[�V�������Ԓ���
	if (animeN <= 77)
	{
		animeN++;
		if (animeN >= 78) {
			animeN = 1000;
		}

	}

	

	DrawGraph(0, -50, AnimData[(animeN + 10)], true);//�h�q�^�[���A�j���[�V�����`��

		GetMousePoint(&mouseX, &mouseY);
		SetFontSize(30);

	if (DebugMode == true)
	{
		

		DrawFormatString(width - 200, 0, GetColor(255, 255, 255), "%s%s", GameSceneName[NowGameScene], "�`�撆");

		DrawFormatString(300, 300, GetColor(255, 255, 255), "�܂���X%d", mouseX);
		DrawFormatString(300, 320, GetColor(255, 255, 255), "�܂���Y%d", mouseY);

		DrawFormatString(100, 100, GetColor(255, 255, 255), "�U���̓_��%f", AtackScore);
		DrawFormatString(100, 110, GetColor(255, 255, 255), "�h�q�̓_��%f", DefenceScore);

		DrawFormatString(1000, 110, GetColor(255, 255, 255), "kumoMove[1] %d", kumoMove[1]);


		/*if (hasyaLR == true)
		{
			DrawFormatString(100, 200, GetColor(0, 0, 0), "���̔��ˑ�N���b�N�ł�");
		}

		if (hasyaLR == false)
		{
			DrawFormatString(100, 200, GetColor(0, 0, 0), "�E�̔��ˑ�N���b�N�ł�");
		}
		
		*/

	}

		
		return;
	}

	// �J�v�Z���^�̒�`
	struct Capsule 
	{
		VECTOR pointA;
		VECTOR pointB;
		float radius;
	};

	// �J�v�Z���^�̏Փ˔���֐�
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

	// 3D��Ԃł̉~��`�悷��֐�
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

	// �J�v�Z����`�悷��֐�
	void DrawCapsule(Capsule capsule, int color) 
	{
		// �J�v�Z���̒[�_�����Ԑ���`��
		DrawLine3D(capsule.pointA, capsule.pointB, color);

		// �J�v�Z���̒[�_�ɉ~��`��
		VECTOR normal = VNorm(VSub(capsule.pointB, capsule.pointA));
		DrawCircle3D(capsule.pointA, capsule.radius, normal, 32, color);
		DrawCircle3D(capsule.pointB, capsule.radius, normal, 32, color);
	}


	// �N���[�̃J�v�Z����`
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
				//�������Ɋi�[����Ă���A�j���[�V�����ȊO�̃f�[�^�����
				for (int i = 0; i < 201; i++) 
				{ 
					DeleteGraph(GraphData[i]); 
				}
				BattleTextureLoad();
				LoadMovie = true;


				// �����_���ɔw�i�摜��I��
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



//�U��������
void AtackInit(void)
{
	Cley1Time = 0;

	//���ˉ\�񐔂̏����l(2��)
	shootCo = 2;

	BreakCrey1 = false;	//�q�b�g�t���O��off
	BreakCrey2 = false;	//�q�b�g�t���O��off

	Cley1.Shooted = false;
	Cley2.Shooted = false;


	if (DebugMode == true)
	{
		DrawFormatString(width - 200, 0, GetColor(255, 255, 255), "%s%s", GameSceneName[ChangeGameScene], "������");

	}

	//���łɓǂݍ��񂾃T�E���h���~
	StopSoundMem(SoundData[7]);

	//���łɓǂݍ��񂾃T�E���h���~
	StopSoundMem(SoundData[8]);


	//-------------[���W�n�̕ϊ�]---------------------
	camPos = VGet(0, 0, 0);    //���_�ɒu��
	camDir = VGet(0, 0, 1.0f); //Z������
	camTop = VGet(0, 1.0f, 0); //����y���K�𖳍C
	//-------------------------------------------------

	
	//==================================================================
	//�ȉ��̒������ //��΂ɏ����ȁI�I�I�I�I�I�I���ɔ�ÁI���O����I�I
	//==================================================================
	
		// ��]( x, y, z����]�̏� )�{���W�ړ��s��̍쐬
	Bullet1TransformMatrix = MGetRotX(Bullet1.Angle.x);
	Bullet1TransformMatrix = MMult(Bullet1TransformMatrix, MGetRotY(Bullet1.Angle.y));
	Bullet1TransformMatrix = MMult(Bullet1TransformMatrix, MGetRotZ(Bullet1.Angle.z));
	Bullet1TransformMatrix = MMult(Bullet1TransformMatrix, MGetTranslate(VGet(Bullet1.Position.x, Bullet1.Position.y, Bullet1.Position.z)));

	// �s����g���ă��[���h���W���Z�o
	Bullet1Vertex[0].pos = VTransform(VGet(-100.0f, 100.0f, 0.0f), Bullet1TransformMatrix);
	Bullet1Vertex[1].pos = VTransform(VGet(100.0f, 100.0f, 0.0f), Bullet1TransformMatrix);
	Bullet1Vertex[2].pos = VTransform(VGet(-100.0f, -100.0f, 0.0f), Bullet1TransformMatrix);
	Bullet1Vertex[3].pos = VTransform(VGet(100.0f, -100.0f, 0.0f), Bullet1TransformMatrix);

	Bullet1Vertex[4].pos = Bullet1Vertex[2].pos;
	Bullet1Vertex[5].pos = Bullet1Vertex[1].pos;

	// �s����g���Ė@�����Z�o
	Bullet1Vertex[0].norm = VTransformSR(VGet(0.0f, 0.0f, -1.0f), Bullet1TransformMatrix);
	Bullet1Vertex[1].norm = Bullet1Vertex[0].norm;
	Bullet1Vertex[2].norm = Bullet1Vertex[0].norm;
	Bullet1Vertex[3].norm = Bullet1Vertex[0].norm;
	Bullet1Vertex[4].norm = Bullet1Vertex[0].norm;
	Bullet1Vertex[5].norm = Bullet1Vertex[0].norm;


	// �Q�|���S�����̒��_�̍��W�Ɩ@���ȊO�̃f�[�^���Z�b�g
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

	//�Q���ڗp


		// ��]( x, y, z����]�̏� )�{���W�ړ��s��̍쐬
	Bullet2TransformMatrix = MGetRotX(Bullet2.Angle.x);
	Bullet2TransformMatrix = MMult(Bullet2TransformMatrix, MGetRotY(Bullet2.Angle.y));
	Bullet2TransformMatrix = MMult(Bullet2TransformMatrix, MGetRotZ(Bullet2.Angle.z));
	Bullet2TransformMatrix = MMult(Bullet2TransformMatrix, MGetTranslate(VGet(Bullet2.Position.x, Bullet2.Position.y, Bullet2.Position.z)));

	// �s����g���ă��[���h���W���Z�o
	Bullet2Vertex[0].pos = VTransform(VGet(-100.0f, 100.0f, 0.0f), Bullet2TransformMatrix);
	Bullet2Vertex[1].pos = VTransform(VGet(100.0f, 100.0f, 0.0f), Bullet2TransformMatrix);
	Bullet2Vertex[2].pos = VTransform(VGet(-100.0f, -100.0f, 0.0f), Bullet2TransformMatrix);
	Bullet2Vertex[3].pos = VTransform(VGet(100.0f, -100.0f, 0.0f), Bullet2TransformMatrix);

	Bullet2Vertex[4].pos = Bullet2Vertex[2].pos;
	Bullet2Vertex[5].pos = Bullet2Vertex[1].pos;

	// �s����g���Ė@�����Z�o
	Bullet2Vertex[0].norm = VTransformSR(VGet(0.0f, 0.0f, -1.0f), Bullet2TransformMatrix);
	Bullet2Vertex[1].norm = Bullet2Vertex[0].norm;
	Bullet2Vertex[2].norm = Bullet2Vertex[0].norm;
	Bullet2Vertex[3].norm = Bullet2Vertex[0].norm;
	Bullet2Vertex[4].norm = Bullet2Vertex[0].norm;
	Bullet2Vertex[5].norm = Bullet2Vertex[0].norm;


	// �Q�|���S�����̒��_�̍��W�Ɩ@���ȊO�̃f�[�^���Z�b�g
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



	//----------�e�̏�����------------------

	//�P����
	Bullet1.Angle.x = 0.0f;
	Bullet1.Angle.y = 0.0f;
	Bullet1.Angle.z = 0.0f;
	Bullet1.Position.x = 0;
	Bullet1.Position.y = 0;
	Bullet1.Position.z = 0;
	Bullet1.IsMoving = false;

	//�Q����
	Bullet2.Angle.x = 0.0f;
	Bullet2.Angle.y = 0.0f;
	Bullet2.Angle.z = 0.0f;
	Bullet2.Position.x = 0;
	Bullet2.Position.y = 0;
	Bullet2.Position.z = 0;
	Bullet2.IsMoving = false;


	BulletSpeed = 500.0f; // �e�e�̈ړ����x



	//�V�[���؂�ւ���̌o�߃t���[������������
	GameSceneFrameCount[ChangeGameScene] = 0;


	animeF = 0;
	animeN = 0;
	animeN2 = 0;


	//==================================
	//�h�q�̃X�e�]�^�X�𔽉f

		//���ˑ�F��

	//y�����ω����邽�߁A�����ȊO�͈ȉ��ň�C�ɏ�����
	Cley1.Position.x = -1300;
	Cley1.Position.z = 300;

	Cley2.Position.x = 1300;
	Cley2.Position.z = 300;


	Cley1.Dir.x = 1;
	Cley1.Dir.z = 1;

	Cley2.Dir.x = -1;
	Cley2.Dir.z = 1;


	//���ˑ�F��
	
		//����
	if (hasyaL.v == 0)	
	{
		Cley1.Speed = 40; //���x40

		if (hasyaL.r == 0)//30���̎���
		{					
			Cley1.Position.y = -100;
			Cley1.Dir.y = 0.9f;
		}		
		else if (hasyaL.r == 1)//45���̎��̈ʒu
		{
			Cley1.Position.y = 0;
			Cley1.Dir.y = 1.0;

		}
		else if (hasyaL.r == 2)//60���̎��̈ʒu
		{
			Cley1.Position.y = 200;
			Cley1.Dir.y = 1.0;

		}
	}
	else if (hasyaL.v == 1)		
	{

		Cley1.Speed = 60;	//����60

		if (hasyaL.r == 0)		//30���̎��̈ʒu
		{
			Cley1.Position.y = -300;
			Cley1.Dir.y = 0.8;

		}
		else if (hasyaL.r == 1)			//45��	�̎��̈ʒu 
		{
			Cley1.Position.y = -150;
			Cley1.Dir.y = 0.9;

		}
		else if (hasyaL.r == 2)		  //60��	�̎��̈ʒu
		{
			Cley1.Position.y = 0;
			Cley1.Dir.y = 1.0;

		}
	}
	else if (hasyaL.v == 2)		//����
	{
		Cley1.Speed = 80;

		if (hasyaL.r == 0)					//30���̎��̈ʒu
		{
			Cley1.Position.y = -400;
			Cley1.Dir.y = 0.8;

		}
		else if (hasyaL.r == 1)		//45��	�̎��̈ʒu 
		{
			Cley1.Position.y = -200;
			Cley1.Dir.y = 0.9;

		}
		else if (hasyaL.r == 2)		 //60��	�̎��̈ʒu
		{
			Cley1.Position.y = 0;
			Cley1.Dir.y = 1.0;

		}
	}

			if (hasyaL.color == true) Cley1.Color = 2; //�Ԃ��I�΂�Ă��ꍇ�AhasyaL.color(bool) = true  ����āA�t���X�r�[�J���[��F��
			else Cley1.Color = 1;

	//----------------------------------------------------------------------------------------------------
	//���ˑ�F�E�@�@
			
	if (hasyaR.v == 0)
	{
		Cley2.Speed = 40; //���x40

		if (hasyaR.r == 0)//30���̎���
		{
			Cley2.Position.y = -100;
			Cley2.Dir.y = 0.9f;
		}
		else if (hasyaR.r == 1)//45���̎��̈ʒu
		{
			Cley2.Position.y = 0;
			Cley2.Dir.y = 1.0;

		}
		else if (hasyaR.r == 2)//60���̎��̈ʒu
		{
			Cley2.Position.y = 200;
			Cley2.Dir.y = 1.0;

		}
	}
	else if (hasyaR.v == 1)
	{

		Cley2.Speed = 60;	//����60

		if (hasyaR.r == 0)		//30���̎��̈ʒu
		{
			Cley2.Position.y = -300;
			Cley2.Dir.y = 0.8;

		}
		else if (hasyaR.r == 1)			//45��	�̎��̈ʒu
		{
			Cley2.Position.y = -150;
			Cley2.Dir.y = 0.9;

		}
		else if (hasyaR.r == 2)		  //60��	�̎��̈ʒu
		{
			Cley2.Position.y = 0;
			Cley2.Dir.y = 1.0;

		}
	}
	else if (hasyaR.v == 2)		//����
	{
		Cley2.Speed = 80;

		if (hasyaR.r == 0)					//30���̎��̈ʒu
		{
			Cley2.Position.y = -400;
			Cley2.Dir.y = 0.8;

		}
		else if (hasyaR.r == 1)		//45��	�̎��̈ʒu
		{
			Cley2.Position.y = -200;
			Cley2.Dir.y = 0.9;

		}
		else if (hasyaR.r == 2)		 //60��	�̎��̈ʒu
		{
			Cley2.Position.y = 0;
			Cley2.Dir.y = 1.0;

		}
	}

	if (hasyaR.color == true) Cley2.Color = 2; //�Ԃ��I�΂�Ă��ꍇ�AhasyaL.color(bool) = true  ����āA�t���X�r�[�J���[��F��
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


	//�E���̃N���C��x���W���Ƃ��Ă����B



	return;
}


//�U���Ǘ�	
void AtackCtrl(void)
{

	AtackProc();
	AtackDraw();

	return;
}


//�U������	
void AtackProc(void)
{
	//��ʑJ�ڗp�_���ێ��ϐ�
	float AtScore_keep = AtackScore;
	float DfScore_keep = DefenceScore;


	MATRIX Mv;//�r���[�s��
	MATRIX Mp;//�Ղ낶�������傎�s��
	MATRIX MvMp; //������Z�������̂�����
	MATRIX InversMvMp;//����̋t�s����Ƃ�B


	//�}�E�X�̈ʒu�����
	GetMousePoint(&mouseX, &mouseY);

	//�J�����̐���
	SetCameraPositionAndTargetAndUpVec(camPos, camDir, camTop);
	SetCameraNearFar(1.0f, 10000.0f);//

	Mv = GetCameraViewMatrix();			//�r���[�s����i�[
	Mp = GetCameraProjectionMatrix();   //�v���W�F�N�V�����s����i�[

	//================================================================
	// �v�Z
	//
	Ps.x = (float)((float)mouseX - (width / 2)) / (width / 2);
	Ps.y = float((height / 2) - (float)mouseY) / (height / 2);
	Ps.z = 0;

	MbMouseX = (float)mouseX - (width / 2);
	MbMouseY = (height / 2) - (mouseY);

	MvMp = MMult(Mp, Mv);
	InversMvMp = MInverse(MvMp);

	//Ps�x�N�g�����r���[�s��ƃv���W�F�N�V�����s��ŕϊ�(?)�@�����@�x�N�g���� 1x4�̍s�� �Ƃ��Ă݂Ȃ���InversMpMv�s��Ə�Z�B
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

			//���N���b�N�̎��AColor�𑓐F�ɁB�����łȂ���΁A�ԐF�Ŕ��ˁB
			if (MousePush(MOUSE_INPUT_LEFT) == true)
			{

				//���ʐݒ�
				ChangeVolumeSoundMem(255 * 45 / 100, SoundData[9]);
				//�e�T�E���h�G�t�F�N�g
				PlaySoundMem(SoundData[9], DX_PLAYTYPE_BACK, true);

				//���˂̕���������
				GunDir1.x = GunKari.x / GunKariSq;
				GunDir1.y = GunKari.y / GunKariSq;
				GunDir1.z = GunKari.z / GunKariSq;

				//Bullet1�������Ă����ԂƂ���B
				Bullet1.IsMoving = true;
				Bullet1.Color = 1; // 1 => ��
				Bullet1.StartTime = GetNowCount();


			}
			else if (MousePush(MOUSE_INPUT_RIGHT) == true)
			{
				//���ʐݒ�
				ChangeVolumeSoundMem(255 * 45 / 100, SoundData[9]);
				//�e�T�E���h�G�t�F�N�g
				PlaySoundMem(SoundData[9], DX_PLAYTYPE_BACK, true);

				//���˂̕���������
				GunDir1.x = GunKari.x / GunKariSq;
				GunDir1.y = GunKari.y / GunKariSq;
				GunDir1.z = GunKari.z / GunKariSq;

				//Bullet1�������Ă����ԂƂ���B
				Bullet1.IsMoving = true;
				Bullet1.Color = 2; // 2 => ��
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

			if (GetNowCount() - Bullet1.StartTime > 3000)//������Ԃɖ߂�
			{
				Bullet1.Position.x = 0;
				Bullet1.Position.y = 0;
				Bullet1.Position.z = 0;
				Bullet1.IsMoving = false;
			}

		}

		//�Q����
		if (Bullet2.IsMoving != true && shootCo == 1)
		{

			//���N���b�N�̎��AColor�𑓐F�ɁB�����łȂ���΁A�ԐF�Ŕ��ˁB
			if (MousePush(MOUSE_INPUT_LEFT) == true)
			{
				//���ʐݒ�
				ChangeVolumeSoundMem(255 * 45 / 100, SoundData[9]);
				//�e�T�E���h�G�t�F�N�g
				PlaySoundMem(SoundData[9], DX_PLAYTYPE_BACK, true);

				//���˂̕���������
				GunDir2.x = GunKari.x / GunKariSq;
				GunDir2.y = GunKari.y / GunKariSq;
				GunDir2.z = GunKari.z / GunKariSq;

				//Bullet1�������Ă����ԂƂ���B
				Bullet2.IsMoving = true;
				Bullet2.Color = 1; // 1 => ��
				Bullet2.StartTime = GetNowCount();


			}
			else if (MousePush(MOUSE_INPUT_RIGHT) == true)
			{
				//���ʐݒ�
				ChangeVolumeSoundMem(255 * 45 / 100, SoundData[9]);
				//�e�T�E���h�G�t�F�N�g
				PlaySoundMem(SoundData[9], DX_PLAYTYPE_BACK, true);

				//���˂̕���������
				GunDir2.x = GunKari.x / GunKariSq;
				GunDir2.y = GunKari.y / GunKariSq;
				GunDir2.z = GunKari.z / GunKariSq;

				//Bullet1�������Ă����ԂƂ���B
				Bullet2.IsMoving = true;
				Bullet2.Color = 2; // 2 => ��
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

		if (GetNowCount() - Bullet1.StartTime > 3000)//������Ԃɖ߂�
		{
			Bullet2.Position.x = 0;
			Bullet2.Position.y = 0;
			Bullet2.Position.z = 0;
			Bullet2.IsMoving = false;
		}

	}






	// �N���[�̔��a��ݒ�
	float FrisbeeRadius = 300.0f; // �N���[�̓����蔻��̔��a��ݒ�

	// �e�e�̔��a��ݒ�
	float BulletRadius = 200.0f; // �e�e�̓����蔻��̔��a��ݒ�


	if (animeN >= 1050)//�A�j���[�V�����I����
	{
		// �N���[�i�t���X�r�[�j�̏����ʒu�Ƒ��x��ݒ�
		void InitializeFrisbee();
		{

			if (Cley1.Shooted == false)
			{
				// �X�y�[�X�L�[�������āA�t���X�r�[�̈ʒu���Ԃ�����������B	Moving��true�̂��߁A���Updata()�֐��ŃN���C������
				if (KeyPush(KEY_INPUT_SPACE) == true)
				{
					Cley1.IsMoving = true;
					Cley1.StartTime = GetNowCount();
					//FrisbeeVelocity1 = VGet(FrisbeeSpeed, 60, FrisbeeSpeed);// �����x�ݒ�
					Cley1.Velocity.x = Cley1.Dir.x * Cley1.Speed;
					Cley1.Velocity.y = Cley1.Dir.y * Cley1.Speed;
					Cley1.Velocity.z = Cley1.Dir.z * Cley1.Speed;

					frisbeeCapsule1.pointA = Cley1.Position;
					frisbeeCapsule1.pointB = VAdd(Cley1.Position, VScale(Cley1.Velocity, 0.1f)); // �����𒲐�
					frisbeeCapsule1.radius = FrisbeeRadius; // �J�v�Z���̔��a��ݒ�

					//���ʐݒ�
					ChangeVolumeSoundMem(255 * 45 / 100, SoundData[9]);
					//�N���C�T�E���h�G�t�F�N�g
					PlaySoundMem(SoundData[11], DX_PLAYTYPE_BACK, true);

					Cley1.Shooted = true;

				}
			}

			if (Cley1.Shooted == true) Cley1Time +=  1 * fps.deltaTime;

			if (Cley1Time >= 1 && Cley2.Shooted != true) Cley2.Shooted = true;

			
			if (Cley2.Shooted == true && Cley2.IsMoving != true && Cley2.Break != true)		//�E���̃N���C�B�@���������˂��ꂽ��An�b��ɔ��˂���B
			{
				Cley2.IsMoving = true;
				Cley2.StartTime = GetNowCount();
				//FrisbeeVelocity2 = VGet(FrisbeeSpeed, 60, FrisbeeSpeed);// �����x�ݒ�
				Cley2.Velocity.x = Cley2.Dir.x * Cley2.Speed;
				Cley2.Velocity.y = Cley2.Dir.y * Cley2.Speed;
				Cley2.Velocity.z = Cley2.Dir.z * Cley2.Speed;

				frisbeeCapsule2.pointA = Cley2.Position;
				frisbeeCapsule2.pointB = VAdd(Cley2.Position, VScale(Cley2.Velocity, 0.1f)); // �����𒲐�
				frisbeeCapsule2.radius = FrisbeeRadius; // �J�v�Z���̔��a��ݒ�

				//���ʐݒ�
				ChangeVolumeSoundMem(255 * 45 / 100, SoundData[9]);
				//�N���C�T�E���h�G�t�F�N�g
				PlaySoundMem(SoundData[11], DX_PLAYTYPE_BACK, true);


				
				/*
				IsFrisbeeMoving2 = true;
				FrisbeeStartTime2 = GetNowCount();
				FrisbeeVelocity2 = VGet(FrisbeeSpeed, 60, FrisbeeSpeed);// �����x�ݒ�
				frisbeeCapsule2.pointA = FrisbeePosition2;
				frisbeeCapsule2.pointB = VAdd(FrisbeePosition2, VScale(FrisbeeVelocity2, 0.1f)); // �����𒲐�
				frisbeeCapsule2.radius = FrisbeeRadius; // �J�v�Z���̔��a��ݒ�
				*/

					
						
							

			}
			




		}

		void UpdateFrisbee();
		{
			if (Cley1.IsMoving)
			{
				float t = (GetNowCount() - Cley1.StartTime) / 1000.0f;	//�N���C�̓����̍X�V
				Cley1.Velocity.y -= Gravity * t;	//�d�͂ɂ�����
				Cley1.Position = VAdd(Cley1.Position, Cley1.Velocity);	//���x�Ɋ�Â����ʒu�̍X�V(�ړ�)
				Cley1.Velocity.x *= 0.99f;	//��C��R
				Cley1.Velocity.z *= 0.99f;	//��C��R

				// �J�v�Z���̍X�V
				frisbeeCapsule1.pointA = Cley1.Position;
				frisbeeCapsule1.pointB = VAdd(Cley1.Position, VScale(Cley1.Velocity, 0.1f));

				if (GetNowCount() - Cley1.StartTime > 6000) {
					Cley1.IsMoving = false;
				}
			}

			
			//�N���C���
			if (Cley2.IsMoving)
			{
				float t = (GetNowCount() - Cley2.StartTime) / 1000.0f;	//�N���C�̓����̍X�V
				Cley2.Velocity.y -= Gravity * t;	//�d�͂ɂ�����
				Cley2.Position = VAdd(Cley2.Position, Cley2.Velocity);	//���x�Ɋ�Â����ʒu�̍X�V(�ړ�)
				Cley2.Velocity.x *= 0.99f;	//��C��R
				Cley2.Velocity.z *= 0.99f;	//��C��R

				// �J�v�Z���̍X�V
				frisbeeCapsule2.pointA = Cley2.Position;
				frisbeeCapsule2.pointB = VAdd(Cley2.Position, VScale(Cley2.Velocity, 0.1f));

				if (GetNowCount() - Cley2.StartTime > 6000) {
					Cley2.IsMoving = false;
				}



			}
			


		}
	}




	//�e1,2�̍s��̐�����
	{

		// ��]( x, y, z����]�̏� )�{���W�ړ��s��̍쐬
		Bullet1TransformMatrix = MGetRotX(Bullet1.Angle.x);
		Bullet1TransformMatrix = MMult(Bullet1TransformMatrix, MGetRotY(Bullet1.Angle.y));
		Bullet1TransformMatrix = MMult(Bullet1TransformMatrix, MGetRotZ(Bullet1.Angle.z));
		Bullet1TransformMatrix = MMult(Bullet1TransformMatrix, MGetTranslate(VGet(Bullet1.Position.x, Bullet1.Position.y, Bullet1.Position.z)));

		// �s����g���ă��[���h���W���Z�o
		Bullet1Vertex[0].pos = VTransform(VGet(-100.0f, 100.0f, 0.0f), Bullet1TransformMatrix);
		Bullet1Vertex[1].pos = VTransform(VGet(100.0f, 100.0f, 0.0f), Bullet1TransformMatrix);
		Bullet1Vertex[2].pos = VTransform(VGet(-100.0f, -100.0f, 0.0f), Bullet1TransformMatrix);
		Bullet1Vertex[3].pos = VTransform(VGet(100.0f, -100.0f, 0.0f), Bullet1TransformMatrix);

		Bullet1Vertex[4].pos = Bullet1Vertex[2].pos;
		Bullet1Vertex[5].pos = Bullet1Vertex[1].pos;

		// �s����g���Ė@�����Z�o
		Bullet1Vertex[0].norm = VTransformSR(VGet(0.0f, 0.0f, -1.0f), Bullet1TransformMatrix);
		Bullet1Vertex[1].norm = Bullet1Vertex[0].norm;
		Bullet1Vertex[2].norm = Bullet1Vertex[0].norm;
		Bullet1Vertex[3].norm = Bullet1Vertex[0].norm;
		Bullet1Vertex[4].norm = Bullet1Vertex[0].norm;
		Bullet1Vertex[5].norm = Bullet1Vertex[0].norm;

		//�Q����
	// ��]( x, y, z����]�̏� )�{���W�ړ��s��̍쐬
		Bullet2TransformMatrix = MGetRotX(Bullet2.Angle.x);
		Bullet2TransformMatrix = MMult(Bullet2TransformMatrix, MGetRotY(Bullet2.Angle.y));
		Bullet2TransformMatrix = MMult(Bullet2TransformMatrix, MGetRotZ(Bullet2.Angle.z));
		Bullet2TransformMatrix = MMult(Bullet2TransformMatrix, MGetTranslate(VGet(Bullet2.Position.x, Bullet2.Position.y, Bullet2.Position.z)));

		// �s����g���ă��[���h���W���Z�o
		Bullet2Vertex[0].pos = VTransform(VGet(-100.0f, 100.0f, 0.0f), Bullet2TransformMatrix);
		Bullet2Vertex[1].pos = VTransform(VGet(100.0f, 100.0f, 0.0f), Bullet2TransformMatrix);
		Bullet2Vertex[2].pos = VTransform(VGet(-100.0f, -100.0f, 0.0f), Bullet2TransformMatrix);
		Bullet2Vertex[3].pos = VTransform(VGet(100.0f, -100.0f, 0.0f), Bullet2TransformMatrix);

		Bullet2Vertex[4].pos = Bullet2Vertex[2].pos;
		Bullet2Vertex[5].pos = Bullet2Vertex[1].pos;

		// �s����g���Ė@�����Z�o
		Bullet2Vertex[0].norm = VTransformSR(VGet(0.0f, 0.0f, -1.0f), Bullet2TransformMatrix);
		Bullet2Vertex[1].norm = Bullet2Vertex[0].norm;
		Bullet2Vertex[2].norm = Bullet2Vertex[0].norm;
		Bullet2Vertex[3].norm = Bullet2Vertex[0].norm;
		Bullet2Vertex[4].norm = Bullet2Vertex[0].norm;
		Bullet2Vertex[5].norm = Bullet2Vertex[0].norm;
	}



	//=======================================================================================

	//�e�P�ƃN���C1�̓����蔻��
	if (Cley1.IsMoving && Bullet1.IsMoving && BreakCrey1 != true) 
	{
		if (CheckCapsuleCollision(frisbeeCapsule1, Bullet1.Position, BulletRadius)) 
		{

			if (Cley1.Color == Bullet1.Color)
			{

				Cley1.BreakPosition = Cley1.Position; //��ꂽ�ꏊ���L�^
				Cley1.Break = 1;//�P����ꂽ��Ԃ�=1�ł���

				CollisionDisplayStartTime = GetNowCount(); // �Փ˂������������Ԃ��L�^
				Cley1.IsMoving = false;
				Bullet1.IsMoving = false;
				Bullet1.Position = VGet(0, 0, 0);
				Cley1.Position = VGet(0, 0, 0);
				BreakCrey1 = true;
			}
			//PlaySoundMem(CollisionSoundHandle, DX_PLAYTYPE_BACK);
		}
	}

	//�e�Q�ƃN���C1�̔���
	if (Cley1.IsMoving && Bullet2.IsMoving && BreakCrey1 != true)
	{
		if (CheckCapsuleCollision(frisbeeCapsule1, Bullet2.Position, BulletRadius))
		{

			if (Cley1.Color == Bullet2.Color)
			{

				Cley1.BreakPosition = Cley1.Position; //2��ꂽ�ꏊ���L�^
				Cley1.Break = 1;//2����ꂽ��Ԃ�=1�ł���

				CollisionDisplayStartTime = GetNowCount(); // �Փ˂������������Ԃ��L�^
				Cley1.IsMoving = false;
				Bullet2.IsMoving = false;
				Bullet2.Position = VGet(0, 0, 0);
				Cley1.Position = VGet(0, 0, 0);
				BreakCrey1 = true;
			}
			//PlaySoundMem(CollisionSoundHandle, DX_PLAYTYPE_BACK);
		}
	}



	

//�e�P�ƃN���C2�̓����蔻��
if (Cley2.IsMoving && Bullet1.IsMoving && BreakCrey2 != true)
{
	if (CheckCapsuleCollision(frisbeeCapsule2, Bullet1.Position, BulletRadius))
	{

		if (Cley2.Color == Bullet1.Color)
		{

			Cley2.BreakPosition = Cley2.Position; //��ꂽ�ꏊ���L�^
			Cley2.Break = 1;//�P����ꂽ��Ԃ�=1�ł���
			CollisionDisplayStartTime = GetNowCount(); // �Փ˂������������Ԃ��L�^
			Cley2.IsMoving = false;
			Bullet1.IsMoving = false;
			Bullet1.Position = VGet(0, 0, 0);
			Cley2.Position = VGet(0, 0, 0);
			BreakCrey2 = true;
		
		}
		//PlaySoundMem(CollisionSoundHandle, DX_PLAYTYPE_BACK);
	}
}


//�e�Q�ƃN���C�Q�̔���
if (Cley2.IsMoving && Bullet2.IsMoving && BreakCrey2 != true)
{
	if (CheckCapsuleCollision(frisbeeCapsule2, Bullet2.Position, BulletRadius))
	{

		if (Cley2.Color == Bullet2.Color)
		{

			Cley2.BreakPosition = Cley2.Position; //��ꂽ�ꏊ���L�^
			Cley2.Break = 1;//�P����ꂽ��Ԃ�=1�ł���

			CollisionDisplayStartTime = GetNowCount(); // �Փ˂������������Ԃ��L�^
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
	}//�������Ă���̉���A�j���[�V����1

	if (Cley2.Break == 1) {
		Cley2.BreakMoveYgravity++;
		Cley2.BreakMoveX++;
		Cley2.BreakMoveY -= 30 - (2 * Cley2.BreakMoveYgravity);
	}//�������Ă���̉���A�j���[�V����1
	


	kumoMove[1] += 1;
	kumoMove[0] += 1;

	if (kumoMove[0] > -620 && kumoMove[0] < -610) kumoMove[1] = -1920;
	if (kumoMove[1] > -200 && kumoMove[1] < -190) kumoMove[0] = -1770;






//---------------------------------------------------------------------------


	if (BreakCrey1 == true)Cley1.Position = VGet(0, 0, -10);	//�N���C1���j�󂳂ꂽ�ꍇ�A�ʒu��(0, 0, -10)�ɌŒ肵�A���x���������ē��_���o�O������`�悳�ꂽ�肵�Ȃ��悤�ɂ���
	//if (BreakCrey2 == true)FrisbeePosition2 = VGet(0, 0, -10);	//�N���C�Q�����l

	//========================================================================================


	//�f�o�b�O�p�̃R�[�h
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

	//else if (Cley1.Position.y < -3000 && Cley1.IsMoving == true) DefenceScore++;	//�N���C����ʉ��ɍs�����Ƃ��h�q���ɉ��_�B

	//if (BreakCrey1 == true  && IsFrisbeeMoving1 == true)	AtackScore++;	//�j�󂳂ꂽ�Ƃ��A�^�b�N�ɉ��_
	if (Cley1.BreakMoveX >  70 && Cley2.BreakMoveX > 70)	AtackScore++;//�j�󂳂ꂽ�Ƃ��A�^�b�N�ɉ��_�B

	if (Cley1.BreakMoveX > 70)
	{
		if (Cley2.Position.y < -3000 && Cley2.Break != true)	//�N���C�P���j�󂳂ꂽ��ԂŁA�N���C�Q����ʊO�ɒ��񂾎��A���҂�0.5�_
		{
			DefenceScore += 0.5f;
			AtackScore += 0.5f;
		}
	}
	else if (Cley2.BreakMoveX > 70)
	{
		if (Cley1.Position.y < -3000 && Cley1.IsMoving == true)	//�N���C�Q���j�󂳂ꂽ���A�N���C�P����ʉ��ɒ��񂾎��A���҂ɉ��_0.5
		{
			DefenceScore += 0.5f;
			AtackScore += 0.5f;
		}
	}

	if (Cley2.Break != true && Cley1.Break != true)	//���҂Ƃ��ɔj�󂳂�Ă��炸�A���҂Ƃ��ɉ�ʉ��ɒ��񂾏ꍇ�A�h�q��1�_���_
	{
		if (Cley2.Position.y < -3000 && Cley1.Position.y < -3000)
		{
			DefenceScore++;
		}

	}





	
	//if (BreakCrey1 == true  && BreakCrey2 == true)	AtackScore++;						//��Ƃ��j�󂳂ꂽ�Ƃ��A�^�b�N�ɉ��_
	
	//if (BreakCrey1 = true && FrisbeePosition2.y < -3000)	DefenceScore++;				//�N���C�P���j�󂳂ꂽ���A�Q����ʉ��ɍs�������ߖh�q�ɉ��_
	//if (BreakCrey2 = true && FrisbeePosition1.y < -3000)	DefenceScore++;				//�N���C2���j�󂳂ꂽ���A1����ʉ��ɍs�������ߖh�q�ɉ��_
	
	//if (FrisbeePosition1.y < -3000 && FrisbeePosition2.y < -3000)	DefenceScore++;		//�N���C�Q�ƃN���C�P�̗�������ʉ��Ɍ��������ߖh�q�ɉ��_�B


	
	//-------------------------------------------------
	//�ǂ��炩�ɓ_�����������ꍇ�A�h�q�ɉ�ʑJ��	(�P�_����A��������0.5�_����B)

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
	


	
		//�ܓ_�擾���Ƀ��U���g�ɑJ��
			if (AtackScore >= WinScore || DefenceScore >= WinScore)
			{

				ChangeGameScene = ResultScene;

				return;
			}









	return;
}


//�U���`��	
void AtackDraw(void)
{


	// �I�����ꂽ�w�i�摜�̕`��
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

	DrawString(0, 480, "SPACE�L�[:�N���C���΂�", GetColor(255, 255, 255));

	DrawGraph(0, -50, AnimData[animeN + 78], true);

	if (DebugMode == true)
	{
		SetUseLighting(FALSE);

		DrawFormatString(width - 200, 0, GetColor(255, 255, 255), "%s%s", GameSceneName[NowGameScene], "�`�撆");

		if (Bullet2.IsMoving == true) DrawFormatString(500, 500, GetColor(255, 255, 255), "%s%s", GameSceneName[NowGameScene], "Bullet2true");
		if (Bullet2.IsMoving != true) DrawFormatString(500, 500, GetColor(255, 255, 255), "%s%s", GameSceneName[NowGameScene], "Bullet2false");

		if (Bullet1.IsMoving == true) DrawFormatString(500, 800, GetColor(255, 255, 255), "%s%s", GameSceneName[NowGameScene], "Bullet1true");
		if (Bullet1.IsMoving != true) DrawFormatString(500, 800, GetColor(255, 255, 255), "%s%s", GameSceneName[NowGameScene], "Bullet1false");


		DrawFormatString(100, 100, GetColor(255, 255, 255), "�U���̓_��%f", AtackScore);
		DrawFormatString(100, 110, GetColor(255, 255, 255), "�h�q�̓_��%f", DefenceScore);



		// ��ʂɃp�����[�^��\��
		//DrawFormatString(0, 0, GetColor(255, 255, 255), "x:%.3f y:%.3f z:%.3f", Angle.x, Angle.y, Angle.z);
		//DrawString(0, 460, "S�L�[:�O�i", GetColor(255, 255, 255));
		DrawFormatString(0, 700, GetColor(255, 255, 255), "shootco:%d", shootCo);



		DrawFormatString(0, 600, GetColor(255, 255, 255), "PosX:%f\nPosY:%f\nPosZ%n", Cley1.Position.x, Cley1.Position.y, Cley1.Position.z);

		// �J�v�Z����`��
		DrawCapsule(frisbeeCapsule1, GetColor(255, 0, 0));
		DrawCapsule(frisbeeCapsule2, GetColor(255, 0, 0));

		//if(Cley2.Shooted == true)DrawFormatString(0, 500, GetColor(255, 0, 0), "�N���C�P���˂�aaaaaaaaaaaaaaaaaaaaaaaa�I");


	// �Փ˃��b�Z�[�W�̕\��
		if (CollisionDisplayStartTime != -1 && GetNowCount() - CollisionDisplayStartTime < 2000)
		{
			DrawFormatString(0, 500, GetColor(255, 0, 0), "�Փˌ��o�I");


		}
	}


	// �Q�|���S���̕`��
		//DrawPolygon3D(Bullet1Vertex, 2, GraphData[173], TRUE);




		// �e�̕`��
		if (Bullet1.Color == 1) DrawPolygon3D(Bullet1Vertex, 2, GraphData[173], TRUE);
		else if (Bullet1.Color == 2)DrawPolygon3D(Bullet1Vertex, 2, GraphData[174], true);

		if (Bullet2.Color == 1) DrawPolygon3D(Bullet2Vertex, 2, GraphData[173], TRUE);
		else if (Bullet2.Color == 2)DrawPolygon3D(Bullet2Vertex, 2, GraphData[174], true);


		//�ގ����Ƃ̕\��1
		if (Cley1.IsMoving)
		{
			//�E�ԃN���[�ω�
			if (Cley1.Color == 2)
			{
				DrawExtendGraph(150 * 10, 150 * 10, 150 * 10, 150 * 10, GraphData[202], TRUE);
				if (hasyaL.zaisitu == true)DrawRotaGraph3D(Cley1.Position.x, Cley1.Position.y, Cley1.Position.z, 1.0, Cley1.Angle.x, GraphData[202 + SelectedBackgroundIndex], TRUE, FALSE);
				else 	DrawRotaGraph3D(Cley1.Position.x, Cley1.Position.y, Cley1.Position.z, 1.0, Cley1.Angle.x, GraphData[175], TRUE, FALSE);

			}

			//���N���[�ω�
			if (Cley1.Color == 1)
			{
				if (hasyaL.zaisitu == true) DrawRotaGraph3D(Cley1.Position.x, Cley1.Position.y, Cley1.Position.z, 1.0, Cley1.Angle.x, GraphData[206 + SelectedBackgroundIndex], TRUE, FALSE);
				else    DrawRotaGraph3D(Cley1.Position.x, Cley1.Position.y, Cley1.Position.z, 1.0, Cley1.Angle.x, GraphData[176], TRUE, FALSE);
			}
		}

		//�ގ����Ƃ̕\��2
		if (Cley2.IsMoving)
		{
			//�E�ԃN���[�ω�
			if (Cley2.Color == 2)
			{
				if (hasyaR.zaisitu == true)DrawRotaGraph3D(Cley2.Position.x, Cley2.Position.y, Cley2.Position.z, 1.0, Cley2.Angle.x, GraphData[202 + SelectedBackgroundIndex], TRUE, FALSE);
				else 	DrawRotaGraph3D(Cley2.Position.x, Cley2.Position.y, Cley2.Position.z, 1.0, Cley2.Angle.x, GraphData[175], TRUE, FALSE);

			}

			//���N���[�ω�
			if (Cley2.Color == 1)
			{
				if (hasyaR.zaisitu == true) DrawRotaGraph3D(Cley2.Position.x, Cley2.Position.y, Cley2.Position.z, 1.0, Cley2.Angle.x, GraphData[206 + SelectedBackgroundIndex], TRUE, FALSE);
				else    DrawRotaGraph3D(Cley2.Position.x, Cley2.Position.y, Cley2.Position.z, 1.0, Cley2.Angle.x, GraphData[176], TRUE, FALSE);
			}
		}








		/*
		// �t���X�r�[�̕`��
		if (Cley1.IsMoving)
		{
			if (Cley1.Color == 1)DrawRotaGraph3D(Cley1.Position.x, Cley1.Position.y, Cley1.Position.z, 1.0, Cley1.Angle.x, GraphData[176], TRUE, FALSE);
			if (Cley1.Color == 2)DrawRotaGraph3D(Cley1.Position.x, Cley1.Position.y, Cley1.Position.z, 1.0, Cley1.Angle.x, GraphData[175], TRUE, FALSE);
		}

		// �t���X�r�[�̕`��
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


		//�u���C�N���o�`��
		
		
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
		


		//score��
		
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

		// �}�E�X�J�[�\���ʒu�ɉ摜��`��
		DrawExtendGraph(mouseX - newWidth / 2, mouseY - newHeight / 2, mouseX + newWidth / 2, mouseY + newHeight / 2, GraphData[172], TRUE);


	return;
}


//���U���g������
void ResultInit(void)
{
	if (DebugMode == true)
	{
	
		DrawFormatString(width - 200, 0, GetColor(255, 255, 255), "%s%s", GameSceneName[ChangeGameScene], "������");
	
	
	}

	//���łɓǂݍ��񂾃T�E���h���~
	StopSoundMem(SoundData[8]);

	for (int i = 0; i < 201; i++) { DeleteGraph(GraphData[i]); }
	ResultTextureLoad();


		//���ʐݒ�
	ChangeVolumeSoundMem((255 * 20 / 100) / SoundVolume, SoundData[10]);

	//���[�v�ʒu�̕ύX�����ꂪ�Ȃ��ƃv���O����������(�L;��;�M)
	SetLoopPosSoundMem(0, SoundData[10]);


	PlaySoundMem(SoundData[10], DX_PLAYTYPE_BACK, FALSE);



	debugGraph = 0;

	ResultState = 0;

	//�V�[���؂�ւ���̌o�߃t���[������������
	GameSceneFrameCount[ChangeGameScene] = 0;

	LoadMovie = false;

	return;
}



//���U���g�Ǘ�
void ResultCtrl(void)
{

	ResultProc();
	ResultDraw();


	return;
}



//���U���g����
void ResultProc(void)
{

		//�X�y�[�X�L�[�������ꂽ�Ƃ�

	GetMousePoint(&mouseX, &mouseY);

		//�V�[��������
		//TitleInit();


	if (SetUI(40, 872, 422, 872, 40, 1060, 422, 1060) == true && MousePush(MOUSE_INPUT_LEFT) == true)
	{//�V�[���؂�ւ�
		ChangeGameScene = MainScene;


		LoadMovie = false;

		//�����ɐ؂�ւ���
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




//���U���g�`��
void ResultDraw(void)
{

	DrawGraph(0, 0, GraphData[3], true); //�w�i


	//�U�����h�q�����_�������āA�U�������������ꍇ
	if (AtackScore > DefenceScore && AtackScore >= WinScore)
	{
		if (solo == false) {
			DrawGraph(0, 0, GraphData[1], false); //�w�i A Win
			DrawGraph(0, UIanime[4], GraphData[14], true); //�w�i A Win
		}

		if (solo == true) {
			DrawGraph(0, 0, GraphData[8], false); //�w�i A Win
			DrawGraph(0, UIanime[4], GraphData[13], true); //�w�i A Win
		}

		for (int i = 0; i <= 4; i++)
		{
			DrawGraph(-40 + (i * 170), 0, GraphData[2], true); //�`�F�b�N�}�[�N�\��
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
	else if (DefenceScore > AtackScore && DefenceScore >= WinScore)	//�h�q���U�����������A�h�q�����������ꍇ�B
	{
		if (solo == false) {
			DrawGraph(0, 0, GraphData[0], false); //�w�i D Win
			DrawGraph(0, UIanime[4], GraphData[11], true); //�w�i D Win
		}

		if (solo == true) {
			DrawGraph(0, 0, GraphData[7], false); //�w�i D Win
			DrawGraph(0, UIanime[4], GraphData[12], true); //�w�i D Win
		}

		for (int i = 0; i <= 4; i++)
		{
			DrawGraph(-40 + (i * 170), 0, GraphData[2], true);
		}

		//for (int i = 0; i <= AtScore; i++)
		for (int i = 0; i <= AtackScore - 1; i++)
		{
			DrawGraph(580 + (i * 170), 180, GraphData[2], true); //�`�F�b�N�}�[�N
		}

		SetFontSize(100);
		DrawFormatString(1600, 780, GetColor(255, 255, 255), "%0.1lf", AtackScore);

		SetFontSize(200);
		DrawFormatString(750, 480, GetColor(255, 255, 255), "%0.1lf", DefenceScore);
		SetFontSize(15);
	}

	else if (DefenceScore == AtackScore)
	{

		//�h���[���w�i
		if (solo == false) DrawGraph(0, 0, GraphData[5], false); //�w�i A Win
		if (solo == true) DrawGraph(0, 0, GraphData[9], false); //�w�i A Win

		DrawGraph(0, UIanime[4], GraphData[10], true);

		SetFontSize(150);
		DrawFormatString(1370, 640, GetColor(255, 255, 255), "%0.1lf", AtackScore);
		DrawFormatString(560, 640, GetColor(255, 255, 255), "%0.1lf", DefenceScore);
		SetFontSize(15);
	}

	 
	DrawGraph(0-1350, 100,GraphData[4], true); //�w�i
	if (SetUI(40, 872, 422, 872, 40, 1060, 422, 1060)) {
		DrawGraph(0 - 1350, 100, GraphData[6], true); //�w�i
	}



	if (DebugMode == true)
	{
		DrawFormatString(width - 200, 0, GetColor(255, 255, 255), "%s%s", GameSceneName[NowGameScene], "�`�撆");

		DrawFormatString(100, 100, GetColor(0, 0, 0), "�U���̓_��%d", AtackScore);
		DrawFormatString(100, 110, GetColor(0, 0, 0), "�h�q�̓_��%d", DefenceScore);


		DrawFormatString(100, 300, GetColor(0, 0, 0), "�}�E�X��x%d", mouseX);
		DrawFormatString(100, 330, GetColor(0, 0, 0), "�}�E�X��y%d", mouseY);

	}



	return;
}



