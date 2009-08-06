/* A recursive-descent parser generated by peg 0.1.2 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define YYRULECOUNT 16

  #include "cspec.h"

  #define YYSTYPE char *
  
  #define LPAREN '{'
  #define RPAREN '}'

  #define DUP yy = strdup(yytext)
  
  #define LITERAL printf("%s", yytext)
  
  #define NODE(T) current = nodeType##T, buf2 = NULL;
    
  #define NODE2(T, S) current = nodeType##T, buf2 = S;
  
  #define END printf("\n%c\n", RPAREN);  
  
  #define DEFER(S, ...) sprintf(buf, S "\n", __VA_ARGS__); strcat(defer, buf);
  
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
   LITERAL ;
}
YY_ACTION(void) yy_2_main(char *yytext, int yyleng)
{
  yyprintf((stderr, "do yy_2_main\n"));
   OUT ;
}
YY_ACTION(void) yy_1_main(char *yytext, int yyleng)
{
  yyprintf((stderr, "do yy_1_main\n"));
   LITERAL ;
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
  {  int yypos7= yypos, yythunkpos7= yythunkpos;  if (!yymatchChar('\n')) goto l8;  goto l7;
  l8:;	  yypos= yypos7; yythunkpos= yythunkpos7;  if (!yymatchString("\r\n")) goto l9;  goto l7;
  l9:;	  yypos= yypos7; yythunkpos= yythunkpos7;  if (!yymatchChar('\r')) goto l6;
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
  }  yyText(yybegin, yyend);  if (!(YY_END)) goto l43;  yyDo(yy_2_expr, yybegin, yyend);  goto l37;
  l43:;	  yypos= yypos37; yythunkpos= yythunkpos37;  yyText(yybegin, yyend);  if (!(YY_BEGIN)) goto l48;  if (!yymatchClass((unsigned char *)"\000\000\000\000\000\000\000\000\376\377\377\207\376\377\377\007\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000")) goto l48;
  l49:;	
  {  int yypos50= yypos, yythunkpos50= yythunkpos;  if (!yymatchClass((unsigned char *)"\000\000\000\000\000\000\000\000\376\377\377\207\376\377\377\007\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000")) goto l50;  goto l49;
  l50:;	  yypos= yypos50; yythunkpos= yythunkpos50;
  }  if (!yymatchChar('(')) goto l48;
  l51:;	
  {  int yypos52= yypos, yythunkpos52= yythunkpos;
  {  int yypos53= yypos, yythunkpos53= yythunkpos;  if (!yymatchChar(')')) goto l53;  goto l52;
  l53:;	  yypos= yypos53; yythunkpos= yythunkpos53;
  }  if (!yymatchDot()) goto l52;  goto l51;
  l52:;	  yypos= yypos52; yythunkpos= yythunkpos52;
  }  if (!yymatchChar(')')) goto l48;  yyText(yybegin, yyend);  if (!(YY_END)) goto l48;  yyDo(yy_3_expr, yybegin, yyend);  goto l37;
  l48:;	  yypos= yypos37; yythunkpos= yythunkpos37;  if (!yy_id()) goto l36;
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
  yyprintf((stderr, "%s\n", "assertion"));
  {  int yypos55= yypos, yythunkpos55= yythunkpos;  if (!yy_expr()) goto l56;  yyDo(yySet, -3, 0);  if (!yy_s()) goto l56;  if (!yymatchString("should")) goto l56;  if (!yy_s()) goto l56;  if (!yymatchString("not")) goto l56;  if (!yy_s()) goto l56;  if (!yy_id()) goto l56;  yyDo(yySet, -2, 0);  if (!yy_consume()) goto l56;  yyDo(yySet, -1, 0);  yyDo(yy_1_assertion, yybegin, yyend);  goto l55;
  l56:;	  yypos= yypos55; yythunkpos= yythunkpos55;  if (!yy_expr()) goto l54;  yyDo(yySet, -3, 0);  if (!yy_s()) goto l54;  if (!yymatchString("should")) goto l54;  if (!yy_s()) goto l54;  if (!yy_id()) goto l54;  yyDo(yySet, -2, 0);  if (!yy_consume()) goto l54;  yyDo(yySet, -1, 0);  yyDo(yy_2_assertion, yybegin, yyend);
  }
  l55:;	
  yyprintf((stderr, "  ok   %s @ %s\n", "assertion", yybuf+yypos));  yyDo(yyPop, 3, 0);
  return 1;
  l54:;	  yypos= yypos0; yythunkpos= yythunkpos0;
  yyprintf((stderr, "  fail %s @ %s\n", "assertion", yybuf+yypos));
  return 0;
}
YY_RULE(int) yy_end()
{  int yypos0= yypos, yythunkpos0= yythunkpos;
  yyprintf((stderr, "%s\n", "end"));
  {  int yypos58= yypos, yythunkpos58= yythunkpos;  if (!yy_ws()) goto l58;  goto l59;
  l58:;	  yypos= yypos58; yythunkpos= yythunkpos58;
  }
  l59:;	  if (!yymatchString("end")) goto l57;
  {  int yypos60= yypos, yythunkpos60= yythunkpos;  if (!yy_ws()) goto l60;  goto l61;
  l60:;	  yypos= yypos60; yythunkpos= yythunkpos60;
  }
  l61:;	
  yyprintf((stderr, "  ok   %s @ %s\n", "end", yybuf+yypos));
  return 1;
  l57:;	  yypos= yypos0; yythunkpos= yythunkpos0;
  yyprintf((stderr, "  fail %s @ %s\n", "end", yybuf+yypos));
  return 0;
}
YY_RULE(int) yy_block()
{  int yypos0= yypos, yythunkpos0= yythunkpos;
  yyprintf((stderr, "%s\n", "block"));
  {  int yypos63= yypos, yythunkpos63= yythunkpos;  if (!yy_ws()) goto l64;  if (!yymatchString("before_each")) goto l64;  if (!yy_ws()) goto l64;  yyDo(yy_1_block, yybegin, yyend);  goto l63;
  l64:;	  yypos= yypos63; yythunkpos= yythunkpos63;  if (!yy_ws()) goto l65;  if (!yymatchString("before")) goto l65;  if (!yy_ws()) goto l65;  yyDo(yy_2_block, yybegin, yyend);  goto l63;
  l65:;	  yypos= yypos63; yythunkpos= yythunkpos63;  if (!yy_ws()) goto l66;  if (!yymatchString("after_each")) goto l66;  if (!yy_ws()) goto l66;  yyDo(yy_3_block, yybegin, yyend);  goto l63;
  l66:;	  yypos= yypos63; yythunkpos= yythunkpos63;  if (!yy_ws()) goto l62;  if (!yymatchString("after")) goto l62;  if (!yy_ws()) goto l62;  yyDo(yy_4_block, yybegin, yyend);
  }
  l63:;	  yyDo(yy_5_block, yybegin, yyend);
  yyprintf((stderr, "  ok   %s @ %s\n", "block", yybuf+yypos));
  return 1;
  l62:;	  yypos= yypos0; yythunkpos= yythunkpos0;
  yyprintf((stderr, "  fail %s @ %s\n", "block", yybuf+yypos));
  return 0;
}
YY_RULE(int) yy_spec()
{  int yypos0= yypos, yythunkpos0= yythunkpos;  yyDo(yyPush, 1, 0);
  yyprintf((stderr, "%s\n", "spec"));  if (!yymatchString("it")) goto l67;  if (!yy_s()) goto l67;  if (!yy_string()) goto l67;  yyDo(yySet, -1, 0);  yyDo(yy_1_spec, yybegin, yyend);
  yyprintf((stderr, "  ok   %s @ %s\n", "spec", yybuf+yypos));  yyDo(yyPop, 1, 0);
  return 1;
  l67:;	  yypos= yypos0; yythunkpos= yythunkpos0;
  yyprintf((stderr, "  fail %s @ %s\n", "spec", yybuf+yypos));
  return 0;
}
YY_RULE(int) yy_suite()
{  int yypos0= yypos, yythunkpos0= yythunkpos;  yyDo(yyPush, 1, 0);
  yyprintf((stderr, "%s\n", "suite"));  if (!yymatchString("describe")) goto l68;  if (!yy_s()) goto l68;  if (!yy_string()) goto l68;  yyDo(yySet, -1, 0);  yyDo(yy_1_suite, yybegin, yyend);
  yyprintf((stderr, "  ok   %s @ %s\n", "suite", yybuf+yypos));  yyDo(yyPop, 1, 0);
  return 1;
  l68:;	  yypos= yypos0; yythunkpos= yythunkpos0;
  yyprintf((stderr, "  fail %s @ %s\n", "suite", yybuf+yypos));
  return 0;
}
YY_RULE(int) yy_main()
{  int yypos0= yypos, yythunkpos0= yythunkpos;
  yyprintf((stderr, "%s\n", "main"));  yyText(yybegin, yyend);  if (!(YY_BEGIN)) goto l69;
  {  int yypos72= yypos, yythunkpos72= yythunkpos;  if (!yymatchString("describe")) goto l72;  goto l69;
  l72:;	  yypos= yypos72; yythunkpos= yythunkpos72;
  }  if (!yymatchDot()) goto l69;
  l70:;	
  {  int yypos71= yypos, yythunkpos71= yythunkpos;
  {  int yypos73= yypos, yythunkpos73= yythunkpos;  if (!yymatchString("describe")) goto l73;  goto l71;
  l73:;	  yypos= yypos73; yythunkpos= yythunkpos73;
  }  if (!yymatchDot()) goto l71;  goto l70;
  l71:;	  yypos= yypos71; yythunkpos= yythunkpos71;
  }  yyText(yybegin, yyend);  if (!(YY_END)) goto l69;  yyDo(yy_1_main, yybegin, yyend);
  l74:;	
  {  int yypos75= yypos, yythunkpos75= yythunkpos;
  {  int yypos76= yypos, yythunkpos76= yythunkpos;  if (!yy_suite()) goto l77;  goto l76;
  l77:;	  yypos= yypos76; yythunkpos= yythunkpos76;  if (!yy_spec()) goto l78;  goto l76;
  l78:;	  yypos= yypos76; yythunkpos= yythunkpos76;  if (!yy_block()) goto l79;  goto l76;
  l79:;	  yypos= yypos76; yythunkpos= yythunkpos76;  if (!yy_end()) goto l80;  yyDo(yy_2_main, yybegin, yyend);  goto l76;
  l80:;	  yypos= yypos76; yythunkpos= yythunkpos76;  if (!yy_assertion()) goto l81;  goto l76;
  l81:;	  yypos= yypos76; yythunkpos= yythunkpos76;  yyText(yybegin, yyend);  if (!(YY_BEGIN)) goto l75;  if (!yymatchDot()) goto l75;  yyText(yybegin, yyend);  if (!(YY_END)) goto l75;  yyDo(yy_3_main, yybegin, yyend);
  }
  l76:;	  goto l74;
  l75:;	  yypos= yypos75; yythunkpos= yythunkpos75;
  }
  yyprintf((stderr, "  ok   %s @ %s\n", "main", yybuf+yypos));
  return 1;
  l69:;	  yypos= yypos0; yythunkpos= yythunkpos0;
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
