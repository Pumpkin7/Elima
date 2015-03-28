#include <iostream>
#include <fstream>
#include <string>
#include <boost/filesystem.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

using namespace std;
using namespace boost::filesystem;
using boost::property_tree::ptree;
void c(path p, ptree &pt) {
	for (directory_iterator i(p);
		i != directory_iterator();
		++i)
	{
		if (is_directory(*i)) c(*i, pt);
		if (is_regular_file(*i)) {
			path p1 = *i;
			ptree elima;
			elima.put("Filename", p1.filename().string());
			elima.put("Filesize", file_size(*i));
			elima.put("Filepath", p1.string());
			pt.push_back(make_pair("", elima));
		}
	}
}
ptree s() {cout << "Enter your path" << endl;
ptree pt;
ptree files_array;
path pk;
string s1;
getline(cin, s1);
pk = s1;

c(pk, files_array);

pt.add_child("Path(" + pk.string() + ")Files", files_array);
return pt;
}
int main() {
	ptree pt = s();
	write_xml("./elima.xml", pt);
	return 0; 
}