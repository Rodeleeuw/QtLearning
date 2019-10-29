#pragma once
#include "customdatatypes.hpp"

/* Class that reads the excel file.
It is used to retrieve the vacancies and
the total count */
class ExcelReader
{
private:
    unsigned int m_NumVacancies;
    std::vector<vacancy> m_vacancies;
    // work book
    xlnt::workbook m_wb;
    // work sheet
    xlnt::worksheet m_ws;


public:
    explicit ExcelReader(std::string filename);
    void PrintRawSheet();
    void FillVacancies();
    void PrintVacancies();
    // unsigned int GetNumVacancies();

};

// Usage:
// ExcelReader reader("../request_digest.xlsx");
// reader.FillVacancies();
// reader.PrintVacancies();
