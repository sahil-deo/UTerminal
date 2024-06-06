#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>
#include <cstdio>
#include <vector>
#include <filesystem>
#include <curl/curl.h>
#include <random>
#include <string>
namespace fs = std::filesystem;

//std::cerr << "\033[31m" << " " << "\033[0m" << std::endl;

//Function prototypes for helper functions
void fetchData(std::string outputFilename, std::string url);

long long getFileSize(std::string file);


void line(int n)
{
	for (int i = 0; i < n; i++)
		std::cout << "---------------------------------------------------" << std::endl;
}

void read(int args, char* commands[])
{
	if (args < 2)
	{
		line(1);
		std::cerr << "\033[31m" << "Key not given" << "\033[0m" << std::endl;
		line(1);
		return;
	}

	std::string text;
	std::ifstream reader;
	reader.open(commands[2], std::ios::binary);

	if (!reader.is_open())
	{
		line(1);
		std::cerr << "\033[31m\"" << commands[2] << "\" " << "Unable to open file" << "\033[0m" << std::endl;
		line(1);
	}
	else
	{
		line(1);
		while (std::getline(reader, text))
		{
			std::cout << text << std::endl;
		}
		line(1);
		reader.close();
	}
}

void write(int args, char* commands[])
{

	std::string FileName;
	line(1);
	std::cout << "Enter File Name: ";
	std::cin >> FileName;
	line(1);
	std::cout << "Enter \"STOP\" to exit " << std::endl;
	line(1);
	std::string text;
	std::ofstream writer;

	writer.open(FileName + ".txt", std::ios::trunc);
	writer.close();
	writer.open(FileName + ".txt", std::ios::app);


	while (std::getline(std::cin, text))
	{
		if (text == "STOP") break;
		std::cout << ">";
		writer << text << std::endl;
	}

	line(1);
	writer.close();

}

void search(int args, char* commands[])
{

	if (args < 4)
	{
		line(1);
		std::cerr << "\033[31m" << "Invalid Syntax please used uterminal --help to learn the correct argument syntax" << "\033[0m" << std::endl;
		line(1);
		return;
	}

	std::string text, key = commands[3];
	std::ifstream reader;
	reader.open(commands[2]);
	int Line = 0, Char = 0, KeyChar = 0;
	bool flag = false;

	if (args == 5 && strcmp(commands[4], "-i") == 0) {
		for (int i = 0; i < key.length(); i++) {
			key[i] = tolower(key[i]);
			//std::cout << key[i] << std::endl;
		}

		//std::cout << key << std::endl;
	}
	else if (args == 5) {
		line(1);
		std::cerr << "\033[31m" << "Invalid Syntax please used uterminal --help for the correct argument syntax" << "\033[0m" << std::endl;
		line(1);
		for (int i = 0; i < args; i++) {
			std::cout << commands[i] << " ";
		}
		std::cout << std::endl;
		return;
	}


	if (!reader.is_open())
	{
		line(1);
		std::cerr << "\033[31m\"" << commands[2] << "\" " << "Unable to open file" << "\033[0m" << std::endl;
		line(1);
	}

	while (std::getline(reader, text))
	{
		Line++;
		Char = 0;
		for (char c : text)
		{
			Char++;

			if (args == 5) {
				if (key[KeyChar] == tolower(c))
				{
					KeyChar++;
					if (KeyChar == key.length())
					{
						flag = true;
						Char = Char - (key.length() - 1);
						break;
					}
				}
				else
				{
					KeyChar = 0;
				}
			}else{
				if (key[KeyChar] == c)
				{
					KeyChar++;
					if (KeyChar == key.length())
					{
						flag = true;
						Char = Char - (key.length() - 1);
						break;
					}
				}
				else
				{
					KeyChar = 0;
				}
			}

			
		}
		if (flag)
			break;
	}

	if (flag)
	{
		line(1);
		std::cout << commands[3] << " found at Line " << Line << " Character " << Char << std::endl;
		line(1);
	}
	else
	{
		line(1);
		std::cout << "\033[31m" << "Enable to find \"" << commands[3] << "\" in the file" << "\033[0m" << std::endl;
		line(1);
	}
}

void Delete(int args, char* commands[])
{
	if (fs::is_directory(commands[2])) {

		if (fs::remove(fs::current_path().string() + "/" + commands[2]) != 0)
		{
			line(1);
			std::cerr << "\033[31m\"" << commands[2] << "\" " << "Unable to Remove Directory" << "\033[0m" << std::endl;
			line(1);
		}		
	}
	else if (fs::is_regular_file(commands[2])) {

		if (std::remove(commands[2]) != 0)
		{
			line(1);
			std::cerr << "\033[31m\"" << commands[2] << "\" " << "Unable to Remove File" << "\033[0m" << std::endl;
			line(1);
		}
		else {
			line(1);
			std::cout << "Successfully removed " << commands[2] << std::endl;
			line(1);
		}
	}else{
		line(1);
		std::cerr << "\033[31m\"" << commands[2] << "\" " << "Unable to Remove" << "\033[0m" << std::endl;
		line(1);
	}
}

