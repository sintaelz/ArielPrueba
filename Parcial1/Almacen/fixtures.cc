#include "fixtures.h"

void Almacen::pushBack(int quantity){
    productList.push_back(quantity);
}

void Almacen::pushFront(int quantity){
    productList.insert(productList.begin(), quantity);
}

bool Almacen::isEmpty(){
    if (productList.size() != 0){ return 1; }
    return 0;
}


void Almacen::deleteAt(int index){
    productList.erase(productList.begin()+index);
}

void Almacen::print(){
    std::vector<int>::iterator index;
    for(index = productList.begin(); index != productList.end(); ++index){
        std::cout << *index << std::endl;

    }
}
