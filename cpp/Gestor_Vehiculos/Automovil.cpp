#include "Automovil.h"
#include <iostream>

// Primero mando los datos comunes al constructor de Vehiculo (para que
// el "padre" se termine de armar), y despues guardo lo que es solo de
// Automovil (puertas, electrico).
Automovil::Automovil(const std::string& placa, const std::string& marca, const std::string& modelo,
                       int anio, double precio, bool disponible, int numeroPuertas, bool electrico)
    : Vehiculo(placa, marca, modelo, anio, precio, disponible),
      numeroPuertas(numeroPuertas), electrico(electrico) {
}

// Esta es la version de mostrarInformacion() que le toca a Automovil.
// Uso mostrarDatosComunes() para no repetir lo que ya imprime cualquier
// vehiculo, y despues agrego lo que es solo de un auto.
void Automovil::mostrarInformacion() const {
    std::cout << "----------------------------------------" << std::endl;
    std::cout << "Tipo: Automovil" << std::endl;
    mostrarDatosComunes();
    std::cout << "Numero de Puertas: " << numeroPuertas << std::endl;
    std::cout << "Electrico: " << (electrico ? "Si" : "No") << std::endl;
    std::cout << "----------------------------------------" << std::endl;
}

// Getters y setters de los datos propios de Automovil.
int Automovil::getNumeroPuertas() const { return numeroPuertas; }
void Automovil::setNumeroPuertas(int numeroPuertas) { this->numeroPuertas = numeroPuertas; }
bool Automovil::isElectrico() const { return electrico; }
void Automovil::setElectrico(bool electrico) { this->electrico = electrico; }