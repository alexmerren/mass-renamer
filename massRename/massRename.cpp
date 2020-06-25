#include <iostream> 
#include <vector> 
#include <chrono> 
#include <cstdio>
#include <cstring>

/**
    Splits the input string into the individual files.
    @param filesString A string of files delimited by a comma. 
    @return A vector of all the file names.
*/
std::vector<std::string> listFiles(std::string filesString); 

/**
    Renames the files given by the listFiles function.
    @param inputs A vector of the existing file names in the directory. 
    @param outputs A vector of the wanted file names in the directory.
    @param print Boolean of whether to print diagnostics of the function.
    @return void
*/
void renameFiles(std::vector<std::string> inputs, std::vector<std::string> outputs, bool print);

int main(int argc, char* argv[])
{
    int start = 1;
    bool verbose = false;
    
    if ( argc == 1 )
    {
        std::printf("Please enter a file name.\n");
        return 1;
    }

    if ( (strcmp(argv[1],"-v")) == 0 ) 
    {
        start = 2;
        verbose = true;
    }
    
    std::vector<std::string> inputs = listFiles(argv[start]); 
    std::vector<std::string> outputs = listFiles(argv[start+1]); 
    renameFiles(inputs, outputs, verbose);
    return 0;
}

std::vector<std::string> listFiles(std::string filesString) 
{
	// This is the array of all the files we are returning.
	std::vector<std::string> filesArr; 
	std::string file,delimiter; 
	delimiter = ","; 
	int pos = 0;

	// This makes the integer pos into the location of where the first delimiter is
	// from the start.  It continues to do this until it hits the end of the string.
	// std::string::npos is a fancy way of doing that.
	while ( ( pos = filesString.find( delimiter )) != std::string::npos ) 
	{
		// This string is the substring between commas, or a file that we want.	
		file = filesString.substr( 0,pos ); 
	
        // Add the current file to the filesArr vector.
		filesArr.push_back( file );
	
        // Remove the substring that we found and put into file, 
		// and the comma that is next to it.
		filesString.erase( 0, pos + delimiter.length() ); 
	}
	filesArr.push_back( filesString ); 
	return filesArr;
}

void renameFiles(std::vector<std::string> inputs, std::vector<std::string> outputs, bool print)
{
	try
	{
		// This starts the timing clock.
		auto start = std::chrono::high_resolution_clock::now(); 
		
        // Create const char* for conversion from string.
		const char* inputsBeginChar; 
		const char* outputsBeginChar;
		
        // Get the first element in the inputs and outputs vectors.
		auto inputsBegin = inputs.cbegin(); 
		auto outputsBegin = outputs.cbegin(); 
		
        // This for loop goes through the input and outputs vectors, and renames them.
		for (; inputsBegin != inputs.end() and outputsBegin != outputs.end(); inputsBegin++, outputsBegin++ ) 
		{
			// Convert std::string to const char*
			inputsBeginChar = inputsBegin->c_str(); 
		    outputsBeginChar = outputsBegin->c_str(); 
			
            if ( rename( inputsBeginChar, outputsBeginChar ) != 0 )
            {
				perror( "Error renaming file" );
			}
            else if ( print )
            {
				printf( "%s -> %s\n", inputsBeginChar, outputsBeginChar ); 
	    	}
        }
		// This ends the timing clock.
		auto finish = std::chrono::high_resolution_clock::now(); 
		std::chrono::duration<double> elapsed = finish - start; 
        
        if ( print ) 
        {
		    printf( "Renaming took %f seconds.\n", elapsed.count() ); 
        }
	} 
    catch (const std::exception& e) 
    {	
		printf("There was an error in the program.\n");
	}
}
