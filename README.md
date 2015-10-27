# SafeVariantNumber
The purpose of this tiny header-only library is to provide a type called SafeVariantNumber which can hold any integral or floating point number.
Additionally it provides a safe way to convert a value between the original type and a different one.

In short:

* When _extracting_ a value, it is compile-time type-safe. 
* When _converting_ to a different type, it prevents unexpected data loss, particularly when performing narrowing or signedness conversions of numeric data types. 
* It doesn't use pointers and heap memory. Therefore an array/vector of SafeVariantNumber(s) will be cache-friendly.
* It is a fast as limit checking and metaprogramming allows to be.

## Dependencies
SafeVariantNumber is based on __Boost::Variant__. No other dependencies are needed.

## Implementation 
SafeVariantNumber is nothing more than a [Boost::Variant](http://www.boost.org/doc/libs/1_59_0/doc/html/variant.html). The visitors are inspired by [Poco::DynamicAny](http://pocoproject.org/docs-1.4.6/Poco.DynamicAny.html).
I was an happy user of DynamicAny, that by the way is far more complete and flexible than SafeVariantNumber, but I didn like the fact that pointers are the cornerstone of the type erasure strategy.
In hard real-time applications you want to avoid heap memory allocation and page faults.

Preliminary results show that __SafeVariantNumber__ seems to be __4X-5X__ time faster than __Poco::DynamicAny__.

## Todo
Lot of stuff... in particular a proper benchmark of SafeVariantNumber vs Poco::DynamicAny.


