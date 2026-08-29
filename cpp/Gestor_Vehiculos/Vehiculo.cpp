#include "Vehiculo.h"
#include <iostream>

Vehiculo::Vehiculo(const std::string& placa, const std::string& marca, const std::string& modelo,
                     int anio, double precio, bool disponible)
    : placa(placa), marca(marca), modelo(modelo), anio(anio), precio(precio), disponible(disponible) {
}

void Vehiculo::mostrarDatosComunes() const {
    std::cout << "Placa: " << placa << std::endl;
    std::cout << "Marca: " << marca << std::endl;
    std::cout << "Modelo: " << modelo << std::endl;
    std::cout << "Ano: " << anio << std::endl;
    std::cout << "Precio: $" << precio << std::endl;
    std::cout << "Disponible: " << (disponible ? "Si" : "No") << std::endl;
}

std::string Vehiculo::getPlaca() const { return placa; }
std::string Vehiculo::getMarca() const { return marca; }
std::string Vehiculo::getModelo() const { return modelo; }
int Vehiculo::getAnio() const { return anio; }
double Vehiculo::getPrecio() const { return precio; }
bool Vehiculo::isDisponible() const { return disponible; }

void Vehiculo::setPlaca(const std::string& placa) { this->placa = placa; }
void Vehiculo::setPrecio(double precio) { this->precio = precio; }
void Vehiculo::setDisponible(bool disponible) { this->disponible = disponible; }
