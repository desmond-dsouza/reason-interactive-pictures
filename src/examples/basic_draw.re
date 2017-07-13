module P = Picture;

let view =
  P.picture
    (1000, 600)
    [
      P.Circle (100, 100) 50 P.Pink,
      P.Rect (100, 100) 300 20 P.Purple,
      P.Line (100, 50) (600, 100) 3 P.Green,
      P.Arrow (100, 50) (100, 100) 5 P.Black,
      P.Polygon [(120, 150), (100, 180), (120, 190), (130, 200), (150, 160)] P.Blue,
      P.Polyline [(120, 250), (100, 280), (120, 290), (130, 300), (150, 260)] P.Green,
      P.Image (120, 350) 130 130 "http://cdn2-www.dogtime.com/assets/uploads/2010/12/puppies.jpg",
      P.Text (320, 350) "Hello",
      P.Labeled "speed" (P.Arrow (320, 380) (350, 400) 1 P.Brown),
      P.Arrow (320, 280) (450, 400) 1 P.Brown
    ];

let main: Picture.simpleDisplay = Interaction.draw view;
