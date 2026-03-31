#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>
#include "USB.h"
#include "USBHIDKeyboard.h"

USBHIDKeyboard Keyboard;
BLECharacteristic *pCharacteristic;
bool deviceConnected = false;

#define SERVICE_UUID        "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"

class MyServerCallbacks: public BLEServerCallbacks {
    void onConnect(BLEServer* pServer) { deviceConnected = true; }
    void onDisconnect(BLEServer* pServer) {
        deviceConnected = false;
        pServer->getAdvertising()->start();
    }
};

class MyCallbacks: public BLECharacteristicCallbacks {
    void onWrite(BLECharacteristic *pCharacteristic) {
        String value = pCharacteristic->getValue().c_str();
        if (value.length() > 0) {
            if (value.indexOf("LUO!") != -1) {
                Keyboard.press(KEY_LEFT_SHIFT);
                delay(50);
                Keyboard.releaseAll();
                delay(200);
            }
            Keyboard.print(value);
        }
    }
};

void setup() {


  // --- 深度模拟罗技 K120 键盘 (关键修改点) ---
  USB.VID(0x046D);               // Logitech 供应商 ID
  USB.PID(0xC31C);               // K120 键盘产品 ID
  USB.productName("Logitech USB Keyboard");
  USB.manufacturerName("Logitech");
  USB.serialNumber("LGP920820"); // 模拟一个伪随机序列号

  Keyboard.begin();
  USB.begin();

  // --- 蓝牙初始化 ---
  BLEDevice::init("Logitech-BT-Link"); // 建议也改成 Logi-BT-Link
  BLEServer *pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());
  BLEService *pService = pServer->createService(SERVICE_UUID);
  pCharacteristic = pService->createCharacteristic(
                      CHARACTERISTIC_UUID,
                      BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_WRITE | BLECharacteristic::PROPERTY_NOTIFY
                    );
  pCharacteristic->setCallbacks(new MyCallbacks());
  pCharacteristic->addDescriptor(new BLE2902());
  pService->start();
  BLEDevice::getAdvertising()->start();
}

void loop() { delay(100); }