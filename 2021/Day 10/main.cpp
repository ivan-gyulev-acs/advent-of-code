#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <stdlib.h>
#include <vector>

void swap(long long& a, long long& b)
{
    if(a == b) return;
    a ^= b;
    b ^= a;
    a ^= b;
}

void heapify(std::vector<long long>& input, int length, int index = 0)
{
    if (4 * index + 3 < length)
        heapify(input, length, 2 * index + 1);
    if (4 * index + 5 < length)
        heapify(input, length, 2 * index + 2);

    if (2 * index + 1 < length)
        if (input[2 * index + 1] > input[index])
            swap(input[2 * index + 1], input[index]);
    if (2 * index + 2 < length)
        if (input[2 * index + 2] > input[index])
            swap(input[2 * index + 2], input[index]);
}

void heapsort(std::vector<long long>& input, int length)
{
    int counter = length;
    while (counter > 1)
    {
        heapify(input, counter--);
        swap(input[0], input[counter]);
    }
}

struct Triple
{
    Triple(char k, char v, int s)
    {
        key = k;
        value = v;
        score = s;
    }
    char key;
    char value;
    int score;
};

char getValue(std::vector<Triple>& dictionary, char key)
{
    for(Triple triplet : dictionary)
        if(key == triplet.key)
            return triplet.value;
    return '\n';
}

int getScore(std::vector<Triple>& dictionary, char value)
{
    for(Triple triplet : dictionary)
        if(value == triplet.value)
            return triplet.score;
    return INT_MIN / 10;
}

int getIndex(std::vector<Triple>& dictionary, char key)
{
    for(int a = 0; a < dictionary.size(); a++)
        if(key == dictionary[a].key)
            return a;
    return -1;
}

bool isCorrupt(std::vector<int> corruptLines, int lineIndex)
{
    for(int line : corruptLines)
        if(line == lineIndex)
            return true;
    return false;
}

int main()
{
    int answer = 0;
    long long answer2 = 0;

    std::vector<Triple> dictionary;
    dictionary.push_back(Triple('(', ')', 3));
    dictionary.push_back(Triple('[', ']', 57));
    dictionary.push_back(Triple('{', '}', 1197));
    dictionary.push_back(Triple('<', '>', 25137));
    std::vector<std::string> codeLines;
    std::vector<char> blocks;
    std::vector<long long> completionScores;

    std::string line;
    std::fstream file;
    file.open("input.txt", std::ios_base::in);
    while(!file.eof())
    {
        std::getline(file, line);
        codeLines.push_back(line);
    }
    file.close();

    bool corruptedLineFlag = false;
    for(int a = 0; a < codeLines.size(); a++)
    {
        for(int b = 0; b < codeLines[a].length(); b++)
        {
            if(codeLines[a][b] == '(' || codeLines[a][b] == '[' || codeLines[a][b] == '{' || codeLines[a][b] == '<')
                blocks.push_back(codeLines[a][b]);
            else
                if(blocks.size() == 0 || getValue(dictionary, blocks.back()) != codeLines[a][b])
                {
                    corruptedLineFlag = true;
                    answer += getScore(dictionary,  codeLines[a][b]);
                    break;
                }
                else
                    blocks.pop_back();
        }
        if(!corruptedLineFlag)
        {
            completionScores.push_back(0);
            for(auto it = blocks.end() - 1; it >= blocks.begin(); it--)
                completionScores.back() = completionScores.back() * 5 + getIndex(dictionary, *it) + 1;
        }
        else
            corruptedLineFlag = false;
        blocks.clear();
    }

    heapsort(completionScores, completionScores.size());
    answer2 = completionScores[completionScores.size() / 2];

    std::cout << "Advent of Code 2021 | Day 10 | Part 1 | Answer: " << answer << std::endl;
    std::cout << "Advent of Code 2021 | Day 10 | Part 2 | Answer: " << answer2 << std::endl;
    return 0;
}
