#pragma once

#include <string>
#include <ostream>
#include <sstream>
#include <stdexcept>
#include <boost/preprocessor.hpp>

namespace enum_helpers
{
    
// Exception type throw by to_enum function
using EnumLookupException = std::invalid_argument;

// Convenience function for converting an IDCGlobalDefines enum into string
template <typename T>
inline std::string to_string(T value)
{
    std::ostringstream ss;
    ss << value;
    return ss.str();
}

// Convenience function for convering an IDCGlobalDefines enum into equivalent integer value
template<typename T>
constexpr auto to_integral(T value) -> typename std::underlying_type<T>::type 
{
   return static_cast<typename std::underlying_type<T>::type>(value);
}

#define ENUM_STREAM_OPERATOR(ENUMTYPE, ...)                                    \
inline std::ostream& operator<<(std::ostream& os, ENUMTYPE value)              \
{                                                                              \
    switch(value)                                                              \
    {                                                                          \
        BOOST_PP_SEQ_FOR_EACH(CASE_ENUM_TO_STRING, ENUMTYPE,                   \
            BOOST_PP_VARIADIC_TO_SEQ(__VA_ARGS__))                             \
        default:                                                               \
            throw EnumLookupException("Invalid IDCGlobalDefines:: enum value: " + to_string(to_integral(value))); \
    }                                                                          \
    return os;                                                                 \
};

#define CASE_ENUM_TO_STRING(r, type, name)                                     \
    case type::name: os << BOOST_PP_STRINGIZE(name); break;

#define TO_ENUM_FUNCTION(ENUMTYPE, ...)                                        \
ENUM_FUNC_DEFINITION()                                                         \
template<> inline ENUMTYPE to_enum<ENUMTYPE>(const std::string& value)         \
{                                                                              \
    BOOST_PP_SEQ_FOR_EACH(RETURN_IF_MATCHES_ENUM, ENUMTYPE,                    \
        BOOST_PP_VARIADIC_TO_SEQ(__VA_ARGS__))                                 \
    throw EnumLookupException("Invalid conversion from '" + value + "' to IDCGlobalDefines::"); \
};

#define ENUM_FUNC_DEFINITION(_)                                                \
template <typename T>                                                          \
T to_enum(const std::string& value);

// Convenience macros for consistent enum <-> string conversions
#define RETURN_IF_MATCHES_ENUM(r, type, name)                                  \
    if (value == BOOST_PP_STRINGIZE(name))       return type::name;            \
    if (value == BOOST_PP_STRINGIZE(type::name)) return type::name;

#define GENERATE_ENUM_HELPERS(ENUMTYPE, ...)                                   \
    ENUM_STREAM_OPERATOR(ENUMTYPE, __VA_ARGS__)                                \
    TO_ENUM_FUNCTION(ENUMTYPE, __VA_ARGS__) 

} // namespace enum_helpers
