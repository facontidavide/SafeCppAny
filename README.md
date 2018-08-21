# std::any with small object optimization and safe numerical conversion

The purpose of this tiny header-only library is to provide a type called SafeAny::Any which can hold any 
type, just like std::any or boost::any.
But it has few importants features:

- It has small object optimization for objects smaller than two words (16 bytes on a 64bits platform), thanks to this 3rdparty implementation [thelink2012/any](https://github.com/thelink2012/any).

- it is less pedantic than usual when an arithmetic value (integer, floating point, enum, etc.) is casted into another one. The library will check for narrowing, signedness conversions and numerical cancellation. 

## Example

```c++
using SafeAny::Any;

{
  Any val( int(-1000) );

  int    int_val = val.cast<int>(); //OK
  double real_val = val.cast<double>(); //OK
  double long_val = val.cast<long>(); //OK

  int8_t small_val      = val.cast<uint8_t>(); // throws exception
  uint16_t unsigned_val = val.cast<uint16_t>(); // throws exception
}

{
  Any val( float(3.1) );

  float  f_val = val.cast<float>(); //OK
  double d_val = val.cast<double>(); //OK
  
  int i_val = val.cast<int>(); // throws exception. 
}
``` 

## Implementation 
SafeVariantNumber is strongly inspired by [Boost::Variant](http://www.boost.org/doc/libs/1_59_0/doc/html/variant.html). The implementation of the visitors, on the other hand, is based on [Poco::DynamicAny](http://pocoproject.org/docs-1.4.6/Poco.DynamicAny.html).
Both these libraries are much more flexible than SafeVariantNumber, is __way__ faster, maintaining the same level of type safety. 
The main drawback of Poco::DynamicAny is that it requires heap allocation, something that is slow and not very cache-friendly.
Boost::variant doesn't have this problem, but it uses more memory because of the ["Never-Empty Guarantee"](http://www.boost.org/doc/libs/1_59_0/doc/html/variant/design.html#variant.design.never-empty).




