%{
/************************************************
* ANJANA SINGH
* Y8127079
* DEPARTMENT OF COMPUTER SCIENCE AND ENGINNERING
* IIT KANPUR
*
* C LEXICAL ANALYSIS
* LEXEMES ARE ONLY FOR RELEVENT
* WORKING
************************************************/

#include <stdlib.h>
#include <stdio.h>
void yyerror(char *);
#include "y.tab.h"
#include<string.h>
#include<math.h>
int count_bracket;
extern int yylex();
%}


D			[0-9]
L			[a-zA-Z_]
H			[a-fA-F0-9]
E			[Ee][+-]?{D}+
FS			(f|F|l|L)
IS			(u|U|l|L)*
singlelinecomment 		("//")(.)*

space       [ \t\v\f]*

%x CMNT
%s DEF
%s DEF_CMNT
%s LOOP_CMNT
%s LOOP
%%

"// PARALLELIZE IN CUDA START"	{BEGIN(LOOP); start_num = line_num; printf("PARALLEL_START "); return(PARALLEL_START);}

<CMNT>{
"*/"			{BEGIN(INITIAL);}
"\n"			{line_num++;}
.				; 
}

<DEF_CMNT>{
"*/"			{BEGIN(DEF);}
"\n"			{line_num++;}
.				; 
}

<LOOP_CMNT>{
"*/"			{BEGIN(LOOP);}
"\n"			{line_num++;}
.				; 
}




"char"			{ count_bracket=0; BEGIN(DEF); printf("TYPE "); return(CHAR); }
"const"			{ count_bracket=0; BEGIN(DEF); printf("TYPE "); return(CONST); }
"double"		{ count_bracket=0; BEGIN(DEF); printf("TYPE "); return(DOUBLE); }
"float"			{ count_bracket=0; BEGIN(DEF); printf("TYPE "); return(FLOAT); }
"int"			{ count_bracket=0; BEGIN(DEF); printf("TYPE "); return(INT); }
"long"			{ count_bracket=0; BEGIN(DEF); printf("TYPE "); return(LONG); }
"short"			{ count_bracket=0; BEGIN(DEF); printf("TYPE "); return(SHORT); }
"signed"		{ count_bracket=0; BEGIN(DEF); printf("TYPE "); return(SIGNED); }
"static"		{ count_bracket=0; BEGIN(DEF); printf("TYPE "); return(STATIC); }
"unsigned"		{ count_bracket=0; BEGIN(DEF); printf("TYPE "); return(UNSIGNED); }
"void"			{ count_bracket=0; BEGIN(DEF); printf("TYPE "); return(VOID); }
"volatile"		{ count_bracket=0; BEGIN(DEF); printf("TYPE "); return(VOLATILE); }



<DEF>{

"/*"   		{BEGIN(DEF_CMNT);}
{singlelinecomment}		{printf("comment\n");}


{L}({L}|{D})*		{	struct StringNode* s = malloc(sizeof(struct StringNode));
						int len = strlen(yytext);
						s->string = malloc(sizeof(char)*(len+1));
						memcpy(s->string,yytext,sizeof(char)*(len+1));
						s->next = NULL;
						s->size = NULL;
						yylval.stringNode = s;
						printf("IDENTIFIER "); 
						return(IDENTIFIER);
					}

0[xX]{H}+{IS}?		{   struct StringNode* s = malloc(sizeof(struct StringNode));
						int len = strlen(yytext);
						s->string = malloc(sizeof(char)*(len+1));
						memcpy(s->string,yytext,sizeof(char)*(len+1));
						s->next = NULL;
						s->size = NULL;
						yylval.stringNode = s;
						printf("CONSTANT "); 
						return(CONSTANT); 
					}

0{D}+{IS}?		    {   struct StringNode* s = malloc(sizeof(struct StringNode));
						int len = strlen(yytext);
						s->string = malloc(sizeof(char)*(len+1));
						memcpy(s->string,yytext,sizeof(char)*(len+1));
						s->next = NULL;
						s->size = NULL;
						yylval.stringNode = s;
						printf("CONSTANT ");
                        return(CONSTANT); 
                	}
{D}+{IS}?			{ 		struct StringNode* s = malloc(sizeof(struct StringNode));
						int len = strlen(yytext);
						s->string = malloc(sizeof(char)*(len+1));
						memcpy(s->string,yytext,sizeof(char)*(len+1));
						s->next = NULL;
						s->size = NULL;
						yylval.stringNode = s;
						printf("CONSTANT ");
                        return(CONSTANT); 
                    }
L?'(\\.|[^\\'])+'	{   struct StringNode* s = malloc(sizeof(struct StringNode));
						int len = strlen(yytext);
						s->string = malloc(sizeof(char)*(len+1));
						memcpy(s->string,yytext,sizeof(char)*(len+1));
						s->next = NULL;
						s->size = NULL;
						yylval.stringNode = s;
						printf("CONSTANT ");
                        return(CONSTANT); 
                    }

