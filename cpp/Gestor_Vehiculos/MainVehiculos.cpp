#include <iostream>
#include <string>
#include <limits>
#include <memory>
#include "GestorVehiculos.h"
#include "Automovil.h"
#include "Motocicleta.h"

// Aqui esta el menu y las funciones que lo mueven. Todo es "static"
// porque solo se usa dentro de este archivo, no hace falta que se vea
// desde afuera.

// Prototipos: los declaro arriba para poder usarlos en main() aunque el
// codigo completo este mas abajo.
static void registrarAutomovilCiclico(IVehiculoGestor& gestor);
static void registrarMotocicletaCiclico(IVehiculoGestor& gestor);
static void modificarVehiculo(IVehiculoGestor& gestor);
static void eliminarVehiculo(IVehiculoGestor& gestor);

static std::string leerTextoNoVacio(const std::string& mensaje);
static std::string leerRespuestaSiNo(const std::string& mensaje);
static bool leerBooleanoSiNo(const std::string& mensaje);
static int leerEntero();
static int leerEnteroPositivo(const std::string& mensaje);
static double leerDoubleNoNegativo(const std::string& mensaje);

// Si el usuario escribe letras donde yo espero un numero, cin se
// "traba". Esta funcion lo desatasca para poder volver a preguntar.
static void limpiarEntradaInvalida() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int main() {
    // El gestor vive aqui mientras corre el programa. Cuando main()
    // termina, se destruye solo y libera todos los vehiculos que
    // hayan quedado guardados, sin que yo tenga que hacer nada extra.
    GestorVehiculos gestor;
    int opcion;

    // El menu se repite hasta que elijo la opcion 6 (salir).
    do {
        std::cout << "\n========================================" << std::endl;
        std::cout << "      SISTEMA DE GESTION VEHICULAR      " << std::endl;
        std::cout << "========================================" << std::endl;
        std::cout << "1. Registrar Automovil" << std::endl;
        std::cout << "2. Registrar Motocicleta" << std::endl;
        std::cout << "3. Listar todos los vehiculos" << std::endl;
        std::cout << "4. Modificar vehiculo por placa" << std::endl;
        std::cout << "5. Eliminar vehiculo por placa" << std::endl;
        std::cout << "6. Salir" << std::endl;
        std::cout << "Seleccione una opcion [1-6]: ";

        opcion = leerEntero();

        // Segun lo que elijo, llamo a la funcion que corresponde.
        switch (opcion) {
            case 1:
                registrarAutomovilCiclico(gestor);
                break;
            case 2:
                registrarMotocicletaCiclico(gestor);
                break;
            case 3:
                gestor.mostrarTodos();
                break;
            case 4:
                modificarVehiculo(gestor);
                break;
            case 5:
                eliminarVehiculo(gestor);
                break;
            case 6:
                std::cout << "Finalizando programa..." << std::endl;
                break;
            default:
                std::cout << "Opcion invalida. Intente de nuevo." << std::endl;
        }
    } while (opcion != 6);

    return 0;
}

