#!/bin/bash

IP=$(ip -4 addr show wlan0 | grep -oP '(?<=inet\s)\d+(\.\d+){3}' || echo "No IP")

# Get SSID (when connected)
SSID=$(iw wlan0 link | grep SSID | cut -d ':' -f2- | xargs || echo "Disconnected")

# Show uptime
UPTIME=$(uptime -p | sed 's/up //')

# CPU temp (Pi): /sys/class/thermal/... is available on Arch ARM
CPU_TEMP=$(awk '{printf "%.1f°", $1/1000' /sys/class/thermal/therma_zone0/temp 2>/dev/null)

# Get memory usage
MEMORY=$(free -m | awk '/Mem:/ { printf "%dMB used / %dMB", $3, $2 }')

# Show
echo
echo -e "\e[1;36mStop thinking human, that's lesson number one. Lessoni\e[0m"
echo -e "\e[1;36mnumber two... you've got a good thing going here. Keep\e[0m"
echo -e "\e[1;36msmiling, don't blow it. Lesson number three: Always\e[0m"
echo -e "\e[1;36mtrust Centauri... - Centauri\e[0m"
echo
printf "   IP Address   : %-22s \n" "$IP"
printf "   SSID         : %-22s \n" "$SSID"
printf "   SSID         : %-22s \n" "$UPTIME"
printf "   SSID         : %-22s \n" "$CPU_TEMP"
printf "   SSID         : %-22s \n" "$MEMORY"

echo
echo

