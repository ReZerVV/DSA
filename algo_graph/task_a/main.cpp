/*
    Арбітражні операції дозволяють використовувати різницю в
    поточному курсі валюти для перетворення одиниці валюти у більшу
    кількість одиниць тієї ж валюти. Вхідні дані задаються таблицею
    обмінних курсів, яка визначає, скільки за одну одиницю однієї валюти
    можна купити одиниць іншої валюти. Знайти для заданої
    користувачем валюти найвигіднішу можливість виконання таких
    арбітражних операцій. Необхідні перетворення можна виконати за
    допомогою логарифмування.
*/

#include <iostream>
#include <iomanip>
#include "graph.hpp"
#include <string>
#include <map>

const std::vector<std::string> currency_sing {
    "UAN",
    "USD",
    "EUR",
    "GBP",
    "GPY",
    "CNY",
    "ILS",
    "KRW",
};

struct exchange_rate {
    std::string from;   // currency from 
    std::string to;     // currency to
    int32_t     rate;    // amount of currency 'to' for currency 'from'
};

int main(int argc, char **argv) {
    graph g(currency_sing.size());

    g.append_edge(0, 1, 4);
    g.append_edge(0, 2, 4);

    g.append_edge(2, 4, 4);
    g.append_edge(2, 5, -2);

    g.append_edge(3, 0, 3);
    g.append_edge(3, 2, 2);

    g.append_edge(4, 3, 1);
    g.append_edge(4, 6, -2);

    g.append_edge(5, 1, 3);
    g.append_edge(5, 4, -3);
    
    g.append_edge(6, 5, 2);
    g.append_edge(6, 7, 2);

    g.append_edge(7, 4, -2);

    std::cout << std::boolalpha << g.is_contains_negative_cycle() << std::endl;
    
    std::vector<int32_t> cycle = g.get_negative_cycle();
    { // print cycle
        std::cout << "cycle:" << std::endl;
        for (int32_t i = 0; i < cycle.size(); ++i) {
            std::cout << "(" << currency_sing[cycle[i]] << ")  ";
        }
        std::cout << std::endl;
    }
    return 0;
}