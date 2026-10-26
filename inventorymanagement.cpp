#include <iostream>
#include <fstream>
#include <string>

using namespace std;
class product
{
private:
    int product_id = 0;
    string product_name;
    string category;
    float price;
    int quantity;
    int min_reorder;

    void add_product();
    void restock_product();
    void search_product();
    void display_all_products();

public:
    void product_menu();
    void check_low_stock_alerts();
};
void product::check_low_stock_alerts()
{
    ifstream file("product.txt");
    if (!file)
        return;

    int product_id, quantity, min_reorder;
    string product_name, category;
    float price;
    bool has_warning = false;

    while (file >> product_id >> product_name >> category >> price >> quantity >> min_reorder)
    {
        if (quantity <= min_reorder)
        {
            if (!has_warning)
            {
                cout << "\n--------------------------------------------------" << endl;
                cout << "     LOW-STOCK WARNING: Items Need Restocking!" << endl;
                cout << "--------------------------------------------------" << endl;
                has_warning = true;
            }
            cout << product_name << " (ID: " << product_id << ") | Stock: " << quantity
                 << "  Min Threshold: " << min_reorder << endl;
        }
    }
    if (has_warning)
    {
        cout << "--------------------------------------------------\n"
             << endl;
    }
    file.close();
}

void product::search_product()
{
    string name;
    cout << "enter the name of productt u want to search" << endl;
    cin >> name;

    ifstream products("product.txt");
    int product_id;
    string product_name, category;
    float price;
    int quantity, min_reorder;
    bool found = false;
    while (products >> product_id >> product_name >> category >> price >> quantity >> min_reorder)
    {
        if (product_name == name)
        {
            found = true;
            cout << "product id is:" << product_id << endl;
            cout << "product name is:" << product_name << endl;
            cout << " product category is :" << category << endl;
            cout << "product price is:" << price << endl;
            cout << "product quantity is:" << quantity << endl;
            cout << " minimum stock must be :" << min_reorder << endl;
            if (quantity <= min_reorder)
            {
                cout << " low stock alert" << endl;
            }
            cout << endl;
        }
    }
    products.close();
    if (found == false)
    {
        cout << "no product found" << endl;
    }
}
void product::add_product()
{

    ifstream check("product.txt");
    int last_id = 0, quantity, min_reorder;
    string product_name, category;
    float price;
    while (check >> last_id >> product_name >> category >> price >> quantity >> min_reorder)
    {
    }
    check.close();

    product_id = last_id + 1;
    ofstream products("product.txt", ios::app);

    cout << "enter the product name" << endl;
    cin >> product_name;
    cout << "enter the category" << endl;
    cin >> category;
    cout << "enter the product price" << endl;
    cin >> price;
    cout << "enter the quantiy of product" << endl;
    cin >> quantity;
    cout << "what should be the min stock of this product" << endl;
    cin >> min_reorder;
    products << product_id << " " << product_name << " " << category << " " << price << " " << quantity << " " << min_reorder << endl;
    products.close();
    cout << "product added successfully!" << endl;
}

void product::restock_product()
{
    string search_name;
    int add_qty;
    cout << "\n--- Restock Incoming Shipment ---" << endl;
    cout << "Enter product name to restock: ";
    cin >> search_name;
    cout << "Enter quantity received: ";
    cin >> add_qty;

    if (add_qty <= 0)
    {
        cout << "Invalid quantity." << endl;
        return;
    }

    ifstream read_file("product.txt");
    ofstream temp_file("temp_product.txt");

    int product_id, quantity, min_reorder;
    string product_name, category;
    float price;
    bool found = false;

    while (read_file >> product_id >> product_name >> category >> price >> quantity >> min_reorder)
    {
        if (product_name == search_name)
        {
            found = true;
            quantity = quantity + add_qty;
            cout << "Stock updated! New quantity for " << product_name << ": " << quantity << endl;
        }
        temp_file << product_id << " " << product_name << " " << category << " " << price << " " << quantity << " " << min_reorder << endl;
    }
    read_file.close();
    temp_file.close();

    remove("product.txt");
    rename("temp_product.txt", "product.txt");

    if (!found)
    {
        cout << "Product ID not found." << endl;
    }
}

