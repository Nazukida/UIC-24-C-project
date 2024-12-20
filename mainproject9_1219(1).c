#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>
#include <stdlib.h>
char time_flag[50];
int num_class = 0;
int numn;
struct t
{
    char time_express[30];
} time_e[8];
struct classroom
{
    char can_book_0[9];
    char can_book_1[9];
    char can_book_2[9];
    char filename[10];
    char name[10];
    char size[10];
} c[1000];
void fail(void);
void set_classroom();
void initialize(struct classroom c);
// void book(struct classroom c, int a);
void welcome(void);
bool login_hide();
void judgement();
void time_judge(void);
void today_judge(void);
void tomorrow_output(void);
void next_output(void);
void room_judge(int input);
void day_choose(void);
void refresh(void);
void init(void);
void room_output(int room_size, int total_room, char *time, int day);
void book(int class, char *time_flag, int day);
int main()
{
    init(); //
    // set_classroom();
    int day_reserve;
    FILE *fp;
    struct tm *tblock;
    time_t current_time;
    time(&current_time);
    tblock = localtime(&current_time);
    fp = fopen("date.txt", "r");
    fscanf(fp, "%d", &day_reserve);
    // printf("(%d)\n",day_reserve);
    // printf("(%d)\n",tblock->tm_mday);
    // printf("%d",day_reserve!=(tblock->tm_mday));
    fclose(fp);
    if (day_reserve != (tblock->tm_mday))
    {
        // printf("need refresh\n");
        refresh();
    }
    fp = fopen("date.txt", "w");
    fprintf(fp, "%d", tblock->tm_mday);
    fclose(fp);
    welcome();
    judgement();
    day_choose();
    return 0;
}

void welcome(void)
{
    printf("         JMMM      JMMM      JMMM              MMMJ                                                                     \n");
    printf("          MMMM     MMMMM     MMMMM             MMMM                                                                     \n");
    printf("          MMMM     MMMMM     MMMMJ             MMMM                                                                     \n");
    printf("          JMMMJ   JMMMMMM   JMMMM    JJJJJ     MMMM     JJJJJ       JJJJJ       JJ   JJJ    JJJJ        JJJJ            \n");
    printf("           MMMM   MMMMMMM   MMMMJ  JMMMMMMMJ   MMMM   JMMMMMMM    JMMMMMMMMJ    MMMMMMMMMM MMMMMMJ    JMMMMMMM          \n");
    printf("           MMMM   MMMMMMMJ  MMMM  JMMMMMMMMMM  MMMM  JMMMMMMMMMJ MMMMMMMMMMMM   MMMMMMMMMMMMMMMMMMJ  MMMMMMMMMMJ        \n");
    printf("            MMMJ MMMM MMMM JMMMM  MMMMJ   MMM  MMMM  MMMMJ  JMMM MMMMJ    MMMJ  MMMMJ  MMMMM   MMMM  MMMMJ  JMMM        \n");
    printf("            MMMM MMMM  MMM MMMMJ  MMMMMMMMMMMM MMMM  MMMM       JMMMM     MMMM  MMMM   JMMMM   MMMM  MMMMMMMMMMMM       \n");
    printf("            JMMMJMMMJ  MMMJMMMM   MMMMMMMMMMMM MMMM  MMMM       JMMMM     MMMM  MMMM   JMMMJ   MMMM JMMMMMMMMMMMM       \n");
    printf("             MMMMMMM   JMMMMMMM   MMMMJJJJJJJJ MMMM  MMMM       JMMMM     MMMM  MMMM   JMMMJ   MMMM  MMMMJJJJJJJJ       \n");
    printf("             MMMMMMM    MMMMMMJ   MMMM    MMJ  MMMM  MMMM   MMMJ MMMM    MMMMM  MMMM   JMMMJ   MMMM  MMMM    MMJ        \n");
    printf("             JMMMMM     MMMMMM     MMMMMMMMMMM MMMM   MMMMMMMMMM  MMMMMMMMMMM   MMMM   JMMMJ   MMMM   MMMMMMMMMMJ       \n");
    printf("              MMMMM      MMMMM      MMMMMMMMM  MMMM    MMMMMMMM    MMMMMMMMM    MMMM   JMMMJ   MMMM    MMMMMMMMJ        \n");
    printf("               JJJJ       JJJ         JMMMJ     JJJ      JMMJJ       JMMMJ       JJJ    JJJ     JJJ      JMMMJ          \n");
}
void init(void)
{
    num_class = 0;
    FILE *p;
    p = fopen("classroom_info.txt", "r");
    while (fscanf(p, "%s%s", c[num_class].name, c[num_class].size) != EOF)
        num_class++;
    strcpy(time_e[0].time_express, "9:00 am - 9:50 am   |");
    strcpy(time_e[1].time_express, "10:00 am - 10:50 am |");
    strcpy(time_e[2].time_express, "11:00 am - 11:50 am |");
    strcpy(time_e[3].time_express, "12:00 am - 12:50 am |");
    strcpy(time_e[4].time_express, "1:00 pm - 1:50 pm   |");
    strcpy(time_e[5].time_express, "2:00 pm - 2:50 pm   |");
    strcpy(time_e[6].time_express, "3:00 pm - 3:50 pm   |");
    strcpy(time_e[7].time_express, "4:00 pm - 4:50 pm   |");
    fclose(p);
}

