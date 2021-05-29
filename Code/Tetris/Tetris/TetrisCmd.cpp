#include <iostream>
#include <thread>
#include <vector>
using namespace std;

#include <stdio.h>
#include <Windows.h>

wstring tetromino[7];
int nFieldWidth = 12;
int nFieldHeight = 18;
unsigned char* field = nullptr;

//console screen size
int nScreenHeight = 30;
int nScreenWidth = 80;

int rotatePiece(int x, int y, int r)
{
	switch (r % 4)
	{
	case 0: return y * 4 + x;	//0 degree turn
	case 1: return 12 + y - (x * 4);
	case 2: return 15 - (y * 4) - x;
	case 3: return 3 - y + (x * 4);
	}
	return 0;
}

bool doesTetrominoFit(int nTetromino, int rotation, int posX, int posY)
{
	for (int x = 0; x < 4; x++)
	{
		for (int y = 0; y < 4; y++)
		{
			//get index into piece 
			int pieceIndex = rotatePiece(x, y, rotation);

			//get indec into field
			int fieldIndex = (posY + y) * nFieldWidth + (posX + x);

			if (posX + x >= 0 && posX + x < nFieldWidth)
			{
				if (posY + y >= 0 && posY + y < nFieldHeight)
				{
					if (tetromino[nTetromino][pieceIndex] == L'X' && field[fieldIndex] != 0)
					{
						return false; //failure on the first hit
					}
				}
			}

		}
	}
}

