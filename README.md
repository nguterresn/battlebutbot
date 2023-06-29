# BattleButBot: Your Ultimate Antweight Fighting Robot Companion

BattleButBot is a small and powerful robot designed specifically for the Antweight class of robot combat events. With its sleek design, sturdy construction, and advanced control features, BattleButBot is the perfect choice for robot fighting enthusiasts of all skill levels.

## Features

- **Intuitive Web-based Control**: BattleButBot can be easily controlled from any device with a web browser, allowing you to take full control of your robot in real-time.
- **Powerful Motors**: BattleButBot's high-torque motors provide superior performance and speed, allowing your robot to deliver powerful punches and moves.
- **Durable Build**: BattleButBot is built to withstand the toughest battles in Antweight robot combat events. Its rugged construction and impact-resistant design ensure that your robot stays in one piece, no matter how intense the fight gets.
- **Customizable Weapons**: BattleButBot's weapons can be customized to suit your fighting style. With a range of weapons and attachments available, you can build your robot to be the ultimate fighting machine.
- **Easy to Use**: BattleButBot is easy to use and requires no special skills or training. With its intuitive controls and simple setup process, you can start battling right away.

## Clone

Clone the project by running the following command:

```bash
git clone --recurse-submodules -j8 git@github.com:nguterresn/battlebutbot.git
```

The option `-j8` will allow the command to download up to 8 sumodules in parallel. 


## Goal

* Design the skeleton of the battle bot and list all the required hardware components.
* Assemble the battle bot by mounting all the necessary parts.
* Compete in battles to test the performance of the battle bot.
* Iterate and improve the design based on the performance results.
* Profit from your successful battle bot design.

## List of requirements

* **Cheap**: Priced under $50/500kr
* **Weight**: Weighs less than 150 milligrams
* **Acessable**: All parts are easily available
* **Flexible**: Can be controlled over WiFi or using an RF controller
* **Simple**: All hardware components are easy to assemble
* **Portable**: Powered by a lithium battery

## List of hardware:

| Hardware                 | Qty | Price |
|--------------------------|-----|-------|
| [N20 Gear Motor 6V 600RPM](https://www.aliexpress.com/item/1005003480074662.html?spm=a2g0o.cart.0.0.66f238dazFIII7&mp=1) | 2   | 90kr  |
| [DollaTek 5PCS DRV8833 1.5A 2-Channel DC Motor Drive Board](https://www.amazon.se/DollaTek-drivbräda-ultra-liten-drivmodul-ingångsspänning/dp/B07ML2RDNY/ref=sr_1_1?crid=39VO6618PX6XD&keywords=DRV8833&qid=1667334481&qu=eyJxc2MiOiIyLjI4IiwicXNhIjoiMS43NiIsInFzcCI6IjAuOTIifQ%3D%3D&sprefix=drv8833%2Caps%2C115&sr=8-1)              | 1   | 17kr  |
| [Wemos D1 Mini ESP8266](https://www.amazon.se/-/en/dp/B01N9RXGHY/ref=twister_B08BY192W7?_encoding=UTF8&psc=1) | 1   | 87kr  |

## Pinout

![pinout-diagram](https://user-images.githubusercontent.com/38976366/216715656-edc0af38-324e-40f0-a209-d9a60cee573b.svg)

## How to open the GUI

Connect using WiFi to `BattleButBot`.

<img src="https://user-images.githubusercontent.com/38976366/205155319-393798c9-7dc4-4a2e-bb77-cfcf4a954b22.PNG" width="30%"/>

Open `bot.local` on you browser.

<img src="https://user-images.githubusercontent.com/38976366/229373820-6bef6aad-05de-4926-8b85-3b51f318f65f.jpeg" width="30%"/>

## About the GUI

To control BattleButBot, simply use the **joystick** located in the center of the screen. To configure your joystick settings, click the `⚙️ Config` button.

You can monitor your robot's speed with the speed meter located above the joystick, which displays your robot's speed in meters per second.

Although the **action** button is currently inactive, it will be available in the near future.

For ease of development while the robot firmware is unstable or in development, a console log is located at the bottom of the screen. In the future, an option will be added to hide this log.

## Robot Controls

You can control BattleButBot using the joystick on the graphical user interface (GUI). To move forward, drag the joystick upwards, and to move backward, drag the joystick downwards. The joystick works on an X and Y axis, with Y controlling the speed of the robot and X controlling the direction of movement (left or right).

## Technical Details

(TBA)

## 3rd Party Libraries

- [ESPAsyncWebServer](https://github.com/me-no-dev/ESPAsyncWebServer)
- [Joystick 2](https://github.com/bobboteck/JoyStick)
- [CSS Skeleton Framework](https://skeleton-framework.github.io)

## Tools

- VSCode with PlatformIO
- Fusion360

## Support

If you have any questions or issues with BattleButBot, please contact guterresnogueira@gmail.com. We're always here to help you get the most out of your robot.
