#include <stdio.h>   // for printf
#include <iostream>  // for cout cin etc.
#include <string>	   // for std::string
#include <vector>    // for std::vector< >
#include <fstream>   // for aggregate error [compiler] on ifstream declaration
#include <string.h>  // for memcpy and other block move operations
#include <time.h>

// [00 to 31] [Not Printable]
// [32 to 126] [Printable]
// [127]		 [ DELETE ]
// [128..254]  [ Odd Printable]
// [255]		 [ NBSP ]

// #define DEBUG 1

// Should morph this into a vigenere class or something...

void remove_last_newline( std::string &alphabet)
{
	if( alphabet.c_str()[alphabet.size()-1] == '\n') {
			alphabet.erase(alphabet.size()-1, 1);
	}
	return;
}

void suppress_character( std::string &alphabet, char c)
{
	for( int i = 0; i < alphabet.size(); ++i) {
		if( alphabet.c_str()[i] == c) {
			alphabet.erase(i,1);
		}
	}
	return;
}

// O(n^2) loop to find if duplicate exists - no l33t optimizations used
// return j position where first duplicate found
// otherwise return 0
int verify_alphabet( std::string &alphabet)
{
	for( int i = 0; i < alphabet.size(); ++i) {
		for( int j = i+1; j < alphabet.size(); ++j) {
			if( alphabet.c_str()[i] == alphabet.c_str()[j]) {
				return( j);
			}
		}
	}
	return( alphabet.size());
}

// Just display a row of numbers above the alphabet, like on exams
void print_alphabet( std::string &alphabet)
{
	if( alphabet.size() >= 100) {
		for( int i = 0; i < alphabet.size(); ++i) {
			printf( "%c", ((i%10 == 0) ? (char) ((i/100)%10)+0x30 : ' '));
		}
		printf("\n");
	}
	if( alphabet.size() >= 10) {
		for( int i = 0; i < alphabet.size();++i) {
			printf( "%c", ((i%10 == 0) ? (char) ((i/10)%10)+0x30 : ' '));
		}
		printf("\n");
	}
	for( int i = 0; i < alphabet.size();++i) {
		printf( "%c", (char) (i%10)+0x30 );
	}
	printf("\n");

	printf( "%s", alphabet.c_str());
	printf("\n");
}

// Anyways, open up some file filename and read from it
// Make sure you are in BINARY mode
void read_file( std::string &text, const char *filename)
{
	unsigned char *memblock;	 // Standard pointer for file io block of memory read
	std::ifstream input_file;	// Input Stream see C++ Reference for more info
	std::streampos size;		  // This will be used to get the size of the file in bytes

	input_file.open( filename, std::ios::in | std::ios::binary | std::ios::ate ); // Mode input, read as a binary file, the output position starts at end of file
	if (input_file.is_open()) {
		size = input_file.tellg();						// Returns current position of current character input stream (this would be current size of file, cool huh?)
		std::cout << "FILESIZE: " << size << std::endl;
		memblock = new unsigned char [1+ (unsigned long int) size];		// Not sure I need the extra +1 but FEOF may require it
		input_file.seekg (0, std::ios::beg);		  // Now move to beginning of file
		input_file.read ((char *) memblock, size);  // and start reading
		input_file.close();								 // reading all done, close file

		text.clear();
		text.assign( (char *) memblock);
		delete[] memblock;																		// Don't want a memory leak, it would be a large one
	} else {
		std::cout << "Unable to open  input file" << filename << std::endl;
	}
	return;
}

// Same, output buffer text to the file note ios::trunc means overwrite file
// Also, be sure it is in BINARY mode for write
void write_file( std::string &text, const char *filename)
{
	std::ofstream output_file;

	output_file.open( filename, std::ios::out | std::ios::trunc | std::ios::binary);  // Mode output, overwrite contents, write binary not text data
	if ( output_file.is_open()) {
		output_file.write( text.c_str(), text.size());
		output_file.close();
	} else {
		std::cout << "Unable to open output file" << filename << std::endl;
	}
	return;
}
	