int main()
{
	// Create Screen Buffer
	wchar_t* screen = new wchar_t[nScreenWidth * nScreenHeight];
	for (int i = 0; i < nScreenWidth * nScreenHeight; i++) screen[i] = L' ';
	HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleActiveScreenBuffer(hConsole);
	DWORD dwBytesWritten = 0;

	//create the assets
	tetromino[0].append(L"..X.");
	tetromino[0].append(L"..X.");
	tetromino[0].append(L"..X.");
	tetromino[0].append(L"..X.");

	tetromino[1].append(L"..X.");
	tetromino[1].append(L".XX.");
	tetromino[1].append(L".X..");
	tetromino[1].append(L"....");

	tetromino[2].append(L".X..");
	tetromino[2].append(L".XX.");
	tetromino[2].append(L"..X.");
	tetromino[2].append(L"....");

	tetromino[3].append(L"....");
	tetromino[3].append(L".XX.");
	tetromino[3].append(L".XX.");
	tetromino[3].append(L"....");

	tetromino[4].append(L"..X.");
	tetromino[4].append(L".XX.");
	tetromino[4].append(L"..X.");
	tetromino[4].append(L"....");

	tetromino[5].append(L"....");
	tetromino[5].append(L".XX.");
	tetromino[5].append(L"..X.");
	tetromino[5].append(L"..X.");

	tetromino[6].append(L"....");
	tetromino[6].append(L".XX.");
	tetromino[6].append(L".X..");
	tetromino[6].append(L".X..");

	//initialize field 
	field = new unsigned char[nFieldWidth * nFieldHeight]; // Create play field buffer
	for (int x = 0; x < nFieldWidth; x++) // Board Boundary
		for (int y = 0; y < nFieldHeight; y++)
			field[y * nFieldWidth + x] = (x == 0 || x == nFieldWidth - 1 || y == nFieldHeight - 1) ? 9 : 0;


	bool gameOver = false;
	//vars needed for keeping up with game
	int currentPiece = rand() % 7;
	int currentRotation = 0;
	int currentX = nFieldWidth / 2;
	int currentY = 0;
	bool bKey[4];
	bool rotateHold = false;

	int speed = 20;
	int speedCounter = 0;
	bool forceDown = false;
	int pieceCounter = 0;
	int score = 0;

	vector<int> lines;

	while (!gameOver)
	{
		//timing
		this_thread::sleep_for(50ms);
		speedCounter++;
		forceDown = (speedCounter == speed);


		//inputs
		for (int k = 0; k < 4; k++)
		{														// ->  <-  v 'Z'
			bKey[k] = (0x8000 & GetAsyncKeyState((unsigned char)("\x27\x25\x28Z"[k]))) != 0;
		}
		//game logic
		if (bKey[1])
		{
			if (doesTetrominoFit(currentPiece, currentRotation, currentX - 1, currentY))
			{
				currentX--;
			}
		}
		if (bKey[0])
		{
			if (doesTetrominoFit(currentPiece, currentRotation, currentX + 1, currentY))
			{
				currentX++;
			}
		}
		if (bKey[2])
		{
			if (doesTetrominoFit(currentPiece, currentRotation, currentX, currentY + 1))
			{
				currentY++;
			}
		}
		if (bKey[3])
		{
			if (!rotateHold && doesTetrominoFit(currentPiece, currentRotation + 1, currentX, currentY))
			{
				currentRotation++;
			}
			rotateHold = true;
		}
		else rotateHold = false;

		if (forceDown)
		{
			if(doesTetrominoFit(currentPiece, currentRotation, currentX, currentY + 1))
			{
				currentY++;
			}
			else
			{
				//lock the piece in place on field
				for (int px = 0; px < 4; px++)
					for (int py = 0; py < 4; py++)
						if (tetromino[currentPiece][rotatePiece(px, py, currentRotation)] != L'.')
							field[(currentY + py) * nFieldWidth + (currentX + px)] = currentPiece + 1;
				
				//increase difficultly as more pieces are played
				pieceCounter++;
				if (pieceCounter % 10 == 0)
				{
					if (speed >= 10) speed--;
				}
				
				//check for horizontal lines
				for (int py = 0; py < 4; py++)
				{
					if (currentY + py < nFieldHeight - 1)
					{
						bool completeLine = true;
						for (int px = 1; px < nFieldWidth - 1; px++)
						{
							completeLine &= (field[(currentY + py) * nFieldWidth + px]) != 0;
						}

						if (completeLine)
						{
							//set line to = then remove line
							for (int px = 1; px < nFieldWidth - 1; px++)
							{
								field[(currentY + py) * nFieldWidth + px] = 8;
							}
							lines.push_back(currentY + py);
						}
					}
				}

				//scoring
				score += 25;
				if (!lines.empty())
				{
					score += (1 << lines.size()) * 100;
				}

				//choose next piece
				currentX = nFieldWidth / 2;
				currentY = 0;
				currentRotation = 0;
				currentPiece = rand() % 7;
				//if piece does not fit
				gameOver = !doesTetrominoFit(currentPiece, currentRotation, currentX, currentY);
			}
			speedCounter = 0;
		}

		//Rendering

		// Draw Field
		for (int x = 0; x < nFieldWidth; x++)
		{
			for (int y = 0; y < nFieldHeight; y++)
			{
				screen[(y + 2) * nScreenWidth + (x + 2)] = L" ABCDEFG=#"[field[y * nFieldWidth + x]];
			}
		}

		// Draw player piece
		for (int px = 0; px < 4; px++)
			for (int py = 0; py < 4; py++)
				if (tetromino[currentPiece][rotatePiece(px, py, currentRotation)] != L'.')
					screen[(currentY + py + 2) * nScreenWidth + (currentX + px + 2)] = currentPiece + 65;
				
		// Draw Score
		swprintf_s(&screen[2 * nScreenWidth + nFieldWidth + 6], 16, L"SCORE: %8d", score);

		if (!lines.empty())
		{
			//display frame (draw lines)
			WriteConsoleOutputCharacter(hConsole, screen, nScreenWidth* nScreenHeight, { 0,0 }, & dwBytesWritten);
			this_thread::sleep_for(400ms); // Delay a bit

			for (auto& v : lines)
				for (int px = 1; px < nFieldWidth - 1; px++)
				{
					for (int py = v; py > 0; py--)
						field[py * nFieldWidth + px] = field[(py - 1) * nFieldWidth + px];
					field[px] = 0;
				}

			lines.clear();
		}

		//display the frame
		WriteConsoleOutputCharacter(hConsole, screen, nScreenWidth * nScreenHeight, { 0, 0 }, &dwBytesWritten);
	}

	CloseHandle(hConsole);
	cout << "Game Over" << endl << "Score: " << score << endl;
	system("pause");

	return 0;
}