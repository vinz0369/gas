String ssid = "Simulator Wifi";  // Tên mạng Wifi để kết nối
String password = ""; // Mật khẩu của mạng Wifi (trống vì mạng này không có mật khẩu)
String host = "api.thingspeak.com"; // Địa chỉ host của Thingspeak, nơi dữ liệu sẽ được gửi đến
const int httpPort = 80; // Cổng HTTP sẽ được sử dụng
String uri = "/update?api_key=U3UN596KESQJ906U&field1="; // Đường dẫn (URI) và thông tin khóa API để gửi dữ liệu lên Thingspeak

int setupESP8266(void) {
  Serial.begin(115200);   // Khởi tạo giao tiếp Serial với baudrate 115200
  Serial.println("AT");   // Gửi lệnh "AT" để kiểm tra module ESP8266
  delay(10);        // Dừng một chút để chờ phản hồi từ module ESP8266
  if (!Serial.find("OK")) return 1; // Nếu không tìm thấy chuỗi "OK" trong phản hồi, trả về mã lỗi 1

  Serial.println("AT+CWJAP=\"" + ssid + "\",\"" + password + "\""); // Gửi lệnh kết nối đến mạng Wifi với tên mạng và mật khẩu đã được cấu hình
  delay(10);        // Dừng một chút để chờ phản hồi từ module ESP8266
  if (!Serial.find("OK")) return 2; // Nếu không tìm thấy chuỗi "OK" trong phản hồi, trả về mã lỗi 2
  
  Serial.println("AT+CIPSTART=\"TCP\",\"" + host + "\"," + httpPort); // Thiết lập kết nối TCP với host (Thingspeak) qua cổng HTTP đã cấu hình
  delay(50);        // Dừng một chút để chờ phản hồi từ module ESP8266
  if (!Serial.find("OK")) return 3; // Nếu không tìm thấy chuỗi "OK" trong phản hồi, trả về mã lỗi 3
  
  return 0; // Trả về 0 để báo hiệu rằng việc khởi tạo ESP8266 đã hoàn thành mà không có lỗi nào xảy ra
}

void anydata(void) {
  
  int temp = map(analogRead(A5), 85, 390, 0, 100); // Đọc giá trị từ cảm biến analog và chuyển đổi nó sang một phạm vi khác
  
  // Tạo chuỗi HTTP request để gửi dữ liệu lên Thingspeak
  String httpPacket = "GET " + uri + String(temp)  + " HTTP/1.1\r\nHost: " + host + "\r\n\r\n";
  
  int length = httpPacket.length(); // Đo chiều dài của gói tin HTTP
  
  Serial.print("AT+CIPSEND=");
  Serial.println(length); // Gửi lệnh để thông báo ESP8266 về chiều dài của gói tin HTTP sẽ được gửi đi
  delay(10); 

  // Gửi gói tin HTTP request
  Serial.print(httpPacket);
  delay(10); // Dừng một chút để chờ phản hồi từ ESP8266
  if (!Serial.find("SEND OK\r\n")) return; // Nếu không tìm thấy chuỗi "SEND OK" trong phản hồi, thoát khỏi hàm
}

void setup() {
  
  setupESP8266(); // Gọi hàm setupESP8266 để khởi tạo module ESP8266
  pinMode(A5, INPUT); // Cấu hình chân A5 là chân đầu vào
  pinMode(5, OUTPUT); // Cấu hình chân 5 là chân đầu ra
  pinMode(7, OUTPUT); // Cấu hình chân 7 là chân đầu ra
  pinMode(2, OUTPUT); // Cấu hình chân 2 là chân đầu ra
}

void loop() {
  
 anydata(); // Gọi hàm anydata để gửi dữ liệu lên Thingspeak
  
  Serial.println(analogRead(A5)); // In giá trị đọc từ cảm biến analog ra Serial Monitor
  // Điều khiển các chân đầu ra dựa trên giá trị đọc từ cảm biến analog
  if (analogRead(A5) <= 99) {
    digitalWrite(5, HIGH); // Nếu giá trị đọc nhỏ hơn hoặc bằng 99, đặt chân 5 ở mức cao
  } else {
    digitalWrite(5, LOW); // Ngược lại, đặt chân 5 ở mức thấp
  }
  if (analogRead(A5) > 99) {
    tone(7, 523, 1000); // Phát ra âm thanh với tần số 523 Hz trong 1 giây trên chân 7
    digitalWrite(2, HIGH); // Đặt chân 2 ở mức cao
  } else {
    digitalWrite(2, LOW); // Ngược lại, đặt chân 2 ở mức thấp
  }
  delay(1000); // Dừng 10 giây trước khi lặp lại
}
