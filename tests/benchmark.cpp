// cpd - Coherent Point Drift
// Copyright (C) 2017 Pete Gadomski <pete.gadomski@gmail.com>
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License along
// with this program; if not, write to the Free Software Foundation, Inc.,
// 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

#include <cpd/affine.hpp>
#include <cpd/nonrigid.hpp>
#include <cpd/rigid.hpp>
#include <cpd/utils.hpp>
#include <fstream>
#include <iostream>
#include <string>

int main(int argc, char** argv) {
    if (argc != 6) {
        std::cout << "ERROR: invalid usage" << std::endl;
        return 1;
    }

    std::string method(argv[1]);
    cpd::Matrix fixed = cpd::matrix_from_path(argv[2]);
    cpd::Matrix moving = cpd::matrix_from_path(argv[3]);
    size_t niter(std::stoi(argv[4]));
    std::ofstream outfile(argv[5]);

    for (size_t i = 0; i < niter; ++i) {
        std::cout << "Beginning iteration #" << i << "..." << std::flush;
        auto tic = std::chrono::high_resolution_clock::now();
        if (method == "rigid") {
            cpd::rigid(fixed, moving);
        } else if (method == "affine") {
            cpd::affine(fixed, moving);
        } else if (method == "nonrigid") {
            cpd::nonrigid(fixed, moving);
        } else {
            std::cout << "ERROR: invalid method: " << method << std::endl;
            return 1;
        }
        auto toc = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> runtime = toc - tic;
        outfile << runtime.count() << std::endl;
        std::cout << "done in " << runtime.count() << " seconds" << std::endl;
    }

    return 0;
}
