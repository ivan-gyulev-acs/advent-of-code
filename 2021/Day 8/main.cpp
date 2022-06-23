#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

struct Digit
{
    Digit()
    {
        Initialize();
    }
    Digit(std::string signal)
    {
        Initialize(signal);
    }
    Digit(Digit& rhs)
    {
        length =rhs.length;
        for(int a = 0; a < 7; a++)
            signals[a] = rhs.signals[a];
    }
    virtual ~Digit()
    {

    }
    
    void Initialize()
    {
        length = 0;
        for(int a = 0; a < 7; a++)
            signals[a] = false;
    }
    void Initialize(std::string signal)
    {
        length = 0;
        for(int a = 0; a < 7; a++)
            signals[a] = false;
        for(char letter : signal)
        {
            signals[letter - 'a'] = true;
            length++;
        }
    }
    bool Contains(Digit rhs)
    {
        for(int a = 0; a < 7; a++)
            if(rhs[a] && !signals[a])
                return false;
        return true;
    }
    void Print()
    {
        for(int a = 0; a < 7; a++)
            if(signals[a])
                std::cout << (char)(a + 'a');
        std::cout << '(' << length << ')';
    }
    
    void operator=(std::string signal)
    {
        Initialize(signal);
    }
    void operator=(Digit& rhs)
    {
        length = rhs.length;
        for(int a = 0; a < 7; a++)
            signals[a] = rhs.signals[a];
    }
    bool operator==(Digit signal)
    {
        for(int a = 0; a < 7; a++)
            if(signals[a] ^ signal[a])
                return false;
        return true;
    }
    bool operator[](int index)
    {
        return signals[index];
    }
    void operator+=(char letter)
    {
        signals[letter - 'a'] = true;
        length++;
    }

    int length;
    bool signals[7];
};

Digit Xor(Digit digit1, Digit digit2)
{
    Digit output;
    for(int a = 0; a < 7; a++)
        output.signals[a] = digit1[a] ^ digit2[a];
    return output;
}

void decode(Digit * chaos)
{
    Digit order[10];
    for(int a = 0; a < 10; a++)
    {
        if(chaos[a].length == 2)
            order[1] = chaos[a];
        else if(chaos[a].length == 3)
            order[7] = chaos[a];
        else if(chaos[a].length == 4)
            order[4] = chaos[a];
        else if(chaos[a].length == 7)
            order[8] = chaos[a];
    }
    for(int a = 0; a < 10; a++)
    {
        if(chaos[a].length == 5)
            if(chaos[a].Contains(Xor(order[1], order[4])))
                order[5] = chaos[a];
            else if(chaos[a].Contains(Xor(order[4], order[8])))
                order[2] = chaos[a];
            else
                order[3] = chaos[a];
        if(chaos[a].length == 6)
            if(!chaos[a].Contains(Xor(order[1], order[4])))
                order[0] = chaos[a];
            else if(chaos[a].Contains(Xor(order[4], order[8])))
                order[6] = chaos[a];
            else
                order[9] = chaos[a];
    }
    for(int a = 0; a < 10; a++)
        chaos[a] = order[a];
}

int main()
{
    int answer = 0;
    int answer2 = 0;

    Digit currentDigit;
    Digit placeholder[10];
    for(int a = 0; a < 10; a++)
        placeholder[a].Initialize();

    std::string line;
    std::fstream file;
    file.open("input.txt", std::ios_base::in);
    while(!file.eof())
    {
        std::getline(file, line);
        for(int a = 0, b = 0; line[a] != '|'; a++)
        {
            placeholder[b] += line[a];
            if(line[a + 1] == ' ')
            {
                a++;
                b++;
            }
        }

        decode(placeholder);
        
        for(int a = line.find('|') + 2, b = 3; a < line.length(); a++)
        {
            currentDigit += line[a];
            if(a + 1 == line.length() || line[a + 1] == ' ')
            {
                a++;
                for(int c = 0; c < 10; c++)
                    if(currentDigit == placeholder[c])
                    {
                        if(c == 1 || c == 4 || c == 7 || c == 8)
                            answer++;
                        answer2 += c * pow(10, b--);
                        break;
                    }
                currentDigit.Initialize();
            }
        }
        for(int a = 0; a < 10; a++)
            placeholder[a].Initialize();
    }
    file.close();

    std::cout << "Advent of Code 2021 | Day 08 | Part 1 | Answer: " << answer << std::endl;
    std::cout << "Advent of Code 2021 | Day 08 | Part 2 | Answer: " << answer2 << std::endl;

    return 0;
}