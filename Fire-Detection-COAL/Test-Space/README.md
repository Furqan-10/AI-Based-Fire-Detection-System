---
title: Fire Detection (Temperature)
emoji: 🔥
colorFrom: red
colorTo: yellow
sdk: gradio
sdk_version: "3.39.0"
app_file: app.py
pinned: false
---

# Temperature-Based Fire Detection Model

A `RandomForestClassifier` model to detect fire using temperature sensor data.

## Usage
```python
import joblib
model = joblib.load("fire_detection_model.pkl")
prediction = model.predict([[temperature_in_celsius]])  # Returns 1 (Fire) or 0 (Normal)