void day_choose()
{
    struct tm *tblock;
    time_t current_time;
    time(&current_time);
    tblock = localtime(&current_time);
    time_judge();
    int input; // 选择时间
    int time_choice;
    int room_size;
    int class;
    while (1)
    {
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        printf("===================================================================================================\n");
        printf("Please make your choice: 1. Today 2. Tomorrow 3. The day after tomorrow 4. Quit  ||:");
        scanf("%d", &input);
        while (1)
        {
            if (input == 1)
            {
                today_judge();
                if (tblock->tm_hour >= 17)
                {
                    break;
                }
                else
                {
                    scanf("%d", &time_choice);
                    if (time_choice == numn)
                    {
                        break;
                    }
                    if (time_choice < numn || time_choice > 1)
                    {
                        room_judge(time_choice);
                        printf("Please input room size: ");
                        scanf("%d", &room_size);
                        room_output(room_size, num_class, time_flag, input);
                        printf("Please input the number of the classroom you want to book: ");
                        scanf("%d", &class);
                        book(class, time_flag, input);
                        break;
                    }
                    else
                    {
                        printf("Please input valid number!\n");
                        continue;
                    }
                }
            }
            else if (input == 2)
            {
                tomorrow_output();
                scanf("%d", &time_choice);
                if (time_choice == numn)
                {
                    break;
                }
                if (time_choice < numn || time_choice > 1)
                {
                    room_judge(time_choice);
                    printf("Please input room size: ");
                    scanf("%d", &room_size);
                    room_output(room_size, num_class, time_flag, input);
                    printf("Please input the number of the classroom you want to book: ");
                    scanf("%d", &class);
                    book(class, time_flag, input);
                    break;
                }
                else
                {
                    printf("Please input valid number!\n");
                    continue;
                }
                break;
            }
            else if (input == 3)
            {
                next_output();
                scanf("%d", &time_choice);
                if (time_choice == numn)
                {
                    break;
                }
                if (time_choice < numn || time_choice > 1)
                {
                    room_judge(time_choice);
                    printf("Please input room size: ");
                    scanf("%d", &room_size);
                    room_output(room_size, num_class, time_flag, input);
                    printf("Please input the number of the classroom you want to book: ");
                    scanf("%d", &class);
                    book(class, time_flag, input);
                    break;
                }
                else
                {
                    printf("Please input valid number!\n");
                    continue;
                }
                break;
            }
            else if (input == 4)
            {
                printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
                printf("===================================================================================================\n");
                printf("Quit, thanks for using!\n");
                printf("===================================================================================================\n");
                printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
                break;
            }
            else
            {
                printf("Please input valid number!\n");
            }
        }
        printf("continue? 1. yes 2. no\n");
        int continue_judge; // 111111111111111111111111111111111111111111111111111111111111111111111111111

        scanf("%d", &continue_judge);
        if (continue_judge == 1)
        {
            break;
        }
        else if (continue_judge == 2)
        {
            printf("                                                                                                                        \n");
            printf("                                                                                                                        \n");
            printf("                                                                         MMMMMM                                         \n");
            printf("                      JMMMMMMMMMMMMMMMMMMMJ                              MMMMMMMM                                       \n");
            printf("                      JMMMMMMMMMMMMMMMMMMMMJ                             MMMMMMMM        JJJJJ                          \n");
            printf("                      JMMMMMMMMMMMMMMMMMMMMJ                              JMMMMMM       JMMMMMMJ                        \n");
            printf("                      JMMMMMMMMJJJJJJJJJJJJJ                                            MMMMMMMJ                        \n");
            printf("                      JMMMMMMMM              JJJJJJ            JJJJJJ    JJJJJJ     JJJJMMMMMMMJJJJ                     \n");
            printf("                      JMMMMMMMM              JMMMMMMJ        JMMMMMMJ    MMMMMM    JMMMMMMMMMMMMMMMM                    \n");
            printf("                      JMMMMMMMM               JMMMMMMM      JMMMMMMMMMJ  MMMMMMMMJ JMMMMMMMMMMMMMMMMMM                  \n");
            printf("                      JMMMMMMMMJJJJJJJJJ        MMMMMMMJ   MMMMMMMMMM    MMMMMMMMJ   JMMMMMMMMMMMMMMMM                  \n");
            printf("                      JMMMMMMMMMMMMMMMMMMJ       MMMMMMMJJMMMMMMMMMJ     MMMMMMMMJ     JMMMMMMMJ                        \n");
            printf("                      JMMMMMMMMMMMMMMMMMMM        JMMMMMMMMMMMMMMMJ      MMMMMMMMJ     JMMMMMMMJ                        \n");
            printf("                      JMMMMMMMMMMMMMMMMMMM          MMMMMMMMMMMMM        MMMMMMMMJ     JMMMMMMMJ                        \n");
            printf("                      JMMMMMMMM                      MMMMMMMMMMJ         MMMMMMMMJ     JMMMMMMMJ                        \n");
            printf("                      JMMMMMMMM                    JMMMMMMMMMMJ          MMMMMMMMJ     JMMMMMMMJ                        \n");
            printf("                      JMMMMMMMM                   JMMMMMMMMMMMMM         MMMMMMMMJ     JMMMMMMMJ                        \n");
            printf("                     JMMMMMMMM                  MMMMMMMMMMMMMMMMJ       MMMMMMMMJ     JMMMMMMMJ                         \n");
            printf("                      JMMMMMMMMJJJJJJJJJJJJ    JMMMMMMMMMJ JMMMMMMM      MMMMMMMMJ     JMMMMMMMJ                        \n");
            printf("                      JMMMMMMMMMMMMMMMMMMMMJJ MMMMMMMMMM    JMMMMMMM     MMMMMMMMJ      MMMMMMMMMMMM                    \n");
            printf("                      JMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM       MMMMMMMJ   MMMMMMMMJ       MMMMMMMMMMMMM                  \n");
            printf("                       JMMMMMMMMMMMMMMMMMMMMMJJMMMMMMJ         JMMMMMMM  JJMMMMMMJ        JMMMMMMMMMMM                  \n");
            printf("                                                                                             JJMMJJJ                    \n");
            printf("                                                                                                                        \n");
            printf("                                                                                                                        \n");
            return;
        }
        else
        {
            printf("Please input valid number!\n");
            continue;
        }
    }
    return;
}

