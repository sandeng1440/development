let trafficChart = null;
let packetsChart = null;
let bandwidthChart = null;
let throughputChart = null;

function formatBytes(bytes) {
  const sizes = ['Bytes', 'KB', 'MB', 'GB', 'TB', 'PB', 'EB', 'ZB'];
  if (bytes === 0) return '0 Bytes';
  let i = 0;

  while (bytes >= 1024 && i < (sizes.length - 1)) {
    bytes /= 1024;
    i++;
  }
  return b + sizes[i];
}


function formatTimeAgo(timestamp) {
  const now = moment();
  const time = moment(timestamp);
  const diffMinutes = now.diff(time, 'minutes');

  if (diffMinutes < 60) {
    return `${diffMinutes}m`;
  } else {
    const hours = Math.floor(diffMinutes / 60);
    const minutes = diffMinutes % 60;
    return `${hours}h ${minutes}m`;
  }
}


function formatAxisLabel(value, maxDigits = 3) {
  const suffixes = ['', 'K', 'M', 'G', 'T', 'P', 'E', 'Z'];
  let suffixIndex = 0;

  while (value >= 1024 && suffixIndex < (suffixes.length - 1)) {
    value /= 1024;
    suffixIndex++;
  }

  return value.toPrecision(maxDigits) + suffixes[suffixIndex];
}


function updateCurrentStats(latestData) {
  const stats = document.getElementById('currentStats');
  const lastIndex = latestData.timestamps.length - 1;

  if (lastIndex >= 0) {
    const bytesSent = latestData.bytes_sent[lastIndex];
    const bytesRecv = latestData.bytes_recv[lastIndex];
    const packetsSent = latestData.packets_sent[lastIndex];
    const packetsRecv = latestData.packets_recv[lastIndex];

    stats.innerHTML = `
            <div class="stat-box">
                <strong>Bytes Sent:</strong><br>${formatBytes(bytesSent)}
            </div>
            <div class="stat-box">
                <strong>Bytes Received:</strong><br>${formatBytes(bytesRecv)}
            </div>
            <div class="stat-box">
                <strong>Packets Sent:</strong><br>${packetsSent.toLocaleString()}
            </div>
            <div class="stat-box">
                <strong>Packets Received:</strong><br>${packetsRecv.toLocaleString()}
            </div>
        `;
  }
}

function updateAdditionalStats() {
  fetch('/additional_stats')
    .then(response => response.json())
    .then(data => {
      const stats = document.getElementById('additionalStats');
      stats.innerHTML = `
                <div class="stat-box">
                    <strong>Latency:</strong><br>${data.latency.toFixed(2)} ms
                </div>
                <div class="stat-box">
                    <strong>Packet Loss:</strong><br>${data.packet_loss.toFixed(2)}%
                </div>
                <div class="stat-box">
                    <strong>Packet Burst:</strong><br>${data.packet_burst}
                </div>
            `;
    });
}

