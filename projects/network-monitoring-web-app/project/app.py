from bottle import Bottle, run, template, static_file, response, request
import sqlite3
from nmap3 import NmapScanTechniques
import threading
import logging

DB_NAME = "network_monitor.db"
app = Bottle()

# Initialize Database
def init_db():
    conn = sqlite3.connect(DB_NAME)
    cursor = conn.cursor()
    cursor.execute("""
        CREATE TABLE IF NOT EXISTS devices (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            hostname TEXT NOT NULL,
            ip TEXT NOT NULL,
            mac TEXT NOT NULL UNIQUE,
            vendor TEXT,
            operating_system TEXT,
            last_scanned TIMESTAMP DEFAULT CURRENT_TIMESTAMP
        );
    """)
    conn.commit()
    conn.close()

init_db()

def db_get_connection():
    conn = sqlite3.connect(DB_NAME)
    conn.row_factory = sqlite3.Row
    return conn

def db_upsert_device(device):
    conn = db_get_connection()
    try:
        cur = conn.cursor()
        cur.execute('''
            INSERT INTO devices (hostname, ip, mac, vendor, operating_system)
            VALUES (?, ?, ?, ?, ?)
            ON CONFLICT(mac) DO UPDATE SET
                hostname = excluded.hostname,
                ip = excluded.ip,
                vendor = excluded.vendor,
                operating_system = excluded.operating_system,
                last_scanned = CURRENT_TIMESTAMP
        ''', (device['hostname'], device['ip'], device['mac'], device['vendor'], device['os']))
        conn.commit()
    finally:
        conn.close()

def db_get_devices():
    conn = db_get_connection()
    cursor = conn.cursor()
    cursor.execute('SELECT * FROM devices ORDER BY last_scanned DESC')
    devices = cursor.fetchall()
    conn.close()
    
    device_list = []
    for device in devices:
        device_list.append({
            'hostname': device['hostname'],
            'ip': device['ip'],
            'mac': device['mac'],
            'vendor': device['vendor'],
            'os': device['operating_system']
        })
    return device_list

def scan_network(target_ip):
    nmap = NmapScanTechniques()
    scan_result = nmap.nmap_os_detection(target_ip)
    devices = []
    for ip, details in scan_result.items():
        if ip in ['stats', 'runtime']: continue

        ip_address = ip
        hostname = details.get('hostname', {}).get('name', 'Unknown')
        mac_address = details.get('macaddress', {}).get('addr', 'Unknown')
        vendor = details.get('macaddress', {}).get('vendor', 'Unknown')
        os = details.get('osmatch', [{}])[0].get('name', 'Unknown') if details.get('osmatch') else "Unknown"

        dev = {
            'hostname': hostname,
            'ip_address': ip_address,
            'mac_address': mac_address,
            'vendor': vendor,
            'os': os
        }
        devices.append(dev)
        db_upsert_device(dev)
    
    return devices

@app.route('/get_devices', method='GET')
def get_devices():
    devices = db_get_devices()
    response.content_type = 'application/json'
    return {'devices': devices}

@app.route('/static/<filename>')
def server_static(filename):
    return static_file(filename, root='./static')

@app.route('/')
def dashboard():
    devices = get_devices()
    return template('dashboard', devices=devices)

@app.route('/scan', method='POST')
def scan():
    target_ip = request.forms.get('target_ip', '192.168.100.0/24')  # Default to a subnet if none is provided
    if target_ip:
        try:
            threading.Thread(target=scan_network, args=(target_ip,)).start()
            return "Scanning started!"
        except Exception as e:
            return f"Error occurred while starting the scan: {e}"
    return "Please provide a valid IP range."

if __name__ == "__main__":
    run(app, host='localhost', port=8080, debug=True, reloader=True)
