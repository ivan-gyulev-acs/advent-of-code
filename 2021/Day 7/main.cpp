#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

void swap(int& a, int& b)
{
    if(a == b) return;
    a ^= b;
    b ^= a;
    a ^= b;
}

void heapify(int* input, int length, int index = 0)
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

void heapsort(int* input, int length)
{
    int counter = length;
    while (counter > 1)
    {
        heapify(input, counter--);
        swap(input[0], input[counter]);
    }
}

int sum(int* input, int length)
{
    int sum = 0;
    for(int a = 0; a < length; a++)
        sum += input[a];
    return sum;
}

int sumUpTo(int num)
{
    if(num % 2 == 0)
        return (1 + num) * num / 2;
    else
        return num * (num / 2 + 1);
}

int main()
{
    int answer = 0;
    int answer2 = 0;

    int length = 0;

    std::string line;
    std::fstream file;
    file.open("input.txt", std::ios_base::in);
    std::getline(file, line);
    file.close();
    
    for(char ch : line)
        if(ch == ',')
            length++;
    length++;
    
    int* crabs = new int[length];
    for(int a = 0; a < length; a++)
        crabs[a] = 0;
    
    for(int a = line.length() - 1, b = length - 1, c = 0; a >= 0; a--)
    {
        crabs[b] += (line[a] - '0') * pow(10, c++);
        if(line[a - 1] == ',')
        {
            a--;
            b--;
            c = 0;
        }
    }

    heapsort(crabs, length);

    int median = crabs[length / 2];
    double average = 1.0 * sum(crabs, length) / length;
    int mean = sum(crabs, length) / length;

    for(int a = 0; a < length; a++)
        answer += abs(crabs[a] - median);

    for(int a = 0; a < length; a++)
        answer2 += sumUpTo(abs(crabs[a] - mean));

    std::cout << "Advent of Code 2021 | Day 07 | Part 1 | Answer: " << answer << std::endl;
    std::cout << "Advent of Code 2021 | Day 07 | Part 2 | Answer: " << answer2 << std::endl;

    delete[] crabs;
    return 0;
}