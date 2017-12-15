#pragma once //�C���N���[�h�K�[�h

#define WindowHeightSize 896/2 //�E�B���h�E��Y��
#define WindowWidthSize 640    //�E�B���h�E��X��
#define FrameHeightSize 896/2
#define FrameWidthSize 448/2
#define GameHeight 12
#define GameWidth 6
#define PUYOSize 64/2 //�Ղ�̉摜�T�C�Y
#define PUYOType 3

//�Q�[���̃��[�h
enum Game_Mode
{
	StartScreenProcessing,   //�X�^�[�g��ʂ̐ݒ�
	GameStartProcessing,     //��������
	PlayerProcessing,        //�v���C���[����i�I���\�����j
	ExtinctionProcess,       //���Łi�A���j����
	GameEndProcessing,       //�ŏI����
};

//�Ղ�̎��
enum PUYO
{
	red,
	blue,
	green,
	null
};

typedef struct
{
	//�v���C���[�����쒆��
	bool PlayerUse;
	//�Ղ�̎��
	PUYO Type;
}PUYODATA;

PUYODATA PuyoData[GameHeight][GameWidth];