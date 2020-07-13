#include <tuple>
#include <vector> 
#include <iostream> 
#include <cstdio>
#include <sstream>
#include <filesystem>
#include <stdlib.h>

/**
    Function to check the amount of parameters given to the file.
    @param t_amountOfParams the amount of params given to the file.
*/
void checkParams(int t_amountOfArgs);

/**
    Function to split a given string into a vector of strings.
    @param t_filesString A string of files delimited by a comma.
    @return filesArr A vector of the files in the string. 
*/
std::vector<std::string> splitString(std::string t_filesString); 

/**
    Function to rename files given in two vectors split by splitString.
    @param t_input A vector of the input file names.
    @param t_output A vector of the output file names.
*/
void renameFiles(std::vector<std::string> t_input, std::vector<std::string> t_output);

int main(int argc, char* argv[])
{
    // Check that the right amount of params are being passed to the file.
    checkParams(argc);

    // Get a vector of the input files and the output files.
    std::vector<std::string> inputs = splitString(argv[1]); 
    std::vector<std::string> outputs = splitString(argv[2]); 
   
    // Rename the input files to the output files.
    renameFiles(inputs, outputs);
    
    return 0;
}

void checkParams(int t_amountOfArgs)
{
    if (t_amountOfArgs == 1)
    {
        std::printf("Please enter a file name.\n");
        exit(1); 
    }
}

std::vector<std::string> splitString(std::string t_filesString) 
{
	std::vector<std::string> filesArr;
    std::string file;
    std::stringstream stringstream(t_filesString);

    // While loop to extract characters from 
    // stringstream to file until it finds a comma.
    while (getline(stringstream, file, ','))
    {
        filesArr.push_back(file);
    }
	return filesArr;
}


void renameFiles(std::vector<std::string> t_input, std::vector<std::string> t_output)
{
	try
    {
        // Create an iterator for the t_input vector and t_output vector.
        std::vector<std::string>::const_iterator inputIterator, outputIterator;

        // For loop to go through t_input and t_output and rename the files.
		for (auto [inputIterator, outputIterator] = std::tuple{t_input.begin(), t_output.begin()};
            inputIterator != t_input.end() && outputIterator != t_output.end();
            ++inputIterator, ++outputIterator) 
		{
            // Check if the output file name already exists, if so, skip it.
            if (std::filesystem::exists(outputIterator->c_str()))
            {   
                std::printf("Could not rename %1$s to %2$s, %2$s already exists\n",
                            inputIterator->c_str(), outputIterator->c_str());
                continue;
            }
            std::rename(inputIterator->c_str(), outputIterator->c_str());
            std::printf("%s -> %s\n", inputIterator->c_str(), outputIterator->c_str()); 
        }
    }
    catch (const std::exception& e) 
    {	
		std::printf("There was an error in the program.");
	}
}
