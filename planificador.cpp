#include <iostream>
#include <string>

#include "lista_circular_d.h"
#include "proceso.h"

using namespace std;



// Muestra el estado actual de la lista de procesos
void muestraEstadoActual(ListaCircularD<Proceso> *l) {
    cout << "\nEstado actual del sistema:" << endl;
    if(l->esVacia())
        cout << "\tNo hay procesos en el sistema." << endl;
    else
        cout << *l << endl;
}



// Agrega un nuevo proceso a la lista
void agregarProceso(ListaCircularD<Proceso> *lista, int tiempo, int idP, int t_inicio, int t_total) {
    Proceso* proc = new Proceso(idP, t_inicio, t_total);
    lista->insertar(proc);
    cout << "\nTiempo = " << tiempo << ": Entra " << *proc << endl;
}



// Elimina un proceso de la lista
void terminarProceso(ListaCircularD<Proceso> *lista, int tiempo, int t_ciclo) {
    Proceso* proc = lista->eliminar();
    proc->actualizarTRestante(t_ciclo);
    cout << "\nTiempo = " << tiempo << ": Termina "<< *proc << endl;
    delete proc;
}



// Actualiza el tiempo de ejecución del proceso actual y avanza al siguiente
void reemplazarProceso(ListaCircularD<Proceso> *lista, int tiempo, int t_ciclo) {
    Proceso* proc = lista->elementoActual();
    lista->elementoActual()->actualizarTRestante(t_ciclo);
    cout << "\nTiempo = " << tiempo << ": Se reemplaza " << *proc << endl;
    lista->avanzar();
}


// Reinicia la ejecución del proceso actual
void reiniciarProceso(ListaCircularD<Proceso> *lista, int tiempo) {
    Proceso* proc = lista->elementoActual();
    cout << "\nTiempo = " << tiempo << ": Reinicia " << *proc << endl;
}


int main() {
    // Tiempo máximo de ejecución de la CPU
    int TIEMPO_MAX = 1000;
    
    // Duración de un ciclo de la CPU
    int TIEMPO_CICLO = 20;
    
    // Número procesos que se consideran en la simulación
    int NUM_PROC = 8;
    
    // Tiempo de inicio de cada proceso
    int t_inicio[] = {60, 110, 120, 150, 160, 600, 700, 710};
    
    // Tiempo de CPU que requiera cada proceso
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
