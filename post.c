#include <stdio.h>
#include <curl/curl.h>

size_t write_callback(char *ptr, size_t size, size_t count, void *userdata)
{
    // Fonction utlisée par curl
    return size * count;
}

int post(char* login, char* mdp, char* urlCible)
{
    CURL *curl;
    CURLcode res;

    curl = curl_easy_init();
    if (curl)
    {
        // Il faut modifier l'URL sur laquelle on passe la requête ici.
        const char *url = "localhost:8888/gsbsecu/public/login";

        // Génération de la requête
        char postFirstPart[100] = "login=";
        strcat(postFirstPart, login);
        char postSecondPart[6] = "&mdp=";
        strcat(postFirstPart, postSecondPart);
        strcat(postFirstPart, mdp);
        const char *post_data = postFirstPart;

        // Set URL
        curl_easy_setopt(curl, CURLOPT_URL, url);
        // Set HTTP POST
        curl_easy_setopt(curl, CURLOPT_POST, 1L);
        // Mettre les data dans la requête POST
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, post_data);
        // Configuration pour suivre les redirections
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        // permet de gérer la redirection
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);

        // On exécute la requête
        res = curl_easy_perform(curl);

        // Si y'a une erreur on print l'erreur
        if (res != CURLE_OK)
        {
            fprintf(stderr, "Erreur curl : %s\n", curl_easy_strerror(res));
        }
        // Sinon on print le résultat
        else
        {
            // Obtention du code HTTP
            long http_code = 0;
            res = curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);

            if (res == CURLE_OK)
            {
                printf("Code HTTP : %ld\n", http_code);
                // Valeurs choisies car j'ai remarqué que 500 = réussie et 200 = retour vers l'index
                // On pourrait les modifier selon le serveur qu'on vise
                if (http_code == 500 || http_code == 200)
                {
                    char *final_url = NULL;
                    res = curl_easy_getinfo(curl, CURLINFO_EFFECTIVE_URL, &final_url);
                    if (res == CURLE_OK)
                    {
                        // On print l'url de la redirection
                        printf("Redirection vers : %s\n", final_url);

                        // Si on est redirigé sur l'URL qu'on ciblait, ça veut dire qu'on est connecté
                        if (strcmp(final_url, urlCible) == 0)
                        {
                            // Affichage des infos et fin du programme
                            printf("Les identifiants sont\nlogin : %s\nmot de passe : %s.", login, mdp);
                            exit(0);
                        }
                        
                    }
                    else
                    {
                        fprintf(stderr, "Erreur lors de la récupération de l'URL de redirection : %s\n", curl_easy_strerror(res));
                    }
                }
            }
            else
            {
                fprintf(stderr, "Erreur lors de la récupération du code de réponse HTTP : %s\n", curl_easy_strerror(res));
            }
        }

        curl_easy_cleanup(curl);
    }

    return 0;
}
