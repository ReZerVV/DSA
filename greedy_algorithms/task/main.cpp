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

    struct Product {
        Product()
            :
            type(ProductType::PRODUCT_NULL),
            count(1) {}
        Product(const ProductType type, const int count = 0)
            :
            type(type),
            count(count) {}
        ProductType type;
        int         count;
    };
    bool compareProduct(const Product& firstProduct, const Product& secondProduct) {
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
        Seller seller;
    public:
        Store(const int fastProductCount)
            :
            seller({ fastProductCount }) {}
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
                }
                else {
                    time += 2;
                    if (seller.fastProducts.size() >= seller.maxSizeFastProducts) {
                        std::sort(seller.fastProducts.begin(), seller.fastProducts.end(), compareProduct);
                        seller.fastProducts.erase(seller.fastProducts.begin());
                    }
                    seller.fastProducts.push_back(Product{ it->type, 1 });
                }
            }
            std::cout << "Time: " << time << std::endl;
            return time;
        }
    };

}

int main(int argc, char** argv) {
    task::Store store{ 3 };
    store.Buy(std::vector<task::Product>
    {
        task::Product{ task::ProductType::PRODUCT_1 },
        task::Product{ task::ProductType::PRODUCT_5 },
        task::Product{ task::ProductType::PRODUCT_1 },
        task::Product{ task::ProductType::PRODUCT_6 },
        task::Product{ task::ProductType::PRODUCT_8 },
    });
    store.Buy(std::vector<task::Product>
    {
        task::Product{ task::ProductType::PRODUCT_1 },
        task::Product{ task::ProductType::PRODUCT_5 },
    });
    store.Buy(std::vector<task::Product>
    {
        task::Product{ task::ProductType::PRODUCT_8 },
        task::Product{ task::ProductType::PRODUCT_3 },
        task::Product{ task::ProductType::PRODUCT_1 },
        task::Product{ task::ProductType::PRODUCT_8 },
    });
    store.Buy(std::vector<task::Product>
    {
        task::Product{ task::ProductType::PRODUCT_7 },
        task::Product{ task::ProductType::PRODUCT_1 },
        task::Product{ task::ProductType::PRODUCT_8 },
    });

    return 0;
}