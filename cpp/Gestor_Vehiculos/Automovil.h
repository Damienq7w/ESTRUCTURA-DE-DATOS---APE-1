#ifndef Automovil_h
#define Automovil_h

#include "Vehiculo.h"

// Automovil hereda de Vehiculo, es decir: ya tiene
// placa, marca, modelo, etc sin que yo escriba nada, y aqui solo agrego
// lo que le falta especificamente a un auto.
class Automovil : public Vehiculo {
private:
    // Esto solo lo tiene Automovil, Motocicleta no.
    int numeroPuertas;
    bool electrico;

public:
    // Recibe los datos de siempre + los dos propios.
    Automovil(const std::string& placa, const std::string& marca, const std::string& modelo,
               int anio, double precio, bool disponible, int numeroPuertas, bool electrico);

    // "override" es para avisarle al compilador que estoy reemplazando
    // el metodo de la clase padre. Si me equivoco escribiendo el nombre,
    // el compilador me avisa en vez de crear un metodo nuevo por error.
    void mostrarInformacion() const override;

    int getNumeroPuertas() const;
    void setNumeroPuertas(int numeroPuertas);
    bool isElectrico() const;
    void setElectrico(bool electrico);
};

#endif // Automovil_h