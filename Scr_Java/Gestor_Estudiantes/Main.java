import java.time.LocalDate;
import java.time.format.DateTimeFormatter;
import java.time.format.DateTimeParseException;
import java.util.Locale;
import java.util.Scanner;

public class Main {

    private static final Scanner sc = new Scanner(System.in);
    private static final DateTimeFormatter FORMATO_FECHA = DateTimeFormatter.ofPattern("dd/MM/yyyy");
    private static final GestorEstudiantes gestor = new GestorEstudiantes();

    public static void main(String[] args) {
        int opcion;
        do {
            System.out.println("\n=== GESTOR DE PERSONAS ===");
            System.out.println("1.- Estudiantes.");
            System.out.println("2.- Registro de calificaciones.");
            System.out.println("3.- Determinar el promedio de notas de un estudiante.");
            System.out.println("4.- Determinar el promedio de notas del curso.");
            System.out.println("0.- Salir.");
            opcion = leerEntero("Teclee su opción (0-4): ", 0, 4);

            switch (opcion) {
                case 1 -> gestionarEstudiantes();
                case 2 -> registrarCalificaciones();
                case 3 -> promedioDeUnEstudiante();
                case 4 -> promedioDelCurso();
                case 0 -> System.out.println("Saliendo del programa...");
            }
        } while (opcion != 0);
    }

    // ==================== OPCION 1: ESTUDIANTES ====================

    private static void gestionarEstudiantes() {
        int opcion;
        do {
            System.out.println("\n=== ESTUDIANTES ===");
            listarEstudiantes();
            System.out.println("1.- Insertar.");
            System.out.println("2.- Modificar.");
            System.out.println("3.- Eliminar.");
            System.out.println("4.- Volver al menu principal.");
            opcion = leerEntero("Teclee su opción (1-4): ", 1, 4);

            switch (opcion) {
                case 1 -> insertarEstudiantes();
                case 2 -> modificarEstudiante();
                case 3 -> eliminarEstudiante();
                case 4 -> System.out.println("Volviendo al menu principal...");
            }
        } while (opcion != 4);
    }

    private static void listarEstudiantes() {
        if (gestor.getNumEstudiantes() == 0) {
            System.out.println("No hay estudiantes registrados.");
            return;
        }
        for (int i = 0; i < gestor.getNumEstudiantes(); i++) {
            System.out.println((i + 1) + ". " + gestor.getEstudiante(i));
        }
    }

    private static void insertarEstudiantes() {
        boolean continuar = true;
        while (continuar) {
            if (!gestor.hayCupo()) {
                System.out.println("Ya se registró el cupo máximo de " + GestorEstudiantes.MAX_ESTUDIANTES
                        + " estudiantes. No se pueden insertar más.");
                return;
            }

            String cedula = leerCedulaNueva("Ingrese la cédula del estudiante: ");
            String nombres = leerTextoNoVacio("Ingrese los nombres: ");
            String apellidos = leerTextoNoVacio("Ingrese los apellidos: ");
            LocalDate fechaNacimiento = leerFecha("Ingrese la fecha de nacimiento (dd/MM/yyyy): ");

            gestor.insertar(new Estudiante(cedula, nombres, apellidos, fechaNacimiento));
            System.out.println("Estudiante registrado correctamente.");

            continuar = gestor.hayCupo() && leerSiNo("¿Desea insertar otro estudiante? (S/N): ");
        }
    }

    private static void modificarEstudiante() {
        if (gestor.getNumEstudiantes() == 0) {
            System.out.println("No hay estudiantes registrados para modificar.");
            return;
        }

        boolean continuar = true;
        while (continuar) {
            listarEstudiantes();
            int numero = leerEntero("Ingrese el número del estudiante a modificar: ", 1, gestor.getNumEstudiantes());
            Estudiante estudiante = gestor.getEstudiante(numero - 1);

            System.out.println("Datos actuales: " + estudiante);
            estudiante.setNombres(leerTextoNoVacio("Nuevos nombres: "));
            estudiante.setApellidos(leerTextoNoVacio("Nuevos apellidos: "));
            estudiante.setFechaNacimiento(leerFecha("Nueva fecha de nacimiento (dd/MM/yyyy): "));
            System.out.println("Estudiante actualizado correctamente.");

            continuar = gestor.getNumEstudiantes() > 0 && leerSiNo("¿Desea modificar otro estudiante? (S/N): ");
        }
    }

