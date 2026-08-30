#include "Motocicleta.h"
#include <iostream>

// Primero armo la parte comun con
// Vehiculo(...), despues guardo lo propio de la moto.
Motocicleta::Motocicleta(const std::string& placa, const std::string& marca, const std::string& modelo,
                           int anio, double precio, bool disponible, int cilindrada, bool tieneMaletero)
    : Vehiculo(placa, marca, modelo, anio, precio, disponible),
      cilindrada(cilindrada), tieneMaletero(tieneMaletero) {
}

// Version de mostrarInformacion() para motocicletas: datos comunes + los
// datos que solo tiene una motocicleta.
void Motocicleta::mostrarInformacion() const {
    std::cout << "----------------------------------------" << std::endl;
    std::cout << "Tipo: Motocicleta" << std::endl;
    mostrarDatosComunes();
    std::cout << "Cilindrada: " << cilindrada << " cc" << std::endl;
    std::cout << "Tiene Maletero: " << (tieneMaletero ? "Si" : "No") << std::endl;
    std::cout << "----------------------------------------" << std::endl;
}

int Motocicleta::getCilindrada() const { return cilindrada; }
void Motocicleta::setCilindrada(int cilindrada) { this->cilindrada = cilindrada; }
bool Motocicleta::isTieneMaletero() const { return tieneMaletero; }
void Motocicleta::setTieneMaletero(bool tieneMaletero) { this->tieneMaletero = tieneMaletero; }