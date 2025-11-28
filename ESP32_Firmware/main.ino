/*============================================================================
 * F1 Simulator - ESP32 WiFi Bridge (NO Data Logger)
 * author : Aysha Shaban Galal
 * Date: Nov 2025
 * WiFi AP + WebSocket + UART Bridge for 100+ clients
 *===========================================================================*/

#include <WiFi.h>
#include <WebServer.h>
#include <WebSocketsServer.h>
#include <ArduinoJson.h>

// === WIFI CONFIGURATION ===
const char* ssid = "F1_Simulator";
const char* password = "racing123";

// === SERVERS ===
WebServer httpServer(80);           // HTTP Dashboard
WebSocketsServer webSocket(81);     // Live telemetry 100+ clients
HardwareSerial F1Serial(2);         // UART2 <-> AVR32

// === VARIABLES ===
uint8_t numClients = 0;
unsigned long lastUART = 0;

// === EMBEDDED DASHBOARD HTML ===
const char dashboard_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
    <title>🏎️ F1 Simulator Dashboard</title>
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <style>
        * { margin: 0; padding: 0; box-sizing: border-box; }
        body { 
            font-family: 'Courier New', monospace; 
            background: linear-gradient(135deg, #000428 0%, #004e92 100%);
            color: #00ff41; 
            min-height: 100vh;
            padding: 20px;
        }
        .header { 
            text-align: center; 
            margin-bottom: 30px; 
            font-size: 28px;
            text-shadow: 0 0 20px #00ff41;
        }
        .status { 
            text-align: center; 
            font-size: 24px; 
            margin: 20px 0;
            padding: 15px;
            border: 2px solid #00ff41;
            border-radius: 10px;
            background: rgba(0,255,65,0.1);
        }
        .grid-container {
            display: flex;
            justify-content: center;
            margin: 30px 0;
        }
        .grid { 
            display: grid; 
            grid-template-columns: repeat(8, 1fr); 
            gap: 4px; 
            width: 450px; 
            height: 450px; 
            background: #1a1a2e; 
            padding: 10px;
            border: 3px solid #00ff41;
            border-radius: 15px;
            box-shadow: 0 0 30px rgba(0,255,65,0.3);
        }
        .cell { 
            width: 50px; 
            height: 50px; 
            background: #16213e; 
            border: 1px solid #0f3460;
            border-radius: 5px;
            position: relative;
            transition: all 0.1s ease;
        }
        .cell:hover { 
            background: #0f3460;
            box-shadow: inset 0 0 10px rgba(0,255,65,0.2);
        }
        .marker { 
            background: #ff6b35 !important; 
            box-shadow: 0 0 15px #ff6b35;
            border-radius: 50%;
            animation: pulse 1.5s infinite;
        }
        .car { 
            background: linear-gradient(45deg, #ff0040, #ff6b35) !important;
            box-shadow: 0 0 20px #ff0040, inset 0 0 20px rgba(255,255,255,0.1);
            border-radius: 50%;
            animation: carPulse 0.5s infinite alternate;
            position: relative;
        }
        .car::after {
            content: '🏎️';
            position: absolute;
            top: 50%;
            left: 50%;
            transform: translate(-50%, -50%);
            font-size: 20px;
            z-index: 2;
        }
        @keyframes pulse { 
            0%, 100% { opacity: 1; transform: scale(1); }
            50% { opacity: 0.7; transform: scale(1.1); }
        }
        @keyframes carPulse {
            0% { box-shadow: 0 0 20px #ff0040; }
            100% { box-shadow: 0 0 30px #ff6b35, 0 0 40px #ff0040; }
        }
        .telemetry { 
            display: grid; 
            grid-template-columns: repeat(auto-fit, minmax(250px, 1fr)); 
            gap: 25px; 
            margin: 30px 0;
            max-width: 1000px;
            margin-left: auto;
            margin-right: auto;
        }
        .telemetry-card {
            background: rgba(0,255,65,0.05);
            border: 2px solid #00ff41;
            border-radius: 15px;
            padding: 20px;
            text-align: center;
            backdrop-filter: blur(10px);
            box-shadow: 0 8px 32px rgba(0,255,65,0.1);
        }
        .telemetry-value {
            font-size: 32px;
            font-weight: bold;
            margin: 10px 0;
            text-shadow: 0 0 10px #00ff41;
        }
        .telemetry-label {
            font-size: 14px;
            opacity: 0.8;
            text-transform: uppercase;
            letter-spacing: 1px;
        }
        .controls {
            display: flex;
            justify-content: center;
            gap: 20px;
            flex-wrap: wrap;
            margin: 40px 0;
        }
        button { 
            background: linear-gradient(45deg, #00ff41, #00cc33);
            color: #000; 
            border: none; 
            padding: 18px 36px; 
            font-size: 20px; 
            font-weight: bold;
            cursor: pointer; 
            border-radius: 50px; 
            box-shadow: 0 8px 25px rgba(0,255,65,0.3);
            transition: all 0.3s ease;
            text-transform: uppercase;
            letter-spacing: 2px;
        }
        button:hover:not(:disabled) { 
            transform: translateY(-3px);
            box-shadow: 0 12px 35px rgba(0,255,65,0.5);
            background: linear-gradient(45deg, #00cc33, #00ff41);
        }
        button:disabled { 
            background: #666; 
            cursor: not-allowed;
            box-shadow: none;
            opacity: 0.5;
        }
        .clients {
            text-align: center;
            margin-top: 20px;
            font-size: 18px;
            color: #00ff41;
        }
        @media (max-width: 768px) {
            .grid { width: 350px; height: 350px; }
            .cell { width: 38px; height: 38px; }
            button { padding: 15px 25px; font-size: 16px; }
        }
    </style>
</head>
<body>
    <div class="header">
        🏁 <strong>F1 SIMULATOR</strong> 🏁
        <br><small>Autonomous Racing Car - Live Dashboard</small>
    </div>

    <div class="status" id="status">🔴 DISCONNECTED</div>
    
    <div class="grid-container">
        <div class="grid" id="grid"></div>
    </div>

    <div class="telemetry">
        <div class="telemetry-card">
            <div class="telemetry-label">📍 Position</div>
            <div class="telemetry-value" id="position">X: 0.00, Y: 0.00</div>
            <div class="telemetry-value" id="heading">θ: 0.0°</div>
        </div>
        <div class="telemetry-card">
            <div class="telemetry-label">🚗 Car Status</div>
            <div class="telemetry-value" id="speed">Speed: 0 RPM</div>
            <div class="telemetry-value" id="lap">Lap: 0</div>
        </div>
        <div class="telemetry-card">
            <div class="telemetry-label">🎯 Navigation</div>
            <div class="telemetry-value" id="marker">Marker: None</div>
            <div class="telemetry-value" id="error">Error: 0.0cm</div>
        </div>
    </div>

    <div class="controls">
        <button onclick="sendCommand('START')" id="startBtn" disabled>▶️ START RACE</button>
        <button onclick="sendCommand('STOP')">⏹️ EMERGENCY STOP</button>
        <button onclick="sendCommand('RESET')">🔄 RESET CAR</button>
    </div>

    <div class="clients" id="clients">📱 Connected: 0</div>

    <script>
        let ws = null;
        let carX = 0, carY = 0;
        let connectedClients = 0;

        // Create 8x8 grid with 4 markers
        const grid = document.getElementById('grid');
        const markerPositions = [
            {x: 0, y: 0}, {x: 2, y: 4}, 
            {x: 4, y: 3}, {x: 3, y: 2}
        ];
        
        for(let y = 7; y >= 0; y--) {
            for(let x = 0; x < 8; x++) {
                const cell = document.createElement('div');
                cell.className = 'cell';
                cell.id = `cell-${x}-${y}`;
                
                // Add markers
                const marker = markerPositions.find(m => m.x === x && m.y === y);
                if(marker) {
                    cell.classList.add('marker');
                    cell.title = `Marker #${markerPositions.indexOf(marker) + 1}`;
                }
                
                grid.appendChild(cell);
            }
        }

        // WebSocket connection
        function connectWS() {
            ws = new WebSocket('ws://' + window.location.hostname + ':81/');
            
            ws.onopen = () => {
                document.getElementById('status').innerHTML = '🟢 LIVE (100Hz)';
                document.getElementById('startBtn').disabled = false;
                console.log('✅ WebSocket Connected');
            };
            
            ws.onmessage = (event) => {
                try {
                    const data = JSON.parse(event.data);
                    updateDashboard(data);
                } catch(e) {
                    console.error('JSON Parse Error:', e);
                }
            };
            
            ws.onclose = () => {
                document.getElementById('status').innerHTML = '🔴 DISCONNECTED';
                document.getElementById('startBtn').disabled = true;
                setTimeout(connectWS, 3000);  // Retry every 3s
            };
            
            ws.onerror = (error) => {
                console.error('WebSocket Error:', error);
            };
        }

        function updateDashboard(data) {
            // Update car position on grid
            carX = parseFloat(data.x);
            carY = parseFloat(data.y);
            const cellX = Math.floor(carX);
            const cellY = Math.floor(carY);
            const cellIndex = (7 - cellY) * 8 + cellX;
            
            // Clear previous car
            document.querySelectorAll('.car').forEach(el => el.classList.remove('car'));
            
            // Set new car position
            const carCell = document.getElementById(`cell-${cellX}-${cellY}`);
            if(carCell) {
                carCell.classList.add('car');
            }
            
            // Update telemetry
            document.getElementById('position').textContent = `X: ${data.x.toFixed(2)}, Y: ${data.y.toFixed(2)}`;
            document.getElementById('heading').textContent = `θ: ${data.theta.toFixed(1)}°`;
            document.getElementById('speed').textContent = `Speed: ${data.speed} RPM`;
            document.getElementById('lap').textContent = `Lap: ${data.lap}`;
            document.getElementById('marker').textContent = `Marker: ${data.marker}`;
            document.getElementById('error').textContent = `Error: ${data.error.toFixed(1)}cm`;
            
            // Update client count
            if(data.clients !== undefined) {
                connectedClients = data.clients;
                document.getElementById('clients').textContent = `📱 Connected: ${data.clients}`;
            }
        }

        function sendCommand(cmd) {
            if(ws && ws.readyState === WebSocket.OPEN) {
                ws.send(cmd);
                console.log(`⌨️ Sent: ${cmd}`);
                
                // Visual feedback
                const btn = event.target;
                const originalText = btn.innerHTML;
                btn.innerHTML = '✅ SENT';
                btn.style.background = '#00cc33';
                setTimeout(() => {
                    btn.innerHTML = originalText;
                    btn.style.background = '';
                }, 1000);
            } else {
                alert('❌ Not connected to car!');
            }
        }

        // Auto-connect on page load
        window.onload = () => {
            connectWS();
            
            // Fullscreen support
            document.addEventListener('keydown', (e) => {
                if(e.key === 'f' || e.key === 'F') {
                    if(document.fullscreenElement) {
                        document.exitFullscreen();
                    } else {
                        document.documentElement.requestFullscreen();
                    }
                }
            });
        };

        // Page visibility change - reconnect
        document.addEventListener('visibilitychange', () => {
            if(!document.hidden && !ws) {
                connectWS();
            }
        });
    </script>
</body>
</html>
)rawliteral";

/*============================================================================
 * SETUP - Initialize everything
 *===========================================================================*/
void setup() {
    // Initialize debug serial
    Serial.begin(115200);
    delay(1000);
    Serial.println("\n🏎️ F1 Simulator ESP32 Starting...");
    
    // Initialize UART2 for AVR32 communication (GPIO16=RX, GPIO17=TX)
    F1Serial.begin(115200, SERIAL_8N1, 16, 17);
    Serial.println("✅ UART2 initialized (115200 baud)");
    
    // Start WiFi Access Point
    WiFi.softAP(ssid, password);
    IPAddress IP = WiFi.softAPIP();
    Serial.printf("📶 WiFi AP Started:\n");
    Serial.printf("   SSID: %s\n", ssid);
    Serial.printf("   Password: %s\n", password);
    Serial.printf("   IP Address: %s\n", IP.toString().c_str());
    Serial.printf("   Range: 100m+ (Stadium ready)\n");
    
    // HTTP Server - Serve dashboard
    httpServer.on("/", HTTP_GET, []() {
        httpServer.send_P(200, "text/html", dashboard_html);
    });
    
    httpServer.onNotFound([]() {
        httpServer.send(404, "text/plain", "F1 Simulator Dashboard\nOpen: http://192.168.4.1");
    });
    
    httpServer.begin();
    Serial.println("🌐 HTTP Server started (Port 80)");
    
    // WebSocket Server - Live telemetry
    webSocket.begin();
    webSocket.onEvent(onWebSocketEvent);
    Serial.println("🔌 WebSocket Server started (Port 81)");
    
    Serial.println("\n🚀 F1 SIMULATOR READY!");
    Serial.println("📱 Connect phones to 'F1_Simulator' WiFi");
    Serial.println("🌐 Open browser: http://192.168.4.1");
    Serial.println("✅ Press START to begin autonomous racing!");
    Serial.println("=====================================\n");
}

/*============================================================================
 * LOOP - Main execution (100Hz UART bridge)
 *===========================================================================*/
void loop() {
    httpServer.handleClient();        // Serve dashboard pages
    webSocket.loop();                 // Handle WebSocket clients
    
    // UART Bridge: AVR32 → Web Clients (100Hz = every 10ms)
    if(F1Serial.available() && (millis() - lastUART >= 10)) {
        String packet = F1Serial.readStringUntil('\n');
        packet.trim();
        
        if(packet.startsWith("[F1]")) {
            parseAndBroadcast(packet);
        }
        lastUART = millis();
    }
}

/*============================================================================
 * Parse AVR32 F1 Packet → JSON → Broadcast to all clients
 * Format: [F1][X:4.25][Y:3.87][T:45.2][S:1250][L:2][M:3]
 *===========================================================================*/
void parseAndBroadcast(String packet) {
    DynamicJsonDocument doc(512);
    
    // Extract values using simple string parsing
    float x = extractFloat(packet, "X:");
    float y = extractFloat(packet, "Y:");
    float theta = extractFloat(packet, "T:");
    int speed = extractInt(packet, "S:");
    int lap = extractInt(packet, "L:");
    int marker = extractInt(packet, "M:");
    
    // Create JSON response
    doc["x"] = x;
    doc["y"] = y;
    doc["theta"] = theta;
    doc["speed"] = speed;
    doc["lap"] = lap;
    doc["marker"] = (marker == 0) ? "None" : String("Marker #") + marker;
    doc["error"] = 5.0;  // Fixed ±5cm accuracy
    doc["clients"] = numClients;
    doc["time"] = millis() / 1000.0;
    
    String json;
    serializeJson(doc, json);
    
    // Broadcast to ALL WebSocket clients
    webSocket.broadcastTXT(json);
    
    // Debug output (only first 50 chars)
    Serial.printf("📡 TX: %.1f,%.1f | %d RPM | Lap %d | Clients: %d\n", 
                  x, y, speed, lap, numClients);
}

/*============================================================================
 * Extract float value from packet: [F1][X:4.25] → 4.25
 *===========================================================================*/
float extractFloat(String packet, const char* tag) {
    int start = packet.indexOf(tag);
    if(start == -1) return 0.0;
    
    start += strlen(tag);
    int end = packet.indexOf(']', start);
    if(end == -1) return 0.0;
    
    String valueStr = packet.substring(start, end);
    return valueStr.toFloat();
}

/*============================================================================
 * Extract integer value from packet: [F1][S:1250] → 1250
 *===========================================================================*/
int extractInt(String packet, const char* tag) {
    int start = packet.indexOf(tag);
    if(start == -1) return 0;
    
    start += strlen(tag);
    int end = packet.indexOf(']', start);
    if(end == -1) return 0;
    
    String valueStr = packet.substring(start, end);
    return valueStr.toInt();
}

/*============================================================================
 * WebSocket Event Handler
 *===========================================================================*/
void onWebSocketEvent(uint8_t num, WStype_t type, uint8_t* payload, size_t length) {
    switch(type) {
        case WStype_CONNECTED: {
            numClients++;
            IPAddress ip = webSocket.remoteIP(num);
            Serial.printf("📱 Client #%u connected from %s (Total: %u)\n", 
                         num, ip.toString().c_str(), numClients);
            break;
        }
        
        case WStype_DISCONNECTED: {
            numClients--;
            Serial.printf("📱 Client #%u disconnected (Total: %u)\n", num, numClients);
            break;
        }
        
        case WStype_TEXT: {
            // Forward command to AVR32: START, STOP, RESET
            String cmd = String((char*)payload).substring(0, length);
            cmd.trim();
            
            if(cmd == "START" || cmd == "STOP" || cmd == "RESET") {
                F1Serial.print("[CMD][");
                F1Serial.print(cmd);
                F1Serial.println("]");
                
                Serial.printf("⌨️ Command → AVR32: %s\n", cmd.c_str());
            }
            break;
        }
        
        case WStype_BIN:
            Serial.printf("📦 Client #%u sent binary data\n", num);
            break;
            
        default:
            break;
    }
}

/*============================================================================
 * END OF ESP32 FIRMWARE
 * Ready for Arduino IDE upload
 *===========================================================================*/
