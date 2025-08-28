#ifndef ASCII_H
#define ASCII_H

#include <vector>
#include "system.h"

class Grid{
    private:
        int rows, cols;
        std::vector<char> data;
    public:
        Grid(int ROWS,int COLUMNS);

        char& operator()(int x, int y);
        const char& operator()(int x, int y) const;

        void print() const;
        void clearInterior(char fill = ' ');
        void drawParticle(const Particle& particle,char sym = 'o');
        void drawSystem(const System & system);
        void drawBins(const int binSize);

};

void printHistogram(const std::vector<Particle>& particles, int bins = 20, int height = 10);

#endif