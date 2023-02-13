#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

#include "queue.h"
#include "student_generation.h"


#define NO_FOCUS        0
#define STRIKING_FOCUS  1
#define KICKING_FOCUS   2
#define HOLDS_FOCUS     3

#define MAX_STUDENTS1   40

#define EXIT 5

struct Time{
    int weeks;
    int months;
    int years;
};

void belt_test(struct Student* student);
void new_student_batch(struct Student* student_list, int* number_of_students);
void money_handler(int* dojo_money, int number_of_students, int* months_in_debt);
void menu_handler_advance_week(int* number_of_students, struct Time* date, int* dojo_money, int* months_in_debt, int training_focus, struct Student* stud_muffin, int DBG_happy_times);
void menu_handler_set_training_focus(int* training_focus);
void menu_handler_show_all_students_stats(int number_of_students, struct Student* stud_muffin);
void menu_handler_show_student_stat_history(int number_of_students, struct Student* stud_muffin);
void print_main_menu(struct Time* date, int dojo_money);

int main(int argc, char* argv[]){
    int i, j;
    int DBG_happy_times = 0; // enable to prevent students from leaving (debug feature)
    struct Time date;
    int dojo_money = 1000;
    int number_of_students = 5;
    int months_in_debt = 0;
    int training_focus = 0; // default to no focus
    int c = ' ';
    struct Student stud_muffin[MAX_STUDENTS1];
    srand((unsigned int)time(NULL));
    for(i = 0; i < number_of_students; i++){ 
        stud_muffin[i] = generate_student();
        print_student_stats(stud_muffin[i]);
    }


    if(argc > 1){
        if(strcmp(argv[1], "--happy-times") == 0){
           DBG_happy_times = 1; 
        }
    }

    date.weeks = 1;
    date.months = 10;
    date.years = 1;

    while(c != EXIT){
        print_main_menu(&date, dojo_money);
        scanf("%d", &c);
        getchar();  // consumes newline

        /* user input and menu handling */
        switch(c){
            case 1:
                menu_handler_advance_week(&number_of_students, &date, &dojo_money, &months_in_debt, training_focus, stud_muffin, DBG_happy_times);
            break;
            case 2:
                menu_handler_set_training_focus(&training_focus);
            break;
            case 3:
                menu_handler_show_all_students_stats(number_of_students, stud_muffin);
            break;
            case 4:
                menu_handler_show_student_stat_history(number_of_students, stud_muffin);
            break;
        }

        if(months_in_debt == 3){
            printf("\nYour dojo has gone bankrupt! GAME OVER!\n");
            c = EXIT;
        }
        printf("\n");
    }

    return 0;
}

