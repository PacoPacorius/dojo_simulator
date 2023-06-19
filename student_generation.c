#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <string.h>

#include "name_generator.h"
#include "student_generation.h"

struct Student generate_student(){
    struct Student temp;
    char* dummy_name = random_name();
    strcpy(temp.name, dummy_name);
    free(dummy_name);

    /* generate age */
    temp.age = rand_lim(45) + 16;

    /* generate weight class */
    temp.weight_class = generate_weight_class();

    /* physical stats (0-100) */
    temp.agility = generate_agility(temp.weight_class, temp.age);
    temp.strength = generate_strength(temp.weight_class, temp.age);
    temp.flexibility = generate_flexibility(temp.weight_class, temp.age);
    temp.stamina = generate_stamina(temp.weight_class, temp.age);

    /* skill stats (0-100) */
    temp.holds = 0;
    temp.striking = 0;
    temp.kicking = 0;

    
    /* personality stats (0-100) */
    temp.motivation = 50;
    temp.training_preference = rand_lim(4) - 1;
    temp.months_at_dojo = 0;

    /* hidden stats (0-100) */
    generate_destiny_values(&temp);

    /* initialize stat increase queues */
    temp.striking_incr = create_queue();
    temp.kicking_incr = create_queue();
    temp.holds_incr = create_queue();

    temp.agility_incr = create_queue();
    temp.strength_incr = create_queue();
    temp.stamina_incr = create_queue();
    temp.flexibility_incr = create_queue();

    /* belt rank */
    temp.belt_rank = WHITE_BELT;
    temp.months_since_previous_test = 0;

    return temp;
}

int rand_lim(int limit) {
    /* return a random number between 0 and limit inclusive.*/

    int divisor = RAND_MAX/(limit+1);
    int retval;

    do { 
        retval = rand() / divisor;
    } while (retval > limit);

    return retval;
}

int randint(int limit){
    if((limit - 1) == RAND_MAX) return rand();
    else {
        assert(limit <= RAND_MAX);

        int end = RAND_MAX / limit;
        assert(end > 0);
        end *= limit;

        int r;
        while((r = rand()) >= end);

        return r % limit;
    }
}
int generate_weight_class(){
    int r = 0;

    r = randint(RAND_MAX);
    if(r < RAND_MAX / 6){
        /* if student is in the minority that isn't a lightweight, a middleweight or a light heavy, 50 50 chance to be really big or really small*/
        r = rand_lim(1);
        if(r == 1){
            r = rand_lim(1) + 5 + 1; // Heavy or Super Heavy
        }
        else r = rand_lim(1) + 1; // Small or Very Small
    }
    else { // majority, lightweight, middleweight, light heavy
        r = rand_lim(2) + 2 + 1;
    }
    
    return r;
}

int generate_agility(int weight_class, int age){
    int r = 0;

    if(age < 31){
        if(weight_class < 3){   
            /* small & very small only */
            r = rand_lim(30) + 10;
        }
        else if( weight_class > 5){
            /* heavyweights and super heavyweights only */
            r = rand_lim(20);
        }
        else {
            /* the best of the rest */
            r = rand_lim(30);
        }
    }
    else if(age > 45){
        if(weight_class < 3){
            r = rand_lim(10);
        }
        else if( weight_class > 5){
            r = rand_lim(5);
        }
        else {
            r = rand_lim(10);
        }
    }
    else {
        if(weight_class < 3){
            r = rand_lim(25);
        }
        else if( weight_class > 5){
            r = rand_lim(10);
        }
        else {
            r = rand_lim(20);
        }
    }

    return r;
}

