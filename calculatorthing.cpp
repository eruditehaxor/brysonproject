#include "calculatorthing.h"
#include <fstream>
#include <string>
#include <vector>
#include <ctype.h>
#include <cctype>


vector<item> items;

int split(string firstString, char delimiter, string storeInto[], int storeIntoLength)
    {
        if (firstString == "")
            {
                return 0;
            }
        if (firstString[0] == delimiter)
            {
                firstString.erase(0, 1); //Erases delimiter that could otherwise accidentally be stored into storeInto or create an unneccessary split.
            }
        string tempString;
        int storeIntoPosition = 0; //Keeps track of which element of storeInto to place tempString when a delimiter is found.
        int splits = 0;
        firstString += delimiter; //Adds a delimiter to the end of firstString to ensure the function also counts the last word of the string.
        for (int i = 0; i < firstString.length(); i++)
            {
                if (firstString[i] != delimiter) //Adds the character at i, if it isn't a delimiter, to tempString
                    {
                        tempString += firstString[i];
                    }
                else
                    {
                        if (firstString[i+1] == delimiter) //Checks to see if the next character is also a delimiter
                            {
                                firstString.erase(i+1, 1); //Erases redundant delimiters
                            }
                        storeInto[storeIntoPosition] = tempString;
                        storeIntoPosition++;
                        tempString.clear(); //Clears tempString for the next set of characters before a delimiter is found.
                        splits++; //Increases splits to keep track of how many times the function has been split.
                    }
            }
        return splits;
    }

//Used to populate the items vector from the items.txt file
void populateItems(string fileName)
    {
        string line;
        string tempArray[500];
        item newItem;
        ifstream openFile;
        openFile.open(fileName);
        if (openFile.fail())
            {
                cout << "Failed to populate items." << endl;
                return;
            }
        while (getline(openFile, line))
            {
                split(line, ',', tempArray, 500);
                if (tempArray[0] == "")
                    {
                        continue;
                    }
                newItem.setName(tempArray[0]);
                newItem.setValue(stod(tempArray[1]));
                items.push_back(newItem);
            }
        
        
    }

//Used for the third case of the switch statement in main. Edits the 'dollars' of a specified item
int editItemValue(string newName, double newValue)
    {
        for (int i = 0; i < items.size(); i++)
            {
                if (items[i].getName() == newName)
                    {
                        items[i].setValue(newValue);
                        return 1;
                    }
            }
        return 0;
    }

//Returns the item specified by itemName. 
item findItem(string itemName)
    {
        for (int i = 0; i < items.size(); i++)
            {
                if (itemName == items[i].getName())
                    {
                        return items[i];
                    }
            }
        item falseItem;
        falseItem.setName("false");
        return falseItem;
    }

//Returns the name of an item, using the name of said item. Mostly used for confirming if a an item exists or not.
string findItemName(string itemName)
    {
        for(int i = 0; i < items.size(); i++)
            {
                if (itemName == items[i].getName())
                    {
                        string itemFound = items[i].getName();
                        return itemFound;
                    }
            }
        return "";
    }

//Returns the 'dollars' of a specified item
double findItemValue(string itemName)
    {
        for(int i = 0; i < items.size(); i++)
            {
                if (itemName == items[i].getName())
                    {
                        return items[i].getValue();
                    }
            }
        return -1.0;
    }

//simple function to list all of the items current stored
void listItems()
    {
        for (int i = 0; i < items.size(); i++)
            {
                string manipName = items[i].getName();
                manipName[0] = toupper(manipName[0]);
                cout << manipName + "'s value: " + to_string(items[i].getValue()) << endl;
            }
        return;
    }

/* Function to calculate the percentage of work done compared to the 'expected' work done. This has three inputs: a vector of items (items), 
  a vector of integers (quants), and an integer (minutesWorked). All of these are supplied by the first case of the switch statement
  in int main().
    1. Declares a double totalDollars, a double percentage, and a double hoursWorked. The first two are set to 0.0 so that I can
       manipulate them, and hoursWorked is set to minutesWorked divided by 60.
    2. Creates a for loop, which goes through the items vector. It takes totalDollars and adds the amount of items (quants) and 
       multiplies it by the dollars amount for every item in the vector. Because the items and quants vectors recieve their values at 
       the same iteration in the first switch case, the items and their quantities are linked by what position they have in the vectors.
    3. Creates a double called expected and sets it equal to 100 * hoursWorked. This is the expected dollars for the total work done
       over the amount of hours.
    4. Sets percentage equal to totalDollars * houorsWorked divided by the expected dollars (expected). This gets a raw percentage
       for how much work was done compared to the expected work done. 
    5. Multiplies percentage by 100 to obtain the true percentage. It then returns the percentage as a double.
    
*/
double calculate(vector<item> items, vector<int> quants, int minutesWorked)
    {
        double totalDollars = 0.0;
        double percentage = 0.0;
        double hoursWorked = minutesWorked / 60.0;
        
        //
        for (int i = 0; i < items.size(); i++)
            {
                totalDollars = totalDollars + (quants[i] * items[i].getValue());
            }
        
        //
        double expected = 100 * hoursWorked;
        
        //
        
        percentage = (totalDollars * hoursWorked) / expected;
        
        //
        percentage = percentage * 100;
        
        //
        double totalPay;
        if (percentage < 100)
            {
                totalPay = 11.66 * hoursWorked;
            }
        totalPay = hoursWorked * ((percentage / 100) * 11.66) + 11.66;
        cout << "Total pay from today: " + to_string(totalPay) + " dollars" << endl;
        return percentage;
    }

