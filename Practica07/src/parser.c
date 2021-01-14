#include "parser.h"
#include <stdio.h>
extern token *yylex();
extern int yylineno;


void parse() {
  P();
}



void error(char *msg) {
  printf("\n%s", msg);
  printf(": línea %i\n", yylineno);
  exit(1);
}


//AQUI EMPIEZA
void P(){
    D();
	F();
	puts("Fin de análisis sintáctico.");
}

void D(){
    if(equals(tokenActual,INT) || equals(tokenActual,FLOAT) || equals(tokenActual,CHAR) || equals(tokenActual,DOUBLE)  || equals(tokenActual,VOID)){
        TI();
	    LV();
	    if(equals(tokenActual, PCOMA)){
	        tokenActual = yylex();
	        D();
	    }
	    else{
	        error("Error de sintaxis"); 
	    }
    }
}

void TI(){
    B();
    C();
}

void B(){
    switch(tokenActual->clase){
	    case INT:
	        tokenActual = yylex();        
	        break;
	    case FLOAT:
	        tokenActual = yylex();
	        break;
        case CHAR:
	        tokenActual = yylex();
	        break;
	    case DOUBLE:
	        tokenActual = yylex();
	        break;
	    case VOID:
	        tokenActual = yylex();
	        break;
	    default:
	        error("Error de sintaxis");
	        break;
        }
}

void C(){
    if(equals(tokenActual,CIZQ)){
        tokenActual=yylex();
        if(equals(tokenActual,NUM)){
            tokenActual=yylex();
            if(equals(tokenActual,CDER)){
                tokenActual=yylex();
                C();
            }else{
                error("Error de sintaxis");
            }
        } else{
            error("Error de sintaxis");
        }    
   }
   
}

void LV(){
    if(equals(tokenActual,ID)){
        tokenActual=yylex();
        LVP();
    }else{
        error("Error de sintaxis");
    }
}

void LVP(){
    if(equals(tokenActual, COMA)){
        tokenActual = yylex();
        if(equals(tokenActual,ID)){
            tokenActual = yylex();
            LVP();
        }else{
            error("Error de sintaxis");
        }
    }
}



void F(){
    if(equals(tokenActual,FUNC)){
        tokenActual= yylex();
        if(equals(tokenActual,ID)){
            tokenActual= yylex();
            if(equals(tokenActual,PIZQ)){
                tokenActual= yylex();
                A();
                if(equals(tokenActual, PDER)){
                    tokenActual= yylex();
                    BL();
                    F();
                } else{
                    error("Error de sintaxis");
                }
                
            } else{
                error("Error de sintaxis");
            }
        } else{
            error("Error de sintaxis");
        }
    } 
}

void A(){
    LA();    
}

void LA(){
    TI();
    if(equals(tokenActual,ID)){
        tokenActual = yylex();
        LAP();
    } else{
        error("Error de sintaxis");
    }
}

void LAP(){
    if(equals(tokenActual,COMA)){
        tokenActual = yylex();
        TI();
        if(equals(tokenActual,ID)){
            tokenActual = yylex();
            LAP();
        }else{
            error("Error de sintaxis");
        }
    } 
    
}

void BL(){
    if(equals(tokenActual,KIZQ)){
        tokenActual= yylex();
        D();
        I();
        if(equals(tokenActual,KDER)){
            tokenActual= yylex();
        } else{
            error("Error de sintaxis");
        }
    } else{
        error("Error de sintaxis");
    }
}

void I(){
    S();
    IP();
}

void IP(){
    if(equals(tokenActual,IF) || equals(tokenActual,WHILE) || equals(tokenActual,DO) || equals(tokenActual,SWITCH) || equals(tokenActual,BREAK)|| equals(tokenActual,ID) || equals(tokenActual, KIZQ)){
        S();
        IP();
    }
    
}



void S(){
          
    switch(tokenActual->clase){
	    case IF:
	        tokenActual = yylex();    
            if(equals(tokenActual,PIZQ)){
                tokenActual = yylex();
                BO();
                if(equals(tokenActual,PDER)){
                    tokenActual = yylex();
                    S();
                    SP();
                } else{
                    error("Error de sintaxis");
                }
            }else{
                error("Error de sintaxis");
            }    
	        break;
	    case WHILE:
	        tokenActual = yylex();
            if(equals(tokenActual,PIZQ)){
                tokenActual = yylex();
           
                BO();
           
                if(equals(tokenActual,PDER)){
                    tokenActual = yylex();
              
                    S();
                } else{
                    error("Error de sintaxis");
                }
            }else{
                error("Error de sintaxis");
            }    
	        break;
        case DO:
	        tokenActual = yylex();
	        S();
            if(equals(tokenActual,WHILE)){
                tokenActual = yylex();
                if(equals(tokenActual,PIZQ)){
                    tokenActual = yylex();
                    BO();
                    if(equals(tokenActual,PDER)){
                        tokenActual = yylex();
                    } else{
                        error("Error de sintaxis");
                    }
                }else{
                    error("Error de sintaxis");
                }
            } else{
                error("Error de sintaxis");
            }    
	        break;
	    case BREAK:
	        tokenActual = yylex();
	        if(equals(tokenActual,PCOMA)){
	            tokenActual = yylex();
	        }else{
	            error("Error de sintaxis");
	        }
	        break;
	    case SWITCH:
	        tokenActual = yylex();
	        if(equals(tokenActual,PIZQ)){
                tokenActual = yylex();
                BO();
                if(equals(tokenActual,PDER)){
                    tokenActual = yylex();
                    if(equals(tokenActual,KIZQ)){
                        tokenActual = yylex();
                        CA();
                         if(equals(tokenActual,KDER)){
                            tokenActual = yylex();
                        } else{
                            error("Error de sintaxis");
                        }
                    } else{
                        error("Error de sintaxis");
                    }
                } else{
                    error("Error de sintaxis");
                }
            }else{
                error("Error de sintaxis");
            }    
	        break;
	    case KIZQ:
	        BL();
	        break;
	        
	    case ID:
	        LO();
            if(equals(tokenActual,ASSIG)){
                tokenActual= yylex();
                BO();
            } else{
                error("Error de sintaxis");
            }
        
	        break;
	    default:	    
	        error("Error de sintaxis");
    }        
    
}

