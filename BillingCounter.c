#include <stdio.h>
#include <string.h>
#include <stdlib.h>
void bills();
void add();
void edit();
void ddelete();
void display();
void menu();
void retmenu();
struct data
{
    int code;
    char name[50];
    int rate;
} s;

void main()
{
    menu();
}

void menu()
{
    char options;
    system("clear");
    printf("\n\n\t\t\t\t\t\t\t\tPESU MART\n\n\n");
    printf("MAIN MENU:\n1.Calculate Bills\n2.Add Items to Inventory\n3.Edit Items in Inventory\n4.Delete Items in Inventory\n5.Display all items in the Inventory\n6.Exit\n\n");
    printf("Choose An Option:");
    scanf(" %c", &options);
    switch (options)
    {
    case '1':
        bills();
        break;
    case '2':
        add();
        break;
    case '3':
        edit();
        break;
    case '4':
        ddelete();
        break;
    case '5':
        system("clear");
        display();
        retmenu();
        break;
    case '6':
        printf("\n\n\t\t Thank You!!\n");
        exit(1);
        break;
    default:
        printf("\n\nINVALID OPTION!");
        menu();
    }
}

void bills()
{
    struct data s;
    FILE *fp, *fp1;
    int code[100], qty[100], rate[100], amount[100], i, ni, j, input, v, cnt;
    float total = 0.0, sgst = 0.0;
    char cname[100];
    system("clear");
    fp = fopen("items.txt", "r");
    fp1 = fopen("bill.txt", "w");
    if (fp == NULL)
    {
        printf("cannot open file");
        exit(1);
    }
    if (fp1 == NULL)
    {
        printf("cannot open file");
        exit(1);
    }
    printf("___Calculate Bills___\n");
    printf("Enter Customer's Name:");
    scanf("%s", &cname);
    printf("\nEnter Number of Items:");
    scanf("%d", &ni);
    system("clear");
    display();
    printf("\n\n\n");
    for (i = 0; i < ni; i++)
    {
        printf("\n\nEnter Code:");
        scanf("%d", &cnt);
        code[i] = cnt;
        printf("\nEnter Quantity:");
        scanf("%d", &cnt);
        qty[i] = cnt;
    }
    system("clear");
    printf("\t\t\tCUSTOMER'S BILL");
    printf("\n\n\tNAME: %s", cname);
    printf("\n\n\nS.N\tPARTICULARS\tQUANTITY\tRATE\t  AMOUNT ");
    fprintf(fp1, "\n\t\t\tCUSTOMER'S BILL\n\n\t Name: %s\n\nS.N\tPARTICULARS\t\tQUANTITY\t RATE \t AMOUNT \n\n", cname);
    for (i = 0; i < ni; i++)
    {
        cnt = 0;
        float gst;
        while (!feof(fp))
        {
            fscanf(fp, " %d\t%s\t%d\n", &s.code, s.name, &s.rate);
            if (s.code == code[i])
            {
                if (code[i] / 2 == 0)
                    gst = 0.18;
                else
                    gst = 0.07;
                amount[i] = s.rate * qty[i];
                printf("\n %2d\t %-10.10s\t%7d \t%4d\t%7d\n", i + 1, s.name, qty[i], s.rate, amount[i]);
                fprintf(fp1, "\n %2d\t  %-11s\t\t\t%8d\t\t%6d\t%8d\n", i + 1, s.name, qty[i], s.rate, amount[i]);
                total = total + amount[i] + (gst * amount[i]);
                sgst += (gst * amount[i]);
                cnt = 1;
            }
        }
        if (cnt != 1)
        {
            printf("\nItem not found\n");
        }
        rewind(fp);
    }
    if (total < 200.0)
    {
        printf("\n\tMinimum Billing amount is 200");
        printf("\n\tPlease add items worth Rs%.2f more",(200.0-total));
        // printf("\n\tPlease Add some more Items ");
        printf("\n\tWe have Plenty of items in our store you can always check out some more :)");
    }
    else
    {
        printf("\n\n\t\t\t\t\t GST=Rs. %.2f ", sgst);
        fprintf(fp1, "\n\n\t\t\t\t\t GST=Rs. %.2f ", sgst);
        printf("\n\n\t\t\t\t\t Total=Rs. %.2f (Including GST)", total);
        fprintf(fp1, "\n\n\t\t\t\t\t Total=Rs. %.2f (Including GST)", total);
    }

    fclose(fp);
    fclose(fp1);
    retmenu();
}

