#ifndef GESTORVEHICULOS_H
#define GESTORVEHICULOS_H

#include <memory>
#include <string>
#include "IVehiculoGestor.h"
#include "Vehiculo.h"

class GestorVehiculos : public IVehiculoGestor {
private:
    static const int CAPACIDAD = 10;
    std::unique_ptr<Vehiculo> vehiculos[CAPACIDAD];
    int cantidad;

public:
    GestorVehiculos();

    bool registrar(std::unique_ptr<Vehiculo> nuevoVehiculo) override;
    int buscarPorPlaca(const std::string& placa) const override;
    bool modificar(int indice, double nuevoPrecio, bool nuevaDisponibilidad) override;
    bool eliminar(int indice) override;
    void mostrarTodos() const override;
    bool estaLleno() const override;
    int getCantidad() const override;

    // Devuelve un puntero no propietario (equivalente a "get" de Java); puede ser nullptr.
    Vehiculo* obtenerVehiculo(int indice) const;
};

#endif // GESTORVEHICULOS_H