int generate_stamina(int weight_class, int age){
    int r = 0;

    if(age < 31){
        if(weight_class < 3){   
            /* small & very small only */
            r = rand_lim(30) + 20;
        }
        else if( weight_class > 5){
            /* heavyweights and super heavyweights only */
            r = rand_lim(30);
        }
        else {
            /* the best of the rest */
            r = rand_lim(30) + 10;
        }
    }
    else if(age > 45){
        if(weight_class < 3){
            r = rand_lim(10);
        }
        else if( weight_class > 5){
            r = rand_lim(5);
        }
        else {
            r = rand_lim(5);
        }
    }
    else {
        if(weight_class < 3){
            r = rand_lim(40);
        }
        else if( weight_class > 5){
            r = rand_lim(20);
        }
        else {
            r = rand_lim(30);
        }
    }

    return r;
}
int generate_flexibility(int weight_class, int age){
    int r = 0;

    if(age < 31){
        if(weight_class < 3){   
            /* small & very small only */
            r = rand_lim(30);
        }
        else if( weight_class > 5){
            /* heavyweights and super heavyweights only */
            r = rand_lim(10);
        }
        else {
            /* the best of the rest */
            r = rand_lim(20);
        }
    }
    else if(age > 45){
        if(weight_class < 3){
            r = rand_lim(10);
        }
        else if( weight_class > 5){
            r = rand_lim(5);
        }
        else {
            r = rand_lim(5);
        }
    }
    else {
        if(weight_class < 3){
            r = rand_lim(20);
        }
        else if( weight_class > 5){
            r = rand_lim(5);
        }
        else {
            r = rand_lim(10);
        }
    }

    return r;
}
int generate_strength(int weight_class, int age){
    int r = 0;

    if(age < 31){
        if(weight_class < LIGHTWEIGHT){   
            /* small & very small only */
            r = rand_lim(30);
        }
        else if( weight_class > L_HEAVYWEIGHT){
            /* heavyweights and super heavyweights only */
            r = rand_lim(30) + 30;
        }
        else {
            /* the best of the rest */
            r = rand_lim(30) + 10;
        }
    }
    else if(age > 45){
        if(weight_class < LIGHTWEIGHT){
            r = rand_lim(20);
        }
        else if( weight_class > L_HEAVYWEIGHT){
            r = rand_lim(30) + 20;
        }
        else {
            r = rand_lim(30);
        }
    }
    else {
        if(weight_class < LIGHTWEIGHT){
            r = rand_lim(40);
        }
        else if( weight_class > L_HEAVYWEIGHT){
            r = rand_lim(30) + 40;
        }
        else {
            r = rand_lim(30) + 20;
        }
    }

    return r;
}

void generate_destiny_values(struct Student* stud){
    /* generate physical stats */
    do{
        stud->destiny_agility = get_gaussdist_number(30, 100);
    } while(stud->destiny_agility < stud->agility);
    do{
        stud->destiny_flexibility = get_gaussdist_number(30, 100);
    } while(stud->destiny_flexibility < stud->flexibility);
    do{
        stud->destiny_strength = get_gaussdist_number(30, 100);
    } while(stud->destiny_strength < stud->strength);
    do{
        stud->destiny_stamina = get_gaussdist_number(30, 100);
    } while(stud->destiny_stamina < stud->stamina);


    do{
        stud->destiny_striking = get_gaussdist_number(30, 100);
    } while(stud->destiny_striking < stud->striking);
    do{
        stud->destiny_kicking = get_gaussdist_number(30, 100);
    } while(stud->destiny_kicking < stud->kicking);
    do{
        stud->destiny_holds = get_gaussdist_number(30, 100);
    } while(stud->destiny_holds < stud->holds);
    
    /* add body type bonuses / penalties */
}

double get_gaussdist_number(int lower_lim, int upper_lim){
    double gaussian_num = -1.0;
    double uniform_nums;
    double uniform_numu;
    int uniform_number;

    /* Box-Muller transform */
    while(gaussian_num < lower_lim || gaussian_num > upper_lim){
        uniform_nums = (double)rand_lim(RAND_MAX - 1) / RAND_MAX;
        uniform_numu = (double)rand_lim(RAND_MAX - 1) / RAND_MAX;

        gaussian_num = sqrt(-2*log(uniform_numu))*cos(2*M_PI*uniform_nums);
        gaussian_num *= 60;
    }

    return gaussian_num;
}

