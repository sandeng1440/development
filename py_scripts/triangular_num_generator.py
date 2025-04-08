import numpy as np

def triangular_generator(a, c, b):
    """Generates a random variate from a triangular distribution."""
    U = np.random.uniform(0, 1)

    if U <= (c - a) / (b - a):
        X = a + np.sqrt(U * (b - a) * (c - a))
    else:
        X = b - np.sqrt((1 - U) * (b - a) * (b - c))
    return X

# Parameters
a = 1
c = 4
b = 10

# Generate 1000 random variates
random_variates = [triangular_generator(a, c, b) for _ in range(1000)]

# Calculate the sample mean
sample_mean = np.mean(random_variates)

# Calculate the true mean
true_mean = (a + b + c) / 3

# Print results
print(f"Sample Mean: {sample_mean}")
print(f"True Mean: {true_mean}")
