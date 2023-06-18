## Run with

`platformio run --target uploadfs --environment d1_mini && platformio run --target upload --upload-port /dev/cu.usbserial-A50285BI`

<!-- - We need both commands because the first will save any `.html` file into the ESP file system and the second will flash the code. -->

- You can replace `d1_mini` with your env/board inside `platformio.ini`.

## Web Page

<s> Each HTML page can only have up to 14kB of space. We can reduce it by minifying the code: </s>

This is no longer a constraint. Now we use the ESP file system (littleFS) to pass the html page (limit size not tested yet).

 - For JavaScript, we can use this [page](https://www.toptal.com/developers/javascript-minifier).

## Icons

Icon pack from [ikonate.com](https://ikonate.com/).

<!-- ## Models

- Models
  - (A - Expert)
      - (Provided CAD design)
      - (Provided PCB design)
      - (No hardware provided)
  - (B - Advanced)
      - (Provided CAD design)
      - (Provided PCB)
      - (No hardware provided)
  - (C - Medium)
      - (Provided CAD design)
      - (Provided PCB)
      - (Provided hardware)
  - (D - Beginner)
      - (Provided CAD)
      - (Provided PCB)
      - (Provided hardware) -->
