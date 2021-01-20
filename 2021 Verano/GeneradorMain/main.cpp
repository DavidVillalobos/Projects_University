/* File: main.cpp
 * Date: 20/01/2021
 * Author: Luis David Villobos Gonzalez
 * Description: The program is responsible for generating 
 * 				the main file with a hello world of 
 * 				languages such as c ++, c #, java 
 * 				python and ruby.
 * */


#include<iostream>
#include <cctype>
#include <cstring>
#include <cstdio>
#include<sstream>
using std::cout;
using std::string;

string generate_cplusplus_main();
string generate_csharp_main();
string generate_java_main();
string generate_python_main();
string generate_ruby_main();

int main(int argc, char** argv){
	if(argc != 2){
		cout << "\t Please only enter the language in\n";
		cout << "\twhich you want to generate the main.";
	}else{
		string language = "";
		for (int i=0; i<strlen(argv[1]); i++)
			language += tolower(argv[1][i]);
		if(language == "c++" || language == "cplusplus")
			cout << generate_cplusplus_main();
		else if(language == "c#" || language == "csharp")
			cout << generate_csharp_main();
		else if(language == "java")
			cout << generate_java_main();
		else if(language == "python")
			cout << generate_python_main();
		else if(language == "ruby")
			cout << generate_ruby_main();
		else {
			cout << "\t The word entered is not a programming\n";
			cout << "\tlanguage or we do not have it available\n";
			cout << "\t     to generate a main, sorry.";
		}
	}
}

string generate_cplusplus_main(){ return "c++";}
string generate_java_main(){ return "java";}
string generate_python_main(){ return "python";}         
string generate_ruby_main(){ return "ruby";}
string generate_csharp_main(){ return "c#";}