void set_classroom()
{
    num_class = 0;
    char r;
    FILE *p;
    p = fopen("classroom_info.txt", "r");
    int n = 0, s = 0;
    while (fscanf(p, "%s%s", c[num_class].name, c[num_class].size) != EOF)
    {
        strcpy(c[num_class].can_book_0, "yyyyyyyy");
        strcpy(c[num_class].can_book_1, "yyyyyyyy");
        strcpy(c[num_class].can_book_2, "yyyyyyyy");
        strcpy(c[num_class].filename, c[num_class].name);
        strcat(c[num_class].filename, ".txt");
        initialize(c[num_class]);
        num_class++;
    }
    fclose(p);
}
// 111111111111111111111111111111111111111111111111111111
void refresh()
{
    num_class = 0;
    char r;
    FILE *p;
    p = fopen("classroom_info.txt", "r");
    int n = 0, s = 0;
    FILE *fp;
    char skip[50];
    char ch;
    char judge[3];
    while (fscanf(p, "%s%s", c[num_class].name, c[num_class].size) != EOF)
    {
        strcpy(c[num_class].filename, c[num_class].name);
        strcat(c[num_class].filename, ".txt");
        fp = fopen(c[num_class].filename, "r");
        // printf("%s",c[num_class].filename);
        while (ch = fgetc(fp), ch != 'w')
            ;
        for (int i = 0; i < 8; i++)
        {
            while (ch = fgetc(fp), ch != '|')
                ;
            fscanf(fp, ": %s", judge);
            // printf("(%s)",judge);
            if (strcmp(judge, "yes") == 0)
                c[num_class].can_book_0[i] = 'y';
            else
                c[num_class].can_book_0[i] = 'n';
        }
        while (ch = fgetc(fp), ch != 'w')
            ;
        for (int i = 0; i < 8; i++)
        {
            while (ch = fgetc(fp), ch != '|')
                ;
            fscanf(fp, ": %s", judge);
            // printf("(%s)",judge);
            if (strcmp(judge, "yes") == 0)
                c[num_class].can_book_1[i] = 'y';
            else
                c[num_class].can_book_1[i] = 'n';
        }
        strcpy(c[num_class].can_book_2, "yyyyyyyy");

        // printf("%s %s %s\n",c[num_class].can_book_0,c[num_class].can_book_1,c[num_class].can_book_2);
        fclose(fp);
        initialize(c[num_class]);
        num_class++;
    }
    fclose(p);
}
// 111111111111111111111111111111111111111111111111111111

void initialize(struct classroom a)
{
    FILE *fp;
    fp = fopen(a.filename, "w");
    fprintf(fp, "%s\n", a.size);
    fprintf(fp, "Today\n");
    for (int i = 0; i < 8; i++)
    {
        // printf("%c ",a.can_book_0[i]);
        if (a.can_book_0[i] == 'y')
            fprintf(fp, "%s: yes\n", time_e[i].time_express);
        else
            fprintf(fp, "%s: no \n", time_e[i].time_express);
    }
    // printf("\n");
    fprintf(fp, "Tomorrow\n");
    for (int i = 0; i < 8; i++)
    {
        // printf("%c ",a.can_book_1[i]);
        if (a.can_book_1[i] == 'y')
            fprintf(fp, "%s: yes\n", time_e[i].time_express);
        else
            fprintf(fp, "%s: no \n", time_e[i].time_express);
    }
    // printf("\n");
    fprintf(fp, "The day after Tomorrow\n");
    for (int i = 0; i < 8; i++)
    {
        // printf("%c ",a.can_book_2[i]);
        if (a.can_book_2[i] == 'y')
            fprintf(fp, "%s: yes\n", time_e[i].time_express);
        else
            fprintf(fp, "%s: no \n", time_e[i].time_express);
    }
    // printf("\n");
    fclose(fp);
    return;
}

#include <stdio.h>
#include <string.h>

