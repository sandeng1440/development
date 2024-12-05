import sqlite3
from bottle import Bottle, run, template, static_file, response
import scapy.all as scapy
import psutil
import time
import json
from threading import Thread
import netifaces
import datetime
import os
import socket
import pingparsing
import random

class DB:
    def __init__(self, db_name='network_monitor.db'):
        self.db_name = db_name

    def init_db(self):
        with sqlite3.connect(self.db_name) as conn:
            c = conn.cursor()
            
            c.execute('''CREATE TABLE IF NOT EXISTS devices
                         (mac TEXT PRIMARY KEY, ip TEXT, hostname TEXT, 
                          first_seen TIMESTAMP, last_seen TIMESTAMP)''')
            
            c.execute('''CREATE TABLE IF NOT EXISTS network_stats
                         (timestamp TIMESTAMP PRIMARY KEY, bytes_sent INTEGER, 
                          bytes_recv INTEGER, packets_sent INTEGER, 
                          packets_recv INTEGER)''')
            
            c.execute('''CREATE INDEX IF NOT EXISTS idx_timestamp 
                         ON network_stats(timestamp)''')
            
            conn.commit()

    def insert_device(self, mac, ip, hostname, current_time):
        with sqlite3.connect(self.db_name) as conn:
            c = conn.cursor()
            c.execute('''INSERT OR REPLACE INTO devices 
                        (mac, ip, hostname, first_seen, last_seen)
                        VALUES (?, ?, ?, COALESCE(
                            (SELECT first_seen FROM devices WHERE mac = ?), 
                            ?), ?)''',
                     (mac, ip, hostname, mac, current_time, current_time))
            conn.commit()

    def get_bandwidth(self):
        with sqlite3.connect(self.db_name) as conn:
            c = conn.cursor()
            c.execute('''
                SELECT timestamp, 
                (bytes_sent - LAG(bytes_sent) OVER (ORDER BY timestamp)) / 
                (JULIANDAY(timestamp) - JULIANDAY(LAG(timestamp) OVER (ORDER BY timestamp))) * 86400 AS bandwidth_sent,
                (bytes_recv - LAG(bytes_recv) OVER (ORDER BY timestamp)) / 
                (JULIANDAY(timestamp) - JULIANDAY(LAG(timestamp) OVER (ORDER BY timestamp))) * 86400 AS bandwidth_recv
                FROM network_stats 
                WHERE timestamp >= datetime('now', '-5 minutes')
                ORDER BY timestamp
            ''')
            return c.fetchall()

    def get_throughput(self):
        with sqlite3.connect(self.db_name) as conn:
            c = conn.cursor()
            c.execute('''
                SELECT timestamp, 
                (packets_sent - LAG(packets_sent) OVER (ORDER BY timestamp)) / 
                (JULIANDAY(timestamp) - JULIANDAY(LAG(timestamp) OVER (ORDER BY timestamp))) * 86400 AS throughput_sent,
                (packets_recv - LAG(packets_recv) OVER (ORDER BY timestamp)) / 
                (JULIANDAY(timestamp) - JULIANDAY(LAG(timestamp) OVER (ORDER BY timestamp))) * 86400 AS throughput_recv
                FROM network_stats 
                WHERE timestamp >= datetime('now', '-5 minutes')
                ORDER BY timestamp
            ''')
            return c.fetchall()


    def insert_network_stats(self, current_time, stats):
        with sqlite3.connect(self.db_name) as conn:
            c = conn.cursor()
            c.execute('''INSERT INTO network_stats 
                         (timestamp, bytes_sent, bytes_recv, 
                          packets_sent, packets_recv)
                         VALUES (?, ?, ?, ?, ?)''',
                     (current_time, stats.bytes_sent, 
                      stats.bytes_recv, stats.packets_sent, 
                      stats.packets_recv))
            
            c.execute('''DELETE FROM network_stats 
                         WHERE timestamp < datetime('now', '-1 hour')''')
            conn.commit()

    def get_network_stats(self):
        with sqlite3.connect(self.db_name) as conn:
            c = conn.cursor()
            c.execute('''SELECT timestamp, bytes_sent, bytes_recv, 
                                packets_sent, packets_recv 
                         FROM network_stats 
                         WHERE timestamp >= datetime('now', '-5 minutes')
                         ORDER BY timestamp''')
            return c.fetchall()

    def get_devices(self):
        with sqlite3.connect(self.db_name) as conn:
            c = conn.cursor()
            c.execute('SELECT * FROM devices ORDER BY last_seen DESC')
            return c.fetchall()

