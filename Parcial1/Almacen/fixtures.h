#ifndef Almacen_h
#define Almacen_h

#include <stdio.h>
#include <vector>
#include <iostream>

class Almacen{

    // Vector of pair containing Product and Quantity
    std::vector<int> productList;

public:

    Almacen();
    // Default constructor
    Almacen(int n){
        productList.reserve(n);
    };

    // Element administration
    void pushBack(int quantity);
    void pushFront(int quantity);
    void deleteAt(int);

    // Get functions
    double getSize(){ return productList.size(); }
    bool isEmpty();

    void print();

};
#endif /* Almacen_h */
