#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*On defini la taille maximal des donnees*/
#define MAX_SIZE 100
/*On defini le code d'erreur qui sera utiliser pour signaler une erreur*/
#define ERROR_CODE -1

/*On defini la structure Student*/
typedef struct
{
	char name[50];
	char first_name[50];
	int year;
	int month;
	int day;
	char filiere[50];
	char level[50];
} Student;


/*On defini la structure Subject*/
typedef struct
{
	char name[50];
	int coef;
} Subject;

/*On defini la structure Note*/
typedef struct
{
	int subject_id;
	int student_id;
	int note;
} Note;

/*On defini la structure Moyenne*/
typedef struct
{
	int nb_subject;
	int note_total;
	int coef_total;
	float moyenne;
} Moyenne;

/*Fonction permettant d'avoir la valeur en entier d'un nombre de type char*/
int char_to_int(char number[MAX_SIZE]);

/*Fonction qui demande l'utilisateur d entree un entier*/
int get_int(void);

/*Fonction qui permet d'obtenir un entier dans un interval donnee*/
int get_int_in(int min, int max);

/*Fonction qui permet d'ajouter un etudiant*/
void add_student(Student students[MAX_SIZE], int next_position_student);

/*Fonction qui permet d'ajouter une matiere*/
void add_subject(Subject subjects[MAX_SIZE], int next_position_subject);

/*Fonction qui permet de choisir une matiere*/
int choose_subject(Subject subjects[MAX_SIZE], int nb_subject);

/*Fonction qui permet de choisir un etudiant*/
int choose_student(Student students[MAX_SIZE], int nb_student);

/*Fonction qui permet d'inscrire un etudiant dans une matiere*/
void signin_subject(Note notes[MAX_SIZE], int next_position_note, int subject_id, int student_id);

/*Fonction qui permet d'assigner une note a un etudiant*/
void add_note(Note notes[MAX_SIZE], int next_position_note, int subject_id, int student_id);

void show_student(int student_id, Student students[MAX_SIZE], Subject subjects[MAX_SIZE], Note notes[MAX_SIZE], int next_position_note);

/*Fonction qui permet de sauvegarder les donnees d'un etudiant*/
void save(Student students[MAX_SIZE], Subject subjects[MAX_SIZE], Note notes[MAX_SIZE], int student_id, int next_position_note);