{D}+{E}{FS}?		{	struct StringNode* s = malloc(sizeof(struct StringNode));
						int len = strlen(yytext);
						s->string = malloc(sizeof(char)*(len+1));
						memcpy(s->string,yytext,sizeof(char)*(len+1));
						s->next = NULL;
						s->size = NULL;
						yylval.stringNode = s;
						printf("CONSTANT ");
                        return(CONSTANT); 
                    }
{D}*"."{D}+({E})?{FS}?	{	struct StringNode* s = malloc(sizeof(struct StringNode));
						int len = strlen(yytext);
						s->string = malloc(sizeof(char)*(len+1));
						memcpy(s->string,yytext,sizeof(char)*(len+1));
						s->next = NULL;
						s->size = NULL;
						yylval.stringNode = s;
						printf("CONSTANT ");
                        return(CONSTANT); 
                        }
{D}+"."{D}*({E})?{FS}?	{ 	struct StringNode* s = malloc(sizeof(struct StringNode));
						int len = strlen(yytext);
						s->string = malloc(sizeof(char)*(len+1));
						memcpy(s->string,yytext,sizeof(char)*(len+1));
						s->next = NULL;
						s->size = NULL;
						yylval.stringNode = s;
						printf("CONSTANT ");
                        return(CONSTANT); 
                        }



("["|"<:")		{count_bracket++; printf("[ "); return('['); }
("]"|":>")		{count_bracket--; printf("] "); return(']'); }
"&"			{ return('&'); }
"!"			{ return('!'); }
"~"			{ return('~'); }
"-"			{ return('-'); }
"+"			{ printf("+ "); return('+'); }
"*"			{ printf("* "); return('*'); }
"/"			{ return('/'); }
"%"			{ return('%'); }
"<"			{ return('<'); }
">"			{ return('>'); }
"^"			{ return('^'); }
"|"			{ return('|'); }
";"             { BEGIN(INITIAL); printf("; "); return(';'); }
"="             {printf("= "); return('=');}
","             {printf(", "); return(',');}
"{"             {if(count_bracket==0) {BEGIN(INITIAL); printf("; "); return(';');} else { printf("{ "); return('{');}}
"}"             {if(count_bracket==0) {BEGIN(INITIAL); printf("; "); return(';');} else { printf("} "); return('}');}}
")"             {printf(") "); return(')');}
"("             {printf("( "); return('(');}

[ \t\v\f]		{ }
\n			{ printf("%d\n",line_num); line_num++;}
. 			{if(count_bracket==0) {BEGIN(INITIAL); printf("; "); return(';');}}

}


