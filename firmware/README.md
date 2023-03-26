## Run with

`platformio run --target uploadfs --environment d1_mini && platformio run --target upload --upload-port /dev/cu.usbserial-A50285BI`

You can replace `d1_mini` with your env/board.
We need both commands because the first will save any `.html` file into the ESP file system and the second will flash the code.

## Web Page

<s> Each HTML page can only have up to 14kB of space. We can reduce it by minifying the code: </s>

This is no longer a constraint. Now we use the ESP file system to pass the html page (Limit size not tested yet).

 - For JavaScript, we can use this [page](https://www.toptal.com/developers/javascript-minifier).


