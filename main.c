#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#include "queue.h"
#include "student_generation.h"


#define NO_FOCUS        0
#define STRIKING_FOCUS  1
#define KICKING_FOCUS   2
#define HOLDS_FOCUS     3

void increase_physical_stats(struct Student* stud, int training_focus, int weeks);
void increase_skill_stats(struct Student* stud, int training_focus, int weeks);
void print_student_stats(struct Student student);
void print_student_stat_history(struct Student student);

int main(){
    int i, weeks, months, years;
    int number_of_students = 5;
    int training_focus = 0; // default to no focus
    char c;
    struct Student stud_muffin[5];
    srand((unsigned int)time(NULL));
        stud_muffin[0] = generate_student("John Doe");
        stud_muffin[1] = generate_student("Jane Doe");
        stud_muffin[2] = generate_student("Hammer Hadley");
        stud_muffin[3] = generate_student("Commander Kawagishi");
        stud_muffin[4] = generate_student("Fujio Narahashi");
    for(i = 0; i < 5; i++){ 
        print_student_stats(stud_muffin[i]);
    }



    weeks = 0;
    months = 0;
    years = 0;
    while(c != 'q'){
        c = getchar();
        switch(c){
            case '\n':
            printf("\nWeeks/Months/Years passed: %d/%d/%d", weeks, months, years);
            printf("\n1. Advance 1 Week");
            printf("\n2. Set training focus");
            printf("\n3. Show your students' stats");
            printf("\n4. Show your students' stat increase history");
            printf("\nQuit\n");
            printf("\nWhat do? ");
            break;
            case '1':
            weeks++;
            /* increase all of the students' stats */
            for(i = 0; i < 5; i++){             
                increase_physical_stats(&stud_muffin[i], training_focus, weeks);
                increase_skill_stats(&stud_muffin[i], training_focus, weeks);
            }
            break;
            case '2':
            do{
                c = getchar();
                printf("\n0. No Focus");
                printf("\n1. Striking Focus");
                printf("\n2. Kicking Focus");
                printf("\n3. Holds Focus\n");
                printf("\nSelect training focus: ");
            } while(c < '0' || c > 3 + '0');
            i = c - '0'; 
            training_focus = i;
            break;
            case '3':
            /* show student stats */
            do{
                c = getchar();
                printf("\nWhich student? ");
            } while(c < '0' || c > number_of_students - 1 + '0');
            /* quick and dirty int <-> char conversion ±'0'*/
            i = c - '0';
            print_student_stats(stud_muffin[i]);
            break;
            case '4':
            do{
                c = getchar();
                printf("\nWhich student? ");
            } while(c < '0' || c > number_of_students - 1 + '0');
            /* quick and dirty int <-> char conversion ±'0'*/
            i = c - '0';
            print_student_stat_history(stud_muffin[i]);
            break;
        }
        if(weeks == 5){
            months++;
            weeks = 0;
        }
        if(months == 12){
            months = 0;
            years++;
            for(i = 0; i < 5; i++) stud_muffin[i].age++;
        }

        printf("\n");
    }

    return 0;
}

void print_student_stats(struct Student student){
    printf("\n");
    printf("\n");
    printf("Name: %s", student.name);
    printf("\t\tAge: %i", student.age);
    printf("\n");

    printf("\nSkill Stats: ");
    printf("\nStriking: %f\t\tPotential: %d", student.striking, student.destiny_striking);
    printf("\nKicking: %f\t\tPotential: %d", student.kicking, student.destiny_kicking);
    printf("\nHolds: %f\t\t\tPotential: %d", student.holds, student.destiny_holds);
    printf("\n");

    printf("\nPhysical Stats: ");
    printf("\nAgility: %f\t\tPotential: %d", student.agility, student.destiny_agility);
    printf("\nStrength: %f\t\tPotential: %d", student.strength, student.destiny_strength);
    printf("\nFlexibility: %f\t\tPotential: %d", student.flexibility, student.destiny_flexibility);
    printf("\nStamina: %f\t\tPotential: %d", student.stamina, student.destiny_stamina);
    printf("\n");

    printf("\nWeight Class: ");
    switch(student.weight_class){
        case 1:
            printf("Very Small");
            break;
        case 2:
            printf("Small");
            break;
        case 3:
            printf("Lightweight");
            break;
        case 4:
            printf("Middleweight");
            break;
        case 5:
            printf("Light Heavyweight");
            break;
        case 6:
            printf("Heavyweight");
            break;
        case 7:
            printf("Super Heavyweight");
            break;
    }
    printf("\n");

}

