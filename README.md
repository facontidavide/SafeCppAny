# std::any with small object optimization and safe numerical conversion

The purpose of this tiny header-only library is to provide a type called SafeVariantNumber which can hold any integral or floating point number.
Additionally, it provides a safe way to convert a value between the original type and a different one.

It is a relatively simple extension of this library [thelink2012/any](https://github.com/thelink2012/any).

In short:

* When _extracting_ a value, it is compile-time type-safe. 
* When _converting_ to a different type, it prevents unexpected data loss, particularly when performing narrowing or signedness conversions of numeric data types. 
* It doesn't use pointers and heap memory. Therefore an array/vector of SafeVariantNumber(s) will be cache-friendly.
* It is as fast as limit checking and metaprogramming allow to be.

## Implementation 
SafeVariantNumber is strongly inspired by [Boost::Variant](http://www.boost.org/doc/libs/1_59_0/doc/html/variant.html). The implementation of the visitors, on the other hand, is based on [Poco::DynamicAny](http://pocoproject.org/docs-1.4.6/Poco.DynamicAny.html).
Both these libraries are much more flexible than SafeVariantNumber, is __way__ faster, maintaining the same level of type safety. 
The main drawback of Poco::DynamicAny is that it requires heap allocation, something that is slow and not very cache-friendly.
Boost::variant doesn't have this problem, but it uses more memory because of the ["Never-Empty Guarantee"](http://www.boost.org/doc/libs/1_59_0/doc/html/variant/design.html#variant.design.never-empty).

## Todo
Lot of stuff... in particular a proper benchmark of SafeVariantNumber vs Poco::DynamicAny.


