import os
import sys
import subprocess
import netifaces


from config import (
    REQUIRED_IP,
    REQUIRED_SSID, 
    INTERFACE
)
    
    
# === Get current IP address ===
def get_current_ip(interface):
    try:
        ip = netifaces.ifaddresses(interface)[netifaces.AF_INET][0]['addr']
        return ip
    except Exception as e:
        print(f"❌ Failed to get IP address on {interface}: {e}")
        return None


# === Get current Wi-Fi SSID ===
def get_current_ssid():
    try:
        result = subprocess.check_output(["nmcli", "-t", "-f", "active,ssid", "dev", "wifi"], text=True)
        for line in result.strip().split("\n"):
            if line.startswith("yes:"):
                return line.split(":")[1]
    except Exception as e:
        print(f"❌ Failed to get SSID: {e}")
    return None


# === Safety check before continuing ===
def validate_network():
    current_ssid = get_current_ssid()
    current_ip = get_current_ip(INTERFACE)

    print(f"📶 Connected SSID: {current_ssid}")
    print(f"🌐 IP Address on {INTERFACE}: {current_ip}")

    if current_ssid != REQUIRED_SSID:
        print(f"❌ SSID mismatch! Expected: {REQUIRED_SSID}, Found: {current_ssid}")
        if current_ip != REQUIRED_IP:
            print(f"❌ IP mismatch! Expected: {REQUIRED_IP}, Found: {current_ip}")
        sys.exit(1)

    if current_ip != REQUIRED_IP:
        print(f"❌ IP mismatch! Expected: {REQUIRED_IP}, Found: {current_ip}")
        sys.exit(1)
