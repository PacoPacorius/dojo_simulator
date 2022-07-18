#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#include "student_generation.h"
#include "student.h"

void increase_physical_stats(struct Student* stud);
void increase_skill_stats(struct Student* stud);

int main(){
    int i, weeks, months, years;
    char c;
    struct Student student;
    srand((unsigned int)time(NULL));
    student = generate_student();


    print_worker_stats(student);

    weeks = 0;
    months = 0;
    years = 0;
    while(1){
        for(i = 0; i < 4; i++){
            c = getchar();
            weeks++;
            printf("Weeks/Months/Years passed: %d/%d/%d", weeks, months, years);
            int j = 0;
            while(j < 3){
                increase_physical_stats(&student);
                increase_skill_stats(&student);
                j++;
            }
        }
        print_worker_stats(student);
        months++;
        weeks = 0;
        if(months == 12){
            months = 0;
            years++;
            student.age++;
        }

        printf("\n");
    }

    return 0;
}

void print_worker_stats(struct Student student){
    printf("\n");
    printf("\n");
    printf("Name: %s", student.name);
    printf("\tAge: %i", student.age);
    printf("\n");

    printf("\nSkill Stats: ");
    printf("\nHolds: %f", student.holds);
    printf("\nStriking: %f", student.striking);
    printf("\nKicking: %f", student.kicking);
    printf("\n");

    printf("\nPhysical Stats: ");
    printf("\nAgility: %f", student.agility);
    printf("\nStrength: %f", student.strength);
    printf("\nFlexibility: %f", student.flexibility);
    printf("\nStamina: %f", student.stamina);
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




void increase_physical_stats(struct Student* stud){
    float age_coefficient = (float)(1 - (stud->age - 16) / 100);
    float destiny_agility_coefficient = (float)(((stud->destiny_agility - (stud->agility - 20)) / 100));
    float destiny_stamina_coefficient = (float)(((stud->destiny_stamina - (stud->stamina - 20)) / 100));
    float destiny_strength_coefficient = (float)(((stud->destiny_strength - (stud->strength - 20)) / 100));
    float destiny_flexibility_coefficient = (float)(((stud->destiny_flexibility - (stud->flexibility - 20)) / 100));
    float point = 0.1;

    float agility_increase = point * destiny_agility_coefficient;
    float stamina_increase = point * destiny_stamina_coefficient;
    float strength_increase = point * destiny_strength_coefficient;
    float flexibility_increase = point * destiny_flexibility_coefficient;

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
}

void increase_skill_stats(struct Student* stud){
    float age_coefficient = (float)(1 - (stud->age - 16) / 100);
    float destiny_striking_coefficient = (float)(((stud->destiny_striking - (stud->striking - 20)) / 100));
    float destiny_kicking_coefficient = (float)(((stud->destiny_kicking - (stud->kicking - 20)) / 100));
    float destiny_holds_coefficient = (float)(((stud->destiny_holds - (stud->holds - 20)) / 100));
    float point = 0.1;

    /* coefficient based on dependence by physical skills */
    float striking_coefficient = stud->strength / (stud->striking + 20);
    float kicking_coefficient = 0.5*(stud->flexibility + stud->agility + 1/3 * stud->strength) / (stud->kicking + 20);
    float holds_coefficient = 1;

    float striking_increase = point * destiny_striking_coefficient * striking_coefficient;
    float kicking_increase = point * destiny_kicking_coefficient * kicking_coefficient;
    float holds_increase = point * destiny_holds_coefficient * holds_coefficient;

    if(striking_increase < 0) striking_increase = 0;
    if(kicking_increase < 0) kicking_increase = 0;
    if(holds_increase < 0) holds_increase = 0;

    printf("\nStriking increase: %f", striking_increase);
    printf("\nKicking increase: %f", kicking_increase);
    printf("\nHolds increase: %f", holds_increase);
    printf("\n");

    if(stud->striking < 100) stud->striking += striking_increase;
    if(stud->kicking < 100) stud->kicking += kicking_increase;
    if(stud->holds < 100) stud->holds += holds_increase;
}
