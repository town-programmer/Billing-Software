#include <stdio.h>
#include <string.h>
#include <ctype.h>
//#include <conio.h>

// To store the details of the items in the store
struct item
{
    int product_no;
    char product_name[10];
    int quantity;
    int price;
}
item;

// To store the customer details
struct customer
{
    int product_no;
    char product_name[10];
    int quantity;
    int price;
    int amount;
}
customer[100];

// To store and print tha values temporarily
struct temporary
{
    int product_no;
    char product_name[10];
    int quantity;
    int price;
    int amount;
}
temp[100];

// global variable to all function access
int t = 0;
int n = 0;  // to store quantity and records
int k = 0;
int ba = 0;
int ti = 0;

int create();
int bill();
int display();
int edit();
int invoice();
int mdelete();
int mdisplay();

// main function
int main()
{
    char ch, password[10], q[10] = "admin";
    int s = 0;
    int y = 0;
    int w = 1;

    FILE *file = fopen("Quantity.txt", "r");
    if (file == NULL)
    {
        printf("\nError code 1");
        return 1;
    }
    fscanf(file, "%d", &n);
    fclose(file);

    printf("\n");
	printf("************************************************************************************************************************");
	printf("\n");
	printf("*****************************************     WELCOME TO HARI DMART    *************************************************");
	printf("\n");
	printf("\t                               YOU ARE LUCKY TO BE SHOPPING HERE");
	printf("\n\n");
	printf("\t\t\tPlease note that all the Product's Price are Discounted and are Genuine");
	printf("\n");
	printf("\t\t\t\t\t");
    printf("      Reference Number: %d\n",n);


    q: printf("\n\t");
    printf("****************************");
    printf("\n");
    printf("\t");
    printf("Please Select an Option: ");
    printf("\n");
    printf("\t");
    printf("****************************");
    printf("\n");
    printf("\t");
	printf("01. ADMINISTRATOR");
	printf("\n\t");
	printf("02. CUSTOMER");
	printf("\n\t");
	printf("03. EXIT");
	printf("\n");
	printf("\n\t");

	printf("Please Enter an Option: ");
    scanf("%d", &s);

    switch(s)
    {
        case 1:
        printf("\tEnter Password : \t"); // admin is the password
        scanf("%s", password);

        if(strcmp(password, q))
        {
            printf("\nWrong Password Please Try Again");
            goto q;
        }
        else
        goto l3;
        l3:    printf("Access Granted\n");
               printf("\n\n");
               printf("\t");
               printf("****************************");
               printf("\n");
               printf("\t");
               printf("Please Select an Option: ");
               printf("\n");
               printf("\t");
               printf("****************************");
               printf("\n");
		       printf("\t01.CREATE");
		       printf("\n\t");
		       printf("02.DELETE/MODIFY");
		       printf("\n\t");
		       printf("03.DISPLAY");
		       printf("\n\t");
		       printf("04.MAIN MENU");
		       printf("\n");
		       printf("\n");
		       printf("\t");
		       printf("Please Enter an Option: ");
               scanf("%d", &y);
               switch(y)
               {
                    case 1: create();
                            goto q;
                    case 2 : edit();
                            goto q;
                    case 3 : display();
                            goto q;
                    case 4 : goto q;

                    default : printf("\nSomething Went Wrong...");
                              goto q;
               }
               break;
        case 2:printf("\t");
               printf("****************************");
               printf("\n");
               printf("\t");
               printf("Plese Select an Option: ");
               printf("\n");
               printf("\t");
               printf("****************************");
               printf("\n");
               printf("\t");
               printf("01.BILL");
               printf("\n\t");
               printf("02.INVOICE");
               printf("\n\t");
               printf("03.DISPLAY");
               printf("\n\t");
               printf("04.MYCART");
               printf("\n\t");
               printf("05.MAIN MENU");
               printf("\n\t");
               printf("06.DELETE ITEMS IN CART\n");
               printf("\n\t");
               printf("Please Enter an Option: ");
               scanf("%d",&y);
               printf("\n");

               switch(y)
               {
                case 1 : bill();
                        goto q;

                case 2 : invoice();
                         goto q;

                case 3 : display();
                         goto q;

                case 4 : mdisplay();
                         goto q;

                case 5 : goto q;

                case 6 : mdelete();
                         goto q;

                default : printf("Error\n");
                          goto q;

               }
               break;
        case 3: printf("\nExiting...");
        break;

        default: printf("\nSomething Went Wrong...");
        break;
        return 0;
    }
}

