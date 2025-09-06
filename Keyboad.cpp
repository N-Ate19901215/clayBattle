//�L�[���͂̃\�[�X�t�@�C��


#include "Keyboad.h"





//----------�O���[�o���ϐ�--------------------

//���݂̃L�[�������Ă���t���[����
int NowKeyPressFrame[KeyKindMax];

//�ЂƂO�̃L�[�������Ă���t���[����
int OldKeyPressFrame[KeyKindMax];







//���͏����̏�����
void KeyInit(void)
{

	//�z��̏�����
	for (int i = 0; i < KeyKindMax; i++)
	{
		NowKeyPressFrame[i] = 0;
		OldKeyPressFrame[i] = 0;
	}

	return;
}




//���͏����̍X�V
void KeyUpdate(void)
{
	//�ꎞ�I�ɕێ�����L�[���
	char KeyState[KeyKindMax];

	//�S�ẴL�[�̏�Ԃ���x�Ɋm�F
	GetHitKeyStateAll(&KeyState[0]);

	//�L�[�����X�V
	for (int i = 0; i < KeyKindMax; i++)
	{

		//1�O�̃L�[���̓��͂�ۑ�
		OldKeyPressFrame[i] = NowKeyPressFrame[i];

		//���݃L�[��������Ă��鎞�A�������t���[�������J�E���g�B
		if (KeyState[i] != 0)
		{
			NowKeyPressFrame[i]++;

		}
		else if (KeyState[i] == 0) //������Ă��Ȃ��̂Ȃ�A�J�E���g��0�ɁB
		{
			NowKeyPressFrame[i] = 0;
		}


	}

	return;
}


/*



�����Ă鎞��������̕ϐ����傫���Ȃ��Ă��B

��������̕ϐ����ʂ̂Ƃ���ɂP�������Ƃ��A�����Ă锻����o���B

����ȊO�̎���false��Ԃ��B


*/



//����̃L�[�����������ǂ���
bool KeyDown(int KEY_INPUT_)
{



	//������[KEY_INPUT_]��DX���C�u�����Ƀ}�N����`����Ă�A�e�L�[�̃R�[�h

	//���݉�����Ă���L�[�̃t���[���J�E���g��0���傫��������A�u�����Ă���v�Ɣ��f
	if (NowKeyPressFrame[KEY_INPUT_] > 0)
	{
		return true;
	}



	return false; //�����Ă��Ȃ�
}







//����̃L�[���N���b�N�������ǂ����@(���������ƁA�w�𗣂��܂ł̓�������m����̂��@�N���b�N�Ƃ���)
bool KeyClick(int KEY_INPUT_)
{

	if (NowKeyPressFrame[KEY_INPUT_] == 0 && OldKeyPressFrame[KEY_INPUT_] > 0)
	{
		return true;
	}

	return false;
}


//�L�[�_�E�������m����...?
// 

bool KeyPush(int KEY_INPUT_)
{
	if (OldKeyPressFrame[KEY_INPUT_] == 0 && NowKeyPressFrame[KEY_INPUT_] > 0)
	{
		return true;
	}

	return false;

}



//�@����̃L�[���������t���[����
//�@���Ԃ��l�̓t���[�����Ȃ̂ŁA�g���ەK�v�ł���΂����ƕϊ����邱�ƁB
int KeyPressFrame(int KEY_INPUT_)
{



	return NowKeyPressFrame[KEY_INPUT_];
}










