#define PIN_OUT PB1  // 输出引脚
#define PERIOD 20    // 50Hz，对应 20ms 周期（高10ms，低10ms）
#define RUN_TIME 600000   // 运行时间：10分钟（毫秒）
#define STOP_TIME 1200000 // 停止时间：20分钟（毫秒）

unsigned long previousMillis = 0;
unsigned long cycleStartMillis = 0;
bool state = false;
bool running = true;  // 是否处于运行状态

void setup() {
    pinMode(PIN_OUT, OUTPUT);
    cycleStartMillis = millis(); // 记录循环开始时间
}

void loop() {
    unsigned long currentMillis = millis();

    // 计算当前是否在 10 分钟的运行时间内
    if (running) {
        // 运行状态：输出 50Hz 信号
        if (currentMillis - previousMillis >= PERIOD / 2) { // 每 10ms 翻转一次
            previousMillis = currentMillis;
            state = !state;
            digitalWrite(PIN_OUT, state);
        }

        // 如果运行超过 10 分钟，切换到停止状态
        if (currentMillis - cycleStartMillis >= RUN_TIME) {
            running = false;  // 进入停止状态
            digitalWrite(PIN_OUT, LOW); // 关闭信号
            cycleStartMillis = currentMillis; // 记录停止时间起点
        }
    } 
    else {
        // 停止状态：保持低电平
        digitalWrite(PIN_OUT, LOW);

        // 如果停止超过 20 分钟，重新启动输出
        if (currentMillis - cycleStartMillis >= STOP_TIME) {
            running = true;  // 进入运行状态
            cycleStartMillis = currentMillis; // 记录启动时间
            previousMillis = currentMillis;   // 重新开始 PWM 计时
        }
    }
}
