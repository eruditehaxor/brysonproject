#ifndef ITEM_H
#define ITEM_H
#include <iostream>
using namespace std;

class item
    {
        private:
        double value;
        string name;

        public:
        item();
        item(double setValue, string setName);
        string getName();
        double getValue();
        void setName(string newName);
        void setValue(double newValue);
        

    };

#endif