void edit()
{
    FILE *fp1, *fp2;
    int cod;
    system("clear");
    fp1 = fopen("items.txt", "r");
    fp2 = fopen("temp.txt", "w");
    if (fp1 == NULL)
    {
        printf("Cannot Open File");
        exit(1);
    }
    if (fp2 == NULL)
    {
        printf("Cannot Open File");
        exit(1);
    }
    printf("Records Before Alteration\n");
    display();
    rewind(fp1);

    printf("Enter Code to Edit:");
    scanf("%d", &cod);
    while (!feof(fp1))
    {

        fscanf(fp1, "%d\t%s\t%d\n", &s.code, s.name, &s.rate);
        if (s.code == cod)
        {
            printf("Enter New Name:");
            scanf("%s", s.name);
            printf("Enter New Rate:");
            scanf("%d", &s.rate);
            fprintf(fp2, "%d\t%s\t%d\n", s.code, s.name, s.rate);
        }
        else
        {
            fprintf(fp2, "%d\t%s\t%d\n", s.code, s.name, s.rate);
        }
    }
    fclose(fp1);
    fclose(fp2);

    remove("items.txt");
    rename("temp.txt", "items.txt");
    system("clear");
    printf("Records After Alteration\n");
    display();
    rewind(fp1);
    retmenu();
}

void display()
{
    int i = 0;
    struct data s;
    FILE *fp;
    fp = fopen("items.txt", "r");
    if (fp == NULL)
    {
        printf("Cannot open file");
        exit(1);
    }
    printf("\nCode\tPARTICULARS\tRATE");
    while (!feof(fp))
    {

        fscanf(fp, "%d\t%s\t%d\n", &s.code, s.name, &s.rate);
        printf("\n %2d\t %-11.10s\t%4d\n", s.code, s.name, s.rate);
    }
    fclose(fp);
}

void ddelete()
{
    FILE *fp1, *fp2;
    int delno;
    system("clear");
    fp1 = fopen("items.txt", "r");
    fp2 = fopen("temp.txt", "w");
    if (fp1 == NULL)
    {
        printf("Cannot open file");
        exit(1);
    }
    if (fp2 == NULL)
    {
        printf("Cannot open file");
        exit(1);
    }
    printf("Records Before Alteration\n");
    display();
    rewind(fp1);
    printf("Enter Code to Delete:");
    scanf("%d", &delno);
    while (!feof(fp1))
    {
        fscanf(fp1, "%d\t%s\t%d\n", &s.code, s.name, &s.rate);
        if (s.code == delno)
        {
            continue;
        }
        else
        {
            fprintf(fp2, "%d\t%s\t%d\n", s.code, s.name, s.rate);
        }
    }
    fclose(fp1);
    fclose(fp2);

    remove("items.txt");
    rename("temp.txt", "items.txt");
    system("clear");
    printf("Records After Alteration\n");
    display();
    rewind(fp1);
    retmenu();
}

void add()
{
    char opt = 'y';
    FILE *fp;
    system("clear");
    fp = fopen("items.txt", "a");
    if (fp == NULL)
    {
        printf("cannot open file");
        exit(1);
    }

    while (opt == 'y' || opt == 'Y')
    {
        printf("Enter Code:");
        scanf(" %d", &s.code);
        printf("Enter Name:");
        scanf(" %s", s.name);
        printf("Enter Rate:");
        scanf(" %d", &s.rate);
        fprintf(fp, "%d\t%s\t%d\n", s.code, s.name, s.rate);
        printf("\n\n Record Added Successfully.");
        printf("\nAdd More Items[Y/N]?");
        scanf("%c", &opt);
        scanf("%c", &opt);
    }
    fclose(fp);
    retmenu();
}

void retmenu()
{
    char mm;
    printf("\n\n\nReturn to Main Menu?[Y/N]");
    scanf(" %c", &mm);
    if (mm == 'y' || mm == 'Y')
    {
        system("clear");
        menu();
    }
    else if (mm == 'N' || mm == 'n')
        exit(1);
    else
        retmenu();
}
