#include <iostream>
#include <map>
#include <string>
#include <iterator>
#include <vector>
#include <algorithm>
#include <functional>
#include <array>

std::vector<std::pair<std::string, int>> rendezMap ( std::map <std::string, int> &rank )
{
        std::vector<std::pair<std::string, int>> rendezett;

        for ( auto & i : rank ) {
                if ( i.second ) {
                        std::pair<std::string, int> p {i.first, i.second};
                        
                        rendezett.push_back ( p );

                }
        };

        std::sort (
                std::begin ( rendezett ), std::end ( rendezett ),
        [ = ] ( auto && p1, auto && p2 ) {

        		
        		std::cout<<p1.second<<std::endl;
        		std::cout<<p2.second<<std::endl;
        		std::cout<<"========="<<std::endl;
                return p1.second > p2.second;
                
        }
        );

        return rendezett;
}



 
int main()
{

    std::map<std::string, int> planetsMap;
    planetsMap.insert(std::make_pair("earth", 4));
    planetsMap.insert(std::make_pair("moon", 2));
    planetsMap.insert(std::make_pair("jupiter", 10));
    planetsMap.insert(std::make_pair("mars", 7));
    planetsMap.insert(std::make_pair("uranus", 3));
    planetsMap.insert(std::make_pair("saturnus", 9));
    std::map<std::string, int>::iterator it = planetsMap.begin();
    while(it != planetsMap.end())
    {
        std::cout<<it->first<<" :: "<<it->second<<std::endl;
        it++;
    }
    std::cout<<"-------------------------------------------------------------"<<std::endl;
      std::vector<std::pair<std::string, int>> rendezett=rendezMap(planetsMap);
      std::cout<<"-------------------------------------------------------------"<<std::endl;
      std::cout<<"Rendezés után:"<<std::endl;
    for ( auto & i : rendezett )
                std::cout << i.first << " - "  << i.second << std::endl;
    return 0;
}
