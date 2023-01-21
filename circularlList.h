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
//  Version 0.0.1 pushed by David Coleman III on*
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


