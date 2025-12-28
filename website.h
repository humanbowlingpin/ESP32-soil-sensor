const char style_css[] PROGMEM = R"rawliteral(
:root {
	--primary: #2d5a27;
	--bg: #f0f4f0;
}

@font-face {
	font-family: perth;
	src: url(https://humanbowlingpin.github.io/random/soopafresh/soopafre.ttf);
}

@font-face {
  font-family: JetBrainsMono;
  src: url(https://humanbowlingpin.github.io/random/jetbrain/JetBrainsMono-Regular.ttf);
  font-weight: normal;
  font-style: normal;
}

@font-face {
  font-family: JetBrainsMono;
  src: url(https://humanbowlingpin.github.io/random/jetbrain/JetBrainsMono-Italic.ttf);
  font-weight: normal;
  font-style: italic;
}

@font-face {
  font-family: JetBrainsMono;
  src: url(https://humanbowlingpin.github.io/random/jetbrain/JetBrainsMono-ExtraBold.ttf);
  font-weight: bold;
  font-style: normal;
}

@font-face {
  font-family: JetBrainsMono;
  src: url(https://humanbowlingpin.github.io/random/jetbrain/JetBrainsMono-ExtraBoldItalic.ttf);
  font-weight: bold;
  font-style: italic;
}

* {
	font-family: JetBrainsMono;
}

body {
	font-family: JetBrainsMono;
	background: url(https://files.catbox.moe/hd2x67.png);
	background-size: cover;
	background-repeat: no-repeat;
	margin: 0;
	padding: 20px;
	display: flex;
	letter-spacing: -0.5px;
	justify-content: center;
}

.container {
	max-width: 600px;
	width: 100%;
	background: white;
	padding: 25px;
	border-radius: 20px;
	box-shadow: 0 10px 30px rgba(0, 0, 0, 0.4);
}

h1, h3 {
	font-family: perth;
	color: var(--primary);
	text-align: center;
	letter-spacing: 0;
}

.grid {
	display: grid;
	grid-template-columns: 1fr 1fr;
	gap: 10px;
	margin-bottom: 20px;
	padding: 1em;
}

.card {
	background: #fafafa;
	padding: 12px;
	border-radius: 10px;
	border: 2px solid var(--primary);
	/* border-left: 5px solid var(--primary); */
}

.label {
	font-size: 0.7rem;
	color: #888;
	text-transform: uppercase;
}

.value {
	font-size: 1.2rem;
	font-weight: bold;
	display: block;
}

.search-box, .recommend-box {
	margin-top: 1em;
	border-top: 1px solid #eee;
	padding-top: 20px;
	text-align: center;
}

input {
	padding: 10px;
	width: 60%;
	border-radius: 5px;
	border: 1px solid #ccc;
}

button {
	padding: 10px 15px;
	background: var(--primary);
	color: white;
	border: none;
	border-radius: 5px;
	cursor: pointer;
}

.improve-box {
	display: none;
	text-align: left;
	margin: 0 auto;
	max-width: 450px;
}

.msg-box, .recmsg-box {
	display: block;
	border: 1px solid #ccc;
	margin-top: 15px;
	padding: 15px;
	border-radius: 8px;
}
)rawliteral";

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
    <title>Soil Monitor</title>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <link rel="stylesheet" href="/style.css">
</head>
<body>
    <div class="container">
        <h1>Soil Status</h1>
        <div class="grid">
            <div class="card"><span class="label">Humidity</span> : <span class="value">%HUMID% &percnt;</span></div>
            <div class="card"><span class="label">Temp</span> : <span class="value">%TEMP% °C</span></div>
            <div class="card"><span class="label">pH</span> : <span class="value">%PH%</span></div>
            // <div class="card"><span class="label">EC</span> : <span class="value">%EC%</span></div>
            <div class="card"><span class="label">Nitrogen (N)</span> : <span class="value">%N%</span></div>
            <div class="card"><span class="label">Phosphorus (P)</span> : <span class="value">%P%</span></div>
            <div class="card"><span class="label">Potassium (K)</span> : <span class="value">%K%</span></div>
        </div>

        <div class="recommend-box">
            <h3>Recommended Plants</h3>
            <div class="recmsg-box" id="recommend"></div>
        </div>
        <div class="search-box">
            <h3>Plant Compatibility</h3>
            <input type="text" id="plantIn" placeholder="e.g. Tomato">
            <button onclick="check()">Check</button>
            <div id="resultCon" class="msg-box">
                <div id="result">Enter a plant name to check compatibility with current pH.</div>
                <div id="improvement" class="improve-box"></div>
            </div>
        </div>
    </div>
    <script>
        const db = {
            "tomato": { minPH: 6.0, maxPH: 6.8, info: "Needs slightly acidic soil.", N: 23, P: 30, K: 45 },
            "lavender": { minPH: 6.7, maxPH: 7.3, info: "Likes alkaline soil and sun.", N: 23, P: 30, K: 45 },
            "rice": { minPH: 5.5, maxPH: 6.5, info: "Needs acidic soil and plenty of water.", N: 23, P: 30, K: 45 }
        };

        const currentSoil = {
            PH: parseFloat("%PH%") || 0,
            N: parseFloat("%N%") || 0,
            P: parseFloat("%P%") || 0,
            K: parseFloat("%K%") || 0
        };

        function getPlantStatus(plant) {
            const status = {
                idealPH: currentSoil.PH >= plant.minPH && currentSoil.PH <= plant.maxPH,
                idealN: currentSoil.N >= plant.N,
                idealP: currentSoil.P >= plant.P,
                idealK: currentSoil.K >= plant.K
            };
            status.isAllMatch = Object.values(status).every(v => v === true);
            return status;
        }

        function getSuitablePlants() {
            const result = Object.entries(db)
                .filter(([name, plant]) => getPlantStatus(plant).isAllMatch)
                .map(([name]) => name);

            const rec = document.querySelector('#recommend');
            rec.innerHTML = result.length === 0 
                ? "We did not find a suitable plant." 
                : `The dirt is suitable for planting: ${result.join(", ")}`;
        }

        function check() {
            const name = document.querySelector('#plantIn').value.toLowerCase();
            const resbox = document.querySelector('#resultCon');
            const res = document.querySelector('#result');
            const improve = document.querySelector('#improvement');

            improve.style.display = "none";

            const plant = db[name];
            if (!plant) {
                res.innerHTML = "Plant not found.";
                resbox.style.backgroundColor = "#eee";
                return;
            }

            const status = getPlantStatus(plant);
            const capName = name.charAt(0).toUpperCase() + name.slice(1);

            if (status.isAllMatch) {
                res.innerHTML = `<strong>✅ Match!</strong><br>${plant.info}`;
                resbox.style.backgroundColor = "#e8f5e9";
            } else {
                res.innerHTML = `<strong>❌ Not Ideal.</strong>`;
                resbox.style.backgroundColor = "#fff3e0";

                const feedback = [];
                if (!status.idealPH) feedback.push(`Current pH is ${currentSoil.PH}. ${capName} needs ${plant.minPH}-${plant.maxPH}.`);
                if (!status.idealN)  feedback.push(`Current Nitrogen is ${currentSoil.N}. Needs at least ${plant.N}.`);
                if (!status.idealP)  feedback.push(`Current Phosphorus is ${currentSoil.P}. Needs at least ${plant.P}.`);
                if (!status.idealK)  feedback.push(`Current Potassium is ${currentSoil.K}. Needs at least ${plant.K}.`);

                improve.innerHTML = feedback.join("<br>");
                improve.style.display = "block";
            }
        }

        getSuitablePlants();
    </script>
</body>
</html>
)rawliteral";