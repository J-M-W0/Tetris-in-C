# Tetris in C

Welcome to the Tetris game implemented in C language! 
This project aims to recreate the classic Tetris experience using simple and efficient C code.

## Table of Contents

- [Features](#features)
- [Demo](#demo)
- [Installation](#installation)
- [Usage](#usage)
- [Code Structure](#code-structure)
- [Contributing](#contributing)
- [License](#license)
- [Acknowledgements](#acknowledgements)

## Features

- **Classic Tetris Gameplay**: Enjoy the nostalgic Tetris game with traditional mechanics.
- **Score Tracking**: Keep track of your score as you clear lines.
- **Various Tetromino Shapes**: Play with all the classic Tetris shapes.
- **Game Over Detection**: The game accurately detects when there are no more moves left.

## Demo

### Watch the YouTube Demo Video I uploaded
[Watch the demo video](https://www.youtube.com/watch?v=ZUFBVfejH8s)

## Installation

To set up the Tetris game on your local machine, follow these steps:

1. **Clone the Repository**: Download the repository to your local machine using git.
    ```sh
    git clone <repo>
    ```

2. **Navigate to the Project Directory**: Change your current directory to the project's root directory.
    ```sh
    cd <repo-directory>
    ```

3. **Compile the Program**: Use Makefile to compile the Tetris program.
    ```sh
    make
    ```

4. **Run the Program**: Execute the compiled program to start playing Tetris.
    ```sh
    ./tetris
    ```

## Usage

Once the game is running, use the following keyboard controls to play:

- **Left Arrow Key**: Move the tetromino left.
- **Right Arrow Key**: Move the tetromino right.
- **Down Arrow Key**: Move the tetromino down faster.
- **Up Arrow Key**: Rotate the tetromino.

### Gameplay Instructions

1. **Objective**: The goal of the game is to score points by clearing lines. You clear a line by filling every square within a single row.
2. **Tetromino Shapes**: The game includes all seven standard Tetris shapes (I, O, T, S, Z, J, L).
3. **Scoring**: Points are awarded for every line cleared. Clearing multiple lines at once increases your score significantly.
4. **Game Over**: The game ends when new tetrominoes can no longer be placed at the top of the playfield.

## Code Structure

The project consists of the following files:

- `README.md`: Documentation file providing an overview of the project and instructions for setup and usage.
- `main.c`: The entry point of the program.
- `tetrisdef.c`: Contains the main game logic, including the game loop, input handling, and rendering.
- `tetrisfunc.c`: Contains the functions about drawing the tetris, and tetris moving logics.
- `gridfunc.c`: Contains the functions about drawing the game grid, and tetris grid.

## Contributing

Contributions are welcome! If you have any ideas for improvements or find any bugs, feel free to open an issue or submit a pull request. Please follow these steps:

1. Fork the repository.
2. Create a new branch (`git checkout -b feature-branch`).
3. Commit your changes (`git commit -am 'Add new feature'`).
4. Push to the branch (`git push origin feature-branch`).
5. Create a new Pull Request.

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for more details.

## Acknowledgements

- Inspired by the classic Tetris game.
- Developed by [Junzhe Wang](https://github.com/J-M-W0).
- Special thanks to the C programming community for their support and resources.


