#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct dugum
{
    int data;
    char  kelime[20];
    struct dugum * next;
};
typedef struct dugum node;

void ekranaBas(node * r)
{
    int i = 1;
    while(r != NULL)
    {
        printf("%d. %s - %d\n", i, r -> kelime, r -> data);
        r = r -> next;
        i++;
    }
}

int say(node * r)
{
    node * iter = r;
    int sayi = 1;
    while(iter -> next != NULL)
    {
        if(strcmp(r -> kelime, iter -> next -> kelime) == 0)
            sayi++;
        iter = iter -> next;
    }
    return sayi;
}

node * sil(node *r, char x[20])
{
    node * temp;
    node * iter = r;
    if(strcmp(r -> kelime, x) == 0)
    {
        temp = r;
        r = r -> next;
        free(temp);
        return r;
    }

    while(iter -> next != NULL && strcmp(iter -> next -> kelime, x) != 0)
    {
        iter = iter -> next;
    }

    if(iter -> next == NULL)
    {
        printf("Sayi listede bulunamadi.\n");
        return r;
    }

    temp = iter -> next;
    iter -> next = iter -> next -> next;
    free(temp);
    return r;
}

void ekle(node *r, char kelime[20]){

    if(r -> next == NULL){
        strcpy(r -> kelime, kelime);
    }
    else{
        node * iter = r;
        while(iter -> next != NULL)
            iter = iter -> next;
        iter -> next = malloc(sizeof(node));
        strcpy(iter -> next -> kelime, kelime);
        iter -> next -> next = NULL;
    }
}

node * basaEkleme(node * r, int x, char k[20])
{
    node * temp;
    temp = (node *)malloc(sizeof(node));
    temp -> data = x;
    strcpy(temp -> kelime, k);
    temp -> next = r;
    return temp;
}

node * arayaEkleme(node * r, int x, char k[20])
{
    node * iter;
    iter = r;
    while(iter -> next != NULL && iter -> next -> data >= x)
        iter = iter -> next;
    node * temp = malloc(sizeof(node));
    temp -> next = iter -> next;
    iter -> next = temp;
    temp -> data = x;
    strcpy(temp -> kelime,k);
    return r;
}

node * sonaEkleme(node * r, int x, char k[20])
{
    node * temp = malloc(sizeof(node));
    temp -> data = x;
    strcpy(temp -> kelime,k);
    node * iter = r;
    while(iter -> next != NULL)
        iter = iter -> next;
    iter -> next = temp;
    temp -> next = NULL;
    return r;
}

node * siraliEkleme(node *r, int x, char k[20])
{
     if(r -> data == NULL) //linkedlistin ici bossa
    {
        r -> data = x;
        strcpy(r -> kelime,k);
        r -> next = NULL;
        return r;
      }

     if(r -> data < x){ //ilk elemandan küçük olma durumu
        return basaEkleme(r, x, k);
    }

    node * iter = r;
    while(iter -> next != NULL)
        iter = iter -> next;
    if(iter -> data >= x)
        return sonaEkleme(r, x, k);

    return arayaEkleme(r, x, k);
}

int main(){
    node * root;   node * iter;   node * liste;   node * bos;
    root = malloc(sizeof(node));
    iter = root;
    liste = malloc(sizeof(node));
    liste -> next = NULL;
    bos = malloc(sizeof(node));
    bos -> next = NULL;
    bos -> data = NULL;

    FILE * words = fopen("words.txt", "r+");
    char * karakter = (char*)malloc(sizeof(char)*100);
    if(words == NULL){
        printf("words.txt dosyasi bulunamadi!");
        return 0;
    }else{
        printf("DOSYA BULUNDU\n");
        while(!feof(words)){
            fscanf(words, "%s", karakter);
            strcpy(iter -> kelime, karakter);
            if(!feof(words)){
                iter -> next = malloc(sizeof(node));
                iter = iter -> next;
            }
        }
        iter -> next = NULL;
    }
    fclose(words);

    while(root != NULL){
        int sayi = say(root);
        ekle(liste,root->kelime);
        bos = siraliEkleme(bos, sayi, root -> kelime);
        for(int i=0; i<sayi; i++)
            root = sil(root,liste -> kelime);
    }
    ekranaBas(bos);
}