// #define DEBUG 1
// parse ASCII block plaintext into alphabet position numbers, do same for key and then add
// together for new result.
// BE WARY -  -5 mod 23 will not result in correct cyrptographic result of 18 so you'll need to compensate
// that is why +alphabet_size during decryption phase
// if ignore_nonalphabet is true than it will skip but NOT increment key index
// if false than it will just pass it through as plaintext value if it is not in alphabet
void encrypt( std::string &cyphertext, std::string &plaintext, std::string &key, std::string &alphabet, bool ignore_nonalphabet)
{
	cyphertext.clear();
	size_t index = 0;
	for( int i = 0; i < plaintext.size(); ++i) {
		size_t position = alphabet.find( plaintext.c_str()[i]);
		size_t keynum = alphabet.find( key.c_str()[index%key.size()]);
		if( position != std::string::npos) {
#ifdef DEBUG
			printf("plain in alphabet: %lu (%c), key index: %lu (%c), P: %c (%d), C: %c (%lu)\n", position, alphabet[position], keynum, alphabet[keynum], plaintext.c_str()[i], i, alphabet.c_str()[(position+keynum) % alphabet.size()], (position+keynum) % alphabet.size() );
#endif
			cyphertext.push_back( alphabet.c_str()[(position+keynum) % alphabet.size()]);
			++index;
		} else { 
#ifdef DEBUG
			printf("plain in alphabet: ---, key index: %lu (%c), P: %c (%d), C: %c (%lu):    ", keynum, alphabet[keynum], plaintext.c_str()[i], i, alphabet.c_str()[(position+keynum) % alphabet.size()], (position+keynum) % alphabet.size() );
#endif
			if( !ignore_nonalphabet) {
				cyphertext.push_back( plaintext.c_str()[i]);
#ifdef DEBUG
				std::cout << "Ignored Character: " << plaintext.c_str()[i] << " (" << i << ")" << std::endl;
#else
				;
#endif
			} else {
#ifdef DEBUG
				std::cout << "Passed  Character: " << plaintext.c_str()[i] << " (" << i << ")" << std::endl;
#endif
			}
		}
	}
}

// parse ASCII block plaintext into alphabet position numbers, do same for key and then add
// together for new result.  This result is an index which can be used to retrieve new character
// BE WARY -  -5 mod 23 will not result in correct cyrptographic result of 18 so you'll need to compensate
// that is why +alphabet_size during decryption phase
// if ignore_nonalphabet is true than it will skip but NOT increment key index
// if false than it will just pass it through as plaintext value if it is not in alphabet
// this is for if you are decrypting a cypher with a wider alphabet YMMV
void decrypt( std::string &decrypttext, std::string &cyphertext, std::string &key, std::string &alphabet, bool ignore_nonalphabet)
{
	decrypttext.clear();
	size_t index = 0;
	for( int i = 0; i < cyphertext.size(); ++i) {
		size_t position = alphabet.find( cyphertext.c_str()[i]);
		size_t keynum = alphabet.find( key.c_str()[index%key.size()]);
		if( position != std::string::npos) {
#ifdef DEBUG
			printf("cypher in alphabet: %lu (%c), key index: %lu, (%c), C: %c (%d), R: %c (%lu)\n", position, alphabet[position], keynum, alphabet[keynum], cyphertext.c_str()[i], i, alphabet.c_str()[(position-keynum+alphabet.size()) % alphabet.size()], (position-keynum+alphabet.size()) % alphabet.size());
#endif
			decrypttext.push_back( alphabet.c_str()[(position-keynum+alphabet.size()) % alphabet.size()]);
			++index;
		} else {
#ifdef DEBUG
			printf("cypher in alphabet: ---, key index: %lu (%c), C: %c (%d), R: %c (%lu):    ", keynum, alphabet[keynum], cyphertext.c_str()[i], i, alphabet.c_str()[(position-keynum+alphabet.size()) % alphabet.size()], (position-keynum+alphabet.size()) % alphabet.size());
#endif
			if( !ignore_nonalphabet) {
				decrypttext.push_back( cyphertext.c_str()[i]);
#ifdef DEBUG
				std::cout << "Passed  Character: " << cyphertext.c_str()[i] << " (" << i << ")" << std::endl;
#endif
			} else {
#ifdef DEBUG
				std::cout << "Ignored Character: " << cyphertext.c_str()[i] << " (" << i << ")" << std::endl;
#else
				;
#endif
			}
		}
	}
}
// #undef DEBUG

