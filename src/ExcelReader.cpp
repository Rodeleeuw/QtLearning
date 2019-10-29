#include "ExcelReader.hpp"


/* Constructor:
* Open the file and get the data of the active
* sheet.
 */
ExcelReader::ExcelReader(std::string filename)
{
    // Load file into wb
    m_wb.load(filename);
    // return active worksheet
    m_ws = m_wb.active_sheet();
}


/* Just print the raw data for
debuging purposes */
void ExcelReader::PrintRawSheet()
{
    for (auto row : m_ws.rows(false))
    {
        for (auto cell : row)
        {
            std::clog << cell.to_string() << std::endl;
        }
    }
}

/* Fill the vector of opportunities */
void ExcelReader::FillVacancies()
{
    // Temporal object to read the sheet
    vacancy temp;

    // row contains the columns of the sheet
    // fill the data
    for( auto row : m_ws.rows( false ) )
    {
        temp.name = row[0].to_string();
        temp.description = row[1].to_string();
        //TODO: correct the date!!
        temp.date = row[2].to_string();
        temp.owner = row[3].to_string();
        temp.company = row[4].to_string();

        // Append the data
        m_vacancies.emplace_back(temp);
    }
}

/* Print the vector with vacancies */
void ExcelReader::PrintVacancies()
{
    for( auto vacancy : m_vacancies)
    {
        std::cout << "\n\n================================" << std::endl;
        std::cout << "Name: " << vacancy.name << std::endl;
        std::cout << "Company : " << vacancy.company << std::endl;
        std::cout << "Owner : " << vacancy.owner << std::endl;
        std::cout << "Creation date : " << vacancy.date << std::endl;
        std::cout << "Description : " << vacancy.description << std::endl;
    }
}

/* Return the vacancies obtained from the reading */
std::vector<vacancy> ExcelReader::GetVacancies()
{
    return m_vacancies;
}