void product::display_all_products()

{
    ifstream products("product.txt");

    if (!products)
    {
        cout << "No products available." << endl;
        return;
    }
    int product_id, min_reorder;
    string product_name, category;
    float price;
    int quantity;
    cout << "-----product list is : -----" << endl;
    while (products >> product_id >> product_name >> category >> price >> quantity >> min_reorder)
    {

        cout << "product id is:" << product_id << endl;
        cout << "product name is:" << product_name << endl;
        cout << " product category is:" << category << endl;
        cout << "product price is:" << price << endl;
        cout << "product quantity is:" << quantity << endl;
        cout << " stock must be :" << min_reorder << endl;
        cout << endl;
    }
    products.close();

    cout<<"------low stock products are------"<<endl;
    check_low_stock_alerts();
}
void product::product_menu()

{

    while (true)
    {
        cout << "--------------------" << endl;
        cout << " Product Management " << endl;
        cout << "--------------------" << endl;
        cout << "1.Add product" << endl;
        cout << "2.restock product" << endl;
        cout << "3.search product" << endl;
        cout << "4.display all products" << endl;
        cout << "5.back" << endl;
        int choice;
        cout << "enter the choice" << endl;
        cin >> choice;
        switch (choice)
        {
        case 1:
            add_product();
            break;
        case 2:
            restock_product();
            break;
        case 3:
            search_product();
            break;
        case 4:
            display_all_products();
            break;
        case 5:
            return;
        default:
            cout << "invalid choice" << endl;
        }
    }
}

class customer
{
private:
    int customer_id = 0;
    string customer_name;
    long long phone_number;
    void add_customer();
    void search_customer();
    void display_all_customer();

public:
    void customer_menu();
};

void customer::customer_menu()
{

    while (true)
    {
        cout << "---------------------" << endl;
        cout << " Customer Management " << endl;
        cout << "---------------------" << endl;
        cout << "1.add customer" << endl;
        cout << "2.search customer" << endl;
        cout << "3.display all customer" << endl;
        cout << "4.exit" << endl;

        int choice;
        cout << "enter the choice " << endl;
        cin >> choice;
        switch (choice)
        {
        case 1:
            add_customer();
            break;
        case 2:
            search_customer();
            break;
        case 3:
            display_all_customer();
            break;
        case 4:
            return;
        default:
            cout << "invalid choice" << endl;
        }
    }
}
void customer::add_customer()
{
    ifstream check2("customers.txt");
    int last_id = 0;
    string customer_name;
    long long phone_number;

    while (check2 >> last_id >> customer_name >> phone_number)
    {
    }
    check2.close();

    customer_id = last_id + 1;
    ofstream customers("customers.txt", ios::app);
    cout << "enter customer name" << endl;
    cin >> customer_name;
    cout << "enter phone number" << endl;
    cin >> phone_number;

    customers << customer_id << " " << customer_name << " " << phone_number << endl;
    customers << endl;

    customers.close();
}
void customer::search_customer()
{
    ifstream customers("customers.txt");
    string name;
    cout << "enter name of customer u  want to search" << endl;
    cin >> name;

    string customer_name;
    long long phone_number;
    bool found = false;

    while (customers >> customer_id >> customer_name >> phone_number)
    {
        if (customer_name == name)
        {
            found = true;
            cout << "customer name is :" << customer_name << endl;
            cout << "mobile number is :" << phone_number << endl;
        }
    }
    if (found == false)
    {
        cout << "no customer found" << endl;
    }
    customers.close();
}
void customer::display_all_customer()
{
    ifstream customers("customers.txt");

    string customer_name;
    long long phone_number;

    while (customers >> customer_id >> customer_name >> phone_number)
    {
        cout << "customer name is :" << customer_name << endl;
        cout << "mobile number is :" << phone_number << endl;
        cout << endl;
    }
    customers.close();
}

class bill
{
    char que;
    int billing_id = 0;
    string buy_product;
    int buy_quantity;
    string name;
    bool found = false;

    void add_product();
    void show_cart();
    void total_bill();

public:
    void bill_menu();
};