void menu_handler_advance_week(int* number_of_students, struct Time* date, int* dojo_money, int* months_in_debt, int training_focus, struct Student* stud_muffin, int DBG_happy_times){
    int i = 0;

    date->weeks++;
    /* handle students individually */
    for(i = 0; i < *number_of_students; i++){             
        /* increase all of the students' stats */
        increase_physical_stats(&stud_muffin[i], training_focus, date->weeks);
        increase_skill_stats(&stud_muffin[i], training_focus, date->weeks);

        /* update motivation */
        motivation_updater(&stud_muffin[i], training_focus);

        /* check to see if it is time for exam, this should be more tidy when I expand it, maybe move some of the ifs inside the function */
        /* in the first week of july or january, if it has been at least 6 months since last test and the student has lower belt rank than red / black belt, belt exams */
        if(stud_muffin[i].months_since_previous_test >= 6 && stud_muffin[i].belt_rank < RED_BLACK_BELT && (date->months == 6 || date->months == 0) && date->weeks == 1 ){
            belt_test(&stud_muffin[i]);
        }
        /* in the first week of january, if it has been at least 12 months since last test and the student has red / black belt rank, belt exams */
        else if(stud_muffin[i].months_since_previous_test >= 12 && stud_muffin[i].belt_rank == RED_BLACK_BELT && date->months == 0 && date->weeks == 1 ){
            belt_test(&stud_muffin[i]);
        }

        if((will_they_leave(&stud_muffin[i]) == 1 && DBG_happy_times == 0)){
            leave_dojo(stud_muffin, number_of_students, i);
        }
    }

    /* generate new batch of students */
    if(date->months == 9 && date->weeks == 1){
        new_student_batch(stud_muffin, number_of_students);
        printf("\nA new batch of students has arrived!\n");
    }

    /* change month */
    if(date->weeks == 5){
        date->months++;
        /* update months since previous belt rank test */
        for(i = 0; i < *number_of_students; i++){
            stud_muffin[i].months_since_previous_test++; 
            stud_muffin[i].months_at_dojo++;
        }
        date->weeks = 1;
        money_handler(dojo_money, *number_of_students, months_in_debt);
    }
    /* change year */
    if(date->months == 13){
        date->months = 1;
        date->years++;
        for(i = 0; i < *number_of_students; i++) stud_muffin[i].age++;
    }    
}
void belt_test(struct Student* student){
    student->months_since_previous_test = 0;
    student->belt_rank++;
    if(student->motivation + 10 < 100) student->motivation += 10;
    else student->motivation = 100;

    /* this is additive to the previous motivation boost */
    if(student->belt_rank == DAN_1ST){
        if(student->motivation + 30 < 100) student->motivation += 30;
        else student->motivation = 100;
    }
    
    if(student->belt_rank <= DAN_1ST){
        switch(student->belt_rank){
            case 1:
                printf("\n%s: White Belt -> White / Yellow Belt\tCongrats!", student->name);
                break;
            case 2:
                printf("\n%s: White / Yellow Belt -> Yellow Belt\tCongrats!", student->name);
                break;
            case 3:
                printf("\n%s: Yellow / Green Belt -> Green Belt\tCongrats!", student->name);
                break;
            case 4:
                printf("\n%s: Green Belt -> Green / Blue Belt\tCongrats!", student->name);
                break;
            case 5:
                printf("\n%s: Green Belt -> Green / Blue Belt\tCongrats!", student->name);
                break;
            case 6:
                printf("\n%s: Green / Blue Belt -> Blue Belt\tCongrats!", student->name);
                break;
            case 7:
                printf("\n%s: Blue Belt -> Blue / Red Belt\tCongrats!", student->name);
                break;
            case 8:
                printf("\n%s: Blue / Red Belt -> Red Belt\tCongrats!", student->name);
                break;
            case 9:
                printf("\n%s: Red Belt -> Red / Black Belt\tCongrats!", student->name);
                break;
            case 10:
                printf("\n%s: Red / Black Belt -> Black Belt, 1st Dan\tCongrats!", student->name);
                break;
        }
    }
    printf("\n");

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

void money_handler(int* dojo_money, int number_of_students, int* months_in_debt){
    printf("\n*** START OF MONTHLY BUDGET CALCULATIONS ***\n");
    printf("\n====================================");
    printf("\n Initial Budget: \t  %d€", *dojo_money);
    if(number_of_students * 100 < 1000)
        printf("\n Student Income:    %d*100=+%d€", number_of_students, number_of_students * 100);
    else
        printf("\n Student Income:  %d*100=+%d€", number_of_students, number_of_students * 100);
    printf("\n Rent/Bills:\t          -500€");
    printf("\n --------------------------------");
    *dojo_money -= 500;
    *dojo_money += number_of_students*100;
    printf("\n New Budget: \t\t  %d€", *dojo_money);
    printf("\n====================================");
    printf("\n\n*** END OF MONTHLY BUDGET CALCULATIONS ***");

    if(*dojo_money < 0) months_in_debt++;
    else months_in_debt = 0;
}

void menu_handler_set_training_focus(int* training_focus){
    int i;

    do{
        
        printf("\nCurrent traning focus: ");
        switch(*training_focus){
            case 0:
                printf("General Training\n");
            break;
            case 1:
                printf("Striking Focus\n");
            break;
            case 2:
                printf("Kicking Focus\n");
            break;
            case 3:
                printf("Holds Focus\n");
            break;
        }
        printf("\n0. General Training");
        printf("\n1. Striking Focus");
        printf("\n2. Kicking Focus");
        printf("\n3. Holds Focus\n");
        printf("\nPress -1 to go back to the main menu...\n");
        printf("\nSelect training focus: ");
        scanf("%d", &i);
        getchar();
    } while(i < -1 || i > 3);
    if(i != -1) *training_focus = i;
}


void menu_handler_show_all_students_stats(int number_of_students, struct Student* stud_muffin){
    int i;
    /* show student stats */
    do{
        for(i = 0; i < number_of_students; i++)
            printf("\n%d. %s", i, stud_muffin[i].name);
        printf("\n\nPress -1 to go back to the main menu...\n");
        printf("\nWhich student? ");
        //c = getchar();
        scanf("%d", &i);
        getchar();
    } while(i < -1 || i > number_of_students - 1);
    if(i != -1) print_student_stats(stud_muffin[i]);
}


void menu_handler_show_student_stat_history(int number_of_students, struct Student* stud_muffin){
    
    int i;
    int student_selection, focus_selection;
    
    /* choose student */
    do{         
        /* print students' names */
        for(i = 0; i < number_of_students; i++)
            printf("\n%d. %s", i, stud_muffin[i].name);
        printf("\n\nPress -1 to go back to the main menu...\n");
        printf("\nWhich student? ");
        //c = getchar();
        scanf("%d", &student_selection);
        getchar();
    } while(student_selection < -1 || student_selection > number_of_students - 1);
    /* quick and dirty int <-> char conversion ±'0'*/
    //i = c - '0';
    if(student_selection == -1) return;

    /* choose stat */
    do{                 
        printf("\n\n1. Striking");
        printf("\n2. Kicking");
        printf("\n3. Holds");
        printf("\n4. Agility");
        printf("\n5. Strength");
        printf("\n6. Stamina");
        printf("\n7. Flexibility");
        printf("\n\nPress -1 to go back to the main menu...\n");
        printf("\nWhich stat would you like to see? ");
        //c = getchar();
        /* this works quite well actually */
        scanf("%d", &focus_selection);
        getchar();
        if(focus_selection == -1) return;
    } while(focus_selection < 1 || focus_selection > 7) ;
    //j = c - '0';
    /* very sloppy but the alternative is too much work and I'm lazy */
    if(focus_selection == -1) return;
    print_student_stat_history(stud_muffin[student_selection], focus_selection);
}

void print_main_menu(struct Time* date, int dojo_money){
        printf("\nWeeks/Months/Years passed: %d/%d/%d\tMoney: %d€", date->weeks, date->months, date->years, dojo_money);
        printf("\n1. Advance 1 Week");
        printf("\n2. Set training focus");
        printf("\n3. Show your students' stats");
        printf("\n4. Show your students' stat increase history");
        printf("\n5. Quit");
        printf("\n10. (Debug) Add new student");
        printf("\n11. (Debug) Remove student");
        printf("\n12. (Debug) Add money");
        printf("\nWhat do? ");
}