<LOOP>{

"/*"   		{BEGIN(LOOP_CMNT);}

"for"			{ printf("FOR "); return(FOR); }

"("{space}"char"{space}")"			{	struct StringNode* s = malloc(sizeof(struct StringNode));
										int len = strlen(yytext);
										s->string = malloc(sizeof(char)*(len+1));
										memcpy(s->string,yytext,sizeof(char)*(len+1));
										s->next = NULL;
										s->size = NULL;
										yylval.stringNode = s;
										printf("TYPE_OP "); 
										return(TYPE_OP);
									}

"("{space}"int"{space}")"			{	struct StringNode* s = malloc(sizeof(struct StringNode));
										int len = strlen(yytext);
										s->string = malloc(sizeof(char)*(len+1));
										memcpy(s->string,yytext,sizeof(char)*(len+1));
										s->next = NULL;
										s->size = NULL;
										yylval.stringNode = s;
										printf("TYPE_OP "); 
										return(TYPE_OP);
									}
"("{space}"float"{space}")"			{	struct StringNode* s = malloc(sizeof(struct StringNode));
										int len = strlen(yytext);
										s->string = malloc(sizeof(char)*(len+1));
										memcpy(s->string,yytext,sizeof(char)*(len+1));
										s->next = NULL;
										s->size = NULL;
										yylval.stringNode = s;
										printf("TYPE_OP "); 
										return(TYPE_OP);
									}
"("{space}"double"{space}")"			{	struct StringNode* s = malloc(sizeof(struct StringNode));
										int len = strlen(yytext);
										s->string = malloc(sizeof(char)*(len+1));
										memcpy(s->string,yytext,sizeof(char)*(len+1));
										s->next = NULL;
										s->size = NULL;
										yylval.stringNode = s;
										printf("TYPE_OP "); 
										return(TYPE_OP);
									}
"("{space}"void"{space}")"			{	struct StringNode* s = malloc(sizeof(struct StringNode));
										int len = strlen(yytext);
										s->string = malloc(sizeof(char)*(len+1));
										memcpy(s->string,yytext,sizeof(char)*(len+1));
										s->next = NULL;
										s->size = NULL;
										yylval.stringNode = s;
										printf("TYPE_OP "); 
										return(TYPE_OP);
									}

{L}({L}|{D})*		{	struct StringNode* s = malloc(sizeof(struct StringNode));
						int len = strlen(yytext);
						s->string = malloc(sizeof(char)*(len+1));
						memcpy(s->string,yytext,sizeof(char)*(len+1));
						s->next = NULL;
						s->size = NULL;
						yylval.stringNode = s;
						printf("IDENTIFIER "); 
						return(IDENTIFIER);
					}

0[xX]{H}+{IS}?		{   struct StringNode* s = malloc(sizeof(struct StringNode));
						int len = strlen(yytext);
						s->string = malloc(sizeof(char)*(len+1));
						memcpy(s->string,yytext,sizeof(char)*(len+1));
						s->next = NULL;
						s->size = NULL;
						yylval.stringNode = s;
						printf("CONSTANT ");
						return(CONSTANT); 
					}
0{D}+{IS}?		    {   struct StringNode* s = malloc(sizeof(struct StringNode));
						int len = strlen(yytext);
						s->string = malloc(sizeof(char)*(len+1));
						memcpy(s->string,yytext,sizeof(char)*(len+1));
						s->next = NULL;
						s->size = NULL;
						yylval.stringNode = s;
                        printf("CONSTANT ");
						return(CONSTANT); 
                	}
{D}+{IS}?			{ 		struct StringNode* s = malloc(sizeof(struct StringNode));
						int len = strlen(yytext);
						s->string = malloc(sizeof(char)*(len+1));
						memcpy(s->string,yytext,sizeof(char)*(len+1));
						s->next = NULL;
						s->size = NULL;
						yylval.stringNode = s;
                        printf("CONSTANT ");
						return(CONSTANT); 
                    }
L?'(\\.|[^\\'])+'	{   struct StringNode* s = malloc(sizeof(struct StringNode));
						int len = strlen(yytext);
						s->string = malloc(sizeof(char)*(len+1));
						memcpy(s->string,yytext,sizeof(char)*(len+1));
						s->next = NULL;
						s->size = NULL;
						yylval.stringNode = s;
                        printf("CONSTANT ");
						return(CONSTANT); 
                    }

