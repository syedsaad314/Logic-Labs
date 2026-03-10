import turtle
import math
import colorsys

class Epicycle:
    """Mathematical model for a single rotating circle in a Fourier series."""
    def __init__(self, radius, frequency, phase):
        self.radius = radius
        self.frequency = frequency
        self.phase = phase

    def compute_position(self, time):
        """Calculates the (x, y) offset based on rotation logic."""
        angle = self.frequency * time + self.phase
        x = self.radius * math.cos(angle)
        y = self.radius * math.sin(angle)
        return x, y

class FourierRenderer:
    """Engine to render complex mathematical paths using epicycles."""
    def __init__(self):
        self.screen = turtle.Screen()
        self.screen.bgcolor("#0a0a0a") # Deep OLED black
        self.screen.setup(width=900, height=900)
        self.screen.tracer(0)
        
        self.pen = turtle.Turtle()
        self.pen.hideturtle()
        self.pen.speed(0)
        
        self.path_pen = turtle.Turtle()
        self.path_pen.hideturtle()
        self.path_pen.color("#00ffcc") # Neon Mint
        self.path_pen.width(2)
        
        self.circles = self._generate_series()
        self.path = []

    def _generate_series(self):
        """Creates a series of circles with decreasing radii (Square Wave logic)."""
        series = []
        for i in range(1, 15, 2): # High-order harmonics
            radius = 150 * (4 / (i * math.pi))
            series.append(Epicycle(radius, i, 0))
        return series

    def render(self):
        time = 0
        while True:
            self.pen.clear()
            cx, cy = 0, 0 # Starting origin
            
            # Mathematical Logic: Summation of Vectors
            for i, circle in enumerate(self.circles):
                prev_x, prev_y = cx, cy
                dx, dy = circle.compute_position(time)
                cx += dx
                cy += dy
                
                # Draw the rotating mechanism (Engine view)
                self.pen.penup()
                self.pen.goto(prev_x, prev_y)
                self.pen.pendown()
                hue = (i / len(self.circles))
                self.pen.pencolor(colorsys.hsv_to_rgb(hue, 0.8, 1))
                self.pen.circle(circle.radius)
                self.pen.goto(cx, cy)

            # Trace the resulting path
            self.path.insert(0, (cx, cy))
            self.path_pen.clear()
            self.path_pen.penup()
            for i, pos in enumerate(self.path):
                if i > 500: break # Keep memory clean
                self.path_pen.goto(pos)
                self.path_pen.pendown()
            
            self.screen.update()
            time += 0.05

if __name__ == "__main__":
    engine = FourierRenderer()
    engine.render()