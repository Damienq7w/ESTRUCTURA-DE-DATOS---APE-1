package Scr_Java.Gestor_Vehiculos;


public class Motocicleta extends Vehiculo {
    private int cilindrada;
    private boolean tieneMaletero;

    public Motocicleta(String placa, String marca, String modelo, int anio, double precio, 
                       boolean disponible, int cilindrada, boolean tieneMaletero) {
        super(placa, marca, modelo, anio, precio, disponible);
        this.cilindrada = cilindrada;
        this.tieneMaletero = tieneMaletero;
    }

    
    @Override
    public void mostrarInformacion() {
        System.out.println("----------------------------------------");
        System.out.println("Tipo: Motocicleta");
        mostrarDatosComunes();
        System.out.println("Cilindrada: " + cilindrada + " cc");
        System.out.println("Tiene Maletero: " + (tieneMaletero ? "Si" : "No"));
        System.out.println("----------------------------------------");
    }

    public int getCilindrada() { return cilindrada; }
    public void setCilindrada(int cilindrada) { this.cilindrada = cilindrada; }
    public boolean isTieneMaletero() { return tieneMaletero; }
    public void setTieneMaletero(boolean tieneMaletero) { this.tieneMaletero = tieneMaletero; }
}