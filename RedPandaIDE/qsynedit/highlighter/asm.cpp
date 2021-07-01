#include "asm.h"
#include "../Constants.h"

const QSet<QString> SynEditASMHighlighter::Keywords {
    "aaa","aad","aam","adc","add","and","arpl","bound","bsf","bsr","bswap","bt","btc","btr","bts",
    "call","cbw","cdq","clc","cld","cli","clts","cmc","cmp","cmps","cmpsb","cmpsd","cmpsw",
    "cmpxchg","cwd","cwde","daa","das","dec","div","emms","enter","f2xm1","fabs","fadd","faddp","fbld",
    "fbstp","fchs","fclex","fcmovb","fcmovbe","fcmove","fcmovnb","fcmovnbe","fcmovne","fcmovnu",
    "fcmovu","fcom","fcomi","fcomip","fcomp","fcompp","fcos","fdecstp","fdiv","fdivp","fdivr",
    "fdivrp","femms","ffree","fiadd","ficom","ficomp","fidiv","fidivr","fild","fimul","fincstp",
    "finit","fist","fistp","fisub","fisubr","fld","fld1","fldcw","fldenv","fldl2e","fldl2t","fldlg2",
    "fldln2","fldpi","fldz","fmul","fmulp","fnclex","fninit","fnop","fnsave","fnstcw","fnstenv",
    "fnstsw","fpatan","fprem1","fptan","frndint","frstor","fsave","fscale","fsin","fsincos",
    "fsqrt","fst","fstcw","fstenv","fstp","fstsw","fsub","fsubp","fsubr","fsubrp","ftst",
    "fucom","fucomi","fucomip","fucomp","fucompp","fwait","fxch","fxtract","fyl2xp1","hlt","idiv",
    "imul","in","inc","ins","insb","insd","insw","int","into","invd","invlpg","iret","iretd","iretw",
    "ja","jae","jb","jbe","jc","jcxz","je","jecxz","jg","jge","jl","jle","jmp","jna","jnae","jnb","jnbe","jnc",
    "jne","jng","jnge","jnl","jnle","jno","jnp","jns","jnz","jo","jp","jpe","jpo","js","jz","lahf","lar","lds",
    "lea","leave","les","lfs","lgdt","lgs","lidt","lldt","lmsw","lock","lods","lodsb","lodsd","lodsw",
    "loop","loope","loopne","loopnz","loopz","lsl","lss","ltr","mov","movd","movq"," movs","movsb",
    "movsd","movsw","movsx","movzx","mul","neg","nop","not","or","out","outs","outsb","outsd","outsw",
    "packssdw","packsswb","packuswb","paddb","paddd","paddsb","paddsw","paddusb","paddusw",
    "paddw","pand","pandn","pavgusb","pcmpeqb","pcmpeqd","pcmpeqw","pcmpgtb","pcmpgtd","pcmpgtw",
    "pf2id","pfacc","pfadd","pfcmpeq","pfcmpge","pfcmpgt","pfmax","pfmin","pfmul","pfrcp",
    "pfrcpit1","pfrcpit2","pfrsqit1","pfrsqrt","pfsub","pfsubr","pi2fd","pmaddwd","pmulhrw",
    "pmulhw","pmullw","pop","popa","popad","popaw","popf","popfd","popfw","por","prefetch","prefetchw",
    "pslld","psllq","psllw","psrad","psraw","psrld","psrlq","psrlw","psubb","psubd","psubsb",
    "psubsw","psubusb","psubusw","psubw","punpckhbw","punpckhdq","punpckhwd","punpcklbw",
    "punpckldq","punpcklwd","push","pusha","pushad","pushaw","pushf","pushfd","pushfw","pxor",
    "rcl","rcr","rep","repe","repne","repnz","repz","ret","rol","ror","sahf","sal","sar","sbb","scas",
    "scasb","scasd","scasw","seta","setae","setb","setbe","setc","sete","setg","setge","setl","setle",
    "setna","setnae","setnb","setnbe","setnc","setne","setng","setnge","setnl","setnle","setno",
    "setnp","setns","setnz","seto","setp","setpo","sets","setz","sgdt","shl","shld","shr","shrd","sidt",
    "sldt","smsw","stc","std","sti","stos","stosb","stosd","stosw","str","sub","test","verr","verw",
    "wait","wbinvd","xadd","xchg","xlat","xlatb","xor"
};



