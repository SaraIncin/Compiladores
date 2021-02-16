#ifndef TOKENS_H
#define TOKENS_H
#include <string>
#define COMA 1001
#define PCOMA 1002
#define CIZQ 1003
#define CDER 1004
#define INT 1005
#define FLOAT 1006
#define NUM 1007
#define ID 1008
#define CHAR 1009
#define DOUBLE 1010
#define VOID 1011
#define FUNC 1012
#define PIZQ 1013 // (
#define PDER 1014 // )
#define IF 1015
#define ELSE 1016
#define WHILE 1017
#define DO 1018
#define BREAK 1019
#define SWITCH 1020
#define CASE 1021
#define DEFAULT 1022
#define AND 1023   // &&
#define EQ 1024    // ==
#define NEQ 1025   // !=
#define LESS 1026  // <
#define LEQ 1027   // <=
#define GEQ 1028   // >=
#define GRE 1029   // >
#define ASSIG 1030 // =
#define SUM 1031   // +
#define SUB 1032   // -
#define MUL 1033   // *
#define DIV 1034   // /
#define RES 1035   // %
#define NEG 1036   // !
#define DOSP 1037  // :
#define TRUE 1038
#define FALSE 1039
#define STRING 1040
#define KIZQ 1041 // {
#define KDER 1042 // }
#define OR 1043   // ||
#define FIN 9001
/*
 * podemos definir más o cambiar las definiciones
 * siempre y cuando actualicemos el lexer
 */
#endif


using namespace std;

/**
 * Estructura para modelar tokens (componentes léxicos)
 */
struct Token {
  int clase;    // léxica
  string valor; // lexema
  int tipo;     // para diferenciar entre diferentes lexemas de una misma clase
                // léxica
public:
  Token(int clase, string valor);
  Token(int clase, string valor, int tipo);
  bool equals(int clase);
};
