// ===== Classe base: Pontos =====
public class Pontos {
    protected double x, y;

    public Pontos(double x, double y) {
        this.x = x;
        this.y = y;
    }

    public void setPonto(double x, double y) {
        this.x = x;
        this.y = y;
    }

    public double getX() {
        return x;
    }

    public double getY() {
        return y;
    }
    public static void main(String[] args) {
        Circulo c = new Circulo(0, 0, 5);
        System.out.println("\n\nCirculo:");
        System.out.println(" - Centro em (" + c.getX() + ", " + c.getY() + ")");
        System.out.println(" - Raio: " + c.getRaio());
        System.out.println(" - Area: " + c.area());
        System.out.println(" - Volume: " + c.volume());

        System.out.println("\n-------------------------");

        Cilindro cil = new Cilindro(0, 0, 5, 10);
        System.out.println("Cilindro:");
        System.out.println(" - Base em (" + cil.getX() + ", " + cil.getY() + ")");
        System.out.println(" - Raio: " + cil.getRaio());
        System.out.println(" - Altura: " + cil.getAlt());
        System.out.println(" - Area total: " + cil.area());
        System.out.println(" - Volume: " + cil.volume());
    }
}


// ===== Classe Circulo =====
class Circulo extends Pontos {
    protected double raio;

    public Circulo(double X, double Y, double raio) {
        super(X, Y); // chama o construtor da superclasse
        this.raio = raio;
    }

    public double getRaio() {
        return raio;
    }

    public void setRaio(double raio) {
        this.raio = raio;
    }

    public double area() {
        return Math.PI * raio * raio;
    }

    public double volume() {
        return 0; // círculo não tem volume
    }
}


// ===== Classe Cilindro =====
class Cilindro extends Circulo {
    protected double alt;

    public Cilindro(double X, double Y, double raio, double alt) {
        super(X, Y, raio);
        this.alt = alt;
    }

    public void setAlt(double alt) {
        this.alt = alt;
    }

    public double getAlt() {
        return alt;
    }

    public double area() {
        return (2 * Math.PI * raio * raio) + (2 * Math.PI * raio * alt);
    }

    public double volume() {
        return Math.PI * raio * raio * alt;
    }
}



