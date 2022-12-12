#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#include "queue.h"
#include "student_generation.h"


#define NO_FOCUS        0
#define STRIKING_FOCUS  1
#define KICKING_FOCUS   2
#define HOLDS_FOCUS     3

#define MAX_STUDENTS1   40

void belt_test(struct Student* student);
void new_student_batch(struct Student* student_list, int* number_of_students);
void money_handler(int* dojo_money, int number_of_students);

int main(){
    int i, j, weeks, months, years;
    int dojo_money = 1000;
    int number_of_students = 5;
    int months_in_debt = 0;
    int training_focus = 0; // default to no focus
    char c = ' ';
    struct Student stud_muffin[MAX_STUDENTS1];
    srand((unsigned int)time(NULL));
    for(i = 0; i < number_of_students; i++){ 
        stud_muffin[i] = generate_student();
        print_student_stats(stud_muffin[i]);
    }



    weeks = 0;
    months = 0;
    years = 0;
    while(c != 'q' && c != 'Q'){
        printf("\nWeeks/Months/Years passed: %d/%d/%d\tMoney: %d€", weeks, months, years, dojo_money);
        printf("\n1. Advance 1 Week");
        printf("\n2. Set training focus");
        printf("\n3. Show your students' stats");
        printf("\n4. Show your students' stat increase history");
        printf("\nQuit\n");
        printf("\nWhat do? ");
        c = getchar();
        getchar();  // consumes newline

        /* user input and menu handling */
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
            /* handle students individually */
            for(i = 0; i < number_of_students; i++){             
                /* increase all of the students' stats */
                increase_physical_stats(&stud_muffin[i], training_focus, weeks);
                increase_skill_stats(&stud_muffin[i], training_focus, weeks);

                /* update motivation */
                motivation_updater(&stud_muffin[i], training_focus);

                /* check to see if it is time for exam, this should be more tidy when I expand it, maybe move some of the ifs inside the function */
                /* in the first week of july or january, if it has been at least 6 months since last test and the student has lower belt rank than red / black belt, belt exams */
                if(stud_muffin[i].months_since_previous_test >= 6 && stud_muffin[i].belt_rank < RED_BLACK_BELT && (months == 6 || months == 0) && weeks == 1 ){
                    belt_test(&stud_muffin[i]);
                }
                /* in the first week of january, if it has been at least 12 months since last test and the student has red / black belt rank, belt exams */
                else if(stud_muffin[i].months_since_previous_test >= 12 && stud_muffin[i].belt_rank == RED_BLACK_BELT && months == 0 && weeks == 1 ){
                    belt_test(&stud_muffin[i]);
                }

                if(will_they_leave(&stud_muffin[i]) == 1){
                    leave_dojo(stud_muffin, &number_of_students, i);
                }
            }

            /* generate new batch of students */
            if(months == 9 && weeks == 1){
                new_student_batch(stud_muffin, &number_of_students);
                printf("\nA new batch of students has arrived!\n");
            }

            /* change month */
            if(weeks == 5){
                months++;
                /* update months since previous belt rank test */
                for(i = 0; i < number_of_students; i++){
                    stud_muffin[i].months_since_previous_test++; 
                    stud_muffin[i].months_at_dojo++;
                }
                weeks = 0;
                money_handler(&dojo_money, number_of_students);
                if(dojo_money < 0) months_in_debt++;
                else months_in_debt = 0;
            }
            /* change year */
            if(months == 12){
                months = 0;
                years++;
                for(i = 0; i < number_of_students; i++) stud_muffin[i].age++;
            }    
            break;
            case '2':
            do{
                
                printf("\n0. No Focus");
                printf("\n1. Striking Focus");
                printf("\n2. Kicking Focus");
                printf("\n3. Holds Focus\n");
                printf("\nPress -1 to go back to the main menu...\n");
                printf("\nSelect training focus: ");
                //c = getchar();
                scanf("%d", &i);
                getchar();
            } while(i < -1 || i > 3);
            //i = c - '0'; 
            if(i != -1) training_focus = i;
            break;
            case '3':
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
            /* quick and dirty int <-> char conversion ±'0'*/
            //i = c - '0';
            if(i != -1) print_student_stats(stud_muffin[i]);
            break;
            case '4':
            /* choose student */
            int student_selection, focus_selection;
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
            if(student_selection == -1) break;

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
                if(focus_selection == -1) break;
            } while(focus_selection < 1 || focus_selection > 7) ;
            //j = c - '0';
            /* very sloppy but the alternative is too much work and I'm lazy */
            if(focus_selection == -1) break;
            print_student_stat_history(stud_muffin[student_selection], focus_selection);
            break;
        }

        if(months_in_debt == 3){
            printf("\nYour dojo has gone bankrupt! GAME OVER!\n");
            break;
        }
        printf("\n");
    }

    return 0;
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

void money_handler(int* dojo_money, int number_of_students){
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
}
