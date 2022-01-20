#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*On defini la taille maximal des donnees*/
#define MAX_SIZE 100
/*On defini le code d'erreur qui sera utiliser pour signaler une erreur*/
#define ERROR_CODE -1

// We define the structure student
typedef struct
{
	char name[50];
	char first_name[50];
	int year;
	int month;
	int day;
	char department[50];
	char level[50];
} Student;


// We define the structure course
typedef struct
{
	char name[50];
	int coef;
} Course;

// We define the structure note
typedef struct
{
	int course_id;
	int student_id;
	int note;
} Note;

// We define the structure average
typedef struct
{
	int nb_course;
	int note_total;
	int coef_total;
	float average;
} Average;

// This function permit to parse an integer from a string
int parse_int(char number[MAX_SIZE]);

// This function get an integer from the user
int get_int(void);

// This function permit to get an integer in a closed interval
int get_int_in(int min, int max);

// This function permit to add a new student
void add_student(Student students[MAX_SIZE], int next_position_student);

// This function permit to add a new course
void add_course(Course courses[MAX_SIZE], int next_position_course);

// This function permit to select a course
int choose_course(Course courses[MAX_SIZE], int nb_course);

// This function permit to select a student
int choose_student(Student students[MAX_SIZE], int nb_student);

// This function permit to register a student in a course
void register_course(Note notes[MAX_SIZE], int next_position_note, int course_id, int student_id);

// This function permit to assign a note to a student
void add_note(Note notes[MAX_SIZE], int next_position_note, int course_id, int student_id);

// This function permit to show the information of a student
void show_student(int student_id, Student students[MAX_SIZE], Course courses[MAX_SIZE], Note notes[MAX_SIZE], int next_position_note);

// This function permit to export the data of a student
void save(Student students[MAX_SIZE], Course courses[MAX_SIZE], Note notes[MAX_SIZE], int student_id, int next_position_note);


int main(int argc, char const *argv[])
{
	Student students[MAX_SIZE];

	Course courses[MAX_SIZE];

	Note notes[MAX_SIZE];

	int choice = 0;

	int entry1;
	int entry2;

	int next_position_student = 0;

	int next_position_course = 0;

	int next_position_note = 0;

	// We show some important information
	printf("Student Management System\n");
	printf("Max %d students\n", MAX_SIZE);
	printf("Max %d courses\n", MAX_SIZE);
	printf("Max %d notes\n", MAX_SIZE);
	printf("--------------------\n");

	// We show the menu
	printf("Command:\n");
	printf("\t0 to exit\n");
	printf("\t1 to add a student\n");
	printf("\t2 to add a course\n");
	printf("\t3 to registered a student in a course\n");
	printf("\t4 to assign a note to a student\n");
	printf("\t5 to print student's info\n");
	printf("\t10 to export student's info\n");

	while (1)
	{
		printf("Choice: ");
		
		// we get the user choice
		choice = get_int();

		// we analyze the choice
		switch(choice)
		{
			case 1:
				add_student(students, next_position_student);
				next_position_student++;
				break;
			case 2:
				add_course(courses, next_position_course);
				next_position_course++;
				break;
			case 3: case 4:/*Ici on evalu le cas 3 et 4 en une fois*/
			    entry1 = choose_course(courses, next_position_course);
				entry2 = choose_student(students, next_position_student);

				if (entry1 != ERROR_CODE & entry2 != ERROR_CODE)
				{
					if (choice == 3)
					{
						register_course(notes, next_position_note, entry1, entry2);
						next_position_note++;
					}
					else
					{
						add_note(notes, next_position_note, entry1, entry2);
					}
				}
				break;
            case 5:
				entry1 = choose_student(students, next_position_student);

				if (entry1 != ERROR_CODE)
				{
				    show_student(entry1, students, courses, notes, next_position_note);
				}
				break;
			case 10:
				entry1 = choose_student(students, next_position_student);

				if (entry1 != ERROR_CODE)
				{
					save(students, courses, notes, entry1, next_position_note);
				}
				break;
		}
		if (choice == 0)
		{
			break;
		}
	}
	printf("Thanks to use our program.\n");
	return 0;
}

