
<h1>Traffic Data</h1>
<table>
    <tr><th>Timestamp</th><th>Bandwidth Usage (MB)</th></tr>
    % for data in traffic_data:
        <tr><td>{{ data[3] }}</td><td>{{ data[2] }}</td></tr>
    % end
</table>
<a href="/">Back to Dashboard</a>

