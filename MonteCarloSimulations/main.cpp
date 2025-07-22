#include <iostream>
#include <random>
#include <cmath>
#include <vector>
#include <chrono>

// Function to generate a random number from normal distribution using Box-Muller
double gaussian_box_muller(std::mt19937& gen) {
    static std::uniform_real_distribution<double> dist(0.0, 1.0);
    double u1 = dist(gen);
    double u2 = dist(gen);
    return std::sqrt(-2.0 * std::log(u1)) * std::cos(2.0 * M_PI * u2);
}

// Monte Carlo simulation for European Call Option
double monte_carlo_call_price(
    double S0,    // Initial stock price
    double K,     // Strike price
    double T,     // Time to maturity
    double r,     // Risk-free rate
    double sigma, // Volatility
    int num_sims  // Number of simulations
) {
    // Set up random number generation
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 gen(seed);

    double sum_payoff = 0.0;

    // Run Monte Carlo simulations
    for (int i = 0; i < num_sims; ++i) {
        // Generate random price path
        double gaussian = gaussian_box_muller(gen);
        // Calculate stock price at maturity using Black-Scholes dynamics
        double ST = S0 * std::exp((r - 0.5 * sigma * sigma) * T + sigma * std::sqrt(T) * gaussian);

        // Calculate payoff for call option: max(ST - K, 0)
        double payoff = std::max(ST - K, 0.0);
        sum_payoff += payoff;
    }

    // Calculate option price: discount average payoff
    double option_price = std::exp(-r * T) * (sum_payoff / num_sims);
    return option_price;
}

int main() {
    // Option parameters
    double S0 = 100.0;    // Initial stock price
    double K = 100.0;     // Strike price
    double T = 1.0;       // Time to maturity (1 year)
    double r = 0.05;      // Risk-free rate (5%)
    double sigma = 0.2;   // Volatility (20%)
    int num_sims = 1000000; // Number of simulations

    // Calculate option price
    double price = monte_carlo_call_price(S0, K, T, r, sigma, num_sims);

    // Output result
    std::cout << "European Call Option Price: " << price << std::endl;

    return 0;
}
