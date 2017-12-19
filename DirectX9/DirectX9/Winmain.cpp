
#include <Windows.h>
#pragma comment(lib,"winmm.lib")

#include <tchar.h>


#include"Direct3D.h"

#include "Sprite.h"
#include "Texture.h"

#include "DirectInput.h"

#include"PuyoDown.h"

#include <random>


//ウィンドウプロシージャ
LRESULT CALLBACK WndPrc
(
	HWND hWnd,	//ウィンドウのハンドル
	UINT msg,	//メッセージ
	WPARAM wParam,
	LPARAM lParam
)
{
	//メッセージ処理のための関数
	//DispatchMessageによって呼び出される

	//ウィンドウクラスの登録時に
	//各ウィンドウに設定される

	//アプリケーションがメッセージを
	//取得したら呼び出される

	//メッセージの例

	//WM_DESTROY ウィンドウが破棄された
	//			 ×ボタンが押された時など
	//WM_MOVE    ウィンドウが移動
	//WM_SIZE    ウィンドウサイズの変更
	//等

	//特別な処理を必要とする場合
	//または自分で独自の処理を定義したい場合
	//ここでメッセージの種類に応じた
	//処理を行う

	//取りあえず WM_DESTROYが来た時の
	//終了処理のみ定義

	switch (msg)
	{
	case WM_DESTROY:

		PostQuitMessage(0);

		//メッセージキューに
		//新しくWM_QUITメッセージを送る

		//いずれメッセージキューから
		//取り出され
		//メインループが終了する
		//(メインループの終了条件を
		//そのように作る)
		break;
	}

	//独自の処理を行ったら
	//デフォルトのウィンドウプロシージャを実行

	return DefWindowProc(hWnd, msg, wParam, lParam);
}

//ウィンドウ設定の名前
static const TCHAR* WC_BASIC = _T("Basic");

//作りたいウィンドウの設定を
//登録する関数
HRESULT RegistClassEx(HINSTANCE hInstance)
{
	//ウィンドウの設定を保存する構造体
	WNDCLASSEX wcex;

	//wcexの先頭アドレスから
	//WNDCLASSEXの長さ分のメモリを
	//全て0で埋める
	memset(&wcex, 0, sizeof(WNDCLASSEX));
	//つまりはwcexが使用しているメモリ領域を
	//全て0で初期化する処理

	//ウィンドウの設定

	//構造体のサイズ
	wcex.cbSize = sizeof(WNDCLASSEX);

	//ウィンドウの設定情報に追加する捕捉を付けないので
	//0で固定
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;

	//Windowのスタイル
	//それぞれがビット単位のフラグであるため
	//オア演算で合成したものがスタイルの最終的な設定
	wcex.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;

	//CS_HREDRAW 横サイズが変わったときウィンドウ全体の再描画
	//   VREDRAW 縦サイズが変わったときウィンドウ全体の再描画
	//   DBLCLKS ダブルクリックが発生したことをウィンドウに通知

	//WinMainのインスタンスハンドル
	wcex.hInstance = hInstance;

	//ウィンドウプロシージャのアドレス
	//関数ポインタの設定
	//ウィンドウプロシージャをOSが呼び出せるようにする
	wcex.lpfnWndProc = (WNDPROC)WndPrc;

	//背景色
	wcex.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);

	//メニュー　なし
	wcex.lpszMenuName = NULL;

	//ウィンドウクラスの名前　このウィンドウ設定の名前
	wcex.lpszClassName = WC_BASIC;

	//アイコン　デフォルトのを使う
	wcex.hIcon = (HICON)LoadImage(NULL,
		MAKEINTRESOURCE(IDI_APPLICATION),
		IMAGE_ICON,
		0,
		0,
		LR_DEFAULTSIZE | LR_SHARED);
	wcex.hIconSm = NULL;

	//カーソル デフォルトのものを使う
	wcex.hCursor = (HCURSOR)LoadImage(NULL,
		MAKEINTRESOURCE(IDC_ARROW),
		IMAGE_CURSOR,
		0,
		0,
		LR_DEFAULTSIZE | LR_SHARED);

	//設定したウィンドウクラスを登録
	//登録したウィンドウ設定でないと
	//ウィンドウを作ることができない
	return RegisterClassEx(&wcex);
	//HRESULT型の実行結果が戻される
}