//Takes the name of an item and the value you want to change that item's dollars to.
void editValue(string itemName, double itemValue)
    {
        for (int i = 0; i < items.size(); i++)
            {
                if (itemName == items[i].getName())
                    {
                        items[i].setValue(itemValue);
                    }
            }
    }

//Updates items.txt with any new items entered from case 2, or edited items from case 3. Essentially just overwrites the 
//previous contents of the file with the more accurate one from the items vector.
void updateMasterlist()
    {
        ofstream openFile;
        openFile.open("items.txt");
        for (int i = 0; i < items.size(); i++)
            {
                openFile << items[i].getName() + "," + to_string(items[i].getValue()) << endl;
            }
        openFile.close();
        return;
    }

bool isNum(string check)
    {
        for (int i = 0; i < check.length(); i++)
            {
                char temp = check[i];
                if (isdigit(temp) == false && temp != '.')
                    {
                        return false;
                    }
            }
        return true;
    }


int main()
    {
        populateItems("items.txt");
        int minutesWorked = 0;
        string minutesWorkedStr = "";
        int menuChoice0 = 0;
        string itemSearch = "";
        double newItemValue = 0.0;
        string newItemValueStr = "";
        string itemName = "";
        string newItemName = "";
        string itemValueString = "";
        double itemQuantity = 0;
        string itemQuantityStr = "";
        string tempNum = "";
        string tempChoice = "";
        double tempPercent = 0.0;
        item newItem;
        int quantity = 0;
        double val = 0.0;
        vector<item> calcItems;
        vector<int> calcQuants;
        while (menuChoice0 != 5)
            {
                cout << "Choose an option, Bryson:\n";
                cout << "1. Start calculating\n2. Enter new item\n3. Edit item\n4. List items\n5. Quit\n";
                getline(cin, tempChoice);
                //cin.ignore()
                menuChoice0 = stoi(tempChoice);
                bool calcFinished = false;
                switch(menuChoice0)
                    {
                        case 1: cout << "How many minutes did you work?" << endl;
                                getline(cin, minutesWorkedStr);
                                if (isNum(minutesWorkedStr) == false)
                                    {
                                        cout << "Invalid response. Please only include minutes worked." << endl;
                                        break;
                                    }
                                minutesWorked = stoi(minutesWorkedStr);
                                //cin.ignore();

                                do 
                                {
                                    cout << "Enter the item's name: " << endl;
                                    getline(cin, itemSearch);
                                    //cin.ignore();
                                    if (itemSearch == "done")
                                        {
                                            itemSearch = "";
                                            itemQuantity = 0.0;
                                            itemQuantityStr = "";
                                            calcFinished = true;
                                            break;
                                        }
                                    if (findItemName(itemSearch) == "")
                                        {
                                            cout << "Item not found, Bryson. Try again." << endl;
                                            continue;
                                        }
                                    
                                    cout << "Enter the quanitity of " + itemSearch << ": " << endl;
                                    getline(cin, itemQuantityStr);
                                    //cin.ignore();
                                    
                                    calcItems.push_back(findItem(itemSearch));
                                    calcQuants.push_back(stoi(itemQuantityStr));
                                    itemSearch = "";
                                    itemQuantity = 0.0;
                                    itemQuantityStr = "";
                                }while(!calcFinished);
                                minutesWorkedStr = "";
                                tempPercent = calculate(calcItems, calcQuants, minutesWorked);
                                cout << "Your percentage compared to expected: " << tempPercent << "%" << endl;
                                cout << "Press enter to continue..." << endl;
                                calcItems.clear();
                                calcQuants.clear();
                                cin.get();
                                break;

                        case 2: cout << "Enter name of the item you'd like to add: \n";
                                getline(cin, newItemName);
                                //cin.ignore();
                                if (findItemName(newItemName) == newItemName)
                                    {
                                        cout << "Item already exists. Please edit instead.\n";
                                        break;
                                    }
                                cout << "Enter the item's dollars: \n";
                                getline(cin, newItemValueStr);
                                //cin.ignore();
                                newItem.setName(newItemName);
                                val = stod(newItemValueStr);
                                newItem.setValue(val);
                                items.push_back(newItem);
                                newItemName = "";
                                newItemValueStr = "";
                                val = 0.0;
                                updateMasterlist();
                                break;

                        case 3: cout << "Enter the name of the item you'd like to edit:\n";
                                getline(cin, itemSearch);
                                //cin.ignore();
                                if (findItemName(itemSearch) == "")
                                    {
                                        cout << "Item does not exist. Try adding it.\n";
                                        break;
                                    }
                                cout << "Enter the new dollars of " + itemSearch + ":\n";
                                getline(cin, newItemValueStr);
                                val = stod(newItemValueStr);
                                editValue(itemSearch, val);
                                updateMasterlist();
                                break;

                        case 4: listItems();
                                break;
                        case 5: return 0;
                                break;

                        default:break;
                    }
                
            }
        return 0;
    }

//outline
//1.calc total number of items * dollars
//2.convert previous total to percentage of how many is expected
//3.calc pay by multiplying any percentage over 100 by 11.66
//4.???
//5.Profit

