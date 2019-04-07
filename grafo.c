#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"
#include <graphviz/cgraph.h>

//header de funções adicionais
void recomenda(grafo g, grafo r, Agnode_t *u, Agnode_t *v);

//------------------------------------------------------------------------------
// (apontador para) estrutura de dados para representar um grafo
//
// o grafo pode ser direcionado ou não
//
// o grafo tem um nome, que é uma "string"

struct grafo {
	Agraph_t *g;
};

//------------------------------------------------------------------------------
// desaloca toda a memória usada em *g
//
// devolve 1 em caso de sucesso,
//         ou
//         0, caso contrário

int destroi_grafo(grafo g) {
    agclose(g->g);
    free(g);
    // Devolve 1 no erro pq não percebe erro
 	return 1;
}
//------------------------------------------------------------------------------
// lê um grafo no formato dot de input
//
// devolve o grafo lido,
//         ou
//         NULL, em caso de erro

grafo le_grafo(FILE *input) {
	grafo g = malloc(sizeof(struct grafo));
	g->g = agread(input, 0);

    return g;
}
//------------------------------------------------------------------------------
// escreve o grafo g em output usando o formato dot.
//
// devolve o grafo escrito,
//         ou
//         NULL, em caso de erro

grafo escreve_grafo(FILE *output, grafo g) {
	agwrite(g->g, output);
	return g;
}

//------------------------------------------------------------------------------
// devolve o grafo de recomendações de g
//
// cada aresta {c,p} de H representa uma recomendação do produto p
// para o consumidor c, e tem um atributo "weight" que é um inteiro
// representando a intensidade da recomendação do produto p para o
// consumidor c.
//
// cada vértice de g tem um atributo "tipo" cujo valor é 'c' ou 'p',
// conforme o vértice seja consumidor ou produto, respectivamente

void recomenda(grafo g, grafo r, Agnode_t *u, Agnode_t *v){
    char attr_str[100];
    Agedge_t *e, *edge;
    int intersect = 0, difference = 0;

    // Calcula interseção e a diferença das vizinhanças
    for(e = agfstout(g->g, u); e; e = agnxtout(g->g, e)){
        edge = agedge(g->g,e->node,v,NULL,FALSE);
        if(edge){
            intersect++;
        } else {
            difference++;
        }
    }

    // se recomendar, soma 1 no peso da aresta dos produtos recomendados
    if(intersect >= difference && intersect != 0 && difference > 0){
        for(e = agfstout(g->g, u); e; e = agnxtout(g->g, e)){
            edge = agedge(g->g,e->node,v,NULL,FALSE);
            if(!edge){
                edge = agedge(r->g, agnode(r->g, agnameof(e->node), FALSE), agnode(r->g, agnameof(v), FALSE), NULL, TRUE);
                sprintf(attr_str, "%d", atoi(agget(edge, (char*)(unsigned long) "weight")) + 1);
                agset(edge, (char*)(unsigned long) "weight", attr_str);
            }
        }
    }
}

grafo recomendacoes(grafo g){
    // !-- setup do grafo de recomendações
    grafo r = malloc(sizeof(struct grafo));

    r->g = agopen((char*)(unsigned long) "R", Agstrictundirected, NULL);

    agattr(r->g, AGEDGE, (char*)(unsigned long) "weight", (char*)(unsigned long) "");
    agattr(r->g, AGNODE, (char*)(unsigned long) "tipo", (char*)(unsigned long) "");

    for(Agnode_t *n = agfstnode(g->g); n; n = agnxtnode(g->g, n)){
        Agnode_t *new_n = agnode(r->g, agnameof(n), TRUE);
		agcopyattr(n, new_n);
    }
    // --! fim do setup

    // checa recomendações entre todos os pares de vértices
	for (Agnode_t *n1 = agfstnode(g->g); n1; n1 = agnxtnode(g->g,n1)) {
		if(strcmp(agget(n1, (char *)(unsigned long)  "tipo"), "c") == 0){
			for (Agnode_t *n2 = agnxtnode(g->g,n1); n2; n2 = agnxtnode(g->g,n2)){
				if(strcmp(agget(n2, (char *)(unsigned long) "tipo"), "c") == 0){
					recomenda(g, r, n1, n2);
                    recomenda(g, r, n2, n1);
				}
			}
		}
	}

	return r;
}

//------------------------------------------------------------------------------