int create()
{
    FILE *fp = fopen("Record.txt", "a+");

    // to check if the file exists
    if (fp == NULL)
    {
        printf("File Missing...\n");
        printf("\nError code 2");
        return 1;
    }

    printf("Enter the Number of Products: ");
    scanf("%d", &n);

    FILE *fpq = fopen("Quantity.txt", "w");

    if(fpq == NULL)
    {
        printf("File Missing...\n");
        printf("\nError code 3");
        return 1;
    }

    fprintf(fpq, "%d", n);
    fclose(fpq);

    int i = 0;
    while (i < n) // It checks if the no of item is more than 0
    {
        printf("\nEnter Product Code : ");
        scanf("%d", &item.product_no);

        printf("\nEnter Product Name : ");
        scanf("%s", item.product_name);

        printf("\nEnter Quantity : ");
        scanf("%d", &item.quantity);

        printf("\nEnter Price : ");
        scanf("%d", &item.price);

        i ++; // Increment after a successful record

        // writing the entered data to the file
        fprintf(fp, "%d\t%s\t%d\t%d\t\n", item.product_no, item.product_name, item.quantity, item.price);
    }
    fclose(fp);
    printf("Records are Created Successfuly !!!\n");
    return 0;
}

// to print out the billing details
int bill()
{
    int na = 0;
    int a = 0;
    int count = 0;
    int r = 0;
    int w = 0;
    int ch = 0;
    int l = 0;
    int bi = 0;
    int ln = 0;

    printf("\t");
    l3: printf("\nEnter the Product Number : ");
    scanf("%d", &na);
    printf("\n");

    FILE *fp = fopen("Record.txt", "a+");
    if (fp == NULL)
    {
        printf("\nError code 4");
        return 1;
    }

    FILE *tmp = fopen("temp.txt", "w");
    if (tmp == NULL)
    {
        printf("\nError code 5");
        return 1;
    }

    while (!(feof(fp)))
    {
        l++;
        fscanf(fp, "%d", &item.product_no);
        fscanf(fp, "%s", item.product_name);
        fscanf(fp, "%d", &item.quantity);
        fscanf(fp, "%d", &item.price);

        if (item.product_no == na)
        {
            ln++;
            if (ln == 2)
            break;
            printf("\nEnter the Quantity : ");
            scanf("%d", &a);
            if (a <= item.quantity)
            {
                // here we are copying the datas entered into customer struct
                customer[ti].product_no = item.product_no;
                strcpy(customer[ti].product_name, item.product_name);
                customer[ti].quantity = a;
                customer[ti].price = item.price;
                item.quantity = item.quantity - a;
                ti ++;
            }

            else
            {
                printf("Sorry out of Stock\n");
                bi++;
            }
        }

        else
        {
            count ++;
            fprintf(tmp, "%d\t", item.product_no);
            fprintf(tmp, "%s\n", item.product_name);
            fprintf(tmp, "%d\t", item.quantity);
            fprintf(tmp, "%d\n", item.price);
            continue;
        }

        fprintf(tmp, "%d\t", item.product_no);
        fprintf(tmp, "%s\n", item.product_name);
        fprintf(tmp, "%d\t", item.quantity);
        fprintf(tmp, "%d\n", item.price);

    }

    if (l == count)
    {
        printf("Error: Please Choose Properly\n");
    }

    fclose(tmp);
    fclose(fp);
    remove("Record.txt");
    rename("temp.txt", "Record.txt");
    ln = 0;

    printf("Do you want to shop more: \n Press 1 for More\n Press 2 to Exit\n");
    scanf("%d", &k);
    if(k == 1)
    {
        goto l3;
    }
    return 0;
}

// to display the product details
int display()
{
    int nk = 0;
    FILE *file = fopen("Record.txt", "r");
    if (file == NULL)
    {
        printf("\nError code 7");
        return 1;
    }

    if(feof(file))
    {
        printf("Error in opening files\n");
    }

    printf("==============================================================\n");

    printf("|Product Number\tProduct Name\t|Quantity\t|Price\t\n");

    printf("==============================================================\n");

    while (nk != n)
    {
        nk++;
        fscanf(file, "%d", &item.product_no);

        if (item.product_no == 0)
        {
            printf("There are no items in Cart\n");
            return 1;
        }

        fscanf(file, "%s", item.product_name);
        fscanf(file, "%d", &item.quantity);
        fscanf(file, "%d", &item.price);

        printf("\n\t%d|\t%s|\t%d|\t%d|\n",item.product_no,item.product_name,item.quantity,item.price);
    }
    fclose(file);
    return 0;
}

