#include "GestorVehiculos.h"
#include <iostream>

GestorVehiculos::GestorVehiculos() : cantidad(0) {
    for (int i = 0; i < CAPACIDAD; ++i) {
        vehiculos[i].reset();
    }
}

bool GestorVehiculos::registrar(std::unique_ptr<Vehiculo> nuevoVehiculo) {
    if (!nuevoVehiculo || cantidad >= CAPACIDAD) {
        return false;
    }

    if (buscarPorPlaca(nuevoVehiculo->getPlaca()) != -1) {
        return false;
    }

    vehiculos[cantidad] = std::move(nuevoVehiculo);
    ++cantidad;
    return true;
}

int GestorVehiculos::buscarPorPlaca(const std::string& placa) const {
    for (int i = 0; i < cantidad; ++i) {
        if (vehiculos[i] && vehiculos[i]->getPlaca() == placa) {
            return i;
        }
    }
    return -1;
}

bool GestorVehiculos::modificar(int indice, double nuevoPrecio, bool nuevaDisponibilidad) {
    if (indice < 0 || indice >= cantidad || !vehiculos[indice]) {
        return false;
    }

    vehiculos[indice]->setPrecio(nuevoPrecio);
    vehiculos[indice]->setDisponible(nuevaDisponibilidad);
    return true;
}

bool GestorVehiculos::eliminar(int indice) {
    if (indice < 0 || indice >= cantidad || !vehiculos[indice]) {
        return false;
    }

    for (int i = indice; i < cantidad - 1; ++i) {
        vehiculos[i] = std::move(vehiculos[i + 1]);
    }

    vehiculos[cantidad - 1].reset();
    --cantidad;
    return true;
}

void GestorVehiculos::mostrarTodos() const {
    if (cantidad == 0) {
        std::cout << "No hay vehiculos registrados." << std::endl;
        return;
    }

    std::cout << "\n===== LISTADO DE VEHICULOS =====" << std::endl;
    for (int i = 0; i < cantidad; ++i) {
        if (vehiculos[i]) {
            vehiculos[i]->mostrarInformacion();
        }
    }
}

bool GestorVehiculos::estaLleno() const {
    return cantidad >= CAPACIDAD;
}

int GestorVehiculos::getCantidad() const {
    return cantidad;
}

Vehiculo* GestorVehiculos::obtenerVehiculo(int indice) const {
    if (indice < 0 || indice >= cantidad) {
        return nullptr;
    }
    return vehiculos[indice].get();
}
