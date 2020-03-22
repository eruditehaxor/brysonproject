#include "item.h"

item::item()
    {
        name = "";
        value = 0.0;
    }

item::item(double setValue, string setName)
    {
        name = setName;
        value = setValue;
    }

string item::getName()
    {
        return name;
    }

double item::getValue()
    {
        return value;
    }

void item::setName(string newName)
    {
        name = newName;
        return;
    }

void item::setValue(double newValue)
    {
        value = newValue;
        return;
    }