#pragma once
#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

template<class P>
bool foundProduct(P* p);

template<class Producto>
class Almacen
{
    int size;
    Producto** array;
    int current_position;
public:

    static string name_to_find;
    Almacen()
    {
        size = 100;
        array = new Producto*[size];
        current_position = 0;
    }
    /*Almacen(const Almacen &obj)
    {
      array = new Producto**;
      **array = **obj.array;
    }*/
    ~Almacen()
    {
      delete[] array;
    }
    void add(Producto* p)
    {
        if(current_position >= size)
        {
            cout << "no hay espacio para almacenar";
            return;
        }
        array[current_position++] = p;
        return;
    }
    void eliminar(Producto* p)
    {
    }
    void print()
    {
        for(int i=0; i<current_position; i++)
        {
            array[i]->print();
        }
    }
    VideoJuego** findByName(string name)
    {
        VideoJuego** found;
        Almacen::name_to_find = name;
        found = find_if(array, array+current_position, foundProduct<Producto>);
        name_to_find = "";
        if(found[0]->getName().compare(name) == 0)
            return found;
        else
            return NULL;
    }
};

template<class P>
string Almacen<P>::name_to_find = "";

template<class P>
bool foundProduct(P* p)
{
    return (p->getName().compare(Almacen<P>::name_to_find) == 0);
}
