def adicionar_usuario(dicionario, nome, valor):
    """
    Adiciona um usuário ao dicionário, garantindo que não haja repetição de nomes.
    """
    if nome in dicionario:
        print(f"⚠️ O nome '{nome}' já está em uso. Escolha outro.")
        return 
    else:
        dicionario[nome] = valor
        print(f"✅ Usuário '{nome}' adicionado com valor '{valor}'.")
        return 


def gerador_de_dicionario():
    """
    Preenche o dicionário de usuários em loop, perguntando se deseja adicionar mais.
    """
    dicionario = dict()
    print("Este dicionario se inicia vazio,por tanto, não possui usuarios")

    pergunta1 = input("Deseja adicionar algum usuário? (s/n): ").strip().lower()

    if pergunta1 != "s":
        return 
    
    else:
        while True:
            nome = input("Digite um nome de usuário: ")
            valor = input(f"Digite o valor para {nome}: ")

            adicionar_usuario(dicionario, nome, valor)

            pergunta2 = input("Deseja adicionar outro usuário? (s/n): ").strip().lower()
            if pergunta2 != "s":

                break

        return dicionario


def printar_bonitinho(dicionario):
    """
    Exibe os usuários e valores de forma organizada.
    """
    print("\n📋 Lista de Usuários:")
    for nome, valor in dicionario.items():
        print(f" - Usuário: {nome} | Valor: {valor}\n")


# Execução principal
if __name__ == "__main__":
    usuarios = gerador_de_dicionario()
    printar_bonitinho(usuarios)
    print("\nEncerrando o programa....")

    """
    .values
    .keys
    .values
    """