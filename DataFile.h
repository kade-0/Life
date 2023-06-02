#pragma once
#ifndef DATAFILE_INCLUDE
#define DATAFILE_INCLUDE
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

std::string datafile_static_version = "version;1.6.2.23#";

struct Field {
public:
	std::string Key;
	std::string Value;

	Field(std::string k, std::string v)
	{
		Key = k;
		Value = v;
	}
};

class DataFile {
public:
	std::string path = "";
	std::string version = "";

	std::vector<Field> fields;

	DataFile(std::string _path)
	{
		path = _path;

	}

	void Deserialize()
	{
		std::ifstream f(path);
		std::string line;
		int i = 0;
		while (std::getline(f, line))
		{
			std::string key = line.substr(0, line.find_last_of(";"));
			std::string value = line.substr(line.find_last_of(";") + 1, line.find_last_of("#"));

			if (i == 0) // 1st line is always the version
			{
				version = value;
				continue;
			}


			fields.push_back(Field(key, value));

			i++;
		}

	}

	void Seriallize()
	{
		std::ofstream f(path);

		f << datafile_static_version << "\n";
		for (Field& df : fields)
		{
			f << df.Key << ";" << df.Value << "#\n";
		}

		f.close();
	}
};

#endif