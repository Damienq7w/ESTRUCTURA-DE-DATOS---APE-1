#ifndef IVehiculoGestor_h
#define IVehiculoGestor_h

#include <memory>
#include <string>
#include "Vehiculo.h"

// Esto es como una "lista de tareas obligatorias" para GestorVehiculos.
// C++ no tiene "interface" como Java, entonces hago una clase donde
// todos los metodos terminan en "= 0", y quien herede de esta clase
// SI tiene que escribir el codigo de cada uno.
class IVehiculoGestor {
public:
    virtual ~IVehiculoGestor() = default;

    // Recibo un unique_ptr: Es la forma moderna de C++
    // de pasar objetos sin preocuparme de
    // hacer delete manual ni de que se pierda memoria.
    virtual bool registrar(std::unique_ptr<Vehiculo> nuevoVehiculo) = 0;

    // Cambia el precio y la disponibilidad de un vehiculo que ya existe.
    virtual bool modificar(int indice, double nuevoPrecio, bool nuevaDisponibilidad) = 0;

    // Borra el vehiculo de esa posicion.
    virtual bool eliminar(int indice) = 0;

    // Busca por placa. Si lo encuentra devuelve la posicion, si no -1.
    virtual int buscarPorPlaca(const std::string& placa) const = 0;

    // Imprime todos los vehiculos registrados.
    virtual void mostrarTodos() const = 0;

    // Dice si ya no hay espacio (limite de 10).
    virtual bool estaLleno() const = 0;

    // Cuantos vehiculos hay ahora mismo.
    virtual int getCantidad() const = 0;
};

#endif // IVehiculoGestor_h