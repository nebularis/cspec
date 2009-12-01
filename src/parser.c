/* A recursive-descent parser generated by peg 0.1.2 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define YYRULECOUNT 16

  #include "cspec.h"

  #define YYSTYPE char *
  
  #define LPAREN '{'
  #define RPAREN '}'

  #define DUP \
    yy = strdup(yytext)
  
  #define NODE(T) \
    current = nodeType##T, buf2 = NULL;
    
  #define NODE2(T, S) \
    current = nodeType##T, buf2 = S;
  
  #define END \
    printf("\n%c\n", RPAREN);  
  
  #define DEFER(S, ...) \
    sprintf(buf, S "\n", __VA_ARGS__); strcat(defer, buf);
  
  #define YY_INPUT(buf, result, max_size) { \
      int yyc = getc(stdin); \
      result = (EOF == yyc) ? 0 : (*(buf) = yyc, 1); \
      yyprintf((stderr, "<%c>", yyc)); \
    }
    
  #define SUITE(S) \
    parent_suite = nsuites - 1; current_suite = nsuites; \
    DEFER("Suite *suite_%d = Suite_new(%s);\n", nsuites++, S); \
    if (parent_suite > -1) { \
      DEFER("Suite_push_suite(suite_%d, suite_%d);\n", parent_suite, current_suite) \
    } else { \
      DEFER("%c", ' ') \
    }
    
  #define SPEC(S) BLOCK("Spec", S);
        
  #define BLOCK(S, D) \
    DEFER("Block *block_%d = Block_new(blockType%s, %s, &block_%d_callback);\n", nblocks, S, D == NULL ? "NULL" : D, nblocks); \
    DEFER("Suite_push_block(suite_%d, block_%d);\n", nsuites-1, nblocks); \
    nblocks++;
    
  #define BLOCK_CALLBACK \
    printf("void block_%d_callback() %c\n", nblocks, LPAREN);
    
  #define ASSERTION(V, M, C, N) \
    printf(N ? "expect(!(match_%s(%s, %s)));\n" : \
               "expect((match_%s(%s, %s)));\n", M, V, C);
    
  #define OUT \
    switch (current) { \
      case nodeTypeBefore    : END; BLOCK("Before",     buf2); break; \
      case nodeTypeBeforeEach: END; BLOCK("BeforeEach", buf2); break; \
      case nodeTypeAfter     : END; BLOCK("After",      buf2); break; \
      case nodeTypeAfterEach : END; BLOCK("AfterEach",  buf2); break; \
      case nodeTypeSpec      : END; SPEC(buf2);                break; \
    } \
    current = nodeTypeNone;
  
  typedef enum {
    nodeTypeNone,
    nodeTypeBeforeEach,
    nodeTypeAfterEach,
    nodeTypeBefore,
    nodeTypeAfter,
    nodeTypeSpec
  } nodeType;
  
  static int nsuites = 0;
  static int nblocks = 0;
  static int parent_suite = 0;
  static int current_suite = 0;
  static nodeType current = nodeTypeNone;
  static char buf[CSPEC_BUFFER_SIZE];
  static char defer[CSPEC_BUFFER_SIZE];
  static char *buf2;

#ifndef YY_VARIABLE
#define YY_VARIABLE(T)	static T
#endif
#ifndef YY_LOCAL
#define YY_LOCAL(T)	static T
#endif
#ifndef YY_ACTION
#define YY_ACTION(T)	static T
#endif
#ifndef YY_RULE
#define YY_RULE(T)	static T
#endif
#ifndef YY_PARSE
#define YY_PARSE(T)	T
#endif
#ifndef YYPARSE
#define YYPARSE		yyparse
#endif
#ifndef YYPARSEFROM
#define YYPARSEFROM	yyparsefrom
#endif
#ifndef YY_INPUT
#define YY_INPUT(buf, result, max_size)			\
  {							\
    int yyc= getchar();					\
    result= (EOF == yyc) ? 0 : (*(buf)= yyc, 1);	\
    yyprintf((stderr, "<%c>", yyc));			\
  }
#endif
#ifndef YY_BEGIN
#define YY_BEGIN	( yybegin= yypos, 1)
#endif
#ifndef YY_END
#define YY_END		( yyend= yypos, 1)
#endif
#ifdef YY_DEBUG
# define yyprintf(args)	fprintf args
#else
# define yyprintf(args)
#endif
#ifndef YYSTYPE
#define YYSTYPE	int
#endif

#ifndef YY_PART

typedef void (*yyaction)(char *yytext, int yyleng);
typedef struct _yythunk { int begin, end;  yyaction  action;  struct _yythunk *next; } yythunk;

YY_VARIABLE(char *   ) yybuf= 0;
YY_VARIABLE(int	     ) yybuflen= 0;
YY_VARIABLE(int	     ) yypos= 0;
YY_VARIABLE(int	     ) yylimit= 0;
YY_VARIABLE(char *   ) yytext= 0;
YY_VARIABLE(int	     ) yytextlen= 0;
YY_VARIABLE(int	     ) yybegin= 0;
YY_VARIABLE(int	     ) yyend= 0;
YY_VARIABLE(int	     ) yytextmax= 0;
YY_VARIABLE(yythunk *) yythunks= 0;
YY_VARIABLE(int	     ) yythunkslen= 0;
YY_VARIABLE(int      ) yythunkpos= 0;
YY_VARIABLE(YYSTYPE  ) yy;
YY_VARIABLE(YYSTYPE *) yyval= 0;
YY_VARIABLE(YYSTYPE *) yyvals= 0;
YY_VARIABLE(int      ) yyvalslen= 0;

YY_LOCAL(int) yyrefill(void)
{
  int yyn;
  while (yybuflen - yypos < 512)
    {
      yybuflen *= 2;
      yybuf= realloc(yybuf, yybuflen);
    }
  YY_INPUT((yybuf + yypos), yyn, (yybuflen - yypos));
  if (!yyn) return 0;
  yylimit += yyn;
  return 1;
}

YY_LOCAL(int) yymatchDot(void)
{
  if (yypos >= yylimit && !yyrefill()) return 0;
  ++yypos;
  return 1;
}

YY_LOCAL(int) yymatchChar(int c)
{
  if (yypos >= yylimit && !yyrefill()) return 0;
  if (yybuf[yypos] == c)
    {
      ++yypos;
      yyprintf((stderr, "  ok   yymatchChar(%c) @ %s\n", c, yybuf+yypos));
      return 1;
    }
  yyprintf((stderr, "  fail yymatchChar(%c) @ %s\n", c, yybuf+yypos));
  return 0;
}

YY_LOCAL(int) yymatchString(char *s)
{
  int yysav= yypos;
  while (*s)
    {
      if (yypos >= yylimit && !yyrefill()) return 0;
      if (yybuf[yypos] != *s)
        {
          yypos= yysav;
          return 0;
        }
      ++s;
      ++yypos;
    }
  return 1;
}

YY_LOCAL(int) yymatchClass(unsigned char *bits)
{
  int c;
  if (yypos >= yylimit && !yyrefill()) return 0;
  c= yybuf[yypos];
  if (bits[c >> 3] & (1 << (c & 7)))
    {
      ++yypos;
      yyprintf((stderr, "  ok   yymatchClass @ %s\n", yybuf+yypos));
      return 1;
    }
  yyprintf((stderr, "  fail yymatchClass @ %s\n", yybuf+yypos));
  return 0;
}

YY_LOCAL(void) yyDo(yyaction action, int begin, int end)
{
  while (yythunkpos >= yythunkslen)
    {
      yythunkslen *= 2;
      yythunks= realloc(yythunks, sizeof(yythunk) * yythunkslen);
    }
  yythunks[yythunkpos].begin=  begin;
  yythunks[yythunkpos].end=    end;
  yythunks[yythunkpos].action= action;
  ++yythunkpos;
}

YY_LOCAL(int) yyText(int begin, int end)
{
  int yyleng= end - begin;
  if (yyleng <= 0)
    yyleng= 0;
  else
    {
      while (yytextlen < (yyleng - 1))
	{
	  yytextlen *= 2;
	  yytext= realloc(yytext, yytextlen);
	}
      memcpy(yytext, yybuf + begin, yyleng);
    }
  yytext[yyleng]= '\0';
  return yyleng;
}

YY_LOCAL(void) yyDone(void)
{
  int pos;
  for (pos= 0;  pos < yythunkpos;  ++pos)
    {
      yythunk *thunk= &yythunks[pos];
      int yyleng= thunk->end ? yyText(thunk->begin, thunk->end) : thunk->begin;
      yyprintf((stderr, "DO [%d] %p %s\n", pos, thunk->action, yytext));
      thunk->action(yytext, yyleng);
    }
  yythunkpos= 0;
}

YY_LOCAL(void) yyCommit()
{
  if ((yylimit -= yypos))
    {
      memmove(yybuf, yybuf + yypos, yylimit);
    }
  yybegin -= yypos;
  yyend -= yypos;
  yypos= yythunkpos= 0;
}

YY_LOCAL(int) yyAccept(int tp0)
{
  if (tp0)
    {
      fprintf(stderr, "accept denied at %d\n", tp0);
      return 0;
    }
  else
    {
      yyDone();
      yyCommit();
    }
  return 1;
}

YY_LOCAL(void) yyPush(char *text, int count)	{ yyval += count; }
YY_LOCAL(void) yyPop(char *text, int count)	{ yyval -= count; }
YY_LOCAL(void) yySet(char *text, int count)	{ yyval[count]= yy; }

#endif /* YY_PART */

