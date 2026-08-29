#include "Automovil.h"
#include <iostream>

Automovil::Automovil(const std::string& placa, const std::string& marca, const std::string& modelo,
                       int anio, double precio, bool disponible, int numeroPuertas, bool electrico)
    : Vehiculo(placa, marca, modelo, anio, precio, disponible),
      numeroPuertas(numeroPuertas), electrico(electrico) {
}

void Automovil::mostrarInformacion() const {
    std::cout << "----------------------------------------" << std::endl;
    std::cout << "Tipo: Automovil" << std::endl;
    mostrarDatosComunes();
    std::cout << "Numero de Puertas: " << numeroPuertas << std::endl;
    std::cout << "Electrico: " << (electrico ? "Si" : "No") << std::endl;
    std::cout << "----------------------------------------" << std::endl;
}

int Automovil::getNumeroPuertas() const { return numeroPuertas; }
void Automovil::setNumeroPuertas(int numeroPuertas) { this->numeroPuertas = numeroPuertas; }
bool Automovil::isElectrico() const { return electrico; }
void Automovil::setElectrico(bool electrico) { this->electrico = electrico; }