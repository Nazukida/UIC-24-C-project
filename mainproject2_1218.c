#include<stdio.h>
#include<string.h>
#include<conio.h>
#include<stdbool.h>
#include<time.h>
#include<math.h>
#include<stdlib.h>
#include<windows.h>
char time_flag[50];
int num_class = 0;
int numn;
struct t
{
    char time_express[30];
}time_e[8];
struct classroom
{
    char can_book_0[9];
    char can_book_1[9];
    char can_book_2[9];
    char filename[10];
    char name[10];
    char size[10];
} c[1000];

void set_classroom();
void initialize(struct classroom c);
//void book(struct classroom c, int a);
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
void room_output(int room_size, int total_room, char *time);
void book(int class, char *time_flag, int day);
int main()
{
    init();
    set_classroom();
    int day_reserve;
    FILE *fp;
    struct tm *tblock;
    time_t current_time;
    time(&current_time);
    tblock = localtime(&current_time);
    fp=fopen("date.txt","r");
    fscanf(fp,"%d",&day_reserve);
    //printf("(%d)\n",day_reserve);
    //printf("(%d)\n",tblock->tm_mday);
    //printf("%d",day_reserve!=(tblock->tm_mday));
    fclose(fp);
    if(day_reserve!=(tblock->tm_mday))
    {
        printf("need refresh\n");
        refresh();
    }
    fp=fopen("date.txt","w");
        fprintf(fp,"%d",tblock->tm_mday);
    fclose(fp);
    judgement();
    day_choose();
    return 0;
}
void init(void)
{
    num_class=0;
    FILE*p;
    p=fopen("Classroom_info.txt","r");
    while(fscanf(p,"%s%s",c[num_class].name,c[num_class].size)!=EOF)
        num_class++;
    strcpy(time_e[0].time_express,"9:00 am - 9:50 am   |");
    strcpy(time_e[1].time_express,"10:00 am - 10:50 am |");
    strcpy(time_e[2].time_express,"11:00 am - 11:50 am |");
    strcpy(time_e[3].time_express,"12:00 am - 12:50 am |");
    strcpy(time_e[4].time_express,"1:00 pm - 1:50 pm   |");
    strcpy(time_e[5].time_express,"2:00 pm - 2:50 pm   |");
    strcpy(time_e[6].time_express,"3:00 pm - 3:50 pm   |");
    strcpy(time_e[7].time_express,"4:00 pm - 4:50 pm   |");
    fclose(p);
}

void day_choose()
{
    struct tm *tblock;
    time_t current_time;
    time(&current_time);
    tblock = localtime(&current_time);
    time_judge();
    int input;//选择时间
    int time_choice;
    int room_size;
    int class;
    while (1)
    {
        printf("Please make your choice: 1. Today 2. Tomorrow 3. The day after tomorrow 4. Quit\n");
        scanf("%d", &input);
        while (1)
        {
            if (input == 1)
            {
                today_judge();
                if (tblock -> tm_hour >= 17)
                {
                    break;
                }else
                {
                    scanf("%d", &time_choice);
                    if (time_choice == numn)
                    {
                        break;
                    }
                    room_judge(time_choice);
                    printf("Please input room size: ");
                    scanf("%d", &room_size);
                    room_output(room_size, num_class, time_flag);
                    printf("Please input the number of the classroom you want to book: ");
                    scanf("%d", &class);
                    book(class, time_flag, input);
                    break;
                }
            }else if (input == 2)
            {
                tomorrow_output();
                scanf("%d", &time_choice);
                if (time_choice == numn)
                {
                    break;
                }
                room_judge(time_choice);
                printf("Please input room size: ");
                scanf("%d", &room_size);
                room_output(room_size, num_class, time_flag);
                printf("Please input the number of the classroom you want to book: ");
                scanf("%d", &class);
                book(class, time_flag, input);
                break;
            }else if (input == 3)
            {
                next_output();
                scanf("%d", &time_choice);
                if (time_choice == numn)
                {
                    break;
                }
                room_judge(time_choice);
                printf("Please input room size: ");
                scanf("%d", &room_size);
                room_output(room_size, num_class, time_flag);
                printf("Please input the number of the classroom you want to book: ");
                scanf("%d", &class);
                book(class, time_flag, input);
                break;
            }else if (input == 4)
            {
                printf("Quit, thanks for using!\n");
                break;
            }else
            {
                printf("Please input valid number!\n");
            }
        }
        printf("continue? 1. yes 2. no\n");
        int continue_judge;
        scanf("%d", &continue_judge);
        if (continue_judge == 1)
        {
            continue;
        }else if (continue_judge == 2)
        {
            return;
        }else
        {
            printf("Please input valid number!\n");
            continue;
        }
    }
    return;
}

