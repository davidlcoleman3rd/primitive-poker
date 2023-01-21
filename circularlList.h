//***********************************************
//      CIRCULAR LIST CLASS (Header/Implement.  *
//                                              *
//***********************************************
//                                              *
//  This C++ class defines templated objects    *
//  that serve as a circular implementation of  *
//  a linked list data structure.               *
//                                              *
//***********************************************
//                                              *
//  Version 0.1 pushed by David Coleman III on  *
//      01 - 18 - 23                            *
//                                              *
//  0.1 added Features:                         *
//  - Input function added - allows user to     *
//     use an integer as an argument for their  *
//     current test iteration                   *
//                                              *
//  - Print function added - allows user to     *
//     print the integer member variable that   *
//     stands for the current test iteration    *
//                                              *
//  - InputPrint function added - performs the  *
//     task of both Input and Print to save the *
//     client time and screen real estate       *
//                                              *
//***********************************************
//                                              *
//***********************************************
//                                              *
//  Version 0.1 pushed by David Coleman III on  *
//      01 - 18 - 23                            *
//***********************************************



#ifndef CIRCULARLIST_H
#define CIRCULARLIST_H

#include "node.h"

//************************************************

template <class Type>
class CircularList {
private:
    CircularList(Node<Type> tInput) {     //Generates a circular list with one node
        head = tInput;
        curr = head;
        next = head;
        prev = head;
    }

//******
    CircularList(Type tFirst, Type tSecond) { //Generates a circular list with two nodes
        head = tFirst;
        head->SetNext()
        SetNext(tSecond, tFirst;
    }

//******
    CircularList(Type tFirst, Type tSecond,
                 Type tThird) {
        data tInput;
        SetNext(tFirst, tSecond);
        SetNext(tSecond, tThird);
        SetNext(tThird, tFirst);
    }

//******
    void SetNext(Type tFirst)

public:
    Node<Type>* nHead;
    Node<Type>* nCurr;
    Node<Type>* nNext;
    Node<Type>* nPrev;
    int iLength;

};



#endif // CIRCULARLIST_H


