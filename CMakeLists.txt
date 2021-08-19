cmake_minimum_required(VERSION 3.19)
project(OptionExactPricingMonteCarloPricing)


set(CMAKE_CXX_STANDARD 14)


set(BOOST_ROOT "/Users/muyaosi/CppD/boost_1_62_0")


find_package(Boost 1.62.0)

include_directories(${BOOST_ROOT})


add_executable(OptionExactPricingMonteCarloPricing main.cpp Options.cpp Options.h EuroOption.cpp EuroOption.h OptionMatrix.h AmericanOption.cpp AmericanOption.h OptionParameter.h NormalDistribution.cpp NormalDistribution.h path.cpp path.h)