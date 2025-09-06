#include "Mouse.h"
#include "Game.h"


//�O���[�o���ϐ�
MousePoint NowPoint;	//���݂̈ʒu
MousePoint OldPoint;	//�ЂƂO�̈ʒu



int NowMousePressFrame[MouseKindMax];	//���݂̃{�^���̉����Ă�t���[�������Ǘ�
int OldMousePressFrame[MouseKindMax];	//�ߋ��̉��O�̉����Ă�t���[�������Ǘ�



int MouseCodeIndex[MouseKindMax]
{
	MOUSE_INPUT_LEFT,
	MOUSE_INPUT_RIGHT,
	MOUSE_INPUT_MIDDLE
};


void MouseNowIntoOld(void)				//Now����׌n�̕ϐ��̒l��Old����׌n�̕ϐ��֓����
{

	OldPoint = NowPoint;

	for (int i = 0; i < MouseKindMax; i++)
	{
		OldMousePressFrame[i] = NowMousePressFrame[i];
	}



	return;
}


int MouseCodeToIndex(int MOUSE_INPUT_)  //�}�E�X�̂ڂ��񂱁[�ǂ�z��̗v�f���ɕϊ�����
{


	for (int i = 0; i < MouseKindMax; i++)
	{
		if (MouseCodeIndex[i] == MOUSE_INPUT_)//�}�E�X�R�[�h���R�Â�����Ă�Ȃ�
		{
			return i;	//���̗v�f����Ԃ�
		}
	}

	
	//�}�E�X�R�[�h��������΃G���[(999)
	return MouseErrorIndex;
}





void MouseInit(void)//�܂������͏����̏�����
{

	//�}�E�X�ʒu�̏�����(���݂ƈȑO)
	NowPoint.x = 0;
	NowPoint.y = 0;

	//���̓t���[���̏�����
	for (int i = 0; i < MouseKindMax; i++)
	{
		NowMousePressFrame[i] = 0;	
	}



	
	//����������Now��Old�ɃR�s�[(Old�n��������)
	MouseNowIntoOld();	




	return;
}

void MouseUpdate(void)//�}�E�X���͏����̍X�V
{
	//�}�E�X�̑S�Ẵ{�^���̏����擾

	//���݂̏����ȑO�̏��Ƃ��ĕۑ��B
	MouseNowIntoOld();


	//���݂̃N���C�A���g���W��ۑ�
	GetMousePoint(&NowPoint.x, &NowPoint.y);

	//�����A�}�E�X�|�C���^�[���Q�[���E�B���h�E�̊O�ɂ���Ȃ�A���W���E�B���h�E�̒[�̍��W�ŕێ��B

	if (NowPoint.x < 0)//��
	{
		NowPoint.x = 0;
	} 
	else if (NowPoint.x > width) //�E
	{
		NowPoint.x = width;
	}


	if (NowPoint.y < 0)//��
	{
		NowPoint.y = 0; 
	}
	else if (NowPoint.y < height)//��
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

bool MouseDown(int MOUSE_INPUT_)//����̃}�E�X�{�^������������
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


 bool MousePush(int MOUSE_INPUT_)			//�}�E�X�{�^�����������u�Ԃ̔���
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

 bool MouseClick(int MOUSE_INPUT_)		//����̃}�E�X�{�^�����N���b�N������
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

 int  MousePressFrame(int MOUSE_INPUT_)	//����̃{�^�����������t���[����
{
	return NowMousePressFrame[MOUSE_INPUT_];
}



 //���݂̃|�C���^�[���W���擾
MousePoint NowMousePos(void)
{
	return NowPoint;
}

//�ȑO�̃|�C���^�[���W���擾
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

