import java.util.Scanner;

public class P{
// declaração dos atributos 

    private int idade;
    private String cpf,nome;


// metodo contrutor
public void P(int I,String C,String N){
    this.idade=I;
    this.cpf=C;
    this.nome=N;
}

// metodos subsequenctes ( relacionados a classe P)
// metodo de impressão padrão
void imprimir_dados(int idade,String cpf,String nome){
    System.out.println("Cpf: "+cpf);
    System.out.println("Nome: "+nome);
    System.out.println("Idade: "+idade);
}
// Metodos gets->  servem para ...
int get_idade(){
    return idade;
}

String get_cpf(){
    return cpf;
}

String get_nome(){
    return nome;
}

// métodos subsequentes
int fazer_aniversario(){
    idade=idade+1;
    return idade;
}

// chamada principal do método "MAIN"
public static void main (String[] args){
    // instanciação do objeto
    P pes1 = new P();
    // definição dos atributos do objeto ->  por entrada interna
    pes1.idade = 24;
    pes1.cpf = "1111111";
    pes1.nome = "teste";
    // definição dos atributos do objeto ->  por entrada interna

    // chamada padrao da impressao ao final do metodo principal
    pes1.imprimir_dados(pes1.idade,pes1.cpf,pes1.nome);


}

}