#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <map>
#include <vector>
#include <unistd.h>
#include "myrandom.h"
#include "barchart.h"

using namespace std;

/* BarChartAnimate
 *
 * This class is used to add a frame and animate though each frame. This
 * class includes a parameterized contructor, destructor, addframe, animate
 * getsize and, [] operator
 */
class BarChartAnimate {
 private:
    BarChart* barcharts;  // pointer to a C-style array
    int size;
    int capacity;
    unsigned int count = 0;  // keeps track of color count
    map<string, string> colorMap;
    string title;
    string xlabel;
    string source;
    int speed=1;

 public:
    /* BarChartAnimate
     *
     * This is a parameterized contructor at allocates 4 spaces for barchart
     * pointer and sets the other variables up
     */
    BarChartAnimate(string title, string xlabel, string source) {
        barcharts = new BarChart[4];
        size = 0;
        capacity = 4;
        this->title = title;
        this->xlabel = xlabel;
        this->source = source;
    }


    /* Destructor
     *
     * deallocates barcharts pointer and sets it equal to null
     */
    virtual ~BarChartAnimate() {
        if (barcharts != nullptr) {
            delete[] barcharts;
            barcharts = nullptr;
        }
    }


    /* setColorMap
     *
     * This function sets up the color system. If the category is new then
     * add a new color, If it runs out of colors than loop back to the start
     * color vector.
     */
    void setColorMap(string category) {
        if (!colorMap.count(category)) {
            if (count >= COLORS.size()) {
                count = 0;
            }
            colorMap.emplace(category, COLORS[count]);
            count++;
         }
    }


    /* addFrame
     *
     * This function reads in the file line by line and seperates each frame
     * and line and adds it all to that barchart pointer. The barchart array
     * doubles in size everytime it reaches its capacity
     */
    void addFrame(ifstream &file) {
        string numgroup, name1, name2, value, frame, category;
        file.ignore(100, '\n');
        getline(file, numgroup);

        if(numgroup == "") {return;}
        BarChart* tempbar = new BarChart(stoi(numgroup));

        for (int i = 0; i < stoi(numgroup); i++) {
            getline(file, frame, ',' );
            getline(file, name1, ',');
            getline(file, name2, ',');
            getline(file, value, ',');
            getline(file, category, '\n');

            (*tempbar).addBar(name1, stoi(value), category);
            (*tempbar).setFrame(frame);
            setColorMap(category);
        }
        if (size == capacity) {
            int newcapacity = capacity * 2;
            BarChart* newbarcharts = new BarChart[newcapacity];
            for (int i = 0; i < size; i++) {
                newbarcharts[i] = barcharts[i];
            }
            delete[] barcharts;
            barcharts = newbarcharts;
            capacity = newcapacity;
        }
        barcharts[size] = *tempbar;
        delete tempbar;
        size++;
    }


    /* setSpeed
     *
     * Sets the speed for play backspeed(Used for creative component)
     */
    void setSpeed(int speed) {
        this->speed = speed;
    }


    /* animate
     *
     * This function animates the bars. It does this by graphing the frame
     * clearing the console and then delays the next frame causing it to
     * animate
     */
	void animate(ostream &output, int top, int endIter) {
		unsigned int microsecond = 50000;

        if (endIter == -1) {
            endIter = size;;
        }
        if (endIter > size) {
            endIter = size;
        }
        if (speed <= 0) {
            speed = 1;
        }

        for(int i = 0; i < endIter; i++){
            usleep((3*microsecond)/speed);

            output << CLEARCONSOLE << endl;
            output << BLACK << title << endl;
            output << BLACK <<  source << endl;

            barcharts[i].graph(output, colorMap, top);

            output << BLACK << xlabel << endl;
            output << BLACK << "Frame: " << barcharts[i].getFrame() << endl;
        }
	}


    /* getSize
     *
     * returns the size
     */
    int getSize() {
        return size;
    }


    /* [] operator
     *
     * returns the index at i
     */
    BarChart& operator[](int i) {
        if (i < 0 || i >= size){
          throw out_of_range("BarChartAnimate: i out of bounds");
        }
        return barcharts[i];
    }
};
