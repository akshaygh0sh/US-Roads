#include<iostream>
#include<rapidcsv.h>

int main(){
    rapidcsv::Document nodes("data/NA.cnode.txt", rapidcsv::LabelParams(-1,-1), rapidcsv::SeparatorParams(' '));
    auto x_coords = nodes.GetColumn<double>(1);
    auto y_coords = nodes.GetColumn<double>(2);

    rapidcsv::Document edges("data/NA.cedge.txt", rapidcsv::LabelParams(-1,-1), rapidcsv::SeparatorParams(' '));
    auto from = edges.GetColumn<double>(1);
    auto to = edges.GetColumn<double>(2);
    auto length = edges.GetColumn<double>(3);


    for(auto x : x_coords){
        std::cout << x << '\n';
    }
}