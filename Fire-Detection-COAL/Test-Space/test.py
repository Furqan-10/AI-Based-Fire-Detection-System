import joblib
model = joblib.load("fire_detection_model.pkl")
prediction = model.predict([[5]])  # Returns 1 (Fire) or 0 (Normal)
print(prediction)