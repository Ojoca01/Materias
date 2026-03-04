#comandos condicionais if,else,elif,match_case


idade=int(input("Digite sua idade:"))

if(idade<=18):print("voce eh jovem: ",idade)
elif(idade==25):print("voce eh exeção: ",idade)
else:print("voce eh maior de idade: ",idade)

comando=int(input(print("DIGITE:1-INICIAR\n 2-PARAR\n   3-REINICIAR ")))

match comando:
    case 1:
        print("Iniciando...")
    case 2:
        print("Parando...")
    case 3:
        print("Reiniciando...")
    case _:
        print("Comando desconhecido")
