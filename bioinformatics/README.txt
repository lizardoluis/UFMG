================TRABALHO PRÁTICO 1 DE INTRODUÇÃO A BIOINFORMÁTICA: Alinhamento de Sequências Proteicas=====================

**
Hugo Richard Amaral (hucharal@dcc.ufmg.br)
Luís Eduardo Oliveira Lizardo (lizardo@dcc.ufmg.br)

**
O Alinhamento de sequências possibilita comparar duas sequências e verificar a similaridade entre elas. Neste trabalho foi implementado um algoritmo de alinhamento de sequências para tentar identificar possíveis mutações em uma proteína. As analises foram feitas para a enzima triose-fosfato isomerase (TIM). O objetivo do trabalho é identificar as mutações que podem alterar a função proteica desta enzima e sugerir possíveis modificações que possam restaurar a função proteica desta enzima.


** Código-fonte:

Os arquivos listados a seguir se encontram na pasta src.

* Arquivos:

 - main.cpp: Arquivo principal do programa.

 - Align.h/Align.cpp: Implementa o algoritmo de alinhamento.

 - ScoringMatrix.h/ScoringMatrix.cpp:  Implementa a estrutura de dados que armazena a matriz de pontuação importada.

 - Import.h/Import.cpp: Implementa as funções responsáveis pela a importação das sequências proteicas.
 

** Compilação

O programa deve ser compilado utilizando-se o compilador G++ através de um makefile ou do seguinte comando:

	g++ src/ScoringMatrix.h src/ScoringMatrix.cpp src/Align.h src/Align.cpp src/Import.h src/Import.cpp src/main.cpp

** Execução

O comando para a execução do programa é da forma:

	./a.out

