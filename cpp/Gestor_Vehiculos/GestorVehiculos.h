#ifndef GestorVehiculos_h
#define GestorVehiculos_h

#include <memory>
#include <string>
#include "IVehiculoGestor.h"
#include "Vehiculo.h"

// Esta es la clase que de verdad hace el trabajo: guarda los vehiculos
// (maximo 10) y tiene las funciones para registrar, buscar, modificar,
// eliminar y listar. Como hereda de IVehiculoGestor, tengo que escribir
// el codigo de los 7 metodos que esa clase promete.
class GestorVehiculos : public IVehiculoGestor {
private:
    // El limite del sistema, igual que en la version en Java.
    static const int CAPACIDAD = 10;

    // Aqui guardo los vehiculos. Cada casilla es un unique_ptr.
    std::unique_ptr<Vehiculo> vehiculos[CAPACIDAD];

    // Cuantas casillas estan ocupadas de verdad.
    int cantidad;

public:
    // Al crear el gestor, arranca sin ningun vehiculo.
    GestorVehiculos();

    // Aqui va el codigo real de los 7 metodos de la interfaz.
    bool registrar(std::unique_ptr<Vehiculo> nuevoVehiculo) override;
    int buscarPorPlaca(const std::string& placa) const override;
    bool modificar(int indice, double nuevoPrecio, bool nuevaDisponibilidad) override;
    bool eliminar(int indice) override;
    void mostrarTodos() const override;
    bool estaLleno() const override;
    int getCantidad() const override;

    // Este metodo extra sirve para ver un vehiculo puntual. Devuelvo un
    // puntero "prestado": quien lo recibe puede leerlo, pero el dueño
    // real sigue siendo el gestor (no hay que borrarlo desde afuera).
    Vehiculo* obtenerVehiculo(int indice) const;
};

#endif // GestorVehiculos_h