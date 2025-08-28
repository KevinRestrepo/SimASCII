#include <iostream>
#include <string>
#include <cmath>
#include <random>
#include <chrono>
#include <thread>
#include "system.h"
#include "ASCII.h"



const double KB = 1.0;
const double T0 = 1;
const double m = 0.1;

constexpr int N = 30;
const double r_cut = 5;
const int height = 15;
const int width = 54;
constexpr int BINSIZE = 5;
constexpr double dt = .01;

int main(int argc, char *argv[]) {
    for(int i=1;i<argc;i++){
        std::string arg = argv[i];
        if(arg == "-dt"){
            dt = std::stod(argv[++i]);
        } 

    }
    Grid grid(height, width);
    GridBin gridbins(height,width,BINSIZE);
    System system(N,gridbins,T0,m,KB,r_cut);

    std::cout << "\x1b[2J"; 
    while(true){
        grid.clearInterior();
        system.update(dt);
        system.rescaleTemp();
        grid.drawSystem(system);

        grid.print();
        std::cout<<"E= "<<system.getEnergy()<<'\n';
        

        std::this_thread::sleep_for(std::chrono::milliseconds(10)); // Sleep 
    }

    return 0;
}