#include <iostream>
#include <string>
#include <vector>
#include <sstream>

#define BOOST_TEST_MAIN
#include <boost/test/included/unit_test.hpp> 
#include "pillowtalk.h"

using namespace std;
using namespace boost::unit_test;

static string 
read_file(const string& filename)
{
  string test_files_dir = string(boost::unit_test::framework::master_test_suite().argv[1]);
  stringstream content;
  string line;
  ifstream myfile((test_files_dir + "/" + filename).c_str());
  if (myfile.is_open())
  {
    while (! myfile.eof() )
    {
      getline (myfile,line);
      content << line << endl;
    }
    myfile.close();
  } else {  
    cout << "Unable to open file" << endl;
    exit(-1);
  }
  return content.str();
}

BOOST_AUTO_TEST_CASE( test_memory_leak )
{
  pt_node_t* root = pt_from_json("{\"test\":{hello:\"world\"}}");
  BOOST_REQUIRE(pt_map_get(root,"test"));
  pt_free_node(root);
}

BOOST_AUTO_TEST_CASE( test_bad_json )
{
  pt_node_t* root = pt_from_json("{}}");
  pt_free_node(root);
}

BOOST_AUTO_TEST_CASE( test_simple_array )
{
  pt_node_t* array = pt_from_json("[\"1\"]");
  BOOST_REQUIRE_EQUAL(pt_array_len(array),1);
  pt_node_t* str = pt_array_get(array,0);
  BOOST_REQUIRE_EQUAL(pt_string_get(str),"1");

  pt_free_node(array);
}