void bill::bill_menu()
{
    while (true)
    {

        cout << "--------------------" << endl;
        cout << "   Bill Management  " << endl;
        cout << "--------------------" << endl;
        cout << "1.add items" << endl;
        cout << "2.show items" << endl;
        cout << "3.total bill" << endl;
        cout << "4.exit" << endl;
        int choice;
        cout << "enter the value" << endl;
        cin >> choice;

        switch (choice)
        {
        case 1:
            add_product();
            break;

        case 2:
            show_cart();
            break;

        case 3:
            total_bill();
            break;

        case 4:
            return;
            break;

        default:
            cout << "invalid choice" << endl;
        }
    }
}
void bill::add_product()
{
    // char que;
    // cout << "are u a regular customer(y/n)" << endl;
    // cin >> que;
    cout << "please enter your name" << endl;
    cin >> name;

    ifstream customers("customers.txt");
    string customer_name;
    int customer_id;
    long long phone_number;
    while (customers >> customer_id >> customer_name >> phone_number)
    {
        if (customer_name == name)
        {
            found = true;
        }
    }
    if (found == false)
    {
        cout << "you are not regular customer" << endl;
    }
    customers.close();
    cout << "enter the product u want to purchase" << endl;
    cin >> buy_product;

    ifstream products("product.txt");
    int product_id, min_reorder;
    string product_name, category;
    float price;
    int quantity;
    bool product_found = false;
    float item_price = 0;
    int item_qty = 0;

    while (products >> product_id >> product_name >> category >> price >> quantity >> min_reorder)
    {
        if (product_name == buy_product)
        {
            product_found = true;
            item_price = price;
            item_qty = quantity;
            break;
        }
    }
    products.close();

    if (product_found == false)
    {
        cout << "no product found" << endl;
        return;
    }
    cout << "enter the quantity" << endl;
    cin >> buy_quantity;

    if (buy_quantity > item_qty)
    {
        cout << "insufficient quantity. " << item_qty << endl;
        return;
    }

    ofstream cart("cart.txt", ios::app);
    cart << buy_product << " " << item_price << " " << buy_quantity << endl;
    cart.close();

    ifstream read_prod("product.txt");
    ofstream write_prod("temp_product.txt");

    while (read_prod >> product_id >> product_name >> category >> price >> quantity >> min_reorder)
    {
        if (product_name == buy_product)
        {
            quantity = quantity - buy_quantity;
        }
        write_prod << product_id << " " << product_name << " " << category << " " << price << " " << quantity << " " << min_reorder << endl;
    }
    read_prod.close();
    write_prod.close();

    remove("product.txt");
    rename("temp_product.txt", "product.txt");

    cout << "product added to cart successfully" << endl;
}

void bill::show_cart()
{
    ifstream cart("cart.txt");
    if (!cart)
    {
        cout << "cart is empty" << endl;
        return;
    }

    string product_name;
    float price;
    int quantity;
    bool empty = true;

    cout << "--- Cart Items ---" << endl;
    while (cart >> product_name >> price >> quantity)
    {
        empty = false;
        cout << "product name is:" << product_name << endl;
        cout << "price:" << price << endl;
        cout << "quantity:" << quantity << endl;
        cout << "total:" << (price * quantity) << endl;
        cout << "--------------------" << endl;
    }
    cart.close();

    if (empty)
    {
        cout << "cart is empty" << endl;
    }
}

