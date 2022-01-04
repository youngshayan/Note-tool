/*
 * Programmer: Shayan Mansornia     Start :12/5/2021    Finish :12/28/2021
 * Instructor: Seyyed Amir Hadi Minoofam
 * Term 1
 * note tools programme
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
int notesCount = 0;

typedef struct note{
    int month;
    int day;
    int year;
    int hour;
    int minute;
    char comment[1000];
}NOTE;

typedef struct hour{
    NOTE* note[60];
    int hour;
    int count;
    struct hour* left;
    struct hour* right;
}hourNode;

typedef struct dayNode{
    int day;
    struct dayNode* left;
    struct dayNode* right;
    hourNode* hourRoot;
}dayNode;

typedef struct monthNode{
    int month;
    struct monthNode* left;
    struct monthNode* right;
    dayNode* dayRoot;
}monthNode;

typedef struct yearNode{
    int year;
    struct yearNode* left;
    struct yearNode* right;
    monthNode* monthRoot;
}yearNode;

yearNode* searchYearNode(yearNode* yearRoot,int year)
{   if(yearRoot == NULL)
        return NULL;

    if(yearRoot->year==year)
    {
        return yearRoot;

    }

    else if(yearRoot->year<year)
    {
        return searchYearNode(yearRoot->right,year);
    }

    else if(yearRoot->year>year)
    {
        return searchYearNode(yearRoot->left,year);
    }


    return yearRoot;
}

yearNode* newYearNode(int year)
{
    yearNode* newnode = (yearNode*)malloc(sizeof(yearNode));
    newnode->year=year;
    newnode->left=NULL;
    newnode->right=NULL;
    newnode->monthRoot=NULL;
    return newnode;
}

yearNode* insertYearNode(yearNode* yearRoot,int year)
{
    if(yearRoot == NULL)
        return newYearNode(year);
    else if(year<yearRoot->year)
        yearRoot->left = insertYearNode(yearRoot->left,year);
    else if(year>yearRoot->year)
        yearRoot->right = insertYearNode(yearRoot->right,year);
    return yearRoot;

}

monthNode* newMonthNode(int month)
{
    monthNode* newnode = (monthNode*)malloc(sizeof(monthNode));
    newnode->month=month;
    newnode->left=NULL;
    newnode->right=NULL;
    newnode->dayRoot=NULL;
    return newnode;
}

monthNode* insertMonthNode(monthNode* monthRoot,int month)
{
    if(monthRoot == NULL)
        return newMonthNode(month);
    else if(month<monthRoot->month)
        monthRoot->left = insertMonthNode(monthRoot->left,month);
    else if(month>monthRoot->month)
        monthRoot->right=insertMonthNode(monthRoot->right,month);
    return monthRoot;

}

monthNode* searchMonthNode(monthNode* monthRoot,int month)
{
    if(monthRoot==NULL)
        return NULL;
    if(monthRoot->month==month)
        return monthRoot;
    else if(monthRoot->month<month)
        return searchMonthNode(monthRoot->right,month);
    else if(monthRoot->month>month)
        return searchMonthNode(monthRoot->left,month);
    return monthRoot;
}

dayNode* newDayNode(int day)
{
    dayNode* newnode = (dayNode*)malloc(sizeof(dayNode));
    newnode->day=day;
    newnode->left=NULL;
    newnode->right=NULL;
    newnode->hourRoot=NULL;
    return newnode;
}

dayNode* insertDayNode(dayNode* dayRoot,int day)
{
    if(dayRoot == NULL)
        return newDayNode(day);
    else if(day<dayRoot->day)
        dayRoot->left = insertDayNode(dayRoot->left,day);
    else if(day>dayRoot->day)
        dayRoot->right = insertDayNode(dayRoot->right,day);
    return dayRoot;

}

dayNode* searchDayNode(dayNode* dayRoot,int day)
{
    if(dayRoot==NULL)
        return NULL;
    if(dayRoot->day==day)
        return dayRoot;
    else if(dayRoot->day<day)
        return searchDayNode(dayRoot->right,day);
    else if(dayRoot->day>day)
        return searchDayNode(dayRoot->left,day);
    return dayRoot;
}

hourNode* newHourNode(int hour)
{
    hourNode* newnode = (hourNode*)malloc(sizeof(hourNode));
    newnode->hour=hour;
    newnode->left=NULL;
    newnode->right=NULL;
    newnode->count=-1;
    return newnode;

}

hourNode* insertHourNode(hourNode* hourRoot,int hour)
{
    if(hourRoot == NULL)
        return newHourNode(hour);
    else if(hour<hourRoot->hour)
        hourRoot->left = insertHourNode(hourRoot->left,hour);
    else if(hour>hourRoot->hour)
        hourRoot->right = insertHourNode(hourRoot->right,hour);
    return hourRoot;

}

hourNode* searchHourNode(hourNode* hourRoot,int hour)
{
    if(hourRoot==NULL)
        return NULL;
    if(hourRoot->hour==hour)
        return hourRoot;
    else if(hourRoot->hour<hour)
        return searchHourNode(hourRoot->right,hour);
    else if(hourRoot->hour>hour)
        return searchHourNode(hourRoot->left,hour);
    return hourRoot;
}



yearNode* insert(yearNode* yearRoot,NOTE* note)
{


    yearNode* year_node = searchYearNode(yearRoot,note->year);
    if(year_node == NULL)
    {
        yearRoot = insertYearNode(yearRoot,note->year);
        year_node = searchYearNode(yearRoot,note->year);
    }
    monthNode* month_node = searchMonthNode(year_node->monthRoot,note->month);
    if(month_node == NULL)
    {
        year_node->monthRoot = insertMonthNode(year_node->monthRoot,note->month);
        month_node = searchMonthNode(year_node->monthRoot,note->month);
    }
    dayNode* day_node = searchDayNode(month_node->dayRoot,note->day);
    if(day_node == NULL)
    {
        month_node->dayRoot = insertDayNode(month_node->dayRoot,note->day);
        day_node = searchDayNode(month_node->dayRoot,note->day);
    }
    hourNode* hour_node = searchHourNode(day_node->hourRoot,note->hour);
    if(hour_node == NULL)
    {
        day_node->hourRoot = insertHourNode(day_node->hourRoot,note->hour);
        hour_node = searchHourNode(day_node->hourRoot,note->hour);
    }
    (hour_node->count)++;

    hour_node->note[hour_node->count]=note;



    return yearRoot;
}

int validation(int year,int month,int day,int hour,int minute)
{   system("cls");

    int flag=0;
    system("color 0c");
    if(year<=0||year>2500)
    {
        printf("\n\n\tEntered Year is Invalid ...");
        flag=1;
    }
    if(month<=0||month>12)
    {
        printf("\n\n\tEntered Month is Invalid ...");
        flag=1;
    }
    if(day<=0||day>31)
    {
        printf("\n\n\tEntered Day is Invalid...");
        flag=1;
    }
    if(hour<0||hour>23)
    {
        printf("\n\n\tEntered Hour is Invalid...");
        flag=1;
    }
    if(minute<0||minute>59)
    {
        printf("\n\n\tEntered Minute is Invalid...");
        flag=1;
    }
    if(flag==1)
    {
        printf("\n\n\n\n\n");
        system("pause");
        system("cls");

    }

    return flag;
}

yearNode* setReminder(yearNode* yearRoot,FILE* fp)
{
    int month;
    int day;
    int year;
    int hour;
    int minute;
    int validFlag=0;
    NOTE* note = NULL;
    char comment[1000];
    if(fp==NULL)
    {
        do
        {

            system("color 0b");
            system("cls");
            printf("\n--------------------------------------------------------------------------------\n");
            printf("                                 SET REMINDER \n");
            printf("--------------------------------------------------------------------------------\n\n");
            printf("Enter the date(dd-mm-yyyy) :");
            scanf("%d-%d-%d",&day,&month,&year);
            validFlag=validation(year,month,day,1,1);
        }while(validFlag!=0);
        do
        {
            printf("\n--------------------------------------------------------------------------------\n");
            printf("                                 SET REMINDER \n");
            printf("--------------------------------------------------------------------------------\n\n");
            system("color 0b");
            printf("Enter the time (hh:mm) in 24 format:");
            scanf("%d:%d",&hour,&minute);
            validFlag=validation(1,1,1,hour,minute);
        }while(validFlag!=0);
        system("color 0b");
        printf("\n--------------------------------------------------------------------------------\n");
        printf("                                 SET REMINDER \n");
        printf("--------------------------------------------------------------------------------\n\n");
        system("color 0b");
        printf("Enter any comment regarding the reminder : ");
        fflush(stdin);
        gets(comment);
        notesCount++;
        note = (NOTE*)malloc(sizeof(NOTE));
        note->month=month;
        note->day=day;
        note->year=year;
        note->hour=hour;
        note->minute=minute;
        strcpy(note->comment,comment);
        yearRoot = insert(yearRoot,note);
    }
    else
    {
        int count=0;
        fscanf(fp,"%d",&count);
        notesCount=count;
        while(count>0)
        {
            fscanf(fp,"%d-%d-%d",&day,&month,&year);
            fscanf(fp,"%d:%d",&hour,&minute);

            int index =0;
            char ch=fgetc(fp);
            while(ch=='\n')
                ch=fgetc(fp);
            do
            {
                comment[index]=ch;
                ch=fgetc(fp);

                index++;
            }while(ch!='\0'&&ch!='\n'&&ch!=EOF);
            comment[index]='\0';


            note = (NOTE*)malloc(sizeof(NOTE));
            note->month=month;
            note->day=day;
            note->year=year;
            note->hour=hour;
            note->minute=minute;
            strcpy(note->comment,comment);
            yearRoot = insert(yearRoot,note);
            count--;
        }
    }


    return yearRoot;

}

int dayReminder(hourNode* hourRoot,FILE* fp,int flag)
{
    if(hourRoot!=NULL)
    {
        int count=hourRoot->count;
        dayReminder(hourRoot->left,fp,flag);
        int fileFlag=0;
        while(count>=0)
        {
            if(fp==NULL)
                printf("                          |  * TIME [24 hour format] %02d:%02d\n\n                           ---> REMINDER: %s\n\n",hourRoot->note[count]->hour,
                       hourRoot->note[count]->minute,hourRoot->note[count]->comment);
            else
            {
                if(flag==0)
                    notesCount++;
                else
                    fprintf(fp,"%d-%d-%d\n%d:%d\n%s\n",hourRoot->note[count]->day,hourRoot->note[count]->month,hourRoot->note[count]->year,
                            hourRoot->note[count]->hour,hourRoot->note[count]->minute,hourRoot->note[count]->comment);

            }
            count--;
            dayReminder(hourRoot->right,fp,flag);
        }
    }
    else
        return 1;
    return 0;
}

int monthReminder(dayNode* dayRoot,int day,FILE* fp,int flag)
{
    if(dayRoot!=NULL)
    {
        if(day==0)
        {
            monthReminder(dayRoot->left,day,fp,flag);
            printf("                  | DAY %d\n",dayRoot->day);
            dayReminder(dayRoot->hourRoot,fp,flag);
            monthReminder(dayRoot->right,day,fp,flag);
        }
        else
        {
            dayNode* day_node = searchDayNode(dayRoot,day);
            if(day_node==NULL)
                return 1;
            printf("                  | DAY %d\n",day_node->day);
            return dayReminder(day_node->hourRoot,fp,flag);
        }
    }
    return 0;
}

int yearReminder(monthNode* monthRoot,int month,int day,FILE* fp,int flag)
{
    if(monthRoot!=NULL)
    {
        if(month==0)
        {
            yearReminder(monthRoot->left,month,day,fp,flag);
            printf("         | MONTH %d\n",monthRoot->month);
            monthReminder(monthRoot->dayRoot,day,fp,flag);
            yearReminder(monthRoot->right,month,day,fp,flag);
        }
        else
        {
            monthNode* month_node = searchMonthNode(monthRoot,month);
            if(month_node==NULL)
                return 1;
            printf("         | MONTH %d\n",month_node->month);
            return monthReminder(month_node->dayRoot,day,fp,flag);

        }


    }
    return 0;
}

int allReminder(yearNode* yearRoot,int year,int month,int day,FILE* fp,int flag)
{
    if(yearRoot!=NULL)
    {
        if(year==0)
        {
            allReminder(yearRoot->left,year,month,day,fp,flag);
            printf(" YEAR %d\n",yearRoot->year);
            yearReminder(yearRoot->monthRoot,month,day,fp,flag);
            allReminder(yearRoot->right,year,month,day,fp,flag);
        }

        else
        {
            yearNode* year_node = searchYearNode(yearRoot,year);
            if(year_node==NULL)
                return 1;
            printf(" YEAR %d\n",year_node->year);
            return yearReminder(year_node->monthRoot,month,day,fp,flag);
        }
    }
    return 0;
}

dayNode* minDayNode(dayNode* dayRoot)
{
    if(dayRoot->left==NULL)
        return dayRoot;
    else
        return minDayNode(dayRoot->left);
}

monthNode* minMonthNode(monthNode* monthRoot)
{
    if(monthRoot->left==NULL)
        return monthRoot;
    else
        return minMonthNode(monthRoot->left);
}

yearNode* minYearNode(yearNode* yearRoot)
{
    if(yearRoot->left==NULL)
        return yearRoot;
    else
        return minYearNode(yearRoot->left);
}

dayNode* delDay(dayNode* dayRoot,int day)
{
    if(dayRoot==NULL)
        return dayRoot;
    if(day<dayRoot->day)
        dayRoot->left = delDay(dayRoot->left,day);
    else if(day>dayRoot->day)
        dayRoot->right = delDay(dayRoot->right,day);
    else
    {

        if(dayRoot->left == NULL)
        {
            dayNode* temp = dayRoot->right;
            free(dayRoot);
            return temp;
        }
        else if(dayRoot->right == NULL)
        {
            dayNode* temp = dayRoot->left;
            free(dayRoot);
            return temp;
        }
        dayNode* temp = minDayNode(dayRoot->right);
        dayRoot->day = temp->day;
        dayRoot->hourRoot = temp->hourRoot;
        dayRoot->right = delDay(dayRoot->right,temp->day);
    }
    return dayRoot;
}



monthNode* delMonth(monthNode* monthRoot,int month)
{
    if(monthRoot==NULL)
        return monthRoot;
    if(month<monthRoot->month)
        monthRoot->left = delMonth(monthRoot->left,month);
    else if(month>monthRoot->month)
        monthRoot->right = delMonth(monthRoot->right,month);
    else
    {
        if(monthRoot->left == NULL)
        {
            monthNode* temp = monthRoot->right;
            free(monthRoot);
            return temp;
        }
        else if(monthRoot->right == NULL)
        {
            monthNode* temp = monthRoot->left;
            free(monthRoot);
            return temp;
        }
        monthNode* temp = minMonthNode(monthRoot->right);
        monthRoot->month = temp->month;
        monthRoot->dayRoot = temp->dayRoot;
        monthRoot->right = delMonth(monthRoot->right,temp->month);
    }
    return monthRoot;
}

yearNode* delYear(yearNode* yearRoot,int year)
{
    if(yearRoot==NULL)
        return yearRoot;
    if(year<yearRoot->year)
        yearRoot->left = delYear(yearRoot->left,year);
    else if(year>yearRoot->year)
        yearRoot->right = delYear(yearRoot->right,year);
    else
    {
        if(yearRoot->left == NULL)
        {
            yearNode* temp = yearRoot->right;
            free(yearRoot);
            return temp;
        }
        else if(yearRoot->right == NULL)
        {
            yearNode* temp = yearRoot->left;
            free(yearRoot);
            return temp;
        }
        yearNode* temp = minYearNode(yearRoot->right);
        yearRoot->year = temp->year;
        yearRoot->monthRoot = temp->monthRoot;
        yearRoot->right = delYear(yearRoot->right,temp->year);
    }
    return yearRoot;
}



yearNode* delDateReminder(yearNode* yearRoot,int year,int month,int day)
{
    int flag=0;
    yearNode* year_node = searchYearNode(yearRoot,year);
    if(year_node != NULL)
    {
        if(month!=0)
        {
            monthNode* month_node = searchMonthNode(year_node->monthRoot,month);
            if(month_node!=NULL)
            {
                if(day!=0)
                {
                    dayNode* day_node = searchDayNode(month_node->dayRoot,day);
                    if(day_node!=NULL)
                        month_node->dayRoot = delDay(month_node->dayRoot,day);
                    else
                        flag=1;
                }
                else
                {
                    year_node->monthRoot = delMonth(year_node->monthRoot,month);
                }
            }
            else
                flag=1;
        }
        else
        {
            yearRoot = delYear(yearRoot,year);
        }
    }
    else
        flag=1;
    if(flag==0)
    {
        if(year!=0 && month!=0 && day!=0)
            printf("Reminders of date[DD-MM-YYYY] %02d-%02d-%d is deleted.....!",day,month,year);
        else if(year!=0 && month!=0)
            printf("Reminders of month[MM-YYYY] %02d-%d is deleted.....!",month,year);
        else if (year!=0)
            printf("Reminders of year %d is deleted.....!",year);
    }
    else
    {
        if(year!=0 && month!=0 && day!=0)
            printf("No Reminders to delete on date[DD-MM-YYYY] %02d-%02d-%d .....!",day,month,year);
        else if(year!=0 && month!=0)
            printf("NO Reminders to delete in month[MM-YYYY] %02d-%d ......!",month,year);
        else if (year!=0)
            printf("No Reminders to delete in year %d .....!",year);
    }
    printf("\n\n");

    return yearRoot;
}

yearNode* pastYear(yearNode* yearRoot2,yearNode* yearRoot,int year)
{

    if(yearRoot2!=NULL)
    {
        pastYear(yearRoot2->left,yearRoot,year);
        if(yearRoot2->year<year)
            yearRoot = delDateReminder(yearRoot,yearRoot2->year,0,0);
        pastYear(yearRoot2->right,yearRoot,year);
    }

    return yearRoot;

}

yearNode* pastMonth(monthNode* monthRoot2,yearNode* yearRoot,int year,int month)
{
    if(monthRoot2!=NULL)
    {
        pastMonth(monthRoot2->left,yearRoot,year,month);
        if(monthRoot2->month<month)
            yearRoot = delDateReminder(yearRoot,year,monthRoot2->month,0);
        pastMonth(monthRoot2->right,yearRoot,year,month);
    }
    return yearRoot;
}

yearNode* pastDay(dayNode* dayRoot,yearNode* yearRoot,int year,int month,int day)
{
    if(dayRoot!=NULL)
    {
        pastDay(dayRoot->left,yearRoot,year,month,day);
        if(dayRoot->day<day)
            yearRoot = delDateReminder(yearRoot,year,month,dayRoot->day);
        pastDay(dayRoot->right,yearRoot,year,month,day);
    }
    return yearRoot;
}

yearNode* delPastReminder(yearNode* yearRoot,int year,int month,int day)
{
    yearRoot = pastYear(yearRoot,yearRoot,year);
    yearNode* year_node = searchYearNode(yearRoot,year);
    if(year_node==NULL)
        return yearRoot;
    yearRoot = pastMonth(year_node->monthRoot,yearRoot,year,month);
    monthNode* month_node = searchMonthNode(year_node->monthRoot,month);
    if(month_node==NULL)
        return yearRoot;
    yearRoot = pastDay(month_node->dayRoot,yearRoot,year,month,day);
    return yearRoot;

}


void LogReminders(yearNode* yearRoot)
{
    FILE* fp;
    system("del Reminders.txt");
    fp = fopen("Reminders.txt","a");
    allReminder(yearRoot,0,0,0,fp,0);
    fprintf(fp,"%d\n",notesCount);
    allReminder(yearRoot,0,0,0,fp,1);
    fclose(fp);

}
yearNode* readLog(yearNode* yearRoot)
{
    FILE* fp;
    fp = fopen("Reminders.txt","r");
    if(fp!=NULL)
        yearRoot = setReminder(yearRoot,fp);
    fclose(fp);
    return yearRoot;
}

int main()
{
    yearNode* yearRoot = NULL;

    yearRoot = readLog(yearRoot);
    int dayFlag;
    int sp_day,sp_year,sp_month;
    int flag=0;
    int validFlag=0;
    int option;
    time_t rawtime;
    struct tm * timeinfo;
    time(&rawtime);
    timeinfo = localtime( &rawtime );
    int day=timeinfo->tm_mday;
    int month = timeinfo->tm_mon+1;
    int year = timeinfo->tm_year+1900;
    int hour = timeinfo->tm_hour;
    int min = timeinfo->tm_min;
    int sec = timeinfo->tm_sec;
    char* time = asctime(timeinfo);
    system("color 0c");

    printf("                                 NOTE TOOLS                                     \n");
    printf("\n\t\t\t            TODAY");
    printf("\n\t\t\t       TIME = %02d:%02d:%02d \n",hour,min,sec);
    printf("\t\t\t      DATE = %02d-%02d-%d \n",day,month,year);
    printf("\n--------------------------------------------------------------------------------\n");
    printf("                               TODAY REMINDERS \n");
    printf("\n\n");
    if(yearRoot!=NULL)
    {
        dayFlag=allReminder(yearRoot,year,month,day,NULL,0);
        if(dayFlag==1)
            printf("\nNo Reminder today...!\n\n");
    }
    else
        printf("\t                 No reminders is set yet ..!\n\n");
    printf("--------------------------------------------------------------------------------\n\n\n\n");
    system("echo press enter key to go back to main menu...");
    system("pause >nul");

    while(1)
    {


        timeinfo = localtime( &rawtime );
        day=timeinfo->tm_mday;
        month = timeinfo->tm_mon+1;
        year = timeinfo->tm_year+1900;
        hour = timeinfo->tm_hour;
        min = timeinfo->tm_min;
        sec = timeinfo->tm_sec;
        time = asctime(timeinfo);
        system("color 0c");
        printf("------------------------   MENU   ------------------------\n\n");
        printf("                   1. Set a Reminder\n\n");
        printf("                    2. All Reminders\n\n");
        printf("                   3. Today Reminders\n\n");
        printf("                4. This Month Reminders\n\n");
        printf("                 5. This Year Reminders\n\n");
        printf("          6. Search for Specific Date Reminders\n\n");
        printf("           7. Delete Reminders of specific Date\n\n");
        printf("          8. Delete Reminders of specific Month\n\n");
        printf("           9. Delete Reminders of specific Year\n\n");
        printf("               10. Delete past Reminders\n\n");
        printf("                11. Delete All Reminders\n\n");
        printf("                       12. Exit\n\n");
        printf("--------------------------------------------------------------------------------\n\n");
        printf(" Enter your choice: ");
        scanf("%d",&option);
        switch(option)
        {
            case 1:
                yearRoot = setReminder(yearRoot,NULL);
                break;
            case 2:

                printf("\n--------------------------------------------------------------------------------\n");
                printf("                                 ALL REMINDERS \n");
                printf("\n\n");
                if(yearRoot!=NULL)
                {
                    allReminder(yearRoot,0,0,0,NULL,0);
                    printf("\n\n");
                }
                else
                    printf("\t No reminders set yet ..!\n\n");
                printf("--------------------------------------------------------------------------------\n\n\n\n\n");
                system("echo press enter key to go back to main menu...");
                system("pause >nul");
                break;
            case 3:

                printf("\n--------------------------------------------------------------------------------\n");
                printf("                          TODAY REMINDERS \n");
                printf("\n\n");
                if(yearRoot!=NULL)
                {
                    dayFlag=allReminder(yearRoot,year,month,day,NULL,0);
                    if(dayFlag==1)
                        printf("No Reminder today...!\n\n");
                }
                else
                    printf("\t No reminders set yet ..!\n\n");
                printf("--------------------------------------------------------------------------------\n\n\n\n");
                system("echo press enter key to go back to main menu...");
                system("pause >nul");
                break;
            case 4:

                printf("\n--------------------------------------------------------------------------------\n");
                printf("                          MONTH REMINDERS \n");
                printf("\n\n");
                if(yearRoot!=NULL)
                {
                    dayFlag=allReminder(yearRoot,year,month,0,NULL,0);
                    if(dayFlag==1)
                        printf("No Reminder this month...!\n\n");
                }
                else
                    printf("\t No reminders set yet ..!\n\n");
                printf("--------------------------------------------------------------------------------\n\n\n\n");
                system("echo press enter key to go back to main menu...");
                system("pause >nul");
                break;
            case 5:

                printf("\n--------------------------------------------------------------------------------\n");
                printf("                          YEAR REMINDERS \n");
                printf("\n\n");
                if(yearRoot!=NULL)
                {
                    dayFlag=allReminder(yearRoot,year,0,0,NULL,0);
                    if(dayFlag==1)
                        printf("No Reminder this year...!\n\n");
                }
                else
                    printf("\t No reminders set yet ..!\n\n");
                printf("--------------------------------------------------------------------------------\n\n\n\n");
                system("echo press enter key to go back to main menu...");
                system("pause >nul");
                break;
            case 6:
                do
                {

                    system("color 0b");
                    printf("\n--------------------------------------------------------------------------------\n");
                    printf("                    SPECIFIC DATE REMINDERS \n");
                    printf("\n\n");
                    printf("Enter Date to search for Reminders [DD-MM-YYYY]:");
                    scanf("%d-%d-%d",&sp_day,&sp_month,&sp_year);
                    validFlag = validation(sp_year,sp_month,sp_day,1,1);
                }while(validFlag!=0);
                system("color 0b");

                printf("\n--------------------------------------------------------------------------------\n");
                printf("                    SPECIFIC DATE REMINDERS \n");
                printf("\n\n");
                if(yearRoot!=NULL)
                {
                    dayFlag=allReminder(yearRoot,sp_year,sp_month,sp_day,NULL,0);
                    if(dayFlag==1)
                        printf("No Reminder this year...!\n\n");
                }
                else
                    printf("\t No reminders set yet ..!\n\n");
                printf("--------------------------------------------------------------------------------\n\n\n\n");
                system("echo press enter key to go back to main menu...");
                system("pause >nul");
                break;
            case 7:
                do
                {
                    system("color 0b");

                    printf("\n--------------------------------------------------------------------------------\n");
                    printf("                   DELETE SPECIFIC DATE REMINDERS \n");
                    printf("\n\n");
                    printf("Enter Date to Delete Reminders [DD-MM-YYYY]:");
                    scanf("%d-%d-%d",&sp_day,&sp_month,&sp_year);
                    validFlag = validation(sp_year,sp_month,sp_day,1,1);

                }while(validFlag!=0);
                system("color 0b");

                printf("\n--------------------------------------------------------------------------------\n");
                printf("                   DELETE SPECIFIC DATE REMINDERS \n");
                printf("\n\n");
                if(yearRoot!=NULL)
                {
                    yearRoot = delDateReminder(yearRoot,sp_year,sp_month,sp_day);

                }
                else
                    printf("\tCan't delete any while there is no reminders set yet ..!\n\n");
                printf("--------------------------------------------------------------------------------\n\n\n\n");
                system("echo press enter key to go back to main menu...");
                system("pause >nul");
                break;
            case 8:
                do
                {

                    printf("\n--------------------------------------------------------------------------------\n");
                    printf("                   DELETE SPECIFIC MONTH REMINDERS \n");
                    printf("\n\n");
                    printf("Enter Month and Date to Delete Reminders [MM-YYYY]:");
                    scanf("%d-%d",&sp_month,&sp_year);
                    validFlag=validation(sp_year,sp_month,1,1,1);
                    system("color 0b");
                }while(validFlag!=0);
                system("cls");
                printf("\n--------------------------------------------------------------------------------\n");
                printf("                   DELETE SPECIFIC MONTH REMINDERS \n");
                printf("\n\n");
                if(yearRoot!=NULL)
                {
                    yearRoot = delDateReminder(yearRoot,sp_year,sp_month,0);
                }
                else
                    printf("\tCan't delete any as No reminders is setted yet ..!\n\n");
                printf("--------------------------------------------------------------------------------\n\n\n\n");
                system("echo press enter key to go back to main menu...");
                system("pause >nul");
                break;
            case 9:
                do
                {

                    printf("\n--------------------------------------------------------------------------------\n");
                    printf("                        DELETE SPECIFIC YEAR REMINDERS \n");
                    printf("\n\n");
                    printf("Enter Year to Delete Reminders [YYYY]:");
                    scanf("%d",&sp_year);
                    validFlag = validation(sp_year,1,1,1,1);
                    system("color 0b");
                }while(validFlag!=0);

                printf("\n--------------------------------------------------------------------------------\n");
                printf("                        DELETE SPECIFIC YEAR REMINDERS \n");
                printf("\n\n");
                if(yearRoot!=NULL)
                {
                    yearRoot = delDateReminder(yearRoot,sp_year,0,0);
                }
                else
                    printf("\tCan't delete any as No reminders is set yet ..!\n\n");
                printf("--------------------------------------------------------------------------------\n\n\n\n");
                system("echo press enter key to go back to main menu...");
                system("pause >nul");
                break;
            case 10:

                printf("\n--------------------------------------------------------------------------------\n");
                printf("                           DELETE PAST REMINDERS \n");
                printf("\n\n");
                if(yearRoot!=NULL)
                {
                    yearRoot = delPastReminder(yearRoot,year,month,day);
                }
                else
                    printf("\tCan't delete any as No reminders is set yet ..!\n\n");
                printf("--------------------------------------------------------------------------------\n\n\n\n");
                system("echo press enter key to go back to main menu...");
                system("pause >nul");
                break;
            case 11:

                printf("\n--------------------------------------------------------------------------------\n");
                printf("                           DELETE ALL REMINDERS \n");
                printf("\n\n");
                if(yearRoot!=NULL)
                {
                    yearRoot = NULL;
                    printf("\tAll Reminders are Deleted...!\n\n");
                }
                else
                    printf("\tCan't delete any as No reminders is set yet ..!\n\n");
                printf("--------------------------------------------------------------------------------\n\n\n\n");
                system("echo press enter key to go back to main menu...");
                system("pause >nul");
                break;

            case 12:
                flag=1;
                notesCount=0;
                system("color 08");
                LogReminders(yearRoot);
                system("cls");
                break;
            default:

                system("cls");

                system("color 0c");
                printf("\n\n\n\tEntered number should be in range of 1-10 only....\n\n\n\n\n");
                system("echo press enter key to go back to main menu...");
                system("pause >nul");
        }
        if(flag==1)
        {
            system("cls");
            printf("\n\t\t\t\t\t\t %s",time);
            break;
        }

    }

    printf("\n\n\n\n\n\tThanks for using the \"NOTE TOOL\"...............!\n\n");

    printf("\n\n\n\n\n\n\n\n\tPress enter key to Exit NOTE TOOL.....\n");


    return 0;
}
