// some_tests.cpp
#include "catch2.hpp"
#include <QString>


// The folliwing are needed for catch2, otherwise it is not able to
// display the correct compared values.
inline std::ostream &operator<<(std::ostream &os, const QByteArray &value)
{
    return os << '"' << (value.isEmpty() ? "" : value.constData()) << '"';
}

inline std::ostream &operator<<(std::ostream &os, const QLatin1String &value)
{
    return os << '"' << value.latin1() << '"';
}

inline std::ostream &operator<<(std::ostream &os, const QString &value)
{
    return os << value.toLocal8Bit();
}




TEST_CASE("Some.Tests", "")
{
    SECTION("Something", "")
    {
        CHECK(QString() == QString());
        const QString someString(QLatin1String("foo"));
        CHECK(someString == QLatin1String("bar"));
    }
}
