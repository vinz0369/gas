# 🔥 Gas Sensor System with ESP8266

## 🚀 Giới Thiệu  
Dự án này triển khai hệ thống cảm biến khí gas sử dụng ESP8266 để gửi dữ liệu lên Thingspeak. Hệ thống gồm:
- Đọc dữ liệu từ cảm biến khí gas (chân A5)
- Gửi dữ liệu lên Thingspeak qua ESP8266
- Điều khiển còi báo động và đèn cảnh báo khi phát hiện khí gas vượt ngưỡng

## 📂 Cấu Trúc Dự Án  
```
gas_sensor_system
├── gas_sensor.ino         # Code chính của hệ thống
├── README.md              # Hướng dẫn sử dụng
```

## 🛠 Cài Đặt  

### 1️⃣ Phần Cứng Cần Thiết  
- **ESP8266** - Module WiFi để gửi dữ liệu
- **Cảm biến khí gas** - Kết nối với chân A5
- **Còi báo động** - Kết nối với chân 7
- **Đèn cảnh báo** - Kết nối với chân 2

### 2️⃣ Kết Nối Phần Cứng  
```
Cảm biến khí gas  -> ESP8266 (A5)
Còi báo động      -> ESP8266 (chân 7)
Đèn cảnh báo      -> ESP8266 (chân 2)
```

### 3️⃣ Cài Đặt Môi Trường Lập Trình  
- Cài đặt Arduino IDE
- Cài đặt thư viện ESP8266WiFi
- Thêm `http://arduino.esp8266.com/stable/package_esp8266com_index.json` vào Board Manager

### 4️⃣ Chạy Chương Trình  
1. **Cập nhật thông tin WiFi**
   - Chỉnh sửa `ssid` và `password` trong file code để phù hợp với mạng WiFi của bạn.

2. **Upload code lên ESP8266**
   - Kết nối ESP8266 với máy tính và nạp code qua Arduino IDE.

3. **Giám sát dữ liệu trên Thingspeak**
   - Mở Thingspeak và kiểm tra dữ liệu cảm biến được cập nhật theo thời gian thực.

## 📸 Cách Hoạt Động  
1. **Đọc Dữ Liệu Cảm Biến**  
   - Cảm biến khí gas gửi dữ liệu analog đến chân A5 của ESP8266.
   - Giá trị này được chuẩn hóa trong phạm vi 0 - 100.

2. **Gửi Dữ Liệu Lên Thingspeak**  
   - Dữ liệu từ cảm biến được gửi lên Thingspeak thông qua lệnh HTTP.

3. **Cảnh Báo Khi Phát Hiện Khí Gas**  
   - Nếu giá trị khí gas vượt ngưỡng:
     - Đèn cảnh báo sáng (chân 2 HIGH)
     - Còi báo động kêu (chân 7 phát âm thanh tần số 523Hz)
   - Nếu mức khí gas an toàn:
     - Đèn cảnh báo tắt
     - Còi báo động ngừng kêu

## 🔥 Công Nghệ Sử Dụng  
- **ESP8266** - Gửi dữ liệu lên mạng
- **Arduino** - Điều khiển cảm biến và thiết bị cảnh báo
- **Thingspeak** - Lưu trữ và hiển thị dữ liệu khí gas

## 📌 Lưu Ý  
- Đảm bảo cảm biến hoạt động chính xác trước khi triển khai.
- Thay đổi ngưỡng cảnh báo tùy theo môi trường sử dụng.
- Kiểm tra kết nối WiFi và module ESP8266 để đảm bảo hệ thống hoạt động ổn định.


