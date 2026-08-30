#ifndef ESTUDIANTE_H
#define ESTUDIANTE_H

#include <string>

/**
 * Representa a un estudiante matriculado en el curso.
 * Las calificaciones se almacenan en un vector de tamano fijo (max. 7 notas),
 * junto con un contador que indica cuantas de esas posiciones estan en uso.
 */
class Estudiante {
public:
    static const int MAX_NOTAS = 7;

    Estudiante(const std::string& cedula, const std::string& nombres, const std::string& apellidos,
               int diaNacimiento, int mesNacimiento, int anioNacimiento);

    // --- Getters y setters ---

    std::string getCedula() const;

    std::string getNombres() const;
    void setNombres(const std::string& nombres);

    std::string getApellidos() const;
    void setApellidos(const std::string& apellidos);

    void getFechaNacimiento(int& dia, int& mes, int& anio) const;
    void setFechaNacimiento(int dia, int mes, int anio);

    int getNumNotas() const;

    /** Devuelve una copia de las notas actualmente registradas (tamano = numNotas). */
    void getNotas(double copia[], int& tamano) const;

    int getEdad() const;

    // --- Logica de calificaciones ---

    bool tieneCupoParaNota() const;

    /** Agrega una nueva calificacion. Devuelve false si ya se alcanzo el maximo. */
    bool agregarNota(double nota);

    /** Modifica la calificacion en la posicion indicada (0-based). */
    bool modificarNota(int indice, double nuevaNota);

    /** Elimina la calificacion en la posicion indicada (0-based) y recorre el vector. */
    bool eliminarNota(int indice);

    double getPromedio() const;

    std::string toString() const;

private:
    std::string cedula;
    std::string nombres;
    std::string apellidos;
    int diaNacimiento;
    int mesNacimiento;
    int anioNacimiento;
    double notas[MAX_NOTAS];
    int numNotas;
};

#endif