#define	YYACCEPT	yyAccept(yythunkpos0)

YY_RULE(int) yy__(); /* 16 */
YY_RULE(int) yy_EOF(); /* 15 */
YY_RULE(int) yy_nl(); /* 14 */
YY_RULE(int) yy_EOL(); /* 13 */
YY_RULE(int) yy_consume(); /* 12 */
YY_RULE(int) yy_ws(); /* 11 */
YY_RULE(int) yy_string(); /* 10 */
YY_RULE(int) yy_s(); /* 9 */
YY_RULE(int) yy_id(); /* 8 */
YY_RULE(int) yy_expr(); /* 7 */
YY_RULE(int) yy_assertion(); /* 6 */
YY_RULE(int) yy_end(); /* 5 */
YY_RULE(int) yy_block(); /* 4 */
YY_RULE(int) yy_spec(); /* 3 */
YY_RULE(int) yy_suite(); /* 2 */
YY_RULE(int) yy_main(); /* 1 */

YY_ACTION(void) yy_1_id(char *yytext, int yyleng)
{
  yyprintf((stderr, "do yy_1_id\n"));
   DUP ;
}
YY_ACTION(void) yy_1_consume(char *yytext, int yyleng)
{
  yyprintf((stderr, "do yy_1_consume\n"));
   DUP ;
}
YY_ACTION(void) yy_1_string(char *yytext, int yyleng)
{
  yyprintf((stderr, "do yy_1_string\n"));
   DUP ;
}
YY_ACTION(void) yy_2_assertion(char *yytext, int yyleng)
{
#define c yyval[-1]
#define b yyval[-2]
#define a yyval[-3]
  yyprintf((stderr, "do yy_2_assertion\n"));
   ASSERTION(a, b, c, 0) ;
#undef c
#undef b
#undef a
}
YY_ACTION(void) yy_1_assertion(char *yytext, int yyleng)
{
#define c yyval[-1]
#define b yyval[-2]
#define a yyval[-3]
  yyprintf((stderr, "do yy_1_assertion\n"));
   ASSERTION(a, b, c, 1) ;
#undef c
#undef b
#undef a
}
YY_ACTION(void) yy_5_block(char *yytext, int yyleng)
{
  yyprintf((stderr, "do yy_5_block\n"));
   BLOCK_CALLBACK ;
}
YY_ACTION(void) yy_4_block(char *yytext, int yyleng)
{
  yyprintf((stderr, "do yy_4_block\n"));
   NODE(After) ;
}
YY_ACTION(void) yy_3_block(char *yytext, int yyleng)
{
  yyprintf((stderr, "do yy_3_block\n"));
   NODE(AfterEach) ;
}
YY_ACTION(void) yy_2_block(char *yytext, int yyleng)
{
  yyprintf((stderr, "do yy_2_block\n"));
   NODE(Before) ;
}
YY_ACTION(void) yy_1_block(char *yytext, int yyleng)
{
  yyprintf((stderr, "do yy_1_block\n"));
   NODE(BeforeEach) ;
}
YY_ACTION(void) yy_1_spec(char *yytext, int yyleng)
{
#define a yyval[-1]
  yyprintf((stderr, "do yy_1_spec\n"));
   NODE2(Spec, a); BLOCK_CALLBACK ;
#undef a
}
YY_ACTION(void) yy_1_suite(char *yytext, int yyleng)
{
#define a yyval[-1]
  yyprintf((stderr, "do yy_1_suite\n"));
   SUITE(a) ;
#undef a
}
YY_ACTION(void) yy_5_expr(char *yytext, int yyleng)
{
  yyprintf((stderr, "do yy_5_expr\n"));
   DUP ;
}
YY_ACTION(void) yy_4_expr(char *yytext, int yyleng)
{
  yyprintf((stderr, "do yy_4_expr\n"));
   DUP ;
}
YY_ACTION(void) yy_3_expr(char *yytext, int yyleng)
{
  yyprintf((stderr, "do yy_3_expr\n"));
   DUP ;
}
YY_ACTION(void) yy_2_expr(char *yytext, int yyleng)
{
  yyprintf((stderr, "do yy_2_expr\n"));
   DUP ;
}
YY_ACTION(void) yy_1_expr(char *yytext, int yyleng)
{
  yyprintf((stderr, "do yy_1_expr\n"));
   DUP ;
}
YY_ACTION(void) yy_3_main(char *yytext, int yyleng)
{
  yyprintf((stderr, "do yy_3_main\n"));
   printf("%s", yytext) ;
}
YY_ACTION(void) yy_2_main(char *yytext, int yyleng)
{
  yyprintf((stderr, "do yy_2_main\n"));
   OUT ;
}
YY_ACTION(void) yy_1_main(char *yytext, int yyleng)
{
  yyprintf((stderr, "do yy_1_main\n"));
   puts(yytext) ;
}

