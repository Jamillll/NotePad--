# NotePad--
### What is it?
Notepad-- is a basic plain text file editor similar to a text editor like notepad (on windows). 

### Why does it exist?
Originally I just wanted practice at making a simple desktop application and chose a plain text editor because it was an area I had practice in before (having basically made this same thing as a console application). Now it has a genuine purpose. Microsoft's notepad app is has changed recently and added quite a couple features that annoy me to no end, they've added a tabs system so a single notepad instance can hold multiple files, and the saving is really weird and annoying and closing it is just a hassle. Its a mess. It's actually a really well made app but shut up-

On top of that I want to use this as an opportunity to both make this a fully feature complete program, as I plan to use it personally, and set up proper testing since the amount of features will be small, making it a nice simple way to learn those processes.

## TODO
### Features to impliment
- Set up a testing framework
- Design a logo and impliment it in the main window
- Zoom font size in and out with controll and scroll wheel
put open and save buttons in am ImGUI menubar instead of just having them as buttons

### Known issues
- Ctrl + O shortcut won't work (and commented out right now) most of the time due to ImGui Multiline text input not updating its own internal buffer while focused, it would only work if the text field was out of focus
