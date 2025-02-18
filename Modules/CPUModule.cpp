/*
** EPITECH PROJECT, 2025
** CPUModule
** File description:
** CPUModule
*/

#include "CPUModule.hpp"

Krell::CPUModule::CPUModule()
{
    _name = "CPU Module";
    getCpuInfo();
    update();
}

Krell::CPUModule::~CPUModule()
{
}

std::string Krell::CPUModule::getModelName() const
{
    return this->_modelName;
}

std::string Krell::CPUModule::getCpuCores() const
{
    return this->_cpuCores;
}

std::string Krell::CPUModule::getCpuSpeed() const
{
    return this->_cpuSpeed;
}

std::string Krell::CPUModule::getCpuUsage() const
{
    return this->_cpuUsage;
}

void Krell::CPUModule::getCpuInfo()
{
    std::ifstream file("/proc/cpuinfo");
    std::string line;

    if (!file.is_open()) {
        std::cerr << "Error: Unable to open /proc/cpuinfo" << std::endl;
        return;
    }

    while (std::getline(file, line)) {
        if (line.find("model name") != std::string::npos)
            this->_modelName = line.substr(line.find(":") + 2);
        if (line.find("cpu cores") != std::string::npos)
            this->_cpuCores = line.substr(line.find(":") + 2);
        if (line.find("cpu MHz") != std::string::npos) {
            this->_cpuSpeed = line.substr(line.find(":") + 2) + " MHz";
        }
    }
    file.close();
}

CpuData Krell::CPUModule::getCpuTimes() {
    std::ifstream file("/proc/stat");
    std::string line;

    if (!file.is_open()) {
        std::cerr << "Error: Unable to open /proc/stat" << std::endl;
        return {};
    }

    std::getline(file, line);
    std::istringstream ss(line);

    std::string cpuLabel;
    ss >> cpuLabel >> this->_cpu.user >> this->_cpu.nice >> this->_cpu.system >> this->_cpu.idle >> this->_cpu.iowait
       >> this->_cpu.irq >> this->_cpu.softirq >> this->_cpu.steal;

    file.close();
    return this->_cpu;
}

void Krell::CPUModule::calculateCpuUsage(const CpuData &oldData, const CpuData &newData) {
    long oldIdle = oldData.idle + oldData.iowait;
    long newIdle = newData.idle + newData.iowait;

    long oldTotal = oldData.user + oldData.nice + oldData.system + oldIdle +
                    oldData.irq + oldData.softirq + oldData.steal;
    long newTotal = newData.user + newData.nice + newData.system + newIdle +
                    newData.irq + newData.softirq + newData.steal;

    long totalDiff = newTotal - oldTotal;
    long idleDiff = newIdle - oldIdle;

    double cpuUsage = (static_cast<double>(totalDiff - idleDiff) / totalDiff) * 100.0;

    std::ostringstream stream;
    stream << std::fixed << std::setprecision(2) << cpuUsage;
    this->_cpuUsage = stream.str() + " %";
}

void Krell::CPUModule::update()
{
    getCpuInfo();

    CpuData oldData = getCpuTimes();

    std::this_thread::sleep_for(std::chrono::seconds(1));

    CpuData newData = getCpuTimes();

    calculateCpuUsage(oldData, newData);

    this->_data = "Model: " + this->_modelName + "\nCores: " + this->_cpuCores + "\nSpeed: " + this->_cpuSpeed + "\nCPU Usage: " + this->_cpuUsage;

}
