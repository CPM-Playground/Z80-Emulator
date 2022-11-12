/**

    @file      memory.h
    @brief     
    @details   ~
    @author    ifknot
    @date      12.11.2022
    @copyright © ifknot, 2022. All right reserved.

**/
#pragma once

#include <array>
#include <format>
#include <iostream>
#include <memory>
#include <random>


#include "memory_types.h"

namespace z80 {


    template<address_t BEGIN, address_t END>
    class memory {

        using byte_array = std::array<byte_t, END - BEGIN + 1>;
        using mem = std::unique_ptr<byte_array>;

    public:

        memory() : bytes(new byte_array{}) {
            for (auto addr{ 0 }; addr < size(); ++addr) {
                bytes->at(addr) = distribution(rand) % 255;
            }
        }

        inline byte_t operator[](address_t addr) const {
            return bytes->at(addr - BEGIN);
        }

        inline byte_t& operator[](address_t addr) {
            return bytes->at(addr - BEGIN);
        }

        void dump(address_t begin, address_t end) const {
            end -= begin;
            for (auto i{ 0 }; i < end; i += 16) {
                dump_paragraph(i);
            }
        }

        void dump_paragraph(address_t addr) const {
            std::cout << std::format("${:04X} ", addr);
            addr -= BEGIN;
            for (auto i{ 0 }; i < 16; ++i) {
                std::cout << std::format("{:02X} ", (uint8_t)bytes->at(addr + i));
            }
            std::cout << "| ";
            for (auto i{ 0 }; i < 16; ++i) {
                if (bytes->at(addr + i) < 32) {
                    std::cout << ' ';
                }
                else {
                    std::cout << bytes->at(addr + i);
                }
            }
            std::cout << " |\n";
        }

        void fill(address_t begin, address_t end, byte_t b) const {
            end -= begin;
            begin -= BEGIN;
            for (auto i{ 0 }; i < end; ++i) {
                bytes->at(begin + i) = b;
            }
        }

        size_t size() const {
            return bytes->size();
        }

    private:

        mem bytes;

        std::mt19937 rand;
        std::uniform_int_distribution<std::mt19937::result_type> distribution;

    };

}