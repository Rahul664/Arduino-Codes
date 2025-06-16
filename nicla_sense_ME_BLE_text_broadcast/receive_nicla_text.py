import asyncio
from bleak import BleakScanner, BleakClient

TARGET_NAME = "XYZNicla"  # Use exact name
CHAR_UUID = "19b10000-2000-537e-4f6c-d104768a1214"


def handle_notification(sender, data):
    print(f"🔔 [{asyncio.get_event_loop().time():.1f}s] Data: {data.decode('utf-8')}")


async def main():
    while True:
        print("\n🔍 Scanning for BLE devices...")
        try:
            devices = await BleakScanner.discover(timeout=5.0)
            target_device = next((d for d in devices if d.name and d.name == TARGET_NAME), None)

            if not target_device:
                print("❌ Device not found. Retrying...")
                await asyncio.sleep(1)
                continue

            print(f"✅ Found {target_device.name} ({target_device.address})")
            async with BleakClient(target_device.address, timeout=10.0) as client:
                print(f"🔗 Connected to {target_device.name}")
                await client.start_notify(CHAR_UUID, handle_notification)
                print("📡 Listening for data...")

                # Monitor connection state
                last_seen = asyncio.get_event_loop().time()
                while True:
                    if not client.is_connected:
                        print("⚠️ Unexpected disconnection!")
                        break

                    await asyncio.sleep(0.5)

        except Exception as e:
            print(f"⚠️ Error: {str(e)}. Reconnecting...")
            await asyncio.sleep(1)


if __name__ == "__main__":
    try:
        asyncio.run(main())
    except KeyboardInterrupt:
        print("\nExited by user")