    private static void eliminarEstudiante() {
        if (gestor.getNumEstudiantes() == 0) {
            System.out.println("No hay estudiantes registrados para eliminar.");
            return;
        }

        boolean continuar = true;
        while (continuar) {
            listarEstudiantes();
            int numero = leerEntero("Ingrese el número del estudiante a eliminar: ", 1, gestor.getNumEstudiantes());
            gestor.eliminar(numero - 1);
            System.out.println("Estudiante eliminado correctamente.");

            continuar = gestor.getNumEstudiantes() > 0 && leerSiNo("¿Desea eliminar otro estudiante? (S/N): ");
        }
    }

    // ==================== OPCION 2: REGISTRO DE CALIFICACIONES ====================

    private static void registrarCalificaciones() {
        while (true) {
            String cedula = leerTextoNoVacio("Ingrese la cédula del estudiante: ");
            int indice = gestor.buscar(cedula);

            if (indice == -1) {
                System.out.println("No se encontró ningún estudiante con la cédula " + cedula + ".");
                System.out.println("1.- Ingresar otra cédula.");
                System.out.println("2.- Volver al menú principal.");
                int opcion = leerEntero("Teclee su opción (1-2): ", 1, 2);
                if (opcion == 2) {
                    return;
                }
                continue;
            }

            Estudiante estudiante = gestor.getEstudiante(indice);
            System.out.println("Nombres: " + estudiante.getNombres()
                    + " | Apellidos: " + estudiante.getApellidos()
                    + " | Edad: " + estudiante.getEdad());
            gestionarNotas(estudiante);
            return;
        }
    }

    private static void gestionarNotas(Estudiante estudiante) {
        while (true) {
            listarNotas(estudiante);

            if (!estudiante.tieneCupoParaNota()) {
                System.out.println("Se han ingresado todas las calificaciones posibles ("
                        + Estudiante.MAX_NOTAS + "). Se da por terminado el proceso de entrada de calificaciones.");
                return;
            }

            System.out.println("1.- Insertar calificación.");
            System.out.println("2.- Modificar calificación.");
            System.out.println("3.- Eliminar calificación.");
            System.out.println("4.- Volver al menú principal.");
            int opcion = leerEntero("Teclee su opción (1-4): ", 1, 4);

            switch (opcion) {
                case 1 -> {
                    double nota = leerNota("Ingrese la calificación: ");
                    estudiante.agregarNota(nota);
                    if (!estudiante.tieneCupoParaNota()) {
                        listarNotas(estudiante);
                        System.out.println("Se han ingresado todas las calificaciones posibles ("
                                + Estudiante.MAX_NOTAS + "). Se da por terminado el proceso de entrada de calificaciones.");
                        return;
                    }
                }
                case 2 -> {
                    if (estudiante.getNumNotas() == 0) {
                        System.out.println("El estudiante no tiene calificaciones registradas para modificar.");
                    } else {
                        int numero = leerEntero("Ingrese el número de la calificación a modificar: ",
                                1, estudiante.getNumNotas());
                        double nota = leerNota("Ingrese la nueva calificación: ");
                        estudiante.modificarNota(numero - 1, nota);
                        System.out.println("Calificación actualizada correctamente.");
                    }
                }
                case 3 -> {
                    if (estudiante.getNumNotas() == 0) {
                        System.out.println("El estudiante no tiene calificaciones registradas para eliminar.");
                    } else {
                        int numero = leerEntero("Ingrese el número de la calificación a eliminar: ",
                                1, estudiante.getNumNotas());
                        estudiante.eliminarNota(numero - 1);
                        System.out.println("Calificación eliminada correctamente.");
                    }
                }
                case 4 -> {
                    return;
                }
            }
        }
    }

    private static void listarNotas(Estudiante estudiante) {
        double[] notas = estudiante.getNotas();
        if (notas.length == 0) {
            System.out.println("No hay calificaciones registradas.");
            return;
        }
        for (int i = 0; i < notas.length; i++) {
            System.out.printf("%d. %.2f%n", i + 1, notas[i]);
        }
    }