YY_RULE(int) yy__()
{
  yyprintf((stderr, "%s\n", "_"));
  l2:;	
  {  int yypos3= yypos, yythunkpos3= yythunkpos;  if (!yymatchClass((unsigned char *)"\000\002\000\000\001\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000")) goto l3;  goto l2;
  l3:;	  yypos= yypos3; yythunkpos= yythunkpos3;
  }
  yyprintf((stderr, "  ok   %s @ %s\n", "_", yybuf+yypos));
  return 1;
}
YY_RULE(int) yy_EOF()
{  int yypos0= yypos, yythunkpos0= yythunkpos;
  yyprintf((stderr, "%s\n", "EOF"));
  {  int yypos5= yypos, yythunkpos5= yythunkpos;  if (!yymatchDot()) goto l5;  goto l4;
  l5:;	  yypos= yypos5; yythunkpos= yythunkpos5;
  }
  yyprintf((stderr, "  ok   %s @ %s\n", "EOF", yybuf+yypos));
  return 1;
  l4:;	  yypos= yypos0; yythunkpos= yythunkpos0;
  yyprintf((stderr, "  fail %s @ %s\n", "EOF", yybuf+yypos));
  return 0;
}
YY_RULE(int) yy_nl()
{  int yypos0= yypos, yythunkpos0= yythunkpos;
  yyprintf((stderr, "%s\n", "nl"));
  {  int yypos7= yypos, yythunkpos7= yythunkpos;  if (!yymatchString("\r\n")) goto l8;  goto l7;
  l8:;	  yypos= yypos7; yythunkpos= yythunkpos7;  if (!yymatchChar('\r')) goto l9;  goto l7;
  l9:;	  yypos= yypos7; yythunkpos= yythunkpos7;  if (!yymatchChar('\n')) goto l6;
  }
  l7:;	
  yyprintf((stderr, "  ok   %s @ %s\n", "nl", yybuf+yypos));
  return 1;
  l6:;	  yypos= yypos0; yythunkpos= yythunkpos0;
  yyprintf((stderr, "  fail %s @ %s\n", "nl", yybuf+yypos));
  return 0;
}
YY_RULE(int) yy_EOL()
{  int yypos0= yypos, yythunkpos0= yythunkpos;
  yyprintf((stderr, "%s\n", "EOL"));
  {  int yypos11= yypos, yythunkpos11= yythunkpos;  if (!yy_nl()) goto l12;  goto l11;
  l12:;	  yypos= yypos11; yythunkpos= yythunkpos11;  if (!yy_EOF()) goto l10;
  }
  l11:;	
  yyprintf((stderr, "  ok   %s @ %s\n", "EOL", yybuf+yypos));
  return 1;
  l10:;	  yypos= yypos0; yythunkpos= yythunkpos0;
  yyprintf((stderr, "  fail %s @ %s\n", "EOL", yybuf+yypos));
  return 0;
}
YY_RULE(int) yy_consume()
{  int yypos0= yypos, yythunkpos0= yythunkpos;
  yyprintf((stderr, "%s\n", "consume"));  yyText(yybegin, yyend);  if (!(YY_BEGIN)) goto l13;
  {  int yypos16= yypos, yythunkpos16= yythunkpos;
  {  int yypos17= yypos, yythunkpos17= yythunkpos;  if (!yy_EOL()) goto l18;  goto l17;
  l18:;	  yypos= yypos17; yythunkpos= yythunkpos17;  if (!yymatchChar(';')) goto l16;
  }
  l17:;	  goto l13;
  l16:;	  yypos= yypos16; yythunkpos= yythunkpos16;
  }  if (!yymatchDot()) goto l13;
  l14:;	
  {  int yypos15= yypos, yythunkpos15= yythunkpos;
  {  int yypos19= yypos, yythunkpos19= yythunkpos;
  {  int yypos20= yypos, yythunkpos20= yythunkpos;  if (!yy_EOL()) goto l21;  goto l20;
  l21:;	  yypos= yypos20; yythunkpos= yythunkpos20;  if (!yymatchChar(';')) goto l19;
  }
  l20:;	  goto l15;
  l19:;	  yypos= yypos19; yythunkpos= yythunkpos19;
  }  if (!yymatchDot()) goto l15;  goto l14;
  l15:;	  yypos= yypos15; yythunkpos= yythunkpos15;
  }  yyText(yybegin, yyend);  if (!(YY_END)) goto l13;  yyDo(yy_1_consume, yybegin, yyend);
  yyprintf((stderr, "  ok   %s @ %s\n", "consume", yybuf+yypos));
  return 1;
  l13:;	  yypos= yypos0; yythunkpos= yythunkpos0;
  yyprintf((stderr, "  fail %s @ %s\n", "consume", yybuf+yypos));
  return 0;
}
YY_RULE(int) yy_ws()
{  int yypos0= yypos, yythunkpos0= yythunkpos;
  yyprintf((stderr, "%s\n", "ws"));
  {  int yypos23= yypos, yythunkpos23= yythunkpos;  if (!yymatchChar(' ')) goto l24;  goto l23;
  l24:;	  yypos= yypos23; yythunkpos= yythunkpos23;  if (!yymatchChar('\t')) goto l25;  goto l23;
  l25:;	  yypos= yypos23; yythunkpos= yythunkpos23;  if (!yy_nl()) goto l22;
  }
  l23:;	
  yyprintf((stderr, "  ok   %s @ %s\n", "ws", yybuf+yypos));
  return 1;
  l22:;	  yypos= yypos0; yythunkpos= yythunkpos0;
  yyprintf((stderr, "  fail %s @ %s\n", "ws", yybuf+yypos));
  return 0;
}
YY_RULE(int) yy_string()
{  int yypos0= yypos, yythunkpos0= yythunkpos;
  yyprintf((stderr, "%s\n", "string"));  yyText(yybegin, yyend);  if (!(YY_BEGIN)) goto l26;  if (!yymatchChar('"')) goto l26;
  l27:;	
  {  int yypos28= yypos, yythunkpos28= yythunkpos;
  {  int yypos29= yypos, yythunkpos29= yythunkpos;  if (!yymatchChar('"')) goto l29;  goto l28;
  l29:;	  yypos= yypos29; yythunkpos= yythunkpos29;
  }  if (!yymatchDot()) goto l28;  goto l27;
  l28:;	  yypos= yypos28; yythunkpos= yythunkpos28;
  }  if (!yymatchChar('"')) goto l26;  yyText(yybegin, yyend);  if (!(YY_END)) goto l26;  yyDo(yy_1_string, yybegin, yyend);
  yyprintf((stderr, "  ok   %s @ %s\n", "string", yybuf+yypos));
  return 1;
  l26:;	  yypos= yypos0; yythunkpos= yythunkpos0;
  yyprintf((stderr, "  fail %s @ %s\n", "string", yybuf+yypos));
  return 0;
}
YY_RULE(int) yy_s()
{  int yypos0= yypos, yythunkpos0= yythunkpos;
  yyprintf((stderr, "%s\n", "s"));  if (!yymatchClass((unsigned char *)"\000\002\000\000\001\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000")) goto l30;
  l31:;	
  {  int yypos32= yypos, yythunkpos32= yythunkpos;  if (!yymatchClass((unsigned char *)"\000\002\000\000\001\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000")) goto l32;  goto l31;
  l32:;	  yypos= yypos32; yythunkpos= yythunkpos32;
  }
  yyprintf((stderr, "  ok   %s @ %s\n", "s", yybuf+yypos));
  return 1;
  l30:;	  yypos= yypos0; yythunkpos= yythunkpos0;
  yyprintf((stderr, "  fail %s @ %s\n", "s", yybuf+yypos));
  return 0;
}
YY_RULE(int) yy_id()
{  int yypos0= yypos, yythunkpos0= yythunkpos;
  yyprintf((stderr, "%s\n", "id"));  yyText(yybegin, yyend);  if (!(YY_BEGIN)) goto l33;  if (!yymatchClass((unsigned char *)"\000\000\000\000\000\000\000\000\376\377\377\207\376\377\377\007\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000")) goto l33;
  l34:;	
  {  int yypos35= yypos, yythunkpos35= yythunkpos;  if (!yymatchClass((unsigned char *)"\000\000\000\000\000\000\000\000\376\377\377\207\376\377\377\007\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000")) goto l35;  goto l34;
  l35:;	  yypos= yypos35; yythunkpos= yythunkpos35;
  }  yyText(yybegin, yyend);  if (!(YY_END)) goto l33;  yyDo(yy_1_id, yybegin, yyend);
  yyprintf((stderr, "  ok   %s @ %s\n", "id", yybuf+yypos));
  return 1;
  l33:;	  yypos= yypos0; yythunkpos= yythunkpos0;
  yyprintf((stderr, "  fail %s @ %s\n", "id", yybuf+yypos));
  return 0;
}
YY_RULE(int) yy_expr()
{  int yypos0= yypos, yythunkpos0= yythunkpos;
  yyprintf((stderr, "%s\n", "expr"));
  {  int yypos37= yypos, yythunkpos37= yythunkpos;  yyText(yybegin, yyend);  if (!(YY_BEGIN)) goto l38;  if (!yymatchClass((unsigned char *)"\000\000\000\000\000\000\000\000\376\377\377\207\376\377\377\007\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000")) goto l38;
  l39:;	
  {  int yypos40= yypos, yythunkpos40= yythunkpos;  if (!yymatchClass((unsigned char *)"\000\000\000\000\000\000\000\000\376\377\377\207\376\377\377\007\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000")) goto l40;  goto l39;
  l40:;	  yypos= yypos40; yythunkpos= yythunkpos40;
  }  if (!yymatchChar('.')) goto l38;  if (!yymatchClass((unsigned char *)"\000\000\000\000\000\000\000\000\376\377\377\207\376\377\377\007\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000")) goto l38;
  l41:;	
  {  int yypos42= yypos, yythunkpos42= yythunkpos;  if (!yymatchClass((unsigned char *)"\000\000\000\000\000\000\000\000\376\377\377\207\376\377\377\007\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000")) goto l42;  goto l41;
  l42:;	  yypos= yypos42; yythunkpos= yythunkpos42;
  }  yyText(yybegin, yyend);  if (!(YY_END)) goto l38;  yyDo(yy_1_expr, yybegin, yyend);  goto l37;
  l38:;	  yypos= yypos37; yythunkpos= yythunkpos37;  yyText(yybegin, yyend);  if (!(YY_BEGIN)) goto l43;  if (!yymatchClass((unsigned char *)"\000\000\000\000\000\000\000\000\376\377\377\207\376\377\377\007\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000")) goto l43;
  l44:;	
  {  int yypos45= yypos, yythunkpos45= yythunkpos;  if (!yymatchClass((unsigned char *)"\000\000\000\000\000\000\000\000\376\377\377\207\376\377\377\007\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000")) goto l45;  goto l44;
  l45:;	  yypos= yypos45; yythunkpos= yythunkpos45;
  }  if (!yymatchString("->")) goto l43;  if (!yymatchClass((unsigned char *)"\000\000\000\000\000\000\000\000\376\377\377\207\376\377\377\007\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000")) goto l43;
  l46:;	
  {  int yypos47= yypos, yythunkpos47= yythunkpos;  if (!yymatchClass((unsigned char *)"\000\000\000\000\000\000\000\000\376\377\377\207\376\377\377\007\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000")) goto l47;  goto l46;
  l47:;	  yypos= yypos47; yythunkpos= yythunkpos47;
  }  if (!yymatchChar('[')) goto l43;
  l48:;	
  {  int yypos49= yypos, yythunkpos49= yythunkpos;
  {  int yypos50= yypos, yythunkpos50= yythunkpos;  if (!yymatchChar(']')) goto l50;  goto l49;
  l50:;	  yypos= yypos50; yythunkpos= yythunkpos50;
  }  if (!yymatchDot()) goto l49;  goto l48;
  l49:;	  yypos= yypos49; yythunkpos= yythunkpos49;
  }  if (!yymatchChar(']')) goto l43;  yyText(yybegin, yyend);  if (!(YY_END)) goto l43;  yyDo(yy_2_expr, yybegin, yyend);  goto l37;
  l43:;	  yypos= yypos37; yythunkpos= yythunkpos37;  yyText(yybegin, yyend);  if (!(YY_BEGIN)) goto l51;  if (!yymatchClass((unsigned char *)"\000\000\000\000\000\000\000\000\376\377\377\207\376\377\377\007\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000")) goto l51;
  l52:;	
  {  int yypos53= yypos, yythunkpos53= yythunkpos;  if (!yymatchClass((unsigned char *)"\000\000\000\000\000\000\000\000\376\377\377\207\376\377\377\007\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000")) goto l53;  goto l52;
  l53:;	  yypos= yypos53; yythunkpos= yythunkpos53;
  }  if (!yymatchString("->")) goto l51;  if (!yymatchClass((unsigned char *)"\000\000\000\000\000\000\000\000\376\377\377\207\376\377\377\007\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000")) goto l51;
  l54:;	
  {  int yypos55= yypos, yythunkpos55= yythunkpos;  if (!yymatchClass((unsigned char *)"\000\000\000\000\000\000\000\000\376\377\377\207\376\377\377\007\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000")) goto l55;  goto l54;
  l55:;	  yypos= yypos55; yythunkpos= yythunkpos55;
  }  yyText(yybegin, yyend);  if (!(YY_END)) goto l51;  yyDo(yy_3_expr, yybegin, yyend);  goto l37;
  l51:;	  yypos= yypos37; yythunkpos= yythunkpos37;  yyText(yybegin, yyend);  if (!(YY_BEGIN)) goto l56;  if (!yymatchClass((unsigned char *)"\000\000\000\000\000\000\000\000\376\377\377\207\376\377\377\007\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000")) goto l56;
  l57:;	
  {  int yypos58= yypos, yythunkpos58= yythunkpos;  if (!yymatchClass((unsigned char *)"\000\000\000\000\000\000\000\000\376\377\377\207\376\377\377\007\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000")) goto l58;  goto l57;
  l58:;	  yypos= yypos58; yythunkpos= yythunkpos58;
  }  if (!yymatchChar('[')) goto l56;
  l59:;	
  {  int yypos60= yypos, yythunkpos60= yythunkpos;
  {  int yypos61= yypos, yythunkpos61= yythunkpos;  if (!yymatchChar(']')) goto l61;  goto l60;
  l61:;	  yypos= yypos61; yythunkpos= yythunkpos61;
  }  if (!yymatchDot()) goto l60;  goto l59;
  l60:;	  yypos= yypos60; yythunkpos= yythunkpos60;
  }  if (!yymatchChar(']')) goto l56;  yyText(yybegin, yyend);  if (!(YY_END)) goto l56;  yyDo(yy_4_expr, yybegin, yyend);  goto l37;
  l56:;	  yypos= yypos37; yythunkpos= yythunkpos37;  yyText(yybegin, yyend);  if (!(YY_BEGIN)) goto l62;  if (!yymatchClass((unsigned char *)"\000\000\000\000\000\000\000\000\376\377\377\207\376\377\377\007\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000")) goto l62;
  l63:;	
  {  int yypos64= yypos, yythunkpos64= yythunkpos;  if (!yymatchClass((unsigned char *)"\000\000\000\000\000\000\000\000\376\377\377\207\376\377\377\007\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000")) goto l64;  goto l63;
  l64:;	  yypos= yypos64; yythunkpos= yythunkpos64;
  }  if (!yymatchChar('(')) goto l62;
  l65:;	
  {  int yypos66= yypos, yythunkpos66= yythunkpos;
  {  int yypos67= yypos, yythunkpos67= yythunkpos;  if (!yymatchChar(')')) goto l67;  goto l66;
  l67:;	  yypos= yypos67; yythunkpos= yythunkpos67;
  }  if (!yymatchDot()) goto l66;  goto l65;
  l66:;	  yypos= yypos66; yythunkpos= yythunkpos66;
  }  if (!yymatchChar(')')) goto l62;  yyText(yybegin, yyend);  if (!(YY_END)) goto l62;  yyDo(yy_5_expr, yybegin, yyend);  goto l37;
  l62:;	  yypos= yypos37; yythunkpos= yythunkpos37;  if (!yy_id()) goto l36;
  }
  l37:;	
  yyprintf((stderr, "  ok   %s @ %s\n", "expr", yybuf+yypos));
  return 1;
  l36:;	  yypos= yypos0; yythunkpos= yythunkpos0;
  yyprintf((stderr, "  fail %s @ %s\n", "expr", yybuf+yypos));
  return 0;
}
YY_RULE(int) yy_assertion()
{  int yypos0= yypos, yythunkpos0= yythunkpos;  yyDo(yyPush, 3, 0);
  yyprintf((stderr, "%s\n", "assertion"));  if (!yy_expr()) goto l68;  yyDo(yySet, -3, 0);  if (!yy_s()) goto l68;  if (!yymatchString("should")) goto l68;  if (!yy_s()) goto l68;
  {  int yypos69= yypos, yythunkpos69= yythunkpos;  if (!yymatchString("not")) goto l70;  if (!yy_s()) goto l70;  if (!yy_id()) goto l70;  yyDo(yySet, -2, 0);  if (!yy_consume()) goto l70;  yyDo(yySet, -1, 0);  yyDo(yy_1_assertion, yybegin, yyend);  goto l69;
  l70:;	  yypos= yypos69; yythunkpos= yythunkpos69;  if (!yy_id()) goto l68;  yyDo(yySet, -2, 0);  if (!yy_consume()) goto l68;  yyDo(yySet, -1, 0);  yyDo(yy_2_assertion, yybegin, yyend);
  }
  l69:;	
  yyprintf((stderr, "  ok   %s @ %s\n", "assertion", yybuf+yypos));  yyDo(yyPop, 3, 0);
  return 1;
  l68:;	  yypos= yypos0; yythunkpos= yythunkpos0;
  yyprintf((stderr, "  fail %s @ %s\n", "assertion", yybuf+yypos));
  return 0;
}
YY_RULE(int) yy_end()
{  int yypos0= yypos, yythunkpos0= yythunkpos;
  yyprintf((stderr, "%s\n", "end"));
  {  int yypos72= yypos, yythunkpos72= yythunkpos;  if (!yy_ws()) goto l72;  goto l73;
  l72:;	  yypos= yypos72; yythunkpos= yythunkpos72;
  }
  l73:;	  if (!yymatchString("end")) goto l71;
  {  int yypos74= yypos, yythunkpos74= yythunkpos;  if (!yy_ws()) goto l74;  goto l75;
  l74:;	  yypos= yypos74; yythunkpos= yythunkpos74;
  }
  l75:;	
  yyprintf((stderr, "  ok   %s @ %s\n", "end", yybuf+yypos));
  return 1;
  l71:;	  yypos= yypos0; yythunkpos= yythunkpos0;
  yyprintf((stderr, "  fail %s @ %s\n", "end", yybuf+yypos));
  return 0;
}
YY_RULE(int) yy_block()
{  int yypos0= yypos, yythunkpos0= yythunkpos;
  yyprintf((stderr, "%s\n", "block"));
  {  int yypos77= yypos, yythunkpos77= yythunkpos;  if (!yy_ws()) goto l78;  if (!yymatchString("before_each")) goto l78;  if (!yy_ws()) goto l78;  yyDo(yy_1_block, yybegin, yyend);  goto l77;
  l78:;	  yypos= yypos77; yythunkpos= yythunkpos77;  if (!yy_ws()) goto l79;  if (!yymatchString("before")) goto l79;  if (!yy_ws()) goto l79;  yyDo(yy_2_block, yybegin, yyend);  goto l77;
  l79:;	  yypos= yypos77; yythunkpos= yythunkpos77;  if (!yy_ws()) goto l80;  if (!yymatchString("after_each")) goto l80;  if (!yy_ws()) goto l80;  yyDo(yy_3_block, yybegin, yyend);  goto l77;
  l80:;	  yypos= yypos77; yythunkpos= yythunkpos77;  if (!yy_ws()) goto l76;  if (!yymatchString("after")) goto l76;  if (!yy_ws()) goto l76;  yyDo(yy_4_block, yybegin, yyend);
  }
  l77:;	  yyDo(yy_5_block, yybegin, yyend);
  yyprintf((stderr, "  ok   %s @ %s\n", "block", yybuf+yypos));
  return 1;
  l76:;	  yypos= yypos0; yythunkpos= yythunkpos0;
  yyprintf((stderr, "  fail %s @ %s\n", "block", yybuf+yypos));
  return 0;
}
YY_RULE(int) yy_spec()
{  int yypos0= yypos, yythunkpos0= yythunkpos;  yyDo(yyPush, 1, 0);
  yyprintf((stderr, "%s\n", "spec"));  if (!yymatchString("it")) goto l81;  if (!yy_s()) goto l81;  if (!yy_string()) goto l81;  yyDo(yySet, -1, 0);  yyDo(yy_1_spec, yybegin, yyend);
  yyprintf((stderr, "  ok   %s @ %s\n", "spec", yybuf+yypos));  yyDo(yyPop, 1, 0);
  return 1;
  l81:;	  yypos= yypos0; yythunkpos= yythunkpos0;
  yyprintf((stderr, "  fail %s @ %s\n", "spec", yybuf+yypos));
  return 0;
}
YY_RULE(int) yy_suite()
{  int yypos0= yypos, yythunkpos0= yythunkpos;  yyDo(yyPush, 1, 0);
  yyprintf((stderr, "%s\n", "suite"));  if (!yymatchString("describe")) goto l82;  if (!yy_s()) goto l82;  if (!yy_string()) goto l82;  yyDo(yySet, -1, 0);  yyDo(yy_1_suite, yybegin, yyend);
  yyprintf((stderr, "  ok   %s @ %s\n", "suite", yybuf+yypos));  yyDo(yyPop, 1, 0);
  return 1;
  l82:;	  yypos= yypos0; yythunkpos= yythunkpos0;
  yyprintf((stderr, "  fail %s @ %s\n", "suite", yybuf+yypos));
  return 0;
}
YY_RULE(int) yy_main()
{  int yypos0= yypos, yythunkpos0= yythunkpos;
  yyprintf((stderr, "%s\n", "main"));  yyText(yybegin, yyend);  if (!(YY_BEGIN)) goto l83;
  {  int yypos86= yypos, yythunkpos86= yythunkpos;  if (!yymatchString("describe")) goto l86;  goto l83;
  l86:;	  yypos= yypos86; yythunkpos= yythunkpos86;
  }  if (!yymatchDot()) goto l83;
  l84:;	
  {  int yypos85= yypos, yythunkpos85= yythunkpos;
  {  int yypos87= yypos, yythunkpos87= yythunkpos;  if (!yymatchString("describe")) goto l87;  goto l85;
  l87:;	  yypos= yypos87; yythunkpos= yythunkpos87;
  }  if (!yymatchDot()) goto l85;  goto l84;
  l85:;	  yypos= yypos85; yythunkpos= yythunkpos85;
  }  yyText(yybegin, yyend);  if (!(YY_END)) goto l83;  yyDo(yy_1_main, yybegin, yyend);
  l88:;	
  {  int yypos89= yypos, yythunkpos89= yythunkpos;
  {  int yypos90= yypos, yythunkpos90= yythunkpos;  if (!yy_suite()) goto l91;  goto l90;
  l91:;	  yypos= yypos90; yythunkpos= yythunkpos90;  if (!yy_spec()) goto l92;  goto l90;
  l92:;	  yypos= yypos90; yythunkpos= yythunkpos90;  if (!yy_block()) goto l93;  goto l90;
  l93:;	  yypos= yypos90; yythunkpos= yythunkpos90;  if (!yy_end()) goto l94;  yyDo(yy_2_main, yybegin, yyend);  goto l90;
  l94:;	  yypos= yypos90; yythunkpos= yythunkpos90;  if (!yy_assertion()) goto l95;  goto l90;
  l95:;	  yypos= yypos90; yythunkpos= yythunkpos90;  yyText(yybegin, yyend);  if (!(YY_BEGIN)) goto l89;  if (!yymatchDot()) goto l89;  yyText(yybegin, yyend);  if (!(YY_END)) goto l89;  yyDo(yy_3_main, yybegin, yyend);
  }
  l90:;	  goto l88;
  l89:;	  yypos= yypos89; yythunkpos= yythunkpos89;
  }
  yyprintf((stderr, "  ok   %s @ %s\n", "main", yybuf+yypos));
  return 1;
  l83:;	  yypos= yypos0; yythunkpos= yythunkpos0;
  yyprintf((stderr, "  fail %s @ %s\n", "main", yybuf+yypos));
  return 0;
}

