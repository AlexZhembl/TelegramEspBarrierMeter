# TelegramEspBarrierMeter
Simple IoT solution to observe any barrier and notify via TelegramBot.
Used as waiter notifyer with bills machine in one of the pubs. Just place the device near bill socket and you'll have message from telegram bot.
<br>

#### Components used
- YL-63 Barier sensor
- Esp8266
- LM1117 DC-DC

#### How to use?
1. Plug in the device with usb port to any charging socket with at least 0.5amps currency (your phone charger is suitable)
2. Wait untill Green led will turn off - means device has connected to WIFI
3. Block YL-63 light sinsort with any barrier (like hand or paper), you'll have immideatelly have a notifiction from Telegram.
4. Algorithm contains some logic to avoid noise from sensor, so if barrier needs to be dissapear and appear again - it need to wait 2sec delay (see SECONDS_TO_TRACK_BARRIER constant)

#### PCB schema
<img src="https://user-images.githubusercontent.com/7920555/177154770-b8cd60c6-4415-41a2-bdc2-bcd97cbb4824.png" width="600" height="500">

#### Code and Firmware
- Create your own instagram bot: https://core.telegram.org/bots, save the bot_token (Get from Botfather)
- Add this bot to any new created chat, get chat_id
- Use arduino IDE as well
- Change the WIFI_SSID and WIFI_PASSWORD in BarrierSensorHTTPClient.ino
- Change the <bot_token> and <chat_id> in BarrierSensorHTTPClient.ino
- flash ESP via any USB-UART tool
