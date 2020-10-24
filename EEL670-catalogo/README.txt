O programa neste projeto pretende implementar um catalogo de filmes.

Para executar:
	Uso: ./catalogo  <comando> 
    Parametros adicionais serão passados de forma interativa.
    Obs: O nome do filme deve ser constituido de apenas um nome sem espacos
	Onde os comandos são:
    
    [help]                  -> Mostra o display de ajuda.
    cout << "Uso: ./catalogo  <comando> " << endl
    [inserir]              -> parametros: <nome> <nomeProdutora> <notaFilme> Insere o filme no catalogo
    [remover]              -> parametros: <nome> Remove o filme do catalogo.
    [edicaoProdutora]      -> parametros: <nome> <novaProdutora> altera o nome da produtora do filme
    [edicaoNota]           -> parametros: <nome> <novaNota> altera a nota do filme
    [exibir]               -> Exibe todo o catalogo.
    [buscaPorNota]         -> Exibe o filme mais bem avaliado.
    [buscaPorNome]         -> Retorna os dados daquele filme.
	
	Para compilar, basta rodar:
		cd ./src 
		make
    Um arquivo com testes também foi criado e pode ser executado fazendo 
        cd ./src
        ./teste.sh

    O arquivo data.txt armazena os dados persistentes do catalogo.

