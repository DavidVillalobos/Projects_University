/* File: Generator.cpp
 * Date: 21/01/2021
 * Author: Luis David Villalobos Gonzalez
 * Description: This file contains the generating 
 * 				methods of the mains of each language.
 * */

#include<sstream>
#include<map>

// Language dictionary
std::map<std::string, int> lang = {
	{"c++",1}, {"cplusplus",1}, {"c#",2}, {"csharp",2},
	{"java",3}, {"python",4}, {"ruby",5}
};

// Extension dictionary
std::map<int, std::string> ext = {
	{1,"cpp"}, {2,"cs"}, {3,"java"}, {4,"py"}, {5,"rb"}
};

// Generator Main file for C++
std::string generate_cplusplus_main()
{ 
	std::stringstream file;
	file << "#include<iostream>\n";
	file << "using namespace std;\n\n";
	file << "int main(int argc, char** argv){\n";
	file << "\tcout << \"Hello World\" << endl;\n";
	file << "}\n";
	return file.str();
}

// Generator Main file for C#
std::string generate_csharp_main(std::string name_class)
{ 
	if(name_class == "Main") name_class = "MainFile";
	std::stringstream file;
	file << "class " << name_class << " {\n";         
	file << "\tstatic void Main(string[] args)\n";
	file << "\t{\n";
	file << "\t\tSystem.Console.WriteLine(\"Hello World\");\n";
	file << "\t}\n";
	file << "}\n";
	return file.str();
}

// Generator Main file for Java
std::string generate_java_main(std::string file_name)
{
	std::stringstream file;
	file << "public class " << file_name << "{\n";
	file << "\tpublic static void main(String[] args){\n";
	file << "\t\tSystem.out.println(\"Hello World\");\n";
	file << "\t}\n";
	file << "}\n";
	return file.str();
}

// Generator Main file for Python
std::string generate_python_main()
{	
	std::stringstream file;
	file << "\nif __name__ == '__main__':\n";
	file << "\tprint('Hello World')\n";
	return file.str();
}

// Generator Main file for Ruby
std::string generate_ruby_main()
{ 
	std::stringstream file;
	file << "\nif __FILE__ == $0\n";
	file << "\tputs 'Hello World'\n";
	file << "\tend\n";
	return file.str();	
}
