O programa neste projeto permite realizar diversas análises estatísticas sobre os dados referentes ao COVID19.

Para executar:
	./analise <comando> [nome do arquivo] [-n=tamanho]

	Onde os comandos são:
	[help]                      -> Mostra o display de ajuda.
	[palavra]                   -> Calcula a palavra mais utilizada no texto.
	[sequencia]                 -> Calcula sequencia de tamanho -n=tamanho mais utilizada no texto usando o método de grafos simples.
    [sequencia2]                -> Calcula sequencia de tamanho -n=tamanho mais utilizada no texto usando o método de super arestas.
	A opcao [-n=tamanho] irá configurar o paramêtro N para o cálculo da melhor sequencia de palavras (padrão=3).
    A opcao obrigatória [nome do arquivo] deve ser o caminho com um arquivo de texto para ser analizada.

	Para compilar, basta rodar:
		make

    Obs:
        O metodo de grafos simples é uma busca em profundidade = TAMANHO. Embora seja mais flexível com relação as palavras adjacentes, pode ocasionar resultados insperados caso um loop ocorra no grafo.
        O metodo de super arestas (recomendado pelo exercicio) foi modelado como um vértice com contem TAMANHO palavras consecutivas. 