bool login_hide()
{
    FILE *fp;
    int judge = 0;
    int n, p;
    // define txt get
    char name[50];
    int nlen;
    char password[50];
    int plen;
    nlen = strlen(name);
    plen = strlen(password);
    int a;
    // define user input
    char name_j[50];
    int nlen_j;
    char password_j[50];
    int plen_j;
    while (1)
    {

        printf("        *                                                                              *                         \n");
        printf("       ***                                                                            ***                        \n");
        printf("     *******                                                                        *******                      \n");
        printf("       ***                                                                            ***                        \n");
        printf("        *                        ->->->->->->->->->->->->->->->                        *                         \n");
        printf("                                 please enter your user's name: ");
        scanf("%s", name_j);
        printf("\n");
        printf("\n");
        char temp;
        printf("                                 <-<-<-<-<-<-<-<-<-<-<-<-<-<-<-\n");
        printf("                                 please enter your password: ");
        scanf("%s",password_j);

        // while (temp = getch(), temp != 13)
        // {
        //     if (temp == 8 && num != 0)
        //     {
        //         printf("\b \b");
        //         num--;
        //     }
        //     else if (num == 0 && temp == 8)
        //         continue;
        //     else
        //     {
        //         printf("*");
        //         password_j[num++] = temp;
        //     }
        // }
        nlen_j = strlen(name_j);
        plen_j = strlen(password_j);
        // printf("%s",name_j);
        // printf("%s\n",password_j);

        // check
        char c;
        fp = fopen("account.txt", "r");
        while (fscanf(fp, "%s%s", name, password) != EOF && !judge)
        {
            // printf("\nname:%s; password:%s;",name,password);
            nlen = strlen(name);
            plen = strlen(password);
            if (nlen == nlen_j && plen == plen_j)
            {
                // printf("success judge length: \n");
                judge = 1;
                // printf("judge name: \n");
                for (int i = 0; i < nlen; i++)
                {
                    // printf("%c : %c\n",name[i],name_j[i]);
                    if (name[i] != name_j[i])
                    {
                        judge = 0;
                        break;
                    }
                }
                // printf("judge password: \n");
                for (int i = 0; i < plen; i++)
                {
                    // printf("%c : %c\n",password[i],password_j[i]);
                    if (password[i] != password_j[i])
                    {
                        judge = 0;
                        break;
                    }
                }
            }
        }
        printf("\n                                    -----------------\n");
        printf("                                    |1.Confirm login|      \n");
        printf("                                    |===============|      \n");
        printf("                                    |2.Re-enter     |      \n");
        printf("                                    -----------------\n");
        printf("\n");
        printf("                             **                               **    \n");
        printf("                              **                               **    \n");
        printf("                                       Please make your choice:");
        scanf("%d", &a);
        printf("                             **                               **    \n");
        printf("                             **                               **    \n");
        if (a == 2)
            continue;
        else
            break;
    }
    fclose(fp);
    if (judge)
        return true;
    else
        return false;
}

