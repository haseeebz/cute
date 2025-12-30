#include "CuteCompiler.hpp"
#include <iostream>

#include <map>


struct ArgParser 
{

	std::map<std::string, std::string> options;
    std::map<std::string, bool> flags;

    void parse(int argc, char** argv) 
	{
        for (int i = 1; i < argc; i++) 
		{
            std::string arg = argv[i];

            if (arg.rfind("--", 0) == 0) 
			{
            
				if (i + 1 < argc && argv[i + 1][0] != '-') 
				{
					options[arg.substr(2)] = argv[++i];
				} 
				else 
				{
					flags[arg.substr(2)] = true;
				}
                
            }
			else if (arg.rfind("-", 0) == 0) 
			{
                if (arg.size() == 2 && i + 1 < argc && argv[i + 1][0] != '-') 
				{
                    options[arg.replace(0, 1, "")] = argv[++i];
                } 
				else 
				{
                    flags[arg.replace(0, 1, "")] = true;
                }

            }
			else 
			{
				std::cout << "Invalid argument: " << arg << std::endl;
				exit(1);
			}
        }
    }

    bool has_flag(const std::string& name)
	{
        return flags.contains(name) ? true : false;
	}

    std::string get_option(std::string name, std::string def = "")
	{
        return (options.contains(name)) ? options[name] : def;
    }

};


void help()
{
	std::cout << "Cute " << CUTE_VERSION << "\n\n";
	std::cout << " -c filepath : Invoke the compiler with a file.\n";
	std::cout << " -f comp     : Invoke the compiler a specific function for the file.\n";
	std::cout << " -o filepath : Specify the outfile for the compiler..\n";
	std::cout << " -r filepath : Invoke the engine with a file.\n";
	std::cout << " -h          : Show help.\n";
}


int main(int argc, char *argv[])
{
	ArgParser args;
	args.parse(argc, argv);

	std::string filepath;

	if (args.has_flag("-h"))
	{
		help();
		return 0;
	}

	filepath = args.get_option("c");

	if (filepath != "")
	{
		CuteCompiler compiler;

		std::string func = args.get_option("f");

		if (func != "")
		{
			compiler.invokeComponent(filepath, func);
			return 0;
		}

		std::string outfile = args.get_option("o", std::string(filepath).append(".out"));

		compiler.compile(filepath, outfile);
		return 0;
	}

	std::cout << "Invalid option!\n";
	return 1;
};