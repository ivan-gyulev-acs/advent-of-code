#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <stdlib.h>
#include <vector>
#include <sstream>

struct Cave
{
    Cave()
    {
        ID = "";
    }
    Cave(std::string inputID)
    {
        ID = inputID;
    }
    virtual ~Cave()
    {
    
    }
    void AddLink(Cave newLink)
    {
        links.push_back(newLink);
    }
    std::string Info()
    {
        std::stringstream output;
        for(int a = 0; a < links.size(); a++)
            output << (a == 0 ? std::string(ID + " -> ") : ",") << links[a].ID;
        return output.str();
    }
    std::string ID;
    std::vector<Cave> links;
};

bool hasOnlyCaps(Cave& cave)
{
    for(char letter : cave.ID)
        if(letter >= 'a' && letter <= 'z')
            return false;
    return true;
}

int findCave(std::vector<Cave>& caves, Cave& searchedCave)
{
    for(int a = 0; a < caves.size(); a++)
        if(caves[a].ID == searchedCave.ID)
            return a;
    return -1;
}

void copyArray(bool* lhs, bool* rhs, int length)
{
    for(int a = 0; a < length; a++)
        lhs[a] = rhs[a];
}

int howManyInString(std::string searchingIn, std::string searchingFor)
{
    int matches = 0;
    for(int a = 0, b = 0; a < searchingIn.length(); a++)
    {
        if(searchingIn[a] == searchingFor[b])
        {
            b++;
        }
        else if(b != 0)
        {
            a--;
            b = 0;
        }
        if(b == searchingFor.length())
        {
            matches++;
            b = 0;
        }
    }
    return matches;
}

void journeyCount(std::vector<Cave>& caves, Cave& currentCave, bool* visitState, int& journeyCounter, bool extraVisit)  
{
    if(currentCave.ID == "end")
    {
        journeyCounter++;
        return;
    }

    bool* visitStateCopy = new bool[caves.size()];
    if(!hasOnlyCaps(currentCave)) visitState[findCave(caves, currentCave)] = true;

    for(int a = 0; a < currentCave.links.size(); a++)
    {
        copyArray(visitStateCopy, visitState, caves.size());
        if(!visitState[findCave(caves, currentCave.links[a])])
            journeyCount(caves, caves[findCave(caves, currentCave.links[a])], visitStateCopy, journeyCounter, extraVisit);
        else if(extraVisit && currentCave.links[a].ID != "start")
            journeyCount(caves, caves[findCave(caves, currentCave.links[a])], visitStateCopy, journeyCounter, false);
    }

    delete[] visitStateCopy;
}

int journeyCount(std::vector<Cave>& caves, bool extraVisit)
{
    Cave startingCave("start");
    bool* visitState = new bool[caves.size()];
    int jorneyCounter = 0;
    
    for(int a = 0; a < caves.size(); a++)
        visitState[a] = false;

    journeyCount(caves, caves[findCave(caves, startingCave)], visitState, jorneyCounter, extraVisit);

    delete[] visitState;
    return jorneyCounter;
}

int main()
{
    int answer = 0;
    int answer2 = 0;

    std::vector<Cave> caves;
    Cave caveLink[2];

    std::string line;
    std::fstream file;
    file.open("input.txt", std::ios_base::in);
    while(!file.eof())
    {
        std::getline(file, line);
        caveLink[0].ID = line.substr(0, line.find('-'));
        caveLink[1].ID = line.substr(line.find('-') + 1);
        for(int a = 0; a < 2; a++)
            if(findCave(caves, caveLink[a]) == -1)
                caves.push_back(caveLink[a]);
        caves[findCave(caves, caveLink[0])].AddLink(caves[findCave(caves, caveLink[1])]);
        caves[findCave(caves, caveLink[1])].AddLink(caves[findCave(caves, caveLink[0])]);
    }
    file.close();

    answer  = journeyCount(caves, false);
    answer2 = journeyCount(caves, true);

    std::cout << "Advent of Code 2021 | Day 12 | Part 1 | Answer: " << answer << std::endl;
    std::cout << "Advent of Code 2021 | Day 12 | Part 2 | Answer: " << answer2 << std::endl;

    return 0;
}
