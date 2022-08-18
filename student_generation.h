#ifndef STUDENT_GENERATION
#define STUDENT_GENERATION


#include "queue.h"

#define V_SMALL         1
#define SMALL           2
#define LIGHTWEIGHT     3
#define MIDDLEWEIGHT    4
#define L_HEAVYWEIGHT   5
#define HEAVYWEIGHT     6
#define S_HEAVYWEIGHT   7

#define NO_PREFERENCE  -1
#define NO_FOCUS        0
#define STRIKING_FOCUS  1
#define KICKING_FOCUS   2
#define HOLDS_FOCUS     3

#define WHITE_BELT              0
#define WHITE_YELLOW_BELT       1
#define YELLOW_BELT             2
#define YELLOW_GREEN_BELT       3
#define GREEN_BELT              4
#define GREEN_BLUE_BELT         5
#define BLUE_BELT               6
#define BLUE_RED_BELT           7
#define RED_BELT                8
#define RED_BLACK_BELT          9
#define DAN_1ST                 10

struct Student {
    char name[40];
    int age;

    /* skill stats (0-100) */
    float holds;
    float striking;
    float kicking;

    /* physical stats (0-100) */
    float agility;
    float strength;
    float flexibility;
    float stamina;

    /* weight class */
    int weight_class;
    
    /* personality stats (0-100) */
    int training_preference;
    float motivation;
    int months_at_dojo;

    /* hidden stats (0-100) */
    int destiny_agility;
    int destiny_strength;
    int destiny_flexibility;
    int destiny_stamina;

    int destiny_striking;
    int destiny_kicking;
    int destiny_holds;

    int decline_age;

    /* stat increase history */
    struct Queue striking_incr;
    struct Queue kicking_incr;
    struct Queue holds_incr;

    struct Queue agility_incr;
    struct Queue strength_incr;
    struct Queue stamina_incr;
    struct Queue flexibility_incr;

    /* belt rank */
    int belt_rank;
    int months_since_previous_test;
};

int rand_lim(int limit);
double get_gaussdist_number(int lower_lim, int upper_lim);

struct Student generate_student(char* new_name);
int generate_weight_class();
int generate_agility(int weight_class, int age);
int generate_strength(int weight_class, int age);
int generate_flexibility(int weight_class, int age);
int generate_stamina(int weight_class, int age);
void generate_destiny_values(struct Student* stud);

void increase_physical_stats(struct Student* stud, int training_focus, int weeks);
void increase_skill_stats(struct Student* stud, int training_focus, int weeks);
void motivation_updater(struct Student* stud, int training_focus);

int will_they_leave(struct Student* student);    // returns 1 for yes, 0 for no
/* the index of the student that leaves */
void leave_dojo(struct Student* studen_list, int* number_of_students, int index);

void print_student_stats(struct Student student);
void print_student_stat_history(struct Student student, int stat_choice);

#endif
