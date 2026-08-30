#include "GestorEstudiantes.h"

GestorEstudiantes::GestorEstudiantes() {
    for (int i = 0; i < MAX_ESTUDIANTES; i++) {
        this->estudiantes[i] = nullptr;
    }
    this->numEstudiantes = 0;
}

int GestorEstudiantes::getNumEstudiantes() const {
    return numEstudiantes;
}

bool GestorEstudiantes::hayCupo() const {
    return numEstudiantes < MAX_ESTUDIANTES;
}

/** Devuelve el estudiante en la posicion 0-based del listado, o null si el indice es invalido. */
Estudiante* GestorEstudiantes::getEstudiante(int indice) const {
    if (indice < 0 || indice >= numEstudiantes) {
        return nullptr;
    }
    return estudiantes[indice];
}

/** Busca un estudiante por cedula. Devuelve su indice (0-based) en el vector, o -1 si no existe. */
int GestorEstudiantes::buscar(const std::string& cedula) const {
    for (int i = 0; i < numEstudiantes; i++) {
        if (estudiantes[i]->getCedula() == cedula) {
            return i;
        }
    }
    return -1;
}

bool GestorEstudiantes::insertar(Estudiante* estudiante) {
    if (!hayCupo()) {
        return false;
    }
    estudiantes[numEstudiantes] = estudiante;
    numEstudiantes++;
    return true;
}

/** Elimina el estudiante en la posicion 0-based indicada y recorre el vector. */
bool GestorEstudiantes::eliminar(int indice) {
    if (indice < 0 || indice >= numEstudiantes) {
        return false;
    }
    for (int i = indice; i < numEstudiantes - 1; i++) {
        estudiantes[i] = estudiantes[i + 1];
    }
    estudiantes[numEstudiantes - 1] = nullptr;
    numEstudiantes--;
    return true;
}

/**
 * Promedio general del curso: promedio de los promedios individuales de los
 * estudiantes que tienen al menos una nota registrada.
 * Devuelve -1 si ningun estudiante tiene notas registradas.
 */
double GestorEstudiantes::promedioCurso() const {
    double sumaPromedios = 0.0;
    int estudiantesConNotas = 0;
    for (int i = 0; i < numEstudiantes; i++) {
        if (estudiantes[i]->getNumNotas() > 0) {
            sumaPromedios += estudiantes[i]->getPromedio();
            estudiantesConNotas++;
        }
    }
    if (estudiantesConNotas == 0) {
        return -1;
    }
    return sumaPromedios / estudiantesConNotas;
}