/*
** EPITECH PROJECT, 2025
** CPUModule
** File description:
** CPUModule
*/

#ifndef CPUMODULE_H
#define CPUMODULE_H

#pragma once
#include "AModule.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <thread>
#include <chrono>
#include <iomanip>

struct CpuData
{
    long user, nice, system, idle, iowait, irq, softirq, steal;
};

namespace Krell {
    class CPUModule : public AModule
    {
    public:
        CPUModule();
        ~CPUModule();

        std::string getModelName() const;
        std::string getCpuCores() const;
        std::string getCpuSpeed() const;
        std::string getCpuUsage() const;

        void update() override;
        
    private:
        void getCpuInfo();
        CpuData getCpuTimes();
        void calculateCpuUsage(const CpuData &oldData, const CpuData &newData);

        std::string _modelName;
        std::string _cpuCores;
        std::string _cpuSpeed;
        std::string _cpuUsage;
        CpuData _cpu;
    };
}

#endif