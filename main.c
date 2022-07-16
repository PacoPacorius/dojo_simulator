#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <assert.h>

#define V_SMALL         1
#define SMALL           2
#define LIGHTWEIGHT     3
#define MIDDLEWEIGHT    4
#define L_HEAVYWEIGHT   5
#define HEAVYWEIGHT     6
#define S_HEAVYWEIGHT   7

struct Student {
    char* name;
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
    float motivation;

    /* hidden stats (0-100) */
    int destiny_agility;
    int destiny_strength;
    int destiny_flexibility;
    int destiny_stamina;
    
};

void print_worker_stats(struct Student student);
struct Student generate_student();
int generate_weight_class();
int generate_agility(int weight_class, int age);
int generate_strength(int weight_class, int age);
int generate_flexibility(int weight_class, int age);
int generate_stamina(int weight_class, int age);
void increase_physical_stats(struct Student* stud);

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
            increase_physical_stats(&student);
            increase_physical_stats(&student);
            increase_physical_stats(&student);
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

  //  printf("\nSkill Stats: ");
  //  printf("\nHolds: %f", student.holds);
  //  printf("\nStriking: %f", student.striking);
  //  printf("\nKicking: %f", student.kicking);

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

struct Student generate_student(){
    struct Student temp;
    temp.name = "Lil Bitch Boy";

    /* generate age */
    temp.age = rand_lim(45) + 16;

    /* generate weight class */
    
    temp.weight_class = generate_weight_class();

    /* physical stats (0-100) */
    // generate agility
    // temp.agility = generate_agility(int weight_class);
    temp.agility = generate_agility(temp.weight_class, temp.age);
    temp.strength = generate_strength(temp.weight_class, temp.age);
    temp.flexibility = generate_flexibility(temp.weight_class, temp.age);
    temp.stamina = generate_stamina(temp.weight_class, temp.age);

    /* skill stats (0-100) */
    temp.holds = 0;
    temp.striking = 0;
    temp.kicking = 0;

    
    /* personality stats (0-100) */
    temp.motivation = 100;

    /* hidden stats (0-100) */
    temp.destiny_stamina     =   100;
    temp.destiny_agility     =   100;
    temp.destiny_strength    =   100;
    temp.destiny_flexibility =   100;

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
        if(weight_class < 3){   
            /* small & very small only */
            r = rand_lim(30);
        }
        else if( weight_class > 5){
            /* heavyweights and super heavyweights only */
            r = rand_lim(30) + 30;
        }
        else {
            /* the best of the rest */
            r = rand_lim(30) + 10;
        }
    }
    else if(age > 45){
        if(weight_class < 3){
            r = rand_lim(20);
        }
        else if( weight_class > 5){
            r = rand_lim(30) + 20;
        }
        else {
            r = rand_lim(30);
        }
    }
    else {
        if(weight_class < 3){
            r = rand_lim(40);
        }
        else if( weight_class > 5){
            r = rand_lim(30) + 40;
        }
        else {
            r = rand_lim(30) + 20;
        }
    }

    return r;
}


void increase_physical_stats(struct Student* stud){
    float age_coefficient = (float)(1 - (stud->age - 16) / 100);
    float destiny_agility_coefficient = (float)(((stud->destiny_agility - (stud->agility - 20)) / 100));
    float destiny_stamina_coefficient = (float)(((stud->destiny_stamina - (stud->stamina - 20)) / 100));
    float destiny_strength_coefficient = (float)(((stud->destiny_strength - (stud->strength - 20)) / 100));
    float destiny_flexibility_coefficient = (float)(((stud->destiny_flexibility - (stud->flexibility - 20)) / 100));
    float point = 0.1;

    float agility_increase = point * age_coefficient * destiny_agility_coefficient;
    float stamina_increase = point * age_coefficient * destiny_stamina_coefficient;
    float strength_increase = point * age_coefficient * destiny_strength_coefficient;
    float flexibility_increase = point * age_coefficient * destiny_flexibility_coefficient;

    if(agility_increase < 0) agility_increase = 0;
    if(stamina_increase < 0) stamina_increase = 0;
    if(strength_increase < 0) strength_increase = 0;
    if(flexibility_increase < 0) flexibility_increase = 0;

    printf("\nAgility increase: %f", agility_increase);
    printf("\nStamina increase: %f", stamina_increase);
    printf("\nStrength increase: %f", strength_increase);
    printf("\nFlexibility increase: %f", flexibility_increase);
    printf("\n");

    if(stud->agility < 100) stud->agility += agility_increase;
    if(stud->stamina < 100) stud->stamina += stamina_increase;
    if(stud->strength < 100) stud->strength += strength_increase;
    if(stud->flexibility < 100) stud->flexibility += flexibility_increase;
}