void judgement(void)
{
    // while(1)
    // {
    //     if(login_hide())
    //     {
    //         printf("\n===============================================================");
    //         printf("\n=                    successfully login!                      =\n");
    //         printf("===============================================================\n");
    //         break;
    //     }
    //     else
    //     {
    //         printf("\n===============================================================");
    //         printf("\n=                   login unsuccessfully!                     =\n");
    //         printf("===============================================================\n");
    //     }
    // }
    // Sleep(1000);
    // system("cls");

    while (1)
    {
        int a, fail_n = 0, out;
        if (fail_n == 3)
        {
            //???????????
            printf("                                            ||||\n");
            printf("                                            ||||\n");
            printf("                                            ||||\n");
            printf("                                      ^^    ||||    ^^\n");
            printf("                                       ^^   ||||   ^^\n");
            printf("                                        ^^  ||||  ^^\n");
            printf("                                          ^^****^^\n");
            printf("                                            ****\n");
            printf("                                             **\n");
            printf("					You do not have choise\n");
            printf("					Please use it later\n");
            printf("================================================================================================\n");
            printf("\n");
            printf("                                     Please enter 1 to exit: ");
            scanf("%d", &out);
            if (out == 1)
            {
                printf("        *                                                                              *                         \n");
                printf("       ***                                                                            ***                        \n");
                printf("     *******                                                                        *******                      \n");
                printf("       ***                                                                            ***                        \n");
                printf("        *                        ->->->->->->->->->->->->->->->                        *                         \n");
                printf("									Thank you for your use\n");
                printf("									   Have a good day!\n");
                return;
            }
        }
        if (login_hide())
        {
            printf("\n");
            printf("           JMMMMJ                                                                                             JJJ     \n");
            printf("         MMMMMMMMMM                                                                                          JMMMM     \n");
            printf("        JMMMMMMMMMMM                                                                                         JMMMM     \n");
            printf("        MMMMMM  MMMMM                                                                                         MMMM    \n");
            printf("        MMMMJ    MMMM                     JJJ          JJJ          JJJJ         JJJ         JJJ              MMMM     \n");
            printf("        MMMM      J    MMMJ     MMMJ    MMMMMMMM     MMMMMMMJ     MMMMMMMM    JMMMMMMM    MMMMMMMM            MMMM    \n");
            printf("        MMMMMJ         MMMM     MMMM   MMMMMMMMMM   MMMMMMMMMM   MMMMMMMMMM   MMMMMMMMMJ JMMMMMMMMM           MMMM    \n");
            printf("         MMMMMMMM      MMMM     MMMM  JMMMMMJJMMMM MMMMMMJMMMMM MMMMMMJJMMMM JMMMMJ MMMM MMMMM  MMMJ          MMMM  \n");
            printf("          MMMMMMMMM    MMMM     MMMM  MMMMM   JMMMJMMMMM   JMMM MMMMJ   MMMMJ MMMM   J   MMMMJ   J            MMMM  \n");
            printf("            MMMMMMMMJ  MMMM     MMMM  MMMMM        MMMM        JMMMMMMMMMMMMM MMMMMM     JMMMMMM              MMMM  \n");
            printf("               JMMMMM  MMMM     MMMM  MMMMJ       JMMMM        JMMMMMMMMMMMMM  MMMMMMMJ   JMMMMMMM            MMMM     \n");
            printf("                 MMMMM MMMM     MMMM  MMMMJ        MMMM        JMMMMMMMMMMMMM   JMMMMMMM    MMMMMMM           MMMM     \n");
            printf("       JMMMJ     MMMMM MMMM    JMMMM  MMMMJ   MJJ  MMMM    JJJ  MMMM               JMMMMJ     JJMMMM           MM      \n");
            printf("        MMMM    JMMMMM MMMMJ   MMMMM  JMMMM   MMMMJMMMMJ  JMMMM MMMM    JMMJ JMM    JMMMMMMM    MMMM          MMMM      \n");
            printf("        MMMMMMMMMMMMM  JMMMMMMMMMMMM   MMMMMMMMMMM  MMMMMMMMMMM  MMMMMMMMMMMMJMMMJJMMMMMMMMMMJJMMMMM         JMMMMM     \n");
            printf("         MMMMMMMMMMMM   MMMMMMMMMMMM    MMMMMMMMMM   MMMMMMMMMJ  JMMMMMMMMMM  MMMMMMMMMM  MMMMMMMMMM         JMMMMM     \n");
            printf("          JMMMMMMMMJ     JMMMMMM MMM     JMMMMMMJ     MMMMMMMJ     MMMMMMMM    MMMMMMMM    MMMMMMMM           JMMM      \n");
            printf("             JJJJ          JJJ              JJ          JJJ          JJJ          JJJ        JJJ                        \n");
            break;
        }
        else
        {
            fail_n++;
            fail();
            printf("\n");
            printf("                                        		1.continue\n");
            printf("                                                     =============\n");
            printf("                                        		2.exit\n");
            printf("                          		 **                               **    \n");
            printf("                          		 **                               **    \n");
            printf("                               			Please make your choice:");
            scanf("%d", &a);
            printf("                          		 **                               **    \n");
            printf("                          		 **                               **    \n");
            //????
            if (a == 1)
                continue;
        }
        // }
    }
}

