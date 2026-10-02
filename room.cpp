#include "Room.hpp"

Room::Room(const std::string& name) 
    : m_name(name), 
    m_scenario(nullptr) 
{
    std::cout << "[Room] Создана комната: " << m_name << std::endl;
}

Room::~Room() {
    std::cout << "[Room] Комната '" << m_name << "' уничтожается. Устройства внутри тоже будут уничтожены." << std::endl;
    // Вектор m_devices автоматически вызовет деструкторы для всех устройств (композиция)
}

void Room::AddDevice(const Device& device) {
    m_devices.push_back(device);
    std::cout << "В комнату '" << m_name << "' добавлено устройство: " << device.GetName() << std::endl;
}

void Room::TurnOnAllDevices() {
    std::cout << "Включение всех устройств в комнате '" << m_name << "':" << std::endl;
    for (auto& dev : m_devices) {
        dev.TurnOn();
    }
}

void Room::TurnOffAllDevices() {
    std::cout << "Выключение всех устройств в комнате '" << m_name << "':" << std::endl;
    for (auto& dev : m_devices) {
        dev.TurnOff();
    }
}

void Room::SetScenario(Scenario* newScenario) {
    m_scenario = newScenario;
    if (m_scenario) {
        std::cout << "Комната '" << m_name << "' теперь использует сценарий: " << m_scenario->GetName() << std::endl;
    }
    else {
        std::cout << "Комната '" << m_name << "' отвязана от сценария." << std::endl;
    }
}

void Room::RunScenario() {
    if (m_scenario == nullptr) {
        std::cout << "  Ошибка: У комнаты '" << m_name << "' нет привязанного сценария!" << std::endl;
        return;
    }

    // ПРОВЕРКА ПРАВИЛА: нельзя запустить неактивный сценарий
    if (!m_scenario->GetIsActive()) {
        std::cout << "  Ошибка: Сценарий '" << m_scenario->GetName() << "' не активирован." << std::endl;
        return;
    }

    std::cout << "Комната '" << m_name << "' выполняет сценарий '" << m_scenario->GetName() << "'..." << std::endl;
    TurnOnAllDevices();
}

std::string Room::GetName() const { return m_name; }
int Room::GetDeviceCount() const { return m_devices.size(); }
Scenario* Room::GetScenario() const { return m_scenario; }