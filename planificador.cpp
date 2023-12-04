#include <iostream>
#include <string>

#include "lista_circular_d.h"
#include "proceso.h"

using namespace std;



void muestraEstadoActual(ListaCircularD<Proceso> *l) {
    cout << "\nEstado actual del sistema:" << endl;
    if(l->esVacia())
        cout << "\tNo hay procesos en el sistema." << endl;
    else
        cout << *l << endl;
}



void agregarProceso(ListaCircularD<Proceso> *lista, int tiempo, int idP, int t_inicio, int t_total) {
    Proceso* proc = new Proceso(idP, t_inicio, t_total);
    lista->insertar(proc);
    cout << "\nTiempo = " << tiempo << ": Entra " << *proc << endl;
}



void terminarProceso(ListaCircularD<Proceso> *lista, int tiempo, int t_ciclo) {
    Proceso* proc = lista->eliminar();
    proc->actualizarTRestante(t_ciclo);
    cout << "\nTiempo = " << tiempo << ": Termina "<< *proc << endl;
    delete proc;
}



void reemplazarProceso(ListaCircularD<Proceso> *lista, int tiempo, int t_ciclo) {
    Proceso* proc = lista->elementoActual();
    lista->elementoActual()->actualizarTRestante(t_ciclo);
    cout << "\nTiempo = " << tiempo << ": Se reemplaza " << *proc << endl;
    lista->avanzar();
}


void reiniciarProceso(ListaCircularD<Proceso> *lista, int tiempo) {
    Proceso* proc = lista->elementoActual();
    cout << "\nTiempo = " << tiempo << ": Reinicia " << *proc << endl;
}


int main() {
    int TIEMPO_MAX = 1000;
    int TIEMPO_CICLO = 20;
    int NUM_PROC = 8;
    int t_inicio[] = {60, 110, 120, 150, 160, 600, 700, 710};
    int t_total[] = {30, 300, 50, 40, 80, 20, 100, 80};
    
    ListaCircularD<Proceso> *lista = new ListaCircularD<Proceso>();
    int tiempo = 0;
    int pid = 0;
    int t_ciclo = 0;
    while (tiempo <= TIEMPO_MAX) {
        if (t_inicio[pid] == tiempo) {
            agregarProceso(lista, tiempo, pid, t_inicio[pid], t_total[pid]);
            pid += 1;
            muestraEstadoActual(lista);
        }
        if (!lista->esVacia()) {
            if (t_ciclo == lista->elementoActual()->obtenerTRestante()) {
                terminarProceso(lista, tiempo, t_ciclo);
                if (!lista->esVacia())
                    reiniciarProceso(lista, tiempo);
                muestraEstadoActual(lista);
                t_ciclo = 0;
            }
            else if (t_ciclo == TIEMPO_CICLO) {
                reemplazarProceso(lista, tiempo, TIEMPO_CICLO);
                reiniciarProceso(lista, tiempo);
                muestraEstadoActual(lista);
                t_ciclo = 0;
            }
        }
        if (!lista->esVacia())
            t_ciclo += 1;
        tiempo += 1;
    }
    cout << "\nTiempo = " << tiempo << ": Se excedió el tiempo máximo." << endl;
    return EXIT_SUCCESS;
}
