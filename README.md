# MonteCarloSimulation

This code implements a Monte Carlo simulation for a European call option using the Black-Scholes model. Here's how it works:

The gaussian_box_muller function generates normally distributed random numbers using the Box-Muller transform.
The monte_carlo_call_price function:
Takes option parameters (initial stock price, strike price, time to maturity, risk-free rate, volatility, number of simulations)
Simulates stock price paths using the geometric Brownian motion model
Calculates the payoff for each path
Returns the discounted average payoff as the option price
The main function sets example parameters and runs the simulation.
To extend this for exotic options (e.g., Asian options, Barrier options), you would modify the payoff calculation or price path generation. For example:

For an Asian option, track the average price over the path instead of just the terminal price.
For a Barrier option, check if the price crosses a barrier level during the path.
