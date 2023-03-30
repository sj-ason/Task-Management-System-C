#include "headerfiles.h"

struct record
{
    char time[6];
    char name[30];
    char category[25];
    char place[25];
    char duedate[25];
    char status[25];
    char note[500];
};

int password()
{
    char pass[15] = {0}, check[15] = {0}, ch;
    FILE *fpp;
    int i = 0, j;
    printf("\n\t\tFOR SECURITY PURPOSE");
    printf("\n\t\tONLY THREE TRIALS ARE ALLOWED");
    for(j = 0; j < 3; j++)
    {
        i = 0;
        printf("\n\n\tENTER THE PASSWORD: ");
        pass[0] = getch();
        while(pass[i] != '\r')
        {
            if(pass[i] == '\b')
            {
                i--;
                printf("\b");
                printf(" ");
                printf("\b");
                pass[i] = getch();
            }
            else
            {
                printf("*");
                i++;
                pass[i] = getch();
            }
        }
        pass[i] = '\0';
        fpp = fopen("SE", "r");
        if(fpp == NULL)
        {
            printf("\nERROR WITH THE SYSTEM FILE [FILE MISSING]\n");
            getch();
            return 1;
        }
        else
            i = 0;
        while(1)
        {
            ch = fgetc(fpp);
            if(ch == EOF)
            {
                check[i] = '\0';
                break;
            }
            check[i] = ch-5;
            i++;
        }
        if(strcmp(pass, check) == 0)
        {
            printf("\n\n\t ACCESS GRANTED\n");
            return 0;
        }
        else
        {
            printf("\n\n\tWRONG PASSWORD\n\n\tACCESS DENIED\n");
        }
    }
    printf("\n\n\tYOU ENTERED WRONG PASSWORD, YOU ARE NOT ALLOWED TO ACCESS ANY FILE\n\n\tPRESS ANY KEY TO GO BACK");
    getch();
    return 1;
}