void SP(){
    if(equals(tokenActual,ELSE)){
        tokenActual= yylex();
        S();
    }
}

void CA(){
    if(equals(tokenActual,CASE) || equals(tokenActual,DEFAULT)){
        CO();
        CA();
        PR();
    }
    
}

void CO(){
    if(equals(tokenActual,CASE)){
        tokenActual= yylex();
        if (equals(tokenActual,NUM)){
            tokenActual= yylex();
            if (equals(tokenActual, DOSP)){
                tokenActual= yylex();
                I();
            } else{
                error("Error de sintaxis");
            }
            
        } else {
            error("Error de sintaxis");
        }
    }else{
        error("Error de sintaxis");
    }
}

void PR(){
    if(equals(tokenActual,DEFAULT)){
        tokenActual= yylex();
        if (equals(tokenActual, DOSP)){
            tokenActual= yylex();
            I();
        } else{
            error("Error de sintaxis");
        }
    }else{
        error("Error de sintaxis");
    }
}

void CB(){
    IG();
    CBP();
}

void CBP(){
    if(equals(tokenActual, AND)){
        tokenActual= yylex();
        IG();
        CBP();
    }
}
void BO(){
    CB();
    BoP();
}

void BoP(){
    if(equals(tokenActual, OR)){
        tokenActual = yylex();
        CB();
        BoP();
    }
}

void IG(){
    R();
    IGPP();
}

void IGPP(){
    if(equals(tokenActual, EQ) || equals(tokenActual, NEQ)){
        IGP();
        IGPP();
    }
    
}

void IGP(){
    if(equals(tokenActual, EQ)){
        tokenActual = yylex();
        R();
    } 
    else if(equals(tokenActual, NEQ)){
        tokenActual= yylex();
        R();
    } 
    else{
        error("Error de sintaxis");
    }
}

void R(){
    E();
    RP();
}

void RP(){
    switch(tokenActual->clase){
	    case LESS:
	        tokenActual = yylex(); 
	        E();       
	        break;
	    case LEQ:
	        tokenActual = yylex();
	        E();
	        break;
	    case GEQ:
	        tokenActual = yylex();
	        E();
	        break;
        case GRE:
	        tokenActual = yylex();
	        E();
	        break;
    }
}


void E(){
    T();
    EPP();
}

void EPP(){
    if(equals(tokenActual, SUM) || equals(tokenActual, SUB)){
        EP();
        EPP();
    }
}

void EP(){
    if(equals(tokenActual, SUM)){
        tokenActual = yylex();
        E();
    } 
    
    else if(equals(tokenActual, SUB)){
        tokenActual= yylex();
        E();
    } 
    else{
        error("Error de sintaxis");
    }
}

void T(){
    U();
    TPP();
}

void TPP(){
    if(equals(tokenActual, MUL) || equals(tokenActual, SUB) || equals(tokenActual, RES)){
        TP();
        TPP();
    }
}

void TP(){
    switch(tokenActual->clase){
	    case MUL:
	        tokenActual = yylex(); 
	        U();       
	        break;
	    case SUB:
	        tokenActual = yylex();
	        U();
	        break;
	    case RES:
	        tokenActual = yylex();
	        U();
	        break;
	 }
}


void U(){

    if(equals(tokenActual, NEG)){
        tokenActual = yylex();
        U();    
    } else if(equals(tokenActual, SUB)){
        tokenActual = yylex();
        U();
    } else {
        FA();
    }
    
 
}



void FA(){
    switch (tokenActual->clase)
    {
	    case PIZQ:
            tokenActual= yylex();
            BO();
            if(equals(tokenActual,PDER)){
                tokenActual= yylex();
            }else{
                error("Error de sintaxis");
            }
            break;
        case NUM:
            tokenActual= yylex();
            break;
        case STRING:
            tokenActual = yylex();
            break;
        case TRUE:
            tokenActual = yylex();
            break;
        case FALSE:
            tokenActual = yylex();
            break;
        case ID:
            tokenActual = yylex();
            if(equals(tokenActual,PIZQ)){
                tokenActual == yylex();
                PA();
                if(equals(tokenActual,PDER)){
                    tokenActual=yylex(); 
                } else{
                    error("Error de sintaxis");
                }
            }
            else if(equals(tokenActual,CIZQ)){
                LOP();
            }
            else{
               
                error("Error de sintaxis");
            }
            break;
       
        default:
            error("Error de sintaxis");
            break;
    
    }    
}

void PA(){
    LP();
}

void LP(){
    if(equals(tokenActual, OR)){
        BO();
        LPP();
    }
    
}

void LPP(){
    if(equals(tokenActual,COMA)){
        tokenActual = yylex();
        BO();
        LPP();
    }
}

void LO(){
    if(equals(tokenActual,ID)){
        tokenActual= yylex();
        LOP();
    }else{
        error("Error de sintaxis");
    }
}

void LOP(){
    if(equals(tokenActual,CIZQ)){
        tokenActual= yylex();
        BO();
        if(equals(tokenActual,CDER)){
            tokenActual= yylex();
            LOP();
        }else{
            error("Error de sintaxis");
        }
    }
}
