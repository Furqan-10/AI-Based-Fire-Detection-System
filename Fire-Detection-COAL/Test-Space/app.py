import joblib
import gradio as gr

# Load model (make sure 'fire_detection_model.pkl' is uploaded)
model = joblib.load("fire_detection_model.pkl")

def predict_fire(temperature):
    try:
        prediction = model.predict([[float(temperature)]])
        return "🔥 FIRE DETECTED!" if prediction[0] == 1 else "✅ Normal"
    except Exception as e:
        return f"Error: {str(e)}"

# Create interface
interface = gr.Interface(
    fn=predict_fire,
    inputs=gr.Number(label="Enter Temperature (°C)"),
    outputs=gr.Label(label="Status"),
    title="Fire Detection System",
    description="Enter a temperature value to check for fire risk.",
    examples=[[75], [150], [200]]
)

interface.launch()
