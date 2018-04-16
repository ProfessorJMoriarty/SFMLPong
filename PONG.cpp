#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <iostream>
using namespace sf;

bool collide(int bx, int by, int bw, int bh, int px, int py, int pw, int ph);

int main()
{
	//these are the same variables from the allegro version of pong
	srand(time(NULL));
	bool keys[2] = { 0,0 }; //should add an enum to make this more readable

	int ball_x = 200;
	int ball_y = 100;
	int ball_dx = 5;
	int ball_dy = 5;

	int paddle_x = 30;
	int paddle_y = 30;


	// Create the window (game screen) of the application
	RenderWindow window(VideoMode(800, 600, 32), "SFML Pong");
	window.setVerticalSyncEnabled(true);

	while (window.isOpen()) //start of game loop
	{

		// Create the left paddle
		RectangleShape leftPaddle;
		leftPaddle.setSize(Vector2f(30, 100));
		leftPaddle.setFillColor(Color(100, 100, 200));

		// Create the ball
		CircleShape ball;
		ball.setRadius(20);
		ball.setFillColor(Color::White);

		//set initial positions
		leftPaddle.setPosition(paddle_x, paddle_y);
		ball.setPosition(ball_x, ball_y);


		// check all the window's events that were triggered since the last iteration of the loop
		Event event;
		while (window.pollEvent(event))
		{

			//IO SECTION////////////////////////////////////////////////////////////////////
			//window close event
			if (event.type == Event::Closed)
				window.close();

			//key press event
			if ((event.type == Event::KeyPressed)) {

				// Move the player's paddle
				if (Keyboard::isKeyPressed(Keyboard::Up)) {
					keys[0] = true;
				}

				if (Keyboard::isKeyPressed(Keyboard::Down)) {
					keys[1] = true;
				}
			}
			if (event.type == sf::Event::KeyReleased) {
				if (event.key.code == sf::Keyboard::Up) {
					keys[0] = false;
				}

				if (event.key.code == sf::Keyboard::Down) {
					keys[1] = false;
				}

			}
		}
		/////////////////////////////////////////////////////////////////////////////

		////////////PHYSICS ENGINE////////////////////////////////////////////////////
				//I don't know how to do timer events in SFML
				//in the meantime, this works-
				//we just can't adjust the overall game speed

		//move the paddle
		if (keys[0] == true)
			paddle_y -= 8;
		if (keys[1] == true)
			paddle_y += 8;

		// Move the ball
		ball_x += ball_dx;
		ball_y += ball_dy;
		if (ball_x > 800 - 30 || ball_x < 0)
			ball_dx *= -1;
		if (ball_y > 600 - 30 || ball_y < 0)
			ball_dy *= -1;

		//check collision and reflect
		if (collide(ball_x, ball_y, 32, 32, paddle_x, paddle_y, 32, 100)) {
			//play sound effect
			ball_dx *= -1;
		}

		//update positions
		ball.setPosition(ball_x, ball_y);
		leftPaddle.setPosition(paddle_x, paddle_y);
		//////////////////////////////////////////////////////////////////////////////



		//RENDER SECTION///////////////////////////////////////////////////////////////
		// clear the window with black color
		window.clear(Color::Black);

		//draw stuff
		window.draw(ball);
		window.draw(leftPaddle);

		//flip the screen
		window.display();

		/////////////////////////////////////////////////////////////////////////////


	}//end game loop

	return 0;
}//end main


//function definitions
//collide function EXACTLY the same as Allegro version :D
bool collide(int bx, int by, int bw, int bh, int px, int py, int pw, int ph) {
	if ((bx + bw > px) && //ball has collided with left side of paddle
		(bx < px + pw) && //ball has hit right side of paddle
		(by + bh > py) && //ball has hit top of paddle
		(by < py + ph)) //ball has hit bottom of paddle
		return true;
	else
		return false;

}