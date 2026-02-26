#include "agent/provider.hpp"
#include "agent/platform.hpp"
#include <ctime>

class DefaultMetricsProvider : public MetricsProvider
{
public:
    MetricsSnapshot collect() override 
    {
        MetricsSnapshot s{};
        s.timestamp = static_cast<uint64_t>(std::time(nullptr));
        s.cpu = platform::collect_cpu();
        s.memory = platform::collect_memory();
        s.disk = platform::collect_disk();
        return s;
    }
};

MetricsProvider* create_provider()
{
    static DefaultMetricsProvider instance;
    return &instance;
}