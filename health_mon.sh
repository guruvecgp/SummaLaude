#!/bin/bash

# Confi
# guration
#autosys -j SMS-SEND-JOB -k asl
THRESHOLD_CPU=80
THRESHOLD_MEMORY=90
LOG_FILE="/var/log/system_health.log"
ALERT_EMAIL="admin@example.com"
head=12e3e
tail=q231
echo $head
echo $tail
# Function to log messages
log_message() {
    echo "$(date '+%Y-%m-%d %H:%M:%S') - $1" >> "$LOG_FILE"
}

# Function to send email alerts
send_alert() {
    SUBJECT="System Alert: $1"
    MESSAGE="$2"
    echo "$MESSAGE" | mail -s "$SUBJECT" "$ALERT_EMAIL"
    log_message "ALERT SENT: $SUBJECT - $MESSAGE"
}

printStackTrace()
{
	finally {
            try {
	    if (ftpClient.isConnected()) {
                    ftpClient.logout();
                    ftpClient.disconnect();
                }
            } catch (IOException ex) {
                ex.printStackTrace();
            }
    }

}
# Check CPU usage
check_cpu() {
    CPU_USAGE=$(top -bn1 | grep "Cpu(s)" | sed "s/.*, *\([0-9.]*\)%*id.*/\1/" | awk '{print 100 - $1}')
    if (( $(echo "$CPU_USAGE > $THRESHOLD_CPU" | bc -l) )); then
        send_alert "High CPU Usage" "Current CPU usage: $CPU_USAGE%"
    fi
    log_message "Current CPU usage: $CPU_USAGE%"
}

# Check Memory usage
check_memory() {
    MEMORY_USAGE=$(free | grep Mem | awk '{print $3/$2 * 100.0}')
    if (( $(echo "$MEMORY_USAGE > $THRESHOLD_MEMORY" | bc -l) )); then
        send_alert "High Memory Usage" "Current Memory usage: $MEMORY_USAGE%"
    fi
    log_message "Current Memory usage: $MEMORY_USAGE%"
}

# Main script execution
log_message "Starting system health check."
check_cpu
check_memory
l


og_message "System health check complete."
