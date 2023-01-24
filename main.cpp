






#include "circularlList.h"
#include "test.h"
#include <iostream>

int main() {
    Test myTest;
    myTest.InputPrint(1);
    CircularList<int> myList(1);
    myTest.InputPrint(2);
    myList.NewNode(2);
    myTest.InputPrint(3);
    myList.NewNode(3);
    myTest.InputPrint(4);
    myList.NewNode(4);
    myTest.InputPrint(5);

    myList.TraverseStart();
    bool fullTraverse = false;
    while (!(fullTraverse)) {
        if (myList.GetCurr() == myList.GetHead()) {
            std::cout << " ___  \n"
                      << "/   \\ \n"
                      << "|   | \n"
                      << "|   " << myList.GetPlayer() << "\n";
        }
        else if (myList.GetCurr() == myList.GetLast()) {

            std::cout << "|   | \n"
                      << "|   | \n"
                      << "|   " << myList.GetPlayer() << "\n"
                     << "\\___/ \n\n";
        }

        else {
           std::cout  << "|   | \n"
                      << "|   | \n"
                      << "|   | \n"
                      << "|   " << myList.GetPlayer() << "\n"
                      << "|   | \n"
                      << "|   | \n";
        }
        myList.TraverseNext();
        if (myList.GetCurr() == myList.GetHead())
            fullTraverse = true;
    }

    return 0;
}
