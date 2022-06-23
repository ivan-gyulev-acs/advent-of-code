#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <stdlib.h>
#include <vector>

void swap(int& a, int& b)
{
    if(a == b) return;
    a ^= b;
    b ^= a;
    a ^= b;
}

struct Position
{
    Position(int row, int col)
    {
        x = row;
        y = col;
    }
    virtual ~Position()
    {

    }
    Position operator=(Position rhs)
    {
        x = rhs.x;
        y = rhs.y;
    }
    bool operator==(Position rhs)
    {
        if(x == rhs.x && y == rhs.y)
            return true;
        return false;
    }
    
    int x;
    int y;
};

bool isLowPoint(std::vector<Position> lowPoints, Position point)
{
    for(Position pos : lowPoints)
        if(point == pos)
            return true;
    return false;
}

void nullifyMap(std::vector<bool*> map, int length, int height)
{
    for(int a = 0; a < height; a++)
        for(int b = 0; b < length; b++)
            map[a][b] = false;
}

void topX(int* topX, int X, int value)
{
    for(int a = 0; a < X; a++)
    {
        if(value > topX[a])
        {
            for(int b = 0; b < X - a - 1; b++)
            {
                swap(topX[X - b - 1], topX[X - b - 2]);
            }
            topX[a] = value;
            return;
        }
    }
}

int basinSize(std::vector<int*>& heightmap, std::vector<bool*>& basinmap, int& length, int& height, Position point, int area = 0)
{
    if(point.y != 0 && heightmap[point.x][point.y - 1] != 9 && !basinmap[point.x][point.y - 1])
    {
        basinmap[point.x][point.y - 1] = true;
        area += 1 + basinSize(heightmap, basinmap, length, height, Position(point.x, point.y - 1));
    }
    if(point.y != length - 1 && heightmap[point.x][point.y + 1] != 9 && !basinmap[point.x][point.y + 1])
    {
        basinmap[point.x][point.y + 1] = true;
        area += 1 + basinSize(heightmap, basinmap, length, height, Position(point.x, point.y + 1));
    }
    if(point.x != 0 && heightmap[point.x - 1][point.y] != 9 && !basinmap[point.x - 1][point.y])
    {
        basinmap[point.x - 1][point.y] = true;
        area += 1 + basinSize(heightmap, basinmap, length, height, Position(point.x - 1, point.y));
    }
    if(point.x != height - 1 && heightmap[point.x + 1][point.y] != 9 && !basinmap[point.x + 1][point.y])
    {
        basinmap[point.x + 1][point.y] = true;
        area += 1 + basinSize(heightmap, basinmap, length, height, Position(point.x + 1, point.y));
    }
    return area;
}

int main()
{
    int answer = 0;
    int answer2 = 0;

    int height = 0, length = 0;
    std::vector<int*> heightmap;
    std::vector<bool*> basinmap;
    std::vector<Position> lowPoints;
    int top3[3] = {0};

    std::string line;
    std::fstream file;
    file.open("input.txt", std::ios_base::in);
    while(!file.eof())
    {
        std::getline(file, line);
        height++;
        length = line.length();
        int* row = new int[length];
        bool* row2 = new bool[length];
        for(int a = 0; a < length; a++)
        {
            row[a] = line[a] - '0';
            row2[a] = false;
        }
        heightmap.push_back(row);
        basinmap.push_back(row2);
    }
    file.close();

    for(int a = 0; a < height; a++)
    {
        for(int b = 0; b < length; b++)
        {
            if(b != 0           && heightmap[a][b - 1] <= heightmap[a][b]) continue;
            if(b != length - 1  && heightmap[a][b + 1] <= heightmap[a][b]) continue;
            if(a != 0           && heightmap[a - 1][b] <= heightmap[a][b]) continue;
            if(a != height - 1  && heightmap[a + 1][b] <= heightmap[a][b]) continue;
            answer += heightmap[a][b] + 1;
            lowPoints.push_back(Position(a, b));
        }
    }

    for(Position pos : lowPoints)
        topX(top3, 3, basinSize(heightmap, basinmap, length, height, pos));

    answer2 = 1;
    for(int num : top3) answer2 *= num;

    std::cout << "Advent of Code 2021 | Day 09 | Part 1 | Answer: " << answer << std::endl;
    std::cout << "Advent of Code 2021 | Day 09 | Part 2 | Answer: " << answer2 << std::endl;

    for(int a = 0; a < height; a++)
    {
        delete[] heightmap[a];
        delete[] basinmap[a];
    }
    return 0;
}