//登録した設定を基にウィンドウを作成する
HRESULT MakeWindow
(HINSTANCE hInstance,//WinMainの識別子
	HWND &refHWnd,	//ウィンドウの識別子
					//正しくウィンドウの作成ができたら
					//この変数に識別子を代入する
	int width = WindowWidthSize,	//クライアント領域の幅
	int height = WindowHeightSize)	//クライアント領域の高さ
						//クライアント領域はウィンドウ全体から
						//外枠やメニューの部分を除いた物と今は思っておけばOK
{
	//クライアント領域のおおきさを決める
	RECT rect;
	rect.top = 0;
	rect.left = 0;
	rect.right = width;
	rect.bottom = height;

	//クライアント領域を保持するのに必要な
	//ウィンドウのおおきさを計算
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE/*TRUE*/);
	//正しく実行されるとrectの値が更新される

	//WS_OVERLAPPEDWINDOWはウィンドウのスタイルの一つ

	//ウィンドウのハンドル
	//ウィンドウの識別に使用する
	HWND hWnd;

	hWnd = CreateWindowEx
	(0,						//ウィンドウ拡張スタイル
		WC_BASIC,				//作りたいウィンドウクラス
								//あらかじめ登録されたもの
		_T("ぽよぽよ"),			//ウィンドウのタイトル
		WS_OVERLAPPEDWINDOW,	//ウィンドウのスタイル
		CW_USEDEFAULT,			//位置x座標 デフォルトの値
		CW_USEDEFAULT,			//位置y座標 デフォルトの値
		rect.right - rect.left,	//ウィンドウ全体の幅
		rect.bottom - rect.top, //ウィンドウ全体の高さ
		NULL,					//親ウィンドウのハンドル
		NULL,					//メニューのハンドル
		hInstance,				//WinMainのハンドル

		NULL);					//ウィンドウ作成データ
								//ウィンドウに好きな32ビットのデータを
								//付属させることができる
								//追加情報構造体へのポインタなど
								//を付けるのが無難な使い方か
								//今回は使わない

								//ウィンドウが正しく作れたかをチェック
								//正しく作れたらhWndにNULL以外が入るはず
	if (hWnd == NULL)
	{
		return S_FALSE;//HRESULT型　失敗を表す識別子の一つ
	}

	//ウィンドウをアクティブにして表示
	//hWndでウィンドウの識別をしていることに注目
	ShowWindow(hWnd, SW_SHOWNORMAL);

	//クライアント領域の更新
	UpdateWindow(hWnd);

	//参照渡しになっている引数に
	//ウィンドウの識別ハンドルをコピーする
	//これによって今作ったウィンドウの識別ハンドルを
	//呼び出し元のプログラムで得ることができる
	refHWnd = hWnd;

	//HRESULT型　成功を表す識別子の一つ
	return S_OK;
}


//エントリーポイント
//プログラムの開始関数

