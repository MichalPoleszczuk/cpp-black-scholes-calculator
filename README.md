# Options Pricing Calculator

## Overview

I am in the process of building this project (options pricing calculator implemented in pure C++ without using any external libraries). The primary goal is to provide a foundational implementation of financial models that can be built upon in future iterations. This project is part of an assignment for the "Programming in C++" class at Warsaw School of Economics.

### Features that I have already implemented

- user input for various option parameters, like: underlying stock price, strike price, time to maturity, risk-free rate, volatility and option type (call/put)
- pricing of european calls and puts with the use of Black-Scholes model
- Calculation of option Greeks (Delta, Gamma, Vega, Theta, Rho)
- Outputting option data, prices, and Greeks to a CSV file (exemplary file for 15 instruments in the repository)

## Purpose

I build this project as an assignment for "Programming in C++" class at my university. The project aims to demonstrate the practical application of C++ in the field of quantitative finance. It showcases fundamental concepts of C++ such as user-defined data types, functions, and mathematical computations, and applies them to real-world financial problems.

## Getting Started

### In order to run, you will need

- C++ compiler (e.g., g++) with support for C++11 standard

### Installation

1. Clone the repository:
   ```bash
   git clone https://github.com/MichalPoleszczuk/cpp-black-scholes-calculator.git
2. Navigate to the project directory:
3. ```bash
   cd cpp-black-scholes-calculator
4. In order to compile:
   ```bash
   g++ -std=c++11 black-scholes-calculator.cpp -o options_pricing_calculator
5. To run:
   ```bash
   ./options_pricing_calculator

### How to use

When you run the program, it will prompt you to enter the following parameters for one or more options:

  - Stock price (S)
  - Strike price (K)
  - Time to maturity (T in years)
  - Risk-free rate (r)
  - Volatility (sigma)
  - Option type (call/put)

After entering the details, the program will calculate and display the price of the specified options using the Black-Scholes model. The newly added feature, calculates the Greeks for each option and display them (only if desired). The results can also be saved to a CSV file for further analysis and other business needs.

### If time allows, these are features that I will implement in the next following days/weeks 

  1. Additional pricing models (e.g., Binomial Tree Model)
  2. Visualization of option prices and Greeks
   
