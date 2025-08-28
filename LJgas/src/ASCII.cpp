#include<iostream>
#include<vector>
#include <cmath>
#include <algorithm>
#include "system.h"
#include "ASCII.h"

Grid::Grid(int ROWS, int COLUMNS): rows(ROWS), cols(COLUMNS), data(ROWS*COLUMNS,' '){
    // Top and bottom borders
    for (int x = 0; x < cols; x++) {
        (*this)(0, x) = '-';             // top row
        (*this)(rows - 1, x) = '-';      // bottom row
    }

    // Left and right borders
    for (int y = 0; y < rows; y++) {
        (*this)(y, 0) = '|';             // left column
        (*this)(y, cols - 1) = '|';      // right column
    }

    // Optional: corners, so they don't show as '+'-ish mixes of | and -
    (*this)(0, 0) = '+';
    (*this)(0, cols - 1) = '+';
    (*this)(rows - 1, 0) = '+';
    (*this)(rows - 1, cols - 1) = '+';
}

char& Grid::operator()(int y, int x) {
    return data[y * cols + x];
}
const char& Grid::operator()(int y, int x) const {
    return data[y * cols + x];
}

void Grid::print() const {
        std::cout << "\x1b[H"; //return cursor to home position
        for (int y = 0; y < rows; y++) {
            std::cout.write(&data[y * cols], cols);
            std::cout << '\n';
        }
    }

void Grid::clearInterior(char fill) {
    for (int y = 1; y < rows - 1; y++) {
        for (int x = 1; x < cols - 1; x++) {
            (*this)(y, x) = fill;
        }
    }
}
void Grid::drawParticle(const Particle& particle,char sym){
    // int i = static_cast<int>(particle.y);
    // int j = static_cast<int>(particle.x);
    int i = static_cast<int>(std::lround(particle.y));
    int j = static_cast<int>(std::lround(particle.x));
    if(j > 0 && j < cols-1 && i > 0 && i < rows-1){
        (*this)(i, j) = sym;
    }
}

void Grid::drawSystem(const System & system){
    for (const auto & p:system.particles){
        drawParticle(p);
    }
}

void Grid::drawBins(const int binSize){
    // Vertical bin boundaries
    for (int x = binSize; x < cols-1; x += binSize) {
        for (int y = 1; y < rows-1; y++) {
            if ((*this)(y, x) == ' ') // don't overwrite walls
                (*this)(y, x) = ':';
        }
    }

    // Horizontal bin boundaries
    for (int y = binSize; y < rows-1; y += binSize) {
        for (int x = 1; x < cols-1; x++) {
            if ((*this)(y, x) == ' ')
                (*this)(y, x) = '-';
        }
    }
}


void printHistogram(const std::vector<Particle>& particles, int bins, int height) {
    // collect speeds
    std::vector<double> speeds;
    speeds.reserve(particles.size());
    for (const auto& p : particles) {
        double v = std::sqrt(p.vx * p.vx + p.vy * p.vy);
        speeds.push_back(v);
    }

    // find max speed to normalize bins
    double vmax = *std::max_element(speeds.begin(), speeds.end());
    if (vmax == 0) return;

    std::vector<int> hist(bins, 0);
    for (double v : speeds) {
        int idx = std::min(int(v / vmax * bins), bins - 1);
        hist[idx]++;
    }

    // find maximum count (for scaling)
    int maxCount = *std::max_element(hist.begin(), hist.end());
    if (maxCount == 0) return;

    // print vertically (top to bottom)
    for (int h = height; h > 0; --h) {
        for (int b = 0; b < bins; b++) {
            if (hist[b] * height / maxCount >= h)
                std::cout << '#';
            else
                std::cout << ' ';
        }
        std::cout << '\n';
    }

    // bottom axis
    for (int b = 0; b < bins; b++) std::cout << '-';
    std::cout << '\n';
}
