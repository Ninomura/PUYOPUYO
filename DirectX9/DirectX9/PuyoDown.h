#include"ExternGV.h"

class Puyo
{
public:
	Puyo();
	~Puyo();

	void Test(int a, int b, int y, int x);
	void Test2(int a, int b, int y, int x);
	void Test3(int a, int b, int y, int x);
	void Test4(int a, int b, int y, int x);

private:

};

Puyo::Puyo()
{
}

Puyo::~Puyo()
{
}

void Puyo::Test(int a, int b, int y, int x)
{
	if (PuyoData[y][x].Link < 3)
	{
		if (a > 0)
		{
			if (PuyoData[a - 1][b].Type == PuyoData[a][b].Type)
			{
				PuyoData[y][x].Link++;
				Test(a - 1, b, y, x);
			}
		}

		if (b < GameWidth - 1)
		{
			if (PuyoData[a][b + 1].Type == PuyoData[a][b].Type)
			{
				PuyoData[y][x].Link++;
				Test3(a, b + 1, y, x);
			}
		}

		if (b > 0)
		{
			if (PuyoData[a][b - 1].Type == PuyoData[a][b].Type)
			{
				PuyoData[y][x].Link++;
				Test4(a, b - 1, y, x);
			}
		}
	}
}

void Puyo::Test2(int a, int b, int y, int x)
{
	if (PuyoData[y][x].Link < 3)
	{

		if (a < GameHeight - 1)
		{
			if (PuyoData[a + 1][b].Type == PuyoData[a][b].Type)
			{
				PuyoData[y][x].Link++;
				Test2(a + 1, b, y, x);
			}
		}

		if (b < GameWidth - 1)
		{
			if (PuyoData[a][b + 1].Type == PuyoData[a][b].Type)
			{
				PuyoData[y][x].Link++;
				Test3(a, b + 1, y, x);
			}
		}

		if (b > 0)
		{
			if (PuyoData[a][b - 1].Type == PuyoData[a][b].Type)
			{
				PuyoData[y][x].Link++;
				Test4(a, b - 1, y, x);
			}
		}
	}
}

void Puyo::Test3(int a, int b, int y, int x)
{
	if (PuyoData[y][x].Link < 3)
	{
		if (a > 0)
		{
			if (PuyoData[a - 1][b].Type == PuyoData[a][b].Type)
			{
				PuyoData[y][x].Link++;
				Test(a - 1, b, y, x);
			}
		}

		if (a < GameHeight - 1)
		{
			if (PuyoData[a + 1][b].Type == PuyoData[a][b].Type)
			{
				PuyoData[y][x].Link++;
				Test2(a + 1, b, y, x);
			}
		}

		if (b < GameWidth - 1)
		{
			if (PuyoData[a][b + 1].Type == PuyoData[a][b].Type)
			{
				PuyoData[y][x].Link++;
				Test3(a, b + 1, y, x);
			}
		}
	}
}

void Puyo::Test4(int a, int b, int y, int x)
{
	if (PuyoData[y][x].Link < 3)
	{
		if (a > 0)
		{
			if (PuyoData[a - 1][b].Type == PuyoData[a][b].Type)
			{
				PuyoData[y][x].Link++;
				Test(a - 1, b, y, x);
			}
		}

		if (a < GameHeight - 1)
		{
			if (PuyoData[a + 1][b].Type == PuyoData[a][b].Type)
			{
				PuyoData[y][x].Link++;
				Test2(a + 1, b, y, x);
			}
		}

		if (b > 0)
		{
			if (PuyoData[a][b - 1].Type == PuyoData[a][b].Type)
			{
				PuyoData[y][x].Link++;
				Test4(a, b - 1, y, x);
			}
		}
	}
}