// Deja registrar varios automoviles seguidos, sin volver al menu cada vez.
static void registrarAutomovilCiclico(IVehiculoGestor& gestor) {
    char repetir;
    do {
        // Si ya no hay espacio, aviso y me salgo de una vez.
        if (gestor.estaLleno()) {
            std::cout << "AVISO: Capacidad maxima del vector alcanzada (10 vehiculos)." << std::endl;
            return;
        }

        std::cout << "\n--- REGISTRO DE AUTOMOVIL ---" << std::endl;
        std::string placa = leerTextoNoVacio("Placa: ");

        // Reviso la placa repetida antes de pedir el resto de datos,
        // para no hacer llenar todo el formulario si va a fallar.
        if (gestor.buscarPorPlaca(placa) != -1) {
            std::cout << "ERROR: Ya existe un vehiculo con esa placa." << std::endl;
        } else {
            std::string marca = leerTextoNoVacio("Marca: ");
            std::string modelo = leerTextoNoVacio("Modelo: ");
            int anio = leerEnteroPositivo("Anio: ");
            double precio = leerDoubleNoNegativo("Precio: ");
            bool disponible = leerBooleanoSiNo("Disponible? (1: Si / 2: No): ");
            int puertas = leerEnteroPositivo("Numero de Puertas: ");
            bool electrico = leerBooleanoSiNo("Es electrico? (1: Si / 2: No): ");

            // Creo el objeto Automovil en memoria. make_unique lo crea y
            // me da un puntero que soy el unico dueño de ese objeto.
            auto auto_ = std::make_unique<Automovil>(placa, marca, modelo, anio, precio,
                                                       disponible, puertas, electrico);

            // std::move le entrega la propiedad al gestor. Tengo que
            // usar move porque un unique_ptr no se puede copiar, solo
            // "pasar de mano en mano" para que siempre tenga un solo dueño.
            if (gestor.registrar(std::move(auto_))) {
                std::cout << "Automovil registrado exitosamente." << std::endl;
            } else {
                std::cout << "No se pudo registrar el automovil." << std::endl;
            }
        }

        std::string respuesta = leerRespuestaSiNo("\nDesea registrar otro automovil? (S/N): ");
        repetir = respuesta[0];
    } while (repetir == 'S' || repetir == 's');
}

// Lo mismo que arriba pero para motocicletas, pidiendo cilindrada y maletero
// en vez de puertas y electrico.
static void registrarMotocicletaCiclico(IVehiculoGestor& gestor) {
    char repetir;
    do {
        if (gestor.estaLleno()) {
            std::cout << "AVISO: Capacidad maxima del vector alcanzada (10 vehiculos)." << std::endl;
            return;
        }

        std::cout << "\n--- REGISTRO DE MOTOCICLETA ---" << std::endl;
        std::string placa = leerTextoNoVacio("Placa: ");

        if (gestor.buscarPorPlaca(placa) != -1) {
            std::cout << "ERROR: Ya existe un vehiculo con esa placa." << std::endl;
        } else {
            std::string marca = leerTextoNoVacio("Marca: ");
            std::string modelo = leerTextoNoVacio("Modelo: ");
            int anio = leerEnteroPositivo("Ano: ");
            double precio = leerDoubleNoNegativo("Precio: ");
            bool disponible = leerBooleanoSiNo("Disponible? (1: Si / 2: No): ");
            int cilindrada = leerEnteroPositivo("Cilindrada (cc): ");
            bool maletero = leerBooleanoSiNo("Tiene maletero? (1: Si / 2: No): ");

            auto moto = std::make_unique<Motocicleta>(placa, marca, modelo, anio, precio,
                                                        disponible, cilindrada, maletero);
            if (gestor.registrar(std::move(moto))) {
                std::cout << "Motocicleta registrada exitosamente." << std::endl;
            } else {
                std::cout << "No se pudo registrar la motocicleta." << std::endl;
            }
        }

        std::string respuesta = leerRespuestaSiNo("\nDesea registrar otra motocicleta? (S/N): ");
        repetir = respuesta[0];
    } while (repetir == 'S' || repetir == 's');
}

// Busco un vehiculo por placa y, si existe, dejo cambiarle el precio y
// la disponibilidad.
static void modificarVehiculo(IVehiculoGestor& gestor) {
    std::string placa = leerTextoNoVacio("\nIngrese la placa del vehiculo a modificar: ");
    int indice = gestor.buscarPorPlaca(placa);

    if (indice == -1) {
        std::cout << "ERROR: No se encontro ningun vehiculo con la placa indicada." << std::endl;
        return;
    }

    double nuevoPrecio = leerDoubleNoNegativo("Nuevo Precio: ");
    bool nuevaDisponibilidad = leerBooleanoSiNo("Nueva Disponibilidad? (1: Si / 2: No): ");

    if (gestor.modificar(indice, nuevoPrecio, nuevaDisponibilidad)) {
        std::cout << "Vehiculo modificado correctamente." << std::endl;
    } else {
        std::cout << "Error al actualizar los datos." << std::endl;
    }
}