    // ==================== OPCION 3: PROMEDIO DE UN ESTUDIANTE ====================

    private static void promedioDeUnEstudiante() {
        String cedula = leerTextoNoVacio("Ingrese la cédula del estudiante: ");
        int indice = gestor.buscar(cedula);

        if (indice == -1) {
            System.out.println("No se encontró un estudiante con el número de cédula indicado.");
            return;
        }

        Estudiante estudiante = gestor.getEstudiante(indice);
        System.out.println("Nombres: " + estudiante.getNombres());
        System.out.println("Apellidos: " + estudiante.getApellidos());
        System.out.println("Edad: " + estudiante.getEdad());

        if (estudiante.getNumNotas() == 0) {
            System.out.println("El estudiante no tiene calificaciones registradas.");
        } else {
            System.out.printf("Promedio de calificaciones: %.2f%n", estudiante.getPromedio());
        }
    }

    // ==================== OPCION 4: PROMEDIO DEL CURSO ====================

    private static void promedioDelCurso() {
        double promedio = gestor.promedioCurso();
        if (promedio < 0) {
            System.out.println("No se han registrado calificaciones de estudiantes.");
        } else {
            System.out.printf("El promedio general de calificaciones del curso es: %.2f%n", promedio);
        }
    }

    // ==================== UTILIDADES DE LECTURA DE DATOS ====================

    private static int leerEntero(String mensaje, int min, int max) {
        while (true) {
            System.out.print(mensaje);
            try {
                int valor = Integer.parseInt(sc.nextLine().trim());
                if (valor < min || valor > max) {
                    System.out.println("Valor fuera de rango. Debe estar entre " + min + " y " + max + ".");
                    continue;
                }
                return valor;
            } catch (NumberFormatException e) {
                System.out.println("Entrada inválida. Ingrese un número entero.");
            }
        }
    }

    private static double leerNota(String mensaje) {
        while (true) {
            System.out.print(mensaje);
            try {
                double valor = Double.parseDouble(sc.nextLine().trim().replace(',', '.'));
                if (valor < 0 || valor > 10) {
                    System.out.println("La calificación debe estar entre 0 y 10.");
                    continue;
                }
                return valor;
            } catch (NumberFormatException e) {
                System.out.println("Entrada inválida. Ingrese un número (ej. 8.5).");
            }
        }
    }

    private static String leerTextoNoVacio(String mensaje) {
        while (true) {
            System.out.print(mensaje);
            String valor = sc.nextLine().trim();
            if (valor.isEmpty()) {
                System.out.println("El valor no puede estar vacío.");
                continue;
            }
            return valor;
        }
    }

    private static String leerCedulaNueva(String mensaje) {
        while (true) {
            String cedula = leerTextoNoVacio(mensaje);
            if (!cedula.matches("\\d{10}")) {
                System.out.println("La cédula debe contener exactamente 10 dígitos numéricos.");
                continue;
            }
            if (gestor.buscar(cedula) != -1) {
                System.out.println("Ya existe un estudiante registrado con esa cédula.");
                continue;
            }
            return cedula;
        }
    }

    private static LocalDate leerFecha(String mensaje) {
        while (true) {
            String texto = leerTextoNoVacio(mensaje);
            try {
                LocalDate fecha = LocalDate.parse(texto, FORMATO_FECHA);
                if (fecha.isAfter(LocalDate.now())) {
                    System.out.println("La fecha de nacimiento no puede ser posterior a hoy.");
                    continue;
                }
                return fecha;
            } catch (DateTimeParseException e) {
                System.out.println("Formato de fecha inválido. Use dd/MM/yyyy (ej. 15/03/2001).");
            }
        }
    }

    private static boolean leerSiNo(String mensaje) {
        while (true) {
            System.out.print(mensaje);
            String valor = sc.nextLine().trim().toUpperCase(Locale.ROOT);
            if (valor.equals("S")) {
                return true;
            }
            if (valor.equals("N")) {
                return false;
            }
            System.out.println("Respuesta inválida. Escriba S o N.");
        }
    }
}