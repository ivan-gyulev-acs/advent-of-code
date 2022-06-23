#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>

struct Pair
{
    Pair()
    {
        instruction = 0;
        count = 0;
    }
    char instruction;
    long long count;
};

int getIndex(std::vector<char>& characters, char character)
{
    for(int a = 0; a < characters.size(); a++)
        if(characters[a] == character)
            return a;
    return -1;
}

long long max(Pair* elementsInfo, std::vector<char>& characters, char first, char last)
{
    long long* lettersCount = new long long[characters.size()];
    for(int a = 0; a < characters.size(); a++) lettersCount[a] = 0;
    for(int a = 0; a < characters.size(); a++)
    {
        for(int b = 0; b < characters.size(); b++)
        {
            lettersCount[a] += elementsInfo[a * characters.size() + b].count;
            lettersCount[b] += elementsInfo[a * characters.size() + b].count;
        }
    }
    for(int a = 0; a < characters.size(); a++)
        lettersCount[a] = lettersCount[a] / 2 + ((a == getIndex(characters, first) || a == getIndex(characters, last)) ? 1 : 0);
        
    long long max = lettersCount[0];
    for(int a = 0; a < characters.size(); a++)
        if(lettersCount[a] > max)
            max = lettersCount[a];
    delete[] lettersCount;
    return max;
}

long long min(Pair* elementsInfo, std::vector<char>& characters, char first, char last)
{
    long long* lettersCount = new long long[characters.size()];
    for(int a = 0; a < characters.size(); a++) lettersCount[a] = 0;
    for(int a = 0; a < characters.size(); a++)
    {
        for(int b = 0; b < characters.size(); b++)
        {
            lettersCount[a] += elementsInfo[a * characters.size() + b].count;
            lettersCount[b] += elementsInfo[a * characters.size() + b].count;
        }
    }
    for(int a = 0; a < characters.size(); a++)
        lettersCount[a] = lettersCount[a] / 2 + ((a == getIndex(characters, first) || a == getIndex(characters, last)) ? 1 : 0);
        
    long long min = lettersCount[0];
    for(int a = 0; a < characters.size(); a++)
        if(lettersCount[a] < min)
            min = lettersCount[a];
    delete[] lettersCount;
    return min;
}

void addNewPair(Pair* pairs, long long* newPairs, int length)
{
    for(int a = 0; a < length; a++)
        pairs[a].count += newPairs[a];
}

int main()
{
    long long answer = 0;
    long long answer2 = 0;

    std::vector<char> characters;
    int characterCount;
    Pair* pairs;
    long long* newPairs;
    char first, last;

    std::string line;
    std::fstream file;
    file.open("input.txt", std::ios_base::in);
    for(int a = 0; a < 2; a++) std::getline(file, line);
    for(char character; !file.eof();)
    {
        bool flag = true;
        character = file.get();
        for(char letter : characters)
            if(letter == character)
                flag = false;
        if(flag && character >= 'A' && character <= 'Z') characters.push_back(character);
    }

    pairs = new Pair[(int)pow(characters.size(), 2)];
    file.clear();
    file.seekg(0, std::ios::beg);

    std::getline(file, line);
    first = line[0];
    last = line.back();
    for(int a = 0; a < line.length() - 1; a++)
        pairs[getIndex(characters, line[a]) * characters.size() + getIndex(characters, line[a + 1])].count++;
    std::getline(file, line);

    while(!file.eof())
    {
        std::getline(file, line);
        pairs[getIndex(characters, line[0]) * characters.size() + getIndex(characters, line[1])].instruction = getIndex(characters, line[6]);
    }
    file.close();
    
    characterCount = characters.size();
    newPairs = new long long[(int)pow(characterCount, 2)];
    for(int a = 0; a < 40; a++)
    {
        for(int b = 0; b < pow(characterCount, 2); b++) newPairs[b] = 0;
        for(int b = 0; b < characterCount; b++)
        {
            for(int c = 0; c < characterCount; c++) 
            {
                newPairs[b * characterCount + c] -= pairs[b * characterCount + c].count;
                newPairs[b * characterCount + pairs[b * characterCount + c].instruction] += pairs[b * characterCount + c].count;
                newPairs[pairs[b * characterCount + c].instruction * characterCount + c] += pairs[b * characterCount + c].count;
            }
        }
        addNewPair(pairs, newPairs, pow(characterCount, 2));
        if(a == 9) answer = max(pairs, characters, first, last) - min(pairs, characters, first, last);
    }
    answer2 = max(pairs, characters, first, last) - min(pairs, characters, first, last);

    std::cout << "Advent of Code 2021 | Day 14 | Part 1 | Answer: " << answer << std::endl;
    std::cout << "Advent of Code 2021 | Day 14 | Part 2 | Answer: " << answer2 << std::endl;

    delete[] newPairs;
    delete[] pairs;
    return 0;
}