#ifndef CONFIG_HPP
#define	CONFIG_HPP

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/foreach.hpp>
#include <iostream>

using namespace std;
using namespace boost::property_tree;

#include "singleton.hpp"

#define CONFIG_DIR "data"
#define DS "/"
#define CONFIG_FN "config.xml"

class config : public singleton {
    /*
     Konfiguracja klucz-wartość w słowniku
     * Funkcja get("klucz") do pobrania
     */
    public:
        config();
};

#endif	/* CONFIG_HPP */

