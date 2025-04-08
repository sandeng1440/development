import numpy as np

def generate_random_variate():
    """Generates a random variate from the given CDF."""
    R = np.random.uniform(0, 1)
    return 2 * (R ** 0.25)

# Generate 1000 random variates
random_variates = [generate_random_variate() for _ in range(1000)]

# Calculate the sample mean
sample_mean = np.mean(random_variates)
true_mean = 1.6
stdev =np.std(random_variates)
diff = abs(sample_mean - true_mean)
within = True if diff < stdev else False

# Print results
print(f"Sample Mean: {sample_mean}")
print(f"True Mean: {true_mean}")
print(f"Std Dev: {stdev}")
print(f"Within STD: {within}")
