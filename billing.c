#include <stdio.h>
#include <string.h>

char *password = "admin"; // password for admin access

// to store the product details all at once variable
struct item
{
    char product[10];
    int id, price, stock;
}
item[100];

struct customer
{
    char product[10];
    int id, gross_value, customer_quantity;
}
customer[100];


int prompt(); // to prompt the option to the user
int display();    // to display the items available
int count_product();  // to count the product available
int add_product();    // to add new products into the file
void billing();
void invoice();


int main()
{
    printf("Welcome to Hari D-Mart\n");
    prompt(); 
}

int prompt()
{
    int choice = 0;

    printf("1. Display Products\n");
    printf("2. Bill Product\n");
    printf("3. Add Products\n");
    printf("4. Exit\n");
    printf("\nChoose Your Option: ");
    scanf("%i", &choice);
    switch(choice)
    {
        case 1 :
            display();
            break;
        case 2 :
            billing();
            break;

        case 3 :
            add_product();
            break;
        case 4 :
            break;
        default :
            printf("Please Choose the right Option\n");
            prompt();

    }
    return 0;
}

int display()
{
    int choice = 0;
    int num_of_product = 0;
    FILE *file = fopen("Product.txt", "r");     // file that holds the data of products

    int product_count = count_product() - 1;
    printf("%i\n",product_count);

    if (file != NULL)
    {
        printf("Product ID      Product Name   Price   Quantity\n");
        printf("____________________________________________________\n");
        for(int i = 0; i < product_count; i++)
        {
            fscanf(file, "%d %s %d %d", &item[i].id, item[i].product,
            &item[i].price, &item[i].stock);               // reads the details of the product in the provided file

            printf("\t%d\t%10s\t%d\t%d\n",
                item[i].id, item[i].product, item[i].price, item[i].stock); // print the readed data to the user

        }
        // prompt the user to go to main menu or exit
        printf("1. Go to Main Menu\n");
        printf("2. Exit\n");
        printf("Enter choice: ");
        scanf("%i", &choice);
        switch (choice)
        {
            case 1 :
                prompt();
            case 2 :
                return 1;
        }
    }
    fclose(file);
    return 0;
}

int count_product()
{
    int i = 0;
    FILE *file = fopen("Product.txt", "r");
    while (!(feof(file)))
    {
        fscanf(file, "%d %s %d %d", &item[i].id, item[i].product,
            &item[i].price, &item[i].stock);
            i++;
    }
    fclose(file);
    return i;
}

int add_product()
{
    int choice = 0;

    int product_count = count_product();
    int count = product_count + 1;
    FILE *file = fopen("Product.txt", "a+");   // used to add new products

    printf("Please enter the product details to be added\n");

    printf("Enter Product ID: ");
    scanf("%i", &item[count].id);

    printf("\nEnter Product Name: ");
    scanf("%s", item[count].product);

    printf("\nEnter Product Price: ");
    scanf("%i", &item[count].price);

    printf("\nEnter Product Stock: ");
    scanf("%i", &item[count].stock);

    fprintf(file,"%i\t%s\t%i\t%i", item[count].id, item[count].product, item[count].price, item[count].stock);
    printf("1. Go to Main Menu\n");
    printf("2. Exit\n");
    printf("Enter choice: ");
    scanf("%i", &choice);
    switch (choice)
    {
        case 1 :
            prompt();
            break;
        case 2 :
            return 1;
    }
    fclose(file);
    return 0;
}

void billing()
{
    int purchase_product;
    int quantity;
    int current_value;
    int gross_value;
    int choice;
    int count = count_product();

    FILE *file = fopen("Product.txt", "r");

    char *filename = NULL;

    printf("\nEnter Product ID : ");
    scanf("%i", &purchase_product);

    for (int i = 0; i < count; i++)
    {
        fscanf(file, "%d %s %d %d", &item[i].id, item[i].product, &item[i].price, &item[i].stock);
        if (purchase_product == item[i].id)
        {
            printf("\nEnter Quantity : ");
            scanf("%i", &quantity);

            if (quantity <= item[i].stock)
            {
                customer[i].id = item[i].id;
                strcpy(customer[i].product, item[i].product);
                customer[i].gross_value = quantity * item[i].price;
                customer[i].customer_quantity = quantity;
                printf("\nItems Entered Successfully...\n");

                item->stock = item->stock - quantity;

                printf("\n1. Add More Items");
                printf("\n2. Print Bill\n");
                scanf("%i", &choice);

                switch (choice)
                {
                case 1:
                    billing();
                    break;
                case 2:
                    invoice();
                    break;
                
                default:
                    break;
                }

            }
            else
            {
                printf("\nSorry Out Of Stock");
            }
        }
    }
    fclose(file);
}
void invoice()
{
    FILE *file = fopen("Product.txt", "r");

    int count = count_product();
    int total_price = 0; 
    char *name;
    printf("\nEnter Customer Name: ");
    scanf("%s", name);
    printf("\n\t\tHARI D-MART\n");
    printf("___________________________________________________\n");
    printf("Customer Name : %s\n", name);
    printf("___________________________________________________\n");
    printf(" ID\t  Product\tQuantity\tPrice\n");
    printf("___________________________________________________\n");
    for (int i = 0; i < count; i++)
    {
        fscanf(file, "%d %s %d %d", &item[i].id, item[i].product, &item[i].price, &item[i].stock);
        if (customer[i].id != 0)
        {
            printf("%2i\t%9s\t  %2i\t\t%4i\n", customer[i].id, customer[i].product, customer[i].customer_quantity, item[i].price);
            total_price = total_price + customer[i].gross_value;
        }       
    } 
    printf("\n");
    printf("___________________________________________________\n");
    printf("\tTotal = %i\n", total_price);
    printf("___________________________________________________\n");
    printf("\n");
    prompt();
}