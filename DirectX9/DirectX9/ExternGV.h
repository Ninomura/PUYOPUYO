#pragma once //インクルードガード

#define WindowHeightSize 896/2 //ウィンドウのY幅
#define WindowWidthSize 640    //ウィンドウのX幅
#define FrameHeightSize 896/2
#define FrameWidthSize 448/2
#define GameHeight 12
#define GameWidth 6
#define PUYOSize 64/2 //ぷよの画像サイズ
#define PUYOType 3

//ゲームのモード
enum Game_Mode
{
	StartScreenProcessing,   //スタート画面の設定
	GameStartProcessing,     //初期処理
	PlayerProcessing,        //プレイヤー操作（選択可能処理）
	ExtinctionProcess,       //消滅（連鎖）処理
	GameEndProcessing,       //最終処理
};

//ぷよの種類
enum PUYO
{
	red,
	blue,
	green,
	null
};

typedef struct
{
	//プレイヤーが操作中か
	bool PlayerUse;
	//ぷよの種類
	PUYO Type;
}PUYODATA;

PUYODATA PuyoData[GameHeight][GameWidth];