int _stdcall WinMain
(HINSTANCE hInstance,	//プログラムを識別するハンドル
	HINSTANCE hPrevInstance,//アプリケーションの前のインスタンスハンドル
							//win32だと常にNULL
	LPSTR lpCmdLine,		//コマンドライン引数
	int nCmdShow)		//ウィンドウの表示状態
{
	//メッセージボックス
	MessageBox(NULL,		//ウィンドウのハンドル 
		TEXT("テスト"),		//本文
		TEXT("テスト-タイトル"),//タイトル
		MB_OK);				//メッセージボックスのタイプ
							//MB_OK  okのボタンが表示

	if (FAILED(RegistClassEx(hInstance)))
	{
		MessageBox(NULL,
			TEXT("ウィンドウクラス設定失敗"),
			TEXT("テスト-タイトル"),
			MB_OK);
		return 0;
	}

	HWND hWnd = NULL;

	//正しくウィンドウが作成されれば
	//hWndにウィンドウの識別ハンドルが入る
	if (FAILED(MakeWindow(hInstance, hWnd)))
	{
		MessageBox(NULL,
			TEXT("ウィンドウ作成失敗"),
			TEXT("テスト-タイトル"),
			MB_OK);
		return 0;
	}

	//Direct3Dを管理するクラス(シングルトン)への参照を取得
	Direct3D& d3d = Direct3D::GetInstance();

	//Direct3DDeviceの作成を試みる
	if (d3d.TryCreate(hWnd))
	{
		MessageBox(NULL,
			TEXT("Direct3D Device作成成功"),
			TEXT("テスト-タイトル"),
			MB_OK);
	}

	d3d.SetRenderState(RENDERSTATE::RENDER_ALPHATEST);

	DirectInput * pDi = DirectInput::GetInstance();
	pDi->Init(hWnd);

	int frame;
	int rol, roly, rolx;
	float DownSpeed;

	bool Linkflag;
	bool breakflag;
	bool Downflag;
	bool Createflag;

	//フレーム画像
	Sprite spriteImgFrame;
	Texture imgFrame;
	spriteImgFrame.SetSize(FrameWidthSize, FrameHeightSize);
	spriteImgFrame.SetPos(FrameWidthSize/2, FrameHeightSize/2);
	imgFrame.Load(_T("Texture/frame.png"));

	//ぷよの画像
	Sprite spriteImgPuyo[GameHeight][GameWidth];
	Texture imgPuyo[GameHeight][GameWidth];
	for (int y = 0; y < GameHeight; y++)
	{
		for (int x = 0; x < GameWidth; x++)
		{
			spriteImgPuyo[y][x].SetSize(PUYOSize, PUYOSize);
			spriteImgPuyo[y][x].SetPos(PUYOSize / 2 + x*PUYOSize + PUYOSize / 2,
				                       PUYOSize / 2 + y*PUYOSize + PUYOSize);

			imgPuyo[y][x].Load(_T("Texture/puyo.png"));
			imgPuyo[y][x].SetDivide(PUYOType, 1);
		}
	}

	Puyo PY;
	//初期を演算処理に設定
	Game_Mode Mode = GameStartProcessing;

	MSG msg = {};

	//メインプログラム-------------------------------------------------
	//quitメッセージが出てくるまでループを繰り返す
	//quitメッセージは上記のウィンドウプロシージャから送信
	//送信の条件などはウィンドウプロシージャを確認
	while (msg.message != WM_QUIT)
	{

		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			//仮想キーメッセージを文字メッセージに変換し
			//それをメッセージキューにポストする
			TranslateMessage(&msg);

			//メッセージの割り当て
			//ウィンドウプロシージャでメッセージを処理
			DispatchMessage(&msg);
		}
		else
		{
			pDi->Update();//キー状態の更新

			switch (Mode)
			{

			//スタート画面
			case Game_Mode::StartScreenProcessing:

				break;

			//初期処理
			case Game_Mode::GameStartProcessing:

				frame = 0;
				Linkflag = false;
				breakflag = false;
				Createflag = true;
				Downflag = false;
				rol = 0;

				for (int y = 0; y < GameHeight; y++)
				{
					for (int x = 0; x < GameWidth; x++)
					{
						PuyoData[y][x].Type = null;
						PuyoData[y][x].PlayerUse = false;
						PuyoData[y][x].RolBase = false;
					}
				}

				//プレイヤー操作（落下処理）に移動
				Mode = PlayerProcessing;
				break;

			//プレイヤー操作（落下処理）
			case Game_Mode::PlayerProcessing:

				//ぷよの生成処理
				if (Createflag == true)
				{
					Createflag = false;

					std::random_device rnd;

					switch (rnd()%PUYOType)
					{
					case 0:
						PuyoData[0][2].Type = green;
						break;
					case 1:
						PuyoData[0][2].Type = red;
						break;
					case 2:
						PuyoData[0][2].Type = blue;
						break;
					}

					switch (rnd() % PUYOType)
					{
					case 0:
						PuyoData[0][3].Type = green;
						break;
					case 1:
						PuyoData[0][3].Type = red;
						break;
					case 2:
						PuyoData[0][3].Type = blue;
						break;
					}

					//プレイヤーが操作しているぷよ
					PuyoData[0][2].PlayerUse = true;
					PuyoData[0][3].PlayerUse = true;

					//回転の基点となるぷよ
					PuyoData[0][2].RolBase = true;

					//回転のフラグをリセット
					rol = 0;
				}

				//落下速度のリセット
				DownSpeed = 1.0;

				//キー入力の処理
				//移動処理
				if (frame > 10 && pDi->KeyState(DIK_RIGHT))
				{
					frame = 0;
					for (int y = GameHeight - 1; y >= 0; y--)
					{
						for (int x = GameWidth; x >= 0; x--)
						{
							if (PuyoData[y][x].PlayerUse == true)
							{
								if (x < GameWidth - 1)
								{
									if (PuyoData[y][x + 1].Type != null
										&&PuyoData[y][x + 1].PlayerUse == false)
									{
										breakflag = true;
										break;
									}
									else
									{
										//下のマスにデータを移行
										PuyoData[y][x + 1].Type = PuyoData[y][x].Type;
										PuyoData[y][x + 1].PlayerUse = PuyoData[y][x].PlayerUse;
										PuyoData[y][x + 1].RolBase = PuyoData[y][x].RolBase;

										//前のマスデータをリセット
										PuyoData[y][x].Type = null;
										PuyoData[y][x].PlayerUse = false;
										PuyoData[y][x].RolBase = false;
									}
								}
								else
								{
									breakflag = true;
									break;
								}
							}
						}
						if (breakflag == true)
						{
							breakflag = false;
							break;
						}
					}
				}
				else if (frame > 10 && pDi->KeyState(DIK_LEFT))
				{
					frame = 0;

					for (int y = GameHeight - 1; y >= 0; y--)
					{
						for (int x = 0; x < GameWidth; x++)
						{
							if (PuyoData[y][x].PlayerUse == true)
							{
								if (x > 0)
								{
									if (PuyoData[y][x - 1].Type != null
										&&PuyoData[y][x - 1].PlayerUse == false)
									{
										breakflag = true;
										break;
									}
									else
									{
										//下のマスにデータを移行
										PuyoData[y][x - 1].Type = PuyoData[y][x].Type;
										PuyoData[y][x - 1].PlayerUse = PuyoData[y][x].PlayerUse;
										PuyoData[y][x - 1].RolBase = PuyoData[y][x].RolBase;

										//前のマスデータをリセット
										PuyoData[y][x].Type = null;
										PuyoData[y][x].PlayerUse = false;
										PuyoData[y][x].RolBase = false;
									}
								}
								else
								{
									breakflag = true;
									break;
								}
							}
						}

						if (breakflag == true)
						{
							breakflag = false;
							break;
						}
					}
				}
				
				if (pDi->KeyState(DIK_DOWN))
				{
					DownSpeed = 5.0;
				}
				else if (pDi->KeyState(DIK_UP))
				{
					DownSpeed = 40.0;
				}

				//回転処理
				if (pDi->KeyJustPressed(DIK_A))
				{
					for (int y = GameHeight - 1; y >= 0; y--)
					{
						for (int x = GameWidth - 1; x >= 0; x--)
						{
							switch (rol)
							{
							case 0:
								roly = -1;
								rolx = -1;
								break;
							case 1:
								roly = 1;
								rolx = -1;
								break;
							case 2:
								roly = 1;
								rolx = 1;
								break;
							case 3:
								roly = -1;
								rolx = 1;
								break;
							}


							if (PuyoData[y + roly][x + rolx].Type == null
								&& PuyoData[y][x].RolBase == false
								&& PuyoData[y][x].PlayerUse == true)
							{
								if ((rol == 0 && y + roly < GameHeight) || (rol == 1 && x + rolx >= 0) || (rol == 3 && x + rolx < GameWidth) || rol == 2)
								{
									//下のマスにデータを移行
									PuyoData[y + roly][x + rolx].Type = PuyoData[y][x].Type;
									PuyoData[y + roly][x + rolx].PlayerUse = PuyoData[y][x].PlayerUse;
									PuyoData[y + roly][x + rolx].RolBase = PuyoData[y][x].RolBase;

									//前のマスデータをリセット
									PuyoData[y][x].Type = null;
									PuyoData[y][x].PlayerUse = false;
									PuyoData[y][x].RolBase = false;

									//回転のフラグを加算
									rol++;

									if (rol > 3) { rol = 0; }

									breakflag = true;
									break;
								}
							}
						}

						if (breakflag == true)
						{
							breakflag = false;
							break;
						}

					}
				}
				else if (pDi->KeyJustPressed(DIK_D))
				{
					for (int y = GameHeight - 1; y >= 0; y--)
					{
						for (int x = GameWidth - 1; x >= 0; x--)
						{
							switch (rol)
							{
							case 0:
								roly = 1;
								rolx = -1;
								break;
							case 1:
								roly = 1;
								rolx = 1;
								break;
							case 2:
								roly = -1;
								rolx = 1;
								break;
							case 3:
								roly = -1;
								rolx = -1;
								break;
							}

							if (PuyoData[y + roly][x + rolx].Type == null
								&& PuyoData[y][x].RolBase == false
								&& PuyoData[y][x].PlayerUse == true)
							{
								if ((rol == 2 && y + roly < GameHeight) || (rol == 3 && x + rolx >= 0) || (rol == 1 && x + rolx < GameWidth) || rol == 0)
								{
									//下のマスにデータを移行
									PuyoData[y + roly][x + rolx].Type = PuyoData[y][x].Type;
									PuyoData[y + roly][x + rolx].PlayerUse = PuyoData[y][x].PlayerUse;
									PuyoData[y + roly][x + rolx].RolBase = PuyoData[y][x].RolBase;

									//前のマスデータをリセット
									PuyoData[y][x].Type = null;
									PuyoData[y][x].PlayerUse = false;
									PuyoData[y][x].RolBase = false;


									rol--;

									if (rol < 0) { rol = 3; }

									breakflag = true;
									break;
								}
							}
						}

						if (breakflag == true)
						{
							breakflag = false;
							break;
						}
					}
				}
					
				if (frame > 50/ DownSpeed
					&& Downflag == false)
				{
					frame = 0;

					//落下処理
					for (int y = GameHeight - 1; y >= 0; y--)
					{
						for (int x = GameWidth; x >= 0; x--)
						{
							//ぷよがプレイヤーが操作中のぷよか
							if (PuyoData[y][x].PlayerUse == true)
							{
								//下マスにぷよがあるかどうか
								if (PuyoData[y + 1][x].Type != null)
								{
									Downflag = true;

									for (int y2 = GameHeight - 1; y2 >= 0; y2--)
									{
										for (int x2 = GameWidth; x2 >= 0; x2--)
										{
											PuyoData[y2][x2].PlayerUse = false;
										}
									}

									breakflag = true;
									frame = 2;
									break;

								}
								//落下処理
								else
								{
									//下のマスにデータを移行
									PuyoData[y + 1][x].Type = PuyoData[y][x].Type;
									PuyoData[y + 1][x].PlayerUse = PuyoData[y][x].PlayerUse;
									PuyoData[y + 1][x].RolBase = PuyoData[y][x].RolBase;

									//前のマスデータをリセット
									PuyoData[y][x].Type = null;
									PuyoData[y][x].PlayerUse = false;
									PuyoData[y][x].RolBase = false;
								}
							}
						}

						if (breakflag == true)
						{
							breakflag = false;
							break;
						}
					}
				}

				if (frame > 10
					&& Linkflag == true
					&& Downflag == false)
				{
					Linkflag = false;
					frame = 0;

					//連鎖処理
					for (int y = GameHeight - 1; y >= 0; y--)
					{
						for (int x = GameWidth - 1; x >= 0; x--)
						{
							PuyoData[y][x].Link = 0;
						}
					}

					for (int y = GameHeight - 1; y >= 0; y--)
					{
						for (int x = GameWidth - 1; x >= 0; x--)
						{
							if (PuyoData[y][x].Type != null)
							{
								if (y > 0)
								{
									if (PuyoData[y][x].Type == PuyoData[y - 1][x].Type)
									{
										PuyoData[y][x].Link++;
										PY.Test(y - 1, x, y, x);
									}
								}

								if (y < GameHeight - 1)
								{
									if (PuyoData[y][x].Type == PuyoData[y + 1][x].Type)
									{
										PuyoData[y][x].Link++;
										PY.Test2(y + 1, x, y, x);
									}
								}

								if (x < GameWidth - 1)
								{
									if (PuyoData[y][x].Type == PuyoData[y][x + 1].Type)
									{
										PuyoData[y][x].Link++;
										PY.Test3(y, x + 1, y, x);
									}
								}

								if (x > 0)
								{
									if (PuyoData[y][x].Type == PuyoData[y][x - 1].Type)
									{
										PuyoData[y][x].Link++;
										PY.Test4(y, x - 1, y, x);
									}
								}
							}
						}
					}

					Createflag = true;
					Downflag = false;

					for (int y = GameHeight - 1; y >= 0; y--)
					{
						for (int x = GameWidth - 1; x >= 0; x--)
						{
							if (PuyoData[y][x].Link >= 3)
							{
								PuyoData[y][x].Type = null;
								PuyoData[y][x].PlayerUse = false;
								PuyoData[y][x].RolBase = false;
								Createflag = false;
								Downflag = true;
							}
						}
					}
				}

				//落下処理
				if (frame > 3
				 && Downflag == true)
				{
					frame = 0;

					Downflag = false;
					Linkflag = true;

					for (int y = GameHeight - 1; y >= 0; y--)
					{
						for (int x = GameWidth - 1; x >= 0; x--)
						{
							if (PuyoData[y][x].Type != null)
							{
								if (PuyoData[y + 1][x].Type != null)
								{}
								else
								{
									//下のマスにデータを移行
									PuyoData[y + 1][x].Type = PuyoData[y][x].Type;
									PuyoData[y + 1][x].PlayerUse = PuyoData[y][x].PlayerUse;
									PuyoData[y + 1][x].RolBase = PuyoData[y][x].RolBase;

									//前のマスデータをリセット
									PuyoData[y][x].Type = null;
									PuyoData[y][x].PlayerUse = false;
									PuyoData[y][x].RolBase = false;

									Downflag = true;
									Linkflag = false;
								}
							}
						}
					}
				}

				frame++;

				break;

			//消滅（連鎖）処理
			case Game_Mode::ExtinctionProcess:

				//プレイヤー操作(選択可能処理)に移動
				Mode = PlayerProcessing;

				break;

			//ゲーム終了
			case Game_Mode::GameEndProcessing:

				if (pDi->MouseButton(0))
				{
					Mode = GameStartProcessing;
				}

				break;

			}

			//描画処理
			//バックバッファのクリア
			if (SUCCEEDED(d3d.BeginScene()))
			{
				d3d.ClearScreen();

				//フレーム
				spriteImgFrame.Draw(imgFrame);

				//ぷよ
				for (int y = 0; y < GameHeight; y++)
				{
					for (int x = 0; x < GameWidth; x++)
					{
						if (PuyoData[y][x].Type != null)
						{
							switch (PuyoData[y][x].Type)
							{
							case green:
								imgPuyo[y][x].SetNum(0, 0);
								break;
							case blue:
								imgPuyo[y][x].SetNum(1, 0);
								break;
							case red:
								imgPuyo[y][x].SetNum(2, 0);
								break;
							}

							spriteImgPuyo[y][x].Draw(imgPuyo[y][x]);
						}
					}
				}

				//描画終了の合図
				d3d.EndScene();
				//バックバッファをフロントへ反映
				d3d.Present();
			}
		}
	}

	return 0;
};
