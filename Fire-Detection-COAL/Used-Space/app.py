from fastapi import FastAPI, Request
from pydantic import BaseModel
import joblib

app = FastAPI()

# Load your trained model (replace with actual path if needed)
model = joblib.load("fire_detection_model.pkl")

class TempInput(BaseModel):
    temperature: float

@app.post("/predict")
async def predict_fire(data: TempInput):
    prediction = model.predict([[data.temperature]])
    return {"prediction": prediction[0]}