/*Fonction principale du programme*/
int main(int argc, char const *argv[])
{
	/*On declare un ttableau students qui representera les etudiants*/
	Student students[MAX_SIZE];
	/*On declare une tableau subjects qui representera les matieres*/
	Subject subjects[MAX_SIZE];
	/*On declare un tableau notes qui representera les notes*/
	/* des differentes matieres de chaque etudiant*/
	Note notes[MAX_SIZE];
	/*On declare une variable option qui stockera un choix utilisateur*/
	int option = 0;
	/*On delcare une variable entry1 qui stockera une entree clavier*/
	int entry1;
	/*On delcare une variable entry2 qui stockera une entree clavier*/
	int entry2;
	/*On delcare une variable next_position_student qui nous permettra*/
	/* de connaitre la prochaine position libre dans le tableau students*/
	int next_position_student = 0;
	/*On delcare une variable next_position_subject qui nous permettra*/
	/* de connaitre la prochaine position libre dans le tableau subjects*/
	int next_position_subject = 0;
	/*On delcare une variable next_position_note qui nous permettra*/
	/* de connaitre la prochaine position libre dans le tableau notes*/
	int next_position_note = 0;
	/*On affiche les indications a l'utilisateur*/
	printf("Programme qui enregistre des etudiants\n");
	printf("Permet d'enregister:\n");
	printf("Max %d etudiants\n", MAX_SIZE);
	printf("Max %d subjects\n", MAX_SIZE);
	printf("Max %d notes\n", MAX_SIZE);
	printf("--------------------\n");
	/*On affiche les differents commande que l'utilisateur peut utiliser*/
	printf("Command:\n");
	printf("\t0 pour quitter\n");
	printf("\t1 pour ajouter un etudiant\n");
	printf("\t2 pour ajouter une matiere\n");
	printf("\t3 pour ajouter une matiere a un etudiant\n");
	printf("\t4 pour donner/changer une note a un etudiant\n");
	printf("\t5 pour afficher les infos d'un etudiant\n");
	printf("\t10 pour afficher les infos d'un etudiant\n");
	while (1)
	{
		printf("choix (entier uniquement): ");
		/*On recupere une entree de la base decimal*/
		option=get_int();
		/*On va faire une analyse de cas*/
		switch(option)
		{
			case 1:
				/*On demande a l'utilisateur d'ajouter un etudiant*/
				add_student(students, next_position_student);
				/*Apres on incremente la prochaine position libre du tableau students*/
				next_position_student++;
				break;
			case 2:
				/*On demande a l'utilisateur d'ajouter une matiere*/
				add_subject(subjects, next_position_subject);
				/*Apres on incremente la prochaine position libre du tableau subjects*/
				next_position_subject++;
				break;
			case 3: case 4:/*Ici on evalu le cas 3 et 4 en une fois*/
				/*On demande a l'utilisateur de choisir une matiere*/
			    entry1 = choose_subject(subjects, next_position_subject);
			    /*On demande a l'utilisateur de choisir un etudiant*/
				entry2 = choose_student(students, next_position_student);
				/*On verifie si les fonctions n'on pas renvoyer d'erreur*/
				if (entry1 != ERROR_CODE & entry2 != ERROR_CODE)
				{
					/*On execute une insctruction pour chaque cas*/
					if (option == 3)
					{
						/*On inscris un etudiant dans une matiere*/
						signin_subject(notes, next_position_note, entry1, entry2);
						/*Apres on incremente la prochaine position libre du tableau notes*/
						next_position_note++;
					}
					else
					{
						/*On demande a l'utilisateur d'assigner une note a l'etudiant selectionner*/
						add_note(notes, next_position_note, entry1, entry2);
					}
				}
				break;
            case 5:
                /*On demande a l'utilisateur de choisir un etudiant*/
				entry1 = choose_student(students, next_position_student);
				/*On verifie si la fonction choose_student n'a pas renvoyer d'erreur*/
				if (entry1 != ERROR_CODE)
				{
				    show_student(entry1, students, subjects, notes, next_position_note);
				}
				break;
			case 10:
				/*On demande a l'utilisateur de choisir un etudiant*/
				entry1 = choose_student(students, next_position_student);
				/*On verifie si la fonction choose_student n'a pas renvoyer d'erreur*/
				if (entry1 != ERROR_CODE)
				{
					/*On sauvegarde les donnees de l'etudiant selectionner*/
					save(students, subjects, notes, entry1, next_position_note);
				}
				break;
		}
		if (option == 0)
		{
			break;
		}
	}
	printf("Merci d'avoir utiliser notre programme\n");
	return 0;
}

int char_to_int(char number[MAX_SIZE])
{
	/*On declare les elements de la base decimal*/
    char snumber[] = "0123456789";
    /*On stocke la longueur des elements de la base decimal*/
    int length_snumber = strlen(snumber);
    /*On initie inumber a ERROR_CODE*/
    /*Le ERROR_CODE permettra de savoir si un nombre a ete trouver ou pas*/
    int inumber = ERROR_CODE;
    /*On stocke la longueur du supposer nombre*/
    int length_number = strlen(number);
    /*On parcours les elements du supposer nombre*/
    for(int i = 0; i < length_number; ++i)
    {
    	/*On parcoure les element du de la base decimal*/
    	for(int ii = 0; ii < length_snumber; ++ii)
    	{
    		/*On verifie si l element du suppose nombre est un nombre*/
    		if(number[i] == snumber[ii])
    		{
    			/*Comme il est entier*/
    			/*On met inumber a 0 si ERROR_CODE enfin de retrouver le nombre chercher*/
    			if (inumber == ERROR_CODE)
    				inumber = 0;
    			/*On ajoute chaque element du nombre a partir de l unite*/
    			/*Exemple: 1 => 12 => 123 => 1234*/
    			inumber = inumber * 10 + ii;
    			/*On arrete le parcour d element de la base decimal*/
    			/*Enfin de passer a l element suivant du suppose nombre*/
    			break;
    		}
    	}
    }
    /*On renvoi le resultat final*/
    return inumber;
}


