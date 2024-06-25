# Breakout game using OPENGL

## How to build:

> 💻 This is a visual studio project. Just open .sln file with visual studio 22, and the project just runs.

> 🎙 I used [IrrKlang](https://www.ambiera.com/irrklang/) to play audio in the game, please go into <mark style="background-color:rgb(252, 248, 227);">**${SolutionDir}/dlls**</mark> and manually copy all the dlls and paste into the build folder for now(Sorry for the inconvenience, I'll add some scripts later 😅)

![image](https://github.com/quangcrazymen/Breakout-Game-OpenGL/assets/80439365/f59c5be7-d42c-4d8b-ab2a-4b0836220162)

## Feature list:

- Classic breakout games
- Better graphics :joy:
- 4 Level
- Endless mode
- Game editor

## Task list:

- [x] Basic gameplay
- [x] Post-processing
- [x] Power-ups
- [x] Audio

### List of Power-ups

| Feature | Description                  | Looks |
| ------- | ---------------------------- | ----|
| Speed (Positive)   | Speed up the ball            |<img width="200" height="50" src="https://github.com/quangcrazymen/Breakout-Game-OpenGL/assets/80439365/6d87aab6-9340-4955-8ef7-8c185b0af22f">|
| Sticky (Positive)   | Stick the ball to the paddle |<img width="200" height="50" src="https://github.com/quangcrazymen/Breakout-Game-OpenGL/assets/80439365/ad8b47c4-d3ed-4fe4-ab60-89938986b34e">|
| Pass-through (Positive)  | The ball can penetrate through all non-solid block | <img width="200" height="50" src="https://github.com/quangcrazymen/Breakout-Game-OpenGL/assets/80439365/f86bdd42-8e89-4ab7-8474-4a28acea5932">|
| Increase (Positive)  | Sligthly increase the size of the paddle | <img width="200" height="50" src="https://github.com/quangcrazymen/Breakout-Game-OpenGL/assets/80439365/e3b7bc6f-6263-42c0-9c0f-06dfd4a1b1fc">|
| Confuse (Negative)  | Everything is upside down, color is converted to negative hue | <img width="200" height="50" src="https://github.com/quangcrazymen/Breakout-Game-OpenGL/assets/80439365/40fb27ce-c5bf-4e0c-a219-03c8963d4470">|
| Chaos (Negative)  | Just try it for you self🙃 | <img width="200" height="50" src="https://github.com/quangcrazymen/Breakout-Game-OpenGL/assets/80439365/9a65cb07-7f60-4bb4-a55b-fa5b4d95eae0">|

| Feature | Description                      |
| ------- | -------------------------------- |
| UI      | Imgui to count FPS, tweak number |
| Editor  | WIP                              |