class NetStats:
    def __init__(self, db_manager):
        self.db_manager = db_manager

    def scan_network(self):
        while True:
            gw = netifaces.gateways()['default'][netifaces.AF_INET][0]
            network = gw + "/24"
            
            ans, _ = scapy.arping(network, timeout=2, verbose=False)
            
            current_time = datetime.datetime.now()
            
            for sent, received in ans:
                mac = received.hwsrc
                ip = received.psrc
                
                try:
                    hostname = socket.gethostbyaddr(ip)[0]
                except socket.herror:
                    hostname = ip
                
                self.db_manager.insert_device(mac, ip, hostname, current_time)

            # rescan after some time
            time.sleep(300)

    def collect_stats(self):
        while True:
            stats = psutil.net_io_counters()
            current_time = datetime.datetime.now()
            self.db_manager.insert_network_stats(current_time, stats)
            time.sleep(2)

class NetworkMonitorApp:
    def __init__(self):
        self.app = Bottle()
        self.db_manager = DB()
        self.net_stats = NetStats(self.db_manager)
        self.setup_routes()

    def setup_routes(self):
        self.app.route('/static/<filepath:path>', callback=self.serve_static)
        self.app.route('/', callback=self.home)
        self.app.route('/stats', callback=self.get_stats)
        self.app.route('/devices', callback=self.get_devices)
        self.app.route('/bandwidth', callback=self.get_bandwidth)
        self.app.route('/throughput', callback=self.get_throughput)
        self.app.route('/additional_stats', callback=self.get_additional_stats)

    def serve_static(self, filepath):
        return static_file(filepath, root=os.path.join(os.path.dirname(__file__), 'static'))

    def home(self):
        return template('index', template_lookup=[os.path.join(os.path.dirname(__file__), 'views')])

    def get_stats(self):
        rows = self.db_manager.get_network_stats()
        return {
            'timestamps': [row[0] for row in rows],
            'bytes_sent': [row[1] for row in rows],
            'bytes_recv': [row[2] for row in rows],
            'packets_sent': [row[3] for row in rows],
            'packets_recv': [row[4] for row in rows]
        }

    def get_additional_stats(self):
        pp = pingparsing.PingParsing()
        pt = pingparsing.PingTransmitter()
        pt.destination = 'google.com'
        pt.count = 10
        res = pt.ping()
        ppDict = pp.parse(res).as_dict()
        latency = ppDict['rtt_avg']
        packet_loss = ppDict['packet_loss_rate']
        
        packet_burst = random.randint(1, 10)
        
        return {
            'latency': latency,
            'packet_loss': packet_loss,
            'packet_burst': packet_burst
        }



    def get_bandwidth(self):
        rows = self.db_manager.get_bandwidth()
        return {
            'timestamps': [row[0] for row in rows],
            'bandwidth_sent': [row[1] if row[1] is not None else 0 for row in rows],
            'bandwidth_recv': [row[2] if row[2] is not None else 0 for row in rows]
        }

    def get_throughput(self):
        rows = self.db_manager.get_throughput()
        return {
            'timestamps': [row[0] for row in rows],
            'throughput_sent': [row[1] if row[1] is not None else 0 for row in rows],
            'throughput_recv': [row[2] if row[2] is not None else 0 for row in rows]
        }


    def get_devices(self):
        rows = self.db_manager.get_devices()
        devices = []
        for row in rows:
            devices.append({
                'mac': row[0],
                'ip': row[1],
                'hostname': row[2],
                'first_seen': row[3],
                'last_seen': row[4]
            })
        return json.dumps(devices)

    def run(self):
        self.db_manager.init_db()
        Thread(target=self.net_stats.scan_network, daemon=True).start()
        Thread(target=self.net_stats.collect_stats, daemon=True).start()
        run(self.app, host='localhost', port=8080, reloader=True)

if __name__ == '__main__':
    app = NetworkMonitorApp()
    app.run()
