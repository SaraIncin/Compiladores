/**
 * Estructura para modelar entradas de la TT
 */
typedef struct tipo {
  int id; //identificador
  char *tipo;
  int tam; //tamaño
  int elem; //elemento en el lexema
  int tipoBase; 
} simbolo ;

/**
 * Inicialización de símbolos
 */
simbolo *crea_entrada_tipo(int id, char *tipo, int tam, int elem, int tipoBase);
