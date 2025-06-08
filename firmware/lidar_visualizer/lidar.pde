import processing.serial.*;

Serial myPort;
String incomingData = "";
float angleDeg, distance;
ArrayList<PVector> points = new ArrayList<PVector>();

void setup() {
  size(600, 600);
  background(0);

  // Set up serial on COM6 with 115200 baud rate
  myPort = new Serial(this, "COM6", 460800);
  myPort.bufferUntil('\n');
}

void draw() {
  background(0);
  translate(width / 2, height / 2);
  drawRadar();

  // Use a copy of points list to avoid concurrent modification
  stroke(0, 255, 0);
  fill(0, 255, 0);
  synchronized(points) {
    for (PVector p : new ArrayList<PVector>(points)) {
      ellipse(p.x, p.y, 2, 2);
    }
  }
}

void serialEvent(Serial port) {
  incomingData = port.readStringUntil('\n');
  if (incomingData != null) {
    incomingData = trim(incomingData);
    String[] parts = split(incomingData, ",");

    if (parts.length == 2) {
      try {
        angleDeg = float(parts[0]);
        distance = float(parts[1]);

        float angleRad = radians(angleDeg);
        float scale = 0.58;
        float x = distance * cos(angleRad) * scale;
        float y = distance * sin(angleRad) * scale;

        synchronized(points) {
          points.add(new PVector(x, y));
          if (points.size() > 300) {
            points.remove(0);
          }
        }
      } catch (Exception e) {
        println("Error parsing input: " + incomingData);
      }
    }
  }
}


void drawRadar() {
  stroke(0, 255, 0);
  noFill();
  
  // Draw range circles
  for (int r = 100; r <= 300; r += 50) {
    ellipse(0, 0, r * 2, r * 2);
  }

  // Sweep line
  float sweepLength = 300;
  float sweepX = sweepLength * cos(radians(angleDeg));
  float sweepY = sweepLength * sin(radians(angleDeg));
  stroke(0, 255, 0, 150);
  line(0, 0, sweepX, sweepY);
}
