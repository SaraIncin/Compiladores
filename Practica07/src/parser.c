#include "parser.h"
#include <stdio.h>
extern token *yylex();
extern int yylineno;


void parse() {
  P();
}



void error(char *msg) {
  printf("%s", msg);
  printf(": línea %i\n", yylineno);
  exit(1);
}


//AQUI EMPIEZA
void P(){
    D();
	F();
}

void D(){
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
	        error("Error de sintaxis1");
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
                error("Error de sintaxis2");
            }
        } else{
            error("Error de sintaxis3");
        }    
   }
   
}

void LV(){
    if(equals(tokenActual,ID)){
        tokenActual=yylex();
        LVP();
    }else{
        error("Error de sintaxis4");
    }
}

void LVP(){
    if(equals(tokenActual, COMA)){
        tokenActual = yylex();
        if(equals(tokenActual,ID)){
            tokenActual = yylex();
            LVP();
        }else{
            error("Error de sintaxis5");
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
                    error("Error de sintaxis6");
                }
                
            } else{
                error("Error de sintaxis7");
            }
        } else{
            error("Error de sintaxis8");
        }
    } 
}

void A(){
    LA();    
}

void LA(){
    T();
    if(equals(tokenActual,ID)){
        tokenActual = yylex();
        LAP();
    } else{
        error("Error de sintaxis9");
    }
}

void LAP(){
    if(equals(tokenActual,COMA)){
        tokenActual = yylex();
        T();
        if(equals(tokenActual,ID)){
            tokenActual = yylex();
            LAP();
        }else{
            error("Error de sintaxis10");
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
            error("Error de sintaxis11");
        }
    } else{
        error("Error de sintaxis12");
    }
}

void I(){
    S();
    IP();
}

void IP(){
    S();
    IP();
}



void S(){
    BL();
        
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
                    error("Error de sintaxis13");
                }
            }else{
                error("Error de sintaxis14");
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
                    error("Error de sintaxis15");
                }
            }else{
                error("Error de sintaxis16");
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
                        error("Error de sintaxis17");
                    }
                }else{
                    error("Error de sintaxis18");
                }
            } else{
                error("Error de sintaxis19");
            }    
	        break;
	    case BREAK:
	        tokenActual = yylex();
	        if(equals(tokenActual,PCOMA)){
	            tokenActual = yylex();
	        }else{
	            error("Error de sintaxis20");
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
                            error("Error de sintaxis21");
                        }
                    } else{
                        error("Error de sintaxis22");
                    }
                } else{
                    error("Error de sintaxis23");
                }
            }else{
                error("Error de sintaxis24");
            }    
	        break;
	    default:
	        LO();
            if(equals(tokenActual,ASSIG)){
                tokenActual= yylex();
                BO();
            } else{
                error("Error de sintaxis25");
            }
	        break;
    }        
    
}

void SP(){
    if(equals(tokenActual,ELSE)){
        tokenActual= yylex();
        S();
    }
}

void CA(){
    CO();
    CA();
    PR();
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
                error("Error de sintaxis26");
            }
            
        } else {
            error("Error de sintaxis27");
        }
    }else{
        error("Error de sintaxis28");
    }
}

void PR(){
    if(equals(tokenActual,DEFAULT)){
        tokenActual= yylex();
        if (equals(tokenActual, DOSP)){
            tokenActual= yylex();
            I();
        } else{
            error("Error de sintaxis29");
        }
    }else{
        error("Error de sintaxis30");
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
    IGP();
    IGPP();
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
        error("Error de sintaxis31");
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
    EP();
    EPP();
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
        error("Error de sintaxis32");
    }
}

void T(){
    U();
    TPP();
}

void TPP(){
    TP();
    TPP();
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
    FA();
    if(equals(tokenActual, NEG)){
        tokenActual = yylex();
        U();    
    } else if(equals(tokenActual, SUB)){
        tokenActual = yylex();
        U();
    } else{
        error("Error de sintaxis33");
    }
}



void FA(){
    LO();
    switch (tokenActual->clase)
    {
	    case PIZQ:
            tokenActual= yylex();
            BO();
            if(equals(tokenActual,PDER)){
                tokenActual= yylex();
            }else{
                error("Error de sintaxis34");
            }
            break;
        case NUM:
            tokenActual= yylex();
        case STRING:
            tokenActual = yylex();
        case TRUE:
            tokenActual = yylex();
        case FALSE:
            tokenActual = yylex();
        case ID:
            tokenActual = yylex();
            if(equals(tokenActual,PIZQ)){
                tokenActual == yylex();
                PA();
                if(equals(tokenActual,PDER)){
                    tokenActual=yylex(); 
                } else{
                    error("Error de sintaxis35");
                }
            }
            else{
                error("Error de sintaxis36");
            }
            break;
        default:
            error("Error de sintaxis37");
            break;
    
    }    
}

void PA(){
    LP();
}

void LP(){
    BO();
    LPP();
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
        error("Error de sintaxis38");
    }
}

void LOP(){
    if(equals(tokenActual,PIZQ)){
        tokenActual= yylex();
        BO();
        if(equals(tokenActual,PDER)){
            tokenActual= yylex();
            LOP();
        }else{
            error("Error de sintaxis39");
        }
    }
}
