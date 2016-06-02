#include "state.h"
#include "list.h"

#include <iostream>
#include <fstream>

int main(int argc, char* argv[])
{
    LinkedList stateList;
    stateList.read("AreaCodes.txt");
    ofstream outf("StateCodes5.txt");
    for(int i = 0; i < stateList.getSize(); i++)
        outf << stateList[i];
    return 0;
}