## Run with

`platformio run --target uploadfs --environment d1_mini && platformio run --target upload --upload-port /dev/cu.usbserial-A50285BI`

<!-- - We need both commands because the first will save any `.html` file into the ESP file system and the second will flash the code. -->

## Web Page

<s> Each HTML page can only have up to 14kB of space. We can reduce it by minifying the code: </s>

This is no longer a constraint. Now we use the ESP file system (littleFS) to pass the html page. The limit is related to the SPIFFS partition, 0x30000 bytes.

## Icons

Icon pack from [ikonate.com](https://ikonate.com/).

---

### Note

For some reason I haven't figured, the `WebServer.h` needs to be inside the `src` folder.