void append(int args, char* commands[]) {
	if (args <= 2) {
		line(1);
		std::cerr << "\033[31m" <<  "Incomplete Arguments" << "\033[0m" << std::endl;
		line(1);
		return;
	}

	if (args > 3) {
		std::string text;
		std::ofstream writer(commands[2], std::ios::app);
		std::ifstream reader(commands[3]);
		while (std::getline(reader, text)) {
			writer << text << std::endl;
		}
		writer.close();
		reader.close();
	}
	else if (args == 3) {
		std::string text;
		std::ofstream writer(commands[2], std::ios::app);
		
		line(1);
		std::cout << "Enter \"STOP\" to exit" << std::endl;
		line(1);

		std::cout << ">";
		while (std::getline(std::cin, text)) {
			if (text == "STOP") break;					
			std::cout << ">";
			writer << text << std::endl;
		}
		line(1);
		writer.close();
	}

}

void list(int args, char* commands[]) {

	line(1);

	std::cout << std::setw(20) << "Name" << std::setw(20) << "Size" << std::endl;
	std::cout << std::setw(20) << "----" << std::setw(20) << "----" << std::endl;
	std::vector<std::string> files = {};
	if (args == 2) {

		for (auto& file : fs::directory_iterator(fs::current_path())) {
				files.push_back(file.path().filename().string());
		}

		for (std::string file : files) {

			long long fileSize = getFileSize(file);
			if (fileSize == -1) {
				std::cout << std::setw(20) << file << std::setw(20) << "(Directory)" << std::endl;
			}
			else {

				std::cout << std::setw(20) << file << std::setw(20) << fileSize << std::endl;
			}
		}

	}
	else if (args == 2){
		std::vector<std::string> extentions = {};
		for (int i = 2; i < args; i++) {
			extentions.push_back(commands[i]);
		}
		for (const auto& file : fs::directory_iterator(fs::current_path()))
		{
			if (fs::is_regular_file(file))
			{
				if (extentions.empty() ||
					std::find(extentions.begin(), extentions.end(), file.path().extension().string()) != (extentions.end()))
				{
					long long fileSize = getFileSize(file.path().filename().string());

					files.push_back(file.path().filename().string());
				}
			}
		}

		for (std::string file : files) {
			long long fileSize = getFileSize(file);
			std::cout << std::setw(20) << file << std::setw(20) << "( " << fileSize << " )" << std::endl;
		}

	}
	line(1);
}

void create(int args, char* commands[]) {
	if (args < 3) {
		line(1);
		std::cerr << "\033[31m" << "Directory name not specified" << "\033[0m" << std::endl;
		line(1);
	}
	else {

		std::string dir = fs::current_path().string();
		dir += "/";
		dir += commands[2];
		fs::create_directory(dir);
		line(1);
		std::cout << "Directory Created Succesfully" << std::endl;
		line(1);

	}
}

void curl_get(int args, char* commands[]) {
	if (args <= 3) {
		line(1);
		std::cerr << "\033[31m" << "Incomplete Arguments" << "\033[0m" << std::endl;
		std::cerr << "\033[31m" << "Command Implementation: curl_get [url] [output file]" << "\033[0m" << std::endl;
		line(1);
		return;
	}

	line(1);
	fetchData(commands[3], commands[2]);
	line(1);


}

void pwd(int args, char* commands[]) {
	if (args > 1) {
		line(1);
		std::cout << std::filesystem::current_path() << std::endl;
		line(1);
	}
}

void random(int args, char* commands[]) {
	if (args == 2) {
		line(1);
		std::cerr << "\033[31m" << "Provide a range for random number generation" << "\033[0m" << std::endl;
		line(1);
		return;
	}
	else if (args == 3) {
		line(1);
		std::cerr << "\033[31m" << "Provide a upper bound for random number generation" << "\033[0m" << std::endl;
		line(1);
		return;
	}
	int low = atoi(commands[2]);
	int high = atoi(commands[3]);

	if (low > high) {
		low = low + high;
		high = low - high;
		low = low - high;
	}
	
	std::random_device rd;
	std::mt19937 gen(rd());

	std::uniform_int_distribution<> dis(low, high);
	int random = dis(gen);
	
	line(1);
	std::cout << random << std::endl;
	line(1);
}

