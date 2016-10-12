#include <benchmark/benchmark.h>

#include "VariantNumber/variant.h"
#include <Poco/DynamicAny.h>

#include <string>
#include <utility>


#define MAX 1000

using namespace VariantNumber;

//-----------------------------------------------

static void BM_VariantAssign(benchmark::State& state)
{
    VarNumber a;

    while (state.KeepRunning())
    {
        for(int i=0; i<MAX; i++)
        {
            benchmark::DoNotOptimize(  a = (int32_t)42 );
        }
    }
}


static void BM_VariantExtract(benchmark::State& state)
{
    VarNumber a = (int32_t)42;
    int64_t total = 0;

    while (state.KeepRunning())
    {
        for(int i=0; i<MAX; i++)
        {
            benchmark::DoNotOptimize( total += a.extract<int32_t>( ) );
        }
    }
}

static void BM_VariantConvert(benchmark::State& state)
{
    VarNumber a = (int32_t)42;
    int64_t total = 0;

    while (state.KeepRunning())
    {
        for(int i=0; i<MAX; i++)
        {
            benchmark::DoNotOptimize( total += a.convert<uint8_t>(  ) );
        }
    }
}


//-----------------------------------------------

static void BM_DynamicAssign(benchmark::State& state)
{
    Poco::DynamicAny  a;

    while (state.KeepRunning())
    {
        for(int i=0; i<MAX; i++)
        {
             benchmark::DoNotOptimize( a = int32_t(42) );
        }
    }
}


static void BM_DynamicExtract(benchmark::State& state)
{
    Poco::DynamicAny a = int32_t(42);
    int64_t total = 0;

    while (state.KeepRunning())
    {
        for(int i=0; i<MAX; i++)
        {
            benchmark::DoNotOptimize( total += a.extract<int32_t>( ) );
        }
    }
}

static void BM_DynamicConvert(benchmark::State& state)
{
    Poco::DynamicAny a = int32_t(42);
    int64_t total = 0;

    while (state.KeepRunning())
    {
        for(int i=0; i<MAX; i++)
        {
            benchmark::DoNotOptimize( total += a.convert<uint8_t>( ) );
        }
    }
}

//-----------------------------------------------

static void BM_baselineAssign(benchmark::State& state)
{
    int64_t a;

    while (state.KeepRunning())
    {
        for(int i=0; i<MAX; i++)
        {
            benchmark::DoNotOptimize(  a = (int32_t)42 );
        }
    }
}


static void BM_baselineExtract(benchmark::State& state)
{
    auto a = (int32_t)42;
    int64_t total = 0;

    while (state.KeepRunning())
    {
        for(int i=0; i<MAX; i++)
        {
            benchmark::DoNotOptimize( total += a );
        }
    }
}

static void BM_baselineConvert(benchmark::State& state)
{
    auto a = (int32_t)42;
     int64_t total = 0 ;

    benchmark::DoNotOptimize(total );

    while (state.KeepRunning())
    {
        for(int i=0; i<MAX; i++)
        {
            if( a < std::numeric_limits<uint8_t>::min() ||
                a > std::numeric_limits<uint8_t>::max() ||
                a != static_cast<int32_t>(static_cast<uint8_t>(a)) )
            {
                assert(true);
            }

            benchmark::DoNotOptimize( total += static_cast<uint8_t>( a ) );
        }
    }
}


//BENCHMARK(BM_DynamicAssign);
//BENCHMARK(BM_VariantAssign);
//BENCHMARK(BM_baselineAssign);

//BENCHMARK(BM_DynamicExtract);
//BENCHMARK(BM_VariantExtract);
//BENCHMARK(BM_baselineExtract);

BENCHMARK(BM_DynamicConvert);
BENCHMARK(BM_VariantConvert);
BENCHMARK(BM_baselineConvert);


BENCHMARK_MAIN();

