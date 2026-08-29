package Scr_Java.Gestor_Vehiculos;

public interface IVehiculoGestor {
    boolean registrar(Vehiculo nuevoVehiculo);
    boolean modificar(int indice, double nuevoPrecio, boolean nuevaDisponibilidad);
    boolean eliminar(int indice);
    int buscarPorPlaca(String placa);
    void mostrarTodos();
    boolean estaLleno();
    int getCantidad();
}