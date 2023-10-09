//
// Created by gxrcondeau on 2023-10-08.
//

#include "ConfigLoader.h"

using namespace pugi;
namespace fs = std::filesystem;

const char *const configLocation = "./Config/Engine.xml";

ConfigLoader::ConfigLoader() {
}

ConfigLoader::~ConfigLoader() {
}

void ConfigLoader::load() {
    configCheck();
    if(configExist) {
        xml_document doc;

        xml_parse_result result = doc.load_file(configLocation);

        std::cout << "Load result: " << result.description() << ", engine version: " << doc.child("PEIM").child("build").attribute("version").value() << ":" << doc.child("PEIM").child("build").attribute("channel").value() << std::endl;
    }
    else {
        reset();
    }
}

void ConfigLoader::reset() {
    std::ofstream outfile (configLocation);
    outfile << "<?xml version=\"1.0\"?>\n"
               "<PEIM>\n"
               "    <build version=\"0.1\" channel=\"dev\"/>\n"
               "    <window width=\"1280\" height=\"720\" fullscreen=\"0\"/>\n"
               "</PEIM>";
    outfile.close();
}

void ConfigLoader::configCheck() {
    if(fs::exists(configLocation)) {
        configExist = true;
    } else {
        configExist = false;
        fs::create_directory("./Config");
    }
}
