#include <benchmark/benchmark.h>

#include "VariantNumber/variant.h"
#include <Poco/Dynamic/Var.h>

#include <string>
#include <utility>


#define MAX 1000

using namespace VariantNumber;

//-----------------------------------------------

static void BM_VariantAssign(benchmark::State& state)
{
    VarNumber a[MAX];

    while (state.KeepRunning())
    {
        for(int i=0; i<MAX; i++)
        {
             a[i] = (int32_t)42 ;
        }
    }
}


//-----------------------------------------------

static void BM_VariantExtract(benchmark::State& state)
{
    VarNumber a[MAX];
    int32_t total = 0;

    if (state.thread_index == 0) {
        for(int i=0; i<MAX; i++) a[i] = int32_t(42);
    }

    while (state.KeepRunning())
    {
        total = 0;
        for(int i=0; i<MAX; i++)
        {
            benchmark::DoNotOptimize( total += a[i].extract<int32_t>( ) );
        }
    }
}

static void BM_VariantConvert(benchmark::State& state)
{
    VarNumber a[MAX];

    if (state.thread_index == 0) {
        for(int i=0; i<MAX; i++) a[i] = int32_t(42);
    }

    int64_t total = 0;

    while (state.KeepRunning())
    {
        total = 0;
        for(int i=0; i<MAX; i++)
        {
            benchmark::DoNotOptimize( total += a[i].convert<uint8_t>(  ) );
        }
    }
}


//-----------------------------------------------

static void BM_DynamicAssign(benchmark::State& state)
{
    Poco::Dynamic::Var  a[ MAX];

    int64_t total = 0;

    while (state.KeepRunning())
    {
        for(int i=0; i<MAX; i++)
        {
            a[i] = int32_t(42);
        }
    }
}


static void BM_DynamicExtract(benchmark::State& state)
{
    Poco::Dynamic::Var  a[ MAX];

    if (state.thread_index == 0) {
        for(int i=0; i<MAX; i++) a[i] = int32_t(42);
    }

    int64_t total = 0;

    while (state.KeepRunning())
    {
        total = 0;
        for(int i=0; i<MAX; i++)
        {
            benchmark::DoNotOptimize( total +=  a[i].extract<int32_t>( ) );
        }
    }
}

static void BM_DynamicConvert(benchmark::State& state)
{
    Poco::Dynamic::Var  a[ MAX];

    if (state.thread_index == 0) {
        for(int i=0; i<MAX; i++) a[i] = int32_t(42);
    }

    int64_t total = 0;

    while (state.KeepRunning())
    {
        total = 0;
        for(int i=0; i<MAX; i++)
        {
            benchmark::DoNotOptimize( total += a[i].convert<uint8_t>( ) );
        }
    }
}

//-----------------------------------------------

BENCHMARK(BM_DynamicAssign);
BENCHMARK(BM_VariantAssign);

BENCHMARK(BM_DynamicExtract);
BENCHMARK(BM_VariantExtract);

BENCHMARK(BM_DynamicConvert);
BENCHMARK(BM_VariantConvert);



BENCHMARK_MAIN();