// Busco un vehiculo por placa y, si existe, lo elimino. 
static void eliminarVehiculo(IVehiculoGestor& gestor) {
    std::string placa = leerTextoNoVacio("\nIngrese la placa del vehiculo a eliminar: ");
    int indice = gestor.buscarPorPlaca(placa);

    if (indice == -1) {
        std::cout << "ERROR: No se encontro ningun vehiculo con la placa indicada." << std::endl;
        return;
    }

    if (gestor.eliminar(indice)) {
        std::cout << "Vehiculo eliminado exitosamente (memoria contigua compactada)." << std::endl;
    } else {
        std::cout << "Error al intentar eliminar el vehiculo." << std::endl;
    }
}

// De aqui para abajo son funciones para pedir datos por consola y
// asegurarme de que lo que escribio el usuario tenga sentido. Cada una
// repite la pregunta hasta que la respuesta sea valida.

// Pide texto y no lo acepta vacio (ni solo espacios).
static std::string leerTextoNoVacio(const std::string& mensaje) {
    std::string valor;
    do {
        std::cout << mensaje;
        std::getline(std::cin, valor);

        // Le quito espacios de mas al inicio y al final del texto.
        size_t inicio = valor.find_first_not_of(" \t\r\n");
        size_t fin = valor.find_last_not_of(" \t\r\n");
        valor = (inicio == std::string::npos) ? "" : valor.substr(inicio, fin - inicio + 1);

        if (valor.empty()) {
            std::cout << "ERROR: Este campo no puede estar vacio." << std::endl;
        }
    } while (valor.empty());
    return valor;
}

// Pide S o N (en cualquier combinacion de mayus/minus) y siempre me
// devuelve "S" o "N" ya en mayuscula, para no complicarme despues.
static std::string leerRespuestaSiNo(const std::string& mensaje) {
    std::string valor;
    while (true) {
        std::cout << mensaje;
        std::getline(std::cin, valor);
        size_t inicio = valor.find_first_not_of(" \t\r\n");
        size_t fin = valor.find_last_not_of(" \t\r\n");
        valor = (inicio == std::string::npos) ? "" : valor.substr(inicio, fin - inicio + 1);

        if (valor == "S" || valor == "s") {
            return "S";
        }
        if (valor == "N" || valor == "n") {
            return "N";
        }
        std::cout << "ERROR: Ingrese solo S o N." << std::endl;
    }
}

// Pide 1 (Si) o 2 (No) y devuelve directamente true/false. Se usa para
// cosas como "Disponible?", "Electrico?", "Tiene maletero?".
static bool leerBooleanoSiNo(const std::string& mensaje) {
    std::string valor;
    while (true) {
        std::cout << mensaje;
        std::getline(std::cin, valor);
        if (valor == "1") {
            return true;
        }
        if (valor == "2") {
            return false;
        }
        std::cout << "ERROR: Ingrese 1 para Si o 2 para No." << std::endl;
    }
}

// Pide un numero entero (lo uso solo para la opcion del menu).
static int leerEntero() {
    int valor;
    while (!(std::cin >> valor)) {
        std::cout << "Entrada invalida. Ingrese un numero entero: ";
        limpiarEntradaInvalida();
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // me quedo sin lo que sobro de la linea
    return valor;
}

// Como leerEntero(), pero encima no dejo pasar numeros menores o
// iguales a 0 (para año, puertas, cilindrada, etc).
static int leerEnteroPositivo(const std::string& mensaje) {
    int valor;
    do {
        std::cout << mensaje;
        while (!(std::cin >> valor)) {
            std::cout << "Entrada invalida. Ingrese un numero entero positivo: ";
            limpiarEntradaInvalida();
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        if (valor <= 0) {
            std::cout << "ERROR: El valor debe ser mayor que 0." << std::endl;
        }
    } while (valor <= 0);
    return valor;
}

// Pide un decimal que no puede ser negativo (lo uso para el precio).
static double leerDoubleNoNegativo(const std::string& mensaje) {
    double valor;
    do {
        std::cout << mensaje;
        while (!(std::cin >> valor)) {
            std::cout << "Entrada invalida. Ingrese un valor numerico: ";
            limpiarEntradaInvalida();
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        if (valor < 0) {
            std::cout << "ERROR: El precio no puede ser negativo." << std::endl;
        }
    } while (valor < 0);
    return valor;
}