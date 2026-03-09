import turtle
import colorsys

# Screen Setup for maximum visual impact
screen = turtle.Screen()
screen.setup(width=800, height=800)
screen.bgcolor("black")
screen.title("Logic-Labs: Neon Hypnosis Engine")
screen.tracer(0) # Turns off animation to allow manual screen updates (OCD-level smoothness)

t = turtle.Turtle()
t.hideturtle()
t.speed(0)
t.width(2)

def draw_neon_star():
    hue = 0
    # The 'rotation' variable creates the moving animation effect
    for rotation in range(360):
        t.clear() # Clears the frame
        for i in range(120):
            # Smooth color transition logic
            color = colorsys.hsv_to_rgb(hue + (i/120), 1, 1)
            t.pencolor(color)
            
            # Mathematical symmetry logic
            t.penup()
            t.goto(0,0)
            t.setheading(rotation + (i * 10))
            t.pendown()
            t.forward(i * 2)
            t.right(120)
            t.forward(i)
            t.circle(i, 60)
            
        screen.update() # Renders the entire frame at once
        hue += 0.01

if __name__ == "__main__":
    try:
        draw_neon_star()
    except:
        print("Animation Closed.")

screen.exitonclick()