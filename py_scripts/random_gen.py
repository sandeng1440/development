import numpy as np

for i in range(5):
    R = round(np.random.uniform(0,1),2)
    X = -3.7 * np.log(1-R)
    print(f"R{i} = -3.7ln(1- {R} ) = {X}")

