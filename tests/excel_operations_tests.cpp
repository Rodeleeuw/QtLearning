#include "catch2.hpp"
#include <xlnt/xlnt.hpp>
#include <vector>
#include <array>
#include "customdatatypes.hpp"

// // The folliwing are needed for catch2, otherwise it is not able to
// // display the correct compared values.
// inline std::ostream &operator<<(std::ostream &os, const QByteArray &value)
// {
//     return os << '"' << (value.isEmpty() ? "" : value.constData()) << '"';
// }

// inline std::ostream &operator<<(std::ostream &os, const QLatin1String &value)
// {
//     return os << '"' << value.latin1() << '"';
// }

// inline std::ostream &operator<<(std::ostream &os, const QString &value)
// {
//     return os << value.toLocal8Bit();
// }

// Alias to the custom datatype
// using sheet = std::vector<vacancy>;

// The number of columns of the digest sheet
static const unsigned short NUMBER_OF_COLUMNS = 5;

std::vector<vacancy> read_excel_sheet(std::string ExcelFileName)
{
    std::vector<vacancy> oportunities;
    xlnt::workbook RequestFile;

    // Open the request file
    RequestFile.load( ExcelFileName );
    // load the sheet into ws
    auto ws = RequestFile.active_sheet();

    // Fill the vector with the opportunities

    for( auto row : ws.rows( false ) )
    {
        for( auto cell : row )
        {
            std::cout << cell.to_string() << std::endl;
        }
    }

    return oportunities;
}

TEST_CASE( "Exel file operations", "[xlnt_lib]"
{


    SECTION("Read empty file", "")
    {
        // a pointer variable to hold the values, a vector of 5 columns
        std::vector<vacancy> request_sheet;

        request_sheet = read_excel_sheet();

        // The vector should be empty
        REQUIRE(requesti_sheet == "");
    }
}
