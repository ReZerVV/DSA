/*
    Продавець у маленькій крамниці має звичку тримати під рукою
    найпопулярніші товари для того, щоб пришвидшити роботу з чергою
    покупців. Кількість таких товарів визначається додатково. Кожен
    покупець замовляє по черзі товари, а продавець перевіряє, чи є такий
    товар під рукою. Якщо товару немає, то він дістає його з полиць, що
    займає більше часу. При цьому для кожного такого товару продавець
    має вирішити, чи не треба його помістити до найпопулярніших
    замість якогось з існуючих. Допоможіть продавцю приймати дане
    рішення протягом просування всієї черги замовлень покупців, якщо
    він прагне зменшити час, за який вся черга залишить крамницю.
    Припустіть, що продавець знає наперед про те, які товари бажає
    купити кожен з покупців у черзі.
*/

#include <stddef.h>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

namespace task
{

enum ProductType : uint8_t {
    PRODUCT_NULL = 0,
    PRODUCT_1,
    PRODUCT_2,
    PRODUCT_3,
    PRODUCT_4,
    PRODUCT_5,
    PRODUCT_6,
    PRODUCT_7,
    PRODUCT_8,
    PRODUCT_9,
    PRODUCT_10,
    PRODUCT_11,
    PRODUCT_12,
    PRODUCT_13,
    PRODUCT_14,
    PRODUCT_15,
    PRODUCT_16,
    PRODUCT_17,
    PRODUCT_18,
    PRODUCT_19,
    PRODUCT_20,
};

std::string ProductTypeToString(const ProductType type) {
    switch (type) {
        case ProductType::PRODUCT_1: return "PRODUCT_1";
        case ProductType::PRODUCT_2: return "PRODUCT_2";
        case ProductType::PRODUCT_3: return "PRODUCT_3";
        case ProductType::PRODUCT_4: return "PRODUCT_4";
        case ProductType::PRODUCT_5: return "PRODUCT_5";
        case ProductType::PRODUCT_6: return "PRODUCT_6";
        case ProductType::PRODUCT_7: return "PRODUCT_7";
        case ProductType::PRODUCT_8: return "PRODUCT_8";
        case ProductType::PRODUCT_9: return "PRODUCT_9";
        case ProductType::PRODUCT_10: return "PRODUCT_10";
        case ProductType::PRODUCT_11: return "PRODUCT_11";
        case ProductType::PRODUCT_12: return "PRODUCT_12";
        case ProductType::PRODUCT_13: return "PRODUCT_13";
        case ProductType::PRODUCT_14: return "PRODUCT_14";
        case ProductType::PRODUCT_15: return "PRODUCT_15";
        case ProductType::PRODUCT_16: return "PRODUCT_16";
        case ProductType::PRODUCT_17: return "PRODUCT_17";
        case ProductType::PRODUCT_18: return "PRODUCT_18";
        case ProductType::PRODUCT_19: return "PRODUCT_19";
        case ProductType::PRODUCT_20: return "PRODUCT_20";
        default: return "undefined";
    }
}

struct Product {
    Product()
        :
        type(ProductType::PRODUCT_NULL),
        count(1) {}
    Product(const ProductType type, const int count)
        :
        type(type),
        count(count) {}
    ProductType type;
    int         count;
};
bool compareProduct(const Product &firstProduct, const Product &secondProduct) {
    return firstProduct.count < secondProduct.count;
}

struct Seller {
    Seller(const int sizeFastProducts) 
        :
        fastProducts(std::vector<Product>{  }),
        maxSizeFastProducts(sizeFastProducts) {}
    std::vector<Product>    fastProducts;
    int                     maxSizeFastProducts;
};

class Store {
public:
    explicit Store(std::vector<std::vector<Product> > orders)
        :
        seller(5) {
        for (auto it = orders.begin(); it != orders.end(); ++it) {
            std::cout << "Time: " << Buy(*it) << std::endl;
        }
    }
public:
    float Buy(std::vector<Product> order) {
        float time = 0.0f;
        for (auto it = order.begin(); it != order.end(); ++it) {
            auto fpit = seller.fastProducts.end();
            for (fpit = seller.fastProducts.begin(); fpit != seller.fastProducts.end(); ++fpit) {
                if (fpit->type == it->type) {
                    break;
                }
            }
            if (fpit != seller.fastProducts.end()) {
                time += 1;
                fpit->count += 1;
            } else {
                time += 2;
                if (seller.fastProducts.size() >= seller.maxSizeFastProducts) {
                    std::sort(seller.fastProducts.begin(), seller.fastProducts.end(), compareProduct);
                    seller.fastProducts.erase(seller.fastProducts.begin());
                    for (fpit = seller.fastProducts.begin(); fpit != seller.fastProducts.end(); ++fpit) {
                        std::cout << fpit->count << ' ';
                    }
                    std::cout << std::endl;
                }
                seller.fastProducts.push_back(Product{it->type, 1});
            }
        }
        return time;
    }
private:
    Seller  seller;
};

}

int main(int argc, char** argv) {
    task::Store store{std::vector<std::vector<task::Product> >{
        {
            task::Product{ task::ProductType::PRODUCT_1, 0 },
            task::Product{ task::ProductType::PRODUCT_5, 0 },
            task::Product{ task::ProductType::PRODUCT_1, 0 },
            task::Product{ task::ProductType::PRODUCT_6, 0 },
            task::Product{ task::ProductType::PRODUCT_8, 0 },
        },
        {
            task::Product{ task::ProductType::PRODUCT_20, 0 },
            task::Product{ task::ProductType::PRODUCT_10, 0 },
        },
        {
            task::Product{ task::ProductType::PRODUCT_19, 0 },
            task::Product{ task::ProductType::PRODUCT_3, 0 },
            task::Product{ task::ProductType::PRODUCT_16, 0 },
            task::Product{ task::ProductType::PRODUCT_8, 0 },
        },
        {
            task::Product{ task::ProductType::PRODUCT_7, 0 },
            task::Product{ task::ProductType::PRODUCT_11, 0 },
            task::Product{ task::ProductType::PRODUCT_12, 0 },
        },
    }};

    return 0;
}