{D}+{E}{FS}?		{	struct StringNode* s = malloc(sizeof(struct StringNode));
						int len = strlen(yytext);
						s->string = malloc(sizeof(char)*(len+1));
						memcpy(s->string,yytext,sizeof(char)*(len+1));
						s->next = NULL;
						s->size = NULL;
						yylval.stringNode = s;
                        printf("CONSTANT ");
						return(CONSTANT); 
                    }
{D}*"."{D}+({E})?{FS}?	{	struct StringNode* s = malloc(sizeof(struct StringNode));
						int len = strlen(yytext);
						s->string = malloc(sizeof(char)*(len+1));
						memcpy(s->string,yytext,sizeof(char)*(len+1));
						s->next = NULL;
						s->size = NULL;
						yylval.stringNode = s;
                        printf("CONSTANT ");
						return(CONSTANT); 
                        }
{D}+"."{D}*({E})?{FS}?	{ 	struct StringNode* s = malloc(sizeof(struct StringNode));
						int len = strlen(yytext);
						s->string = malloc(sizeof(char)*(len+1));
						memcpy(s->string,yytext,sizeof(char)*(len+1));
						s->next = NULL;
						s->size = NULL;
						yylval.stringNode = s;
                        printf("CONSTANT ");
						return(CONSTANT); 
                        }

L?\"(\\.|[^\\"])*\"	{ printf("STRING ");
						return(STRING_LITERAL); }

">>="			{		return(RIGHT_ASSIGN); }
"<<="			{ 		return(LEFT_ASSIGN); }
"+="			{ 		return(ADD_ASSIGN); }
"-="			{ 		return(SUB_ASSIGN); }
"*="			{ 		return(MUL_ASSIGN); }
"/="			{ 		return(DIV_ASSIGN); }
"%="			{ 		return(MOD_ASSIGN); }
"&="			{ 		return(AND_ASSIGN); }
"^="			{ 		return(XOR_ASSIGN); }
"|="			{ 		return(OR_ASSIGN); }
">>"			{ 		return(RIGHT_OP); }
"<<"			{ 		return(LEFT_OP); }
"++"			{ 		return(INC_OP); }
"--"			{ 		return(DEC_OP); }
"->"			{ 		return(PTR_OP); }
"&&"			{ 		return(AND_OP); }
"||"			{ 		return(OR_OP); }
"<="			{ 		return(LE_OP); }
">="			{ 		return(GE_OP); }
"=="			{ 		return(EQ_OP); }
"!="			{ 		return(NE_OP); }
";"			{ return(';'); }
("{"|"<%")		{ return('{'); }
("}"|"%>")		{ return('}'); }
","			{ return(','); }
":"			{ return(':'); }
"="			{ return('='); }
"("			{ return('('); }
")"			{ return(')'); }
("["|"<:")		{ return('['); }
("]"|":>")		{ return(']'); }
"."			{ return('.'); }
"&"			{ return('&'); }
"!"			{ return('!'); }
"~"			{ return('~'); }
"-"			{ return('-'); }
"+"			{ return('+'); }
"*"			{ printf("* "); return('*'); }
"/"			{ return('/'); }
"%"			{ return('%'); }
"<"			{ return('<'); }
">"			{ return('>'); }
"^"			{ return('^'); }
"|"			{ return('|'); }
"?"			{ return('?'); }


"// PARALLELIZE IN CUDA END"       {BEGIN(INITIAL); end_num = line_num+1; printf("PARALLEL_END "); return(PARALLEL_END);}

{singlelinecomment}		{printf("comment\n");}

[ \t\v\f]		{ }
\n			{ printf("%d\n",line_num); line_num++;}
.			{ /* print error message */  }
}

"/*"   		{BEGIN(CMNT);}
{singlelinecomment}		{printf("comment\n");}

"("{space}"double"{space}")"			{}
"("{space}"float"{space}")"			{}
"("{space}"int"{space}")"			{}

{L}({L}|{D})*		{}

\n			{ printf("%d\n",line_num); line_num++;}
.			{ /* print error message */  }

%%

yywrap()
{
	return(1);
}