void editpassword()
{
    system("cls");
    printf("\n");
    char pass[15]= {0},confirm[15]= {0},ch;
    int choice,i,check;
    FILE *fp;
    fp=fopen("SE","rb");
    if(fp==NULL)
    {
        fp=fopen("SE","wb");
        if(fp==NULL)
        {
            printf("SYSTEM ERROR...");
            getch();
            return ;
        }
        fclose(fp);
        printf("\nSYSTEM RESTORED...\nYOUR PASSWORD IS 'ENTER'\n PRESS ENTER TO CHANGE PASSWORD\n\n");
        getch();
    }
    fclose(fp);
    check=password();
    if(check==1)
    {
        return ;
    }
    do
    {
        if(check==0)
        {
            i=0;
            choice=0;
            printf("\n\n\tENTER THE NEW PASSWORD:");
            fflush(stdin);
            pass[0]=getch();
            while(pass[i]!='\r')
            {
                if(pass[i]=='\b')
                {
                    i--;
                    printf("\b");
                    printf(" ");
                    printf("\b");
                    pass[i]=getch();
                }
                else
                {
                    printf("*");
                    i++;
                    pass[i]=getch();
                }
            }
            pass[i]='\0';
            i=0;
            printf("\n\tCONFIRM PASSWORD:");
            confirm[0]=getch();
            while(confirm[i]!='\r')
            {
                if(confirm[i]=='\b')
                {
                    i--;
                    printf("\b");
                    printf(" ");
                    printf("\b");
                    confirm[i]=getch();
                }
                else
                {
                    printf("*");
                    i++;
                    confirm[i]=getch();
                }
            }
            confirm[i]='\0';
            if(strcmp(pass,confirm)==0)
            {
                fp=fopen("SE","wb");
                if(fp==NULL)
                {
                    printf("\n\t\tSYSTEM ERROR");
                    getch();
                    return ;
                }
                i=0;
                while(pass[i]!='\0')
                {
                    ch=pass[i];
                    putc(ch+5,fp);
                    i++;
                }
                putc(EOF,fp);
                fclose(fp);
            }
            else
            {
                printf("\n\tTHE NEW PASSWORD DOES NOT MATCH.");
                choice=1;
            }
        }
    }
    while(choice==1);
    printf("\n\n\tPASSWORD CHANGED...\n\n\tPRESS ANY KEY TO GO BACK...");
    getch();
}
void addtask()
{
    system("cls");
    FILE *fp, *fpr;
    char another = 'Y', time[10], filename[15], str[255];
    struct record e;
    int choice, ch = 1, c;
    printf("\n\n\t\t******************************\n");
    printf("\t\t*WELCOME TO THE ADD TASK MENU*");
    printf("\n\t\t******************************\n\n");
    printf("\n\tCANCEL   [1]");
    printf("\n\tCONTINUE [2]");
    printf("\n\tENTER YOUR CHOICE: ");
    scanf("%d", &ch);
    switch (ch)
    {
        case 1:
            return;
        case 2:
            break;
        default:
            break;
    }
    printf("\n\n\tENTER DATE OF YOUR RECORD [yyyy-mm-dd]: ");
    fflush(stdin);
    gets(filename);
    fp = fopen (filename, "ab+");
    if(fp == NULL)
    {
        fp = fopen(filename, "wb+");
        if(fp == NULL)
        {
            printf("\nSYSTEM ERROR");
            printf("\nPRESS ANY KEY TO EXIT");
            getch();
            return;
        }
    }
    while ( another == 'Y'|| another=='y' )
    {
        choice=0;
        fflush(stdin);
        printf ( "\n\tENTER TIME [hh:mm]: ");
        scanf("%s",time);
        
        rewind(fp);
        while(fread(&e,sizeof(e),1,fp)==1)
        {
            if(strcmp(e.time,time)==0)
            {
                printf("\n\tTHE RECORD ALREADY EXISTS.\n");
                choice=1;
            }
        }
        if(choice == 0)
        {
            strcpy(e.time, time);
            printf("\tENTER TASK NAME: ");
            fflush(stdin);
            gets(e.name);
            fflush(stdin);
            printf("\tENTER TASK CATEGORY: ");
            fflush(stdin);
            gets(e.category);
            fflush(stdin);
            printf("\tENTER TASK PLACE: ");
            gets(e.place);
            fflush(stdin);
            printf("\tENTER DUE DATE: ");
            gets(e.duedate);
            fflush(stdin);
            printf("\tENTER TASK STATUS: ");
            gets(e.status);
            fflush(stdin);
            printf("\tEXTRA NOTE: ");
            gets(e.note);
            fwrite(&e, sizeof(e), 1, fp) ;
            printf("\n\tYOUR RECORD IS ADDED\n\n");
            fpr = fopen("recordtaskname.txt", "a");
            if(fpr == NULL)
            {
                printf("Error! filename can't be recorded\n");
                getch();
                return;
            }
            fflush(stdin);
            printf("\tFORMAT: 15CHARACTERS, YYYY-MM-DD 5SPACES HH:MM\n");
            printf("\tENTER THE TASK NAME AND THE FULL DATE AGAIN: ");
            fgets(str, 255, stdin);
            fprintf(fpr, "%s", str);
            fclose(fpr);

            printf("\n\tFILE CREATED AND SAVED SUCCESSFULLY.\n");    
        }
        printf("\n\tADD ANOTHER RECORD [Y/N]: ");
        fflush(stdin);
        another = getchar();
    }
    fclose(fp);
    printf("\n\n\tPRESS ANY KEY TO EXIT");
    getch();
}

