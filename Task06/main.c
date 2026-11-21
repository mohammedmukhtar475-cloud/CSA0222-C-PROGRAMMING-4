#include <stdio.h>

#define MAX_ITEMS 20
#define MAX_SALES 100

typedef struct {
    int day, month, year;
} Date;

typedef enum {
    PACKAGED = 1,
    COOKED,
    COMBO
} ItemType;

typedef struct {
    float price;
    Date expiry;
} PackagedData;

typedef struct {
    float price;
    int hour, minute;
} CookedData;

typedef struct {
    int componentIds[3];
    int componentCount;
} ComboData;

typedef struct {
    int id;
    char name[40];
    ItemType type;
    int stock;

    union {
        PackagedData packaged;
        CookedData cooked;
        ComboData combo;
    } details;

} Item;

typedef struct {
    int itemId;
    int quantity;
    float revenue;
} Sale;

Item items[MAX_ITEMS];
Sale sales[MAX_SALES];

int itemCount = 0;
int saleCount = 0;

Item *findItem(int id)
{
    for (int i = 0; i < itemCount; i++) {
        if (items[i].id == id)
            return &items[i];
    }

    return NULL;
}

float getPrice(const Item *item)
{
    if (item->type == PACKAGED)
        return item->details.packaged.price;

    if (item->type == COOKED)
        return item->details.cooked.price;

    return 0;
}

float comboPrice(const Item *item)
{
    float total = 0;

    for (int i = 0;
         i < item->details.combo.componentCount; i++) {

        Item *part = findItem(
            item->details.combo.componentIds[i]);

        if (part != NULL)
            total += getPrice(part);
    }

    return total;
}

int recordSale(int id, int quantity)
{
    Item *item = findItem(id);

    if (item == NULL || quantity <= 0 ||
        saleCount >= MAX_SALES) {
        printf("Invalid sale\n");
        return 0;
    }

    if (item->stock < quantity) {
        printf("Insufficient stock for %s\n",
               item->name);
        return 0;
    }

    float price;

    if (item->type == COMBO)
        price = comboPrice(item);
    else
        price = getPrice(item);

    item->stock -= quantity;

    sales[saleCount].itemId = id;
    sales[saleCount].quantity = quantity;
    sales[saleCount].revenue = price * quantity;

    saleCount++;

    printf("Sale recorded: %s = Rs. %.2f\n",
           item->name, price * quantity);

    return 1;
}