int get_int(void)
{
	/*Le ERROR_CODE permettra de savoir si un nombre a ete trouver ou pas*/
	int number = ERROR_CODE;
	/*Variable qui stocke l'entree utilisateur*/
	char entry[MAX_SIZE] = {};
	/*Tant qu'on a pas d'entier on repete le processus*/
	while(1)
	{
		scanf("%s", entry);
		/*On fait la conversion de l'entree en entier*/
		number=char_to_int(entry);
		if(number == ERROR_CODE)
        {
            printf("Please entrer un entier: ");
        }
        else
            break;
	}
	/*On retourne a la fin l'entier recuperer*/
	return number;
}

int get_int_in(int min, int max)
{
    int x;
    do
    {
        x = get_int();
        if(x == ERROR_CODE | x < min | x > max)
        {
            printf("Ce nombre doit etre compris entre %i et %i: ", min, max);
        }
        else
            break;
    } while(1);
}

void add_student(Student students[MAX_SIZE], int next_position_student)
{
	/*On affiche les consignes a l'utilisateur*/
    printf("Entrer son nom: ");
    scanf("%s", &students[next_position_student].name);
	printf("Entrer son prenom: ");
	scanf("%s", &students[next_position_student].first_name);
	printf("Entrer sa date de naissance\n");
	printf("\tJour (entier uniquement): ");
	students[next_position_student].day = get_int_in(1,31);
	printf("\tMois (entier uniquement): ");
	students[next_position_student].month = get_int_in(1,12);
	printf("\tAnnee (entier uniquement): ");
	students[next_position_student].year = get_int();
	printf("Entrer sa filiere: ");
	scanf("%s", &students[next_position_student].filiere);
	printf("Entrer son level: ");
	scanf("%s", &students[next_position_student].level);
	printf("Etudiant enregistree avec success\n");
}

void add_subject(Subject subjects[MAX_SIZE], int next_position_subject)
{
	/*On affiche les consignes a l'utilisateur*/
    printf("Entrer le nom de la matiere: ");
    scanf("%s", &subjects[next_position_subject].name);
	printf("Entrer son coef (entier uniquement): ");
	subjects[next_position_subject].coef = get_int();
	printf("Matiere enregistree avec success\n");
}

int choose_subject(Subject subjects[MAX_SIZE], int nb_subject)
{
	/*On verifie s'il existe au moins une matiere*/
	/*Si oui nb_subject>0*/
    if (nb_subject)
    {
        int i;
        int entry = 0;
        /*On affiche les id des matieres suivi de leur nom*/
		for (i = 0; i < nb_subject; i++)
		{
			printf("%d: %s\n", i, &subjects[i].name);
		}
		/*On demande a l'utilisateur de selectionner une matiere*/
		/*Tant que cette matiere n'est pas dans la liste, il recommancera*/
		do
        {
            printf("Selectionner la matiere (entier uniquement): ");
            entry = get_int();
        }
        while(entry >= i | entry < 0);
        return entry;
    }
	else
    {
        printf("Aucune matiere disponible\n");
        /*On retourne un code d'erreur*/
        return ERROR_CODE;
    }
}

int choose_student(Student students[MAX_SIZE], int nb_student)
{
	if (nb_student)
	{
		int i;
		int entry=0;
		/*On affiche les id des etudiants suivi de leur nom*/
		for (i=0;i<nb_student;i++)
		{
			printf("%d: %s\n", i, &students[i].name);
		}
		/*On demande a l'utilisateur de selectionner un etudiant*/
		/*Tant que cet etudiant n'est pas dans la liste, il recommancera*/
		do
        {
            printf("Selectionner l' etudiant (entier uniquement): ");
			entry = get_int();
        }
        while(entry >= i);
        return entry;
	}
	else
	{
		/*On retourne un code d'erreur*/
		printf("Aucun etudiant disponible\n");
		return ERROR_CODE;
	}
}

void signin_subject(Note notes[MAX_SIZE], int next_position_note, int subject_id, int student_id)
{
	/*On cree une structure note avec l'id de la matiere et l'id de l'etudiant*/
	/*Avec une note de 0 par defaut*/
	notes[next_position_note].subject_id = subject_id;
	notes[next_position_note].student_id = student_id;
	notes[next_position_note].note = 0;
	printf("Matiere ajouter avec success\n");
}

