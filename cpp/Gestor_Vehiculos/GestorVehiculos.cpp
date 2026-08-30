#include "GestorVehiculos.h"
#include <iostream>

// Al crear el gestor, cantidad arranca en 0 (todavia no hay vehiculos).
GestorVehiculos::GestorVehiculos() : cantidad(0) {
}

// Antes de guardar un vehiculo nuevo, reviso tres cosas:
// que no venga vacio, que todavia haya espacio, y que la placa no este
// repetida.
bool GestorVehiculos::registrar(std::unique_ptr<Vehiculo> nuevoVehiculo) {
    if (nuevoVehiculo == nullptr || estaLleno()) {
        return false;
    }

    if (buscarPorPlaca(nuevoVehiculo->getPlaca()) != -1) {
        return false;
    }

    // std::move le pasa la propiedad del vehiculo al arreglo. Despues de
    // esta linea, el parametro "nuevoVehiculo" queda vacio, porque ahora
    // el unico dueño es el arreglo interno del gestor.
    vehiculos[cantidad] = std::move(nuevoVehiculo);
    cantidad++;
    return true;
}

// Recorro todos los vehiculos guardados hasta encontrar la placa que
// busco. Si no aparece ninguna, devuelvo -1.
int GestorVehiculos::buscarPorPlaca(const std::string& placa) const {
    for (int i = 0; i < cantidad; i++) {
        if (vehiculos[i]->getPlaca() == placa) {
            return i;
        }
    }
    return -1;
}

// Solo dejo cambiar precio y disponibilidad, y valido que el indice
// exista y que el precio no sea negativo.
bool GestorVehiculos::modificar(int indice, double nuevoPrecio, bool nuevaDisponibilidad) {
    if (indice < 0 || indice >= cantidad || nuevoPrecio < 0.0) {
        return false;
    }
    vehiculos[indice]->setPrecio(nuevoPrecio);
    vehiculos[indice]->setDisponible(nuevaDisponibilidad);
    return true;
}

// Borro el vehiculo de esa posicion y "corro" todos los que estaban
// despues, un lugar hacia atras, para que no queden huecos.
bool GestorVehiculos::eliminar(int indice) {
    if (indice < 0 || indice >= cantidad) {
        return false;
    }

    for (int i = indice; i < cantidad - 1; i++) {
        vehiculos[i] = std::move(vehiculos[i + 1]);
    }

    vehiculos[cantidad - 1] = nullptr; // esto borra el ultimo, ya duplicado
    cantidad--;
    return true;
}

// Recorro todos los vehiculos y les pido que se muestren. Cada uno sabe mostrarse solo,
// porque cada tipo ya tiene su propia version de mostrarInformacion().
void GestorVehiculos::mostrarTodos() const {
    if (cantidad == 0) {
        std::cout << "No hay vehiculos registrados en el sistema." << std::endl;
        return;
    }

    for (int i = 0; i < cantidad; i++) {
        std::cout << "\n[Registro " << (i + 1) << "]" << std::endl;
        vehiculos[i]->mostrarInformacion();
    }
}

bool GestorVehiculos::estaLleno() const {
    return cantidad >= CAPACIDAD;
}

int GestorVehiculos::getCantidad() const {
    return cantidad;
}

// Devuelvo el vehiculo de esa posicion (o nullptr si no existe), pero
// sin darle la propiedad a quien lo pide: solo lo puede mirar.
Vehiculo* GestorVehiculos::obtenerVehiculo(int indice) const {
    if (indice >= 0 && indice < cantidad) {
        return vehiculos[indice].get();
    }
    return nullptr;
}