package Gestor_Vehiculos;

import java.util.Scanner;

public class MainVehiculos {
    private static final Scanner scanner = new Scanner(System.in);
    private static final IVehiculoGestor gestor = new GestorVehiculos();

    public static void main(String[] args) {
        int opcion;
        do {
            System.out.println("\n========================================");
            System.out.println("      SISTEMA DE GESTION VEHICULAR      ");
            System.out.println("========================================");
            System.out.println("1. Registrar Automovil");
            System.out.println("2. Registrar Motocicleta");
            System.out.println("3. Listar todos los vehiculos");
            System.out.println("4. Modificar vehiculo por placa");
            System.out.println("5. Eliminar vehiculo por placa");
            System.out.println("6. Salir");
            System.out.print("Seleccione una opcion (1-6): ");

            opcion = leerEntero();

            switch (opcion) {
                case 1:
                    registrarAutomovilCiclico();
                    break;
                case 2:
                    registrarMotocicletaCiclico();
                    break;
                case 3:
                    gestor.mostrarTodos();
                    break;
                case 4:
                    modificarVehiculo();
                    break;
                case 5:
                    eliminarVehiculo();
                    break;
                case 6:
                    System.out.println("Finalizando programa...");
                    break;
                default:
                    System.out.println("Opcion invalida. Intente de nuevo.");
            }
        } while (opcion != 6);
    }

    private static void registrarAutomovilCiclico() {
        char repetir;
        do {
            if (gestor.estaLleno()) {
                System.out.println("AVISO: Capacidad maxima del vector alcanzada (10 vehiculos).");
                return;
            }

            System.out.println("\n--- REGISTRO DE AUTOMOVIL ---");
            String placa = leerTextoNoVacio("Placa: ");

            if (gestor.buscarPorPlaca(placa) != -1) {
                System.out.println("ERROR: Ya existe un vehiculo con esa placa.");
            } else {
                String marca = leerTextoNoVacio("Marca: ");
                String modelo = leerTextoNoVacio("Modelo: ");
                int anio = leerEnteroPositivo("Ano: ");
                double precio = leerDoubleNoNegativo("Precio: ");
                boolean disponible = leerBooleanoSiNo("Disponible? (1: Si / 2: No): ");
                int puertas = leerEnteroPositivo("Numero de Puertas: ");
                boolean electrico = leerBooleanoSiNo("Es electrico? (1: Si / 2: No): ");

                // CONCEPTO: INSTANCIACION DE OBJETOS
                Vehiculo auto = new Automovil(placa, marca, modelo, anio, precio, disponible, puertas, electrico);
                if (gestor.registrar(auto)) {
                    System.out.println("Automovil registrado exitosamente.");
                } else {
                    System.out.println("No se pudo registrar el automovil.");
                }
            }

            String respuesta = leerRespuestaSiNo("\nDesea registrar otro automovil? (S/N): ");
            repetir = respuesta.charAt(0);
        } while (repetir == 'S');
    }

    private static void registrarMotocicletaCiclico() {
        char repetir;
        do {
            if (gestor.estaLleno()) {
                System.out.println("AVISO: Capacidad maxima del vector alcanzada (10 vehiculos).");
                return;
            }

            System.out.println("\n--- REGISTRO DE MOTOCICLETA ---");
            String placa = leerTextoNoVacio("Placa: ");

            if (gestor.buscarPorPlaca(placa) != -1) {
                System.out.println("ERROR: Ya existe un vehiculo con esa placa.");
            } else {
                String marca = leerTextoNoVacio("Marca: ");
                String modelo = leerTextoNoVacio("Modelo: ");
                int anio = leerEnteroPositivo("Ano: ");
                double precio = leerDoubleNoNegativo("Precio: ");
                boolean disponible = leerBooleanoSiNo("Disponible? (1: Si / 2: No): ");
                int cilindrada = leerEnteroPositivo("Cilindrada (cc): ");
                boolean maletero = leerBooleanoSiNo("Tiene maletero? (1: Si / 2: No): ");

                Vehiculo moto = new Motocicleta(placa, marca, modelo, anio, precio, disponible, cilindrada, maletero);
                if (gestor.registrar(moto)) {
                    System.out.println("Motocicleta registrada exitosamente.");
                } else {
                    System.out.println("No se pudo registrar la motocicleta.");
                }
            }

            String respuesta = leerRespuestaSiNo("\nDesea registrar otra motocicleta? (S/N): ");
            repetir = respuesta.charAt(0);
        } while (repetir == 'S');
    }

