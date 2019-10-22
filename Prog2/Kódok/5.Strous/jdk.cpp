#include <iostream>
#include <string>
#include <map>
#include <iomanip>
#include <fstream>

#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/program_options.hpp>

using std::cout;
using namespace std;
using namespace boost::filesystem;

static int counter=0;
static std::vector<path> v;
void read_acts ( path p)
{
     

        if ( is_regular_file ( p ) ) {

            std::string ext ( ".java" );
              
                if ( !ext.compare ( extension ( p ) ) ) 
                {
                  counter++;
                  v.push_back(p); 
                }

        } else if ( is_directory ( p ) )
                for ( directory_entry & entry : directory_iterator ( p ) )
                        read_acts ( entry.path());  
}



int main ( int argc, char *argv[] )
{
   if (argc < 2)
  {
    cout << "Usage: jdk path\n";
    return 1;
  }

  path p (argv[1]);

  read_acts(p);  
  for(auto&& x : v)
      cout << x.filename()<< endl;
   cout << counter << endl;
  return 0;
        

}

//g++ -I/home/petra/boost66/include/ -L/home/petra/boost66/lib/ jdk.cpp -o jdk -lboost_system -lboost_filesystem -lboost_program_options -lboost_date_time -std=c++14

