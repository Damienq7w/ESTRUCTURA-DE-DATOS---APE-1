#include "GestorEstudiantes.cpp"
#include <iostream>
#include <regex>
#include <cstdio>
#include <cctype>
#include <algorithm>

static GestorEstudiantes gestor;

// ==================== UTILIDADES DE LECTURA DE DATOS (declaraciones) ====================

static int leerEntero(const std::string& mensaje, int min, int max);
static double leerNota(const std::string& mensaje);
static std::string leerTextoNoVacio(const std::string& mensaje);
static std::string leerCedulaNueva(const std::string& mensaje);
static bool leerFecha(const std::string& mensaje, int& dia, int& mes, int& anio);
static bool leerSiNo(const std::string& mensaje);

// Utilidad interna para validar que una fecha exista en el calendario 
static bool esFechaValidaCalendario(int dia, int mes, int anio) {
    if (mes < 1 || mes > 12 || dia < 1) {
        return false;
    }
    int diasPorMes[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    bool esBisiesto = (anio % 4 == 0 && anio % 100 != 0) || (anio % 400 == 0);
    if (mes == 2 && esBisiesto) {
        return dia <= 29;
    }
    return dia <= diasPorMes[mes - 1];
}

static bool esFechaPosteriorAHoy(int dia, int mes, int anio) {
    std::time_t t = std::time(nullptr);
    std::tm* hoy = std::localtime(&t);
    int anioActual = hoy->tm_year + 1900;
    int mesActual = hoy->tm_mon + 1;
    int diaActual = hoy->tm_mday;

    if (anio != anioActual) return anio > anioActual;
    if (mes != mesActual) return mes > mesActual;
    return dia > diaActual;
}

// ==================== DECLARACIONES DE FUNCIONES DEL MENU ====================

static void gestionarEstudiantes();
static void listarEstudiantes();
static void insertarEstudiantes();
static void modificarEstudiante();
static void eliminarEstudiante();

static void registrarCalificaciones();
static void gestionarNotas(Estudiante* estudiante);
static void listarNotas(Estudiante* estudiante);

static void promedioDeUnEstudiante();
static void promedioDelCurso();

int main() {
    int opcion;
    do {
        std::cout << "\n=== GESTOR DE PERSONAS ===" << std::endl;
        std::cout << "1.- Estudiantes." << std::endl;
        std::cout << "2.- Registro de calificaciones." << std::endl;
        std::cout << "3.- Determinar el promedio de notas de un estudiante." << std::endl;
        std::cout << "4.- Determinar el promedio de notas del curso." << std::endl;
        std::cout << "0.- Salir." << std::endl;
        opcion = leerEntero("Ingrese su opcion (0-4): ", 0, 4);

        switch (opcion) {
            case 1: gestionarEstudiantes(); break;
            case 2: registrarCalificaciones(); break;
            case 3: promedioDeUnEstudiante(); break;
            case 4: promedioDelCurso(); break;
            case 0: std::cout << "Saliendo del programa..." << std::endl; break;
        }
    } while (opcion != 0);

    return 0;
}

// ==================== OPCION 1: ESTUDIANTES ====================

static void gestionarEstudiantes() {
    int opcion;
    do {
        std::cout << "\n=== ESTUDIANTES ===" << std::endl;
        listarEstudiantes();
        std::cout << "1.- Insertar." << std::endl;
        std::cout << "2.- Modificar." << std::endl;
        std::cout << "3.- Eliminar." << std::endl;
        std::cout << "4.- Volver al menu principal." << std::endl;
        opcion = leerEntero("Teclee su opciÃ³n (1-4): ", 1, 4);

        switch (opcion) {
            case 1: insertarEstudiantes(); break;
            case 2: modificarEstudiante(); break;
            case 3: eliminarEstudiante(); break;
            case 4: std::cout << "Volviendo al menu principal..." << std::endl; break;
        }
    } while (opcion != 4);
}

static void listarEstudiantes() {
    if (gestor.getNumEstudiantes() == 0) {
        std::cout << "No hay estudiantes registrados." << std::endl;
        return;
    }
    for (int i = 0; i < gestor.getNumEstudiantes(); i++) {
        std::cout << (i + 1) << ". " << gestor.getEstudiante(i)->toString() << std::endl;
    }
}

static void insertarEstudiantes() {
    bool continuar = true;
    while (continuar) {
        if (!gestor.hayCupo()) {
            std::cout << "Ya se registrÃ³ el cupo mÃ¡ximo de " << GestorEstudiantes::MAX_ESTUDIANTES
                       << " estudiantes. No se pueden insertar mÃ¡s." << std::endl;
            return;
        }

        std::string cedula = leerCedulaNueva("Ingrese la cÃ©dula del estudiante: ");
        std::string nombres = leerTextoNoVacio("Ingrese los nombres: ");
        std::string apellidos = leerTextoNoVacio("Ingrese los apellidos: ");
        int dia, mes, anio;
        leerFecha("Ingrese la fecha de nacimiento (dd/MM/yyyy): ", dia, mes, anio);

        gestor.insertar(new Estudiante(cedula, nombres, apellidos, dia, mes, anio));
        std::cout << "Estudiante registrado correctamente." << std::endl;

        continuar = gestor.hayCupo() && leerSiNo("Â¿Desea insertar otro estudiante? (S/N): ");
    }
}

static void modificarEstudiante() {
    if (gestor.getNumEstudiantes() == 0) {
        std::cout << "No hay estudiantes registrados para modificar." << std::endl;
        return;
    }

    bool continuar = true;
    while (continuar) {
        listarEstudiantes();
        int numero = leerEntero("Ingrese el nÃºmero del estudiante a modificar: ", 1, gestor.getNumEstudiantes());
        Estudiante* estudiante = gestor.getEstudiante(numero - 1);

        std::cout << "Datos actuales: " << estudiante->toString() << std::endl;
        estudiante->setNombres(leerTextoNoVacio("Nuevos nombres: "));
        estudiante->setApellidos(leerTextoNoVacio("Nuevos apellidos: "));
        int dia, mes, anio;
        leerFecha("Nueva fecha de nacimiento (dd/MM/yyyy): ", dia, mes, anio);
        estudiante->setFechaNacimiento(dia, mes, anio);
        std::cout << "Estudiante actualizado correctamente." << std::endl;

        continuar = gestor.getNumEstudiantes() > 0 && leerSiNo("Â¿Desea modificar otro estudiante? (S/N): ");
    }
}

static void eliminarEstudiante() {
    if (gestor.getNumEstudiantes() == 0) {
        std::cout << "No hay estudiantes registrados para eliminar." << std::endl;
        return;
    }

    bool continuar = true;
    while (continuar) {
        listarEstudiantes();
        int numero = leerEntero("Ingrese el nÃºmero del estudiante a eliminar: ", 1, gestor.getNumEstudiantes());
        gestor.eliminar(numero - 1);
        std::cout << "Estudiante eliminado correctamente." << std::endl;

        continuar = gestor.getNumEstudiantes() > 0 && leerSiNo("Â¿Desea eliminar otro estudiante? (S/N): ");
    }
}

// ==================== OPCION 2: REGISTRO DE CALIFICACIONES ====================

static void registrarCalificaciones() {
    while (true) {
        std::string cedula = leerTextoNoVacio("Ingrese la cÃ©dula del estudiante: ");
        int indice = gestor.buscar(cedula);

        if (indice == -1) {
            std::cout << "No se encontrÃ³ ningÃºn estudiante con la cÃ©dula " << cedula << "." << std::endl;
            std::cout << "1.- Ingresar otra cÃ©dula." << std::endl;
            std::cout << "2.- Volver al menÃº principal." << std::endl;
            int opcion = leerEntero("Teclee su opciÃ³n (1-2): ", 1, 2);
            if (opcion == 2) {
                return;
            }
            continue;
        }

        Estudiante* estudiante = gestor.getEstudiante(indice);
        std::cout << "Nombres: " << estudiante->getNombres()
                   << " | Apellidos: " << estudiante->getApellidos()
                   << " | Edad: " << estudiante->getEdad() << std::endl;
        gestionarNotas(estudiante);
        return;
    }
}

static void gestionarNotas(Estudiante* estudiante) {
    while (true) {
        listarNotas(estudiante);

        if (!estudiante->tieneCupoParaNota()) {
            std::cout << "Se han ingresado todas las calificaciones posibles ("
                       << Estudiante::MAX_NOTAS << "). Se da por terminado el proceso de entrada de calificaciones." << std::endl;
            return;
        }

        std::cout << "1.- Insertar calificaciÃ³n." << std::endl;
        std::cout << "2.- Modificar calificaciÃ³n." << std::endl;
        std::cout << "3.- Eliminar calificaciÃ³n." << std::endl;
        std::cout << "4.- Volver al menÃº principal." << std::endl;
        int opcion = leerEntero("Teclee su opciÃ³n (1-4): ", 1, 4);

        switch (opcion) {
            case 1: {
                double nota = leerNota("Ingrese la calificaciÃ³n: ");
                estudiante->agregarNota(nota);
                if (!estudiante->tieneCupoParaNota()) {
                    listarNotas(estudiante);
                    std::cout << "Se han ingresado todas las calificaciones posibles ("
                               << Estudiante::MAX_NOTAS << "). Se da por terminado el proceso de entrada de calificaciones." << std::endl;
                    return;
                }
                break;
            }
            case 2: {
                if (estudiante->getNumNotas() == 0) {
                    std::cout << "El estudiante no tiene calificaciones registradas para modificar." << std::endl;
                } else {
                    int numero = leerEntero("Ingrese el nÃºmero de la calificaciÃ³n a modificar: ",
                            1, estudiante->getNumNotas());
                    double nota = leerNota("Ingrese la nueva calificaciÃ³n: ");
                    estudiante->modificarNota(numero - 1, nota);
                    std::cout << "CalificaciÃ³n actualizada correctamente." << std::endl;
                }
                break;
            }
            case 3: {
                if (estudiante->getNumNotas() == 0) {
                    std::cout << "El estudiante no tiene calificaciones registradas para eliminar." << std::endl;
                } else {
                    int numero = leerEntero("Ingrese el nÃºmero de la calificaciÃ³n a eliminar: ",
                            1, estudiante->getNumNotas());
                    estudiante->eliminarNota(numero - 1);
                    std::cout << "CalificaciÃ³n eliminada correctamente." << std::endl;
                }
                break;
            }
            case 4: {
                return;
            }
        }
    }
}

static void listarNotas(Estudiante* estudiante) {
    double notas[Estudiante::MAX_NOTAS];
    int tamano;
    estudiante->getNotas(notas, tamano);
    if (tamano == 0) {
        std::cout << "No hay calificaciones registradas." << std::endl;
        return;
    }
    for (int i = 0; i < tamano; i++) {
        std::printf("%d. %.2f\n", i + 1, notas[i]);
    }
}

// ==================== OPCION 3: PROMEDIO DE UN ESTUDIANTE ====================

static void promedioDeUnEstudiante() {
    std::string cedula = leerTextoNoVacio("Ingrese la cÃ©dula del estudiante: ");
    int indice = gestor.buscar(cedula);

    if (indice == -1) {
        std::cout << "No se encontrÃ³ un estudiante con el nÃºmero de cÃ©dula indicado." << std::endl;
        return;
    }

    Estudiante* estudiante = gestor.getEstudiante(indice);
    std::cout << "Nombres: " << estudiante->getNombres() << std::endl;
    std::cout << "Apellidos: " << estudiante->getApellidos() << std::endl;
    std::cout << "Edad: " << estudiante->getEdad() << std::endl;

    if (estudiante->getNumNotas() == 0) {
        std::cout << "El estudiante no tiene calificaciones registradas." << std::endl;
    } else {
        std::printf("Promedio de calificaciones: %.2f\n", estudiante->getPromedio());
    }
}

// ==================== OPCION 4: PROMEDIO DEL CURSO ====================

static void promedioDelCurso() {
    double promedio = gestor.promedioCurso();
    if (promedio < 0) {
        std::cout << "No se han registrado calificaciones de estudiantes." << std::endl;
    } else {
        std::printf("El promedio general de calificaciones del curso es: %.2f\n", promedio);
    }
}

// ==================== UTILIDADES DE LECTURA DE DATOS ====================

static int leerEntero(const std::string& mensaje, int min, int max) {
    while (true) {
        std::cout << mensaje;
        std::string linea;
        std::getline(std::cin, linea);
        try {
            size_t pos;
            int valor = std::stoi(linea, &pos);
            if (pos != linea.size()) {
                throw std::invalid_argument("sobran caracteres");
            }
            if (valor < min || valor > max) {
                std::cout << "Valor fuera de rango. Debe estar entre " << min << " y " << max << "." << std::endl;
                continue;
            }
            return valor;
        } catch (...) {
            std::cout << "Entrada invÃ¡lida. Ingrese un nÃºmero entero." << std::endl;
        }
    }
}

static double leerNota(const std::string& mensaje) {
    while (true) {
        std::cout << mensaje;
        std::string linea;
        std::getline(std::cin, linea);
        std::replace(linea.begin(), linea.end(), ',', '.');
        try {
            size_t pos;
            double valor = std::stod(linea, &pos);
            if (pos != linea.size()) {
                throw std::invalid_argument("sobran caracteres");
            }
            if (valor < 0 || valor > 10) {
                std::cout << "La calificaciÃ³n debe estar entre 0 y 10." << std::endl;
                continue;
            }
            return valor;
        } catch (...) {
            std::cout << "Entrada invÃ¡lida. Ingrese un nÃºmero (ej. 8.5)." << std::endl;
        }
    }
}

static std::string leerTextoNoVacio(const std::string& mensaje) {
    while (true) {
        std::cout << mensaje;
        std::string valor;
        std::getline(std::cin, valor);
        // trim
        size_t inicio = valor.find_first_not_of(" \t\r\n");
        size_t fin = valor.find_last_not_of(" \t\r\n");
        valor = (inicio == std::string::npos) ? "" : valor.substr(inicio, fin - inicio + 1);
        if (valor.empty()) {
            std::cout << "El valor no puede estar vacÃ­o." << std::endl;
            continue;
        }
        return valor;
    }
}

static std::string leerCedulaNueva(const std::string& mensaje) {
    while (true) {
        std::string cedula = leerTextoNoVacio(mensaje);
        if (!std::regex_match(cedula, std::regex("\\d{10}"))) {
            std::cout << "La cÃ©dula debe contener exactamente 10 dÃ­gitos numÃ©ricos." << std::endl;
            continue;
        }
        if (gestor.buscar(cedula) != -1) {
            std::cout << "Ya existe un estudiante registrado con esa cÃ©dula." << std::endl;
            continue;
        }
        return cedula;
    }
}

static bool leerFecha(const std::string& mensaje, int& dia, int& mes, int& anio) {
    while (true) {
        std::string texto = leerTextoNoVacio(mensaje);
        int d, m, a;
        char extra;
        int leidos = std::sscanf(texto.c_str(), "%d/%d/%d%c", &d, &m, &a, &extra);
        bool formatoValido = (leidos == 3) && std::regex_match(texto, std::regex("\\d{1,2}/\\d{1,2}/\\d{4}"));

        if (!formatoValido || !esFechaValidaCalendario(d, m, a)) {
            std::cout << "Formato de fecha invÃ¡lido. Use dd/MM/yyyy (ej. 15/03/2001)." << std::endl;
            continue;
        }
        if (esFechaPosteriorAHoy(d, m, a)) {
            std::cout << "La fecha de nacimiento no puede ser posterior a hoy." << std::endl;
            continue;
        }
        dia = d;
        mes = m;
        anio = a;
        return true;
    }
}

static bool leerSiNo(const std::string& mensaje) {
    while (true) {
        std::cout << mensaje;
        std::string valor;
        std::getline(std::cin, valor);
        // trim
        size_t inicio = valor.find_first_not_of(" \t\r\n");
        size_t fin = valor.find_last_not_of(" \t\r\n");
        valor = (inicio == std::string::npos) ? "" : valor.substr(inicio, fin - inicio + 1);
        std::transform(valor.begin(), valor.end(), valor.begin(), ::toupper);
        if (valor == "S") {
            return true;
        }
        if (valor == "N") {
            return false;
        }
        std::cout << "Respuesta invÃ¡lida. Escriba S o N." << std::endl;
    }
}