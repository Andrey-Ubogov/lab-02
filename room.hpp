#pragma once

#include <string>
#include <vector>
#include "Device.hpp"
#include "Scenario.hpp"

// Класс "Комната" — владеет устройствами (композиция) и использует сценарий (агрегация).
class Room {
private:
    std::string m_name;
    std::vector<Device> m_devices; // композиция
    Scenario* m_scenario;          // агрегация (указатель на внешний объект)

public:
    // Конструктор с параметрами
    Room(const std::string& name);

    // Деструктор
    ~Room();

    // Содержательные методы
    void AddDevice(const Device& device); // Добавить устройство
    void TurnOnAllDevices(); // Включить все устройства
    void TurnOffAllDevices(); // Выключить все устройства

    void SetScenario(Scenario* newScenario); // Изменить сценарий
    void RunScenario(); // Запустить сценарий

    // Геттеры
    std::string GetName() const;
    int GetDeviceCount() const;
    Scenario* GetScenario() const;
};