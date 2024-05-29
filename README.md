# Options Pricing Calculator

## Overview

I am in the process of building this project (options pricing calculator implemented in pure C++ without using any external libraries). The primary goal is to provide a foundational implementation of financial models that can be built upon in future iterations. This project is part of an assignment for the "Programming in C++" class at Warsaw School of Economics.

### Features that I have already implemented

- user input for various option parameters, like: underlying inst. price or ttm
- pricing of european calls and puts with the use of Black-Scholes 

## Purpose

I build this project as an assignment for "Programming in C++" class at my university. The project aims to demonstrate the practical application of C++ in the field of quantitative finance. It showcases fundamental concepts of C++ such as user-defined data types, functions, and mathematical computations, and applies them to real-world financial problems.

## Getting Started

### In order to run, you will need

- C++ compiler (e.g., g++)

### Installation

1. Clone the repository:
   ```bash
   git clone https://github.com/MichalPoleszczuk/cpp-black-scholes-calculator.git
2. Navigate to the project directory:
3. ```bash
   cd cpp-black-scholes-calculator
4. In order to compile:
   ```bash
   g++ black-scholes-calculator.cpp -o options_pricing_calculator
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

After entering the details, the program will calculate and display the price of the specified options using the Black-Scholes model.

### Features I will implement in the next following days/weeks 

  1. Additional pricing models (e.g., Binomial Tree Model)
  2. Handling of a volatility surface
  3. Calculation of option Greeks (Delta, Gamma, Vega, Theta, Rho)
  4. Outputting data to CSV files
  5. Visualization of option prices and Greeks
   
