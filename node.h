//***********************************************
//      NODE CLASS (Header/Implementation)      *
//                                              *
//***********************************************
//                                              *
//  This C++ class defines templated objects    *
//  that serve as an implementation of a data   *
//  structure node (specifically a circular     *
//  linked list)                                *
//                                              *
//***********************************************
//                                              *
//  Version 0.0.1 pushed by David Coleman III on*
//      01 - 18 - 23                            *
//***********************************************



#ifndef NODE_H
#define NODE_H

//************************************************

template <class Type>
class Node() {
public:
    Node(Type tInput) {             //Constructor - Sets data to parameter
        data = tInput;
        next = tInput;
        prev = tInput;
    }

//******
    void SetNext(Node<Type> nInput) {
        nInput.SetNext(next);
        next = nInput;
        nInput.SetPrev(*this);
        if (nInput.GetNext() == this) {
            SetPrev(nInput);
        }
    }

//******
    void SetPrev(Node<Type> nInput) {
        prev = nInput;
    }

//******
    Node<Type>* GetPrev() {
        return prev;
    }

//******
    Node<Type>* GetNext() {
        return next;
    }

//******
    Type GetData() {
        return data;
    }

//******
    ~Node() {   }


private:
    Type data;
    Node<Type>* next;
    Node<Type>* prev;

};




#endif // NODE_H




