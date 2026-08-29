package Scr_Java.Gestor_Vehiculos;

public abstract class Vehiculo {
    
    protected String placa;
    protected String marca;
    protected String modelo;
    protected int anio;
    protected double precio;
    protected boolean disponible;

    public Vehiculo(String placa, String marca, String modelo, int anio, double precio, boolean disponible) {
        this.placa = placa;
        this.marca = marca;
        this.modelo = modelo;
        this.anio = anio;
        this.precio = precio;
        this.disponible = disponible;
    }

    
    public abstract void mostrarInformacion();

    public void mostrarDatosComunes() {
        System.out.println("Placa: " + placa);
        System.out.println("Marca: " + marca);
        System.out.println("Modelo: " + modelo);
        System.out.println("Ano: " + anio);
        System.out.println("Precio: $" + precio);
        System.out.println("Disponible: " + (disponible ? "Si" : "No"));
    }

    
    public String getPlaca() { return placa; }
    public void setPlaca(String placa) { this.placa = placa; }
    public String getMarca() { return marca; }
    public String getModelo() { return modelo; }
    public int getAnio() { return anio; }
    public double getPrecio() { return precio; }
    public void setPrecio(double precio) { this.precio = precio; }
    public boolean isDisponible() { return disponible; }
    public void setDisponible(boolean disponible) { this.disponible = disponible; }
}