void bill::total_bill()
{
    ifstream cart("cart.txt");
    if (!cart)
    {
        cout << "cart is empty" << endl;
        return;
    }

    ifstream check("product.txt");
    int last_id = 0, quantity, min_reorder;
    string product_name, category;
    float price;
    while (check >> last_id >> product_name >> category >> price >> quantity >> min_reorder)
    {
    }
    check.close();

    billing_id = last_id + 1;
    float total = 0;

    string bill_filename = name + "_bill.txt";
    ofstream customer_bill(bill_filename, ios::app);

    customer_bill << "================ Final Bill ================" << endl;
    customer_bill << "Billing ID: " << billing_id << endl;
    customer_bill << "Customer Name: " << name << endl;

    while (cart >> product_name >> price >> quantity)
    {
        float item_total = price * quantity;
        total = total + item_total;

        cout << product_name << " x " << quantity << " = " << item_total << endl;
        customer_bill << product_name << " x " << quantity << " = " << item_total << endl;
    }
    cart.close();

    cout << "--------------------------------------------" << endl;
    cout << "subtotal: " << total << endl;
    customer_bill << "--------------------------------------------" << endl;
    customer_bill << "subtotal: " << total << endl;

    float discount = 0;
    if (found == true)
    {
        discount = total * 0.10f;
        cout << "discount (10%): " << discount << endl;
        customer_bill << "discount (10%): " << discount << endl;
    }

    float final_bill = total - discount;
    cout << "total bill: " << final_bill << endl;
    cout << "============================================" << endl;

    customer_bill << "total bill: " << final_bill << endl;
    customer_bill << "============================================\n\n";
    customer_bill.close();

    remove("cart.txt");
    found = false;
}

class reports
{
public:
    void show_reports()
    {
        while (true)
        {
            cout << "--------------------" << endl;
            cout << "  Reports & Trends  " << endl;
            cout << "--------------------" << endl;
            cout << "1. Inventory Valuation" << endl;
            cout << "2. Back" << endl;

            int choice;
            cout << "Enter choice: ";
            cin >> choice;

            switch (choice)
            {
            case 1:
                show_inventory_valuation();
                break;
            case 2:
                return;
            default:
                cout << "Invalid choice." << endl;
            }
        }
    }

private:
    void show_inventory_valuation()
    {
        ifstream products("product.txt");
        if (!products)
        {
            cout << "No products found." << endl;
            return;
        }

        int product_id, quantity, min_reorder;
        string product_name, category;
        float price;
        float total_value = 0;
        int total_units = 0;

        while (products >> product_id >> product_name >> category >> price >> quantity >> min_reorder)
        {
            total_value = total_value + (price * quantity);
            total_units = total_units + quantity;
        }
        products.close();

        cout << "\n============= INVENTORY VALUATION =============" << endl;
        cout << "Total items currently in stock: " << total_units << endl;
        cout << "Total inventory asset value:    $" << total_value << endl;
        cout << "===============================================\n"
             << endl;
    }
};

class payment
{
public:
    payment()
    {
        cout << "please select your payment method" << endl;
    }
    void cash();
    void upi();
    void card();

    void payment_method()
    {
        int que2;
        cout << "1.cash" << endl;
        cout << "2.upi" << endl;
        cout << "3.card" << endl;
        cout << "please enter your choice" << endl;
        cin >> que2;
        switch (que2)
        {
        case 1:
            cash();
            break;
        case 2:
            upi();
            break;
        case 3:
            card();
            break;
        default:
            cout << "invalid choice" << endl;
        }
    }
};
void payment::card()
{
    long int card_number;
    cout << "please enter card details" << endl;
    cin >> card_number;

    cout << "thanks payment done " << endl;
}

void payment::cash()
{
    cout << "please pay money in cash at counter" << endl;
}

void payment::upi()
{
    string upi_id;
    cout << "please enter ur upi id" << endl;
    cin >> upi_id;
    cout << "thanks for the id" << endl;
    cout << "notification has been sent successfully" << endl;
}

int main()
{

    product p;
    customer c;
    bill b;
    payment p1;
    reports r;

    while (true)
    {
        cout << "---------------------------------------" << endl;
        cout << " order and inventory Management System " << endl;
        cout << "---------------------------------------" << endl;
        cout << "1.product management" << endl;
        cout << "2.customer management" << endl;
        cout << "3.bill management" << endl;
        cout << "4.reports" << endl;
        cout << "5.payment" << endl;
        cout << "6.exit" << endl;

        int choice;
        cout << "enter the choice" << endl;
        cin >> choice;
        switch (choice)
        {
        case 1:
            p.product_menu();
            break;
        case 2:
            c.customer_menu();
            break;
        case 3:
            b.bill_menu();
            break;
        case 4:
            r.show_reports();
            break;
        case 5:
            p1.payment_method();
            break;
        case 6:
            exit(0);
            break;
        default:
            cout << "invalid choice" << endl;
        }
    }
}