






#include "circularlList.h"
#include <iostream>

int main() {
    CircularList<int> myList(1);
    myList.NewNode(2);
    myList.NewNode(3);
    myList.NewNode(4);

    myList.TraverseStart();
    bool fullTraverse = false;
    while (!(fullTraverse)) {
        if (myList.GetCurr() == myList.GetHead()) {
            std::cout << " ___  \n"
                      << "/   \ \n"
                      << "|   | \n"
                      << "|   " << myList.GetPlayer() << "\n";
        }
        else if (myList.GetCurr() == myList.GetLast()) {

            std::cout << "|   | \n"
                      << "|   | \n"
                      << "|   " << myList.GetPlayer() << "\n"
                      << "\___/ \n\n";
        }

        else {
           std::cout  << "|   | \n"
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