void print_student_stats(struct Student student){

    printf("\n");
    printf("\n");
    printf("***START OF STUDENT STAT OUTPUT***");
    printf("\n");
    printf("\n");
    printf("Name: %s", student.name);
    printf("\t\tAge: %i", student.age);
    printf("\n");

    printf("\nSkill Stats: ");
    printf("\nStriking: %f\t\tPotential: %d", student.striking, student.destiny_striking);
    printf("\nKicking: %f\t\tPotential: %d", student.kicking, student.destiny_kicking);
    printf("\nHolds:  %f\t\tPotential: %d", student.holds, student.destiny_holds);
    printf("\n");

    printf("\nPhysical Stats: ");
    printf("\nAgility: %f\t\tPotential: %d", student.agility, student.destiny_agility);
    printf("\nStrength: %f\t\tPotential: %d", student.strength, student.destiny_strength);
    printf("\nFlexibility: %f\t\tPotential: %d", student.flexibility, student.destiny_flexibility);
    printf("\nStamina: %f\t\tPotential: %d", student.stamina, student.destiny_stamina);
    printf("\n");

    printf("\nBelt Rank: ");
    switch(student.belt_rank){
        case 0:
            printf("White Belt");
            break;
        case 1:
            printf("White / Yellow Belt");
            break;
        case 2:
            printf("Yellow Belt");
            break;
        case 3:
            printf("Yellow / Green Belt");
            break;
        case 4:
            printf("Green Belt");
            break;
        case 5:
            printf("Green / Blue Belt");
            break;
        case 6:
            printf("Blue Belt");
            break;
        case 7:
            printf("Blue / Red Belt");
            break;
        case 8:
            printf("Red Belt");
            break;
        case 9:
            printf("Red / Black Belt");
            break;
        case 10:
            printf("Black Belt, 1st Dan");
            break;
    }
    printf("\n");

    printf("\nMotivation: %2.f", student.motivation);

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

    printf("\nTraining Preference: ");
    switch(student.training_preference){
        case -1:
            printf("No preference");
            break;
        case 0:
            printf("General Training");
            break;
        case 1:
            printf("Striking");
            break;
        case 2:
            printf("Kicking");
            break;
        case 3:
            printf("Holds");
            break;
    }
    printf("\nMonths At Dojo: %d", student.months_at_dojo);
    printf("\n");
    printf("\n");
    printf("***END OF STUDENT STAT OUTPUT***");
    printf("\n");

}

void print_student_stat_history(struct Student student, int stat_choice){
    int i;

    printf("\n\nStud Muffin: %s\n", student.name);
    switch(stat_choice){
        case 1:
            printf("\nStriking  ");
            print_whole_queue(student.striking_incr);
        break;
        case 2:
            printf("\nKicking  ");
            print_whole_queue(student.kicking_incr);
        break;
        case 3:
            printf("\nHolds  ");
            print_whole_queue(student.holds_incr);
        break;
        case 4:
            printf("\nAgility  ");
            print_whole_queue(student.agility_incr);
        break;
        case 5:
            printf("\nStrength  ");
            print_whole_queue(student.strength_incr);
        break;
        case 6:
            printf("\nStamina  ");
            print_whole_queue(student.stamina_incr);
        break;
        case 7:
            printf("\nFlexibility  ");
            print_whole_queue(student.flexibility_incr);
        break;
    }

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
//          printf("\nWriting physical stat increase history array...");
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
 //         printf("\nWriting skill stat increase history array... %f", striking_increase);
            enqueue(&stud->kicking_incr, kicking_increase);
            enqueue(&stud->striking_incr, striking_increase);
            enqueue(&stud->holds_incr, holds_increase);
        }
        j++;
    }
}

void motivation_updater(struct Student *stud, int training_focus){
    if(stud->training_preference == NO_PREFERENCE){
       if(stud->motivation + 0.25 < 100) stud->motivation += 0.25;
       else stud->motivation = 100;
    }
    else if(training_focus == stud->training_preference){
       if(stud->motivation + 5 < 100) stud->motivation += 5;
       else stud->motivation = 100;
    }
    else {
        if(stud->motivation - 2 > 0) stud->motivation -= 2;
        else stud->motivation = 0;
    }
}

int will_they_leave(struct Student* student){
    /* random out of the blue leave, 1 in 10000 chance */
    int random_num1 = rand_lim(10000);
    int random_num2;
    if(random_num1 == 365){
        printf("\nRandom leave! %s mysteriously disappeared from the face of the earth!", student->name);
        return 1;
    }

    random_num1 = rand_lim(50);
    random_num2 = rand_lim(30);

    if(student->motivation < (random_num1 + random_num2) / 2.0){
        printf("\nLow morale leave! %s just can't stand it at your dojo anymore!", student->name);
        return 1;
    }

    return 0;
}

/* when a student leaves, move the last student in the array in their place */
void leave_dojo(struct Student* student_list, int* number_of_students, int index){
    printf("\nStudent %s has left your dojo! You only have %d students now.\n", student_list[index].name, *number_of_students - 1);

//  printf("\nStudent %s's place is taken by %s's place", student_list[index].name, student_list[*number_of_students - 1].name);
    student_list[index] = student_list[*number_of_students - 1];

    *number_of_students = *number_of_students - 1;


}


void new_student_batch(struct Student* student_list, int* number_of_students){
    int new_student_num = rand_lim(4) + 2;
    int i;

    for(i = 0; i < new_student_num; i++){
        if(*number_of_students < MAX_STUDENTS1){
            student_list[*number_of_students] = generate_student("New Student");
            *number_of_students += 1;
        }

    }

}
