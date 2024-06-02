# BattleButBot: Your Ultimate Antweight Pusher Robot Companion

BattleButBot is a small (<10x10cm) and light (<150g) robot designed specifically for the [Antweight class of robot combat events](https://www.robotwars101.org/ants/rules.htm). With its sleek design, sturdy construction, and advanced control features, BattleButBot is the perfect choice for robot fighting enthusiasts of all skill levels.

<img src="images/IMG_8674.jpg" width="100%"/>

## Features

- **Intuitive Web-based Control**: BattleButBot can be easily controlled from any device with a [web browser](#web-robot-controller), allowing you to take full control of your robot in real-time.
- **Powerful Motors**: BattleButBot's brush DC motors provide great performance and speed, allowing your robot to deliver powerful moves.
- **Durable Build**: BattleButBot is built to withstand the toughest battles in Antweight robot combat events. Its rugged construction and impact-resistant design ensure that your robot stays in one piece, no matter how intense the fight gets.
- **Easy to Use**: BattleButBot is easy to use and requires no special skills or training. With its intuitive controls and simple setup process, you can start battling right away.

## Requirements

**Cheap**: Priced under $50

- ✅ Costs 50$.

**Weight**: Equal or less than 150 milligrams

- ✅ Weigths ~110g. (PLA printed)

**Acessable**: All parts are easily available (can be obtained from anywhere)

- ✅ Parts can be found on [LCSC](lcsc.com), [Digikey](digikey.com) or [AliExpress](https://www.aliexpress.us).

**Flexible**: Can be controlled over WiFi

- ✅ Easy to use web browser GUI

**Simple**: All hardware components are easy to assemble

- ✅ The device uses [PH sockets](https://www.jst-mfg.com/product/index.php?series=199) and requires a few screws.

**Portable**: Powered by a lithium battery

- ✅ Small and light weight 2 cell battery (7.4V).

## Web Robot Controller

Connect to the `BattleButBot` network using WiFi.

<img src="https://user-images.githubusercontent.com/38976366/205155319-393798c9-7dc4-4a2e-bb77-cfcf4a954b22.PNG" width="30%"/>

Open `bot.local` on you browser.

<img src="images/IMG_8620.PNG" width="80%"/>

To control the BattleButBot, simply use both **joysticks** located in the screen.

### Robot Controls

You can control BattleButBot using the joysticks from the graphical user interface (GUI). To move forward, drag the left joystick upwards, and to move backward, drag the left joystick downwards. To lean the BattleButBot to the right, drag the right joystick to the right and vice-versa.

### Settings

To configure your joystick settings, click the `Settings` button.

<img src="images/IMG_8622.PNG" width="30%"/>

For ease of development while the robot firmware is unstable or in development, a console log is located at the bottom of the screen.

<!-- ## How to order

### Shopping list:

| Hardware                 | Qty | Price |
|--------------------------|-----|-------|
| [N20 Gear Motor 6V 600RPM](https://www.aliexpress.us/item/3256803245120861.html?spm=a2g0o.productlist.main.3.be16dmKLdmKLdh&algo_pvid=1b8b9a20-a58e-4537-a37a-af46f9d1652b&algo_exp_id=1b8b9a20-a58e-4537-a37a-af46f9d1652b-1&pdp_npi=4%40dis%21SEK%2125.63%2119.17%21%21%212.34%211.75%21%40211b61a417119945526086789eb5a6%2112000025761667070%21sea%21SE%210%21AB&curPageLogUid=N7UsGzjkJw8d&utparam-url=scene%3Asearch%7Cquery_from%3A&gatewayAdapt=glo2usa) | 2   | 1.36$ x 2 + 2.27$ shipping  |
| [Wheels](https://www.aliexpress.com/item/33026783171.html?spm=a2g0o.order_list.order_list_main.102.76381802470tYv)              | 2   | ~1$ + 4$ shipping |
| [Mini Switch](https://www.aliexpress.com/item/32873386670.html?spm=a2g0o.productlist.main.3.3333yVHtyVHtTG&algo_pvid=fb446a07-847d-47a1-b0f8-d08a0b7cde4f&algo_exp_id=fb446a07-847d-47a1-b0f8-d08a0b7cde4f-1&pdp_npi=4%40dis%21SEK%2115.41%2115.41%21%21%211.40%211.40%21%402103890917131116137334276e13e5%2165526366999%21sea%21SE%21939121189%21&curPageLogUid=9vZMWAunkpDf&utparam-url=scene%3Asearch%7Cquery_from%3A)      | 5 (lot)   | ~1$ + 2$ shipping |
| [BOM](https://github.com/nguterresn/battlebutbot/blob/main/board/bubblebutbot/jlcpcb/production_files/BOM-bubblebutbot.csv)              | 1   | ~10$ + 10$ [shipping](LCSC.com)  |
| [PCB](https://github.com/nguterresn/battlebutbot/blob/main/board/bubblebutbot/jlcpcb/production_files/GERBER-bubblebutbot.zip)              | 5   | ~2$ + 3$ [shipping](jlcpcb.com)
| Total | - | ~40$

When ordering the BOM, make sure to order at least 5 (five!) of each component so you end up with the possibility to solder 5 different PCBs. -->

<!-- ## Design

The design of the BattleButBot plays an important role. How it is designed determines how heavy (or how light) it is. Two requirements: sturdy and light.

<img src="images/79d8942c-3e40-4c1b-89ab-f2965e4c2efd.JPG" width="50%"/>

### Cyberpunk

A cyberpunk alike robot is cold as hell. The low poly edges also make it easier to print.

## Assemble

<img src="images/IMG_8643.jpg" width="80%"/>

What you need:

* 6 M3 5mm screws
* The [body](https://github.com/nguterresn/battlebutbot/blob/main/body/Car.stl)
* The [lid](https://github.com/nguterresn/battlebutbot/blob/main/body/LidThin.stl)
* Two [joints](https://github.com/nguterresn/battlebutbot/blob/main/body/Bot%20Wide%20Wheels_Juntas%20v3.stl)
* A 7.4V Lithium battery
* The [PCB](https://github.com/nguterresn/battlebutbot/tree/main/board/bubblebutbot)
* The two wheels
* A switch

### Motors

Place both motors with the gears facing the top (to prevent any friction with the bottom).

<img src="images/IMG_8645.jpg" width="80%"/>

Place the joint on top of the motor and screw it tight.

<img src="images/IMG_8646.jpg" width="80%"/>

### Battery

Place the battery close to the front of the bot.

<img src="images/IMG_8647.jpg" width="80%"/>

Place the switch.

<img src="images/IMG_8648.jpg" width="80%"/>

<img src="images/IMG_8649.jpg" width="80%"/>

### PCB

Before screwing the PCB down, finish all the connections.

<img src="images/IMG_8651.jpg" width="80%"/>

Place the PCB and screw it down (2 screws are enough).

<img src="images/IMG_8652.jpg" width="80%"/> -->

## Develop

Clone the project by running the following command:

```bash
git clone git@github.com:nguterresn/battlebutbot.git
```

### Tools

- VSCode with PlatformIO
- Fusion360

### 3rd Party Libraries

- [ESPAsyncWebServer](https://github.com/me-no-dev/ESPAsyncWebServer)
- [Joystick 2](https://github.com/bobboteck/JoyStick)

## Support

If you have any questions or issues with the BattleButBot, please contact guterresnogueira@gmail.com.
