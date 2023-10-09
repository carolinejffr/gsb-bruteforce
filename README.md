# gsb-bruteforce
Outil pour tester la sécurité du projet gsb2sio
## Quel est ce projet ?
Il s'agit d'un programme en C qui sert à tester notre site gsb.  
Le programme est séparé en deux fichiers .c :  
* generator.c génère une suite de 5 caractères qui sert de mot de passe
* post.c utilise ce mot de passe et tente de se connecter au site en envoyant une requête POST au formulaire, en utilisant libCurl.
Le programme utilise les codes HTTP et les redirections d'URL pour savoir s'il a réussi à se connecter ou non.
Si un mot de passe est trouvé, le programme notifie l'utilisateur.
## Utilisation
Compilez le code avec votre compiler préféré. Il vous faut les outils de développement en C.  
Vous aurez aussi besoin de [la bibliothèque libcurl](https://curl.se/libcurl/).  
Par exemple :
`clang generator.c -lcurl EmplacementDeLibcurl`  
Puis, entrez le nom d'utilisateur, ainsi que l'adresse à cibler.
Dans notre cas ; `http://localhost:8888/gsbsecu/public/selection`
## Notes
Ce programme est un programme de bruteforce créé et utilisé dans un cadre scolaire.
Il ne doit pas être utilisé dans d'autres conditions et ne doit pas être détourné de son utilisation d'origine.
Je me dédouane de toute responsabilité quand à l'utilisation de ce programme.
