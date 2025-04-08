import numpy as np

mean_lead_time = 3.7

def generate_exponential_lead_time(mean):
    """Generates a random lead time from an exponential distribution."""
    R = np.random.uniform(0, 1)
    lead_time = -mean * np.log(1-R)
    return lead_time

# Generate 5 random lead times
random_lead_times = [generate_exponential_lead_time(mean_lead_time) for _ in range(5)]

# Print the results
for i, lead_time in enumerate(random_lead_times):
    print(f"Lead Time {i + 1}: {lead_time:.2f} days")
