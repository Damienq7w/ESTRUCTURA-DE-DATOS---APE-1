#ifndef AUTOMOVIL_H
#define AUTOMOVIL_H

#include "Vehiculo.h"

class Automovil : public Vehiculo {
private:
    int numeroPuertas;
    bool electrico;

public:
    Automovil(const std::string& placa, const std::string& marca, const std::string& modelo,
               int anio, double precio, bool disponible, int numeroPuertas, bool electrico);

    void mostrarInformacion() const override;

    int getNumeroPuertas() const;
    void setNumeroPuertas(int numeroPuertas);
    bool isElectrico() const;
    void setElectrico(bool electrico);
};

#endif // AUTOMOVIL_H
