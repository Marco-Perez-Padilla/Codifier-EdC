
#include "program.h"

int main(int argc, char* argv[]) {
  Program program(argv[1]); 
  program.Write("binary.txt"); 
  program.Format("binary.txt", argv[2]);
  return 0;
}
