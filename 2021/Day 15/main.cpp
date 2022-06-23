#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cmath>
#include <vector>

using num8  = unsigned char;
using num16 = unsigned short;
using num64 = unsigned long long;

const num8 LEFT = 0;
const num8 RIGHT = 1;
const num8 UP = 2;
const num8 DOWN = 3;
num8** map = nullptr;
num8 height = 0;
num8 width = 0;

void InitializeMap(num8 inputHeight, num8 inputWidth)
{
    if(map != nullptr) return;
    height = inputHeight;
    width = inputWidth;
    map = new num8*[height];
    for(num16 a = 0; a < height; ++a)
        map[a] = new num8[width];
}

void InitializeMap()
{
    if(map != nullptr) return;
    map = new num8*[height];
    for(int a = 0; a < height; ++a)
        map[a] = new num8[width];
}

void DeleteMap()
{
    for(int a = 0; a < height; ++a)
        delete[] map[a];
    delete[] map;
}

// void PrintMap()
// {
//     for(num8 a = 0; a < height; ++a)
//         for(num8 b = 0; b < width; ++b)
//             std::cout << (int)map[a][b] << (b != width - 1 ? (char)0 : '\n');
// }

struct Step
{
    num16 risk;
    num8 x;
    num8 y;
    Step()
    {
        risk = 0;
        x = 0;
        y = 0;
    }
    Step(num16 inputRisk)
    {
        risk = inputRisk;
        x = 0;
        y = 0;
    }
    Step(num16 inputRisk, num8 inputX, num8 inputY)
    {
        risk = inputRisk;
        x = inputX;
        y = inputY;
    }
    void operator=(Step inputStep)
    {
        risk = inputStep.risk;
        x = inputStep.x;
        y = inputStep.y;
    }
};

Step paths[4];

Step traverse(num8 x, num8 y, num8 step, num8 moveHistory = 0, num16 risk = 0)
{
    // std::cout << "STEP: " << (num16)step << std::endl;
    // std::cout << "WIDTH: " << (num16)width << std::endl;
    // std::cout << "HEIGHT: " << (num16)height << std::endl;
    // std::cout << "X: " << (num16)x << std::endl;
    // std::cout << "Y: " << (num16)y << std::endl;
    // std::cout << "firstMove: " << (num16)(moveHistory & 3) << " != " << (num16)RIGHT << " && " << "secondMove: " << (num16)(moveHistory >> 2 & 3) << " != " << (num16)RIGHT << std::endl;
    // std::cout << "firstMove: " << (num16)(moveHistory & 3) << " != " << (num16)LEFT  << " && " << "secondMove: " << (num16)(moveHistory >> 2 & 3) << " != " << (num16)LEFT  << std::endl;
    // std::cout << "firstMove: " << (num16)(moveHistory & 3) << " != " << (num16)DOWN  << " && " << "secondMove: " << (num16)(moveHistory >> 2 & 3) << " != " << (num16)DOWN  << std::endl;
    // std::cout << "firstMove: " << (num16)(moveHistory & 3) << " != " << (num16)UP    << " && " << "secondMove: " << (num16)(moveHistory >> 2 & 3) << " != " << (num16)UP    << std::endl;
    // std::cout << (num16)x << ',' << (num16)y << std::endl;
    if(step == 0 || (x == width - 1 && y == height - 1)) return Step(risk, x, y);
    num8 counter = 0;
    if(x != 0          && (moveHistory & 3) != RIGHT && (moveHistory >> 2 & 3) != RIGHT)paths[counter++] = (traverse(x - 1, y, step - 1, moveHistory << 2 | LEFT , risk + map[y][x - 1]));
    if(x != width - 1  && (moveHistory & 3) != LEFT  && (moveHistory >> 2 & 3) != LEFT )paths[counter++] = (traverse(x + 1, y, step - 1, moveHistory << 2 | RIGHT, risk + map[y][x + 1]));
    if(y != 0          && (moveHistory & 3) != DOWN  && (moveHistory >> 2 & 3) != DOWN )paths[counter++] = (traverse(x, y - 1, step - 1, moveHistory << 2 | UP   , risk + map[y - 1][x]));
    if(y != height - 1 && (moveHistory & 3) != UP    && (moveHistory >> 2 & 3) != UP   )paths[counter++] = (traverse(x, y + 1, step - 1, moveHistory << 2 | DOWN , risk + map[y + 1][x]));
    if(counter == 0) return Step(INT16_MAX);
    
    for(num8 a = 1; a < counter; ++a)
        if((float)paths[a].risk / ((num16)(paths[a].x + paths[a].y) * 5) < (float)paths[0].risk / ((num16)(paths[0].x + paths[0].y) * 5))
            paths[0] = paths[a];

    return paths[0];
}

int main()
{
    num16 answer = 0;

    Step jump;

    std::string line;
    std::fstream file("input.txt", std::ios_base::in);
    while(!file.eof())
    {
        std::getline(file, line);
        ++height;
        if(width < line.length())
            width = line.length();
    }
    InitializeMap(height, width);
    file.seekg(0, std::ios_base::beg);
    for(num16 a = 0; a < height; ++a)
    {
        std::getline(file, line);
        for(num16 b = 0; b < width; ++b)
            map[a][b] = line[b] - '0';
    }
    file.close();

    while(jump.x != width - 1 || jump.y != height - 1)

        jump = traverse(jump.x, jump.y, 12, DOWN << 2 | RIGHT);
        answer += jump.risk;
    }
    std::cout << "Risk: " << answer << "; Position: " << (num16)jump.x << ',' << (num16)jump.y << std::endl;

    // std::cout << "Advent of Code 2021 | Day 15 | Part 1 | Answer: " << answer << std::endl;

    DeleteMap();
    return 0;
}