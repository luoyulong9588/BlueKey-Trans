# ⌨️ 蓝牙键传 (BlueKey-Trans) —— 绕过内网管控的物理注入神器

**Luo-Link: BlueKey-Trans** 是一款专为**禁用 USB 存储、无外网连接**的高安全环境设计的数据“注入”系统。它与 [Air-Gapped QR Transfer](https://github.com/luoyulong9588/Air-Gapped-QR-Transfer) 配合使用，构成了完整的内网双向数据摆渡方案。

---

## 💡 为什么需要它？
在内网环境下，安全软件通常会上报 USB 存储接入，但**USB 键盘**通常被视为合法设备。本项目将 ESP32-S3 伪装成键盘，通过手机蓝牙将数据“敲”进电脑，完美绕过 U 盘禁令。

## 🚀 核心特性
* **物理级隐蔽**：电脑识别为标准 HID 键盘，无需驱动，免安装客户端。
* **全类型摆渡**：支持长篇**中文字符**直接粘贴，或 **Word/Excel/JPG** 等小文件传输。
* **极速压缩**：集成 `pako.js` (Gzip Level 9)，传输体积缩减约 70%，大幅节省“打字”时间。
* **环境自适应**：启动时自动模拟 `Shift` 键，强制切换 Windows 输入法至英文模式。
* **高可靠性**：采用 `LUO!` 特征头识别与数据完整性校验，防止乱码。

## 🛠️ 技术栈
* **硬件**: ESP32-S3 (原生 USB 支持)。
* **通信**: BLE 5.0 + USB HID 模拟。
* **前端**: HTML5 (iOS 玻璃拟态 UI) + Web Bluetooth API。
* **算法**: `pako.js` (Zlib) + Base64 隧道编码。

## 🔗 联动方案 (双向摆渡)
* **入内网 (手机 -> 电脑)**：使用本项目 **BlueKey-Trans**，利用模拟键盘注入数据。
* **出内网 (电脑 -> 手机)**：使用 [Air-Gapped QR Transfer](https://github.com/luoyulong9588/Air-Gapped-QR-Transfer)，通过屏幕显示二维码，手机扫码提取。

## 📋 许可协议
MIT License. 由 ** (Yulong)** 开发。