#include <iostream>
#include "Pirate.h"
#include <cstring>

using std::cout, std::endl;


int main() {

    Pirate luffy("Luffy", GUM_GUM_FRUIT);
    Pirate zoro("Zoro");

    const int crewSize = 2;

    Pirate strawHatCrew[2];
    strawHatCrew[0] = luffy;
    strawHatCrew[1] = zoro;

    strawHatCrew[0].setBounty(1000000);
    strawHatCrew[1].setBounty(500000);
    cout << "Straw Hat crew contains:" << endl;
    for (int i = 0; i < crewSize; i++) {
        cout << strawHatCrew[i] << endl;
    }

    return 0;
}