void set_classroom()
{
    num_class=0;
    char r;
    FILE *p;
    p = fopen("Classroom_info.txt", "r");
    int n = 0, s = 0;
    while(fscanf(p,"%s%s",c[num_class].name,c[num_class].size)!=EOF)
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
//111111111111111111111111111111111111111111111111111111
void refresh()
{
    num_class=0;
    char r;
    FILE *p;
    p = fopen("Classroom_info.txt", "r");
    int n = 0, s = 0;
    FILE *fp;
    char skip[50];
    char ch;
    char judge[3];
    while(fscanf(p,"%s%s",c[num_class].name,c[num_class].size)!=EOF)
    {
        strcpy(c[num_class].filename, c[num_class].name);
        strcat(c[num_class].filename, ".txt");
        fp=fopen(c[num_class].filename,"r");
        //printf("%s",c[num_class].filename);
        while(ch=fgetc(fp),ch!='w');
        for(int i=0;i<8;i++)
        {
            while(ch=fgetc(fp),ch!='|');
            fscanf(fp,": %s",judge);
            //printf("(%s)",judge);
            if(strcmp(judge,"yes")==0)
                c[num_class].can_book_0[i]='y';
            else
                c[num_class].can_book_0[i]='n';
        }
        while(ch=fgetc(fp),ch!='w');
        for(int i=0;i<8;i++)
        {
            while(ch=fgetc(fp),ch!='|');
            fscanf(fp,": %s",judge);
            //printf("(%s)",judge);
            if(strcmp(judge,"yes")==0)
                c[num_class].can_book_1[i]='y';
            else
                c[num_class].can_book_1[i]='n';
        }
        strcpy(c[num_class].can_book_2, "yyyyyyyy");

        //printf("%s %s %s\n",c[num_class].can_book_0,c[num_class].can_book_1,c[num_class].can_book_2);
        fclose(fp);
        initialize(c[num_class]);
        num_class++;
    }
    fclose(p);
}
//111111111111111111111111111111111111111111111111111111

void initialize(struct classroom a)
{
    FILE *fp;
    fp = fopen(a.filename,"w");
    fprintf(fp,"%s\n",a.size);
    fprintf(fp,"Today\n");
    for(int i=0;i<8;i++)
    {
        //printf("%c ",a.can_book_0[i]);
        if(a.can_book_0[i]=='y')
            fprintf(fp,"%s: yes\n",time_e[i].time_express);
        else
            fprintf(fp,"%s: no \n",time_e[i].time_express);
    }
    //printf("\n");
    fprintf(fp,"Tomorrow\n");
    for(int i=0;i<8;i++)
    {
        //printf("%c ",a.can_book_1[i]);
        if(a.can_book_1[i]=='y')
            fprintf(fp,"%s: yes\n",time_e[i].time_express);
        else
            fprintf(fp,"%s: no \n",time_e[i].time_express);
    }
    //printf("\n");
    fprintf(fp,"The day after Tomorrow\n");
    for(int i=0;i<8;i++)
    {
        //printf("%c ",a.can_book_2[i]);
        if(a.can_book_2[i]=='y')
            fprintf(fp,"%s: yes\n",time_e[i].time_express);
        else
            fprintf(fp,"%s: no \n",time_e[i].time_express);
    }
    //printf("\n");
    fclose(fp);
    return;
}

bool login_hide()
{
    FILE *fp;
    int judge=0;
    int n,p;
    //define txt get
    char name[50];int nlen;
    char password[50];int plen;
    nlen=strlen(name);
    plen=strlen(password);

    //define user input
    char name_j[50];int nlen_j;
    char password_j[50];int plen_j;
    printf("===============================================================\n");
    printf("please enter your user's name: ");
    //printf("\n===============================================================\r\b");
    scanf("%s",name_j);
    //scanf("%s",password_j);
    char temp;
    int num=0;
    printf("\n===============================================================\n");
    printf("please enter your password: ");
    //printf("\n===============================================================\r\b");
    
    while(temp=getch(),temp!=13)
    {
        if(temp==8&&num!=0)
        {
            printf("\b \b");
            num--;
        }
        else if(num==0&&temp==8)
            continue;
        else
        {
            printf("*");
            password_j[num++]=temp;
        }
    }
    nlen_j=strlen(name_j);
    plen_j=num;
    //printf("%s",name_j);
    //printf("%s\n",password_j);

    //check
    char c;
    fp = fopen("account.txt","r");
    while(fscanf(fp,"%s%s",name,password)!=EOF&&!judge)
    {
        //printf("\nname:%s; password:%s;",name,password);
        nlen=strlen(name);
        plen=strlen(password);
        if(nlen==nlen_j&&plen==plen_j)
        {
            //printf("success judge length: \n");
            judge=1;
            //printf("judge name: \n");
            for(int i=0;i<nlen;i++)
            {
                //printf("%c : %c\n",name[i],name_j[i]);
                if(name[i]!=name_j[i])
                {
                    judge=0;
                    break;
                }
            }
            //printf("judge password: \n");
            for(int i=0;i<plen;i++)
            {
                //printf("%c : %c\n",password[i],password_j[i]);
                if(password[i]!=password_j[i])
                {
                    judge=0;
                    break;
                }
            }
        }
    }
    fclose(fp);
    if(judge)
        return true;
    else
        return false;
}

void judgement(void)
{
    while(1)
    {
        if(login_hide())
        {
            printf("\n===============================================================");
            printf("\n=                    successfully login!                      =\n");
            printf("===============================================================\n");
            break;
        }
        else
        {
            printf("\n===============================================================");
            printf("\n=                   login unsuccessfully!                     =\n");
            printf("===============================================================\n");
        }
    }
    Sleep(1000);
    system("cls");
}

void time_judge(void){
    struct tm *tblock;
    time_t current_time;
    time(&current_time);
    tblock = localtime(&current_time);
    tblock -> tm_mon += 1;
    tblock -> tm_year += 1900;
    // tblock -> tm_hour = abs(tblock -> tm_hour - 12);
    printf("Today is %d %d %d\n", tblock->tm_year, tblock->tm_mon, tblock->tm_mday);
    printf("Now is %d:%d\n", tblock->tm_hour, tblock->tm_min);
}

void today_judge(void){
    //进行判断,判断今天已经几点了
    //9-5点
    struct tm *tblock;
    time_t current_time;
    time(&current_time);
    tblock = localtime(&current_time);
    //创建文件并写入
    FILE *fp;
    fp = fopen("time.txt", "w");
    if (fp == NULL)
    {
        printf("Error opening file!\n");
        return;
    }
    if (tblock -> tm_hour < 9 && tblock -> tm_hour > 0)//早上0 - 9，输出一整天的时间表
    {
        for (int i = 9; i <= 17; i++)
        {
            int num = i - 8;
            if (i >= 9 && i <= 12)
            {
                printf("%d. %d:00 am - %d:50 am\n", num, i, i);
                fprintf(fp, "%d. %d:00 am - %d:50 am\n", num, i, i);
            }else if (i > 12 && i < 17)
            {
                int i1;
                i1 = abs(i - 12);//转换到12小时制
                printf("%d. %d:00 pm - %d:50 pm\n", num, i1, i1);
                fprintf(fp, "%d. %d:00 pm - %d:50 pm\n", num, i1, i1);
            }
            numn = num;
        }
        printf("%d. quit\n", numn);
    }else if (tblock -> tm_hour >= 9 && tblock -> tm_hour < 12)//9 - 12之间
    {
        int num = 1;
        for (int i = tblock -> tm_hour; i <= 17; i++)
        {
            int flag = i;
            if (flag > 9 && flag <= 12)
            {
                printf("%d. %d:00 am - %d:50 am\n", num, i, i);
                fprintf(fp, "%d. %d:00 am - %d:50 am\n", num, i, i);
            }else if (flag > 12 && flag < 17)
            {
                int i1;
                i1 = abs(i - 12);//转换到12小时制
                printf("%d. %d:00 pm - %d:50 pm\n", num, i1, i1);
                fprintf(fp, "%d. %d:00 pm - %d:50 pm\n", num, i1, i1);
            }
            numn = num;
            num++;
        }
        printf("%d. quit\n", numn);
        
    }else if (tblock -> tm_hour == 12)
    {
        int num = 1;
        for (int i = tblock -> tm_hour; i <= 17; i++)
        {
            int flag = i;
            if (flag == 12)
            {
                printf("%d. %d:00 pm - %d:50 pm\n", num, i, i);
                fprintf(fp, "%d. %d:00 pm - %d:50 pm\n", num, i, i);
            }else if (flag > 12 && flag < 17)
            {
                int i1;
                i1 = abs(i - 12);//转换到12小时制
                printf("%d. %d:00 pm - %d:50 pm\n", num, i1, i1);
                fprintf(fp, "%d. %d:00 pm - %d:50 pm\n", num, i1, i1);
            }
            numn = num;
            num++;
        }
        printf("%d. quit\n", numn);
    }else if (tblock -> tm_hour > 12 && tblock -> tm_hour < 17)//12 - 17之间
    {
        int num = 1;
        for (int i = tblock -> tm_hour; i <= 17; i++)
        {
            int flag = i + 1;
            if (flag <= 17)
            {
                if (flag > 12 && flag <= 17)
                {
                    int i1;
                    i1 = abs(i - 12);//转换到12小时制
                    printf("%d. %d:00 pm - %d:50 pm\n", num, i1, i1);
                    fprintf(fp, "%d. %d:00 pm - %d:50 pm\n", num, i1, i1);
                }
            }
            numn = num;
            num++;
        }
        printf("%d. quit\n", numn);
    }else if(tblock -> tm_hour >= 17 && tblock -> tm_hour < 24)//今天结束了
    {
        printf("There are no classrooms available today!\n");
    }
    fclose(fp);
    return;
}
void tomorrow_output(void){
    FILE *fp;
    fp = fopen("time.txt", "w");
    if (fp == NULL)
    {
        printf("Error opening file!\n");
        return;
    }
    for (int i = 9; i <= 17; i++)
    {
        int num = i - 8;
        if (i >= 9 && i <= 12)
        {
            printf("%d. %d:00 am - %d:50 am\n", num, i, i);
            fprintf(fp, "%d. %d:00 am - %d:50 am\n", num, i, i);
        }else if (i > 12 && i < 17) 
        {
            int i1;
            i1 = abs(i - 12);
            printf("%d. %d:00 pm - %d:50 pm\n", num, i1, i1);
            fprintf(fp, "%d. %d:00 pm - %d:50 pm\n", num, i1, i1);
        }
        numn = num;
    }
    printf("%d. quit\n", numn);
    fclose(fp);
    return;
}

void next_output(void){
    FILE *fp;
    fp = fopen("time.txt", "w");
    if (fp == NULL)
    {
        printf("Error opening file!\n");
        return;
    }
    for (int i = 9; i <= 17; i++)
    {
        int num = i - 8;
        if (i >= 9 && i <= 12)
        {
            printf("%d. %d:00 am - %d:50 am\n", num, i, i);
            fprintf(fp, "%d. %d:00 am - %d:50 am\n", num, i, i);
        }else if (i > 12 && i < 17) 
        {
            int i1;
            i1 = abs(i - 12);
            printf("%d. %d:00 pm - %d:50 pm\n", num, i1, i1);
            fprintf(fp, "%d. %d:00 pm - %d:50 pm\n", num, i1, i1);
        }
        numn = num;
    }
    printf("%d. quit\n", numn);
    fclose(fp);
    return;
}

void room_judge(int input) {
    FILE *fp;
    fp = fopen("time.txt", "r");
    char line[50];
    while (fgets(line, 50, fp)!= NULL) {
        int num;
        char time[50];
        if (sscanf(line, "%d. %s", &num, time) == 2) {
            if (num == input) {
                printf("The time is %s\n", time);
                strcpy(time_flag, time);
                break;
            }
        }
    }
    fclose(fp);
    return;
}

void room_output(int room_size, int total_room, char *time) {
    FILE *fp[total_room];
    char line[100];
    char classroom_size[20];
    sprintf(classroom_size, "%d", room_size);

    for (int i = 0; i < total_room; i++) {
        int num = 1;
        char filename[15];
        sprintf(filename, "C%d.txt", i + 1);
        fp[i] = fopen(filename, "r");
        if (fp[i]!= NULL) {
            if (fgets(line, sizeof(line), fp[i])!= NULL) {
                line[strcspn(line, "\n")] = '\0';
                int file_room_size = atoi(line);
                if (file_room_size >= room_size) {
                    fseek(fp[i], 0, SEEK_SET);
                    int found_flag = 0;
                    while (fgets(line, sizeof(line), fp[i])!= NULL) {
                        line[strcspn(line, "\n")] = '\0';
                        if (strstr(line, time)!= NULL && strstr(line, "|: yes")!= NULL) {
                            found_flag = 1;
                            break;
                        }
                    }
                    if (found_flag) {
                        printf("%d. C%d\n", num, i + 1);
                    }
                }
            }
            fclose(fp[i]);
        } 
    }
}
void book(int class, char *time_flag, int day) {
    char filename[20];
    sprintf(filename, "C%d.txt", class);
    FILE *fp = fopen(filename, "w+");
    char line[100];
    int flag_day = 0;
    while (fgets(line, sizeof(line), fp)!= NULL) {
        line[strcspn(line, "\n")] = '\0';
        if ((day == 1 && strcmp(line, "Today") == 0) || (day == 2 && strcmp(line, "Tomorrow") == 0) ||(day == 3 && strcmp(line, "The day after Tomorrow") == 0)) {
            flag_day = 1;
            continue;
        }
        if (flag_day) {
            if (strstr(line, time_flag)!= NULL && strstr(line, "|: yes")!= NULL) {
                char *flag = strstr(line, "|: yes");
                strcpy(flag, "|: no");
                fseek(fp, -strlen(line) - 1, SEEK_CUR);//移动光标
                fputs(line, fp);//覆盖输出
                break;
            }
        }
    }
    fclose(fp);
}

