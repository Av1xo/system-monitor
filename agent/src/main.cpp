#include "agent/provider.hpp"
#include <iostream>

MetricsProvider* create_provider();

int main()
{
    auto* provider = create_provider();
    auto m = provider->collect();

    std::cout << "CPU: " << m.cpu.total_usage_percent << "%" << " Cores: "<< m.cpu.cores <<  "\n";
    std::cout << "MEM: " << m.memory.used_mb << "/" << m.memory.total_md << " MB\n";
    std::cout << "DISK: " << m.disk.used_gb << "/" << m.disk.total_gd << " GB\n";
}