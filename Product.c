
#include "Product.h"

// Product struct - represents a product in MatamIkya
struct product_t {
    unsigned int id;
    char* name;
    double amount;
    MtmProductData custom_data;
    MatamikyaAmountType amount_type;
    double profit;
    MtmCopyData copyData;
    MtmFreeData freeData;
    MtmGetProductPrice productPrice;
};


static char* stringCopy(const char* str)
{
    int length = strlen(str);
    char *out = malloc((length + 1) * sizeof(char));
    if (out == NULL)
    {
        return NULL;
    }
    for(int i = 0; i < length; i++)
    {
        out[i] = str[i];
    }
    out[length] = '\0';
    return out;
}

// Copy function for product.
// Input: Product src_product - source product from which a copy will be created.
// Output: Product - copy_product, a product with the same fields as the source product.
ListElement copyProduct(ListElement src_product)
{
    if(src_product == NULL)
    {
        return NULL;
    }
    Product copy_product = (Product)malloc(sizeof(*copy_product));
    if(copy_product == NULL)
    {
        return NULL;
    }
    copy_product->custom_data = (((Product)src_product))->copyData((((Product)src_product))->custom_data);
    if(copy_product->custom_data == NULL)
    {
        free(copy_product);
        return NULL;
    }
    copy_product->name = stringCopy(((Product)src_product)->name); //
    if(copy_product->name == NULL)
    {
        ((Product)src_product)->freeData(copy_product->custom_data);
        free(copy_product);
        return NULL;
    }
    copy_product->id = ((Product)src_product)->id;
    copy_product->amount = ((Product)src_product)->amount;
    copy_product->amount_type = ((Product)src_product)->amount_type;
    copy_product->profit = ((Product)src_product)->profit;
    copy_product->freeData = ((Product)src_product)->freeData;
    copy_product->copyData = ((Product)src_product)->copyData;
    copy_product->productPrice = ((Product)src_product)->productPrice;
    return copy_product;
}


// Free function of Product, deallocates all memory of product struct.
// Input: Product product_to_delete - product we want to deallocate.
// Output: None.
void freeProduct(ListElement product_to_delete)
{
    if(product_to_delete == NULL)
    {
        return;
    }
    (((Product)product_to_delete)->freeData((MtmProductData)((Product)product_to_delete)->custom_data));
    free(((Product)product_to_delete)->name);
    free(product_to_delete);
    return;
}

// Compare function for product, returns >0 if id2 is greater than id1, ==0 if id2 is equal to id1
// and <0 if id2 is less than id1.
int compareProduct(ListElement product1, ListElement product2)
{
    if(!product1 || !product2)
    {
        return 0;
    }
    return ((Product)product1)->id - ((Product)product2)->id;
}

