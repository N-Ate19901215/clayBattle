#include "DxLib.h"
#include "Fps.h"
#include "Game.h"
#include "Keyboad.h"
#include "Mouse.h"
#include "LoadSorce.h"









int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{



	ChangeWindowMode(true);  //�E�B���h�E�\�����[�h

	SetGraphMode(width, height, bit);	//�𑜓x�w��

	SetWindowSize(width, height);  //�E�B���h�E�T�C�Y

	SetMainWindowText("CreyShooting");   //�E�B���h�E��(�Q�[����)

	//SetBackgroundColor(0, 0, 0);

	SetWaitVSyncFlag(GameVsync);

	//SetAlwaysRunFlag(true);




	//-------------------------------������-------------------------------------------------


	//DX���C�u�����̏�����
	if (DxLib_Init() == -1) return -1;

	//����ʂɕ`�悷��(�_�u���o�b�t�@�����O�p)
	SetDrawScreen(DX_SCREEN_BACK);


	//FPS�̏�����
	FPSInit();




	

	//�^�C�g���̏�����
	TitleInit();

	//�ŏ��ɓǂݍ��܂��V�[��(�^�C�g��)
	NowGameScene = TitleScene;

	ChangeGameScene = TitleScene;



	//�L�[���͂̏�����
	KeyInit();

	//�}�E�X���͂̏�����
	MouseInit();


	AnimDataLoad();
	SoundLoad();


	//----------------------------------------------------------------------------------------





	//�Q�[�����[�v
	while (true)
	{



		//���b�Z�[�W����
		if (ProcessMessage() != 0)
		{
			break;
		}//�������[�v���甲���o��(�Q�[���I��)




		//ESC���������Ƃ��A�����I��
		if (KeyClick(KEY_INPUT_ESCAPE) == true)
		{
			break;
		}
	
	


		//��ʂ��N���A����
		if (ClearDrawScreen() != 0)
		{

			break;
		}


		//�Q�[��������
		{


			//fps�v��
			FPSCheck();

			//�L�[�����̍X�V
			KeyUpdate();

			//�}�E�X�����̍X�V
			MouseUpdate();





			//���̃V�[����������
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

				//�V�[���؂�ւ���̃V�[�������݂̃V�[���ɂ���
				NowGameScene = ChangeGameScene;


			}


			//�V�[���؂�ւ�
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



			//fps�\��
			FPSDraw();




			//fps�ҋ@
			FPSWait();



		}


		ScreenFlip();
		
	
	
	
	}










	//�A�v���P�[�V�����I�����ɁA�������[�Ɋi�[���ꂽ�摜�Ɖ��̑S�Ẵf�[�^���������
	Releace();


	//�I��
	DxLib_End();






	return 0;
}