#ifndef VEHICULO_H
#define VEHICULO_H

#include <string>

class Vehiculo {
protected:
    std::string placa;
    std::string marca;
    std::string modelo;
    int anio;
    double precio;
    bool disponible;

public:
    Vehiculo(const std::string& placa, const std::string& marca, const std::string& modelo,
              int anio, double precio, bool disponible);

    // Destructor virtual: obligatorio en C++ cuando hay herencia y punteros base
    virtual ~Vehiculo() = default;

    // Metodo abstracto (equivalente a "public abstract void mostrarInformacion();" en Java)
    virtual void mostrarInformacion() const = 0;

    void mostrarDatosComunes() const;

    // Getters
    std::string getPlaca() const;
    std::string getMarca() const;
    std::string getModelo() const;
    int getAnio() const;
    double getPrecio() const;
    bool isDisponible() const;

    // Setters
    void setPlaca(const std::string& placa);
    void setPrecio(double precio);
    void setDisponible(bool disponible);
};

#endif // VEHICULO_H