void print_student_stat_history(struct Student student){
    int i;

    printf("\n\nStud Muffin: %s\n", student.name);
    printf("\nStriking  ");
   
    print_whole_queue(student.striking_incr);
}


void increase_physical_stats(struct Student* stud, int training_focus, int weeks){
    float age_coefficient;
    float destiny_agility_coefficient;
    float destiny_stamina_coefficient;
    float destiny_strength_coefficient;
    float destiny_flexibility_coefficient;
    float point = 0.1;

    /* training focus coefficients */
    float train_focus_agility_coefficient = 1;
    float train_focus_stamina_coefficient = 1;
    float train_focus_strength_coefficient = 1;
    float train_focus_flexibility_coefficient = 1;
   

    int j = 0;
    while(j < 3){
        age_coefficient = (1 - (float)((stud->age - 16) / 100.0));
        destiny_agility_coefficient = (float)(((stud->destiny_agility - (stud->agility - 20)) / 100));
        destiny_stamina_coefficient = (float)(((stud->destiny_stamina - (stud->stamina - 20)) / 100));
        destiny_strength_coefficient = (float)(((stud->destiny_strength - (stud->strength - 20)) / 100));
        destiny_flexibility_coefficient = (float)(((stud->destiny_flexibility - (stud->flexibility - 20)) / 100));

        switch(training_focus){
            case NO_FOCUS:
                train_focus_agility_coefficient = 0.75;
                train_focus_stamina_coefficient = 0.75;
                train_focus_strength_coefficient = 0.75;
                train_focus_flexibility_coefficient = 0.75;
                break;
        case STRIKING_FOCUS:
                train_focus_agility_coefficient = 0.5;
                train_focus_stamina_coefficient = 0.5;
                train_focus_strength_coefficient = 0.75;
                train_focus_flexibility_coefficient = 0.5;
                break;
        case KICKING_FOCUS:
                train_focus_agility_coefficient = 0.5;
                train_focus_stamina_coefficient = 0.5;
                train_focus_strength_coefficient = 0.5;
                train_focus_flexibility_coefficient = 1;
                break;
        case HOLDS_FOCUS:
                train_focus_agility_coefficient = 0.5;
                train_focus_stamina_coefficient = 0.5;
                train_focus_strength_coefficient = 0.5;
                train_focus_flexibility_coefficient = 0.5;
                break;
    }

        float agility_increase = point * destiny_agility_coefficient * train_focus_agility_coefficient;
        float stamina_increase = point * destiny_stamina_coefficient * train_focus_stamina_coefficient;
        float strength_increase = point * destiny_strength_coefficient * train_focus_strength_coefficient;
        float flexibility_increase = point * destiny_flexibility_coefficient * train_focus_flexibility_coefficient;

        if(agility_increase < 0) agility_increase = 0;
        if(stamina_increase < 0) stamina_increase = 0;
        if(strength_increase < 0) strength_increase = 0;
        if(flexibility_increase < 0) flexibility_increase = 0;

    //  printf("\nAgility increase: %f", agility_increase);
    //  printf("\nStamina increase: %f", stamina_increase);
    //  printf("\nStrength increase: %f", strength_increase);
    //  printf("\nFlexibility increase: %f", flexibility_increase);
    //  printf("\n");

        if(stud->agility < 100) stud->agility += agility_increase;
        if(stud->stamina < 100) stud->stamina += stamina_increase;
        if(stud->strength < 100) stud->strength += strength_increase;
        if(stud->flexibility < 100) stud->flexibility += flexibility_increase;

        if(j == 2 && weeks == 1){
            printf("\nWriting physical stat increase history array...");
            enqueue(&stud->agility_incr, agility_increase);
            enqueue(&stud->stamina_incr, stamina_increase);
            enqueue(&stud->strength_incr, strength_increase);
            enqueue(&stud->flexibility_incr, flexibility_increase);
        }
        j++;
    }
}

