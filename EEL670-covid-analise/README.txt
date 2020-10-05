O programa neste projeto permite realizar diversas análises estatísticas sobre os dados referentes ao COVID19.

Para executar:
	./covid <comando> [estado] [-n=tamanho]

	Onde os comandos são:
	[help]                        -> Mostra o display de ajuda.
	[porcentagemEstado]           -> Calcula a série histórica da porcentagem em relação ao valor de obitos no estado pedido.
	[porcentagemNacao]            -> Calcula a série histórica da porcentagem em relação ao valor de obitos no país.
	[categoriaEstado]             -> Informa uma lista de estados com suas respectivas situações: queda, estavel ou crescente.
	[categoriaNacao]              -> Informa se o país está em queda, estável em crescente.
	[extremos]                    -> Informa o estado que está com maior crescimento e maior queda
	[acumuladoEstado]             -> Calcula a série histórica dos valor acumulados do estado pedido.
	[acumuladoNacao]              -> Calcula a série histórica dos valor acumulados da nação.
	[listarDisponiveis]           -> Mostra a Lista dos estados disponiveis para consulta.
	A opcao [-n=tamanho] irá configurar o paramêtro N para o cálculo da média móvel (padrão=7).

	Para inserir novos dados, basta acessar a pasta data/ e alterar cada um dos arquivos de texto relativo a cada um dos estados. Não é necessário um arquivo de texto para o país, os dados do país já são inferidos dos dados do estado. Todos os arquivos de texto devem possuir o mesmo número de linhas (contando o número de óbitos a partir da mesma data). 
	
	Para configurar a data inicial da medição, basta alterar o arquivo DATE.txt e inserir uma única linha contendo o UNIXTIMESTAMP referente ao começo das mediçoes.
	
	Para compilar, basta rodar:
		cd ./src 
		make



