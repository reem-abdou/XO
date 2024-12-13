#include <iostream>
#include "BoardGame_Classes.h"

using namespace std;

int main() {
    playerg1<char> Plyer1("reem" , 'x');
    playerg1<char> Plyer2("reem" , '0');
    Player<char>* Plyrptr[2];
    Plyrptr[0] = &Plyer1;
    Plyrptr[1] = &Plyer2;
    Game1<char> B;
    Board<char>* PtrB = &B;
    GameManager<char> round1(PtrB, Plyrptr);
    round1.run();
    return 0;
}