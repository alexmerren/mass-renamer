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
    Function to check that the amount of strings in two vectors are the same.
    @param t_vector1 The first vector you want to compare.
    @param t_vector2 The second vector you want to compare.
*/
void checkVectorSizes(std::vector<std::string> t_vector1, std::vector<std::string> t_vector2);

/**
    Function to split a given string into a vector of strings.
    @param t_filesString A string of files delimited by a comma.
    @return filesArr A vector of the files in the string. 
*/
std::vector<std::string> splitString(std::string t_filesString); 

/**
    Function to convert from std::vector<>::const_iterator to const char*.
    @param t_iterator The iterator that you want to convert.
    @return conversion The converted const char*.
*/
const char* convertIterator(std::vector<std::string>::const_iterator t_iterator);

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

    // Check that the vectors have the same amount of files in them.
    checkVectorSizes(inputs, outputs);

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

void checkVectorSizes(std::vector<std::string> t_vector1, std::vector<std::string> t_vector2)
{
    if (t_vector1.size() != t_vector2.size())
    {
        std::printf("Please make sure the two lists are the same length.\n");
        exit(2);
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

const char* convertIterator(std::vector<std::string>::const_iterator t_iterator)
{
    const char* conversion = t_iterator->c_str();
    return conversion;
}

void renameFiles(std::vector<std::string> t_input, std::vector<std::string> t_output)
{
    // Create an iterator for the t_input vector and t_output vector.
    std::vector<std::string>::const_iterator inputIterator, outputIterator;

    // For loop to go through t_input and t_output and rename the files.
    for (auto [inputIterator, outputIterator] = std::tuple{t_input.begin(), t_output.begin()};
    inputIterator != t_input.end() && outputIterator != t_output.end();
    ++inputIterator, ++outputIterator) 
    {
        const char* inputIteratorChar = convertIterator(inputIterator);
        const char* outputIteratorChar = convertIterator(outputIterator);

        try
        {
            if (std::filesystem::exists(outputIteratorChar) ||
                strcmp(inputIteratorChar,outputIteratorChar) == 0)
            {
                throw std::exception();
            }
            std::rename(inputIteratorChar, outputIteratorChar);
            std::printf("%s -> %s\n", inputIteratorChar, outputIteratorChar);  
        }
        catch (std::exception& e)
        {
            std::printf("There was an error renaming %s to %s\n", inputIteratorChar, outputIteratorChar);
        }
    }
}
