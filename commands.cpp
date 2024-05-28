#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>
#include <cstdio>
#include <vector>
#include <filesystem>
#include <curl/curl.h>

namespace fs = std::filesystem;

//std::cerr << "\033[31m" << " " << "\033[0m" << std::endl;
void fetchData(std::string outputFilename, std::string url); 

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
	reader.open(commands[2]);

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

	if (args < 3)
	{
		line(1);
		std::cerr << "\033[31m" << "Key not given" << "\033[0m" << std::endl;
		line(1);
		return;
	}

	std::string text, key = commands[3];
	std::ifstream reader;
	reader.open(commands[2]);
	int Line = 0, Char = 0, KeyChar = 0;
	bool flag = false;

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
			std::cerr << "\033[31m\"" << commands[2] << "\" " << "Unable to Remove Directory" << "\033[0m" << std::endl;
		}		
	}
	else if (fs::is_regular_file(commands[2])) {

		if (std::remove(commands[2]) != 0)
		{
			std::cerr << "\033[31m\"" << commands[2] << "\" " << "Unable to Remove File" << "\033[0m" << std::endl;
		}
	}else{
		std::cerr << "\033[31m\"" << commands[2] << "\" " << "Unable to Remove" << "\033[0m" << std::endl;
	}
}

void append(int args, char* commands[]) {
	if (args <= 2) {
		std::cerr << "\033[31m" <<  "Incomplete Arguments" << "\033[0m" << std::endl;
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

	std::cout << "Name" << std::endl << "----" << std::endl;
	std::vector<std::string> files = {};
	if (args == 2) {

		for (auto& file : fs::directory_iterator(fs::current_path())) {
			if (fs::is_regular_file(file))
			{
				files.push_back(file.path().filename().string());				
			}
			else {
				files.push_back(file.path().filename().string().append(" (Directory)"));

			}
		}

		for (std::string file : files) {
			std::cout << file << std::endl;
		}

	}
	else if (args > 2){
		std::vector<std::string> extentions = {};
		for (int i = 2; i < args; i++) {
			extentions.push_back(commands[i]);
		}
		for (const auto& file : fs::recursive_directory_iterator(fs::current_path()))
		{
			if (fs::is_regular_file(file))
			{
				if (extentions.empty() ||
					std::find(extentions.begin(), extentions.end(), file.path().extension().string()) != (extentions.end()))
				{
					files.push_back(file.path().filename().string());
				}
			}
		}

		for (std::string file : files) {
			std::cout << file << std::endl;
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
	}
}

void curl_get(int args, char* commands[]) {
	if (args <= 3) {
		std::cerr << "\033[31m" << "Incomplete Arguments" << "\033[0m" << std::endl;
		std::cerr << "\033[31m" << "Command Implementation: curl_get [url] [output file]" << "\033[0m" << std::endl;
		return;
	}

	fetchData(commands[3], commands[2]);


}

void help()
{
	line(1);
	std::cout << "Commands: " << std::endl;
	std::cout << "read [filename.extention]" << std::endl;
	std::cout << "search [filename.extention] [WordToSearch]" << std::endl;
	std::cout << "write" << std::endl;
	std::cout << "delete [filename.extention]" << std::endl;
	std::cout << "append [file1name.extention] [file2name.extention] // appends fil e 2 to file 1" << std::endl;
	std::cout << "append [filename.extention] // start writing what is too be appended" << std::endl;
	std::cout << "list" << std::endl;
	std::cout << "create [directory name] //To create a new directory" << std::endl;
	line(1);
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
