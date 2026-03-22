const char style_css[] PROGMEM = R"rawliteral(
:root {
	--primary: #2d5a27;
	--bg: #f0f4f0;
}

@import url('https://fonts.googleapis.com/css2?family=Kanit:ital,wght@0,100;0,200;0,300;0,400;0,500;0,600;0,700;0,800;0,900;1,100;1,200;1,300;1,400;1,500;1,600;1,700;1,800;1,900&display=swap');

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

button, input {
	font-family: JetBrainsMono, Kanit;
}

body {
	font-family: JetBrainsMono, Kanit;
	background: url(https://files.catbox.moe/gilx27.png);
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
	background: #e2f3e2;
	padding: 25px;
	border-radius: 20px;
	box-shadow: 0 10px 30px rgba(0, 0, 0, 0.4);
}

h1, h3 {
	font-family: perth, Kanit !important;
	color: var(--primary);
	text-align: center;
	letter-spacing: 1px;
}

h3 {
    font-size: 1.5em;
    margin-top: 0em;
}

.grid {
	display: grid;
	grid-template-columns: 1fr 1fr 1fr;
	gap: 10px;
	margin-bottom: 20px;
	padding: 1em;
}

.grid .card:last-child {
    grid-column: 2;
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

.search-box {
    border: 2px solid var(--primary);
    border-radius: 15px;
    padding: 25px 20px 20px;
    background-color: white;
    position: relative;
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
}

.msg-box, .recmsg-box {
	display: block;
	border: 1px solid #ccc;
	margin-top: 15px;
	padding: 15px;
	border-radius: 8px;
}

.recmsg-box {
    border: 2px solid var(--primary);
    background-color: white;
}

html[lang="en"] *[lang]:not([lang="en"]) {
  display: none;
}

html[lang="th"] *[lang]:not([lang="th"]) {
  display: none;
}

.suggestions {
    border: 1px solid var(--primary);
    background: var(--bg);
    position: absolute;
    left: 5em;
    max-height: 10em;
    overflow-y: auto;
    display: none;
    z-index: 999;
}

.suggestion-item {
    padding: 6px 10px;
    cursor: pointer;
}

.suggestion-item:hover {
    background-color: #e5f5e5;
}

table, th, td {
	border: 1px solid black;
	border-collapse: collapse;
}

th, td {
  padding: .5em;
}

tr > *:first-child, td {
	text-align: left;
}

@media (max-width: 500px) {
    .grid {
        grid-template-columns: 1fr 1fr;
    }
	.container {
		padding: 1em;
		border-radius: 0;
	}
	body {
		padding: 0;
	}
	.suggestions {
		left: 2em;
	}
}
)rawliteral";

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="en">
<head>
    <title>Soil Monitor</title>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <link rel="stylesheet" href="/style.css">
    <link rel="preconnect" href="https://fonts.googleapis.com">
<link rel="preconnect" href="https://fonts.gstatic.com" crossorigin>
<link href="https://fonts.googleapis.com/css2?family=Kanit:ital,wght@0,100;0,200;0,300;0,400;0,500;0,600;0,700;0,800;0,900;1,100;1,200;1,300;1,400;1,500;1,600;1,700;1,800;1,900&display=swap" rel="stylesheet">
</head>
<body>
    <div class="container">
        <h1 style="font-family: Kanit"><span lang="en">Soil Status</span><span lang="th">ตรวจวัดสถานะดิน</span></h1>
        <div class="language-picker"><button id="language-switcher">thai / ภาษาไทย</button></div>
        <div class="grid">
            <div class="card"><span class="label"><span lang="en">Humidity</span><span lang="th">ความชื้น</span></span> : <span class="value">%HUMID% &percnt;</span></div>
            <div class="card"><span class="label"><span lang="en">Temperature</span><span lang="th">อุณหภูมิ</span></span> : <span class="value">%TEMP% °C</span></div>
            <div class="card"><span class="label">pH</span> : <span class="value">%PH%</span></div>
            <div class="card"><span class="label"><span lang="en">Nitrogen</span><span lang="th">ไนโตรเจน</span> (N)</span> : <span class="value">%N% mg/kg</span></div>
            <div class="card"><span class="label"><span lang="en">Phosphorus</span><span lang="th">ฟอสฟอรัส</span> (P)</span> : <span class="value">%P% mg/kg</span></div>
            <div class="card"><span class="label"><span lang="en">Potassium</span><span lang="th">โพแทสเซี่ยม</span> (K)</span> : <span class="value">%K% mg/kg</span></div>
            <div class="card"><span class="label">EC</span> : <span class="value">%EC% &micro;S/cm</span></div>
        </div>
        <p><span lang="en">information at</span><span lang="th">ข้อมู​ล ณ​ เวลา</span> <span id="time"></span></p>

        <div class="search-box">
            <h3><span lang="en">Plant Compatibility</span><span lang="th">ตรวจสอบความเข้ากันของพืชและดิน</span></h3>
            <input type="text" id="plantIn" placeholder="e.g. Tomato">
            <div id="suggestions" class="suggestions"></div>
            <button onclick="check()">Check</button>
            <div id="resultCon" class="msg-box">
                <div id="result"><span lang="en">Enter a plant name to check dirt compatibility.</span><span lang="th">กรอกชื่อพืชเพื่อตรวจสอบความเข้ากันของดิน</span></div>
                <div id="improvement" class="improve-box"></div>
            </div>
            <details style="text-align: left;margin-top: 1em;">
                <summary><span lang="en">Recommendations</span><span lang="th">คำแนะนำ</span></summary>
                <h4>pH</h4>
                <ul>
                    <li><strong>กรด</strong> - ดินมีความเปรี้ยวสูง แนะนำให้ปรับสภาพดิน เช่น นำปูนขาวโรยหน้าดินเพื่อปรับค่า pH</li>
                    <li><strong>กรดเล็กน้อย</strong> - ดินมีความเปรี้ยวเล็กน้อย ไม่ส่งผลเสียรุนแรง หากต้องการรักษาสมดุลค่า pH สามารถโรยเปลือกไข่บดละเอียดลงในดิน หรือเติมสารปรับปรุงดินเพียงเล็กน้อยเช่น ปูนขาว ได้</li>
                    <li><strong>เหมาะสม</strong> - ความเป็นกรด - ด่างอยู่ในเกณฑ์ที่เหมาะสม พืชสามารถดูดซึมสารอาหารได้อย่างเต็มประสิทธิภาพ ไม่จำเป็นต้องปรับสภาพดิน</li>
                    <li><strong>เบสเล็กน้อย</strong> - ดินมีความด่างเล็กน้อย ไม่ส่งผลเสียรุนแรง หากต้องการรักษาสมดุลค่า pH สามารถชะล้างดินด้วยน้ำเปล่า เติมกากกาแฟหรือใบไม้แห้ง ได้</li>
                    <li><strong>เบสมาก</strong> - ดินมีความด่างสูง แนะนำให้ปรับสภาพดิน เช่น เติมปุ๋ยอินทรีย์หรือน้ำหมักชีวภาพที่มีฤทธิ์เป็นกรดอ่อน ๆ เพื่อปรับค่า pH</li>
                </ul>
                <h4>NPK</h4>
                <ul>
                    <li><strong>ต่ำ</strong> - ดินขาดธาตุอาหารนี้ พืชอาจเติบโตช้า ควรเติมปุ๋ยที่เน้นธาตุนี้</li>
                    <li><strong>เหมาะสม</strong> - ธาตุอาหารนี้ อยู่ในระดับที่เหมาะสมสำหรับพืช พืชสามารถดูดซึมไปใช้ได้ดี แนะนำให้บำรุงปุ๋ยเพิ่มเติมเพียงเล็กน้อยเป็นระยะ ๆ เพื่อรักษาความอุดมสมบูรณ์ของดิน</li>
                    <li><strong>สูง</strong> - ธาตุอาหารนี้ มีความอุดมสมบูรณ์สูง ยังไม่จำเป็นต้องบำรุงเพิ่มเติมในขณะนี้</li>
                    <li><strong>สูงเกินไป</strong> - ดินมีธาตุอาหารนี้ สูงเกินไป อาจส่งผลให้พืชเกิดอาการรากหรือใบไหม้ได้ ควรรดน้ำในปริมาณที่มากกว่าปกติเล็กน้อย เพื่อชะล้างธาตุอาหารส่วนเกิน</li>
                </ul>
            </details>
        </div>

        <div class="recommend-box">
            <h3><span lang="en">Recommended Plants</span><span lang="th">พืชแนะนำ</span></h3>
            <div class="recmsg-box" id="recommend"></div>
        </div>
    </div>
    <script>
    const inputEl = document.querySelector("#plantIn");
    const suggestionBox = document.querySelector("#suggestions");
    let currentLang = "en"
    const languageButton = document.querySelector("#language-switcher")
        
    if(languageButton) {
        languageButton.addEventListener('click', () => {
            currentLang == "en" ? currentLang = "th" : currentLang = "en"
            displayLanguage()
        })
    }

    function displayLanguage () {
        currentLang == "en" ? document.documentElement.setAttribute('lang', 'en') : document.documentElement.setAttribute('lang', 'th')
        if (languageButton) currentLang == "en" ? languageButton.innerHTML = "ภาษาไทย" : languageButton.innerHTML = "english"
        getSuitablePlants()
        suggestionBox.style.display = "none"
    }

const PRESETPAKBAI = {
    N: {
        low: [0,60],
        med: [60,100],
        good: [101,200],
        max: [200,1000]
    },
    P: {
        low: [0,10],
        med: [10,20],
        good: [20,200],
        max: [200,1000]
    },
    K: {
        low: [0,60],
        med: [60,100],
        good: [101,200],
        max: [200,1000]
    }  
}

const db = {
    tomato: {
        names: { en: "tomato", th: "มะเขือเทศ" },
        minPH: 6.0,
        maxPH: 6.8,
        info: {
            en: "Needs slightly acidic soil.",
            th: "ต้องการดินเป็นกรดเล็กน้อย"
        },
        N: PRESETPAKBAI.N,
        P: PRESETPAKBAI.P,
        K: PRESETPAKBAI.K, 
    },
    lavender: {
        names: { en: "lavender", th: "ลาเวนเดอร์" },
        minPH: 6.7,
        maxPH: 7.3,
        info: {
            en: "Likes alkaline soil and sun.",
            th: "ชอบดินด่างและแสงแดด"
        },
        N: PRESETPAKBAI.N,
        P: PRESETPAKBAI.P,
        K: PRESETPAKBAI.K, 
    },
    rice: {
        names: { en: "rice", th: "ข้าว" },
        minPH: 5.5,
        maxPH: 6.5,
        info: {
            en: "Needs acidic soil and plenty of water.",
            th: "ต้องการดินเป็นกรดและน้ำมาก"
        },
        N: PRESETPAKBAI.N,
        P: PRESETPAKBAI.P,
        K: PRESETPAKBAI.K, 
    },
}

        const currentSoil = {
            PH: parseFloat("%PH%") || 7,
            N: parseFloat("%N%") || 0,
            P: parseFloat("%P%") || 0,
            K: parseFloat("%K%") || 0
        }

        function getPlantStatus(plant) {
            const status = {
                idealPH: currentSoil.PH >= plant.minPH && currentSoil.PH <= plant.maxPH,
                idealN: currentSoil.N >= plant.N.med[0] && currentSoil.N <= plant.N.good[1] ,
                idealP: currentSoil.P >= plant.P.med[0] && currentSoil.P <= plant.P.good[1] ,
                idealK: currentSoil.K >= plant.K.med[0] && currentSoil.K <= plant.K.good[1] , 
            }
            status.isAllMatch = Object.values(status).every(v => v === true)
            return status
        }
        
        function getPlantStatusText(plant) {
          function compareNPK(minerals, value) {
              let result
              if (value >= plant[minerals].med[0]) {
                if (value >= plant[minerals].good[0]) {
                  if (value >= plant[minerals].max[0]) {
                    result = "max"
                  } else {
                    result = "good"
                  }
                } else {
                  result = "medium"
                }
              } else {
                result = "low"
              }
              return result
            }
            function comparePH() {
              let value = currentSoil.PH
              let result
              if (value <= plant.minPH) {
                result = "too acidic"
              } else if (value <= plant.maxPH) {
                result = "suitable"
              } else {
                result = "too base"
              }
              return result
            }
            const status = {
              pH: comparePH(),
              N: compareNPK("N", currentSoil.N),
              P: compareNPK("P", currentSoil.P),
              K: compareNPK("K", currentSoil.K),
            }
            return status
        }

        function getSuitablePlants() {
            const result = Object.values(db)
                .filter(plant => plant.names[currentLang])
                .filter(plant => getPlantStatus(plant).isAllMatch)
                .map(plant => plant.names[currentLang])

            const rec = document.querySelector("#recommend")

            rec.innerHTML = result.length === 0
                ? "<span lang='en'>We did not find a suitable plant.</span><span lang='th'>ไม่เจอพืชที่เหมาะสมจะปลูกในดินนี้</span>"
                : `<span lang='en'>The soil is suitable for planting</span><span lang='th'>ดินนี้เหมาะกับการปลูก</span>: ${result.join(", ")}`
        }
        
        function getStatusColor(status) {
            switch(status) {
                case "good": return { bg: "#e8f5e9", text: "#2e7d32", th: "สูง" }  // green
                case "medium": return { bg: "#fff9c4", text: "#f57f17", th: "เหมาะสม" } // yellow
                case "low":  return { bg: "#fce4ec", text: "#c62828", th: "ต่ำ" }  // red
                case "max":  return { bg: "#ede7f6", text: "#4527a0", th: "สูงเกินไป" }  // purple
                case "suitable": return { bg: "#e8f5e9", text: "#2e7d32", th: "เหมาะสม" }
                case "too acidic": return { bg: "#fce4ec", text: "#c62828", th: "กรด" }
                case "too base": return { bg: "#fce4ec", text: "#c62828", th: "เบส" }
                default: return { bg: "#f5f5f5", text: "#333", th: "ไม่ทราบ" }
            }
        }
        
        function coloredTd(status) {
            const c = getStatusColor(status)
            return `<td style="background:${c.bg}; color:${c.text}; font-weight:bold"><span lang="en">${status}</span><span lang="th">${c.th}</span></td>`
        }


        function check() {
            const input = document.querySelector("#plantIn").value
            const resbox = document.querySelector("#resultCon")
            const res = document.querySelector("#result")
            const improve = document.querySelector("#improvement")

            improve.style.display = "none"

            const plant = findPlantByName(input)
            if (!plant) {
                res.innerHTML = "Plant not found."
                resbox.style.backgroundColor = "#eee"
                return
            }

            const status = getPlantStatus(plant)
            const statusText = getPlantStatusText(plant)
            const displayName = plant.names[currentLang]

            if (status.isAllMatch) {
                res.innerHTML = `<strong>✅ Match!</strong><br>${plant.info[currentLang]}`
                resbox.style.backgroundColor = "#e8f5e9"
            } else {
                res.innerHTML = `<strong>❌ Not Ideal.</strong>`
                resbox.style.backgroundColor = "#fff3e0"
            }
            improve.innerHTML = `<table><tbody><tr><td>&nbsp;</td><th>pH</th><th>N</th><th>P</th> <th>K</           th></tr><tr><th><span lang="en">Recommend</span><span lang="th">ค่าที่เหมาะสม</span></th>
            <td>${plant.minPH} - ${plant.maxPH}</td>
            <td>${plant.N.good[0]} - ${plant.N.good[1]}</td>
            <td>${plant.P.good[0]} - ${plant.P.good[1]}</td>
            <td>${plant.K.good[0]} - ${plant.K.good[1]}</td>
            </tr><tr><th><span lang="en">Measured</span><span lang="th">ค่าที่วัดได้</span></th>
            <td>${currentSoil.PH}</td>
            <td>${currentSoil.N}</td>
            <td>${currentSoil.P}</td>
            <td>${currentSoil.K}</td>
            </tr><tr><th><span lang="en">Status</span><span lang="th">ผลการประเมิน</span></th>
            ${coloredTd(statusText.pH)}
            ${coloredTd(statusText.N)}
            ${coloredTd(statusText.P)}
            ${coloredTd(statusText.K)}
            </tr></tbody></table>` 
            improve.style.display = "block"
        }

        document.querySelector("#plantIn").addEventListener("keypress", event => {
            if (event.key === "Enter") {
                event.preventDefault()
                check()
            }
        })

        function findPlantByName(input) {
            const value = input.trim().toLowerCase()

            return Object.values(db).find(plant =>
                Object.values(plant.names).some(
                    name => name.toLowerCase() === value
                )
            )
        }

        const timeText = document.querySelector("#time")
        let date = new Date()
        timeText.innerHTML = `${date.getDate()}/${date.getMonth() + 1}/${date.getFullYear()} - ${date.getHours()}:${date.getMinutes()}:${date.getSeconds()}`

        function getPlantSuggestions(query) {
            const q = query.trim().toLowerCase()

            return Object.values(db)
                .map(plant => plant.names[currentLang])
                .filter(name => {
                    if (!q) return true
                    return name.toLowerCase().includes(q)
                })
        }

        function showSuggestions(list) {
            if (list.length === 0) {
                suggestionBox.style.display = "none"
                return
            }

            suggestionBox.innerHTML = list
                .map(name => `<div class="suggestion-item">${name}</div>`)
                .join("")

            suggestionBox.style.display = "block"
        }

        inputEl.addEventListener("input", () => {
            const suggestions = getPlantSuggestions(inputEl.value)
            showSuggestions(suggestions)
        })
        inputEl.addEventListener("focus", () => {
            showSuggestions(getPlantSuggestions(""))
        })

        suggestionBox.addEventListener("click", event => {
            if (!event.target.classList.contains("suggestion-item")) return

            inputEl.value = event.target.textContent
            suggestionBox.style.display = "none"
            check()
        })

        document.addEventListener("click", event => {
            if (!event.target.closest(".search-box")) {
                suggestionBox.style.display = "none"
            }
        })

        displayLanguage()
    </script>
</body>
</html>
)rawliteral";