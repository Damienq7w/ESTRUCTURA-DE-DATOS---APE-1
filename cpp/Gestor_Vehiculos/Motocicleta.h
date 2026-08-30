#ifndef Motocicleta_h
#define Motocicleta_h

#include "Vehiculo.h"

// Hereda todo lo comun de
// Vehiculo y agrega lo suyo (cilindrada, si tiene maletero).
class Motocicleta : public Vehiculo {
private:
    int cilindrada;
    bool tieneMaletero;

public:
    Motocicleta(const std::string& placa, const std::string& marca, const std::string& modelo,
                 int anio, double precio, bool disponible, int cilindrada, bool tieneMaletero);

    // Su propia forma de mostrar la info, distinta a la de Automovil.
    void mostrarInformacion() const override;

    int getCilindrada() const;
    void setCilindrada(int cilindrada);
    bool isTieneMaletero() const;
    void setTieneMaletero(bool tieneMaletero);
};

#endif // Motocicleta_h