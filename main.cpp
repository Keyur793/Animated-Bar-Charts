#include <iostream>
#include "barchartanimate.h"
#include <map>
#include <string.h>
using namespace std;



int main() {

//    testBarChartConstructor();
//    testBarChartCopyConstructor();
    
    vector<string> files = {"cities", "cities-usa", "countries", "movies",
        "trademarks", "patents", "football" , "brands" , "game-of-thrones",
        "endgame" , "baby-names" , "infinity-war"};

    int filenumber;
    cout << "Animated Bar Program\n\n";
    cout << "Files: \n";

    for(int i=0;i<files.size();i++){
        cout << i+1 << ". " << files[i] << endl;
    }
    cout << "\nSelect a File Number to Animate: ";

    cin >> filenumber;
    string fileName = files[filenumber-1] + ".txt";

    int playbackspeed;
    cout << "Choose Your Playback Speed: ";
    cin >> playbackspeed;

   // testBarChartParamConstructor();

    ifstream inFile(fileName);
    string title;
    getline(inFile, title);
    string xlabel;
    getline(inFile, xlabel);
    string source;
    getline(inFile, source);
    BarChartAnimate bca(title, xlabel, source);

    while (!inFile.eof()) {
        bca.addFrame(inFile);
    }
    bca.animate(cout, 12, -1);

    return 0;
}
