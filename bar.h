
#include <iostream>
#include <string>
#include "myrandom.h"
using namespace std;

/* Bar
 *
 * This a class that contains the data for each line in a frame. Each
 * line has three data points to keep track of. Class also contains
 * a defult contructor, a parameterized constructor and getter functions
 * for each variable.
 */


class Bar {
 private:
    string name;
    int value;
    string category;

 public:
    /*
     * Defult contructor
     *
     * resets each variable
     */
    Bar() {
        name = "";
        value = 0;
        category = "";
    }


    /* Parameterized Constructor
     *
     * Sets the varibale equal to the parameters
     */
    Bar(string name, int value, string category) {
        this->name = name;
        this->value = value;
        this->category = category;
    }


    /* Destructor*/
    virtual ~Bar() {
        
    }


    /*
     returns the name
     */
	string getName() {
        return name;
	}


    /*
    * returns the value
    */
	int getValue() {
        return value;
	}


    /*
    * returns the category
    */
	string getCategory() {
        return category;
	}


	bool operator<(const Bar &other) const {
        if (this->value < other.value) {
            return true;
        }
        return false;
	}

	bool operator<=(const Bar &other) const {
        if (this->value <= other.value) {
            return true;
        }
        return false;
	}

	bool operator>(const Bar &other) const {
        if (this->value > other.value) {
            return true;
        }
        return false;
	}

	bool operator>=(const Bar &other) const {
        if (this->value >= other.value) {
            return true;
        }
        return false;
	}
};

