#include <iostream>
#include "tabtenn1.h"

int main(){
    using std::cout;
    using std::endl;
    TableTennisPlayer player1("zhang", "yi", false);
    RatePlayer rplayer1(1140, "zhang", "er", true);
    rplayer1.Name();
    if (rplayer1.HasTable())
        cout << ": has a table.\n";
    else
        cout << ": hasn't a table.\n";
    player1.Name();
    if (player1.HasTable())
        cout << ": has a table";
    else
        cout << ": hasn't a table.\n";

    cout << "Name: ";
    rplayer1.Name();
    cout << "; Rating: " << rplayer1.Rating() << endl;

    RatePlayer rplayer2(1120, player1);
    cout << "Name: ";
    rplayer2.Name();
    cout << "; Rating: " << rplayer2.Rating() << endl;

    return 0;
}