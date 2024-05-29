#include <iostream>
#include <cmath>
#include <vector>
#include <string>

struct OptionData {
    double S;
    double K;
    double T;
    double r;
    double sigma;
    std::string type;
};

std::vector<OptionData> getOptions();
double black_scholes_call(double S, double K, double T, double r, double sigma);
double black_scholes_put(double S, double K, double T, double r, double sigma);
double norm_cdf(double x);

int main() {
    std::vector<OptionData> options = getOptions();

    for (const auto& option : options) {
        double price;
        if (option.type == "call") {
            price = black_scholes_call(option.S, option.K, option.T, option.r, option.sigma);
        } else {
            price = black_scholes_put(option.S, option.K, option.T, option.r, option.sigma);
        }
        std::cout << "The price of the " << option.type << " option is: " << price << std::endl;
    }

    return 0;
}

void getInput(OptionData& option) {
    std::cout << "Enter stock price (S): ";
    std::cin >> option.S;
    std::cout << "Enter strike price (K): ";
    std::cin >> option.K;
    std::cout << "Enter time to maturity (T in years): ";
    std::cin >> option.T;
    std::cout << "Enter risk-free rate (r): ";
    std::cin >> option.r;
    std::cout << "Enter volatility (sigma): ";
    std::cin >> option.sigma;
    std::cout << "Enter option type (call/put): ";
    std::cin >> option.type;
}

std::vector<OptionData> getOptions() {
    std::vector<OptionData> options;
    char choice;
    do {
        OptionData option;
        getInput(option);
        options.push_back(option);
        std::cout << "Do you want to enter another option? (y/n): ";
        std::cin >> choice;
    } while (choice == 'y' || choice == 'Y');
    return options;
}

double norm_cdf(double x) {
    return 0.5 * std::erfc(-x * M_SQRT1_2);
}

double black_scholes_call(double S, double K, double T, double r, double sigma) {
    double d1 = (std::log(S / K) + (r + 0.5 * sigma * sigma) * T) / (sigma * std::sqrt(T));
    double d2 = d1 - sigma * std::sqrt(T);
    return S * norm_cdf(d1) - K * std::exp(-r * T) * norm_cdf(d2);
}

double black_scholes_put(double S, double K, double T, double r, double sigma) {
    double d1 = (std::log(S / K) + (r + 0.5 * sigma * sigma) * T) / (sigma * std::sqrt(T));
    double d2 = d1 - sigma * std::sqrt(T);
    return K * std::exp(-r * T) * norm_cdf(-d2) - S * norm_cdf(-d1);
}
