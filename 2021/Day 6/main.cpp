#include <iostream>
#include <fstream>
#include <string>

int main()
{
    long long answer = 0;
    long long answer2 = 0;
 
    long long fish[9] = {0};
    
    std::string line;
    std::fstream file;
    file.open("input.txt", std::ios_base::in);
    std::getline(file, line);
    file.close();

    for(char ch : line)
        if(ch != ',')
            fish[ch - '0']++;
    

    long long births = 0;
    for(int a = 0, index = 0; a < 256; a++)
    {
        births = fish[index];
        fish[index] += fish[7];
        fish[7] = fish[8];
        fish[8] = births;
        index = (index + 1) % 7;
        if(a == 79)
            for(int a = 0; a < 9; a++)
                answer += fish[a];
    }
    for(int a = 0; a < 9; a++)
        answer2 += fish[a];

    std::cout << "Advent of Code 2021 | Day 06 | Part 1 | Answer: " << answer << std::endl;
    std::cout << "Advent of Code 2021 | Day 06 | Part 2 | Answer: " << answer2 << std::endl;
    return 0;
}