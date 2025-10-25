
// modules innit bruv
#include <SFML/Graphics.hpp>


#define WINDOW_BOUNCE 0.9f
#define WALL_BOUNCE 0.6f
#define BOUNCER_BOUNCE 1.05f
#define DEADENER_BOUNCE 0.08f

#define POWER_MULTIPLIER 800.0f


// extension for sfml thing
// it doesnt work properly and idk why, seemed fine on FlagNinja
namespace sf {

	// division operator
	Vector2f operator/(sf::Vector2f a, sf::Vector2f b) {
		a.x /= b.x;
		a.y /= b.y;
		return a;
	}

	// multiplication operator
	Vector2f operator*(sf::Vector2f a, sf::Vector2f b) {
		a.x *= b.x;
		a.y *= b.y;
		return a;
	}

	// multiplication assignment operator
	Vector2f operator*=(sf::Vector2f a, sf::Vector2f b) {
		a = a * b;
		return a;
	}

	Vector2f operator+=(sf::Vector2f a, sf::Vector2f b) {
		a = a + b;
		return a;
	}
}

// container for window values
namespace Window {
	unsigned int width = 800;
	unsigned int height = 600;
	const char* title = "Ballz";
}


class Obstacle : public sf::RectangleShape
{
public:
	float bounce = WALL_BOUNCE;
};



class Ball : public sf::CircleShape
{
	// stop the ball from being outside the window
	void KeepWithinWindow()
	{
		// get values to make more readable
		const sf::Vector2f& pos = getPosition();
		const float radius = getRadius();

		// left of window
		if (pos.x - radius < 0.0f)
		{
			move(-pos.x + radius, 0);
			velocity.x = -velocity.x * WINDOW_BOUNCE;
		}

		// right of window
		if (pos.x + radius > Window::width)
		{
			move(Window::width - (pos.x + radius), 0);
			velocity.x = -velocity.x * WINDOW_BOUNCE;
		}

		// top of window
		if (pos.y - radius < 0.0f)
		{
			move(0, -pos.y + radius);
			velocity.y = -velocity.y * WINDOW_BOUNCE;
		}

		// bottom of window
		if (pos.y + radius > Window::height)
		{
			move(0, Window::height - (pos.y + radius));
			velocity.y = -velocity.y * WINDOW_BOUNCE;
		}
	}

public:
	sf::Vector2f velocity;

	// consturctor
	Ball(float radius) : sf::CircleShape(radius)
	{
		setOrigin(radius, radius);
		setPosition(Window::width / 2.0f, Window::height / 2.0f);  // spawn ball in the middle of the screen
	}

	// update velocity, check collisions
	void Update()
	{
		// update velocity
		velocity.x *= 0.999f;  // drag
		velocity.y += 5.0f;  // gravity

		// stop the ball going outside the window
		KeepWithinWindow();
	}

	void Move(float deltaTime = 1.f / 60.0f)  // assume fps is 60, cba to do this properly
	{
		move(velocity * deltaTime);
	}

