import numpy as np
import scipy.stats as stats
import matplotlib
matplotlib.use('Agg')  # Use the 'Agg' backend for file-only operations
import matplotlib.pyplot as plt

# Parameters for toy experiment
measured_mean = 6.  # Measured mean value
positive_uncertainty = 4.0  # Positive asymmetric error
negative_uncertainty = 4.0  # Negative asymmetric error
num_toys = 1000     # Number of toy experiments
reference_value = 0   # Reference value for significance calculation

# Step 1: Generate toy datasets for positive and negative uncertainties
toy_datasets_positive = np.random.normal(loc=measured_mean, scale=positive_uncertainty, size=num_toys)
toy_datasets_negative = np.random.normal(loc=measured_mean, scale=negative_uncertainty, size=num_toys)

# Combine the datasets from both uncertainties
toy_datasets_combined = np.concatenate((toy_datasets_positive, toy_datasets_negative))

# Step 2: Count how many toy datasets are more extreme than the reference value (0)
extreme_toys = np.sum(toy_datasets_combined <= reference_value)

# Step 3: Calculate the fraction of extreme toy datasets
fraction_extreme = extreme_toys / float(len(toy_datasets_combined))

# Step 4: Convert the fraction to a significance level (number of sigma)
# We use the inverse of the cumulative distribution function (percent point function) of the normal distribution
significance = stats.norm.ppf(1 - fraction_extreme)

# Plot the results
plt.figure(figsize=(8, 6))

# Plot histogram of combined toy datasets
plt.hist(toy_datasets_combined, bins=50, normed=True, alpha=0.6, color='g', label='Combined Toy Datasets')

# Plot the reference value (0)
plt.axvline(reference_value, color='r', linestyle='dashed', linewidth=2, label='Reference Value')

# Add labels and legend
plt.xlabel('Value')
plt.ylabel('Density')
#plt.title('Toy Dataset Distribution with Asymmetric Errors and Reference Value')
#plt.legend()

# Save the figure to a PDF
plt.savefig('toy_experiment_results_asymmetric_errors.pdf', format='pdf')

# Results
print("Fraction of toys more extreme than the reference value: {}".format(fraction_extreme))
print("Significance (sigma level): {}".format(significance))


