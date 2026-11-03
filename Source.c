
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct Polinom {
    int koef;
    int exp;
    struct Polinom* next;
} Polinom;

Polinom* noviClan(int koef, int exp);
void dodajClan(Polinom** head, int koef, int exp);
void ucitaj(char* ime, Polinom** P, Polinom** Q);
void ispisi(Polinom* P);
Polinom* zbroji(Polinom* P, Polinom* Q);
Polinom* pomnozi(Polinom* P, Polinom* Q);
void oslobodi(Polinom* P);

int main() {

    Polinom* P = NULL;
    Polinom* Q = NULL;
    Polinom* Z = NULL;
    Polinom* M = NULL;

    ucitaj("polinomi.txt", &P, &Q);

    printf("Prvi polinom: ");
    ispisi(P);

    printf("Drugi polinom: ");
    ispisi(Q);

    Z = zbroji(P, Q);

    printf("Zbroj polinoma: ");
    ispisi(Z);

    M = pomnozi(P, Q);

    printf("Umnozak polinoma: ");
    ispisi(M);

    oslobodi(P);
    oslobodi(Q);
    oslobodi(Z);
    oslobodi(M);

    return 0;
}

Polinom* noviClan(int koef, int exp) {

    Polinom* novi = malloc(sizeof(Polinom));

    if (novi == NULL)
        return NULL;

    novi->koef = koef;
    novi->exp = exp;
    novi->next = NULL;

    return novi;
}

void dodajClan(Polinom** head, int koef, int exp) {

    Polinom* novi = noviClan(koef, exp);

    if (novi == NULL)
        return;

    if (*head == NULL || (*head)->exp < exp) {

        novi->next = *head;
        *head = novi;
    }
    //provjera je li trenutni element liste ima isti koeficijent kao sto ima novi element liste
    //ako ima novi koeficijent postaje zbroj ta 2 koeficijenta

    else if ((*head)->exp == exp) {

        (*head)->koef += koef;
        free(novi);
    }
    else {

        Polinom* temp = *head;

        while (temp->next != NULL && temp->next->exp > exp) {
            temp = temp->next;
        }

        if (temp->next != NULL && temp->next->exp == exp) {
            temp->next->koef += koef;
            free(novi);
        }
        else {
            novi->next = temp->next;
            temp->next = novi;
        }
    }
}
void ucitaj(char* ime, Polinom** P, Polinom** Q) {

    FILE* f = fopen(ime, "r");

    if (f == NULL) {
        printf("Greska pri otvaranju datoteke!");
        return;
    }

    int koef, exp;
    int brojac = 0;

    while (fscanf(f, "%d %d", &koef, &exp) == 2) {

        if (brojac < 3) {
            dodajClan(P, koef, exp);
        }
        else {
            dodajClan(Q, koef, exp);
        }

        brojac++;
    }

    fclose(f);
}

void ispisi(Polinom* P) {

    if (P == NULL) {
        printf("0\n");
        return;
    }

    while (P != NULL) {

        printf("%dx^%d ", P->koef, P->exp);

        P = P->next;
    }

    printf("\n");
}

Polinom* zbroji(Polinom* P, Polinom* Q) {

    Polinom* R = NULL;

    /*
    while (P != NULL || Q != NULL) {
        provjera je li P->potencija == Q-<potencija
            novi element(p->koeficijent+q-<koeficijent. p->potencija )
            oba pokazivaca na liste pomaknuti udesno
        provjera je li P->potencija > q->potencija
        provjera je li P-<potencija <q->potencija
    }
    
    */ 

    while (P != NULL) {
        dodajClan(&R, P->koef, P->exp);
        P = P->next;
    }

    while (Q != NULL) {
        dodajClan(&R, Q->koef, Q->exp);
        Q = Q->next;
    }

    return R;
}

Polinom* pomnozi(Polinom* P, Polinom* Q) {

    Polinom* R = NULL;

    Polinom* temp1 = P;

    while (temp1 != NULL) {

        Polinom* temp2 = Q;

        while (temp2 != NULL) {

            int koef = temp1->koef * temp2->koef;
            int exp = temp1->exp + temp2->exp;

            dodajClan(&R, koef, exp);

            temp2 = temp2->next;
        }

        temp1 = temp1->next;
    }

    return R;
}

void oslobodi(Polinom* P) {

    while (P != NULL) {

        Polinom* temp = P;
        P = P->next;

        free(temp);
    }
}
