#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <stdlib.h>
#include <vector>

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
        return *this;
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

bool isValidPosition(Position pos, int length, int height)
{
    if(pos.x < 0 || pos.x >= length) return false;
    if(pos.y < 0 || pos.y >= height) return false;
    return true;
}

struct Octopus
{
    Octopus()
    {
        energyLevel = 0;
        hasLitUp = false;
    }
    Octopus(int el)
    {
        energyLevel = el;
        hasLitUp = false;
    }
    Octopus operator++(int increment)
    {
        energyLevel++;
        return *this;
    }
    bool operator<(int el)
    {
        return energyLevel < el;
    }
    bool operator>(int el)
    {
        return energyLevel > el;
    }
    void operator=(int el)
    {
        energyLevel = el;
    }
    bool operator==(int el)
    {
        return energyLevel == el;
    }
    void operator=(bool hlu)
    {
        hasLitUp = hlu;
    }
    bool operator==(bool hlu)
    {
        return hasLitUp == hlu;
    }
    int energyLevel;
    bool hasLitUp;
};

void flash(Octopus** grid, Position pos)
{
    if(grid[pos.x][pos.y] == true) return;
    if(grid[pos.x][pos.y] < 10) return;
    
    grid[pos.x][pos.y] = true;
    for(int a = pos.x - 1; a < pos.x + 2; a++)
        for(int b = pos.y - 1; b < pos.y + 2; b++)
            if(isValidPosition(Position(a, b), 10, 10))
            {
                grid[a][b]++;
                flash(grid, Position(a, b));
            }
}

int step(Octopus** grid)
{
    int flashes = 0;

    for(int a = 0; a < 10; a++)
        for(int b = 0; b < 10; b++)
            grid[a][b]++;
    
    for(int a = 0; a < 10; a++)
        for(int b = 0; b < 10; b++)
            if(!grid[a][b].hasLitUp && grid[a][b].energyLevel > 8)
                flash(grid, Position(a, b));

    for(int a = 0; a < 10; a++)
        for(int b = 0; b < 10; b++)
            if(grid[a][b].hasLitUp)
            {
                flashes++;
                grid[a][b] = false;
                grid[a][b] = 0;
            }
    
    return flashes;
}

int main()
{
    int answer = 0;
    int answer2 = 0;

    Octopus** grid = new Octopus*[10];
    for(int a = 0; a < 10; a++)
        grid[a] = new Octopus[10];

    std::string line;
    std::fstream file;
    file.open("input.txt", std::ios_base::in);
    for(int a = 0; a < 10; a++)
    {
        std::getline(file, line);
        for(int b = 0; b < 10; b++)
            grid[a][b] = line[b] - '0';
    }
    file.close();

    for(int a = 0, flashes = 0; flashes != 100; a++)
    {
        flashes = step(grid);
        if(a < 100) answer += flashes;
        answer2 = a + 1;
    }

    std::cout << "Advent of Code 2021 | Day 11 | Part 1 | Answer: " << answer << std::endl;
    std::cout << "Advent of Code 2021 | Day 11 | Part 2 | Answer: " << answer2 << std::endl;

    for(int a = 0; a < 10; a++)
        delete[] grid[a];
    delete[] grid;

    return 0;
}