function updateCharts() {
  Promise.all([
    fetch('/stats').then(response => response.json()),
    fetch('/bandwidth').then(response => response.json()),
    fetch('/throughput').then(response => response.json())
  ]).then(([statsData, bandwidthData, throughputData]) => {
    updateCurrentStats(statsData);

    const labels = statsData.timestamps.map(timestamp => formatTimeAgo(timestamp));

    const chartOptions = {
      animation: false,
      responsive: true,
      scales: {
        x: {
          ticks: {
            maxTicksLimit: 6,
            callback: function(value, index) {
              return labels[index];
            }
          },
          title: {
            display: true,
            text: 'Time ago'
          }
        },
        y: {
          beginAtZero: true,
          title: {
            display: true,
            text: 'Value'
          },
          ticks: {
            callback: function(value) {
              return formatAxisLabel(value);
            }
          }
        }
      },
      plugins: {
        pointStyle: false,
        tooltip: {
          callbacks: {
            title: function(context) {
              const dataIndex = context[0].dataIndex;
              const timestamp = statsData.timestamps[dataIndex];
              return moment(timestamp).format('YYYY-MM-DD HH:mm:ss');
            }
          }
        }
      }
    };

    // Destroy existing charts
    if (trafficChart) trafficChart.destroy();
    if (packetsChart) packetsChart.destroy();
    if (bandwidthChart) bandwidthChart.destroy();
    if (throughputChart) throughputChart.destroy();

    // Traffic Chart
    trafficChart = new Chart(document.getElementById('trafficChart'), {
      type: 'line',
      data: {
        labels: labels,
        datasets: [{
          label: 'Bytes Sent',
          data: statsData.bytes_sent,
          borderColor: 'rgb(75, 192, 192)',
          tension: 0.2
        }, {
          label: 'Bytes Received',
          data: statsData.bytes_recv,
          borderColor: 'rgb(255, 99, 132)',
          tension: 0.2
        }]
      },
      options: {
        ...chartOptions,
        scales: {
          ...chartOptions.scales,
          y: {
            ...chartOptions.scales.y,
            title: {
              display: true,
              text: 'Bytes'
            }
          }
        },
        plugins: {
          ...chartOptions.plugins,
          title: {
            display: true,
            text: 'Network Traffic'
          },
          tooltip: {
            callbacks: {
              label: function(context) {
                return context.dataset.label + ': ' +
                  formatBytes(context.parsed.y);
              }
            }
          }
        }
      }
    });

    // Packets Chart
    packetsChart = new Chart(document.getElementById('packetsChart'), {
      type: 'line',
      data: {
        labels: labels,
        datasets: [{
          label: 'Packets Sent',
          data: statsData.packets_sent,
          borderColor: 'rgb(153, 102, 255)',
          tension: 0.2
        }, {
          label: 'Packets Received',
          data: statsData.packets_recv,
          borderColor: 'rgb(255, 159, 64)',
          tension: 0.2
        }]
      },
      options: {
        ...chartOptions,
        scales: {
          ...chartOptions.scales,
          y: {
            ...chartOptions.scales.y,
            title: {
              display: true,
              text: 'Packets'
            }
          }
        },
        plugins: {
          ...chartOptions.plugins,
          title: {
            display: true,
            text: 'Network Packets'
          },
          tooltip: {
            callbacks: {
              label: function(context) {
                return context.dataset.label + ': ' +
                  context.parsed.y.toLocaleString();
              }
            }
          }
        }
      }
    });

    // Bandwidth Chart
    bandwidthChart = new Chart(document.getElementById('bandwidthChart'), {
      type: 'line',
      data: {
        labels: labels,
        datasets: [{
          label: 'Bandwidth Sent',
          data: bandwidthData.bandwidth_sent,
          borderColor: 'rgb(255, 206, 86)',
          tension: 0.2
        }, {
          label: 'Bandwidth Received',
          data: bandwidthData.bandwidth_recv,
          borderColor: 'rgb(75, 192, 192)',
          tension: 0.2
        }]
      },
      options: {
        ...chartOptions,
        scales: {
          ...chartOptions.scales,
          y: {
            ...chartOptions.scales.y,
            title: {
              display: true,
              text: 'Bytes/s'
            },
            ticks: {
              callback: function(value) {
                return formatAxisLabel(value) + 'B/s';
              }
            }
          }
        },
        plugins: {
          ...chartOptions.plugins,
          title: {
            display: true,
            text: 'Network Bandwidth'
          },
          tooltip: {
            callbacks: {
              label: function(context) {
                return context.dataset.label + ': ' +
                  formatBytes(context.parsed.y) + 'B/s';
              }
            }
          }
        }
      }
    });

    // Throughput Chart
    throughputChart = new Chart(document.getElementById('throughputChart'), {
      type: 'line',
      data: {
        labels: labels,
        datasets: [{
          label: 'Throughput Sent',
          data: throughputData.throughput_sent,
          borderColor: 'rgb(153, 102, 255)',
          tension: 0.2
        }, {
          label: 'Throughput Received',
          data: throughputData.throughput_recv,
          borderColor: 'rgb(255, 159, 64)',
          tension: 0.2
        }]
      },
      options: {
        ...chartOptions,
        scales: {
          ...chartOptions.scales,
          y: {
            ...chartOptions.scales.y,
            title: {
              display: true,
              text: 'Packets/s'
            }
          }
        },
        plugins: {
          ...chartOptions.plugins,
          title: {
            display: true,
            text: 'Network Throughput'
          },
          tooltip: {
            callbacks: {
              label: function(context) {
                return context.dataset.label + ': ' +
                  context.parsed.y.toLocaleString() + ' packets/s';
              }
            }
          }
        }
      }
    });
  });
}


function updateDevices() {
  fetch('/devices')
    .then(response => response.json())
    .then(data => {
      const table = `
                <table>
                    <tr>
                        <th>IP Address</th>
                        <th>MAC Address</th>
                        <th>Hostname</th>
                        <th>First Seen</th>
                        <th>Last Seen</th>
                    </tr>
                    ${data.map(device => `
                        <tr>
                            <td>${device.ip}</td>
                            <td>${device.mac}</td>
                            <td>${device.hostname}</td>
                            <td>${formatTimeAgo(device.first_seen)}</td>
                            <td>${formatTimeAgo(device.last_seen)}</td>
                        </tr>
                    `).join('')}
                </table>
            `;
      document.getElementById('deviceList').innerHTML = table;
    });
}

// Update charts and stats every 2 seconds
setInterval(() => {
  updateCharts();
  updateAdditionalStats();
}, 2000);

// Update devices list every 30 seconds
setInterval(updateDevices, 30000);

// Initial updates
updateCharts();
updateAdditionalStats();
updateDevices();
