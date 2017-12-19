
#include <Windows.h>
#pragma comment(lib,"winmm.lib")

#include <tchar.h>


#include"Direct3D.h"

#include "Sprite.h"
#include "Texture.h"

#include "DirectInput.h"

#include"PuyoDown.h"

#include <random>


//�E�B���h�E�v���V�[�W��
LRESULT CALLBACK WndPrc
(
	HWND hWnd,	//�E�B���h�E�̃n���h��
	UINT msg,	//���b�Z�[�W
	WPARAM wParam,
	LPARAM lParam
)
{
	//���b�Z�[�W�����̂��߂̊֐�
	//DispatchMessage�ɂ���ČĂяo�����

	//�E�B���h�E�N���X�̓o�^����
	//�e�E�B���h�E�ɐݒ肳���

	//�A�v���P�[�V���������b�Z�[�W��
	//�擾������Ăяo�����

	//���b�Z�[�W�̗�

	//WM_DESTROY �E�B���h�E���j�����ꂽ
	//			 �~�{�^���������ꂽ���Ȃ�
	//WM_MOVE    �E�B���h�E���ړ�
	//WM_SIZE    �E�B���h�E�T�C�Y�̕ύX
	//��

	//���ʂȏ�����K�v�Ƃ���ꍇ
	//�܂��͎����œƎ��̏������`�������ꍇ
	//�����Ń��b�Z�[�W�̎�ނɉ�����
	//�������s��

	//��肠���� WM_DESTROY����������
	//�I�������̂ݒ�`

	switch (msg)
	{
	case WM_DESTROY:

		PostQuitMessage(0);

		//���b�Z�[�W�L���[��
		//�V����WM_QUIT���b�Z�[�W�𑗂�

		//�����ꃁ�b�Z�[�W�L���[����
		//���o����
		//���C�����[�v���I������
		//(���C�����[�v�̏I��������
		//���̂悤�ɍ��)
		break;
	}

	//�Ǝ��̏������s������
	//�f�t�H���g�̃E�B���h�E�v���V�[�W�������s

	return DefWindowProc(hWnd, msg, wParam, lParam);
}

//�E�B���h�E�ݒ�̖��O
static const TCHAR* WC_BASIC = _T("Basic");

//��肽���E�B���h�E�̐ݒ��
//�o�^����֐�
HRESULT RegistClassEx(HINSTANCE hInstance)
{
	//�E�B���h�E�̐ݒ��ۑ�����\����
	WNDCLASSEX wcex;

	//wcex�̐擪�A�h���X����
	//WNDCLASSEX�̒������̃�������
	//�S��0�Ŗ��߂�
	memset(&wcex, 0, sizeof(WNDCLASSEX));
	//�܂��wcex���g�p���Ă��郁�����̈��
	//�S��0�ŏ��������鏈��

	//�E�B���h�E�̐ݒ�

	//�\���̂̃T�C�Y
	wcex.cbSize = sizeof(WNDCLASSEX);

	//�E�B���h�E�̐ݒ���ɒǉ�����ߑ���t���Ȃ��̂�
	//0�ŌŒ�
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;

	//Window�̃X�^�C��
	//���ꂼ�ꂪ�r�b�g�P�ʂ̃t���O�ł��邽��
	//�I�A���Z�ō����������̂��X�^�C���̍ŏI�I�Ȑݒ�
	wcex.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;

	//CS_HREDRAW ���T�C�Y���ς�����Ƃ��E�B���h�E�S�̂̍ĕ`��
	//   VREDRAW �c�T�C�Y���ς�����Ƃ��E�B���h�E�S�̂̍ĕ`��
	//   DBLCLKS �_�u���N���b�N�������������Ƃ��E�B���h�E�ɒʒm

	//WinMain�̃C���X�^���X�n���h��
	wcex.hInstance = hInstance;

	//�E�B���h�E�v���V�[�W���̃A�h���X
	//�֐��|�C���^�̐ݒ�
	//�E�B���h�E�v���V�[�W����OS���Ăяo����悤�ɂ���
	wcex.lpfnWndProc = (WNDPROC)WndPrc;

	//�w�i�F
	wcex.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);

	//���j���[�@�Ȃ�
	wcex.lpszMenuName = NULL;

	//�E�B���h�E�N���X�̖��O�@���̃E�B���h�E�ݒ�̖��O
	wcex.lpszClassName = WC_BASIC;

	//�A�C�R���@�f�t�H���g�̂��g��
	wcex.hIcon = (HICON)LoadImage(NULL,
		MAKEINTRESOURCE(IDI_APPLICATION),
		IMAGE_ICON,
		0,
		0,
		LR_DEFAULTSIZE | LR_SHARED);
	wcex.hIconSm = NULL;

	//�J�[�\�� �f�t�H���g�̂��̂��g��
	wcex.hCursor = (HCURSOR)LoadImage(NULL,
		MAKEINTRESOURCE(IDC_ARROW),
		IMAGE_CURSOR,
		0,
		0,
		LR_DEFAULTSIZE | LR_SHARED);

	//�ݒ肵���E�B���h�E�N���X��o�^
	//�o�^�����E�B���h�E�ݒ�łȂ���
	//�E�B���h�E����邱�Ƃ��ł��Ȃ�
	return RegisterClassEx(&wcex);
	//HRESULT�^�̎��s���ʂ��߂����
}