void encrypt(int args, char* commands[]) {
	//uterminal encrypt filename
	if (args != 4) {
		std::cerr << "\033[31m" << "Invalid Command Syntax" << "\033[0m" << std::endl;
		return;
	}

	std::string key = commands[3];

	std::string fileName = commands[2];


	std::string outFileName = "enc.";
	outFileName.append(fileName);


	std::ifstream file(fileName, std::ios::binary);
	std::ofstream ofile(outFileName, std::ios::binary);


	if (!file.is_open()) {
		std::cerr << "Error opening file: " << fileName << std::endl;
		return;
	}
	if (!ofile.is_open()) {
		std::cerr << "Error creating Encrpyted file: " << std::endl;
		return;
	}


	std::vector<char> buffer = {};
	buffer = std::vector<char>((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

	size_t keyLen = key.size();
	
	for (size_t i = 0; i < buffer.size(); i++) {
		buffer[i] ^= key[i % keyLen];
	}
	
	ofile.write(buffer.data(), buffer.size());

	line(1);
	std::cout << "File Encrpyted and saved as " << outFileName << std::endl;
	line(1);
	
	ofile.close();
	file.close();
}

void decrypt(int args, char* commands[]) {

	if (args != 4) {
		std::cerr << "\033[31m" << "Invalid Command Syntax" << "\033[0m" << std::endl;
		return;
	}

	std::string key = commands[3];

	std::string fileName = commands[2];

	std::string outFileName = "dec.";
	
	if (fileName[0] == 'e' && fileName[1] == 'n' && fileName[2] == 'c' && fileName[3] == '.') {
		
		std::string fnm = fileName;
		fnm = fnm.substr(4, (fileName.length() - 1));
		outFileName.append(fnm);
	}
	else {
		outFileName.append(fileName);
	}
	

	std::ifstream file(fileName, std::ios::binary);
	std::ofstream ofile(outFileName, std::ios::binary);


	if (!file.is_open()) {
		std::cerr << "Error opening file: " << fileName << std::endl;
		return;
	}
	if (!ofile.is_open()) {
		std::cerr << "Error creating Decrypted file: " << std::endl;
		return;
	}


	std::vector<char> buffer = {};
	buffer = std::vector<char>((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

	size_t keyLen = key.size();

	for (size_t i = 0; i < buffer.size(); i++) {
		buffer[i] ^= key[i % keyLen];
	}

	ofile.write(buffer.data(), buffer.size());

	line(1);
	std::cout << "File Decrypted and saved as " << outFileName << std::endl;
	line(1);

	ofile.close();
	file.close();
}

void help()
{
	line(1);
	std::cout << "Commands:" << std::endl;
	std::cout << "---------" << std::endl;
	std::cout << "1. read [filename.extension]" << std::endl;
	std::cout << "2. search [filename.extension] [WordToSearch] <-i>" << std::endl;
	std::cout << "   use the -i flag to make the search incase-sensitive" << std::endl;
	std::cout << "3. write" << std::endl;
	std::cout << "4. delete [filename.extension]" << std::endl;
	std::cout << "   remove [filename.extension]" << std::endl;
	std::cout << "   rm [filename.extension]" << std::endl;
	std::cout << "5. append [file1name.extension] [file2name.extension] // appends file 2 to file 1" << std::endl;
	std::cout << "   append [filename.extension] // start writing what is too be appended" << std::endl;
	std::cout << "   app [filename.extension] // start writing what is too be appended" << std::endl;
	std::cout << "6. list" << std::endl;
	std::cout << "   ls" << std::endl;
	std::cout << "7. create [directory name] //To create a new directory" << std::endl;
	std::cout << "8. curl_get [url] [filename.extension] //To download a file over the network " << std::endl;
	std::cout << "9. pwd //Get present working directory" << std::endl;
	std::cout << "10. random [interger] [interger] //To get a random number from a range of numbers" << std::endl;
	std::cout << "11. encrypt [filename] [key] //key is like a password" << std::endl;
	std::cout << "    enc [filename] [key]" << std::endl;
	std::cout << "12. decrypt [filename] [key] //use key (password) to get the original file back" << std::endl;
	std::cout << "    dec [filename] [key] " << std::endl;
	line(1);
}

void version() {
	line(1);
	std::cout << "UTERMINAL VERSION 1.3 INSTALLED" << std::endl << std::endl;
	std::cout << "VISIT https://github.com/sahil-deo/Uterminal FOR THE SOURCE CODE" << std::endl;
	std::cout << "VISIT https://github.com/sahil-deo/UTerminal/releases FOR THE LATEST RELEASES" << std::endl;
	line(1);
}



//helper functions 

long long getFileSize(std::string fileName) {
	//uterminal size filename.ext

	char buffer[4096];
	long long fileSize = 0;

	std::ifstream file(fileName, std::ios::binary);

	if (!file.is_open()) {
		return -1;
	}

	while (file.read(buffer, sizeof(buffer))) {
		fileSize += file.gcount();
	}
	fileSize += file.gcount();

	return fileSize;
}

#pragma region CURL FETCH DATA FUNCTIONS

size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
	size_t totalSize = size * nmemb;
	std::ofstream* ofs = static_cast<std::ofstream*>(userp);
	ofs->write(static_cast<char*>(contents), totalSize);
	return totalSize;
}

void fetchData(std::string outputFilename, std::string url) {

	CURL* curl;
	CURLcode res;
	

	curl_global_init(CURL_GLOBAL_DEFAULT);
	curl = curl_easy_init();

	if (curl) {
		std::ofstream ofs(outputFilename, std::ios::binary);

		curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);

		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &ofs);

		res = curl_easy_perform(curl);

		if (res != CURLE_OK) {
			std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
		}
		else {
			std::cout << "File downloaded successfully." << std::endl;
		}

		ofs.close();
		curl_easy_cleanup(curl);
	}

	curl_global_cleanup();

}


#pragma endregion