// to edit the details in the file
int edit()
{
    int delete_file;
    int found = 0;
    int ka = 0;
    int p;

    FILE *file = fopen("Record.txt", "r");
    if (file == NULL)
    {
        printf("\nError code 10");
        return 1;
    }
    FILE *temp1 = fopen("temp1.txt", "w");
    if (file == NULL)
    {
        printf("\nError code 11");
        return 1;
    }
    FILE *temp2 = fopen("temp2.txt", "w");
    if (file == NULL)
    {
        printf("\nError code 12");
        return 1;
    }

    printf("\nEnter the Product Number to Delete : ");
    scanf("%d", &delete_file);

    p = n;

    while (!(ka == p))
    {
        ka ++;
        fscanf(file, "%d", &item.product_no);

        if(item.product_no == delete_file)  // if the selected file is found
        {
            found = 1;
            fscanf(file, "%s", item.product_name);
            fscanf(file, "%d", &item.quantity);
            fscanf(file, "%d", &item.price);
            n--;
            printf("\nProduct %d has been been deleted Successfully\n", delete_file);
        }
        else
        {
            fscanf(file, "%s", item.product_name);
            fscanf(file, "%d", &item.quantity);
            fscanf(file, "%d", &item.price);
            fprintf(temp1,"%d\t%s\t%d\t%d\t",item.product_no,item.product_name,item.quantity,item.price);
        }
    }
    fprintf(temp2, "%d", n);
    fclose(temp2);
    fclose(temp1);
    fclose(file);

    if (found == 0) // if no files have been found to edit
    {
        printf("Product Not Found");
        printf("\nError code 13");
        return 1;
    }

    // copying contents back to file
    remove("Quantity.txt");
    rename("temp2.txt", "Quantity.txt");

    remove("Record.txt");
    rename("temp1.txt", "Record.txt");
    return 0;
}

int invoice()
{
    float gross_value = 0;
    if (ti == 0)
    {
        printf("Ther are No Products in Your Cart\n");
        printf("\nError code 14");
        return 1;
    }
    printf("\n");

    printf("****************************INVOICE**************************");

    printf("product number\t| product name\t| price\t| quantity\t| amount\t|\n");

    printf("****************************INVOICE**************************");

    for (int i = 0; i < ti; i++)
    {
        customer[i].amount = 0;
        customer[i].amount = ((customer[i].price) * (customer[i].quantity));
        gross_value += customer[i].amount;
    }

    for (int i = 0; i < ti; i++)
    {
        printf("%6d\t       |%9s   \t  | %3d\t|%3d\t        |   %3d\n",customer[i].product_no,
        customer[i].product_name,customer[i].price,customer[i].quantity,customer[i].amount);
    }
    printf("\nAmount Payable : %f", gross_value);
    printf("\nThank you for Shopping");
    printf("\nVisit Again");
    return 0;
}

int mdelete()
{
    int file_to_delete = 0;
    int g = 0;
    int ag = 0;
    int aj = 0;
    char ab[100];
    FILE *file = fopen("shop.txt", "r");
    FILE *tmp = fopen("temp4.txt", "w");

    printf("\nEnter the Product Number to be Deleted :");
    scanf("%d", &file_to_delete);

    for (int i = 0; i < ti; i++)
    {
        if(customer[ti].product_no == file_to_delete)
        {
            aj = customer[i].quantity;
            printf("\nProduct Deleted Successfully");
        }
        continue;
        temp[g].product_no = customer[i].product_no;
        strcpy(temp[g].product_name, customer[i].product_name);
        temp[g].quantity = customer[i].quantity;
        temp[g].price = customer[i].price;
        g++;
    }

    for (int j = 0; j < g; j++)
    {
        customer[j].product_no = temp[j].product_no;
        strcpy(customer[j].product_name, temp[j].product_name);
        customer[j].quantity = temp[j].quantity;
        customer[j].price = temp[j].price;
    }
    ti = g;

    printf("\n%d", aj);

    for (int i = 0; i < n; i++)
    {
        fscanf(file, "%d", &item.product_no);
        fscanf(file, "%s", item.product_name);
        fscanf(file, "%d", &item.quantity);
        fscanf(file, "%d", &item.price);

        if (item.product_no == file_to_delete)
        {
            ag = aj + item.quantity;

            fprintf(tmp, "%d\t%s\t%d\t%d\t", item.product_no, item.product_name, ag, item.price);
        }
        else
        {
            fprintf(tmp, "%d\t%s\t%d\t%d\t", item.product_no, item.product_name, item.quantity, item.price);
        }
    }
    fclose(file);
    fclose(tmp);
    remove("Record.txt");
    rename("temp4.txt", "Record.txt");

    return 0;
}

int mdisplay()
{
    printf("================================================================================\n");
	printf("Product number\t|Product name\t|Quantity\t|Price\t\n");
	printf("================================================================================\n");

    for (int i = 0; i < ti; i++)
    {
        printf("%14d\t|%12s\t|%6d\t|%6d\n",customer[i].product_no, customer[i].product_name, customer[i].quantity, customer[i].price);
    }
    return 0;
}