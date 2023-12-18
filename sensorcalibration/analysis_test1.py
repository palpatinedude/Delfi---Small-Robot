import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
from sklearn.metrics import mean_squared_error
from scipy.optimize import minimize

# Load and calibrate data
csv_path = 'calibration.ino\data.csv'
df = pd.read_csv(csv_path)

dat_vec = df['Distance(cm)'].values
x_poly = df['Actual Distance(cm)'].values
order_num = 2

# Initial calibration
poly_fit = np.polyfit(dat_vec, x_poly, order_num)
calibrated_distances = np.polyval(poly_fit, dat_vec)

# Save the calibrated data to a new CSV file
df['Calibrated Distance(cm)'] = calibrated_distances
df.to_csv('initial.csv', index=False)

# Evaluate RMSE for initial calibration
rmse = np.sqrt(mean_squared_error(x_poly, calibrated_distances))
print(f'Root Mean Squared Error (RMSE) for Initial Calibration: {rmse}')

# Plot comparison of actual and calibrated distances
plt.figure(figsize=(12, 9))
plt.scatter(dat_vec, x_poly, label='Actual', color='#3a2a29', s=80, alpha=0.8)
plt.scatter(dat_vec, calibrated_distances, label='Calibrated', color='#b39a7c', s=80, alpha=0.8)
plt.xlabel('Distance (cm)')
plt.ylabel('Distance (cm)')
plt.title('Comparison of Actual and Calibrated Distances')
plt.legend()
plt.show()

# Load the calibrated data
csv_path = 'initial.csv'
df_calibrated = pd.read_csv(csv_path)
calibrated_distances = df_calibrated['Calibrated Distance(cm)'].values
actual_distances = df_calibrated['Actual Distance(cm)'].values
order_num = 2

# Define objective function for optimization
def objective(coefficients, x, y):
    predicted_values = np.polyval(coefficients, x)
    mse = mean_squared_error(y, predicted_values)
    return mse

# Initial guess for optimization
initial_guess = np.zeros(order_num + 1)

# Optimize coefficients
result = minimize(objective, initial_guess, args=(calibrated_distances, actual_distances), method='Nelder-Mead')
optimal_coefficients = result.x


# Plot comparison of actual and optimized calibrated distances
plt.figure(figsize=(10, 6))
plt.scatter(calibrated_distances, actual_distances, label='Actual Results', marker='o', alpha=0.8)
plt.scatter(calibrated_distances, np.polyval(optimal_coefficients, calibrated_distances), label='Original Calibrated Results', marker='x', alpha=0.8)
plt.plot(calibrated_distances, np.polyval(optimal_coefficients, calibrated_distances), color='green', linestyle='--', label='Optimized Calibration')
plt.xlabel('Calibrated Distance')
plt.ylabel('Actual Distance')
plt.title('Comparison of Calibrated and Actual Distances with Optimized Calibration')
plt.legend()
plt.show()

# Apply optimized calibration to new data
dat_vec_to_predict = df['Actual Distance(cm)'].values 
calibrated_distances_to_predict = np.polyval(optimal_coefficients, dat_vec_to_predict)
rmse = np.sqrt(mean_squared_error(df['Actual Distance(cm)'], calibrated_distances_to_predict))
formatted_optimal_coefficients = [f'{coef:.3f}' for coef in optimal_coefficients]
df['Calibrated Distance(cm)'] = calibrated_distances_to_predict

# Print RMSE for optimized calibration
print("Root Mean Squared Error  optimized(RMSE):", rmse)
print("Optimized Coefficients:", formatted_optimal_coefficients)

# Plot comparison of actual and optimized calibrated distances for new data
plt.figure(figsize=(10, 6))
plt.scatter(df['Pulse Duration(ms)'], df['Actual Distance(cm)'], label='Actual Distances', color='blue', marker='o')
plt.plot(df['Pulse Duration(ms)'], calibrated_distances_to_predict, label='Calibrated Distances', color='red', linewidth=2)
plt.title('Actual vs Calibrated Distances')
plt.xlabel('Pulse Duration(ms)')
plt.ylabel('Distance (cm)')
plt.legend()
plt.grid(True)
plt.show()

plt.figure(figsize=(10, 6))


plt.scatter(df['Distance(cm)'], df['Actual Distance(cm)'], label='Actual Distances', color='blue', marker='o')
plt.scatter(df['Distance(cm)'], calibrated_distances_to_predict, label='Optimized Calibrated Distances', color='red', marker='o', alpha=0.8)

plt.title('Comparison of Actual  and Optimized Calibrated Distances')
plt.xlabel('Initial Distance (cm)')
plt.ylabel('Calibrated Distance (cm)')
plt.legend()
plt.grid(True)
plt.show()