//�o�^�����ݒ����ɃE�B���h�E���쐬����
HRESULT MakeWindow
(HINSTANCE hInstance,//WinMain�̎��ʎq
	HWND &refHWnd,	//�E�B���h�E�̎��ʎq
					//�������E�B���h�E�̍쐬���ł�����
					//���̕ϐ��Ɏ��ʎq��������
	int width = WindowWidthSize,	//�N���C�A���g�̈�̕�
	int height = WindowHeightSize)	//�N���C�A���g�̈�̍���
						//�N���C�A���g�̈�̓E�B���h�E�S�̂���
						//�O�g�⃁�j���[�̕��������������ƍ��͎v���Ă�����OK
{
	//�N���C�A���g�̈�̂������������߂�
	RECT rect;
	rect.top = 0;
	rect.left = 0;
	rect.right = width;
	rect.bottom = height;

	//�N���C�A���g�̈��ێ�����̂ɕK�v��
	//�E�B���h�E�̂����������v�Z
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE/*TRUE*/);
	//���������s������rect�̒l���X�V�����

	//WS_OVERLAPPEDWINDOW�̓E�B���h�E�̃X�^�C���̈��

	//�E�B���h�E�̃n���h��
	//�E�B���h�E�̎��ʂɎg�p����
	HWND hWnd;

	hWnd = CreateWindowEx
	(0,						//�E�B���h�E�g���X�^�C��
		WC_BASIC,				//��肽���E�B���h�E�N���X
								//���炩���ߓo�^���ꂽ����
		_T("�ۂ�ۂ�"),			//�E�B���h�E�̃^�C�g��
		WS_OVERLAPPEDWINDOW,	//�E�B���h�E�̃X�^�C��
		CW_USEDEFAULT,			//�ʒux���W �f�t�H���g�̒l
		CW_USEDEFAULT,			//�ʒuy���W �f�t�H���g�̒l
		rect.right - rect.left,	//�E�B���h�E�S�̂̕�
		rect.bottom - rect.top, //�E�B���h�E�S�̂̍���
		NULL,					//�e�E�B���h�E�̃n���h��
		NULL,					//���j���[�̃n���h��
		hInstance,				//WinMain�̃n���h��

		NULL);					//�E�B���h�E�쐬�f�[�^
								//�E�B���h�E�ɍD����32�r�b�g�̃f�[�^��
								//�t�������邱�Ƃ��ł���
								//�ǉ����\���̂ւ̃|�C���^�Ȃ�
								//��t����̂�����Ȏg������
								//����͎g��Ȃ�

								//�E�B���h�E����������ꂽ�����`�F�b�N
								//��������ꂽ��hWnd��NULL�ȊO������͂�
	if (hWnd == NULL)
	{
		return S_FALSE;//HRESULT�^�@���s��\�����ʎq�̈��
	}

	//�E�B���h�E���A�N�e�B�u�ɂ��ĕ\��
	//hWnd�ŃE�B���h�E�̎��ʂ����Ă��邱�Ƃɒ���
	ShowWindow(hWnd, SW_SHOWNORMAL);

	//�N���C�A���g�̈�̍X�V
	UpdateWindow(hWnd);

	//�Q�Ɠn���ɂȂ��Ă��������
	//�E�B���h�E�̎��ʃn���h�����R�s�[����
	//����ɂ���č�������E�B���h�E�̎��ʃn���h����
	//�Ăяo�����̃v���O�����œ��邱�Ƃ��ł���
	refHWnd = hWnd;

	//HRESULT�^�@������\�����ʎq�̈��
	return S_OK;
}


