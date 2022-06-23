#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <stdlib.h>
#include <vector>
#include <sstream>

void fold(bool**& page, int& width, int& height, int fold)
{
    bool** pageCopy = page;
    
    if(fold < 0)
    {
        fold *= -1;
        page = new bool*[fold];
        for(int a = 0; a < fold; a++)
        {
            page[a] = new bool[width];
            for(int b = 0; b < width; b++)
                page[a][b] = (pageCopy[a][b] || pageCopy[fold * 2 - a][b]);
        }
        for(int a = 0; a < height; a++)
            delete[] pageCopy[a];
        delete[] pageCopy;
        height = fold;
    }
    else
    {
        page = new bool*[height];
        for(int a = 0; a < height; a++)
        {
            page[a] = new bool[fold];
            for(int b = 0; b < fold; b++)
                page[a][b] = pageCopy[a][b] || pageCopy[a][fold * 2 - b];
        }
        for(int a = 0; a < height; a++)
            delete[] pageCopy[a];
        delete[] pageCopy;
        width = fold;
    }
}

int main()
{
    system("cls");
    int answer = 0;
    std::stringstream answer2;

    int width = 0;
    int height = 0;
    int foldCount = 0;
    bool** page;
    int* folds;
    bool alphabet[26][24] = 
    {
        {1,1,1,1,1,0,0,1,1,0,0,1,1,1,1,1,1,0,0,1,1,0,0,1},
        {1,1,1,0,1,0,0,1,1,1,1,0,1,0,0,1,1,0,0,1,1,1,1,0},
        {0,1,1,1,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,0,1,1,1},
        {1,1,1,0,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,1,1,0},
        {1,1,1,1,1,0,0,0,1,1,1,1,1,0,0,0,1,0,0,0,1,1,1,1},
        {1,1,1,1,1,0,0,0,1,1,1,1,1,0,0,0,1,0,0,0,1,0,0,0},
        {0,1,1,0,1,0,0,1,1,0,0,0,1,0,1,1,1,0,0,1,0,1,1,1},
        {1,0,0,1,1,0,0,1,1,1,1,1,1,0,0,1,1,0,0,1,1,0,0,1},
        {1,1,1,1,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,1,1,1,1},
        {1,1,1,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,1,1,1,0},
        {1,0,0,1,1,0,1,0,1,1,0,0,1,0,1,0,1,0,1,0,1,0,0,1},
        {1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,1,1,1},
        {1,0,0,1,0,1,1,0,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1},
        {1,0,0,1,1,1,0,1,1,1,0,1,1,0,1,1,1,0,1,1,1,0,0,1},
        {1,1,1,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,1,1,1},
        {1,1,1,0,1,0,0,1,1,0,0,1,1,1,1,0,1,0,0,0,1,0,0,0},
        {1,1,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,1,1,0,0,0,0,1},
        {1,1,1,0,1,0,0,1,1,0,0,1,1,1,1,0,1,0,1,0,1,0,0,1},
        {0,1,1,1,1,0,0,0,1,1,1,0,0,0,0,1,0,0,0,1,1,1,1,0},
        {1,1,1,1,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0},
        {1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,1,1,1},
        {1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,0,1,1,0},
        {1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,0,1,1,0,1,0,0,1},
        {1,0,0,1,1,0,0,1,0,1,1,0,1,0,0,1,1,0,0,1,1,0,0,1},
        {1,0,0,1,1,0,0,1,1,1,1,1,0,0,0,1,0,0,0,1,1,1,1,0},
        {1,1,1,1,0,0,0,1,0,0,1,0,0,1,0,0,1,0,0,0,1,1,1,1}
    };

    std::string line;
    std::fstream file;
    file.open("input.txt", std::ios_base::in);
    for(int position[2]; !file.eof();)
    {
        std::getline(file, line);
        if(line.length() == 0) break;
        position[0] = stoi(line.substr(0, line.find(',')));
        position[1] = stoi(line.substr(line.find(',') + 1));
        if(width < position[0] + 1) width = position[0] + 1;
        if(height < position[1] + 1) height = position[1] + 1;
    }
    while(!file.eof())
    {
        std::getline(file, line);
        foldCount++;
    }
    
    page = new bool*[height];
    for(int a = 0; a < height; a++)
    {
        page[a] = new bool[width];
        for(int b = 0; b < width; b++)
            page[a][b] = false;
    }
    folds = new int[foldCount];
    file.seekg(0, std::ios_base::beg);

    while(!file.eof())
    {
        std::getline(file, line);
        if(line.length() == 0) break;
        page[stoi(line.substr(line.find(',') + 1))][stoi(line.substr(0, line.find(',')))] = true;
    }
    for(int a = 0; a < foldCount; a++)
    {
        std::getline(file, line);
        folds[a] = (line.find('x') != line.npos ? 1 : -1) * stoi(line.substr(line.find('=') + 1));
    }
    file.close();
    
    for(int a = 0; a < foldCount; a++)
    {
        fold(page, width, height, folds[a]);
        if(a == 0)
            for(int b = 0; b < height; b++)
                for(int c = 0; c < width; c++)
                    answer += (page[b][c] ? 1 : 0);
    }

    for(int a = 0; a < 8; a++)
        for(int b = 0; b < 26; b++)
            for(int c = 0; c < 6; c++)
                for(int d = 0; d < 4; d++)
                {
                    if(page[c][a * 5 + d] != alphabet[b][c * 4 + d])
                    {
                        c = 6;
                        break;
                    }
                    if(c * d == 15) answer2 << (char)('A' + b);
                }
    
    system("cls");
    std::cout << "Advent of Code 2021 | Day 13 | Part 1 | Answer: " << answer << std::endl;
    std::cout << "Advent of Code 2021 | Day 13 | Part 2 | Answer: " << answer2.str() << std::endl;

    for(int a = 0; a < height; a++)
        delete[] page[a];
    delete[] page;
    delete[] folds;
    return 0;
}
