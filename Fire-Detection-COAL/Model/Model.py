import pandas as pd
from sklearn.model_selection import train_test_split
from sklearn.ensemble import RandomForestClassifier
from sklearn.metrics import accuracy_score, confusion_matrix
import joblib

# Step 1: Load dataset
df = pd.read_csv('fire_temperature_dataset.csv')

# Step 2: Split features and labels
X = df[['Temperature']]
y = df['Fire']

# Step 3: Train/Test split
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)

# Step 4: Train the model (Random Forest for reliability)
model = RandomForestClassifier(n_estimators=100, random_state=42)
model.fit(X_train, y_train)

# Step 5: Evaluate
y_pred = model.predict(X_test)
accuracy = accuracy_score(y_test, y_pred)
print(f"Accuracy: {accuracy * 100:.2f}%")
print("Confusion Matrix:\n", confusion_matrix(y_test, y_pred))

# Step 6: Save model for cloud deployment later
joblib.dump(model, 'fire_detection_model.pkl')
print("Model saved as 'fire_detection_model.pkl'")
