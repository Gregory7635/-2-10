#include <iostream>
#include <fstream>
#include <string>

struct BuyerData {
    std::string name; 
    std::string purchaseDate; 
    double firstHalfTotalCost;
    double secondHalfTotalCost; 
    double discountPercentage; 
};

int main() {
    // Создание бинарного файла и запись исходных данных
    setlocale(LC_ALL, "RU");
    BuyerData buyer1;
    buyer1.name = "Иванов И.И.";
    buyer1.purchaseDate = "01.07.2024";
    buyer1.firstHalfTotalCost = 5000.0;
    buyer1.secondHalfTotalCost = 8000.0;
    buyer1.discountPercentage = 5.0;

    BuyerData buyer2;
    buyer2.name = "Петров П.П.";
    buyer2.purchaseDate = "15.06.2024";
    buyer2.firstHalfTotalCost = 12000.0;
    buyer2.secondHalfTotalCost = 10000.0;
    buyer2.discountPercentage = 3.0;

    // Вывод данных на консоль до обработки
    std::cout << "Данные покупателя 1 до обновления:" << std::endl;
    std::cout << "Имя: " << buyer1.name << std::endl;
    std::cout << "Дата покупки: " << buyer1.purchaseDate << std::endl;
    std::cout << "Общая стоимость за первое полугодие: " << buyer1.firstHalfTotalCost << std::endl;
    std::cout << "Общая стоимость за второе полугодие: " << buyer1.secondHalfTotalCost << std::endl;
    std::cout << "Процент скидки: " << buyer1.discountPercentage << "%" << std::endl << std::endl;

    std::cout << "Данные покупателя 2 до обновления:" << std::endl;
    std::cout << "Имя: " << buyer2.name << std::endl;
    std::cout << "Дата покупки: " << buyer2.purchaseDate << std::endl;
    std::cout << "Общая стоимость за первое полугодие: " << buyer2.firstHalfTotalCost << std::endl;
    std::cout << "Общая стоимость за второе полугодие: " << buyer2.secondHalfTotalCost << std::endl;
    std::cout << "Процент скидки: " << buyer2.discountPercentage << "%" << std::endl << std::endl;

    // Запись данных в файл
    std::ofstream file("buyers.bin", std::ios::binary);
    if (file.is_open()) {
        file.write(reinterpret_cast<const char*>(&buyer1), sizeof(buyer1));
        file.write(reinterpret_cast<const char*>(&buyer2), sizeof(buyer2));
        file.close();
    }
    else {
        std::cout << "Не удалось открыть файл для записи." << std::endl;
        return 1;
    }

    // Обновление процентной скидки

    // Открытие файла для чтения и обновления данных
    std::ifstream readFile("buyers.bin", std::ios::binary | std::ios::in);
    std::ofstream writeFile("buyers_updated.bin", std::ios::binary | std::ios::out);

    if (readFile.is_open() and writeFile.is_open()) {
        BuyerData buyer;
        while (readFile.read(reinterpret_cast<char*>(&buyer), sizeof(buyer))) {
            // Проверка условия для обновления процентной скидки
            if (buyer.firstHalfTotalCost >= 10000.0 && buyer.secondHalfTotalCost >= 10000.0) {
                buyer.discountPercentage += 7.0;
            }
            // Запись обновленных данных в новый файл
            writeFile.write(reinterpret_cast<const char*>(&buyer), sizeof(buyer));
        }

        // Закрытие файлов
        readFile.close();
        writeFile.close();

        std::cout << "Обновленный файл успешно создан." << std::endl;
    }
    else {
        std::cout << "Не удалось открыть файлы для чтения или записи." << std::endl;
        return 1;
    }
    std::ifstream updatedFile("buyers_updated.bin", std::ios::binary | std::ios::in);
    if (updatedFile.is_open()) {
        BuyerData updatedBuyer;
        std::cout << "Данные покупателей после обновления:" << std::endl;
        while (updatedFile.read(reinterpret_cast<char*>(&updatedBuyer), sizeof(updatedBuyer))) {
            std::cout << "Имя: " << updatedBuyer.name << std::endl;
            std::cout << "Дата покупки: " << updatedBuyer.purchaseDate << std::endl;
            std::cout << "Общая стоимость за первое полугодие: " << updatedBuyer.firstHalfTotalCost << std::endl;
            std::cout << "Общая стоимость за второе полугодие: " << updatedBuyer.secondHalfTotalCost << std::endl;
            std::cout << "Процент скидки: " << updatedBuyer.discountPercentage << "%" << std::endl << std::endl;
        }
        updatedFile.close();
    }

    return 0;
}
