import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from sklearn.model_selection import train_test_split, cross_val_score
from sklearn.linear_model import LinearRegression
from sklearn.metrics import mean_squared_error, r2_score

file_path = 'data.csv'
df = pd.read_csv(file_path)


actual_distances = df['Actual'].values.reshape(-1, 1)
recorded_distances = df['Recorded'].values.reshape(-1, 1)


train_recorded, val_recorded, train_actual, val_actual = train_test_split(
    recorded_distances, actual_distances, test_size=0.3, random_state=42
)

# Before Linear Regression
mse_before = mean_squared_error(val_actual, val_recorded) 


print(f'Mean Squared Error before Linear Regression: {mse_before:.2f}')


X = recorded_distances
y = actual_distances.flatten()


model = LinearRegression()
cv_r2_scores = cross_val_score(model, X, y, cv=5, scoring='r2')
cv_mse_scores = -cross_val_score(model, X, y, cv=5, scoring='neg_mean_squared_error')  

print(f'Cross-Validation R-squared scores: {cv_r2_scores}')
print(f'Cross-Validation Mean Squared Error scores: {cv_mse_scores}')

print(f'Mean Cross-Validation Mean Squared Error: {np.mean(cv_mse_scores):.2f}')


model.fit(recorded_distances, actual_distances)
val_predictions = model.predict(val_recorded)

# After Linear Regression
mse_after = mean_squared_error(val_actual, val_predictions)
print(f'Mean Squared Error after Linear Regression: {mse_after:.2f}')



print(f'Coefficients after Linear Regression: {model.coef_[0][0]:.2f}')
print(f'Intercept after Linear Regression: {model.intercept_[0]:.2f}')

error_recorded = np.abs(val_actual - val_recorded)
error_predicted = np.abs(val_actual - val_predictions)


plt.figure(figsize=(10, 6))
bar_width = 0.35
index = np.arange(len(error_recorded))

plt.bar(index, error_recorded.flatten(), bar_width, label='Actual vs Recorded')
plt.bar(index + bar_width, error_predicted.flatten(), bar_width, label='Actual vs Predicted')

plt.xlabel('Measurement')
plt.ylabel('Absolute Error')
plt.title('Error Comparison: Actual vs Recorded vs Predicted')
plt.xticks(index + bar_width / 2, range(len(error_recorded)))
plt.legend()
plt.show()

plt.plot(val_actual, label='Actual', marker='o')
plt.plot(val_predictions, label='Predicted', marker='x')
plt.xlabel('Data Points')
plt.ylabel('Distances')
plt.title('Actual vs. Predicted Line Plot')
plt.legend()
plt.show()


plt.scatter(val_actual, val_recorded, color='blue', label='Actual vs. Recorded')
plt.scatter(val_actual, val_predictions, color='red', label='Actual vs. Predicted')
plt.xlabel('Actual Distances')
plt.ylabel('Distances')
plt.title('Comparison of Actual, Recorded, and Predicted Distances')
plt.legend()
plt.show()


# Residual Analysis
residuals = val_actual - val_predictions

# Plotting the Residuals
plt.figure(figsize=(10, 6))
plt.scatter(val_predictions, residuals, color='blue', marker='o', label='Residuals')
plt.axhline(y=0, color='r', linestyle='-', label='Zero Residuals Line')
plt.title('Residual Analysis')
plt.xlabel('Predicted Values')
plt.ylabel('Residuals')
plt.legend()
plt.show()

# Histogram of Residuals
plt.figure(figsize=(10, 6))
plt.hist(residuals, bins=30, edgecolor='black')
plt.title('Histogram of Residuals')
plt.xlabel('Residuals')
plt.ylabel('Frequency')
plt.show()