void viewtask()
{
    FILE *fpte;
    system("cls");
    struct record user;
    char time[6], choice, filename[14], recordtaskname[15];
    int ch;
    printf("\n\n\t\t**************************\n");
    printf("\t\t*HERE IS THE VIEWING MENU*");
    printf("\n\t\t**************************\n\n");
    choice = password();
    if (choice !=0)
    {
        return;
    }
    do
    {
        printf("\n\tCANCEL   [1]");
        printf("\n\tCONTINUE [2]");
        printf("\n\tENTER YOUR CHOICE: ");
        scanf("%d", &ch);
        switch (ch)
        {
            case 1:
                return;
            case 2:
                break;
            default:
                break;
        }
        int c;
        printf("\n");
        FILE *fpts = fopen("recordtaskname.txt", "r");
        if(fpts)
        {
            while((c = getc(fpts)) != EOF)
                putchar(c);
            fclose(fpts);
        }
        printf("\n\tFILE OPENED SUCCESSFULLY. READING FILE CONTENTS LINE BY LINE.\n");
        getch();
        printf("\n\tENTER THE DATE OF RECORD TO BE VIEWED [yyyy-mm-dd]: ");
        fflush(stdin);
        gets(filename);
        fpte = fopen(filename, "rb");
        if (fpte == NULL)
        {
            puts("\nTHE TASK DOES NOT EXIST IN THE RECORD\n");
            printf("PRESS ANY KEY TO EXIT");
            getch();
            return;
        }
        system("cls");
        printf("\n\tHOW WOULD YOU LIKE TO VIEW THE TASK: ");
        printf("\n\t[1] WHOLE RECORD OF THE TASK");
        printf("\n\t[2] TASK FOR A FIXED TIME");
        printf("\n\tENTER YOUR CHOICE: ");
        scanf("%d", &ch);
        switch(ch)
        {
            case 1:
                printf("\nTHE WHOLE TASK FOR DATE %s IS: ", filename);
                while(fread(&user, sizeof(user), 1, fpte) == 1)
                {
                    printf("\n");
                    printf("\nTIME: %s", user.time);
                    printf("\nTASK NAME: %s", user.name);
                    printf("\nCATEGORY: %s", user.category);
                    printf("\nMEETING AT: %s", user.place);
                    printf("\nDUE DATE: %s", user.duedate);
                    printf("\nSTATUS: %s", user.status);
                    printf("\nEXTRA NOTE: %s", user.note);
                    printf("\n");
                }
                break;
            case 2:
                fflush(stdin);
                printf("\nENTER TIME [hh:mm]: ");
                gets(time);
                while(fread(&user, sizeof(user), 1, fpte) == 1)
                {
                    if(strcmp(user.time, time) == 0)
                    {
                        printf("\nYOUR RECORD IS: ");
                        printf("\nTIME: %s", user.time);
                        printf("\nTASK NAME: %s", user.name);
                        printf("\nCATEGORY: %s", user.category);
                        printf("\nMEETING AT: %s", user.place);
                        printf("\nDUE DATE: %s", user.duedate);
                        printf("\nSTATUS: %s", user.status);
                        printf("\nNOTE: %s", user.note);
                    }
                }
                break;
            default:
                printf("\nYOU TYPED SOMETHING ELSE");
                break;
        }
        printf("\n\nWOULD YOU LIKE TO CONTINUE VIEWING [Y/N]");
        fflush(stdin);
        scanf("%c", &choice);
    }
    while(choice == 'Y' || choice == 'y');
    fclose(fpte);
    return;
}

