# Square Clicker
Course work project. C++ OpenGL clicker made with freeglut.

## Credits
* I used [Sancaus\`s repo](https://github.com/sancau/simple-clicker) as a reference. Some functions and methods are taken directly from there.
* Also this project uses [stb_image.h](https://github.com/nothings/stb/blob/master/stb_image.h) to load textures (in fact, minecraft textures, lol). Texture implementation was added in a hurry because I would have got a bad mark without them, so the code looks messy. 😛

## Description
This is a clicker game where you need to reach 50k points to win. There're 3 upgrades that'll help you to do this faster. You can click on the Square with your mouse AND spacebar (though it's more of a debug system) and buy the upgrades with points called Clicks.
![](/Preview.png?raw=true "Preview of the game.")

## Crucial Information
To run the application you must have the `freeglut.dll` next to you .exe file. This project makes use of `opengl` and `freeglut` libraries (also `freeglut.h` header), so don't forget to include them.

There are 5 .png\`s for Square "skins" and one background image. You can change them to whatever you prefer, but it's strongly adviced NOT to use images bigger than 512x512 pixels.