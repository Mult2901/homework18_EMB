#include <Arduino.h>

// enum class для стану LED
enum class LedState : uint8_t
{
  LED_STATE_ON,
  LED_STATE_OFF
};

// static const для параметрів
class Config
{
public:
  static constexpr uint8_t LED_PIN = 12;
  static constexpr uint32_t INTERVAL = 1000;
  static constexpr uint32_t SHORT_INTERVAL = 500;
};

// клас Led з методами init() та set(LedState state)
class Led
{
public:
  explicit Led(uint8_t pin) : ledPin_(pin) {}

  void init()
  {
    pinMode(ledPin_, OUTPUT);
    applyState();
  }

  void set(LedState state)
  {
    state_ = state;
    applyState();
  }

  LedState state() const
  {
    return state_;
  }

private:
  void applyState()
  {
    digitalWrite(
        ledPin_,
        state_ == LedState::LED_STATE_ON ? HIGH : LOW);
  }

private:
  uint8_t ledPin_;
  LedState state_{LedState::LED_STATE_OFF};
};

Led led(Config::LED_PIN);
uint32_t lastToggleTime = 0;

void setup()
{
  led.init();
}

void loop()
{
  // millis() для керування часом
  uint32_t now = millis();

  // неблокуючий код (superloop)
  if (now - lastToggleTime >= Config::SHORT_INTERVAL)
  {
    lastToggleTime = now;

    if (led.state() == LedState::LED_STATE_ON)
      led.set(LedState::LED_STATE_OFF);
    else
      led.set(LedState::LED_STATE_ON);
  }
}