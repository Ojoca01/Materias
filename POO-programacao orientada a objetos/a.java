

// Nota: para que o programa entenda "." como o separador de decimais deve-se selecionar o um idioma onde o ponto tem esta função,

// neste caso o ingles americano e para isso acontecer deve-se setar a biblioteca com "import java.util.Locale" 

// e selecionar o idioma com "Locale.setDefault(Locale.US)"  dentro da classe in coding ,obs:. coloque no ponto mais alto que puder
/*Os modificadores de acesso da linguagem Java têm o objetivo de tornar as implementações mais adequadas a uma diversidade de propósitos. 
Uma característica geral dos modificadores de acesso é que são definidos sempre em palavras minúsculas,
tais como FINAL, NATIVE, STATIC, SYNCHRONIZED e VOLATILE, os quais serão tratados neste artigo. */

//static ->torna esse atributo possível de ser inicializado em qualquer parte da classe,
// mas quando recebe um valor, ele é compartilhado com todos os objetos da classe.

// native ->

// final ->
import java.util.Locale;

public class Main {

	public static void main(String[] args) {
		Locale.setDefault(Locale.US);
		
		// DECLARAÇÃO DE VARIÁVEIS EM JAVA
		
		// inteiro em java : int  
		// caracter em java : char  
		// string em java : string  
		// boolean em java : boolean  
		// numero real em java : double  
		
		
		int idade ;
		char genero ;
		String nome; 
		double salario,altura ;
		
		// EXEMPLO
		
		idade = 30;
		genero = 'M';				
		nome = "João" ;
		salario = 1249.134;
		altura= 15.2;
		
		// SAIDA DE DADOS EM JAVA
		
		// System.out.print(" ",var) - > impressao padrao 
		// OU
		// System.out.println("",var) -> impressao em linha 
		
		//EXEMPLO
		System.out.println("Idade: " + idade );
		System.out.println("Genero: "+ genero);
		System.out.println("Nome: "+ nome);
		System.out.println("Salario: "+salario );
		System.out.println("altura: "+altura );
		
		System.out.println();
	
		 
		// para setar o formato da string String.format( estilo "%.2f", nome da string)
		// exemplo:.
		// String.format(placeholder,string)
		System.out.println("altura: "+ String.format("%.2f", altura) );
	
		// OPERADORES ARITMETICOS
		// soma : +
		// subtracao : - 
		// divisao : /
		// multiplicacao : *
		// resto : % 
		
		// OPERADORES COMPARATIVOS
		// menor : <
		// menor ou igual : <=
		// maior : >
		// maior ou igual : >=
		// igual : ==
		// diferente : !=
		
		// OPERADORES LOGICOS 
		
		
		//PROCESSAMENTO E CASTING EM JAVA
		//OBS:. casting é ...
		
		
		
	//fim da linha
}

}
											