	void CheckCollisionWithRect(const Obstacle& sprite, const float deltaTime = 1.0f / 60.0f)
	{
		// get values to make more readable
		const sf::Vector2f& pos = getPosition();
		const float radius = getRadius();
		sf::Vector2f size(radius, radius);
		sf::Vector2f spritePos = sprite.getPosition();
		sf::Vector2f spriteSize = sprite.getSize();

		// check if entity is moving
		if (velocity.x == 0 && velocity.y == 0) return;

		// expand target by player size
		spritePos -= size / 2.0f;
		spriteSize += size;

		// simulate a ray between the current position and next position
		const sf::Vector2f& ray_origin = pos + (size / 2.0f);
		const sf::Vector2f& ray_dir = velocity * deltaTime;

		// check where in the ray a collision occurred
		sf::Vector2f t_near = (spritePos - ray_origin) / ray_dir;
		sf::Vector2f t_far = (spritePos + spriteSize - ray_origin) / ray_dir;

		// if any values are not a number then exit early
		if (std::isnan(t_far.y) || std::isnan(t_far.x) || std::isnan(t_near.y) || std::isnan(t_near.x)) return;

		// make sure the near time is smaller than the far time
		if (t_near.x > t_far.x) std::swap(t_near.x, t_far.x);
		if (t_near.y > t_far.y) std::swap(t_near.y, t_far.y);

		// if a collision has not occurred then exit early
		if (t_near.x > t_far.y || t_near.y > t_far.x) return;

		// get collision point
		float contact_time = std::max(t_near.x, t_near.y);
		float t_hit_far = std::min(t_far.x, t_far.y);

		// if the collision is behind or infront of the ray then exit early
		if (contact_time < 0.0f || contact_time >= 1.0f) return;
		if (t_hit_far < 0) return;

		// calculate the contact normal to resolve the collision
		sf::Vector2f contactAxis;
		if (t_near.x > t_near.y)
			contactAxis = { 1.0f, 0.0f };
		else if (t_near.x < t_near.y)
			contactAxis = { 0.0f, 1.0f };
		else
			contactAxis = { 1.0f, 1.0f };

		// resolve collision
		velocity = velocity + (velocity * contactAxis * - (1.0f + sprite.bounce));
	}
};


int main()
{

	// create the window
	sf::RenderWindow window(sf::VideoMode(Window::width, Window::height), Window::title);
	window.setFramerateLimit(60);

	// create object
	Ball urMom(5.0f);
	urMom.setFillColor(sf::Color::White);

	std::vector<Obstacle> walls;

	{
		Obstacle wall;
		wall.setPosition(500.0f, 400.0f);
		wall.setSize({ 50.0f, 150.0f });
		walls.push_back(wall);
	}
	{
		Obstacle wall;
		wall.setPosition(10.0f, 150.0f);
		wall.setSize({ 200.0f, 50.0f });
		walls.push_back(wall);
	}
	{
		Obstacle wall;
		wall.setPosition(80.0f, 350.0f);
		wall.setSize({ 300.0f, 140.0f });
		wall.setFillColor(sf::Color::Yellow);
		wall.bounce = BOUNCER_BOUNCE;
		walls.push_back(wall);
	}
	{
		Obstacle wall;
		wall.setPosition(500.0f, 100.0f);
		wall.setSize({ 50.0f, 50.0f });
		wall.setFillColor(sf::Color::Black);
		wall.bounce = DEADENER_BOUNCE;
		walls.push_back(wall);
	}


	// game loop
	while (window.isOpen())
	{
		// get mouse pos
		sf::Vector2f targetDir = (sf::Vector2f)sf::Mouse::getPosition(window) - urMom.getPosition();
		targetDir /= sqrt(targetDir.x * targetDir.x + targetDir.y * targetDir.y);
		
		// handle events
		sf::Event sfEvent;
		while (window.pollEvent(sfEvent))
		{
			// close window button
			if (sfEvent.type == sf::Event::Closed)
				window.close();

			// hit ball if mouse button released
			if (sfEvent.type == sf::Event::MouseButtonReleased)
			{
				urMom.velocity = targetDir * POWER_MULTIPLIER;
			}

		}

		// setup power line
		sf::VertexArray lines(sf::LinesStrip, 2);
		lines[0].position = urMom.getPosition();
		lines[1].position = urMom.getPosition() + targetDir * 30.0f;

		// update ball physics
		urMom.Update();
		for (auto& wall : walls)
			urMom.CheckCollisionWithRect(wall);
		urMom.Move();

		// draw objects
		window.draw(urMom);
		for (auto& wall : walls)
			window.draw(wall);
		window.draw(lines);

		// update window
		window.display();
		window.clear(sf::Color(0x1e1e1eff));
	}
}