esphome:
  name: terminal-spi
  friendly_name: Terminal-SPI

esp32:
  board: esp32-s3-devkitc-1
  framework:
    type: arduino

# Enable logging
logger:

# Enable Home Assistant API
api:
  encryption:
    key: "so31NU81DsEBppoI6V03ybhqQZPS/vzCUDYB+O+qf9k="

ota:
  password: "f0c2e1749ab952fd46b4b46078784cdb"

wifi:
  ssid: !secret wifi_ssid
  password: !secret wifi_password

  # Enable fallback hotspot (captive portal) in case wifi connection fails
  ap:
    ssid: "Terminal-Spi Fallback Hotspot"
    password: "117S0PTxiwDu"

captive_portal:
uart:
  - id: myuart1
    rx_pin: 44
    baud_rate: 115200 
    debug:
      direction: RX
      dummy_receiver: true
      sequence:
        # - lambda: UARTDebug::log_hex(uart::UART_DIRECTION_RX, bytes, ':');
        - lambda: UARTDebug::log_string(direction, bytes);
        
font:
  - file: 'slkscr.ttf'
    id: font1
    size: 10

  - file: 'arial.ttf'
    id: font3
    size: 34

  # - file: 'arial.ttf'
  #   id: font4
  #   size: 18

switch:
  - platform: gpio
    name: "led"
    id: ledSPI
    pin: 40
    inverted: no
    #��ʼ��Ϊoff
    restore_mode: ALWAYS_OFF
  - platform: gpio
    name: "bck"
    id: bck
    pin: 46
    inverted: no
    #��ʼ��Ϊoff
    restore_mode: ALWAYS_ON
    
i2c:
  sda: 2 
  scl: 1
  scan: True

sensor:
  - platform: dht
    pin: 11
    temperature:
      name: "Terminal-spi Temperature"
      id: temperature_spi
    humidity:
      id: humidity_spi
      name: "Terminal-spi Humidity"
    update_interval: 10s
    model: DHT11

# sensor:
#   - platform: aht10 #dht12 #am2320 #
#     temperature:
#       name: "Terminal-spi Temperature"
#       id: temperature_spi
#     humidity:
#       name: "Terminal-spi Humidity"
#       id: humidity_spi
#     update_interval: 10s

spi:
  clk_pin: 12
  mosi_pin: 13
  miso_pin: 14

color:
  - id: my_red
    red: 100%
    green: 0%
    blue: 0%
  - id: my_color
    red: 100%
    green: 100%
    blue: 0%
  - id: my_green
    red: 0%
    green: 100%
    blue: 0%
  - id: my_blue
    red: 0%
    green: 0%
    blue: 100%

image:
  - file: "menu_spi.png"
    id: menu
    resize: 480x320
    type: RGB24
  - file: "ON_Light_SPI.png"
    id: ON_Light
    resize: 240x320
    type: RGB24
  - file: "OFF_Light_SPI.png"
    id: OFF_Light
    resize: 240x320
    type: RGB24

display:
  - platform: ili9xxx
    model: ili9488
    dc_pin: 42
    cs_pin: 3
    rotation: 180
    lambda: |-     
      it.image(0, 0, id(menu));
      it.printf(325, 105, id(font3), id(my_red), "%.1f", id(temperature_spi).state);
      it.printf(325, 245, id(font3), id(my_blue), "%.1f", id(humidity_spi).state);
      if (id(ledSPI).state) {
        it.image(0, 0, id(ON_Light));
      } 
      else {
        it.image(0, 0, id(OFF_Light));
      }

  # - platform: ssd1306_i2c
  #   model: "SSD1306 128x64"
  #   address: 0x3C
  #   lambda: |-
  #     it.print(0, 0, id(font4), "WillPower:");
  #     it.printf(0, 15, id(font4), "Temp: %.1f��C", id(temperature1).state);
  #     it.printf(0, 30, id(font4), "Humidity: %.1f%%", id(humidity1).state);
  #     if (id(led).state) {
  #       it.print(0, 45, id(font4), "state: ON");
  #     } 
  #     else {
  #       it.print(0, 45, id(font4), "state: OFF");
  #     }