<!DOCTYPE html>
<html>
<head>
    <title>Network Monitor</title>
    <script src="https://cdnjs.cloudflare.com/ajax/libs/Chart.js/3.7.0/chart.min.js"></script>
    <script src="https://cdnjs.cloudflare.com/ajax/libs/moment.js/2.29.1/moment.min.js"></script>
    <link rel="stylesheet" href="/static/css/style.css">
</head>
<body>
    <h1>Network Monitor Dashboard</h1>
    
    <!-- stats container -->
    <div class="stats-container">
        <h2>Current Statistics</h2>
        <div class="current-stats" id="currentStats"></div> <div class="additional-stats" id="additionalStats"></div>
    </div>
    
    <!-- charts container -->
    <div class="container">
        <div class="chart">
            <canvas id="trafficChart"></canvas>
        </div>
        <div class="chart">
            <canvas id="packetsChart"></canvas>
        </div>
        <div class="chart">
            <canvas id="bandwidthChart"></canvas>
        </div>
        <div class="chart">
            <canvas id="throughputChart"></canvas>
        </div>
    </div>
    
    <h2>Connected Devices</h2>
    <div id="deviceList"></div>
    
    <script src="/static/js/main.js"></script>
</body>
</html>