void add_note(Note notes[MAX_SIZE], int nb_note, int subject_id, int student_id)
{
	/*On parcours le tableau notes*/
	for (int i=0;i<nb_note;i++)
	{
		/*On verifie si la note correspond a la matiere et a l'etudiant chercher*/
		/*Si la donnee note voulu de l'etudiant est trouver, on demande a l'utilisateur d'assigner une note*/
		if (notes[i].subject_id == subject_id & notes[i].student_id == student_id)
		{
			printf("Entrer la note (entier uniquement): ");
			notes[i].note = get_int();
			printf("Note enregistree avec success\n");
			break;
		}
	}
}

void show_student(int student_id, Student students[MAX_SIZE], Subject subjects[MAX_SIZE], Note notes[MAX_SIZE], int next_position_note)
{
    Moyenne moyenne;
    moyenne.nb_subject=0;
    moyenne.note_total=0;
	moyenne.coef_total=0;
	int subject_id;
	printf("Information de %s:\n", students[student_id].name);
	printf("\tNom: %s\n", students[student_id].name);
	printf("\tPrenom: %s\n", students[student_id].first_name);
	printf("\tDate de naissance: %d-%d-%d\n", students[student_id].year, students[student_id].month, students[student_id].day);
	printf("\tFiliere: %s\n", students[student_id].filiere);
	printf("\tNiveau: %s\n", students[student_id].level);
	printf("\tMatricule: %010d\n", student_id);
	printf("Note:\n");
	/*On parcours le tableau notes*/
	for (int i=0;i<next_position_note;i++)
	{
		/*On verifie si la note correspond a l'etudiant chercher*/
		if (notes[i].student_id == student_id)
		{
			subject_id = notes[i].subject_id;
			moyenne.note_total += (notes[i].note*subjects[subject_id].coef);
			moyenne.nb_subject++;
			moyenne.coef_total += subjects[subject_id].coef;
			printf("\t%s: %d\n", subjects[subject_id].name, notes[i].note);
		}
	}
	/*Si moyenne.coef_total=0, on le renvoie a 1, car on peut pas diviser par 0*/
	if(moyenne.coef_total==0)
		moyenne.coef_total=1;
	moyenne.moyenne = (moyenne.note_total/moyenne.coef_total);
	printf("Moyenne: %d/%d = %.02f\n", moyenne.note_total, moyenne.coef_total, moyenne.moyenne);
}

void save(Student students[MAX_SIZE], Subject subjects[MAX_SIZE], Note notes[MAX_SIZE], int student_id, int next_position_note)
{
	int subject_id;
	FILE* file = NULL;
	file = fopen("data.txt", "a+");
	if (file == NULL)
	{
		printf("Error open file\n");
	}
	else
	{
		fprintf(file, "Information de %s:\n", students[student_id].name);
		fprintf(file, "\tNom: %s\n", students[student_id].name);
		fprintf(file, "\tPrenom: %s\n", students[student_id].first_name);
		fprintf(file, "\tDate de naissance: %d-%d-%d\n", students[student_id].year, students[student_id].month, students[student_id].day);
		fprintf(file, "\tFiliere: %s\n", students[student_id].filiere);
		fprintf(file, "\tNiveau: %s\n", students[student_id].level);
		fprintf(file, "\tMatricule: %010d\n", student_id);
		fprintf(file, "Note:\n");
		/*On declare une variable moyenne qui stockera la moyenne d'un etudiant*/
        Moyenne moyenne;
		moyenne.nb_subject=0;
		moyenne.note_total=0;
		moyenne.coef_total=0;
		/*On parcours le tableau notes*/
		for (int i=0;i<next_position_note;i++)
		{
			/*On verifie si la note correspond a l'etudiant chercher*/
			if (notes[i].student_id == student_id)
			{
				subject_id = notes[i].subject_id;
				moyenne.note_total += (notes[i].note*subjects[subject_id].coef);
				moyenne.nb_subject++;
				moyenne.coef_total += subjects[subject_id].coef;
				fprintf(file, "\t%s: %d\n", subjects[subject_id].name, notes[i].note);
			}
		}
		/*Si moyenne.coef_total=0, on le renvoie a 1, car on peut pas diviser par 0*/
		if(moyenne.coef_total==0)
			moyenne.coef_total=1;
		moyenne.moyenne = (moyenne.note_total/moyenne.coef_total);
		fprintf(file, "Moyenne: %d/%d = %.02f\n", moyenne.note_total, moyenne.coef_total, moyenne.moyenne);
		fclose(file);
		printf("Information sauvegarder dans un fichier\n");
	}
}
