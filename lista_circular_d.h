#include <sstream>
#include <string>

#include "nodo_d.h"

template <typename T>
class ListaCircularD {
public:
    ListaCircularD();
    ~ListaCircularD();
    
    // Inserta a x a continuación del cursor
    void insertar(T* x);
    
    // Elimina el elemento a continuación del cursor
    T* eliminar();
    
    // Devuelve el elemento del cursor
    T* elementoActual() const;
    
    // Avanza el cursor
    void avanzar();
    
    // Devuelve true si la lista está vacía, false en caso contrario
    bool esVacia() const;
    
private:
    NodoD<T>* cursor;
    template <typename U>
    friend std::ostream& operator<<(std::ostream &, const ListaCircularD<U> &);
};


ListaCircularD<T>::ListaCircularD() {
    // implementar
}


ListaCircularD<T>::~ListaCircularD() {
    // implementar
}


void ListaCircularD<T>::insertar(T* x) {
    // implementar
}


T* ListaCircularD<T>::eliminar() {
    // implementar
    return NULL;
}


T* ListaCircularD<T>::elementoActual() const {
    // implementar
    return NULL;
}


void ListaCircularD<T>::avanzar() {
    // implementar
}


bool ListaCircularD<T>::esVacia() const {
    // implementar
    return NULL;
}


template <typename T>
std::ostream& operator<<(std::ostream &strm, const ListaCircularD<T> &lista) {
    NodoD<T> *aux = lista.cursor;
    std::string elems = "";
    if (!lista.esVacia()) {
        do {
            std::stringstream ss;
            ss << *(aux->elem);
            elems += ss.str() + "\n";
            aux = aux->siguiente;
        } while (aux != lista.cursor);
        elems.pop_back();
    }

    return strm << elems;
}
