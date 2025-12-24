const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
    <title>Soil Monitor</title>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <style>
        :root { --primary: #2d5a27; --bg: #f0f4f0; }
        body { font-family: sans-serif; background: var(--bg); margin: 0; padding: 20px; display: flex; justify-content: center; }
        .container { max-width: 600px; width: 100%; background: white; padding: 25px; border-radius: 20px; box-shadow: 0 10px 30px rgba(0,0,0,0.1); }
        h1 { color: var(--primary); text-align: center; }
        .grid { display: grid; grid-template-columns: 1fr 1fr; gap: 10px; margin-bottom: 20px; padding: 1em; }
        .card { background: #fafafa; padding: 12px; border-radius: 10px; border-left: 5px solid var(--primary); }
        .label { font-size: 0.7rem; color: #888; text-transform: uppercase; }
        .value { font-size: 1.2rem; font-weight: bold; display: block; }
        .search-box { border-top: 1px solid #eee; padding-top: 20px; text-align: center; }
        input { padding: 10px; width: 60%; border-radius: 5px; border: 1px solid #ccc; }
        button { padding: 10px 15px; background: var(--primary); color: white; border: none; border-radius: 5px; cursor: pointer; }
        #result { margin-top: 15px; padding: 15px; border-radius: 8px; display: none; }
        .msg-box { display: block !important; border: 1px solid #ccc; }
    </style>
</head>
<body>
    <div class="container">
        <h1>Soil Status</h1>
        <div class="grid">
            <div class="card"><span class="label">Humidity</span> : <span class="value">%HUMID% &percnt;</span></div>
            <div class="card"><span class="label">Temp</span> : <span class="value">%TEMP% °C</span></div>
            <div class="card"><span class="label">pH</span> : <span class="value">%PH%</span></div>
            <div class="card"><span class="label">EC</span> : <span class="value">%EC%</span></div>
            <div class="card"><span class="label">Nitrogen (N)</span> : <span class="value">%N%</span></div>
            <div class="card"><span class="label">Phospho (P)</span> : <span class="value">%P%</span></div>
            <div class="card"><span class="label">Potass (K)</span> : <span class="value">%K%</span></div>
        </div>

        <div class="search-box">
            <h3>Plant Compatibility</h3>
            <input type="text" id="plantIn" placeholder="e.g. Tomato">
            <button onclick="check()">Check</button>
            <div id="result" class="msg-box">Enter a plant name to check compatibility with current pH.</div>
        </div>
    </div>
        <script>
        const db = {
            "tomato": { min: 6.0, max: 6.8, info: "Needs slightly acidic soil." },
            "lavender": { min: 6.7, max: 7.3, info: "Likes alkaline soil and sun." },
            "rice": { min: 5.5, max: 6.5, info: "Needs acidic soil and plenty of water." }
        };

        function check() {
            const name = document.getElementById('plantIn').value.toLowerCase();
            const res = document.getElementById('result');
            // We pull the PH value directly from the HTML text that the ESP32 filled in
            const currentPH = parseFloat("%PH%") || 0;

            res.style.display = "block";
            if (db[name]) {
                const p = db[name];
                if (currentPH >= p.min && currentPH <= p.max) {
                    res.innerHTML = "<strong>✅ Match!</strong><br>" + p.info;
                    res.style.backgroundColor = "#e8f5e9";
                } else {
                    res.innerHTML = "<strong>❌ Not Ideal.</strong><br>Current pH is " + currentPH + ". " + name + " needs " + p.min + "-" + p.max;
                    res.style.backgroundColor = "#fff3e0";
                }
            } else {
                res.innerHTML = "Plant not found. Try: Tomato, Rice, or Lavender.";
                res.style.backgroundColor = "#eee";
            }
        }
    </script>
</body>
</html>
)rawliteral";