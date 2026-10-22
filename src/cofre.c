#include <stdio.h>
#include <string.h>
#include <stdint.h>

static const unsigned char programa[] = {150,92,245,31,212,93,51,134,18,92,150,91,245,60,212,94,51,52,18,92,150,82,245,33,212,95,51,150,18,92,150,89,245,198,212,88,51,111,18,92,150,80,245,235,212,89,51,160,18,92,150,95,245,136,212,90,51,216,18,92,150,86,245,173,212,91,51,117,18,92,150,93,245,82,212,93,51,65,18,92,150,84,245,119,212,94,51,228,18,92,150,83,245,20,212,95,51,225,18,92,150,90,245,57,212,88,51,58,18,92,150,81,245,222,212,89,51,191,18,92,150,88,245,195,212,90,51,125,18,92,150,87,245,224,212,91,51,42,18,92,150,94,245,133,212,93,51,60,18,92,150,85,245,170,212,94,51,28,18,92,65,92};
static int validar(const unsigned char *s, size_t n) {
    if (n != 16) return 0;
    uint32_t estado=UINT32_C(0xa53c9e17), erro=0;
    unsigned char a=0;
    for (size_t pc=0; pc+1<sizeof programa; pc+=2) {
        unsigned op=programa[pc]^0xa7, arg=programa[pc+1]^0x5c;
        switch(op) {
        case 0x31:
            if(arg>=n) return 0;
            a=(unsigned char)(s[arg] ^ (unsigned char)(estado>>((arg%4)*8)));
            break;
        case 0x52: a=(unsigned char)(a+arg); break;
        case 0x73:
            if(arg<1 || arg>7) return 0;
            a=(unsigned char)((a<<arg)|(a>>(8-arg))); break;
        case 0x94: erro|=(uint32_t)(a ^ (arg^0xd3)); break;
        case 0xb5: estado=(estado ^ a)*UINT32_C(1103515245)+UINT32_C(12345); break;
        case 0xe6: return (erro==0) & (estado==UINT32_C(1986300283));
        default: return 0;
        }
    }
    return 0;
}

int main(void) {
    unsigned char senha[128];
    puts("COFRE DIGITAL - NIVEL 4 (EXPERT)");
    puts("Laboratorio educativo de engenharia reversa");
    printf("Digite a senha: ");
    fflush(stdout);
    if (!fgets((char *)senha,sizeof senha,stdin)) return 2;
    size_t n=strcspn((char *)senha,"\r\n");
    senha[n]=0;
    int ok=validar(senha,n);
    puts(ok ? "ACESSO LIBERADO! Voce abriu o cofre." : "ACESSO NEGADO! Senha incorreta.");
    puts("Pressione ENTER para sair.");
    getchar();
    return ok ? 0 : 1;
}
