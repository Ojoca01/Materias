// objeto é uma estrutua de dados heterogenea com variadeis/dados(atributos) e funções (métodos)
// bibliotecas em java 
import java.util.Locale;

// declaração da classe
public class Pessoa {
    // public -> é um modificador ainda tem : public, private, protected, default
    // class -> deçaração do que está sendo implementado , uma classe 
    // Pessoa -> nome da classe

    String nome;
    String sobrenome;
    int idade;

    // Método para "falar" -> o metodo é uma função
    // declaraçãp de método -> se declaara como uma funcção normal 
    void dizer_ola() {
        System.out.println("Olá! Meu nome é " + nome + " " + sobrenome + " e tenho " + idade + " anos.");
    }

    // Método principal -> o metodo é uma função
    // declaração de método principal 
    public static void main(String[] args) {
        Locale.setDefault(Locale.US);

        //  public-> modificador de acesso
        //  static->  significa que este metodo pertence a classe
        // void é o tipo de retorno do metodo
        // main é simplesmente um nome para a classe

        // Método construtor
        Pessoa pes1 = new Pessoa();// inicializa e aloca memoria ao objeto

        // fixação dos atributos valores
        pes1.nome = "João";// são atribuidos exatamente como em struts/arrays, usando o pondo e dizendo o que deve ser acessado
        pes1.sobrenome = "Santos";
        pes1.idade = 20;

        // Chamando o método -> equivalente ao "return"
        pes1.dizer_ola();
    }
}
