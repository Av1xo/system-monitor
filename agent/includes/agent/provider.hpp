#pragma once
#include "metrics.hpp"

class MetricsProvider
{
public:
    virtual ~MetricsProvider() = default;
    virtual MetricsSnapshot collect() = 0;
};