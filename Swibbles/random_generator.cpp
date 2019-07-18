#include "random_generator.hpp"

#include <random>

int random_between(int min, int max) {
	std::random_device random_device;															// Generate random device
	std::seed_seq seed{ random_device(), random_device(), random_device(), random_device() };	// Generate random seed
	std::mt19937 engine{ seed };																// Seed Mersenne Twister engine
	return std::uniform_int_distribution<>(min, max)(engine);
}