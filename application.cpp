#include <iostream>
#include "barchartanimate.h"
#include <map>
#include <string.h>
using namespace std;

/* main
 *
 * This function allows the user to select a filename to iterate through
 * and the play back speed to animate through
 *
 */


int main() {
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
    int topbars;
    cout << "Choose Your Playback Speed(1-Normal Speed): ";
    cin >> playbackspeed;
    cout << "Choose how many bars you would like to diplay in each frame:";
    cin >> topbars;

    ifstream inFile(fileName);
    string title;
    getline(inFile, title);
    string xlabel;
    getline(inFile, xlabel);
    string source;
    getline(inFile, source);
    BarChartAnimate bca(title, xlabel, source);

    while (!inFile.eof()) {  // reads each line
        bca.addFrame(inFile);
    }
    bca.setSpeed(playbackspeed);
    bca.animate(cout, topbars, -1);

    return 0;
}
