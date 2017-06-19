module H = Tea.Html;

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
          P.Arrow (100, 50) (200, 200) 2 P.Black
        ],
      H.div [] [H.text "lorem ipsum below the first picture"]
    ];

let main: Picture.mainType = Interaction.draw myViewNew;