void updatetask()
{
    system("cls");
    FILE *fpte, *ftemp;
    struct record user;
    char time[6], choice, filename[14], buffer[MAX_LINE], newline[MAX_LINE];
    int num, count = 0, ch;
    printf("\n\n\t\t*****************************");
    printf("\n\t\t*WELCOME TO THE EDITING MENU*");
    printf("\n\t\t*****************************");
    choice = password();
    if(choice != 0)
    {
        return;
    }
    do
    {
        printf("\n\tCANCEL   [1]");
        printf("\n\tCONTINUE [2]");
        printf("\n\tENTER YOUR CHOICE: ");
        scanf("%d", &ch);
        switch (ch)
        {
            case 1:
                return;
            case 2:
                break;
            default:
                break;
        }
        int c, line, count;
        FILE *fptx = fopen("recordtaskname.txt", "r");
        if(fptx)
        {
            while((c = getc(fptx)) !=   EOF)
                putchar(c);
            fclose(fptx);
        }
        printf("\n");
        printf("\n\tFILE OEPENED SUCCESSFULLY. READING FILE CONTENTS LINE BY LINE.\n");
        getch();
        printf("ENTER THE LINE YOU WANT TO REPLACE [starting from 1]: ");
        scanf("%d", &line);
        fflush(stdin);
        printf("REPLACE '%d' line with: ", line);
        fgets(newline, MAX_LINE, stdin);
        fptx = fopen("recordtaskname.txt", "r");
        ftemp = fopen("replace.tmp", "w");
        if(fptx == NULL || ftemp == NULL)
        {
            printf("\nUNABLE TO OPEN FILE\n");
            printf("PLEASE CHECK WHETHER THE FILE EXISTS AND YOU HAVE READ/WRITE PRIVILEGE\n");
            return;
        }   
        count = 0;
        while((fgets(buffer, MAX_LINE, fptx)) != NULL)
        {
            count++;
            if(count == line)
                fputs(newline, ftemp);
            else
                fputs(buffer, ftemp);
        }
        fclose(fptx);
        fclose(ftemp);
        remove("recordtaskname.txt");
        rename("replace.tmp", "recordtaskname.txt");
        printf("\nSUCCESSFULLY REPLACED '%d' line with '%s'.", line, newline);
        printf("\n\tENTER THE DATE OF RECORD TO BE EDITED [yyyy-mm-dd]: ");
        fflush(stdin);
        gets(filename);
        printf("\n\tENTER TIME [hh:mm]: ");
        gets(time);
        fpte = fopen(filename, "rb+");
        if(fpte == NULL)
        {
            printf("\nRECORD DOES NOT EXISTS");
            printf("\nPRESS ANY KEY TO GO BACK");
            getch();
            return;
        }
        while(fread(&user, sizeof(user), 1, fpte) == 1)
        {
            if(strcmp(user.time, time) == 0)
            {
                printf("\nYOUR OLD RECORD WAS AS: ");
                printf("\nTIME: %s", user.time);
                printf("\nTASK NAME: %s", user.name);
                printf("\nCATEGORY: %s", user.category);
                printf("\nMEETING AT: %s", user.place);
                printf("\nDUE DATE: %s", user.duedate);
                printf("STATUS: %s", user.status);
                printf("\nEXTRA NOTE: %s", user.note);
                printf("\n\n\t\tWHAT WOULD YOU LIKE TO EDIT");
                printf("\n[1] TIME");
                printf("\n[2] TASK NAME");
                printf("\n[3] CATEGORY");
                printf("\n[4] TASK PLACE");
                printf("\n[5] DUE DATE");
                printf("\n[6] STATUS");
                printf("\n[7] NOTE");
                printf("\n[8] WHOLE RECORD");
                printf("\n[9] GO BACK TO MAIN MENU");
                do
                {
                    printf("\n\tENTER YOU CHOICE: ");
                    fflush(stdin);
                    scanf("%d", &num);
                    fflush(stdin);
                    switch (num)
                    {
                    case 1:
                        printf("\nENTER THE NEW DATA");
                        printf("\nNEW TIME [hh:mm]: ");
                        gets(user.time);
                        break;
                    case 2:
                        printf("\nENTER THE NEW DATA");
                        printf("\nNEW TASK NAME: ");
                        gets(user.name);
                        break;
                    case 3:
                        printf("ENTER THE NEW DATA");
                        printf("\nNEW TASK CATEGORY: ");
                        gets(user.category);
                        break;
                    case 4:
                        printf("\nENTER THE NEW DATA");
                        printf("\nNEW MEETING PLACE: ");
                        gets(user.place);
                        break;
                    case 5:
                        printf("\nENTER THE NEW DATA");
                        printf("\nNEW MEETING DUE DATE: ");
                        gets(user.duedate);
                        break;
                    case 6:
                        printf("\nENTER THE NEW DATA");
                        printf("\nNEW MEETING STATUS: ");
                        gets(user.status);
                        break;
                    case 7:
                        printf("\nENTER THE NEW DATA");
                        printf("\nEXTRA NOTE: ");
                        gets(user.note);
                        break;
                    case 8:
                        printf("\nENTER THE NEW DATA");
                        printf("\nNEW TIME [hh:mm]: ");
                        gets(user.time);
                        printf("\nNEW TASK NAME: ");
                        gets(user.name);
                        printf("\nNEW TASK CATEGORY: ");
                        gets(user.category);
                        printf("\nNEW MEETING PLACE: ");
                        gets(user.place);
                        printf("\nNEW MEETING DUE DATE: ");
                        gets(user.duedate);
                        printf("\nNEW TASK STATUS: ");
                        gets(user.status);
                        printf("\nEXTRA NOTE: ");
                        gets(user.note);
                        break;
                    case 9:
                        printf("\nPRESS ANY KEY TO GO BACK");
                        getch();
                        return;
                    default:
                        printf("\nYOU TYPED SOMETHING ELSE, TRY AGAIN");
                        break;
                    }
                }
                while(num < 1 || num > 8);
                fseek(fpte, -sizeof(user), SEEK_CUR);
                fwrite(&user, sizeof(user), 1, fpte);
                fseek(fpte, -sizeof(user), SEEK_CUR);
                fread(&user, sizeof(user), 1, fpte);
                choice = 5;
                break;
            }
        }
        if(choice == 5)
        {
            system("cls");
            printf("\n\t\tEDITING COMPLETED\n");
            printf("---\n");
            printf("THE NEW RECORD IS: \n");
            printf("---\n");
            printf("\nTIME: %s", user.time);
            printf("\nTASK NAME: %s", user.name);
            printf("\nTASK CATEGORY: %s", user.category);
            printf("\nMEETING AT: %s", user.place);
            printf("\nDUE DATE: %s", user.duedate);
            printf("\nNEW TASK STATUS: %s", user.status);
            printf("\nEXTRA NOTE: %s", user.note);
            fclose(fpte);
            printf("\n\n\tWOULD YOU LIKE TO EDIT ANOTHER RECORD [Y/N]");
            scanf("%c",&choice);
            count++;
        }
        else
        {
            printf("\nTHE RECORD DOES NOT EXIST\n");
            printf("\nWOULD YOU LIKE TO TRY AGAIN [Y/N]");
            scanf("%c", &choice);
        }
    }
    while(choice == 'Y' || choice == 'y');
    fclose(fpte);
    if(count == 1)
        printf("\n%d FILE IS EDITED\n", count);
    else if(count > 1)
        printf("\n%d FILES ARE EDITED\n", count);
    else
        printf("\nNO FILES EDITED\n");
    printf("\tPRESS ENTER TO EXIT EDITING MENU");
    getch();
}

