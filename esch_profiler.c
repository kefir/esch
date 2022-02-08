#include "esch_profiler.h"

static esch_profiler_t* cfg = NULL;

void esch_profiler_init(esch_profiler_t* config)
{
    cfg = NULL;
    if (config) {
        cfg = config;
    }
}

void esch_profiler_enable(bool enable)
{
    if (cfg) {
        if (cfg->timer_enable) {
            cfg->timer_enable(enable);
        }
    }
}

void esch_profiler_clear(void)
{
    if (cfg) {
        if (cfg->timer_clear) {
            cfg->timer_clear();
        }
    }
}

uint32_t esch_profiler_count_get(void)
{
    uint32_t ret = 0;
    if (cfg) {
        if (cfg->timer_count_get) {
            ret = cfg->timer_count_get();
        }
    }
    return ret;
}
