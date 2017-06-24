module H = Tea.Html;

module HA = Tea.Html.Attributes;

module P = Picture;

let myViewNew =
  H.div
    []
    [
      H.h1 [] [H.text "A drawing"],
      P.picture
        (1000, 300)
        [
          P.Circle (100, 100) 50 P.Pink,
          P.Rect (100, 100) 500 20 P.Red,
          P.Line (100, 50) (600, 100) 1 P.Green,
          P.Arrow (100, 50) (200, 200) 2 P.Black,
          P.Polygon [(10, 10), (30, 10), (50, 60), (20, 90)] P.Yellow,
          P.Polyline [(110, 10), (130, 10), (150, 60), (120, 90)] P.Green,
          P.Image (500, 0) 100 100 "http://kinetium.com/images/prism.gif"
        ],
      H.div [] [H.text "lorem ipsum below the first picture"]
    ];

let main: Picture.simpleDisplay = Interaction.draw myViewNew;