void increase_skill_stats(struct Student* stud, int training_focus, int weeks){
    float age_coefficient;
    float destiny_striking_coefficient;
    float destiny_kicking_coefficient;
    float destiny_holds_coefficient;
    float point = 0.1;

    /* training focus coefficients */
    float train_focus_striking_coefficient = 1;
    float train_focus_kicking_coefficient = 1;
    float train_focus_holds_coefficient = 1;

    /* coefficient based on dependence by physical skills */
    float striking_coefficient;
    float kicking_coefficient;
    float holds_coefficient;

    int j = 0;
    while(j < 3){
        age_coefficient = (float)(1 - (stud->age - 16) / 100);
        destiny_striking_coefficient = (float)(((stud->destiny_striking - (stud->striking - 20)) / 100));
        destiny_kicking_coefficient = (float)(((stud->destiny_kicking - (stud->kicking - 20)) / 100));
        destiny_holds_coefficient = (float)(((stud->destiny_holds - (stud->holds - 20)) / 100));


        /* coefficient based on dependence by physical skills */
        striking_coefficient = stud->strength / (stud->striking + 20);
        kicking_coefficient = 0.5*(stud->flexibility + stud->agility + 1/3 * stud->strength) / (stud->kicking + 20);
        holds_coefficient = 1;

        switch(training_focus){
            case NO_FOCUS:
                train_focus_striking_coefficient = 0.75;
                train_focus_kicking_coefficient = 0.75;
                train_focus_holds_coefficient = 0.75;
                break;
            case STRIKING_FOCUS:
                train_focus_striking_coefficient = 1.25;
                train_focus_kicking_coefficient = 0.5;
                train_focus_holds_coefficient = 0.5;
            break;
            case KICKING_FOCUS:
                train_focus_striking_coefficient = 0.5;
                train_focus_kicking_coefficient = 1.25;
                train_focus_holds_coefficient = 0.5;
            break;
            case HOLDS_FOCUS:
                train_focus_striking_coefficient = 0.5;
                train_focus_kicking_coefficient = 0.5;
                train_focus_holds_coefficient = 1.25;
            break;
        }

        float striking_increase = point * destiny_striking_coefficient * striking_coefficient * train_focus_striking_coefficient;
        float kicking_increase = point * destiny_kicking_coefficient * kicking_coefficient * train_focus_kicking_coefficient;
        float holds_increase = point * destiny_holds_coefficient * holds_coefficient * train_focus_holds_coefficient;

        if(striking_increase < 0) striking_increase = 0;
        if(kicking_increase < 0) kicking_increase = 0;
        if(holds_increase < 0) holds_increase = 0;

//        printf("\nStud Muffin: %s", stud->name);
//        printf("\nStriking increase: %f", striking_increase);
//        printf("\nKicking increase: %f", kicking_increase);
//        printf("\nHolds increase: %f", holds_increase);
//        printf("\n");

        if(stud->striking < 100) stud->striking += striking_increase;
        if(stud->kicking < 100) stud->kicking += kicking_increase;
        if(stud->holds < 100) stud->holds += holds_increase;

        if(j == 2 && weeks == 1){
            printf("\nWriting skill stat increase history array... %f", striking_increase);
            enqueue(&stud->kicking_incr, kicking_increase);
            enqueue(&stud->striking_incr, striking_increase);
            enqueue(&stud->holds_incr, holds_increase);
        }
        j++;
    }
}
