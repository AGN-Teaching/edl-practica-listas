class Proceso {
public:
    Proceso(int idp, int t_inicio, int t_total);
    int getId();
    int getTInicio();
    int getTTotal();
    int getTEjecutado();
    int obtenerTRestante();
    void actualizarTRestante(int tEjecucion);
    
private:
    int idP;
    int tInicio;
    int tTotal;
    int tEjecutado;
    friend std::ostream& operator<<(std::ostream &, const Proceso &);
};

Proceso::Proceso(int idp, int t_inicio, int t_total)
: idP(idp), tInicio(t_inicio), tTotal(t_total) {
    tEjecutado = 0;
}

int Proceso::getId() {
    return idP;
}

int Proceso::getTInicio() {
    return tInicio;
}

int Proceso::getTTotal() {
    return tTotal;
}

int Proceso::getTEjecutado() {
    return tEjecutado;
}

int Proceso::obtenerTRestante(){
    return tTotal - tEjecutado;
}

void Proceso::actualizarTRestante(int tEjecucion) {
    tEjecutado += tEjecucion;
}


std::ostream& operator<<(std::ostream &strm, const Proceso &proc) {
    return strm << "Proceso " << std::to_string(proc.idP)
                << ": inicio = " << std::to_string(proc.tInicio)
                << "; total = " << std::to_string(proc.tTotal)
                << "; ejecutado = " << std::to_string(proc.tEjecutado);
}
