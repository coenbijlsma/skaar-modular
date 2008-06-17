#ifndef SKAARCONFIG_H
#define SKAARCONFIG_H

#include <iostream>
#include <fstream>
#include <map>
#include <string>

#include "SkaarConfigSection.h"

#define DEFAULT_CONFIGFILE "skaar.conf.default"

using namespace std;

class SkaarConfig {

private:
    string				_filename;
    map<string, SkaarConfigSection*> 	_sections;
    
    /*
     * Reads the config file; is called
     * by the constructor.
     *
     * @throws string If the config file
     * cannot be opened.
     */
    void				_init();
    
    /*
     * Writes a SkaarConfigSection to the
     * provided ofstream*.
     *
     * @throws string If the file is not
     * accessable for writing.
     */
    void				_writeSection(ofstream* _fs, string name);
    
    /*
     * Creates the default config file.
     * This method is called when the provided
     * file (at construction time) doesn't exist,
     * and the default config file doesn't either.
     */
    void				_writeDefaultConfig();
    
public:

    /*
     * Constructor. 
     * Checks whether the provided file exists.
     * If that isn't the case, skaar falls back to
     * the default config file (see DEFAULT_CONFIGFILE).
     * If that doesn't exist either, skaar creates it.
     * 
     * @throws string When the default configfile
     * doesn't exist and can't be created.
     * 
     * @throws string If the _init() call fails.
     */
    SkaarConfig(string filename = "skaar.conf");
    
    /*
     * Destructor.
     * Writes the configfile and exits.
     */
    ~SkaarConfig();
    
    /*
     * Returns the section-config from
     * the section with the provided name.
     * If that section doesn't exist, this
     * method returns a NULL pointer.
     */
    SkaarConfigSection* 		getSection(string name);
    
    /*
     * Returns the value of the provided
     * setting in the provided section.
     * If the setting doesn't exist, 
     * this methods returns an empty string.
     */
    string				getValue(string section, string setting);
    
    /*
     * Sets or overwrites the value
     * of the provided setting in the 
     * section that is provided here.
     * 
     * @throws string When the section
     * doesn't exist. If a setting doesn't 
     * exist, it is created.
     */
    void				setSetting(string section, string setting, string value);
    
    /*
     * Writes the config to the filename
     * that was provided at construction,
     * even if that file didn't exist at 
     * the time.
     */
    bool				writeConfig();
};

typedef SkaarConfig* create_config_t(string filename);
typedef void destroy_config_t(SkaarConfig*);

#endif
