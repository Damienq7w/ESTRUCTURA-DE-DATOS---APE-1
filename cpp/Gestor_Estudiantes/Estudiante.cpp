#include <string>
#include <sstream>
#include <ctime>

/**
 * Representa a un estudiante matriculado en el curso.
 * Las calificaciones se almacenan en un vector de tamano fijo (max. 7 notas),
 * junto con un contador que indica cuantas de esas posiciones estan en uso.
 */
class Estudiante {
public:
    static const int MAX_NOTAS = 7;

    Estudiante(const std::string& cedula, const std::string& nombres, const std::string& apellidos,
               int diaNacimiento, int mesNacimiento, int anioNacimiento) {
        this->cedula = cedula;
        this->nombres = nombres;
        this->apellidos = apellidos;
        this->diaNacimiento = diaNacimiento;
        this->mesNacimiento = mesNacimiento;
        this->anioNacimiento = anioNacimiento;
        this->numNotas = 0;
    }

    // --- Getters y setters ---

    std::string getCedula() const {
        return cedula;
    }

    std::string getNombres() const {
        return nombres;
    }

    void setNombres(const std::string& nombres) {
        this->nombres = nombres;
    }

    std::string getApellidos() const {
        return apellidos;
    }

    void setApellidos(const std::string& apellidos) {
        this->apellidos = apellidos;
    }

    void getFechaNacimiento(int& dia, int& mes, int& anio) const {
        dia = diaNacimiento;
        mes = mesNacimiento;
        anio = anioNacimiento;
    }

    void setFechaNacimiento(int dia, int mes, int anio) {
        this->diaNacimiento = dia;
        this->mesNacimiento = mes;
        this->anioNacimiento = anio;
    }

    int getNumNotas() const {
        return numNotas;
    }

    /** Devuelve una copia de las notas actualmente registradas (tamano = numNotas). */
    void getNotas(double copia[], int& tamano) const {
        for (int i = 0; i < numNotas; i++) {
            copia[i] = notas[i];
        }
        tamano = numNotas;
    }

    int getEdad() const {
        std::time_t t = std::time(nullptr);
        std::tm* hoy = std::localtime(&t);

        int anioActual = hoy->tm_year + 1900;
        int mesActual = hoy->tm_mon + 1;
        int diaActual = hoy->tm_mday;

        int edad = anioActual - anioNacimiento;
        if (mesActual < mesNacimiento || (mesActual == mesNacimiento && diaActual < diaNacimiento)) {
            edad--;
        }
        return edad;
    }

    // --- Logica de calificaciones ---

    bool tieneCupoParaNota() const {
        return numNotas < MAX_NOTAS;
    }

    /** Agrega una nueva calificacion. Devuelve false si ya se alcanzo el maximo. */
    bool agregarNota(double nota) {
        if (!tieneCupoParaNota()) {
            return false;
        }
        notas[numNotas] = nota;
        numNotas++;
        return true;
    }

    /** Modifica la calificacion en la posicion indicada (0-based). */
    bool modificarNota(int indice, double nuevaNota) {
        if (indice < 0 || indice >= numNotas) {
            return false;
        }
        notas[indice] = nuevaNota;
        return true;
    }

    /** Elimina la calificacion en la posicion indicada (0-based) y recorre el vector. */
    bool eliminarNota(int indice) {
        if (indice < 0 || indice >= numNotas) {
            return false;
        }
        for (int i = indice; i < numNotas - 1; i++) {
            notas[i] = notas[i + 1];
        }
        numNotas--;
        return true;
    }

    double getPromedio() const {
        if (numNotas == 0) {
            return 0.0;
        }
        double suma = 0.0;
        for (int i = 0; i < numNotas; i++) {
            suma += notas[i];
        }
        return suma / numNotas;
    }

    std::string toString() const {
        std::ostringstream oss;
        oss << "Cedula: " << cedula
            << " | Nombres: " << nombres
            << " | Apellidos: " << apellidos
            << " | Fecha nac.: " << diaNacimiento << "/" << mesNacimiento << "/" << anioNacimiento
            << " | Edad: " << getEdad();
        return oss.str();
    }

private:
    std::string cedula;
    std::string nombres;
    std::string apellidos;
    int diaNacimiento;
    int mesNacimiento;
    int anioNacimiento;
    double notas[MAX_NOTAS];
    int numNotas;
};