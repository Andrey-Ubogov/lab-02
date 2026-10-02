#include <iostream>
#include "Room.hpp"
#include "Scenario.hpp"
#include "Device.hpp"

int main() {

    system("chcp 1251");
    setlocale(LC_ALL, "Rus");

    std::cout << "========== ДЕМОНСТРАЦИЯ ==========\n" << std::endl;

    // 1. АГРЕГАЦИЯ: Создаем сценарий ВНЕ комнаты
    std::cout << "--- 1. Создание внешнего сценария (Агрегация) ---" << std::endl;
    Scenario* morningScenario = new Scenario("Утренний свет", "07:00");
    morningScenario->Activate();

    // 2. КОМПОЗИЦИЯ: Комната во вложенном блоке
    std::cout << "\n--- 2. Вход во вложенный блок (Композиция) ---" << std::endl;
    {
        // Статическая инициализация объекта
        Room livingRoom("Гостиная");

        // Работа по ссылке: добавляем устройства
        Device lamp("Умная лампа", 10);
        Device tv("Телевизор", 150);

        // Добавляем устройства в комнату (копируются внутрь)
        livingRoom.AddDevice(lamp);
        livingRoom.AddDevice(tv);

        // Привязываем сценарий (Агрегация)
        livingRoom.SetScenario(morningScenario);

        // Работа по указателю: демонстрация полиморфизма или просто доступа
        Device* ptrSocket = new Device("Умная розетка", 0);
        livingRoom.AddDevice(*ptrSocket); // Разыменовываем указатель
        delete ptrSocket; // Удаляем оригинал, в комнате осталась копия

        // Запускаем сценарий
        std::cout << "\n--- Запуск сценария ---" << std::endl;
        livingRoom.RunScenario();

        // Демонстрация проверки правила
        std::cout << "\n--- Проверка правила: поломка устройства ---" << std::endl;
        Device brokenLamp("Сломанная лампа", 5);
        brokenLamp.Break();
        brokenLamp.TurnOn(); // Должна быть ошибка

        std::cout << "\n--- Выход из блока. Комната будет уничтожена. ---" << std::endl;
    } // Здесь сработает деструктор Room, затем деструкторы Device

    // 3. ПРОВЕРКА АГРЕГАЦИИ: Сценарий всё еще жив
    std::cout << "\n--- 3. После уничтожения комнаты ---" << std::endl;
    std::cout << "Сценарий '" << morningScenario->GetName() << "' всё еще существует!" << std::endl;
    morningScenario->Deactivate();

    // Удаляем сценарий вручную
    delete morningScenario;

    // 4. ДИНАМИЧЕСКИЙ МАССИВ ОБЪЕКТОВ
    std::cout << "\n--- 4. Динамический массив объектов (new Device[3]) ---" << std::endl;
    Device* deviceArray = new Device[3]; // Массив из 3 устройств по умолчанию

    for (int i = 0; i < 3; ++i) {
        std::cout << "  Элемент массива " << i << ": " << deviceArray[i].GetName() << std::endl;
    }
    delete[] deviceArray; // Удаляем массив

    // 5. МАССИВ ДИНАМИЧЕСКИХ ОБЪЕКТОВ
    std::cout << "\n--- 5. Массив динамических объектов (Device* arr[2]) ---" << std::endl;
    Device* dynamicDevices[2]; // Массив указателей
    dynamicDevices[0] = new Device("Лампа 1", 10);
    dynamicDevices[1] = new Device("Лампа 2", 12);

    // Работаем с ними
    dynamicDevices[0]->TurnOn();
    dynamicDevices[1]->TurnOn();

    // Удаляем каждый объект отдельно
    delete dynamicDevices[0];
    delete dynamicDevices[1];

    std::cout << "\n========== КОНЕЦ ДЕМОНСТРАЦИИ ==========" << std::endl;
    return 0;
}