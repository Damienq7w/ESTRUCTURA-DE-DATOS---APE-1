#ifndef IVEHICULOGESTOR_H
#define IVEHICULOGESTOR_H

#include <memory>
#include <string>
#include "Vehiculo.h"

// En C++ una "interfaz" se modela como una clase con solo metodos virtuales puros.
class IVehiculoGestor {
public:
    virtual ~IVehiculoGestor() = default;

    // Se recibe un unique_ptr: el gestor toma la propiedad del objeto (equivalente
    // a que el array Java pase a contener la referencia al objeto).
    virtual bool registrar(std::unique_ptr<Vehiculo> nuevoVehiculo) = 0;
    virtual bool modificar(int indice, double nuevoPrecio, bool nuevaDisponibilidad) = 0;
    virtual bool eliminar(int indice) = 0;
    virtual int buscarPorPlaca(const std::string& placa) const = 0;
    virtual void mostrarTodos() const = 0;
    virtual bool estaLleno() const = 0;
    virtual int getCantidad() const = 0;
};

#endif // IVEHICULOGESTOR_H