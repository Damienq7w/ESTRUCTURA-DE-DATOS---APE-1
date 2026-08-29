package Scr_Java.Gestor_Vehiculos;


public class GestorVehiculos implements IVehiculoGestor {
    
    private static final int CAPACIDAD = 10;
    private final Vehiculo[] vehiculos;
    private int cantidad; 

    public GestorVehiculos() {
        this.vehiculos = new Vehiculo[CAPACIDAD];
        this.cantidad = 0;
    }

    @Override
    public boolean registrar(Vehiculo nuevoVehiculo) {
        
        if (nuevoVehiculo == null || estaLleno()) {
            return false;
        }
        
        if (buscarPorPlaca(nuevoVehiculo.getPlaca()) != -1) {
            return false;
        }
        
        
        vehiculos[cantidad] = nuevoVehiculo;
        cantidad++;
        return true;
    }

    @Override
    public int buscarPorPlaca(String placa) {
        
        for (int i = 0; i < cantidad; i++) {
            if (vehiculos[i].getPlaca().equalsIgnoreCase(placa)) {
                return i; 
            }
        }
        return -1; 
    }

    @Override
    public boolean modificar(int indice, double nuevoPrecio, boolean nuevaDisponibilidad) {
        if (indice < 0 || indice >= cantidad || nuevoPrecio < 0.0) {
            return false;
        }
        vehiculos[indice].setPrecio(nuevoPrecio);
        vehiculos[indice].setDisponible(nuevaDisponibilidad);
        return true;
    }

    @Override
    public boolean eliminar(int indice) {
        if (indice < 0 || indice >= cantidad) {
            return false;
        }
        
        
        
        for (int i = indice; i < cantidad - 1; i++) {
            vehiculos[i] = vehiculos[i + 1];
        }
        
        
        vehiculos[cantidad - 1] = null;
        cantidad--;
        return true;
    }

    @Override
    public void mostrarTodos() {
        if (cantidad == 0) {
            System.out.println("No hay vehiculos registrados en el sistema.");
            return;
        }
        
        for (int i = 0; i < cantidad; i++) {
            System.out.println("\n[Registro " + (i + 1) + "]");
            vehiculos[i].mostrarInformacion();
        }
    }

    @Override
    public boolean estaLleno() {
        return cantidad >= CAPACIDAD;
    }

    @Override
    public int getCantidad() {
        return cantidad;
    }

    public Vehiculo obtenerVehiculo(int indice) {
        if (indice >= 0 && indice < cantidad) {
            return vehiculos[indice];
        }
        return null;
    }
}
