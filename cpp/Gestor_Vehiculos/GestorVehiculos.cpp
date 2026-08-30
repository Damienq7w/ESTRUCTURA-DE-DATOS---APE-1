#include "GestorVehiculos.h"
#include <iostream>

// Al crear el gestor, cantidad arranca en 0 y reiniciamos los punteros inteligentes.
GestorVehiculos::GestorVehiculos() : cantidad(0) {
    for (int i = 0; i < CAPACIDAD; ++i) {
        vehiculos[i].reset();
    }
}

// Antes de guardar un vehiculo nuevo, reviso que no venga vacio, que haya espacio,
// y que la placa no este repetida.
bool GestorVehiculos::registrar(std::unique_ptr<Vehiculo> nuevoVehiculo) {
    if (!nuevoVehiculo || estaLleno()) {
        return false;
    }

    if (buscarPorPlaca(nuevoVehiculo->getPlaca()) != -1) {
        return false;
    }

    // std::move le pasa la propiedad del vehiculo al arreglo.
    vehiculos[cantidad] = std::move(nuevoVehiculo);
    cantidad++;
    return true;
}

// Recorro todos los vehiculos guardados hasta encontrar la placa que busco.
int GestorVehiculos::buscarPorPlaca(const std::string& placa) const {
    for (int i = 0; i < cantidad; i++) {
        if (vehiculos[i] && vehiculos[i]->getPlaca() == placa) {
            return i;
        }
    }
    return -1;
}

// Valido que el indice exista, que el puntero sea valido y que el precio no sea negativo.
bool GestorVehiculos::modificar(int indice, double nuevoPrecio, bool nuevaDisponibilidad) {
    if (indice < 0 || indice >= cantidad || !vehiculos[indice] || nuevoPrecio < 0.0) {
        return false;
    }

    vehiculos[indice]->setPrecio(nuevoPrecio);
    vehiculos[indice]->setDisponible(nuevaDisponibilidad);
    return true;
}

// Borro el vehiculo de esa posicion y corro los que estaban despues un lugar hacia atras.
bool GestorVehiculos::eliminar(int indice) {
    if (indice < 0 || indice >= cantidad || !vehiculos[indice]) {
        return false;
    }

    for (int i = indice; i < cantidad - 1; i++) {
        vehiculos[i] = std::move(vehiculos[i + 1]);
    }

    vehiculos[cantidad - 1].reset();
    cantidad--;
    return true;
}

// Muestro la lista de vehiculos registrados.
void GestorVehiculos::mostrarTodos() const {
    if (cantidad == 0) {
        std::cout << "No hay vehiculos registrados en el sistema." << std::endl;
        return;
    }

    std::cout << "\n===== LISTADO DE VEHICULOS =====" << std::endl;
    for (int i = 0; i < cantidad; i++) {
        if (vehiculos[i]) {
            std::cout << "\n[Registro " << (i + 1) << "]" << std::endl;
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

// Devuelvo el vehiculo de esa posicion sin darle la propiedad (solo para consulta).
Vehiculo* GestorVehiculos::obtenerVehiculo(int indice) const {
    if (indice < 0 || indice >= cantidad) {
        return nullptr;
    }
    return vehiculos[indice].get();
}
