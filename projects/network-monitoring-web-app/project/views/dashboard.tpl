
<!DOCTYPE html>
<html>
<head>
    <title>Network Monitoring Dashboard</title>
    <style>
        table {
            width: 100%;
            border-collapse: collapse;
            margin-top: 20px;
        }
        th, td {
            border: 1px solid #ddd;
            padding: 10px;
            text-align: left;
        }
        th {
            background-color: #333;
            color: white;
        }
        tr:nth-child(even) {
            background-color: #f9f9f9;
        }
        tr:hover {
            background-color: #f1f1f1;
        }
    </style>
    <script>
        function startScan() {
            const targetIp = document.getElementById("target_ip").value || "192.168.1.0/24";
            // Start scan (you could show an in-progress indicator here)
            fetch(`/scan?target_ip=${targetIp}`).then(response => {
                console.log("Scan started");
            });

            // Poll for device updates every 2 seconds
            setInterval(fetchDevices, 2000);
        }

        function fetchDevices() {
            fetch('/get_devices', { cache: 'no-store' })  // Disable caching to always get fresh data
                .then(response => response.json())
                .then(data => {
                    const devices = data.devices;
                    const resultsBody = document.getElementById("device_table_body");
                    resultsBody.innerHTML = "";  // Clear previous rows

                    devices.forEach(device => {
                        const row = document.createElement("tr");

                        const hostnameCell = document.createElement("td");
                        hostnameCell.textContent = device.hostname;
                        row.appendChild(hostnameCell);

                        const ipCell = document.createElement("td");
                        ipCell.textContent = device.ip;
                        row.appendChild(ipCell);

                        const macCell = document.createElement("td");
                        macCell.textContent = device.mac;
                        row.appendChild(macCell);

                        const vendorCell = document.createElement("td");
                        vendorCell.textContent = device.vendor;
                        row.appendChild(vendorCell);

                        const osCell = document.createElement("td");
                        osCell.textContent = device.os;
                        row.appendChild(osCell);

                        resultsBody.appendChild(row);
                    });
                });
        }
    </script>
</head>
<body>
    <h1>Network Monitoring Dashboard</h1>

    <h2>Start Scan</h2>
    <form method="POST" action="/scan">
        <input type="text" id="target_ip" placeholder="192.168.1.0/24">
        <button type="button" onclick="startScan()">Scan</button>
    </form>

    <h2>Discovered Devices</h2>
    <table>
        <thead>
            <tr>
                <th>Hostname</th>
                <th>IP Address</th>
                <th>MAC Address</th>
                <th>Vendor</th>
                <th>Operating System</th>
            </tr>
        </thead>
        <tbody id="device_table_body">
            {% if devices %}
                {% for device in devices %}
                    <tr>
                        <td>{{ device['hostname'] }}</td>
                        <td>{{ device['ip_address']}}</td>
                        <td>{{ device['mac_address'] }}</td>
                        <td>{{ device['vendor'] }}</td>
                        <td>{{ device['os'] }}</td>
                    </tr>
                {% endfor %}
            {% else %}
                <tr>
                    <td colspan="5" style="text-align: center;">No devices discovered yet. Start a scan to see results.</td>
                </tr>
            {% endif %}
        </tbody>
    </table>
</body>
</html>

