
#include <iostream>
#include <set>
#include <fstream>
#include <filesystem>

using namespace std;
namespace fs = std::filesystem;


const string pathToCatalog = "D:\\Doc";

set<fs::path> GetListOfFile(string pathToCatalog);
unsigned short GetFileCRC(fs::path pathToFile);

int main()
{
    setlocale(LC_ALL, "Russian");

    cout << "Taask 4" << endl;

    // Get the list of files from catalog
    set<fs::path> listOffile = GetListOfFile(pathToCatalog);
   
    if (!listOffile.empty())
    {
        cout << "Catalog consist files:" << endl;

        for (auto& filePath : listOffile)
        {
            // find the crc of file
            cout << filePath.u8string().substr(filePath.u8string().find_last_of("\\/") + 1) << " CRC is: " << GetFileCRC(filePath) << endl;
        }
    }
    else
    {
        cout << "Catalog is empty!" << endl;
    }  
}


/**
 * @brief Seach in catalog files and add in list full path to file
 *
 * @note List consist only valid file path. files sorted by name
 *
 * @param string pathToCatalog - path to catalog
 *
 * @retval list of file path
 */
set<fs::path> GetListOfFile(string pathToCatalog)
{
    set<fs::path> listOfFile;

    if (fs::is_directory(pathToCatalog))
    {
        for (const auto& entry : fs::directory_iterator(pathToCatalog))
        {
            try
            {
                if (entry.is_regular_file())
                {
                    // we found a file
                    // Add to list
                    listOfFile.insert(entry.path());
                }
            }
            catch (...)
            {
                cout << "Error read file: " << std::endl;
            }
        }
    }
    else
    {
        cout << "Unknow path: " << pathToCatalog << endl;
    }

    return listOfFile;
}

/**
 * @brief Calculate CRC for file use polinom (0x94ED)
 *
 * @note If file is not open ZERO will be return
 *
 * @param filesystem::path pathToFile - Full path to file
 *
 * @retval CRC value
 */
unsigned short GetFileCRC(fs::path pathToFile)
{
    /*
    * Init value is 0x0
    * polinom x 16 + x 15 + x 12 + x 10 + x 7 + x 6 + x 5 + x 3 + x 2 + 1
    *
    */
    unsigned short polinom = 0x94ED;
    unsigned short crc = 0x0;


    ifstream file(pathToFile); // окрываем файл для чтения

    if ((file) && (file.is_open()))
    {
        unsigned char i;
        char rByte;
        
        while (file.get(rByte))
        {
            crc ^= rByte << 8;

            for (i = 0; i < 8; i++)
            {
                /*
                *  Compare the MSB with "1"
                *  true - applay polinom
                *  false - shift to left 
                * 
                */
                crc = crc & 0x8000 ? (crc << 1) ^ polinom : crc << 1;
            }
        }
    }
    else
    {
        cout << "Error open file: " << pathToFile << endl;
    }

    file.close();

    return crc;
}
