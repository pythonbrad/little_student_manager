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
	char* name;
	char* first_name;
	int year;
	int month;
	int day;
	char* department;
	char* level;
} Student;


// We define the structure course
typedef struct
{
	char* name;
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
	int nb_courses;
	int note_total;
	int coef_total;
	float average;
} Average;

int nb_students = 0;

int nb_courses = 0;

int nb_notes = 0;

Student students[MAX_SIZE];

Course courses[MAX_SIZE];

Note notes[MAX_SIZE];

// This function permit to parse an integer from a string
int parse_int(char* number);

// This function get an integer from the user
int get_int(int length);

// This function get a string from the user
char* get_string(int length);

// This function permit to get an integer in a closed interval
int get_int_in(int min, int max);

// This function permit to add a new student
void add_student();

// This function permit to add a new course
void add_course();

// This function permit to select a course
int choose_course();

// This function permit to select a student
int choose_student();

// This function permit to register a student in a course
void register_course(int course_id, int student_id);

// This function permit to assign a note to a student
void assign_note(int course_id, int student_id);

// This function permit to show the information of a student
void print_student(int student_id, FILE* out);

// This function permit to export the data of a student
void save(int student_id);


int main(int argc, char const* argv[])
{
	int choice = 0;
	int entry1;
	int entry2;

	// We show some important information
	printf("Student Management System\n");
	printf("Max %d students\n", MAX_SIZE);
	printf("Max %d courses\n", MAX_SIZE);
	printf("Max %d notes\n", MAX_SIZE);
	printf("--------------------\n");

	while (1)
	{
		// We show the menu
		printf("Command:\n");
		printf("\t0 to exit\n");
		printf("\t1 to add a student\n");
		printf("\t2 to add a course\n");
		printf("\t3 to registered a student in a course\n");
		printf("\t4 to assign a note to a student\n");
		printf("\t5 to print student's info\n");
		printf("\t10 to export student's info\n");

		printf("Choice: ");
		
		// we get the user choice
		choice = get_int(2);

		// we analyze the choice
		switch(choice)
		{
			case 1:
				add_student();
				break;
			case 2:
				add_course();
				break;
			case 3: case 4:
			    entry1 = choose_course();
				entry2 = choose_student();

				if (entry1 != ERROR_CODE & entry2 != ERROR_CODE)
				{
					if (choice == 3)
					{
						register_course(entry1, entry2);
					}
					else
					{
						assign_note(entry1, entry2);
					}
				}
				break;
            case 5:
				entry1 = choose_student();

				if (entry1 != ERROR_CODE)
				{
				    print_student(entry1, stdout);
				}
				break;
			case 10:
				printf("In development\n");

				break;
				entry1 = choose_student();

				if (entry1 != ERROR_CODE)
				{
					save(entry1);
				}
				break;
			default:
				printf("Choice not found.\n");
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

int parse_int(char* number)
{
    int inumber = ERROR_CODE;

    for(int i = 0; i < strlen(number); ++i)
    {
    	// We verify if the character is a number
    	if(number[i] >= '0' && number[i] <= '9')
    	{
    		if (inumber == ERROR_CODE)
    			inumber = 0;

    		inumber = inumber * 10 + number[i] - '0';
    	}
    }

    return inumber;
}


int get_int(int length)
{
	int number;

	char* entry;

	while(1)
	{
		entry = get_string(length);
		
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

char* get_string(int length)
{
	char* temp = malloc(sizeof(char) * (length + 1));

	while (strcmp(temp, "\n") == 0 || strcmp(temp, "") == 0)
	{
		fgets(temp, sizeof(char) * (length + 1), stdin);

		// We remove the return line
		*(temp + length) = '\0';
	}

	return temp;
}

int get_int_in(int min, int max)
{
    int x;

    do
    {
        x = get_int(10);

        // We verify if the integer is correct
        if(x == ERROR_CODE || x < min || x > max)
        {
            printf("This integer should be between %i and %i: ", min, max);
        }
        else
            break;
    } while(1);
}

void add_student(Student* students)
{
    printf("Name: ");
    students[nb_students].name = get_string(255);
	
	printf("First name: ");
	students[nb_students].first_name = get_string(255);
	
	printf("Birth Date\n");
	
	printf("\tDay (integer only): ");
	students[nb_students].day = get_int_in(1, 31);
	
	printf("\tMonth (integer only): ");
	students[nb_students].month = get_int_in(1, 12);
	
	printf("\tYear (integer only): ");
	students[nb_students].year = get_int_in(1940, 2100);
	
	printf("Department: ");
	students[nb_students].department = get_string(255);
	
	printf("Level: ");
	students[nb_students].level = get_string(255);

	nb_students++;
	
	printf("Student recorded successfully\n");
}

void add_course(Course* courses)
{
    printf("Name: ");
    courses[nb_courses].name = get_string(255);
	
	printf("Coef (integer only): ");
	courses[nb_courses].coef = get_int_in(1, 10);

	nb_courses++;
	
	printf("Course recorded successfully\n");
}

int choose_course(Course* courses)
{
	// We verify if courses present
    if (nb_courses)
    {
        int i;
        int entry = 0;

        // We show a list of course recorded
		for (i = 0; i < nb_courses; i++)
		{
			printf("%d: %s\n", i, courses[i].name);
		}

		do
        {
            printf("Select a course (integer only): ");
            entry = get_int(2);
        }
        while(entry > i || entry < 0);

        return entry;
    }
	else
    {
        printf("No course available\n");

        return ERROR_CODE;
    }
}

int choose_student(Student* students)
{
	if (nb_students)
	{
		int i;
		int entry = 0;

		// We show the list of student recorded
		for (i = 0; i < nb_students; i++)
		{
			printf("%d: %s\n", i, students[i].name);
		}

		do
        {
            printf("Select a student (integer only): ");
			entry = get_int(3);
        }
        while(entry > i || entry < 0);

        return entry;
	}
	else
	{
		printf("No student available\n");
		return ERROR_CODE;
	}
}

void register_course(int course_id, int student_id)
{
	notes[nb_notes].course_id = course_id;
	notes[nb_notes].student_id = student_id;
	notes[nb_notes].note = 0;

	nb_notes++;

	printf("Course recorded successfully\n");
}

void assign_note(int course_id, int student_id)
{
	// We assign a note if the student has registered this course
	for (int i = 0; i < nb_notes; i++)
	{
		if (notes[i].course_id == course_id & notes[i].student_id == student_id)
		{
			printf("Note (integer only): ");
			notes[i].note = get_int(2);
			
			printf("Note recorded successfully\n");
			break;
		}
	}
}

void print_student(int student_id, FILE* out)
{
    Average average;
    average.nb_courses = 0;
    average.note_total = 0;
	average.coef_total = 0;

	int course_id;

	fprintf(out, "Information of %s:\n", students[student_id].name);
	fprintf(out, "\tName: %s\n", students[student_id].name);
	fprintf(out, "\tFirst name: %s\n", students[student_id].first_name);
	fprintf(out, "\tBirth Date: %d-%d-%d\n", students[student_id].year, students[student_id].month, students[student_id].day);
	fprintf(out, "\tDepartment: %s\n", students[student_id].department);
	fprintf(out, "\tLevel: %s\n", students[student_id].level);
	fprintf(out, "\tMatricule: %010d\n", student_id);
	fprintf(out, "Note:\n");

	// We print the notes of the registered course and evaluate the average
	for (int i = 0; i < nb_notes; i++)
	{
		if (notes[i].student_id == student_id)
		{
			course_id = notes[i].course_id;
			average.note_total += (notes[i].note * courses[course_id].coef);
			average.nb_courses++;
			average.coef_total += courses[course_id].coef;

			fprintf(out, "\t%s: %d\n", courses[course_id].name, notes[i].note);
		}
	}

	if(average.coef_total == 0)
		average.coef_total = 1;

	average.average = (average.note_total / average.coef_total);

	fprintf(out, "Average: %d/%d = %.02f\n", average.note_total, average.coef_total, average.average);
}

void save(int student_id)
{
	int course_id;

	FILE* file = NULL;
	char filename[1024] = {};
	sprintf(filename, "student_%i.txt", student_id);

	file = fopen(filename, "a+");

	if (file == NULL)
	{
		printf("Error open file\n");
	}
	else
	{
		// We print in the file
		print_student(student_id, file);

		fclose(file);

		printf("Information sauvegarder dans un fichier\n");
	}
}