#ifndef YY_PART

typedef int (*yyrule)();

YY_PARSE(int) YYPARSEFROM(yyrule yystart)
{
  int yyok;
  if (!yybuflen)
    {
      yybuflen= 1024;
      yybuf= malloc(yybuflen);
      yytextlen= 1024;
      yytext= malloc(yytextlen);
      yythunkslen= 32;
      yythunks= malloc(sizeof(yythunk) * yythunkslen);
      yyvalslen= 32;
      yyvals= malloc(sizeof(YYSTYPE) * yyvalslen);
      yybegin= yyend= yypos= yylimit= yythunkpos= 0;
    }
  yybegin= yyend= yypos;
  yythunkpos= 0;
  yyval= yyvals;
  yyok= yystart();
  if (yyok) yyDone();
  yyCommit();
  return yyok;
  (void)yyrefill;
  (void)yymatchDot;
  (void)yymatchChar;
  (void)yymatchString;
  (void)yymatchClass;
  (void)yyDo;
  (void)yyText;
  (void)yyDone;
  (void)yyCommit;
  (void)yyAccept;
  (void)yyPush;
  (void)yyPop;
  (void)yySet;
  (void)yytextmax;
}

YY_PARSE(int) YYPARSE(void)
{
  return YYPARSEFROM(yy_main);
}

#endif


static void usage() {
  printf(
    "\n  \033[1;01mCSpec\033[0m\n"
    "\n    The cspec binary converts the CSpec grammar into literal"
    "\n    C source via stdin and stdout."
    "\n"
    "\n  \033[1;01mUsage:\033[0m"
    "\n"
    "\n    cspec < spec/foo_spec.c > spec/foo.c"
    "\n"
    "\n");
}

int main(int argc, char **argv) {
  if (argc > 1)
    usage();
  else {
    DEFER("int main() %c\n", LPAREN)
    while (YYPARSE()) ;
    DEFER("Suite_run(suite_0);\n"
         "CSpec_stats();\n"
         "return 0;"
         "\n%c\n", RPAREN);
    puts(defer);
  }
  return 0;
}
