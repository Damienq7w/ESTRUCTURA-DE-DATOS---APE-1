#ifndef GESTORESTUDIANTES_H
#define GESTORESTUDIANTES_H

#include "Estudiante.h"
#include <string>

class GestorEstudiantes {
public:
    static const int MAX_ESTUDIANTES = 20;

    GestorEstudiantes();

    int getNumEstudiantes() const;

    bool hayCupo() const;

    /** Devuelve el estudiante en la posicion 0-based del listado, o null si el indice es invalido. */
    Estudiante* getEstudiante(int indice) const;

    /** Busca un estudiante por cedula. Devuelve su indice (0-based) en el vector, o -1 si no existe. */
    int buscar(const std::string& cedula) const;

    bool insertar(Estudiante* estudiante);

    /** Elimina el estudiante en la posicion 0-based indicada y recorre el vector. */
    bool eliminar(int indice);

    /**
     * Promedio general del curso: promedio de los promedios individuales de los
     * estudiantes que tienen al menos una nota registrada.
     * Devuelve -1 si ningun estudiante tiene notas registradas.
     */
    double promedioCurso() const;

private:
    Estudiante* estudiantes[MAX_ESTUDIANTES];
    int numEstudiantes;
};

#endif