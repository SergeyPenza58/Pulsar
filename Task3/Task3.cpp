

#include <iostream>
#include <thread>
#include <mutex>
#include <queue>
#include <fstream>
#include <filesystem>
#include <sstream> 
#include <map>
#include <set>

using namespace std;
namespace fs = std::filesystem;

const string pathToDir = "D:\\Doc";
mutex listOfFiles_access;			/*!< Mutext to control access in var @listOfFiles*/
mutex dicOfStr_cmmnCnt_access;		/*!< Mutext to control access in var @dicOfStr_cmmnCnt*/

queue<std::filesystem::path> listOfFiles;	/*!< Queue which will be contain the path to files*/
map<string, unsigned> dicOfStr_cmmnCnt;		/*!< Dictionary which will be contain common value the string and number of matches*/

void Task_findStrInFile(set<string> str_forSeach);

int main()
{
	vector<std::thread> threadFindStr;

	cout << "Task 3" << endl;

	// list of string which need find
	set<string> listOfStr_forSeach
	{
		{"pa"},
		{"12"},
		{"le"},
		{"54l"}
	};

	// Create common dictionary
	for (const auto& strforSeach : listOfStr_forSeach)
	{
		dicOfStr_cmmnCnt.insert(make_pair(strforSeach, 0));
	}


	// Get the list of file
	if (fs::is_directory(pathToDir))
	{
		for (auto& entry : fs::directory_iterator(pathToDir))
		{
			try
			{
				if (entry.is_regular_file())
				{
					listOfFiles.push(entry.path());
				}
			}
			catch (...)
			{
				cout << "Error read file: " << std::endl;
			}
		}

		if (listOfFiles.empty())
		{
			cout << "Directory is empty" << endl;
			return 0;
		}

	}
	else
	{
		cout << "Unknow path: " << pathToDir << endl;
		return 0;
	}

	// Get the the available number of cores 
	unsigned int numberOfThreads = thread::hardware_concurrency();

	if (numberOfThreads)
	{
		if (listOfFiles.size() < numberOfThreads)
		{
			// Limit count of threads
			numberOfThreads = listOfFiles.size();
		}

		cout << "Program create " << numberOfThreads << " threads" << endl;

		for (int i = 0; i < numberOfThreads; i++)
			threadFindStr.push_back(thread(Task_findStrInFile, listOfStr_forSeach));

		for (auto& myThread : threadFindStr)
			myThread.join();

		cout << endl << "Common list of found lines in files and their count" << endl;

		for (auto& [seachStr, cntStr] : dicOfStr_cmmnCnt)
		{
			cout << "string: " << seachStr << " Count: " << cntStr << endl;
		}
	}
	else
	{
		cout << "Can't create threads. Program will be stope" << endl;
	}
}

/**
 * @brief Task for seaching in file string and add value in common dictionary
 *
 *
 * @param set<string> str_forSeach - list of string  wich need find
 *
 * @retval none
 */
void Task_findStrInFile(set<string> str_forSeach)
{
	/*
	*  key - string for seach
	*  value - counter of string found in file
	* 
	*/
	map<string, unsigned> dicOfStr_Cnt;
	
	for (const auto& strforSeach : str_forSeach)
	{
		dicOfStr_Cnt.insert(make_pair(strforSeach, 0));
	}

	while (1)
	{
		// try to blck access to list of file

		if (listOfFiles_access.try_lock())
		{
			try
			{
				if (listOfFiles.empty())
				{
					// list of file name is empty
					// task need abort
					listOfFiles_access.unlock();
					return;
				}
								
				
				filesystem::path filePath = listOfFiles.front(); // get the file path

				ifstream file(filePath);

				listOfFiles.pop(); // delete current file path from common list

				listOfFiles_access.unlock(); // allow other thread work with list of file

				if ((file) && (file.is_open()))
				{
					// file was opened

					stringstream strStream;
					strStream << file.rdbuf(); //read the file
					string str = strStream.str(); //str holds the content of the file


					// test string need uncomment
					// 
					// str +="54lpa12ler54lapale1254lle1254lle1254lpa54l";
					

					int i = 0;					

					for (auto&& [seachStr, cntStr] : dicOfStr_Cnt)
					{
						i = 0;

						for (i = str.find(seachStr, i++); i != string::npos; i = str.find(seachStr, i + 1))
						{
							// increase the count str inf file
							cntStr++;
						}						
					}


					while (1)
					{
						// try to get access to common dictionary with string counters
						if (dicOfStr_cmmnCnt_access.try_lock())
						{
							try
							{
								cout << endl << "Task ID: " << this_thread::get_id() << endl;

								cout << "In file " << filePath.u8string() << "were found the strings:" << endl;

								for (auto&& [seachStr, cntStr] : dicOfStr_Cnt)
								{
									cout << "string: " << seachStr << " Count: " << cntStr << endl;

									dicOfStr_cmmnCnt[seachStr] += cntStr; // add value in common dictionary

									cntStr = 0; // reset value for th next file
								}
							}
							catch (...)
							{
								cout << "Error union data" << endl;
							}
							
							dicOfStr_cmmnCnt_access.unlock();
							break;
						}						
					}					
				}
			}
			catch (...)
			{
				cout << "thread Err" << endl;
			}
		
			
		}

		

	}

}