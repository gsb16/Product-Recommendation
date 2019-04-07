#include <stdlib.h>
#include <stdio.h>
#include "grafo.h"

//------------------------------------------------------------------------------

int main(void) {

  grafo g = le_grafo(stdin);

  if ( !g )

    return 1;

  escreve_grafo(stdout, g);

  escreve_grafo(stdout, recomendacoes(g));

  return ! destroi_grafo(g);
}
