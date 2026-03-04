/*TAREFA_1_POO
Entregar pelo SIGAA até quarta 05/11/25
• === Crie uma classe ContaBancária que possua os seguintes atributos:
• Nome do proprietário
• Saldo
• Número da conta
• Agência
• === Implemente para esta classe os seguintes métodos:
• Ver saldo
• Depositar
• Sacar
• Exibir proprietário
• ===  No main
• Instanciar um objeto da classe
• Fazer pelo menos 1 depósito e 1 saque nessa conta
• Mostrar o saldo após cada operação feita*/
import javax.swing.JOptionPane;

public class ContaBancaria{
// atributos iniciais
    private static String nome_do_proprietario;
    private static double saldo ;
    private static int numero_da_conta;
    private static String agencia;
// metodo contrutor
public void ContaBancaria(double S,int N_C,String N_P,String A){
    this.nome_do_proprietario=N_P;
    this.saldo=S;
    this.numero_da_conta=N_C;
    this.agencia=A;
}
//metodos da classe ContaBancaria[ ainda devem ser instanciados no objeto da chamada principal]
public static void ver_saldo(double saldo){
        JOptionPane.showMessageDialog(null, "Saldo: "+saldo);
}
// metodo para somar quantia ao saldo
public static double depositar(double saldo){
    double entrada_temporaria =  Double.parseDouble(JOptionPane.showInputDialog("Digite a quantia que deseja depositar"));
    saldo=saldo+entrada_temporaria;
    return saldo;
}
// metodo para subtrair quantia do saldo
public static double sacar(double saldo){
    double entrada_temporaria =  Double.parseDouble(JOptionPane.showInputDialog(" Digite a quantia que deseja sacar da conta"));
    saldo = saldo - entrada_temporaria;
    return saldo;
}
// metodo para exibir proprietario
public static void exibirproprietario(String nome_do_proprietario){
    JOptionPane.showMessageDialog(null, "Proprietario: "+ nome_do_proprietario);

}

// cahamada principal
public static void main (String[] args){
    ContaBancaria C1;
    C1 = new ContaBancaria();
    C1.nome_do_proprietario= JOptionPane.showInputDialog(" Digite o nome do proprietario da conta");
    C1.saldo = 0;
    C1.numero_da_conta = Integer.parseInt(JOptionPane.showInputDialog(" Digite o numero da contra"));
    C1.agencia= JOptionPane.showInputDialog(" Digite o nome do agencia bancaria");  
    
    /* manipulação de dados com "import javax.swing.JOptionPane", entrada com "JOptionPane.showInputDialog("texto de entrada")" 
     saida com  JOptionPane.showMessageDialog(null, "mensagem a ser passada","Titulo da mensagem",JOptionPane."icone da mensagem");
 */

//implementar options e laços

    JOptionPane.showMessageDialog(null, "Conta Bancaria");
    exibirproprietario(nome_do_proprietario);
    ver_saldo(C1.saldo);    
    C1.saldo=depositar(C1.saldo);
    ver_saldo(C1.saldo);
    C1.saldo=sacar( C1.saldo);
    ver_saldo(C1.saldo);
        JOptionPane.showMessageDialog(null, "Encerrando programa....");
    
}

}