void deletetask()
{
    system("cls");
    FILE *fp, *fptr, *fptz, *temp;
    struct record file;
    char filename[15], another = 'Y', time[10], temp_filename[FILENAME_SIZE], record_taskname[FILENAME_SIZE] = "recordtaskname.txt", buffer[MAX_LINE];
    int delete_line = 0, choice, check, c, ch, current_line = 1;
    bool keep_reading = true;
    printf("\n\n\t\t***********************\n");
    printf("\t\t*WELCOME TO DELETE MENU*");
    printf("\n\t\t***********************\n\n");
    check = password();
    if(check == 1)
    {
        return;
    }
    while(another == 'Y')
    {
        printf("\n\tCANCEL   [1]");
        printf("\n\tCONTINUE [2]");
        printf("\n\tENTER YOUR CHOICE: ");
        scanf("%d", &ch);
        switch (ch)
        {
            case 1:
                return;
            case 2:
                break;
            default:
                break;
        }
        printf("\n\n\tHOW WOULD YOU LIKE TO DELETE");
        printf("\n\n\tDELETE WHOLE RECORD\t\t\t[1]");
        printf("\n\tDELETE A PARTICULAR RECORD BY TIME\t[2]");
        do
        {
            printf("\n\tENTER YOUR CHOICE: ");
            scanf("%d", &choice);
            switch (choice)
            {
            case 1:
                fptz = fopen("recordtaskname.txt", "r");
                printf("\n\tYOUR WHOLE RECORD LIST\n");
                if(fptz)
                {
                    while((c = getc(fptz)) !=   EOF)
                        putchar(c);
                    fclose(fptz);
                }
                printf("\n\tENTER THE DATE OF RECORD TO BE DELETED [yyyy-mm-dd]: ");
                fflush(stdin);
                gets(filename);
                strcpy(temp_filename, "temp____");
                strcat(temp_filename, record_taskname);
                printf("Delete Line Number [starting from 1]: ");
                scanf("%d", &delete_line);
                fptz = fopen(record_taskname, "r");
                temp = fopen(temp_filename, "w");
                if(fptz == NULL || temp == NULL)
                {
                    printf("ERROR OPENING FILE(S)\n");
                    return;
                }
                do
                {
                    fgets(buffer, MAX_LINE, fptz);
                    if(feof(fptz)) keep_reading = false;
                    else if (current_line != delete_line)
                        fputs(buffer, temp);
                    current_line++;
                } while (keep_reading);
                fclose(fptz);
                fclose(temp);
                remove(record_taskname);
                rename(temp_filename, record_taskname);
                fp = fopen(filename, "wb");
                if(fp == NULL)
                {
                    printf("\nTHE FILE DOES NOT EXIST");
                    printf("\nPRESS ANY KEY TO GO BACK");
                    getch();
                    return;
                }    
                fclose(fp);
                remove(filename);
                printf("\nDELETED SUCCESSFULLY");
                break;
            case 2:
                fptz = fopen("recordtaskname.txt", "r");
                if(fptz)
                {
                    while((c = getc(fptz)) !=   EOF)
                        putchar(c);
                    fclose(fptz);
                }
                printf("\nENTER THE DATE OF RECORD [yyyy-mm-dd]: ");
                fflush(stdin);
                gets(filename);
                fp = fopen(filename, "rb");
                if(fp == NULL)
                {
                    printf("\nTHE FILE DOES NOT EXIST");
                    printf("\nPRESS ANY KEY TO GO BACK");
                    getch();
                    return;
                }
                fptr = fopen("temp", "wb");
                if(fptr == NULL)
                {
                    printf("\nSYSTEM ERROR");
                    printf("\nPRESS ANY KEY TO GO BACK");
                    getch();
                    return;
                }
                strcpy(temp_filename, "temp____");
                strcat(temp_filename, record_taskname);
                printf("Delete Line Number [starting from 1]: ");
                scanf("%d", &delete_line);
                fptz = fopen(record_taskname, "r");
                temp = fopen(temp_filename, "w");
                if(fptz == NULL || temp == NULL)
                {
                    printf("ERROR OPENING FILE(S)\n");
                    return;
                }
                do
                {
                    fgets(buffer, MAX_LINE, fptz);
                    if(feof(fptz)) keep_reading = false;
                    else if (current_line != delete_line)
                        fputs(buffer, temp);
                    current_line++;
                } while (keep_reading);
                fclose(fptz);
                fclose(temp);
                remove(record_taskname);
                rename(temp_filename, record_taskname);
                printf("\nENTER THE TIME OF RECORD TO BE DELETED [hh:mm]: ");
                fflush(stdin);
                gets(time);
                while(fread(&file, sizeof(file), 1, fp) == 1)
                {
                    if(strcmp(file.time, time) != 0)
                        fwrite(&file, sizeof(file), 1, fptr);
                }
                fclose(fp);
                fclose(fptr);
                remove(filename);
                rename("temp", filename);
                printf("\nDELETED SUCCESSFULLY");
                break;
            default:
                printf("\n\tYOU ENTERED WRONG CHOICE");
                break;
            }
        }
        while(choice < 1 || choice > 2);
        printf("\n\tDO YOU LIKE TO DELETE ANOTHER RECORD [Y/N]");
        fflush(stdin);
        scanf("%c", &another);
    }
    printf("\n\n\tPRESS ANY TO EXIT");
    getch();
}

