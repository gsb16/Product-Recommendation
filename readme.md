Trabalho de implementação 1
CI065 - Algoritmos e Teoria dos Grafos
Maio de 2018

Gabriel de Souza Barreto
Guilherme Bastos de Oliveira

>> Readme com as informações relevantes relacionadas ao trabalho 1 de Grafos. O objetivo do trabalho foi implemetar as funções dadas e eventuais funções adicionais para a leitura de um grafo bipartido de produtos e clientes, criando um grafo também bipartido de recomendações de produtos.

Sobre a estrutura de dados 'struct grafo':
>> Como a biblioteca cgraph estava a disposição e oferece uma estrutura de grafos completa para as necessidades deste trabalho a 'struct grafo' contem apenas um ponteiro para uma varíavel do tipo "Agraph_t".

Sobre funções adicionais:
(As funções da biblioteca cgraph utilizadas serão tratadas posteriormente)
>> Apenas uma função adicional foi necessária para garantir boa organização do código, esta função é a "recomenda(grafo g, grafo r, Agnode_t *u, Agnode_t *v)"

Sobre as funções implementadas:
>> "recomenda()" - recebe o grafo de entrada (grafo g) e o grafo de recomendações ('grafo r') com os vértices 'u' e 'v' (ambos pertencentes ao 'grafo g') do tipo "c". A função decide então se 'u' faz recomendações para 'v', em caso afirmativo a função busca os vértices correspondentes no 'grafo r' e incrementa em 1 o peso das arestas entre 'v' e os produtos recomendados.

>> "recomendacoes()" - realiza um loop que passa por todos os pares de vértices (no código, vértices n1 e n2) do grafo de entrada e chama a função recomenda() para cada uma das permutações dos pares de vértices.

>> "destroi_grafo()" - realiza a chamada para a função "agclose()" da biblioteca cgraph que libera a memória utilizada pela estrutura de grafos da própria biblioteca e libera a memória utilizada pela "struct grafo". Sempre devolve 1 ao final pois não é possível decidir se a liberação de memória foi realizada com sucesso.

>> "le_grafo()" - simplesmente aloca uma "struct grafo" e chama a função "agread()" da biblioteca cgraph que realiza a leitura de um grafo em '.dot dado um ponteiro para um arquivo.

>> "escreve_grafo()" - faz uma chamada para a função "agwrite()" da biblioteca cgraph que imprime um grafo em formato '.dot' dado um ponteiro para um arquivo de saída.


Sobre as estruturas da biblioteca cgraph utilizadas:
>> "Agraph_t" - grafo da biblioteca, possui vértices e arestas.
>> "Agedge_t" - arestas, possuem nome e no grafo de recomendações o atributo "peso".
>> "Agnode_t" - vértices, possuem nome e atributo "tipo".

Sobre as funções da biblioteca cgraph utilizadas em "recomenda()" e "recomendacoes()":
>> "agattr()" - cria atributo para um  dos tipos dos dados da biblioteca (grafo, aresta ou vértice) - utilizada para criar os atributos "tipo" e "weight" no grafo de recomendações.

>> "agcopyattr()" - copia atributos de um objeto para outro - utilizada para copiar os atributos dos vértices do grafo de entrada para os vértices do grafo de recomendações

>> "agget()" - dados um objeto da biblioteca e um atributo, busca o valor do atributo informado para o objeto em questão - utilizada para buscar o tipo dos vértices e pesos das arestas

>> "agset()" - dados um objeto, um atributo e um valor, define o para o objeto o valor do atributo informado - utilizada para atualizar o peso das arestas

>> "agedge()" - busca aresta em um grafo e devolve seu ponteiro - utilizada para verificar as relações entre produtos e consumidores, e encontrar a aresta de recomendação.

>> "agnode()" - busca vértices em um grafo e devolve seu ponteiro - utilizada para buscar vértices do 'grafo r' a partir de seus nomes no 'grafo g'.

>> "agfst{node, out}()" e "agnxt{node, out}()" - retornam o primeiro vértice/aresta de acordo com a organização interna da biblioteca e o próximo vértice/aresta, respectivamente - utilizadas para percorrer o grafo.

Sobre peculiaridades da implementação:
>> Valores de atributo como strings - Como os atributos por padrão da biblioteca possuem como valores strings foi optado não modificar isto e trabalhar com strings mesmo para o atributo de peso das arestas, o que fez necessário toda vez que se buscava o atributo converter para inteiro e para toda atualização converter novamente para string.

>> Casting (char*)(unsigned long) nos tipos 'const char *' - um artifício técnico foi utilizado para suprimir a geração de warnings relacionados as flags "-Wdiscarded-qualifiers" e "-Wcast-qual", o casting serve apenas para que esses warnings não sejam levantados pelo compilador.