//�G���g���[�|�C���g
//�v���O�����̊J�n�֐�

int _stdcall WinMain
(HINSTANCE hInstance,	//�v���O���������ʂ���n���h��
	HINSTANCE hPrevInstance,//�A�v���P�[�V�����̑O�̃C���X�^���X�n���h��
							//win32���Ə��NULL
	LPSTR lpCmdLine,		//�R�}���h���C������
	int nCmdShow)		//�E�B���h�E�̕\�����
{
	//���b�Z�[�W�{�b�N�X
	MessageBox(NULL,		//�E�B���h�E�̃n���h�� 
		TEXT("�e�X�g"),		//�{��
		TEXT("�e�X�g-�^�C�g��"),//�^�C�g��
		MB_OK);				//���b�Z�[�W�{�b�N�X�̃^�C�v
							//MB_OK  ok�̃{�^�����\��

	if (FAILED(RegistClassEx(hInstance)))
	{
		MessageBox(NULL,
			TEXT("�E�B���h�E�N���X�ݒ莸�s"),
			TEXT("�e�X�g-�^�C�g��"),
			MB_OK);
		return 0;
	}

	HWND hWnd = NULL;

	//�������E�B���h�E���쐬������
	//hWnd�ɃE�B���h�E�̎��ʃn���h��������
	if (FAILED(MakeWindow(hInstance, hWnd)))
	{
		MessageBox(NULL,
			TEXT("�E�B���h�E�쐬���s"),
			TEXT("�e�X�g-�^�C�g��"),
			MB_OK);
		return 0;
	}

	//Direct3D���Ǘ�����N���X(�V���O���g��)�ւ̎Q�Ƃ��擾
	Direct3D& d3d = Direct3D::GetInstance();

	//Direct3DDevice�̍쐬�����݂�
	if (d3d.TryCreate(hWnd))
	{
		MessageBox(NULL,
			TEXT("Direct3D Device�쐬����"),
			TEXT("�e�X�g-�^�C�g��"),
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

	//�t���[���摜
	Sprite spriteImgFrame;
	Texture imgFrame;
	spriteImgFrame.SetSize(FrameWidthSize, FrameHeightSize);
	spriteImgFrame.SetPos(FrameWidthSize/2, FrameHeightSize/2);
	imgFrame.Load(_T("Texture/frame.png"));

	//�Ղ�̉摜
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
	//���������Z�����ɐݒ�
	Game_Mode Mode = GameStartProcessing;

	MSG msg = {};

	//���C���v���O����-------------------------------------------------
	//quit���b�Z�[�W���o�Ă���܂Ń��[�v���J��Ԃ�
	//quit���b�Z�[�W�͏�L�̃E�B���h�E�v���V�[�W�����瑗�M
	//���M�̏����Ȃǂ̓E�B���h�E�v���V�[�W�����m�F
	while (msg.message != WM_QUIT)
	{

		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			//���z�L�[���b�Z�[�W�𕶎����b�Z�[�W�ɕϊ���
			//��������b�Z�[�W�L���[�Ƀ|�X�g����
			TranslateMessage(&msg);

			//���b�Z�[�W�̊��蓖��
			//�E�B���h�E�v���V�[�W���Ń��b�Z�[�W������
			DispatchMessage(&msg);
		}
		else
		{
			pDi->Update();//�L�[��Ԃ̍X�V

			switch (Mode)
			{

			//�X�^�[�g���
			case Game_Mode::StartScreenProcessing:

				break;

			//��������
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

				//�v���C���[����i���������j�Ɉړ�
				Mode = PlayerProcessing;
				break;

			//�v���C���[����i���������j
			case Game_Mode::PlayerProcessing:

				//�Ղ�̐�������
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

					//�v���C���[�����삵�Ă���Ղ�
					PuyoData[0][2].PlayerUse = true;
					PuyoData[0][3].PlayerUse = true;

					//��]�̊�_�ƂȂ�Ղ�
					PuyoData[0][2].RolBase = true;

					//��]�̃t���O�����Z�b�g
					rol = 0;
				}

				//�������x�̃��Z�b�g
				DownSpeed = 1.0;

				//�L�[���͂̏���
				//�ړ�����
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
										//���̃}�X�Ƀf�[�^���ڍs
										PuyoData[y][x + 1].Type = PuyoData[y][x].Type;
										PuyoData[y][x + 1].PlayerUse = PuyoData[y][x].PlayerUse;
										PuyoData[y][x + 1].RolBase = PuyoData[y][x].RolBase;

										//�O�̃}�X�f�[�^�����Z�b�g
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
										//���̃}�X�Ƀf�[�^���ڍs
										PuyoData[y][x - 1].Type = PuyoData[y][x].Type;
										PuyoData[y][x - 1].PlayerUse = PuyoData[y][x].PlayerUse;
										PuyoData[y][x - 1].RolBase = PuyoData[y][x].RolBase;

										//�O�̃}�X�f�[�^�����Z�b�g
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

				//��]����
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
									//���̃}�X�Ƀf�[�^���ڍs
									PuyoData[y + roly][x + rolx].Type = PuyoData[y][x].Type;
									PuyoData[y + roly][x + rolx].PlayerUse = PuyoData[y][x].PlayerUse;
									PuyoData[y + roly][x + rolx].RolBase = PuyoData[y][x].RolBase;

									//�O�̃}�X�f�[�^�����Z�b�g
									PuyoData[y][x].Type = null;
									PuyoData[y][x].PlayerUse = false;
									PuyoData[y][x].RolBase = false;

									//��]�̃t���O�����Z
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
									//���̃}�X�Ƀf�[�^���ڍs
									PuyoData[y + roly][x + rolx].Type = PuyoData[y][x].Type;
									PuyoData[y + roly][x + rolx].PlayerUse = PuyoData[y][x].PlayerUse;
									PuyoData[y + roly][x + rolx].RolBase = PuyoData[y][x].RolBase;

									//�O�̃}�X�f�[�^�����Z�b�g
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

					//��������
					for (int y = GameHeight - 1; y >= 0; y--)
					{
						for (int x = GameWidth; x >= 0; x--)
						{
							//�Ղ悪�v���C���[�����쒆�̂Ղ悩
							if (PuyoData[y][x].PlayerUse == true)
							{
								//���}�X�ɂՂ悪���邩�ǂ���
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
								//��������
								else
								{
									//���̃}�X�Ƀf�[�^���ڍs
									PuyoData[y + 1][x].Type = PuyoData[y][x].Type;
									PuyoData[y + 1][x].PlayerUse = PuyoData[y][x].PlayerUse;
									PuyoData[y + 1][x].RolBase = PuyoData[y][x].RolBase;

									//�O�̃}�X�f�[�^�����Z�b�g
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

					//�A������
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

				//��������
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
									//���̃}�X�Ƀf�[�^���ڍs
									PuyoData[y + 1][x].Type = PuyoData[y][x].Type;
									PuyoData[y + 1][x].PlayerUse = PuyoData[y][x].PlayerUse;
									PuyoData[y + 1][x].RolBase = PuyoData[y][x].RolBase;

									//�O�̃}�X�f�[�^�����Z�b�g
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

			//���Łi�A���j����
			case Game_Mode::ExtinctionProcess:

				//�v���C���[����(�I���\����)�Ɉړ�
				Mode = PlayerProcessing;

				break;

			//�Q�[���I��
			case Game_Mode::GameEndProcessing:

				if (pDi->MouseButton(0))
				{
					Mode = GameStartProcessing;
				}

				break;

			}

			//�`�揈��
			//�o�b�N�o�b�t�@�̃N���A
			if (SUCCEEDED(d3d.BeginScene()))
			{
				d3d.ClearScreen();

				//�t���[��
				spriteImgFrame.Draw(imgFrame);

				//�Ղ�
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

				//�`��I���̍��}
				d3d.EndScene();
				//�o�b�N�o�b�t�@���t�����g�֔��f
				d3d.Present();
			}
		}
	}

	return 0;
};
