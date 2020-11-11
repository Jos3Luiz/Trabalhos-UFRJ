Cadastro Médico
Para compilar:
    cd ./src
    make
Para executar:
    cd ./src
    ./main
    
Este programa recebe informações através de um menu iterativo. 
Selecione as opções e digite conforme for solicitado.

Opções do menu:
	1.Exibir paciente -mostra o conteudo em ordem alfabética de todos os pacientes existentes na árvore.
	2.Inserir Paciente - Recebe as informaçoes e cadastra um novo paciente.
		Os Pacientes podem ser de 3 tipos:
		Pacinete comum - não possui informações adicionais
		Paciente doente- possui um double indicando a gravidade da doença
		Paciente internado - possui um unsigned indicando o tempo internado.

	3.Busca Paciente - Mostra as informações de um paciente pesquisando pelo nome dele
	4.Ajuda - mostra esse menu
	5.Sair - deixa o programa
	