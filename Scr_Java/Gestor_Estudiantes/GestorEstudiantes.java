/**
 * Administra el vector de estudiantes del curso (maximo 20).
 */
public class GestorEstudiantes {

    public static final int MAX_ESTUDIANTES = 20;

    private Estudiante[] estudiantes;
    private int numEstudiantes;

    public GestorEstudiantes() {
        this.estudiantes = new Estudiante[MAX_ESTUDIANTES];
        this.numEstudiantes = 0;
    }

    public int getNumEstudiantes() {
        return numEstudiantes;
    }

    public boolean hayCupo() {
        return numEstudiantes < MAX_ESTUDIANTES;
    }

    /** Devuelve el estudiante en la posicion 0-based del listado, o null si el indice es invalido. */
    public Estudiante getEstudiante(int indice) {
        if (indice < 0 || indice >= numEstudiantes) {
            return null;
        }
        return estudiantes[indice];
    }

    /** Busca un estudiante por cedula. Devuelve su indice (0-based) en el vector, o -1 si no existe. */
    public int buscar(String cedula) {
        for (int i = 0; i < numEstudiantes; i++) {
            if (estudiantes[i].getCedula().equals(cedula)) {
                return i;
            }
        }
        return -1;
    }

    public boolean insertar(Estudiante estudiante) {
        if (!hayCupo()) {
            return false;
        }
        estudiantes[numEstudiantes] = estudiante;
        numEstudiantes++;
        return true;
    }

    /** Elimina el estudiante en la posicion 0-based indicada y recorre el vector. */
    public boolean eliminar(int indice) {
        if (indice < 0 || indice >= numEstudiantes) {
            return false;
        }
        for (int i = indice; i < numEstudiantes - 1; i++) {
            estudiantes[i] = estudiantes[i + 1];
        }
        estudiantes[numEstudiantes - 1] = null;
        numEstudiantes--;
        return true;
    }

    /**
     * Promedio general del curso: promedio de los promedios individuales de los
     * estudiantes que tienen al menos una nota registrada.
     * Devuelve -1 si ningun estudiante tiene notas registradas.
     */
    public double promedioCurso() {
        double sumaPromedios = 0.0;
        int estudiantesConNotas = 0;
        for (int i = 0; i < numEstudiantes; i++) {
            if (estudiantes[i].getNumNotas() > 0) {
                sumaPromedios += estudiantes[i].getPromedio();
                estudiantesConNotas++;
            }
        }
        if (estudiantesConNotas == 0) {
            return -1;
        }
        return sumaPromedios / estudiantesConNotas;
    }
}