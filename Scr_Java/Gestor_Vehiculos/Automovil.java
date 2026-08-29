package Gestor_Vehiculos;


public class Automovil extends Vehiculo {
    private int numeroPuertas;
    private boolean electrico;

    public Automovil(String placa, String marca, String modelo, int anio, double precio, 
                     boolean disponible, int numeroPuertas, boolean electrico) {
        
        super(placa, marca, modelo, anio, precio, disponible);
        this.numeroPuertas = numeroPuertas;
        this.electrico = electrico;
    }

    
    @Override
    public void mostrarInformacion() {
        System.out.println("----------------------------------------");
        System.out.println("Tipo: Automovil");
        mostrarDatosComunes();
        System.out.println("Numero de Puertas: " + numeroPuertas);
        System.out.println("Electrico: " + (electrico ? "Si" : "No"));
        System.out.println("----------------------------------------");
    }

    public int getNumeroPuertas() { return numeroPuertas; }
    public void setNumeroPuertas(int numeroPuertas) { this.numeroPuertas = numeroPuertas; }
    public boolean isElectrico() { return electrico; }
    public void setElectrico(boolean electrico) { this.electrico = electrico; }
}