int main(int argc, char **argv)
{
//	printf("^ = %c: %u (0x%x)\n", '^', (unsigned int) '^', (unsigned int) '^');
// Make sure I am seeing the value 0x0A for newline \n
//	printf("\\n = %c: %u (0x%x)\n", '\n', (unsigned int) '\n', (unsigned int) '\n');
//                                     1         2         3         4         5          6         7           8
//                           012345678901234567890123456789012345678901234567890123456789012345678901234567890
//	std::string alphabet = { "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789 :;,.[]<>{}'\"+-=&/\\\n"};

	std::string plaintext;		// original plaintext buffer
	std::string cyphertext;		// cyphertext transmit result buffer
	std::string decrypttext;	// recovered plaintext buffer
	std::string key;				// vignere sequence buffer
	std::string alphabet;

	bool binary_mode = false;						// for use later
	bool ef_dt_operation = false;					// ef = Encrypt if False    dt = Decrypte if True
	bool ignore_encrypt_nonalphabet = true;	// if true than skip over plaintext values
	bool ignore_decrypt_nonalphabet = true;	// otherwise, if false just copy paste plaintext values:  same for cypher

	time_t t0;					// Your standard random number seed source
	srand(time( &t0));		// Seed with time result t0, for better results not to use seconds but useconds

// expect five arguments, didn't feel like writing exhaustive all permutation handler
// diplay usage instructions and exit otherwise
	if( argc != 6) {
		printf("Usage: %s <output_file> <input_file> <alphabet_file> <key> { \"e\", \"d\", \"ei\" \"di\" }\n", argv[0]);
		printf("	  e  = encrypt with passthrough of unrecoginzed characters.\n");
		printf("	  d  = decrypt with passthrough of unrecognized characters.\n");
		printf("	  ei = encrypt, ignoring unrecognized characters.\n");
		printf("	  di = decrypt, ignoring unrecognized characters.\n");
		printf("To create a no newline file echo -n <text> > file.txt\n");
		return(1);
	}

// Case switch is better because ordering size will not be a problem then.
	if( strncmp( argv[5], "eb", 3) == 0) {   // Not used currently
		ef_dt_operation = false;
		binary_mode = true;
	} else if( strncmp( argv[5], "ei", 2) == 0) {
		ef_dt_operation = false;
		ignore_encrypt_nonalphabet = true;
	} else if( strncmp( argv[5], "di", 2) == 0) {
		ef_dt_operation = true;
		ignore_decrypt_nonalphabet = true;
	} else if( strncmp( argv[5], "e", 1) == 0) {
		ef_dt_operation = false;
		ignore_encrypt_nonalphabet = false;
	} else if( strncmp( argv[5], "d", 1) == 0) {
		ef_dt_operation = true;
		ignore_decrypt_nonalphabet = false;
	} else {
		printf("Unrecognized argument %s, not one of { \"e\", \"d\", \"ei\" or \"di\" }\n", argv[5]);
		return(1);
	}

	read_file( alphabet, argv[3]);
	suppress_character( alphabet, '\n');
// search for duplicates in our alphabet
	int test = verify_alphabet(alphabet);
	if ( test < alphabet.size()) {
		std::cout << "ERROR!  ALPHABET contains duplicate: " << alphabet.c_str()[test] << "(" << test << ")" << std::endl;
		exit(-1);
	}

	key.assign( argv[4]);

	print_alphabet( alphabet);
	std::cout << "SIZE: " << alphabet.size() << std::endl;
	if( ef_dt_operation) {
		std::cout << "KEY : " << key << " ---- ";
		read_file( cyphertext, argv[2]);
		std::cout << "INPUT CYPHER  TEXT: " << std::endl;
		std::cout << cyphertext << std::endl;
		std::cout << "\n";


		decrypt( decrypttext, cyphertext, key, alphabet, ignore_decrypt_nonalphabet);
		write_file( decrypttext, argv[1]);

		std::cout << "RECOVERED     TEXT: \n";
		std::cout << decrypttext << std::endl;
		std::cout << "\n";
	} else {
		std::cout << "KEY : " << key << " ---- ";
		read_file( plaintext, argv[2]);
		std::cout << "INPUT  PLAIN  TEXT" << "(" << plaintext.size() << "): ";
		std::cout << plaintext << std::endl;
		std::cout << "\n";

		encrypt( cyphertext, plaintext, key, alphabet, ignore_encrypt_nonalphabet);
		write_file( cyphertext, argv[1]);

		std::cout << "OUTPUT CYPHER TEXT: \n";
		std::cout << cyphertext << std::endl;
		std::cout << "\n";
	}

	return(0);
}

