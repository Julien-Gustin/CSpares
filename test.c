#include <stdio.h>
#include <stdlib.h>

typedef enum{
   Julien,
   Ilias
}ELEVE;


int main() {

   ELEVE juju = Julien;
   printf("J %d\n", juju);
   // printf("I %d\n", test->Ilias);
   //
   // test->Julien++;
   // printf("J %d\n", ELEVE->Julien);
   // printf("I %d\n", ELEVE->Ilias);

   return 0;
}
