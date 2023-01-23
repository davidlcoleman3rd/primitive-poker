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
//  Version 0.0.2 pushed by David Coleman III on*
//      01 - 22 - 23                            *
//***********************************************



#ifndef CIRCULARLIST_H
#define CIRCULARLIST_H

#include "node.h"

//************************************************

template <class Type>
class CircularList {
private:
    CircularList(Type tInput) {                             //Constructor - Generates a circular list with one node
        head = new Node<Type>(tInput);
        curr = head;
        next = head;
        prev = head;
        last = head;
        iLength = 1;
    }

//******
    CircularList(Type tFirst, Type tSecond) {                       //Constructor - Generates a circular list with two nodes
        head = new Node<Type>(tFirst);
        next = new Node<Type>(tSecond);
        head->SetNext(next);
        next->SetPrev(head);
        next->SetNext(head);
        head->SetPrev(next);
        curr = next;
        last = curr;
        prev = head;
        iLength = 2;
    }

//******
    CircularList(Type tFirst, Type tSecond, Type tThird) {          //Constructor - Generates a circular list with three nodes
        head = new Node<Type>(tFirst);
        curr = new Node<Type>(tSecond);
        next = new Node<Type>(tThird);
        head->SetNext(curr);
        curr->SetPrev(head);
        curr->SetNext(next);
        next->SetPrev(curr);
        next->SetNext(head);
        head->SetPrev(next);
        curr = next;
        last = curr;
        prev = head;
        iLenght = 3;
    }

//******
    void NewNode(Type tInput) {                             //Adds a new node to the list and sets it as last
        if(last->GetNext() == head) {                       //...links it to the previous last node and head
            curr = last;
            next = new Node<Type>(tInput);
            curr->SetNext(next);
            next->SetPrev(curr);
            next->SetNext(head);
            head->SetPrev(next);
            last = next;
            curr = last;
            iLength++;
        }
        else {                                              //If last is not set properly, the list is traversed and
            curr = head;                                    //...last is then set properly
            while (curr->GetNext() != head)
                curr = curr->GetNext();
            last = curr;
            next = new Node<Type>(tInput);
            curr->SetNext(next);
            next->SetPrev(curr);
            next->SetNext(head);
            head->SetPrev(next);
            last = next;
            curr = last;
            iLength++;
        }
    }
//******
    void TraverseStart() {                              //Primes for traversal - sets curr to head to begin traversing the list
        curr = head;                                    //...also sets prev to last and next to head + 1 in the list
        prev = last;
        next = curr->GetNext();
    }

//******
    void TraverseNext() {                               //Traverses the list by 1 node. Also traverses prev and next by 1
        curr = curr->GetNext();
        prev = curr->GetPrev();
        next = curr->GetNext();
    }

//******
    Type GetPlayer() {                                  //Returns the current player to the calling function;
        return curr->GetData();
    }

//******
    bool TraverseEnd() {                                //Checks to see if the last player has taken their turn
        if (curr->GetNext() == head)                        //If yes, then returns true to the calling function
            return true;
        else                                                //If no, then returns false to the calling function
            return false;
    }

public:
    Node<Type>* head;               //Head pointer - holds the list's structure
    Node<Type>* curr;               //Curr pointer - serves as the iterator for the list
    Node<Type>* next;               //Next pointer - serves as a means for curr to iterate upon the list
    Node<Type>* prev;               //Prev pointer - currently does nothing, but useful as a reverse-iterator for curr
    Node<Type>* last;               //Last pointer - holds the final value of the list. Useful for allowing the list to function as a
                                    //...linear structure while retaining the capabilities of a circular structure
    int iLength;                    //Legnth - holds the size of the list.  Currently no functionality

};



#endif // CIRCULARLIST_H


