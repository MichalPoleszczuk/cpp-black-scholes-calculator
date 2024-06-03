#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>
#include <iomanip> 

struct OptionData {
    double stockPrice; // Stock price
    double strikePrice; // Strike price
    double timeToMaturity; // Time to maturity
    double riskFreeRate; // Risk-free Rate
    double volatility; // Volatility
    std::string optionType; // Call or Put Option Type
};

std::vector<OptionData> getOptions();
double blackScholesCall(double S, double K, double T, double r, double sigma);
double blackScholesPut(double S, double K, double T, double r, double sigma);
double normCDF(double x);
void calculateGreeks(const OptionData& option, double& delta, double& gamma, double& vega, double& theta, double& rho);
void outputToCSV(const std::vector<OptionData>& options, const std::vector<double>& prices, const std::vector<std::vector<double>>& greeks);
void displayResults(const std::vector<OptionData>& options, const std::vector<double>& prices, const std::vector<std::vector<double>>& greeks, bool showGreeks);

int main() {
    std::vector<OptionData> options = getOptions();
    std::vector<double> prices;
    std::vector<std::vector<double>> greeks; // Each element is a vector of {Delta, Gamma, Vega, Theta, Rho}

    for (const auto& option : options) {
        double price = (option.optionType == "call") ?
            blackScholesCall(option.stockPrice, option.strikePrice, option.timeToMaturity, option.riskFreeRate, option.volatility) :
            blackScholesPut(option.stockPrice, option.strikePrice, option.timeToMaturity, option.riskFreeRate, option.volatility);
        prices.push_back(price);

        double delta, gamma, vega, theta, rho;
        calculateGreeks(option, delta, gamma, vega, theta, rho);
        greeks.push_back({delta, gamma, vega, theta, rho});
    }

    std::cout << "Do you want to display only the option prices or the option prices along with the Greeks? (price/greeks): ";
    std::string choice;
    std::cin >> choice;
    bool showGreeks = (choice == "greeks");

    displayResults(options, prices, greeks, showGreeks);
    outputToCSV(options, prices, greeks);

    return 0;
}

// Function to get user input for an option
void getInput(OptionData& option) {
    std::cout << "Enter stock price (S): ";
    std::cin >> option.stockPrice;
    std::cout << "Enter strike price (K): ";
    std::cin >> option.strikePrice;
    std::cout << "Enter time to maturity (T in years): ";
    std::cin >> option.timeToMaturity;
    std::cout << "Enter risk-free rate (r): ";
    std::cin >> option.riskFreeRate;
    std::cout << "Enter volatility (sigma): ";
    std::cin >> option.volatility;
    std::cout << "Enter option type (call/put): ";
    while (true) {
        std::cin >> option.optionType;
        if (option.optionType == "call" || option.optionType == "put") {
            break;
        } else {
            std::cout << "Invalid option type. Please enter 'call' or 'put': ";
        }
    }
}

// Function to get options from the user
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

// Function to calculate the cumulative distribution function of the normal distribution
double normCDF(double x) {
    return 0.5 * std::erfc(-x * M_SQRT1_2);
}

// Helper function to calculate d1 and d2
void calculate_d1_d2(double S, double K, double T, double r, double sigma, double& d1, double& d2) {
    d1 = (std::log(S / K) + (r + 0.5 * sigma * sigma) * T) / (sigma * std::sqrt(T));
    d2 = d1 - sigma * std::sqrt(T);
}

// Function to calculate the price of a call option using the Black-Scholes formula
double blackScholesCall(double S, double K, double T, double r, double sigma) {
    double d1, d2;
    calculate_d1_d2(S, K, T, r, sigma, d1, d2);
    return S * normCDF(d1) - K * std::exp(-r * T) * normCDF(d2);
}

// Function to calculate the price of a put option using the Black-Scholes formula
double blackScholesPut(double S, double K, double T, double r, double sigma) {
    double d1, d2;
    calculate_d1_d2(S, K, T, r, sigma, d1, d2);
    return K * std::exp(-r * T) * normCDF(-d2) - S * normCDF(-d1);
}

