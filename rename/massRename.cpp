#include <vector> 
#include <iostream> 
#include <cstdio>
#include <cstring>
#include <sstream>
#include <filesystem>

/**
    Function to check the amount of parameters given to the file.
    @param t_amountOfParams the amount of params given to the file.
*/
void isParamsAmountValid(int t_amountOfArgs);

/**
    Function to check that the amount of strings in two vectors are the same.
    @param t_vector1 The first vector you want to compare.
    @param t_vector2 The second vector you want to compare.
*/
void areVectorSizesValid(std::vector<std::string> t_vector1, std::vector<std::string> t_vector2);

/**
    Function to get the extension of a file.
    @param t_filename The filename that you want to get the extension of.
    @return string The extension of the file.
*/
std::string getFileExtension(std::string t_filename);

/**
    Function to convert from std::vector<>::const_iterator to const char*.
    @param t_iterator The iterator that you want to convert.
    @return conversion The converted const char*.
*/
const char* convertIterator(std::vector<std::string>::const_iterator t_iterator);

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

/**
    Function to rename files given in an input vector and a desired name to repeat.
    @param t_input A vector of files that you wish to rename.
    @param t_newName A string that you want to give the files to.
    @param t_startNumber An integer you wish the start the numbers at.
*/
void renameFilesNumbered(std::vector<std::string> t_input, std::string t_newName, int t_startNumber);

int main(int argc, char* argv[])
{
    // Check that the right amount of params are being passed to the file.
    isParamsAmountValid(argc);

    if (strcmp(argv[1],"-n") == 0)
    {
        // If you type in the -n option, use the "numbered" function.
        std::vector<std::string> inputs = splitString(argv[2]);
        std::string newName = argv[3];
        // The atoi() function just gets the raw value from the char* type.
        int startNumber = atoi(argv[4]);

        renameFilesNumbered(inputs, newName, startNumber);
    }
    else 
    {
        // This is the default option, the "name specific" function.
        std::vector<std::string> inputs = splitString(argv[1]); 
        std::vector<std::string> outputs = splitString(argv[2]); 
        areVectorSizesValid(inputs, outputs);

        renameFiles(inputs, outputs);
    }
    return 0;
}

void isParamsAmountValid(int t_amountOfArgs)
{
    if (t_amountOfArgs <= 2)
    {
        std::printf("Usage: ./rename [-e] [file1,file2,...] [file3,file4,...] .\n");
        exit(1); 
    }
}

void areVectorSizesValid(std::vector<std::string> t_vector1, std::vector<std::string> t_vector2)
{
    if (t_vector1.size() != t_vector2.size())
    {
        std::printf("Please make sure the two lists are the same length.\n");
        exit(2);
    }
}

std::string getFileExtension(std::string t_filename)
{
    // Get the index of where the last period is, where the extension starts.
    int position = t_filename.find_last_of(".");
    // Get the substring one of the index one after the final period.
    std::string extension = t_filename.substr(position+1);
    return extension;
}

const char* convertIterator(std::vector<std::string>::const_iterator t_iterator)
{
    const char* CONVERSION = t_iterator->c_str();
    return CONVERSION;
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
    // Create an iterator for the t_input vector and t_output vector.
    std::vector<std::string>::const_iterator inputIterator, outputIterator;

    // For loop to go through t_input and t_output and rename the files.
    for (auto [inputIterator, outputIterator] = std::tuple{t_input.begin(), t_output.begin()};
    inputIterator != t_input.end() && outputIterator != t_output.end();
    ++inputIterator, ++outputIterator) 
    {
        const char* INPUTITERATORCHAR = convertIterator(inputIterator);
        const char* OUTPUTITERATORCHAR = convertIterator(outputIterator);
        try
        {
            if (std::filesystem::exists(OUTPUTITERATORCHAR) ||
                !std::filesystem::exists(INPUTITERATORCHAR) ||
                strcmp(INPUTITERATORCHAR,OUTPUTITERATORCHAR) == 0)
            {
                // If the new file name exists, the existing name doesn't exist
                // or if the file is being renamed to the same name
                // throw an exception.
                throw std::exception();
            }
            std::rename(INPUTITERATORCHAR, OUTPUTITERATORCHAR);
            std::printf("%s -> %s\n", INPUTITERATORCHAR, OUTPUTITERATORCHAR);  
        }
        catch (std::exception& e)
        {
            std::printf("There was an error renaming %s to %s\n", INPUTITERATORCHAR, OUTPUTITERATORCHAR);
        }
    }
}

void renameFilesNumbered(std::vector<std::string> t_input, std::string t_newName, int t_startNumber)
{
    std::string startNumberString, newFile, extension;

    // Loop through the files given in t_input.
    for (std::string file : t_input)
    {
        // Get the extension of the file given in in the loop.
        extension = getFileExtension(file);

        // Convert the number to a string.
        startNumberString = std::to_string(t_startNumber);
        
        // Create the new file name.
        newFile = t_newName + startNumberString + "." + extension;
        t_startNumber++;
        
        const char* FILECHAR = file.c_str();
        const char* NEWFILECHAR = newFile.c_str(); 
        try 
        {
            if (std::filesystem::exists(NEWFILECHAR) ||
                !std::filesystem::exists(FILECHAR))
            {
                // If the new file name exists, or the existing name
                // doesn't exist, throw an exception.
                throw std::exception();
            }
            std::rename(FILECHAR, NEWFILECHAR);
            std::printf("%s -> %s\n", FILECHAR, NEWFILECHAR);  
        }
        catch (std::exception& e)
        {
            std::printf("There was an error renaming %s to %s\n", FILECHAR, NEWFILECHAR);
        }
    }
}