void time_judge(void)
{
    struct tm *tblock;
    time_t current_time;
    time(&current_time);
    tblock = localtime(&current_time);
    // tblock -> tm_hour = abs(tblock -> tm_hour - 12);
    printf("			=================================================================\n");
    printf("*                    			1.Today:(%04d.%02d.%02d)                   \n", tblock->tm_year + 1900, tblock->tm_mon + 1, tblock->tm_mday); //????????
    struct tm tomorrow = *tblock;
    tomorrow.tm_mday++;
    mktime(&tomorrow);
    printf("			~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("*                    			2.Tomorrow:(%04d.%02d.%02d)                \n", tomorrow.tm_year + 1900, tomorrow.tm_mon + 1, tomorrow.tm_mday); //????????
    struct tm the_day_after_tomorrow = tomorrow;
    the_day_after_tomorrow.tm_mday++;
    mktime(&the_day_after_tomorrow);
    printf("			~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("*                    			3.The day after tomorrow:(%04d.%02d.%02d)  \n", the_day_after_tomorrow.tm_year + 1900, the_day_after_tomorrow.tm_mon + 1, the_day_after_tomorrow.tm_mday); //????????
    printf("			~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("*                    			4.Exit                                     \n");
    printf("			=================================================================\n");
    printf("\n");
}

void today_judge(void)
{
    // 进行判断,判断今天已经几点了
    // 9-5点
    struct tm *tblock;
    time_t current_time;
    time(&current_time);
    tblock = localtime(&current_time);
    // 创建文件并写入
    FILE *fp;
    fp = fopen("time.txt", "w");
    if (fp == NULL)
    {
        printf("Error opening file!\n");
        return;
    }
    if (tblock->tm_hour < 9 && tblock->tm_hour > 0) // 早上0 - 9，输出一整天的时间表
    {
        printf("        *                                                                              *                         \n");
        printf("       ***                                                                            ***                        \n");
        printf("     *******                                                                        *******                      \n");
        printf("       ***                                                                            ***                        \n");
        printf("        *                        ->->->->->->->->->->->->->->->                        *                         \n");
        for (int i = 9; i <= 17; i++)
        {
            int num = i - 8;
            if (i >= 9 && i <= 12)
            {
                printf("                                     %d. %d:00 am - %d:50 am\n", num, i, i);
                fprintf(fp, "%d. %d:00 am - %d:50 am\n", num, i, i);
            }
            else if (i > 12 && i < 17)
            {
                int i1;
                i1 = abs(i - 12); // 转换到12小时制
                printf("                                     %d. %d:00 pm - %d:50 pm\n", num, i1, i1);
                fprintf(fp, "%d. %d:00 pm - %d:50 pm\n", num, i1, i1);
            }
            numn = num;
        }
        printf("%d. quit\n", numn);
        printf("        *                        <-<-<-<-<-<-<-<-<-<-<-<-<-<-<-                        *                         \n");
        printf("       ***                                                                            ***                        \n");
        printf("     *******                                                                        *******                      \n");
        printf("       ***                                                                            ***                        \n");
        printf("        *                                                                              *                         \n");
        printf("==============================================================================================\n");
    }
    else if (tblock->tm_hour >= 9 && tblock->tm_hour < 12) // 9 - 12之间
    {
        printf("        *                                                                              *                         \n");
        printf("       ***                                                                            ***                        \n");
        printf("     *******                                                                        *******                      \n");
        printf("       ***                                                                            ***                        \n");
        printf("        *                        ->->->->->->->->->->->->->->->                        *                         \n");
        int num = 1;
        for (int i = tblock->tm_hour; i <= 17; i++)
        {
            int flag = i;
            if (flag > 9 && flag <= 12)
            {
                printf("                                     %d. %d:00 am - %d:50 am\n", num, i, i);
                fprintf(fp, "%d. %d:00 am - %d:50 am\n", num, i, i);
            }
            else if (flag > 12 && flag < 17)
            {
                int i1;
                i1 = abs(i - 12); // 转换到12小时制
                printf("                                     %d. %d:00 pm - %d:50 pm\n", num, i1, i1);
                fprintf(fp, "%d. %d:00 pm - %d:50 pm\n", num, i1, i1);
            }
            numn = num;
            num++;
        }
        printf("%d. quit\n", numn);
        printf("        *                        <-<-<-<-<-<-<-<-<-<-<-<-<-<-<-                        *                         \n");
        printf("       ***                                                                            ***                        \n");
        printf("     *******                                                                        *******                      \n");
        printf("       ***                                                                            ***                        \n");
        printf("        *                                                                              *                         \n");
        printf("==============================================================================================\n");
    }
    else if (tblock->tm_hour == 12)
    {
        printf("        *                                                                              *                         \n");
        printf("       ***                                                                            ***                        \n");
        printf("     *******                                                                        *******                      \n");
        printf("       ***                                                                            ***                        \n");
        printf("        *                        ->->->->->->->->->->->->->->->                        *                         \n");
        int num = 1;
        for (int i = tblock->tm_hour; i <= 17; i++)
        {
            int flag = i;
            if (flag == 12)
            {
                printf("                                     %d. %d:00 pm - %d:50 pm\n", num, i, i);
                fprintf(fp, "%d. %d:00 pm - %d:50 pm\n", num, i, i);
            }
            else if (flag > 12 && flag < 17)
            {
                int i1;
                i1 = abs(i - 12); // 转换到12小时制
                printf("                                     %d. %d:00 pm - %d:50 pm\n", num, i1, i1);
                fprintf(fp, "%d. %d:00 pm - %d:50 pm\n", num, i1, i1);
            }
            numn = num;
            num++;
        }
        printf("%d. quit\n", numn);
        //????????
        printf("==============================================================================================\n");
        printf("        *                        <-<-<-<-<-<-<-<-<-<-<-<-<-<-<-                        *                         \n");
        printf("       ***                                                                            ***                        \n");
        printf("     *******                                                                        *******                      \n");
        printf("       ***                                                                            ***                        \n");
        printf("        *                                                                              *                         \n");
        printf("==============================================================================================\n");
    }
    else if (tblock->tm_hour > 12 && tblock->tm_hour < 17) // 12 - 17之间
    {
        printf("        *                                                                              *                         \n");
        printf("       ***                                                                            ***                        \n");
        printf("     *******                                                                        *******                      \n");
        printf("       ***                                                                            ***                        \n");
        printf("        *                        ->->->->->->->->->->->->->->->                        *                         \n");
        int num = 1;
        for (int i = tblock->tm_hour; i <= 17; i++)
        {
            int flag = i + 1;
            if (flag <= 17)
            {
                if (flag > 12 && flag <= 17)
                {
                    int i1;
                    i1 = abs(flag - 12); // 转换到12小时制
                    if (i1 >= 5)
                    {
                        numn = num;
                        break;
                    }
                    printf("                                     %d. %d:00 pm - %d:50 pm\n", num, i1, i1);
                    fprintf(fp, "%d. %d:00 pm - %d:50 pm\n", num, i1, i1);
                }
            }
            numn = num;
            num++;
        }
        printf("                                     %d. quit\n", numn);
        //????????
        printf("        *                        <-<-<-<-<-<-<-<-<-<-<-<-<-<-<-                        *                         \n");
        printf("       ***                                                                            ***                        \n");
        printf("     *******                                                                        *******                      \n");
        printf("       ***                                                                            ***                        \n");
        printf("        *                                                                              *                         \n");
        printf("==============================================================================================\n");
    }
    else if (tblock->tm_hour >= 17 && tblock->tm_hour < 24) // 今天结束了
    {
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        printf("===================================================================================================\n");
        printf("\n");
        printf("          There are no classrooms available today!\n");

        printf("\n");
        printf("===================================================================================================\n");
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    }
    fclose(fp);
    return;
}
void tomorrow_output(void)
{
    FILE *fp;
    fp = fopen("time.txt", "w");
    if (fp == NULL)
    {
        printf("Error opening file!\n");
        return;
    }
    printf("==============================================================================================\n");
    printf("        *                                                                              *                         \n");
    printf("       ***                                                                            ***                        \n");
    printf("     *******                                                                        *******                      \n");
    printf("       ***                                                                            ***                        \n");
    printf("        *                        ->->->->->->->->->->->->->->->                        *                         \n");
    for (int i = 9; i <= 17; i++)
    {
        int num = i - 8;
        if (i >= 9 && i <= 12)
        {
            printf("                                     %d. %d:00 am - %d:50 am\n", num, i, i);
            fprintf(fp, "%d. %d:00 am - %d:50 am\n", num, i, i);
        }
        else if (i > 12 && i < 17)
        {
            int i1;
            i1 = abs(i - 12);
            printf("                                     %d. %d:00 pm - %d:50 pm\n", num, i1, i1);
            fprintf(fp, "%d. %d:00 pm - %d:50 pm\n", num, i1, i1);
        }
        numn = num;
    }
    printf("                                     %d. quit\n", numn);
    //????????
    printf("        *                        <-<-<-<-<-<-<-<-<-<-<-<-<-<-<-                        *                         \n");
    printf("       ***                                                                            ***                        \n");
    printf("     *******                                                                        *******                      \n");
    printf("       ***                                                                            ***                        \n");
    printf("        *                                                                              *                         \n");
    printf("==============================================================================================\n");
    fclose(fp);
    return;
}

void next_output(void)
{
    FILE *fp;
    fp = fopen("time.txt", "w");
    if (fp == NULL)
    {
        printf("Error opening file!\n");
        return;
    }
    printf("==============================================================================================\n");
    printf("        *                                                                              *                         \n");
    printf("       ***                                                                            ***                        \n");
    printf("     *******                                                                        *******                      \n");
    printf("       ***                                                                            ***                        \n");
    printf("        *                        ->->->->->->->->->->->->->->->                        *                         \n");
    for (int i = 9; i <= 17; i++)
    {
        int num = i - 8;
        if (i >= 9 && i <= 12)
        {
            printf("                                     %d. %d:00 am - %d:50 am\n", num, i, i);
            fprintf(fp, "%d. %d:00 am - %d:50 am\n", num, i, i);
        }
        else if (i > 12 && i < 17)
        {
            int i1;
            i1 = abs(i - 12);
            printf("                                     %d. %d:00 pm - %d:50 pm\n", num, i1, i1);
            fprintf(fp, "%d. %d:00 pm - %d:50 pm\n", num, i1, i1);
        }
        numn = num;
    }
    printf("                                     %d. quit\n", numn);
    //????????
    printf("        *                        <-<-<-<-<-<-<-<-<-<-<-<-<-<-<-                        *                         \n");
    printf("       ***                                                                            ***                        \n");
    printf("     *******                                                                        *******                      \n");
    printf("       ***                                                                            ***                        \n");
    printf("        *                                                                              *                         \n");
    printf("==============================================================================================\n");
    fclose(fp);
    return;
}

void room_judge(int input)
{
    FILE *fp;
    fp = fopen("time.txt", "r");
    char line[50];
    while (fgets(line, 50, fp) != NULL)
    {
        int num;
        char time[50];
        if (sscanf(line, "%d. %s", &num, time) == 2)
        {
            if (num == input)
            {
                // printf("The time is %s\n", time);
                strcpy(time_flag, time);
                break;
            }
        }
    }
    fclose(fp);
    return;
}

void room_output(int room_size, int total_room, char *time, int day)
{
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("===================================================================================================\n");
    printf("\n");
    printf("                             Please enter your desired classroom size:\n");
    FILE *fp;
    char line[100];
    int num = 1;
    FILE *output_file = fopen("classroom.txt", "w");
    for (int i = 0; i < total_room; i++)
    {
        char filename[15];
        sprintf(filename, "C%d.txt", i + 1);
        fp = fopen(filename, "r");
        if (fgets(line, sizeof(line), fp) != NULL)
        { // 逐行读取
            line[strcspn(line, "\n")] = '\0';
            int file_room_size = atoi(line);
            if (file_room_size < room_size)
            { // 确定大小
                fclose(fp);
                continue;
            }
        }
        int today_flag = 0, found_flag = 0;
        while (fgets(line, sizeof(line), fp) != NULL)
        { // 检索对应模块
            line[strcspn(line, "\n")] = '\0';
            if (strcmp(line, "Today") == 0)
            { // 进行检查
                today_flag = 1;
                continue;
            }
            else if (strcmp(line, "Tomorrow") == 0)
            {
                today_flag = 2;
                continue;
            }
            else if (strcmp(line, "The day after Tomorrow") == 0)
            {
                today_flag = 3;
                continue;
            }
            if (today_flag == day && strstr(line, time) != NULL && strstr(line, "|: yes") != NULL)
            {
                found_flag = 1;
                break;
            }
        }
        if (found_flag)
        {
            printf("%d. C%d\n", num, i + 1);
            fprintf(output_file, "%d. C%d\n", num, i + 1);
            num++;
        }
        fclose(fp);
    }
    fclose(output_file);
    printf("\n");
    printf("===================================================================================================\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
}

void book(int class, char *time_flag, int day)
{ // 直接替换新文件hhh
    char filename[20];
    char filename_ss[20];
    FILE *file = fopen("classroom.txt", "r");
    char line[100];
    int flag_class = 1;
    while (fgets(line, sizeof(line), file) != NULL)
    {
        line[strcspn(line, "\n")] = '\0';
        if (flag_class == class)
        {
            sscanf(line, "%*d. %s", filename_ss);
            break;
        }
        flag_class++;
    }
    fclose(file);
    sprintf(filename, "%s.txt", filename_ss);
    FILE *fp = fopen(filename, "r");
    FILE *temp_fp = fopen("temp.txt", "w");
    char file_line[100];
    int current_day = 0;
    int modify_flag = 0;
    while (fgets(file_line, sizeof(file_line), fp) != NULL)
    {
        file_line[strcspn(file_line, "\n")] = '\0';
        if (strcmp(file_line, "Today") == 0)
        {
            current_day = 1;
            fprintf(temp_fp, "%s\n", file_line);
            continue;
        }
        else if (strcmp(file_line, "Tomorrow") == 0)
        {
            current_day = 2;
            fprintf(temp_fp, "%s\n", file_line);
            continue;
        }
        else if (strcmp(file_line, "The day after Tomorrow") == 0)
        {
            current_day = 3;
            fprintf(temp_fp, "%s\n", file_line);
            continue;
        }
        if (current_day == day && strstr(file_line, time_flag) != NULL && strstr(file_line, "|: yes") != NULL)
        {
            char *flag = strstr(file_line, "|: yes");
            strcpy(flag, "|: no");
            modify_flag = 1;
        }

        fprintf(temp_fp, "%s\n", file_line);
    }

    fclose(fp);
    fclose(temp_fp);
    remove(filename);
    rename("temp.txt", filename); // 被替换的文件
}

void fail(void)
{
    printf("                                                                                                                         \n");
    printf("                                                                                                                         \n");
    printf("                                                               MMMMMM       MMMMMM                                       \n");
    printf("            JMMMMMMMMMMMMMMMMMMMJ                             JMMMMMMMM    JMMMMMMMM                  JMMMMMMJ           \n");
    printf("            JMMMMMMMMMMMMMMMMMMMMM                            JMMMMMMMM    JMMMMMMMM                  JMMMMMMMM          \n");
    printf("            JMMMMMMMMMMMMMMMMMMMMM                              JMMMMMJ    JMMMMMMMM                  JMMMMMMMM          \n");
    printf("            JMMMMMMMM                                                      JMMMMMMMM                  JMMMMMMMM          \n");
    printf("            JMMMMMMMM                  JMMMMMMMMMMMM           MMMMMM      JMMMMMMMM                   MMMMMMMM          \n");
    printf("            JMMMMMMMM                JMMMMMMMMMMMMMMMMJ       JMMMMMMMM    JMMMMMMMM                   MMMMMMMM          \n");
    printf("            JMMMMMMMM               JMMMMMMMMMMMMMMMMMMMJ     JMMMMMMMM    JMMMMMMMM                   MMMMMMMM          \n");
    printf("            JMMMMMMMMMMMMMMMMMMJ      MMMMMMM    JMMMMMMMJ    JMMMMMMMM    JMMMMMMMM                   MMMMMMMM          \n");
    printf("            JMMMMMMMMMMMMMMMMMMMMJ           JJJJJMMMMMMMM    JMMMMMMMM    JMMMMMMMM                   MMMMMMMM          \n");
    printf("            JMMMMMMMMMMMMMMMMMMMMJ    JMMMMMMMMMMMMMMMMMMM    JMMMMMMMM    JMMMMMMMM                   MMMMMMMJ          \n");
    printf("            JMMMMMMMM               MMMMMMMMMMMMMMMMMMMMMM    JMMMMMMMM    JMMMMMMMM                   MMMMMMMJ          \n");
    printf("            JMMMMMMMM              MMMMMMMMMMMJ  JMMMMMMMM    JMMMMMMMM    JMMMMMMMM                     MMMMMJ          \n");
    printf("            JMMMMMMMM             JMMMMMMMMJ     JMMMMMMMM    JMMMMMMMM    JMMMMMMMM                                     \n");
    printf("            JMMMMMMMM              MMMMMMMMJ   JMMMMMMMMMM    JMMMMMMMM    JMMMMMMMM                  JMMMMMM            \n");
    printf("            JMMMMMMMM               MMMMMMMMMMMMMMMMMMMMMM    JMMMMMMMM    JMMMMMMMM                  JMMMMMMMM          \n");
    printf("            JMMMMMMMM                JMMMMMMMMMMMMMMMMMMMM    JMMMMMMMM    JMMMMMMMM                  JMMMMMMMM          \n");
    printf("              JMMMMMM                   JMMMMMMMMJ  MMMMMM      JMMMMMM      JMMMMMM                    JMMMMMM          \n");
    printf("\n");
    printf("=========================================================================================================================\n");
}