// Function to calculate the Greeks of an option
void calculateGreeks(const OptionData& option, double& delta, double& gamma, double& vega, double& theta, double& rho) {
    double S = option.stockPrice;
    double K = option.strikePrice;
    double T = option.timeToMaturity;
    double r = option.riskFreeRate;
    double sigma = option.volatility;

    double d1, d2;
    calculate_d1_d2(S, K, T, r, sigma, d1, d2);

    double pdf = std::exp(-0.5 * d1 * d1) / std::sqrt(2 * M_PI);

    if (option.optionType == "call") {
        delta = normCDF(d1);
        theta = -((S * pdf * sigma) / (2 * std::sqrt(T))) - r * K * std::exp(-r * T) * normCDF(d2);
        rho = K * T * std::exp(-r * T) * normCDF(d2);
    } else {
        delta = normCDF(d1) - 1;
        theta = -((S * pdf * sigma) / (2 * std::sqrt(T))) + r * K * std::exp(-r * T) * normCDF(-d2);
        rho = -K * T * std::exp(-r * T) * normCDF(-d2);
    }
    gamma = pdf / (S * sigma * std::sqrt(T));
    vega = S * pdf * std::sqrt(T);
}

// Function to output the option data to a CSV file
void outputToCSV(const std::vector<OptionData>& options, const std::vector<double>& prices, const std::vector<std::vector<double>>& greeks) {
    std::ofstream file("option_data.csv");
    file << "Type,S,K,T,r,sigma,Price,Delta,Gamma,Vega,Theta,Rho\n";
    for (size_t i = 0; i < options.size(); ++i) {
        const auto& option = options[i];
        const auto& greek = greeks[i];
        file << option.optionType << ',' << option.stockPrice << ',' << option.strikePrice << ',' << option.timeToMaturity << ','
             << option.riskFreeRate << ',' << option.volatility << ',';
        file << prices[i] << ',' << greek[0] << ',' << greek[1] << ',' << greek[2] << ',' << greek[3] << ',' << greek[4] << '\n';
    }
    file.close();
}

// Function to display the results to the console
void displayResults(const std::vector<OptionData>& options, const std::vector<double>& prices, const std::vector<std::vector<double>>& greeks, bool showGreeks) {
    const int typeWidth = 11;
    const int numWidth = 9; 

    std::cout << std::fixed << std::setprecision(4); // Set precision for floating-point numbers
    if (showGreeks) {
        std::cout << "+-" << std::string(typeWidth, '-') << "-+";
        std::cout << std::string(numWidth + 2, '-') << "+";
        std::cout << std::string(numWidth + 2, '-') << "+";
        std::cout << std::string(numWidth + 2, '-') << "+";
        std::cout << std::string(numWidth + 2, '-') << "+";
        std::cout << std::string(numWidth + 2, '-') << "+";
        std::cout << std::string(numWidth + 2, '-') << "+\n";

        std::cout << "| " << std::setw(typeWidth) << "Option Type" << " | "
                  << std::setw(numWidth) << "Price" << " | "
                  << std::setw(numWidth) << "Delta" << " | "
                  << std::setw(numWidth) << "Gamma" << " | "
                  << std::setw(numWidth) << "Vega" << " | "
                  << std::setw(numWidth) << "Theta" << " | "
                  << std::setw(numWidth) << "Rho" << " |\n";

        std::cout << "+-" << std::string(typeWidth, '-') << "-+";
        std::cout << std::string(numWidth + 2, '-') << "+";
        std::cout << std::string(numWidth + 2, '-') << "+";
        std::cout << std::string(numWidth + 2, '-') << "+";
        std::cout << std::string(numWidth + 2, '-') << "+";
        std::cout << std::string(numWidth + 2, '-') << "+";
        std::cout << std::string(numWidth + 2, '-') << "+\n";

        for (size_t i = 0; i < options.size(); ++i) {
            const auto& option = options[i];
            const auto& greek = greeks[i];
            std::cout << "| " << std::setw(typeWidth) << option.optionType << " | "
                      << std::setw(numWidth) << prices[i] << " | "
                      << std::setw(numWidth) << greek[0] << " | "
                      << std::setw(numWidth) << greek[1] << " | "
                      << std::setw(numWidth) << greek[2] << " | "
                      << std::setw(numWidth) << greek[3] << " | "
                      << std::setw(numWidth) << greek[4] << " |\n";
        }

        std::cout << "+-" << std::string(typeWidth, '-') << "-+";
        std::cout << std::string(numWidth + 2, '-') << "+";
        std::cout << std::string(numWidth + 2, '-') << "+";
        std::cout << std::string(numWidth + 2, '-') << "+";
        std::cout << std::string(numWidth + 2, '-') << "+";
        std::cout << std::string(numWidth + 2, '-') << "+";
        std::cout << std::string(numWidth + 2, '-') << "+\n";
    } else {
        for (size_t i = 0; i < options.size(); ++i) {
            const auto& option = options[i];
            std::cout << "The price of the " << option.optionType << " option is: " << prices[i] << std::endl;
        }
    }
}