int parse_int(char number[MAX_SIZE])
{
    char snumber[] = "0123456789";

    int length_snumber = strlen(snumber);

    int inumber = ERROR_CODE;

    /*On parcours les elements du supposer nombre*/
    for(int i = 0; i < strlen(number); ++i)
    {
    	for(int ii = 0; ii < length_snumber; ++ii)
    	{
    		// We verify if the character is a number
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
	int number;

	char entry[MAX_SIZE];

	while(1)
	{
		scanf("%s", entry);
		
		// We parse the user input
		number = parse_int(entry);

		// We verify if error got
		if(number == ERROR_CODE)
        {
            printf("Please enter an integer: ");
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

        // We verify if the integer is correct
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
    printf("Name: ");
    scanf("%s", &students[next_position_student].name);
	
	printf("First name: ");
	scanf("%s", &students[next_position_student].first_name);
	
	printf("Birth Date\n");
	
	printf("\tDay (integer only): ");
	students[next_position_student].day = get_int_in(1,31);
	
	printf("\tMonth (integer only): ");
	students[next_position_student].month = get_int_in(1,12);
	
	printf("\tYear (integer only): ");
	students[next_position_student].year = get_int();
	
	printf("Department: ");
	scanf("%s", &students[next_position_student].department);
	
	printf("Level: ");
	scanf("%s", &students[next_position_student].level);
	
	printf("Student recorded successfully\n");
}

void add_course(Course courses[MAX_SIZE], int next_position_course)
{
    printf("Name: ");
    scanf("%s", &courses[next_position_course].name);
	
	printf("Coef (integer only): ");
	courses[next_position_course].coef = get_int();
	
	printf("Course recorded successfully\n");
}

int choose_course(Course courses[MAX_SIZE], int nb_course)
{
	// We verify if courses present
    if (nb_course)
    {
        int i;
        int entry = 0;

        // We show a lsit of course recorded
		for (i = 0; i < nb_course; i++)
		{
			printf("%d: %s\n", i, &courses[i].name);
		}

		do
        {
            printf("Select a course (integer only): ");
            entry = get_int();
        }
        while(entry >= i | entry < 0);

        return entry;
    }
	else
    {
        printf("No course available\n");

        return ERROR_CODE;
    }
}

int choose_student(Student students[MAX_SIZE], int nb_student)
{
	if (nb_student)
	{
		int i;
		int entry=0;

		// We show the list of student recorded
		for (i=0;i<nb_student;i++)
		{
			printf("%d: %s\n", i, &students[i].name);
		}

		do
        {
            printf("Select a student (integer only): ");
			entry = get_int();
        }
        while(entry >= i);

        return entry;
	}
	else
	{
		printf("No student available\n");
		return ERROR_CODE;
	}
}

void register_course(Note notes[MAX_SIZE], int next_position_note, int course_id, int student_id)
{
	notes[next_position_note].course_id = course_id;
	notes[next_position_note].student_id = student_id;
	notes[next_position_note].note = 0;

	printf("Course recorded successfully\n");
}

void add_note(Note notes[MAX_SIZE], int nb_note, int course_id, int student_id)
{
	// We assign a note if the student has registered this course
	for (int i=0;i<nb_note;i++)
	{
		if (notes[i].course_id == course_id & notes[i].student_id == student_id)
		{
			printf("Note (integer only): ");
			notes[i].note = get_int();
			
			printf("Note recorded successfully\n");
			break;
		}
	}
}

void show_student(int student_id, Student students[MAX_SIZE], Course courses[MAX_SIZE], Note notes[MAX_SIZE], int next_position_note)
{
    Average average;
    average.nb_course = 0;
    average.note_total = 0;
	average.coef_total = 0;
	int course_id;

	printf("Information of %s:\n", students[student_id].name);
	printf("\tName: %s\n", students[student_id].name);
	printf("\tFirst name: %s\n", students[student_id].first_name);
	printf("\tBirth Date: %d-%d-%d\n", students[student_id].year, students[student_id].month, students[student_id].day);
	printf("\tDepartment: %s\n", students[student_id].department);
	printf("\tLevel: %s\n", students[student_id].level);
	printf("\tMatricule: %010d\n", student_id);
	printf("Note:\n");

	// We print the notes of the registered course and evaluate the average
	for (int i=0;i<next_position_note;i++)
	{
		if (notes[i].student_id == student_id)
		{
			course_id = notes[i].course_id;
			average.note_total += (notes[i].note * courses[course_id].coef);
			average.nb_course++;
			average.coef_total += courses[course_id].coef;

			printf("\t%s: %d\n", courses[course_id].name, notes[i].note);
		}
	}

	if(average.coef_total==0)
		average.coef_total=1;

	average.average = (average.note_total / average.coef_total);

	printf("Average: %d/%d = %.02f\n", average.note_total, average.coef_total, average.average);
}

void save(Student students[MAX_SIZE], Course courses[MAX_SIZE], Note notes[MAX_SIZE], int student_id, int next_position_note)
{
	int course_id;
	FILE* file = NULL;
	file = fopen("data.txt", "a+");

	if (file == NULL)
	{
		printf("Error open file\n");
	}
	else
	{
		fprintf(file, "Information de %s:\n", students[student_id].name);
		fprintf(file, "Name: %s\n", students[student_id].name);
		fprintf(file, "First name: %s\n", students[student_id].first_name);
		fprintf(file, "Birth Date: %d-%d-%d\n", students[student_id].year, students[student_id].month, students[student_id].day);
		fprintf(file, "Department: %s\n", students[student_id].department);
		fprintf(file, "Level: %s\n", students[student_id].level);
		fprintf(file, "Matricule: %010d\n", student_id);
		fprintf(file, "Note:\n");

		// We evaluate the
        Average average;
		average.nb_course=0;
		average.note_total=0;
		average.coef_total=0;
		/*On parcours le tableau notes*/
		for (int i=0;i<next_position_note;i++)
		{
			/*On verifie si la note correspond a l'etudiant chercher*/
			if (notes[i].student_id == student_id)
			{
				course_id = notes[i].course_id;
				average.note_total += (notes[i].note * courses[course_id].coef);
				average.nb_course++;
				average.coef_total += courses[course_id].coef;
				fprintf(file, "\t%s: %d\n", courses[course_id].name, notes[i].note);
			}
		}
		/*Si average.coef_total=0, on le renvoie a 1, car on peut pas diviser par 0*/
		if(average.coef_total==0)
			average.coef_total=1;
		average.average = (average.note_total / average.coef_total);

		fprintf(file, "Average: %d/%d = %.02f\n", average.note_total, average.coef_total, average.average);

		fclose(file);
		printf("Information sauvegarder dans un fichier\n");
	}
}
