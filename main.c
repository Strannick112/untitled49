#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_NAME_LENGTH 50

struct Student {
    char surname[MAX_NAME_LENGTH];
    char name[MAX_NAME_LENGTH];
    char gender;
    int age;
    char group[MAX_NAME_LENGTH];
    int math_grade;
    int physics_grade;
    int chemistry_grade;
    struct Student *left;
    struct Student *right;
};

struct Student* create_node(char surname[], char name[], char gender, int age, char group[], int math_grade, int physics_grade, int chemistry_grade) {
    struct Student *new_node = (struct Student*)malloc(sizeof(struct Student));
    if (new_node == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    strcpy(new_node->surname, surname);
    strcpy(new_node->name, name);
    new_node->gender = gender;
    new_node->age = age;
    strcpy(new_node->group, group);
    new_node->math_grade = math_grade;
    new_node->physics_grade = physics_grade;
    new_node->chemistry_grade = chemistry_grade;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

struct Student* insert(struct Student *root, struct Student *student) {
    if (root == NULL) {
        return student;
    }
    if (student->age < root->age) {
        root->left = insert(root->left, student);
    } else {
        root->right = insert(root->right, student);
    }
    return root;
}

void print_student_info(struct Student *student) {
    printf("Surname: %s\n", student->surname);
    printf("Name: %s\n", student->name);
    printf("Gender: %c\n", student->gender);
    printf("Age: %d\n", student->age);
    printf("Group: %s\n", student->group);
    printf("Math grade: %d\n", student->math_grade);
    printf("Physics grade: %d\n", student->physics_grade);
    printf("Chemistry grade: %d\n", student->chemistry_grade);
}

void generate_random_grades(struct Student *student) {
    student->math_grade = rand() % 5 + 1;
    student->physics_grade = rand() % 5 + 1;
    student->chemistry_grade = rand() % 5 + 1;
}

void generate_random_grades_in_order(struct Student *root) {
    if (root != NULL) {
        generate_random_grades_in_order(root->left);
        generate_random_grades(root);
        generate_random_grades_in_order(root->right);
    }
}

void increase_physics_grades_in_order(struct Student *root) {
    if (root != NULL) {
        increase_physics_grades_in_order(root->left);
        if (root->physics_grade < 5) {
            root->physics_grade++;
        }
        increase_physics_grades_in_order(root->right);
    }
}

void print_students_in_order(struct Student *root) {
    if (root != NULL) {
        print_students_in_order(root->left);
        print_student_info(root);
        printf("\n");
        print_students_in_order(root->right);
    }
}

int main() {
    srand(time(NULL));

    struct Student *root = NULL;

    struct Student student1 = {"Smith", "John", 'M', 20, "Group A", 0, 0, 0, NULL, NULL};
    root = insert(root, &student1);

    struct Student student2 = {"Doe", "Jane", 'F', 21, "Group B", 0, 0, 0, NULL, NULL};
    root = insert(root, &student2);

    generate_random_grades_in_order(root);

    printf("Original student information:\n");
    print_students_in_order(root);

    increase_physics_grades_in_order(root);

    printf("\nUpdated student information:\n");
    print_students_in_order(root);

    return 0;
}