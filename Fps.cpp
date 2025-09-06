//FPS�����̃t�@�C��

#include "Fps.h"



//�O���[�o���ϐ�
FPS fps;





//������
void FPSInit(void)
{


	//Windows���N�����Ă��猻�݂܂ł̎��Ԃ𓾂�(�}�C�N���b)
	fps.FirstTakeTime = GetNowHiPerformanceCount();

	//���̒l��������
	fps.NowTakeTime = fps.FirstTakeTime;
	fps.OldTakeTime = fps.FirstTakeTime;
	fps.deltaTime = 0.000001f;
	fps.FrameCount = 1;
	fps.Average = 0.0f;

	return;

}




void FPSCheck(void)
{

	//���݂̎������擾
	fps.NowTakeTime = GetNowHiPerformanceCount();


	//�o�ߎ��Ԃ��v�Z
	fps.deltaTime = (fps.NowTakeTime - fps.OldTakeTime) / MicroSecond;


	//���݂̎�����ۑ�
	fps.OldTakeTime = fps.NowTakeTime;

	//���݂��ő�t���[���ڂȂ�
	if (fps.FrameCount == GameFPS)
	{


		//1�t���[���ځ`�ő�t���[���ڂ܂ł̂����������v���Ԃ��v�Z�B
		float TotalTakeTime = fps.NowTakeTime - fps.FirstTakeTime;


		//���v���Ԃ𗝑z��FPS�l�Řa���ĕ��ϒl���v�Z
		float CalcAverage = TotalTakeTime / GameFPS;

		//1�b������̃t���[�����ɕϊ�
		fps.Average = MicroSecond / CalcAverage;


		//1�t���[���ڂ̎������擾
		fps.FirstTakeTime = GetNowHiPerformanceCount();

		//1�t���[���ڂ�1�ɖ߂�
		fps.FrameCount = 1;


	}
	else
	{
		fps.FrameCount++;
	}




	return;
}




//�`��
void FPSDraw(void)
{
	DrawFormatString(0, 0, GetColor(255, 255, 255), "FPS:%3.1f", fps.Average);

	return;

}


//�ҋ@
void FPSWait(void)
{

	int wait = 0;

	//�҂����Ԃ��v��
	wait = MicroSecond / GameFPS * fps.FrameCount 
		   - (fps.NowTakeTime - fps.FirstTakeTime);  //���z�̎��� - ���ۂ̎���


	//�}�C�N���b���~���b�ɕϊ�
	wait /= MillSecond;

	//�����҂����Ԃ�����Ȃ�
	if (wait > 0 && wait <= WaitTimeMill)
	{


		//�u�߂����[���v���������Ȃ���҂�
		WaitTimer(wait);

	}


	return;
}

