# include <stdlib.h>
# include <stdio.h>
# include <string.h>

#define N 50

struct noeuds {
    char Lettre;  // Le caractère.
    int frequence; // Frequence de la lettre.
    struct noeuds* gauche, * droite;
};

struct noeud {
    unsigned taille; // nombre d’éléments de l'arbre.
    int mem; // Nombre maximum d'éléments dans le tableau (Memory).
    struct noeuds ** tab; // le tableau de pointeurs des noeuds (double pointeur).
};

        // Retourner le parent du noeud i
        int parent(int i) {
            return (i - 1) / 2;}
        // Retourner le fils gauche du noeud i
        int gauche(int i) {
            return 2 * i + 1;}
        // Retourner le fils droite du noeud i
        int droite(int i) {
            return 2 * i + 2;}
        // La racine de l'arbre
        int racine(struct noeud* x) {
            return 0;}
        // indice du dernier élément
        int dernier(struct noeud* x) {
            return x->taille - 1;}
        // nb d’éléments dans l’arbre
        int tailleTas(struct noeud* x) {
            return x->taille;}

//La fonction permettant d'allouer un nouveau noeud de tas-min.
struct noeuds* NouveauNoeud(char Lettre, int frequence)
{
    struct noeuds* ta = (struct noeuds*)malloc(sizeof(struct noeuds));

    ta->gauche = ta->droite = NULL;
    ta->Lettre = Lettre;
    ta->frequence = frequence;

    return ta;
}

//La fonction permettant de créer un tas minimum.
struct noeud* TasMin(int mem)
{
    struct noeud* tas = (struct noeud*)malloc(sizeof(struct noeud));

    tas->taille = 0;
    tas->mem = mem;
    tas->tab = (struct noeuds**)malloc(tas->mem * sizeof(struct noeuds*));

    return tas;
}

//La fonction permettant d'échanger deux noeuds de tas-min.
void Echangenoeud(struct noeuds** a, struct noeuds** b)
{
    struct noeuds* t = *a;
    *a = *b;
    *b = t;
}

//La fonction standard entasserMin.
void entasserMin(struct noeud *x, int i) {
    int min; // l'indice de la valeur min dans le tableu
    min = i;
    if ((gauche(i) < tailleTas(x)) && (x->tab[gauche(i)]->frequence < x->tab[min]->frequence) )
        min = gauche(i);
    if ((droite(i) < tailleTas(x)) && (x->tab[droite(i)]->frequence < x->tab[min]->frequence) )
        min = droite(i);
    if (min != i)
    {
        Echangenoeud(&x->tab[min], &x->tab[i]);
        entasserMin(x, min);
    }
}

//La fonction standard extraire-Tas-Min.
struct noeuds* extraireTasMin(struct noeud* x)
{
    struct noeuds* tas = x->tab[0]; // Initialistation du tas : ...
    x->tab[0] = x->tab[dernier(x)];

    -- x->taille; // Decrementation de la taille
    entasserMin(x, 0);

    return tas;
}

//La fonction standard inserer-Tas-Min
void insererTasMin(struct noeud* x, struct noeuds* y)
{
    ++x->taille;  // Incrementation de la taille
    int i = dernier(x);

    while (i && y->frequence < x->tab[parent(i)]->frequence)
    {
        x->tab[i] = x->tab[parent(i)];
        i = parent(i);
    }
    x->tab[i] = y;
}

//La fonction standard permettant de construire un tas min.
void Construirenoeud(struct noeud* x)
{
    int n = dernier(x);
    int i;

    for (i = parent(n); i >= 0; --i)
        entasserMin(x, i);
}

//La fonction permettant d'initialiser et créer un tas min.
struct noeud* construireTasMin(char Lettre[], int frequence[], int taille)
{
    struct noeud* x = TasMin(taille);

    for (int i = 0; i < taille; ++i)
        x->tab[i] = NouveauNoeud(Lettre[i], frequence[i]);

    x->taille = taille;
    Construirenoeud(x);

    return x;
}

//La fonction principale qui construit l'arbre Huffman.
struct noeuds* ArbreHuffman(char Lettre[], int frequence[], int taille)
{
    struct noeuds* gauche, * droite, * Parent;
    struct noeud* x = construireTasMin(Lettre, frequence, taille);

    while (x->taille != 1)  // Tester si il est de taille 1
    {

        gauche = extraireTasMin(x);
        droite = extraireTasMin(x);

        Parent = NouveauNoeud('$', gauche->frequence + droite->frequence);

        Parent->gauche = gauche;
        Parent->droite = droite;

        insererTasMin(x, Parent);
    }
    return extraireTasMin(x);
}
//Fonctions permettent de calculer la frequence totale et d'afficher le resultat.
void Somme_Fre(int tab[], int n)
{
    int somme = 0;
    for (int i = 0; i < n; i++)
        somme = somme + tab[i];

    printf(" La Frequence totale =  %d  | \n", somme);
}

void Sg(int tab[], int Ntab[], int n)
{
    int i;
    for (i = 0; i < n; ++i) {
        tab[i] = Ntab[i];
    }
}

//Fonctions permettent d'afficher un tableau.
void AfficherTab(int tab[], int n)
{
    int i;
    printf("      ");

    for (i = 0; i < n; ++i) {
        printf("%d", tab[i]);
    }

    printf("\n");
}

