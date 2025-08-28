#include <iostream>
#include <string>
#include <chrono>
#include <cmath>
#include <thread>
#include "system.h"
#include "ASCII.h"


constexpr double KB = 8.617333262e-5; //in eV K^-1

int main(int argc, char *argv[]) {

    int N = 30;
    double r_cut = 5;
    int height = 15; //number of rows
    int width = 54; //number of columns
    int BINSIZE = 5;
    double dt = .01;

    //physical constants for Argon
    // double m0 = 6.69e-26; //Argon mass
    double m = 1;
    // double sigma = 3.4e-10; //meters
    double epsilon = 0.010; //EV, in Joules it is 1.65e-21
    double T0 = 300; //in kelvin
    // double t0 = sqrt(m*sigma*sigma/epsilon); //time scale

    for(int i=1;i<argc;i++){
        std::string arg = argv[i];
        if(arg == "-h" || arg == "--help"){
            std::cout << "Usage: " << argv[0] << " [Params]\n";
            std::cout << "Params:\n";
            std::cout << "  -h, --help      Show this help message\n";
            std::cout << "  -dt <value>     Set the time step (default: " << dt << ")\n";
            std::cout << "  -N <value>      Set the number of particles (default: " << N << ")\n";
            std::cout << "  -s <height> <width>  Set the grid size (default: " << height << "x" << width << ")\n";
            std::cout << "  -T <value>      Set the temperature (default: " << T0 << "K)\n";
            std::cout << "  -m <value>      Set the mass (default: " << m << ")\n";
            std::cout << "  -c <value>      Set the cutoff radius (default: " << r_cut << "σ)\n";
            std::cout << "  -e <value>      Set the epsilon (default: " << epsilon << "eV)\n";
            return 0;
        }
        else if(arg == "-dt"){
            if(i+1<argc){
                dt = std::stod(argv[++i]);
            }
            else{
                std::cerr << "Error: -dt requires a value" << std::endl; return 1;
            }
        } 
        else if(arg == "-N"){
            if(i+1<argc){
                N = std::stoi(argv[++i]);
            }
            else{
                std::cerr << "Error: -N requires a value" << std::endl; return 1;
            }
        }
        else if(arg == "-s" || arg == "--size"){
            if(i+2<argc){
                height = std::stoi(argv[++i]);
                width = std::stoi(argv[++i]);
            }
            else{
                std::cerr << "Error: -s requires two values" << std::endl; return 1;
            }
        }
        else if(arg=="-T" || arg == "--temperature"){
            if(i+1<argc){
                T0 = std::stod(argv[++i]);
            }
            else{
                std::cerr << "Error: -T requires a value" << std::endl; return 1;
            }
        }
        else if(arg=="-m" || arg == "--mass"){
            if(i+1<argc){
                m = std::stod(argv[++i]);
            }
            else{
                std::cerr << "Error: -m requires a value" << std::endl; return 1;
            }

        }
        else if(arg=="-c" || arg == "--cutoff"){
            if(i+1<argc){
                r_cut = std::stod(argv[++i]);
            }
            else{
                std::cerr << "Error: -c requires a value"<< std::endl; return 1;
            }
        }
        else if(arg=="-e"|| arg == "--epsilon"){
            if(i+1<argc){
                epsilon = std::stod(argv[++i]);
            }
            else{
                std::cerr << "Error: -e requires a value"<< std::endl; return 1;
            }
        }

    }

    T0 = KB* T0/epsilon; //convert from Kelvin to reduced temperature

    Grid grid(height, width);
    GridBin gridbins(height,width,BINSIZE);
    System system(N,gridbins,T0,m,r_cut);

    std::cout << "\x1b[2J"; 
    while(true){
        grid.clearInterior();
        system.update(dt);
        system.rescaleTemp(); //thermostat
        grid.drawSystem(system);

        grid.print();
        std::cout<<"E= "<<system.getEnergy()*epsilon<<"eV \n";
        std::cout<<"T= "<<system.getTemperature()* epsilon /KB<< "K \n";
        

        std::this_thread::sleep_for(std::chrono::milliseconds(10)); // Sleep 
    }

    return 0;
}