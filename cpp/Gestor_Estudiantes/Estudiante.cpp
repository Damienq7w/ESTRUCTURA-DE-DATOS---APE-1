#include "Estudiante.h"
#include <ctime>
#include <cstring>
#include <sstream>

Estudiante::Estudiante(const std::string& cedula, const std::string& nombres, const std::string& apellidos,
                       int diaNacimiento, int mesNacimiento, int anioNacimiento) {
    this->cedula = cedula;
    this->nombres = nombres;
    this->apellidos = apellidos;
    this->diaNacimiento = diaNacimiento;
    this->mesNacimiento = mesNacimiento;
    this->anioNacimiento = anioNacimiento;
    this->numNotas = 0;
}

// --- Getters y setters ---

std::string Estudiante::getCedula() const {
    return cedula;
}

std::string Estudiante::getNombres() const {
    return nombres;
}

void Estudiante::setNombres(const std::string& nombres) {
    this->nombres = nombres;
}

std::string Estudiante::getApellidos() const {
    return apellidos;
}

void Estudiante::setApellidos(const std::string& apellidos) {
    this->apellidos = apellidos;
}

void Estudiante::getFechaNacimiento(int& dia, int& mes, int& anio) const {
    dia = diaNacimiento;
    mes = mesNacimiento;
    anio = anioNacimiento;
}

void Estudiante::setFechaNacimiento(int dia, int mes, int anio) {
    this->diaNacimiento = dia;
    this->mesNacimiento = mes;
    this->anioNacimiento = anio;
}

int Estudiante::getNumNotas() const {
    return numNotas;
}

/** Devuelve una copia de las notas actualmente registradas (tamano = numNotas). */
void Estudiante::getNotas(double copia[], int& tamano) const {
    for (int i = 0; i < numNotas; i++) {
        copia[i] = notas[i];
    }
    tamano = numNotas;
}

int Estudiante::getEdad() const {
    std::time_t t = std::time(nullptr);
    std::tm* hoy = std::localtime(&t);

    int anioActual = hoy->tm_year + 1900;
    int mesActual = hoy->tm_mon + 1;
    int diaActual = hoy->tm_mday;

    int edad = anioActual - anioNacimiento;
    if (mesActual < mesNacimiento || (mesActual == mesNacimiento && diaActual < diaNacimiento)) {
        edad--;
    }
    return edad;
}

// --- Logica de calificaciones ---

bool Estudiante::tieneCupoParaNota() const {
    return numNotas < MAX_NOTAS;
}

/** Agrega una nueva calificacion. Devuelve false si ya se alcanzo el maximo. */
bool Estudiante::agregarNota(double nota) {
    if (!tieneCupoParaNota()) {
        return false;
    }
    notas[numNotas] = nota;
    numNotas++;
    return true;
}

/** Modifica la calificacion en la posicion indicada (0-based). */
bool Estudiante::modificarNota(int indice, double nuevaNota) {
    if (indice < 0 || indice >= numNotas) {
        return false;
    }
    notas[indice] = nuevaNota;
    return true;
}

/** Elimina la calificacion en la posicion indicada (0-based) y recorre el vector. */
bool Estudiante::eliminarNota(int indice) {
    if (indice < 0 || indice >= numNotas) {
        return false;
    }
    for (int i = indice; i < numNotas - 1; i++) {
        notas[i] = notas[i + 1];
    }
    numNotas--;
    return true;
}

double Estudiante::getPromedio() const {
    if (numNotas == 0) {
        return 0.0;
    }
    double suma = 0.0;
    for (int i = 0; i < numNotas; i++) {
        suma += notas[i];
    }
    return suma / numNotas;
}

std::string Estudiante::toString() const {
    std::ostringstream oss;
    oss << "Cedula: " << cedula
        << " | Nombres: " << nombres
        << " | Apellidos: " << apellidos
        << " | Fecha nac.: " << diaNacimiento << "/" << mesNacimiento << "/" << anioNacimiento
        << " | Edad: " << getEdad();
    return oss.str();
}