//Fonctions permettent de Calculer la taille d'un tableau
int Tab_Taille(char tab[])
{
    //Pour avoir la taille de la chaine
    int j;
    for (j = 0; tab[j]; j++);

    return j + 1;
}

//Fonction permettent de stocker les frequences et rederiger les lettres de la chaine Sans doublon (Calcul des frequences)
void Doublon(char tab[], int frequence[])
{
    int i, j, k;
    int c;

    for (i = 0; i < strlen(tab); i++)
    {
        c = 1;
        for (j = i + 1; tab[j] != '\0'; j++)
        {
            if (tab[j] == tab[i])
            {
                c++;
                for (k = j; tab[k] != '\0'; k++)
                {
                    tab[k] = tab[k + 1];
                    frequence[k] = frequence[k + 1];
                }
            }
        }
        frequence[i] = c;
    }
}
//Fonctions permettent d'exectuer des tests et afficher les résultats.
void AfficherCode(struct noeuds* racine, int tab[],FILE* FICH, int Parent)
{
    //---Condition sur les fils
    if (racine->gauche)
    {
        tab[Parent] = 0;
        AfficherCode(racine->gauche, tab, FICH, Parent + 1);
    }
    if (racine->droite)
    {
        tab[Parent] = 1;
        AfficherCode(racine->droite, tab, FICH, Parent + 1);
    }
    //---Condition sur les feuilles
    if (!(racine->gauche) && !(racine->droite))
    {
        printf("    %c      | ", racine->Lettre);
        AfficherTab(tab, Parent);
        fprintf(FICH, "\n%c :", racine->Lettre);
        for (int i = 0; i < Parent; ++i) {
            fflush(stdout); // Force l'affichage (vide le buffer)
            //fwrite(tab, sizeof(int), n, fichier);
            fprintf(FICH, "%d", tab[i]); // permettent d'ecrire le code dans le fichier Codebinaire_Sortie.txt
        }
    }

}

//La fonction permettant de construire un arbre Huffman
void Huffman(char Lettre[], int frequence[], int taille)
{
    struct noeuds* racine = ArbreHuffman(Lettre, frequence, taille);  // Construire un Tas min

    int tab[N], Parent = 0; // Definir le tableau et l'initiation du parent.

    FILE* fichier;
    fichier = fopen("Codebinaire_Sortie.txt", "w");

    AfficherCode(racine, tab, fichier, Parent);

    int Binaire = taille * 8; // 8 Represente un octet.
    printf("\n Taille en bits:    %d      | \n", Binaire);

    Somme_Fre(frequence, taille);
}

//La fonction permettant de Lire un fichier
char* Lirefichier(char* fichier)
{
    FILE* file = fopen(fichier, "r");
    char* code;
    size_t n = 0; // unsigned int.
    int c;

    if (file == NULL)
        return NULL;

    code = malloc(1000);

    while ((c = fgetc(file)) != EOF) //End-of-file LA FIN DE FICHIER
    {
        code[n++] = (char)c;
    }

    code[n] = '\0';

    return code;
}
/*const char* decode(struct noeuds* racine, FILE* FICH, char tab[])
{
    char* ans;
    struct noeuds* curr = racine;
    for (int i = 0; tab[i] != '\0'; i++)
    {
        if (tab[i] == '0')
            curr = curr->gauche;
        else
            curr = curr->droite;

        if (curr->gauche == NULL && curr->droite == NULL)
        {
            ans += curr->Lettre;
            curr = racine;
            for (int i = 0; tab[i] != '\0'; ++i) {
                fflush(stdout); // Force l'affichage (vide le buffer)
                //fwrite(tab, sizeof(int), n, fichier);
                fprintf(FICH, "%c", curr->Lettre); // permettent d'ecrire le code dans le fichier Codebinaire_Sortie.txt
            }
        }
    }
    return ans;
}*/

//-----------------------------------Main-----------------------------------------------
int main()
{
    char NomFichier[] = "Texte.txt";

    char *donne = malloc(N * sizeof(char)); //Alocation dynamique

    donne = Lirefichier(NomFichier); // Stockage de la chaine dans un tableau

    int* frequence = malloc(N * sizeof(int));
    Doublon(donne, frequence);

    //int taille = sizeof(donne) / sizeof(*donne);
    int taille = 0;

    printf("------------+");
    for (int i = 0; donne[i] != '\0'; i++) {
        printf("----+");
    }
    printf("\n Caractere  |");
    for(int i =0 ; donne[i] != '\0'; i++){
        printf("  %c |", donne[i]);
        taille++;
    }
    printf("\n------------+");
    for (int i = 0; donne[i] != '\0'; i++) {
        printf("----+");
    }
    printf("\n frequence  |");
    for(int i =0 ; i < taille ; i++){
        printf("  %d |", frequence[i]);
    }
    printf("\n------------+");
    for (int i = 0; i < taille; i++) {
        printf("----+");
    }


    printf("\n\n-----------+----------------------+");
    printf("\n Caractere | Huffman code binaire |");
    printf("\n-----------+----------------------+\n");
    printf("\n");

    Huffman(donne, frequence, taille);

    return 0;
}
