import java.util.Scanner;
import java.lang.Math;

public class Operacoes {

    int x, y;

    int soma() {
        return x + y;
    }

     int subtracao() {
        return x - y;
    }

     int divisao() {
        return x / y;
    }

     int multiplicacao() {
        return x * y;
    }

    int exponencial() {
        int resultado =(int)  Math.pow(x,y);
        return resultado;
    }  


    public static void main(String[] args) {


        
        Operacoes op = new Operacoes();
        Scanner sc = new Scanner(System.in);
        System.out.println();
        System.out.println("Digite os valores a serem operados:");
        op.x  = sc.nextInt();
        op.y = sc.nextInt();

        System.out.println();
        System.out.println("===Resultados===");
        System.out.println("Soma:");
        System.out.println(op.soma());
        System.out.println("Substração:");
        System.out.println(op.subtracao());
        System.out.println("Divisão:");
        System.out.println(op.divisao());
        System.out.println("multiplicação:");
        System.out.println(op.multiplicacao());
        System.out.println("exponencial:");
        System.out.println(op.exponencial());

        sc.close();

    }
}
