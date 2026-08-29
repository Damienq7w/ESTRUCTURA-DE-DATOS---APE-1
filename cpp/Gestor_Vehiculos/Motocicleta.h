#ifndef MOTOCICLETA_H
#define MOTOCICLETA_H

#include "Vehiculo.h"

class Motocicleta : public Vehiculo {
private:
    int cilindrada;
    bool tieneMaletero;

public:
    Motocicleta(const std::string& placa, const std::string& marca, const std::string& modelo,
                 int anio, double precio, bool disponible, int cilindrada, bool tieneMaletero);

    void mostrarInformacion() const override;

    int getCilindrada() const;
    void setCilindrada(int cilindrada);
    bool isTieneMaletero() const;
    void setTieneMaletero(bool tieneMaletero);
};

#endif // MOTOCICLETA_H