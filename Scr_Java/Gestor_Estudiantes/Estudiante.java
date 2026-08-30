
import java.time.LocalDate;
import java.time.Period;

/**
 * Representa a un estudiante matriculado en el curso.
 * Las calificaciones se almacenan en un vector de tamano fijo (max. 7 notas),
 * junto con un contador que indica cuantas de esas posiciones estan en uso.
 */
public class Estudiante {

    public static final int MAX_NOTAS = 7;

    private String cedula;
    private String nombres;
    private String apellidos;
    private LocalDate fechaNacimiento;
    private double[] notas;
    private int numNotas;

    public Estudiante(String cedula, String nombres, String apellidos, LocalDate fechaNacimiento) {
        this.cedula = cedula;
        this.nombres = nombres;
        this.apellidos = apellidos;
        this.fechaNacimiento = fechaNacimiento;
        this.notas = new double[MAX_NOTAS];
        this.numNotas = 0;
    }

    // --- Getters y setters ---

    public String getCedula() {
        return cedula;
    }

    public String getNombres() {
        return nombres;
    }

    public void setNombres(String nombres) {
        this.nombres = nombres;
    }

    public String getApellidos() {
        return apellidos;
    }

    public void setApellidos(String apellidos) {
        this.apellidos = apellidos;
    }

    public LocalDate getFechaNacimiento() {
        return fechaNacimiento;
    }

    public void setFechaNacimiento(LocalDate fechaNacimiento) {
        this.fechaNacimiento = fechaNacimiento;
    }

    public int getNumNotas() {
        return numNotas;
    }

    /** Devuelve una copia de las notas actualmente registradas (tamano = numNotas). */
    public double[] getNotas() {
        double[] copia = new double[numNotas];
        System.arraycopy(notas, 0, copia, 0, numNotas);
        return copia;
    }

    public int getEdad() {
        return Period.between(fechaNacimiento, LocalDate.now()).getYears();
    }

    // --- Logica de calificaciones ---

    public boolean tieneCupoParaNota() {
        return numNotas < MAX_NOTAS;
    }

    /** Agrega una nueva calificacion. Devuelve false si ya se alcanzo el maximo. */
    public boolean agregarNota(double nota) {
        if (!tieneCupoParaNota()) {
            return false;
        }
        notas[numNotas] = nota;
        numNotas++;
        return true;
    }

    /** Modifica la calificacion en la posicion indicada (0-based). */
    public boolean modificarNota(int indice, double nuevaNota) {
        if (indice < 0 || indice >= numNotas) {
            return false;
        }
        notas[indice] = nuevaNota;
        return true;
    }

    /** Elimina la calificacion en la posicion indicada (0-based) y recorre el vector. */
    public boolean eliminarNota(int indice) {
        if (indice < 0 || indice >= numNotas) {
            return false;
        }
        for (int i = indice; i < numNotas - 1; i++) {
            notas[i] = notas[i + 1];
        }
        numNotas--;
        return true;
    }

    public double getPromedio() {
        if (numNotas == 0) {
            return 0.0;
        }
        double suma = 0.0;
        for (int i = 0; i < numNotas; i++) {
            suma += notas[i];
        }
        return suma / numNotas;
    }

    @Override
    public String toString() {
        return String.format("Cédula: %s | Nombres: %s | Apellidos: %s | Fecha nac.: %s | Edad: %d",
                cedula, nombres, apellidos, fechaNacimiento, getEdad());
    }
}