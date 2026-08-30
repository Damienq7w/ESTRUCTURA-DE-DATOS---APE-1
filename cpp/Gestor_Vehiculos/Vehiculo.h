#ifndef Vehiculo_h
#define Vehiculo_h

#include <string>

// Esta es la clase "padre" de todos los vehiculos. Aqui pongo todo lo
// que un automovil y una motocicleta tienen en comun (placa, marca,
// modelo, etc).

class Vehiculo {

// protected = las clases hijas (Automovil, Motocicleta) si pueden
// usar estos datos directamente, pero nadie mas afuera.
protected:
    std::string placa;
    std::string marca;
    std::string modelo;
    int anio;
    double precio;
    bool disponible;

public:
    // Constructor: aqui guardo los datos que todo vehiculo necesita.

    Vehiculo(const std::string& placa, const std::string& marca, const std::string& modelo,
              int anio, double precio, bool disponible);

    // Destructor virtual: obligatorio en C++ cuando hay herencia y punteros base
    virtual ~Vehiculo() = default;

    // Metodo abstracto (equivalente a "public abstract void mostrarInformacion();" en Java)
    virtual void mostrarInformacion() const = 0;

    void mostrarDatosComunes() const;

    // Getters: Para leer los datos sin poder cambiarlos directamente.
    std::string getPlaca() const;
    std::string getMarca() const;
    std::string getModelo() const;
    int getAnio() const;
    double getPrecio() const;
    bool isDisponible() const;

    // Setters: Solo estos tres se pueden cambiar despues de crear el vehiculo.
    void setPlaca(const std::string& placa);
    void setPrecio(double precio);
    void setDisponible(bool disponible);
};

#endif // Vehiculo_h