void firsttime()
{
    printf("\n\n\tHello! Thank you for uisng this Personal Task Management System...");
    printf("\n\tAs it is you first time, please do open option number 5 which is edit password menu to enable the view and edit functions.");
    printf("\n\tBy the way, the default password is the enter key, not the word enter!!!");
    printf("\n\tThank you and have fun!!!\n");
    getch();
    return;
}

int main() 
{
    int ch;
    printf("\n\n\t*********************************************\n");
    printf("\t*PASSWORD PROTECTED PERSONAL TASK MANAGEMENT*\n");
    printf("\t*********************************************\n");
    while(1)
    {
        printf("\n\t[1] ADD NEW TASK\t");
        printf("\n\t[2] VIEW ALL TASK\t");
        printf("\n\t[3] UPDATE TASK\t");
        printf("\n\t[4] DELETE TASK\t");
        printf("\n\t[5] EDIT PASSWORD\t");
        printf("\n\t[6] EXIT PROGRAM\t\t");
        printf("\n\t[7] READ THIS IF THIS YOUR FIRST TIME USING THIS PROGRAM\t");
        printf("\n\n\tENTER OPTION: ");
        scanf("%d", &ch);
        switch(ch)
        {
            case 1:
                addtask();
                break;
            case 2:
                viewtask();
                break;
            case 3:
                updatetask();
                break;
            case 4:
                deletetask();
                break;
            case 5:
                editpassword();
                break;
            case 6:
                printf("\n\n\t\tTHANK YOU FOR USING THE APPLICATION");
                getch();
                exit(0);
            case 7:
                firsttime();
                break;
            default:
                printf("\nYOU ENTERED WRONG CHOICE");
                printf("\nPRESS ANY KEY TO TRY AGAIN");
                getch();
                break;
        }
        system("cls");
    }
    return 0;
}
