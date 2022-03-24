#include <iostream>
#include <algorithm>
#include <map>
#include "myrandom.h"
#include "bar.h"
#include <string>
#include <vector>
#include <functional>


using namespace std;


const string BOX = "\u29C8";
const string CLEARCONSOLE = "\033[2J";

const string RED("\033[1;36m");
const string PURPLE("\033[1;32m");
const string BLUE("\033[1;33m");
const string CYAN("\033[1;31m");
const string GREEN("\033[1;35m");
const string GOLD("\033[1;34m");
const string BLACK("\033[1;37m");
const string RESET("\033[0m");
const vector<string> COLORS = {RED, PURPLE, BLUE, CYAN, GREEN, GOLD, BLACK};

/* BarChart
 *
 * This class stores each frame depending on the size of the frame
 * This class includes a defult constructor, parameterized constructor,
 * copy constructor, copy operator, clear function, destructor, set and
 * get frame, addbar, dump, graph, and bracket operator.
 */

class BarChart {
 private:
    Bar* bars;
    int capacity;
    int size;
    string frame;

 public:

    /* Defult contructor
     *
     * resets each variable
     */
    BarChart() {
        bars = nullptr;
        capacity = 0;
        size = 0;
        frame = "";
    }


    /* Parameterized contructor
     *
     * dynamically allocates space for bar pointer
     * sets the capacity, size, and frame
     */
    BarChart(int n) {
        bars = new Bar[n];
        capacity = n;
        size = 0;
        frame = "";
    }


    /* Copy Constructor
     *
     * Copies over the data from parameter object into the varibales
     * in this class
     */
    BarChart(const BarChart& other) {
        this->bars = new Bar[other.capacity];
        this->capacity = other.capacity;
        this->size = other.size;
        this->frame = other.frame;

        for (int i = 0; i < other.size; ++i) {
          this->bars[i] = other.bars[i];
        }
    }


    /* Copy Operator
     *
     * Copies over the data from parameter object into the varibales
     * in this class
     */
    BarChart& operator=(const BarChart& other) {
        if (this == &other) {
            return *this;
        }
        delete[] bars;

        this->bars = new Bar[other.capacity];
        this->capacity = other.capacity;
        this->size = other.size;
        this->frame = other.frame;

        for (int i = 0; i < other.size; ++i) {
          this->bars[i] = other.bars[i];
        }

        return *this;
    }
    /* Clear
     *
     * Sets the varibles equal to original values
     */
    void clear() {
        delete[] bars;
        bars = NULL;
        capacity = 0;
        size = 0;
        frame = "";
    }


    /* Destructor
     *
     * Deallocates bars pointer and sets it to null
     */
    virtual ~BarChart() {
        if (bars != nullptr) {
            delete[] bars;
            bars = nullptr;
        }
    }


    /* setFrame
     *
     * Sets the frame varible
     */
    void setFrame(string frame) {
        this->frame = frame;
    }


    /* getFrame
     *
     * returns the frame
     */
    string getFrame() {
        return frame;
    }


    /* addBar
     *
     * This function adds a bar by creating a new temporary Bar point with
     * each each variable as a parameter and adds it to the bars array, then
     * delete the temporary pointer
     */
    bool addBar(string name, int value, string category) {
        if (size >= capacity) {
            return false;
        }
         Bar* br = new Bar(name, value, category);
         bars[size] = *br;
         size++;
         delete br;

        return true;
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
    Bar& operator[](int i) {
        if (i < 0 || i >= size) {
          throw out_of_range("BarChart: i out of bounds");
        }
        return bars[i];
    }


    /* dump
     *
     * This function displays each line of the frame by iterating
     * though the bars array
     */
    void dump(ostream &output) {
        sort(bars, bars+size, greater<Bar>());
        output  << "frame: "<< frame << endl;
        for (int i=0; i < size; i++) {
            output << bars[i].getName() << " "
                   << bars[i].getValue() << " "
                   << bars[i].getCategory() << endl;
        }
    }


    /* graph
     *
     * This funtion graphs the frame based on the top varible by sorting the array
     * then diplaying the number of boxes and the correct color based on the
     * color map.
     */
    void graph(ostream &output, map<string, string> &colorMap, int top) {
    	int lenMax;

        sort(bars, bars+size, greater<Bar>());

        double topvalue = bars[0].getValue();
        if (top > size) {
            top = size;
            // makes sure that top isn't greater than size
        }
        for (int i=0; i < top; i++) {
            lenMax = floor((bars[i].getValue()/topvalue)*60);
            string color;

            if (colorMap.count(bars[i].getCategory())) {
                color = colorMap.at(bars[i].getCategory());
            } else {
                color = BLACK;
            }

            string barstr = "";
            for (int j = 0; j < lenMax; j++) {
                barstr += BOX;
            }
            output  << color << barstr << " " <<bars[i].getName() << " "
            << bars[i].getValue() << endl;
        }
    }
};

