#pragma once


#include "DxLib.h"

#define TextureNo 220	//�摜�̐�
#define SoundNo	  20	//�T�E���h�̐�

extern int GraphData[TextureNo];//�e�N�X�`����ǂݍ��ނ��߂̔z��
extern int AnimData[TextureNo];//�A�j���[�V���������Ɨ�������

extern int SoundData[SoundNo]; //����ǂݍ��ނ��߂̔z��

extern int LoadFrame;




extern void TitleTextureLoad();		//Title�摜�̃��[�h
extern void HomeTextureLoad();		//Home�摜�̃��[�h
extern void ShopTextureLoad();		//Shop�摜�̃��[�h
extern void BattleTextureLoad();	//Battle�摜�̃��[�h
extern void ResultTextureLoad();	//Result�摜�̃��[�h
extern void OptionTextureLoad();	//Option�摜�̃��[�h
extern void TutorialTextureLoad();    //Tutorial�摜�̃��[�h 


extern void AnimDataLoad(); //�A�j���[�V�����p�̉摜�����[�h����֐�

extern void SoundLoad() ; 	//Title�T�E���h�̃��[�h




