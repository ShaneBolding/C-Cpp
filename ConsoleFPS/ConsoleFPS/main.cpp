// main.cpp : This file contains the 'main' function. Program execution begins and ends there.
#include <iostream>
#include <chrono>
#include <vector>
#include <algorithm>
using namespace std;

#include <Windows.h> //utilize this to get the cmd screen buffer

int nScreenWidth = 120;
int nScreenHeight = 40;

float playerX = 8.0f, playerY = 8.0f, playerA = 0.0f;

int nMapHeight = 16, nMapWidth = 16;

float FOV = 3.14159 / 4.0;
float fDepth = 16;

int main()
{
    //set up screen
    wchar_t* screen = new wchar_t[nScreenWidth * nScreenHeight]; //creates screen with unicode of preset size
    HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL); //create screen buffer
    SetConsoleActiveScreenBuffer(hConsole); //tell buffer it will be our console
    DWORD dwBytesWritten = 0;

    wstring map;
    map += L"################";
    map += L"#..............#";
    map += L"#..............#";
    map += L"#..............#";
    map += L"#..........#...#";
    map += L"#..........#...#";
    map += L"#..............#";
    map += L"#..............#";
    map += L"#..............#";
    map += L"#..............#";
    map += L"#..............#";
    map += L"#..............#";
    map += L"#.......########";
    map += L"#..............#";
    map += L"#..............#";
    map += L"################";

    auto tp1 = chrono::system_clock::now();
    auto tp2 = chrono::system_clock::now();
    //game
    while (true)
    {
        //time
        tp2 = chrono::system_clock::now(); //current time
        chrono::duration<float> dt = tp2 - tp1; //delta time
        tp1 = tp2;
        float fdt = dt.count(); //turn to point
        //controls
        // handle CCW rotation
        if (GetAsyncKeyState((unsigned short)'A') && 0x8000) //LEFT
        {
            playerA -= 0.8f * fdt;
        }
        if (GetAsyncKeyState((unsigned short)'D') && 0x8000) //RIGHT
        {
            playerA += 0.8f * fdt;
        }
        if (GetAsyncKeyState((unsigned short)'W') && 0x8000) //UP
        {
            playerX += sinf(playerA) * 5.0f * fdt;
            playerY += cosf(playerA) * 5.0f * fdt;
            
            //collision detection
            if (map[(int)playerY * nMapWidth + playerX] == '#')
            {
                playerX -= sinf(playerA) * 5.0f * fdt;
                playerY -= cosf(playerA) * 5.0f * fdt;
            }
        }
        if (GetAsyncKeyState((unsigned short)'S') && 0x8000) //DOWN
        {
            playerX -= sinf(playerA) * 5.0f * fdt;
            playerY -= cosf(playerA) * 5.0f * fdt;
            //collision detection
            if (map[(int)playerY * nMapWidth + playerX] == '#')
            {
                playerX += sinf(playerA) * 5.0f * fdt;
                playerY += cosf(playerA) * 5.0f * fdt;
            }
        }
        for (int x = 0; x < nScreenWidth; x++) //for each column find the projected ray angle
        {
            float fRayA = (playerA - FOV / 2.0f) + ((float)x / (float)nScreenWidth) * FOV;

            float fDistToWall = 0; 
            bool hitWall = false;
            bool boundry = false;

            float fEyeX = sinf(fRayA); // unit vector for player ray
            float fEyeY = cosf(fRayA);

            while (!hitWall && fDistToWall < fDepth)    //test if player view hits wall
            {
                fDistToWall += 0.1f;
                int testX = (int)(playerX + fEyeX * fDistToWall);
                int testY = (int)(playerY + fEyeY * fDistToWall);

                //test if the ray is OOB
                if (testX < 0 || testX >= nMapWidth || testY < 0 || testY >= nMapHeight)
                {
                    hitWall = true;
                    fDistToWall = fDepth;
                }
                else 
                {
                    // ray is inbounds therefore test to see if the ray cell is a wall block
                    if (map[testY * nMapWidth + testX] == '#')
                    {
                        hitWall = true;

                        vector<pair<float, float>> p; // distance to perfect corner and dot product

                        for (int tx = 0; tx < 2; tx++)
                        {
                            for (int ty = 0; ty < 2; ty++)
                            {
                                float vy = (float)testY + ty - playerY; //vector from the player to perfect corners
                                float vx = (float)testX + tx - playerX;
                                float mag = sqrt(vx * vx + vy * vy);    //get mag
                                float dot = (fEyeX * vx / mag) + (fEyeY * vy / mag);    //get dot prod
                                p.push_back(make_pair(mag, dot));
                            }
                        }
                        // Sort pairs from closest to farthest
                        sort(p.begin(), p.end(), [](const pair<float, float>& left, const pair<float, float>& right) {return left.first < right.first; }); //sorts based on dist

                        float fBound = 0.01;
                        if (acos(p.at(0).second) < fBound) boundry = true;
                        if (acos(p.at(1).second) < fBound) boundry = true;
                        if (acos(p.at(2).second) < fBound) boundry = true;
                    }
                }
            }
            //calculate the distance to the ceiling to floor
            int nCeiling = (float)(nScreenHeight / 2.0) - nScreenHeight / ((float)fDistToWall); //half the screenheight - a portion of screenheight relative to dist to wall
            int nFloor = nScreenHeight - nCeiling;

            //shading for distance effect
            short nShade = ' ';

            if (fDistToWall <= fDepth / 4.0f)         nShade = 0x2588;   //very close
            else if (fDistToWall <= fDepth / 3.0f)    nShade = 0x2593;
            else if (fDistToWall <= fDepth / 2.0f)    nShade = 0x2592;
            else if (fDistToWall <= fDepth)           nShade = 0x2591;
            else                                      nShade = ' ';

            if (boundry) nShade = ' ';
                
            //draw in column
            for (int y = 0; y < nScreenHeight; y++)
            {
                if (y < nCeiling)
                    screen[y * nScreenWidth + x] = ' ';
                else if(y > nCeiling && y <= nFloor)
                    screen[y * nScreenWidth + x] = nShade;
                else
                {
                    //shade floor
                    short fShade = ' ';
                    float b = 1.0f - (((float)y - nScreenHeight / 2.0f) / ((float)nScreenHeight / 2.0f));
                    if (b < 0.25)
                        fShade = '#';
                    else if (b < 0.5)          
                        fShade = 'x';
                    else if (b < 0.75)          
                        fShade = '.';
                    else if (b < 0.9)          
                        fShade = '-';
                    else                        
                        fShade = ' ';
                    screen[y * nScreenWidth + x] = fShade;
                }
            }
        }
        //display stats
        swprintf_s(screen, 39, L"X=%3.2f, Y=%3.2f, A=%3.2f FPS=%3.2f ", playerX, playerY, playerA, (1.0f / fdt));

        //display minimap
        for (int mx = 0; mx < nMapWidth; mx++)
        {
            for (int my = 0; my < nMapHeight; my++)
            {
                screen[(my + 1) * nScreenWidth + mx] = map[my * nMapWidth + mx];
            }
        }
        screen[((int)playerY + 1) * nScreenWidth + (int)playerX] = 'P';

        screen[nScreenHeight * nScreenWidth - 1] = '\0';
        WriteConsoleOutputCharacter(hConsole, screen, nScreenHeight * nScreenWidth, { 0,0 }, &dwBytesWritten); //write to the top left to prevent scroll
    }
    return 0;
}
