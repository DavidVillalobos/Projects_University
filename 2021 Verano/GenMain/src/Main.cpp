/* File: Main.cpp
 * Date: 21/01/2021
 * Author: Luis David Villalobos Gonzalez
 * Description: The program is responsible for  
 * 		generating the main file with a hello  
 * 		world of languages such as c++, c#,
 * 		java, python and ruby.
 * */

#include<iostream>
#include<fstream>
#include<cctype>
#include<cstring>
#include<cstdio>
#include"Generator.cpp"


int main(int argc, char** argv){
	if (argc < 2) {
		std::cout << "\t Please only enter the language in\n";
		std::cout << "\twhich you want to generate the main.";
		return 0;
	}
	std::stringstream out;
	std::string language = "";
	std::string file_name;
	for (int i=0; i<strlen(argv[1]); i++) {
		language += tolower(argv[1][i]);
	}
	if (language == "help") {
		std::cout << "GENMAIN: Main file generator\n";
		std::cout << "\tUsage: genmain [Lenguage][fileName]\n";
		std::cout << "\tLenguages: c++, java, python c#, ruby";
		return 0;
	}
	if (argc < 3) {
		std::cout << "File name (Main): ";
		std::getline(std::cin, file_name);
		if (file_name.empty()) { 
			file_name = "Main";
		}
	} else {
		file_name = argv[2];
	}
	switch (lang[language]){
		case 1: {
			out << generate_cplusplus_main();
			break;
		}
		case 2: { 
			out << generate_csharp_main(file_name); 
			break;
		}
		case 3: {
			out << generate_java_main(file_name); 
			break;
		}
		case 4: {
			out << generate_python_main(); 
			break;
		}
		case 5: {
			out << generate_ruby_main(); 
			break;
		}
		default: {
			std::cout << "\t The word entered is not a programming\n";
			std::cout << "\tlanguage or we do not have it available\n";
			std::cout << "\t     to generate a main, sorry.";
			break;
		}
	}
	if (!out.str().empty()) {
		std::string name = file_name + '.' + ext[lang[language]];	
		std::ofstream main_file(name);
		main_file << out.str();
		main_file.close();
		std::cout << "Your file is ready -> " << name << '\n';
	}
}