    private static void modificarVehiculo() {
        String placa = leerTextoNoVacio("\nIngrese la placa del vehiculo a modificar: ");
        int indice = gestor.buscarPorPlaca(placa);

        if (indice == -1) {
            System.out.println("ERROR: No se encontro ningun vehiculo con la placa indicada.");
            return;
        }

        double nuevoPrecio = leerDoubleNoNegativo("Nuevo Precio: ");
        boolean nuevaDisponibilidad = leerBooleanoSiNo("Nueva Disponibilidad? (1: Si / 2: No): ");

        if (gestor.modificar(indice, nuevoPrecio, nuevaDisponibilidad)) {
            System.out.println("Vehiculo modificado correctamente.");
        } else {
            System.out.println("Error al actualizar los datos.");
        }
    }

    private static void eliminarVehiculo() {
        String placa = leerTextoNoVacio("\nIngrese la placa del vehiculo a eliminar: ");
        int indice = gestor.buscarPorPlaca(placa);

        if (indice == -1) {
            System.out.println("ERROR: No se encontro ningun vehiculo con la placa indicada.");
            return;
        }

        if (gestor.eliminar(indice)) {
            System.out.println("Vehiculo eliminado exitosamente (memoria contigua compactada).");
        } else {
            System.out.println("Error al intentar eliminar el vehiculo.");
        }
    }

    private static String leerTextoNoVacio(String mensaje) {
        String valor;
        do {
            System.out.print(mensaje);
            valor = scanner.nextLine().trim();
            if (valor.isEmpty()) {
                System.out.println("ERROR: Este campo no puede estar vacio.");
            }
        } while (valor.isEmpty());
        return valor;
    }

    private static String leerRespuestaSiNo(String mensaje) {
        String valor;
        do {
            System.out.print(mensaje);
            valor = scanner.nextLine().trim();
            if (valor.equalsIgnoreCase("S")) {
                return valor;
            }
            if (valor.equalsIgnoreCase("N")) {
                return valor;
            }
            System.out.println("ERROR: Ingrese solo S o N.");
        } while (true);
    }

    private static boolean leerBooleanoSiNo(String mensaje) {
        String valor;
        do {
            System.out.print(mensaje);
            valor = scanner.nextLine().trim();
            if (valor.equals("1")) {
                return true;
            }
            if (valor.equals("2")) {
                return false;
            }
            System.out.println("ERROR: Ingrese 1 para Si o 2 para No.");
        } while (true);
    }

    private static int leerEntero() {
        while (!scanner.hasNextInt()) {
            System.out.print("Entrada invalida. Ingrese un numero entero: ");
            scanner.next();
        }
        int valor = scanner.nextInt();
        scanner.nextLine();
        return valor;
    }

    private static int leerEnteroPositivo(String mensaje) {
        int valor;
        do {
            System.out.print(mensaje);
            while (!scanner.hasNextInt()) {
                System.out.print("Entrada invalida. Ingrese un numero entero positivo: ");
                scanner.next();
            }
            valor = scanner.nextInt();
            scanner.nextLine();
            if (valor <= 0) {
                System.out.println("ERROR: El valor debe ser mayor que 0.");
            }
        } while (valor <= 0);
        return valor;
    }

    private static double leerDouble() {
        while (!scanner.hasNextDouble()) {
            System.out.print("Entrada invalida. Ingrese un valor numerico: ");
            scanner.next();
        }
        double valor = scanner.nextDouble();
        scanner.nextLine();
        return valor;
    }

    private static double leerDoubleNoNegativo(String mensaje) {
        double valor;
        do {
            System.out.print(mensaje);
            while (!scanner.hasNextDouble()) {
                System.out.print("Entrada invalida. Ingrese un valor numerico: ");
                scanner.next();
            }
            valor = scanner.nextDouble();
            scanner.nextLine();
            if (valor < 0) {
                System.out.println("ERROR: El precio no puede ser negativo.");
            }
        } while (valor < 0);
        return valor;
    }
}
