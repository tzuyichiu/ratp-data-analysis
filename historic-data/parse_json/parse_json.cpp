#include <jsoncpp/json/json.h>
#include <iostream>
#include <fstream>
#include <string.h>
#include <algorithm>

int main(int argc, char* argv[]) {
	
	if (argc != 2) {
		printf("Usage: %s docname\n", argv[0]);
		return (0);
	}

	Json::Value json;
	Json::FastWriter fastWriter;
	std::ifstream RERA_file(argv[1]);
	RERA_file >> json;

	std::string response;

	for (int i=0; i<json["run"]["executions"].size(); i++) {
		response = fastWriter.write(json["run"]["executions"][i]["assertions"][0]["assertion"]);
		
		response = response.substr(1,response.length()-3);
			
		for(size_t pos = 0; ; pos += 2) {
	        // Locate the substring to replace
	        pos = response.find("\\\"", pos);
	        if (pos == std::string::npos)
	        	break;
	        // Replace by erasing and inserting
	        response.erase(pos, 2);
	        response.insert(pos, "\"");
	    }

	    std::string name(argv[1]);
	    name = name.substr(0, name.length()-5);
		std::ofstream station_file("xml/" + std::to_string(i+1) + "station.xml");
		station_file << response;
		station_file.close();
	}
	return (1);
}