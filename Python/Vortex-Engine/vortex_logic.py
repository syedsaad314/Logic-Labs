import turtle
import colorsys
import math
import time

class VortexEngine:
    """A high-performance geometric engine designed for visual saturation and OCD-level smoothness."""
    def __init__(self):
        self.screen = turtle.Screen()
        self.screen.title("syedsaad314 | Logic-Labs :: Psychedelic Vortex Engine")
        self.screen.bgcolor("#000000") 
        self.screen.setup(width=1.0, height=1.0) 
        self.screen.tracer(0) 

        self.t = turtle.Turtle()
        self.t.hideturtle()
        self.t.speed(0)
        
        # Professional HEX Palette
        self.hex_palette = [
            "#FF0000", "#9933FF", "#FFFFFF", "#008080", 
            "#00FFFF", "#FF3399", "#8B00FF", "#4B0082", 
            "#0000FF", "#00FF00", "#FFFF00", "#FF6600"
        ]
        
        # Convert HEX to RGB Normalized (0-1) for colorsys compatibility
        self.rgb_palette = [self._hex_to_rgb(h) for h in self.hex_palette]

    def _hex_to_rgb(self, hex_str):
        """Logic to convert HEX strings to normalized RGB tuples."""
        h = hex_str.lstrip('#')
        return tuple(int(h[i:i+2], 16) / 255.0 for i in (0, 2, 4))

    def draw_pulsing_layer(self, rotation, scale_pulse, hue_offset):
        """Renders a single rotating, pulsing geometric layer with high color saturation."""
        for i, base_rgb in enumerate(self.rgb_palette):
            # Shift the hue of the existing palette colors dynamically
            h, s, v = colorsys.rgb_to_hsv(*base_rgb)
            final_rgb = colorsys.hsv_to_rgb((h + hue_offset) % 1.0, s, v)
            self.t.pencolor(final_rgb)

            # Mathematical logic for circular distribution
            t_logic = i / len(self.rgb_palette)
            radius = (120 * scale_pulse) + (240 * t_logic)
            angle = (360 / len(self.rgb_palette)) * i + rotation
            
            x = radius * math.cos(math.radians(angle))
            y = radius * math.sin(math.radians(angle))
            
            self.t.penup()
            self.t.goto(x, y)
            self.t.pendown()
            
            # Draw vortex sub-structures
            for _ in range(3):
                self.t.forward(radius * 0.4)
                self.t.left(120)
                self.t.circle(20 * scale_pulse, 180)

    def run_engine(self):
        """Main rendering loop controlling the animation and logic state."""
        start_time = time.time()
        try:
            while True:
                self.t.clear()
                elapsed = time.time() - start_time
                
                # Logic Constants
                rot = elapsed * 45
                pulse = 1.2 + 0.4 * math.sin(elapsed * 1.5)
                hue_shift = (elapsed * 0.1) % 1.0
                
                # Layer 1: Core Vortex
                self.t.width(3)
                self.draw_pulsing_layer(rot, pulse, hue_shift)
                
                # Layer 2: Outer Saturation
                self.t.width(1)
                self.draw_pulsing_layer(-rot * 0.5, pulse * 1.5, -hue_shift)

                self.screen.update()
        except (turtle.Terminator, Exception):
            print("Engine Shutdown Gracefully.")

if __name__ == "__main__":
    VortexEngine().run_engine()