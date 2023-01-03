# bubblebutbots

A (bubble but) battle bot.

You can search for:

 - [The 3D Model](https://github.com/nguterresn/bubblebutbots/tree/main/body)
 - [The firmware code (based on Arduino)](https://github.com/nguterresn/bubblebutbots/tree/main/firmware)
 - The PCB design

## Goal

* Create the skeleton of a battle bot and list all the required hardware.
* Mount.
* Battle.
* ?
* Profit.

## List of requirements

* **Cheap**: less than 50$/500kr
* **Weight**: less than 150 miligrams
* **Acessable**: parts easily available
* **Flexible**: work over WiFi or RF Controller
* **Simple**: all the hardware must be easy to assemble
* **Portable**: powered by a lithium battery

## List of hardware:

| Hardware                 | Qty | Price |
|--------------------------|-----|-------|
| [N20 Gear Motor 6V 600RPM](https://www.aliexpress.com/item/1005003480074662.html?spm=a2g0o.cart.0.0.66f238dazFIII7&mp=1) | 2   | 90kr  |
| [DollaTek 5PCS DRV8833 1.5A 2-Channel DC Motor Drive Board](https://www.amazon.se/DollaTek-drivbräda-ultra-liten-drivmodul-ingångsspänning/dp/B07ML2RDNY/ref=sr_1_1?crid=39VO6618PX6XD&keywords=DRV8833&qid=1667334481&qu=eyJxc2MiOiIyLjI4IiwicXNhIjoiMS43NiIsInFzcCI6IjAuOTIifQ%3D%3D&sprefix=drv8833%2Caps%2C115&sr=8-1)              | 1   | 17kr  |
| [Wemos D1 Mini ESP8266](https://www.amazon.se/-/en/dp/B01N9RXGHY/ref=twister_B08BY192W7?_encoding=UTF8&psc=1) | 1   | 87kr  |

## How to open the GUI

Connect using WiFi to `BubbleButBot`.

<img src="https://user-images.githubusercontent.com/38976366/205155319-393798c9-7dc4-4a2e-bb77-cfcf4a954b22.PNG" width="30%"/>

Open `bot.local` on you browser.

<img src="https://user-images.githubusercontent.com/38976366/210432287-72701887-a142-48db-ab18-691532257a02.jpg" width="30%"/>

## About the GUI

To control the robot you need to move the **joystick** placed in the middle of the screen. It is possible to **configure** by clicking in the button `⚙️ Config`.

Right above the joystick, there is a speed meter that will show the robot's speed in meters per second.

The **action** button is currently inactive.

At the bottom of the screen there is a console log to ease the development while the robot firmware is unstable or in development. A option will be added in the future to hide the text.

## Robot Controls

The robot can be controlled by the joystick that exist on the GUI. Drag up to go forward or down to go backwards. It essentially works based on a X and Y axis (2 quadrants), where Y is the speed of the robot and X is the direction of the movement (left or right).

## 3rd Party Libraries

- [ESPAsyncWebServer](https://github.com/me-no-dev/ESPAsyncWebServer)
- [Joystick 2](https://github.com/bobboteck/JoyStick)
- [CSS Skeleton Framework](https://skeleton-framework.github.io)

## Tools

- VSCode with PlatformIO
- Fusion360