void SynEditASMHighlighter::CommentProc()
{
    mTokenID = TokenKind::Comment;
    do {
        mRun++;
    } while (! (mLine[mRun]==0 || mLine[mRun] == '\r' || mLine[mRun]=='\n'));
}

void SynEditASMHighlighter::CRProc()
{
    mTokenID = TokenKind::Space;
    mRun++;
    if (mLine[mRun] == 10)
        mRun++;
}

bool SynEditASMHighlighter::eol() const
{
    return mTokenID == TokenKind::Null;
}

QString SynEditASMHighlighter::languageName()
{
    return "asm";
}

SynHighlighterLanguage SynEditASMHighlighter::language()
{
    return SynHighlighterLanguage::Asssembly;
}

QString SynEditASMHighlighter::getToken() const
{
    return mLineString.mid(mTokenPos,mRun-mTokenPos);
}

PSynHighlighterAttribute SynEditASMHighlighter::getTokenAttribute() const
{
    switch(mTokenID) {
    case TokenKind::Comment:
        return mCommentAttribute;
    case TokenKind::Identifier:
        return mIdentifierAttribute;
    case TokenKind::Key:
        return mKeywordAttribute;
    case TokenKind::Number:
        return mNumberAttribute;
    case TokenKind::Space:
        return mWhitespaceAttribute;
    case TokenKind::String:
        return mStringAttribute;
    case TokenKind::Symbol:
        return mSymbolAttribute;
    case TokenKind::Unknown:
        return mIdentifierAttribute;
    }
    return PSynHighlighterAttribute();
}

SynTokenKind SynEditASMHighlighter::getTokenKind()
{
    return mTokenID;
}

SynHighlighterTokenType SynEditASMHighlighter::getTokenType()
{
    switch(mTokenID) {
    case TokenKind::Comment:
        return SynHighlighterTokenType::Comment;
    case TokenKind::Identifier:
        return SynHighlighterTokenType::Identifier;
    case TokenKind::Key:
        return SynHighlighterTokenType::Keyword;
    case TokenKind::Number:
        return SynHighlighterTokenType::Number;
    case TokenKind::Space:
        return SynHighlighterTokenType::Space;
    case TokenKind::String:
        return SynHighlighterTokenType::String;
    case TokenKind::Symbol:
        return SynHighlighterTokenType::Symbol;
    case TokenKind::Unknown:
        return SynHighlighterTokenType::Default;
    }
    return SynHighlighterTokenType::Default;
}

void SynEditASMHighlighter::next()
{
    mTokenPos = mRun;
    switch(mLine[mRun].unicode()) {
    case 0:
        NullProc();
        break;
    case 10:
        LFProc();
        break;
    case 13:
        CRProc();
        break;
    case '\"':
        StringProc();
        break;
    case '\'':
        SingleQuoteStringProc();
        break;
    case '>':
        GreaterProc();
        break;
    case '<':
        LowerProc();
        break;
    case '/':
        SlashProc();
        break;
    case '#':
    case ';':
        CommentProc();
        break;
    case '.':
    case ':':
    case '&':
    case '{':
    case '}':
    case '=':
    case '^':
    case '-':
    case '+':
    case '(':
    case ')':
    case '*':
        SymbolProc();
        break;
    default:
        if (mLine[mRun]>='0' && mLine[mRun]<='9') {
            NumberProc();
        } else if ((mLine[mRun]>='A' && mLine[mRun]<='Z')
                   || (mLine[mRun]>='a' && mLine[mRun]<='z')
                   || (mLine[mRun]=='_')) {
            IdentProc();
        } else if (mLine[mRun]<=32) {
            SpaceProc();
        } else {
            UnknownProc();
        }
    }
}

void SynEditASMHighlighter::setLine(const QString &newLine, int lineNumber)
{
    mLineString = newLine;
    mLine = mLineString.data();
    mLineNumber = lineNumber;
    mRun = 0;
    next();
}

SynHighlighterClass SynEditASMHighlighter::getClass() const
{
    return SynHighlighterClass::CppHighlighter;
}

QString SynEditASMHighlighter::getName() const
{
    return SYN_HIGHLIGHTER_CPP;
}
