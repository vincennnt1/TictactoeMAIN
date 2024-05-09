#include <SFML/Graphics.hpp>
#include <iostream>
#include <windows.h>  


void player_move(int board[3][3], int player, int x, int y)
{
    if (board[y][x] == 0)
    {
        if (player == 1)
            board[y][x] = 1;
        else if (player == 2)
            board[y][x] = 2;
    }
}

bool checkMouse(int board[3][3], int playerTurn, sf::RenderWindow& window)
{
    int x = sf::Mouse::getPosition(window).x;
    int y = sf::Mouse::getPosition(window).y;

    if (x >= 130 && x <= 370 && y >= 130 && y <= 370)
    {
        x = x - 130;
        y = y - 130;

        if (x >= 0 && x <= 80)
            x = 0;
        else if (x >= 81 && x <= 160)
            x = 1;
        else if (x >= 161 && x <= 240)
            x = 2;
        if (y >= 0 && y <= 80)
            y = 0;
        else if (y >= 81 && y <= 160)
            y = 1;
        else if (y >= 161 && y <= 240)
            y = 2;

        if (board[y][x] == 0)
        {
            player_move(board, playerTurn, x, y);
            return true;
        }
        else {
            return false;
        }

    }
}

void updateSprites(sf::Sprite sprites[3][3], int board[3][3], sf::Texture& potato, sf::Texture& steak)
{
    for (int x = 0; x < 3; x++)
    {
        for (int y = 0; y < 3; y++)
        {
            if (board[y][x] == 1)
            {
                sprites[y][x].setTexture(potato);
                sprites[y][x].setPosition(sf::Vector2f(135 + 80 * x, 135 + 80 * y));
                sprites[y][x].setScale(sf::Vector2f(0.15, 0.14));
            }
            if (board[y][x] == 2)
            {
                sprites[y][x].setTexture(steak);
                sprites[y][x].setPosition(sf::Vector2f(135 + 80 * x, 135 + 80 * y));
                sprites[y][x].setScale(sf::Vector2f(0.15, 0.14));
            }
        }
    }
}

sf::Text winner(sf::Font& font, int Tictactoe[3][3])
{
    sf::Text result;
    result.setFont(font);
    result.setCharacterSize(35);
    result.setPosition(sf::Vector2f(55, 400));

    if ((Tictactoe[0][0] == Tictactoe[1][1] && Tictactoe[1][1] == Tictactoe[2][2]) && (Tictactoe[0][0] != 0))
    {
        if (Tictactoe[0][0] == 1)
        {
            result.setString("Player 1 is the Winner!");
            return result;
        }
        else {
            result.setString("Player 2 is the Winner!");
            return result;
        }
    }

    if ((Tictactoe[2][0] == Tictactoe[1][1] && Tictactoe[1][1] == Tictactoe[0][2]) && (Tictactoe[2][0] != 0))
    {
        if (Tictactoe[2][0] == 1)
        {
            result.setString("Player 1 is the Winner!");
            return result;
        }
        else {
            result.setString("Player 2 is the Winner!");
            return result;
        }
    }

    for (int x = 0; x < 3; x++)
    {
        if ((Tictactoe[x][0] == Tictactoe[x][1] && Tictactoe[x][1] == Tictactoe[x][2]) && (Tictactoe[x][0] != 0))
        {
            if (Tictactoe[x][0] == 1)
            {
                result.setString("Player 1 is the Winner!");
                return result;
            }
            else {
                result.setString("Player 2 is the Winner!");
                return result;
            }
        }
        if ((Tictactoe[0][x] == Tictactoe[1][x] && Tictactoe[1][x] == Tictactoe[2][x]) && (Tictactoe[0][x] != 0))
        {
            if (Tictactoe[0][x] == 1)
            {
                result.setString("Player 1 is the Winner!");
                return result;
            }
            else {
                result.setString("Player 2 is the Winner!");
                return result;
            }
        }
    }
    result.setString('0');
    return result;
}

int main()
{
    // tracks player turn, 1 = potato, 2 = steak
    int playerTurn = 1;

    // tracks amount of turns taken
    int turns = 0;

    //declares window, "sf::Style::Titlebar | sf::Style::Close" tells SFML to remove resize button
    sf::RenderWindow window(sf::VideoMode(500, 500), "Tic Tac Toe", sf::Style::Titlebar | sf::Style::Close);

    // Array with all visual board squares
    sf::RectangleShape boardSquares[9];
    for (int x = 0; x < 3; x++)
    {
        for (int y = 0; y < 3; y++)
        {
            boardSquares[x * 3 + y] = sf::RectangleShape(sf::Vector2f(80, 80));
            boardSquares[x * 3 + y].move(sf::Vector2f(130 + 80 * x, 130 + 80 * y));
            boardSquares[x * 3 + y].setFillColor(sf::Color(255, 255, 255, 0));
            boardSquares[x * 3 + y].setOutlineColor(sf::Color::White);
            boardSquares[x * 3 + y].setOutlineThickness(4.f);
        }
    }

    // array that tracks where x's and o's are
    // 0 = empty, 1 = potato, 2 = steak
    int board[3][3] =
    {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}
    };

    // Array of sprites for each square
    sf::Sprite sprites[3][3];

    // POTATO IMAGE
    sf::Texture potato;
    potato.loadFromFile("potato.png");

    // STEAK IMAGE
    sf::Texture steak;
    steak.loadFromFile("steak.png");

    // FONT
    sf::Font font;
    font.loadFromFile("font.ttf");

    // TIE TEXT
    sf::Text tieText;
    tieText.setFont(font);
    tieText.setCharacterSize(50);
    tieText.setString("Tie!");
    tieText.setPosition(sf::Vector2f(205, 400));

    // TITLE TEXT
    sf::Text titleText;
    titleText.setFont(font);
    titleText.setCharacterSize(60);
    titleText.setString("TicTacToe");
    titleText.setPosition(sf::Vector2f(115, 30));

    // MAIN LOOP
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
            {
                if (checkMouse(board, playerTurn, window) == true)
                {
                    if (playerTurn == 1)
                        playerTurn = 2;
                    else if (playerTurn == 2)
                        playerTurn = 1;
                    turns++;

                    updateSprites(sprites, board, potato, steak);

                }
            }
        }

        window.clear();

        for (int i = 0; i < 9; i++)
        {
            window.draw(boardSquares[i]);
        }
        for (int x = 0; x < 3; x++)
        {
            for (int y = 0; y < 3; y++)
            {
                window.draw(sprites[x][y]);
            }
        }

        window.draw(titleText);

        // WIN CONDITIONS
        if (winner(font, board).getString() != '0') {
            window.draw(winner(font, board));
        }
        // TIE CONDITION
        else if (turns == 9)
        {
            window.draw(tieText);
        }

        window.display();


        // WIN and TIE conditions
        if (winner(font, board).getString() != '0' || turns == 9)
        {
            Sleep(2000); // 2000 MILLISECONDS = 2 SECONDS
            window.close();
        }

    }

    return 0;
}